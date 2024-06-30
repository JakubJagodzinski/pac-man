#include "player.h"

size_t Player::get_points() const {
    return this->points;
}

enum difficulties_t Player::get_difficulty() const {
    return this->difficulty;
}

int16_t Player::get_level() const {
    return this->level;
}

int16_t Player::get_lives() const {
    return this->lives;
}

int16_t Player::get_elixir() const {
    return this->elixir;
}

int16_t Player::get_x() const {
    return this->x;
}

int16_t Player::get_y() const {
    return this->y;
}

void Player::make_move(class Board &board) {
    this->move_up(board);
    this->move_down(board);
    this->move_left(board);
    this->move_right(board);
}

void Player::move_up(class Board &board) {
    if (GetAsyncKeyState(VK_UP) or GetAsyncKeyState('W')) {
        go_to_x_y(this->x, this->y);
        INTENSITY_BACKGROUND
        cout << ' ';
        if (this->x == FIRST_UPPER_X and this->y == FIRST_UPPER_Y) {
            this->x = FIRST_LOWER_X;
            this->y = FIRST_LOWER_Y;
        } else if (this->x == SECOND_UPPER_X and this->y == SECOND_UPPER_Y) {
            this->x = SECOND_LOWER_X;
            this->y = SECOND_LOWER_Y;
        } else if (this->y > 0 and board.get_field(this->x, int16_t(this->y - 1)) != '#') {
            --this->y;
        }
        this->collect_effect_from_field(board);
    }
}

void Player::move_down(class Board &board) {
    if (GetAsyncKeyState(VK_DOWN) or GetAsyncKeyState('S')) {
        go_to_x_y(this->x, this->y);
        INTENSITY_BACKGROUND
        cout << ' ';
        if (this->x == FIRST_LOWER_X and this->y == FIRST_LOWER_Y) {
            this->x = FIRST_UPPER_X;
            this->y = FIRST_UPPER_Y;
        } else if (this->x == SECOND_LOWER_X and this->y == SECOND_LOWER_Y) {
            this->x = SECOND_UPPER_X;
            this->y = SECOND_UPPER_Y;
        } else if (this->y < SCREEN_HEIGHT - 1 and board.get_field(this->x, int16_t(this->y + 1)) != '#') {
            ++this->y;
        }
        this->collect_effect_from_field(board);
    }
}

void Player::move_left(class Board &board) {
    if (GetAsyncKeyState(VK_LEFT) or GetAsyncKeyState('A')) {
        go_to_x_y(this->x, this->y);
        INTENSITY_BACKGROUND
        cout << ' ';
        if (this->x == MIDDLE_UPPER_LEFT_X and this->y == MIDDLE_UPPER_LEFT_Y) {
            this->x = MIDDLE_UPPER_RIGHT_X;
            this->y = MIDDLE_UPPER_RIGHT_Y;
        } else if (this->x == MIDDLE_LOWER_LEFT_X and this->y == MIDDLE_LOWER_LEFT_Y) {
            this->x = MIDDLE_LOWER_RIGHT_X;
            this->y = MIDDLE_LOWER_RIGHT_Y;
        } else if (this->x > 0 and board.get_field(int16_t(this->x - 1), this->y) != '#') {
            --this->x;
        }
        this->collect_effect_from_field(board);
    }
}

void Player::move_right(class Board &board) {
    if (GetAsyncKeyState(VK_RIGHT) or GetAsyncKeyState('D')) {
        go_to_x_y(this->x, this->y);
        INTENSITY_BACKGROUND
        cout << ' ';
        if (this->x == MIDDLE_UPPER_RIGHT_X and this->y == MIDDLE_UPPER_RIGHT_Y) {
            this->x = MIDDLE_UPPER_LEFT_X;
            this->y = MIDDLE_UPPER_LEFT_Y;
        } else if (this->x == MIDDLE_LOWER_RIGHT_X and this->y == MIDDLE_LOWER_RIGHT_Y) {
            this->x = MIDDLE_LOWER_LEFT_X;
            this->y = MIDDLE_LOWER_LEFT_Y;
        } else if (this->x < SCREEN_WIDTH - 1 and board.get_field(int16_t(this->x + 1), this->y) != '#') {
            ++this->x;
        }
        this->collect_effect_from_field(board);
    }
}

void Player::collect_effect_from_field(class Board &board) {
    char c = board.get_field(this->x, this->y);
    switch (c) {
        case '.':
            this->points += this->points_multiplier;
            if (this->hunger) {
                --this->hunger;
            }
            break;
        case '$':
            DOLLAR_SOUND
            this->points_multiplier_time = SET_TIME;
            ++this->points_multiplier;
            break;
        case '+':
            ELIXIR_SOUND
            this->elixir = SET_TIME;
            break;
        case '*':
            FROZEN_SOUND
            if (this->freeze) {
                this->freeze = false;
                this->freeze_time = 0;
                this->is_frozen = true;
                this->frozen_time = SET_TIME;
            } else {
                this->freeze = true;
                this->freeze_time = SET_TIME;
            }
            break;
        case '&':
            BOMB_SOUND
            --this->lives;
            this->display_lives();
            if (this->lives == 0) {
                Sleep(1000);
            }
            break;
        default:
            break;
    }
    board.set_field(this->x, this->y, ' ');
}

void Player::reduce_frozen_time() {
    if (this->frozen_time) {
        --this->frozen_time;
        if (!this->frozen_time) {
            this->is_frozen = false;
            GetAsyncKeyState(VK_UP);
            GetAsyncKeyState(VK_DOWN);
            GetAsyncKeyState(VK_LEFT);
            GetAsyncKeyState(VK_RIGHT);
            GetAsyncKeyState('W');
            GetAsyncKeyState('S');
            GetAsyncKeyState('A');
            GetAsyncKeyState('D');
        }
    }
}

void Player::reduce_freeze_time(int16_t tick) {
    if (this->freeze_time and tick % this->freeze_reduce_speed == 0) {
        --this->freeze_time;
        if (!this->freeze_time) {
            this->freeze = false;
        }
    }
}

void Player::reduce_elixir() {
    if (this->elixir) {
        --this->elixir;
    }
}

void Player::reduce_points_multiplier_time(int16_t time_tick) {
    if (this->points_multiplier_time and time_tick % this->points_multiplier_speed == 0) {
        --this->points_multiplier_time;
        if (!this->points_multiplier_time) {
            this->points_multiplier = 1;
        }
    }
}

void Player::increase_hunger(int16_t time_tick, class Monster (&monsters)[], int16_t monsters_in_game, bool &pause) {
    if (time_tick % this->hunger_speed == 0) {
        ++this->hunger;
        if (this->hunger == 100) {
            go_to_x_y(this->x, this->y);
            cout << ' ';
            pause = true;
            --this->lives;
            this->reset_properties();
            for (int16_t i = 0; i < monsters_in_game; ++i) {
                monsters[i].reset_properties();
            }
            HUNGER_DEATH_SOUND
            go_to_x_y(42, 25);
            RED_TEXT
            cout << "UMARLES Z GLODU!";
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(42, 26);
            cout << string(16, ' ');
            go_to_x_y(42, 27);
            cout << "[SPACJA] START";
            INTENSITY_BACKGROUND
            GetAsyncKeyState(VK_SPACE);
        }
    }
}

void Player::check_if_eaten(class Monster (&monsters)[], int16_t monsters_in_game, bool &pause) {
    for (int i = 0; i < monsters_in_game; ++i) {
        if (!monsters[i].get_eaten_info() and monsters[i].get_x() == this->x and monsters[i].get_y() == this->y) {
            if (this->elixir) {
                this->display();
                monsters[i].set_eaten_flag(true);
                monsters[i].set_respawn_cool_down(SET_TIME);
                monsters[i].set_x_y(0, 0);
                this->elixir = 0;
                this->hunger = this->hunger - this->hunger_reduce < 0 ? 0 : this->hunger - this->hunger_reduce;
                this->points += this->add_points_for_monster;
                MONSTER_EATEN_SOUND
                break;
            } else {
                monsters[i].display(this->get_elixir());
                --this->lives;
                this->reset_properties();
                for (int j = 0; j < monsters_in_game; ++j) {
                    monsters[j].reset_properties();
                }
                pause = true;
                PLAYER_EATEN_SOUND
                go_to_x_y(42, 25);
                RED_TEXT
                cout << "ZJEDZONO CIE!";
                go_to_x_y(42, 26);
                WHITE_TEXT_BLACK_BACKGROUND
                cout << string(16, ' ');
                go_to_x_y(42, 27);
                cout << "[SPACJA] START";
                INTENSITY_BACKGROUND
                GetAsyncKeyState(VK_SPACE);
                break;
            }
        }
    }
}

void Player::check_next_level(class Board &board, class Monster (&monsters)[], int16_t monsters_in_game, bool &pause) {
    if (this->points >= this->floor_points and this->get_points() <= this->ceil_points) {
        pause = true;
        ++this->level;
        this->floor_points += this->points_gap;
        this->ceil_points += this->points_gap;
        for (int i = 0; i < monsters_in_game; ++i) {
            monsters[i].reset_properties();
        }
        this->reset_properties();
        board.display_next_map(*this, monsters, monsters_in_game);
        go_to_x_y(43, 25);
        GREEN_TEXT
        cout << "NOWY POZIOM!";
        WHITE_TEXT_BLACK_BACKGROUND
        go_to_x_y(40, 26);
        cout << string(16, ' ');
        go_to_x_y(42, 27);
        cout << "[SPACJA] START";
        NEW_LEVEL_SOUND
        GetAsyncKeyState(VK_SPACE);
    }
}

void Player::display() const {
    if (this->lives) {
        go_to_x_y(this->x, this->y);
        if (this->freeze) {
            LIGHT_BLUE_TEXT_INTENSITY_BACKGROUND
        } else if (this->elixir) {
            if (this->is_frozen) {
                RED_TEXT_LIGHT_BLUE_BACKGROUND
            } else {
                RED_TEXT_INTENSITY_BACKGROUND
            }
        } else if (this->is_frozen) {
            BLUE_TEXT_LIGHT_BLUE_BACKGROUND
        } else {
            BLUE_TEXT_INTENSITY_BACKGROUND
        }
        cout << '0';
        INTENSITY_BACKGROUND
        this->display_statistics();
    }
}

void Player::display_statistics() const {
    this->display_points();
    this->display_hunger();
    this->display_elixir_time();
    this->display_frozen_time();
    this->display_level();
    this->display_lives();
}

void Player::display_lives() const {
    go_to_x_y(89, 26);
    WHITE_TEXT_BLACK_BACKGROUND
    cout << this->lives;
    INTENSITY_BACKGROUND
}

void Player::display_level() const {
    go_to_x_y(12, 1);
    WHITE_TEXT_BLACK_BACKGROUND
    cout << this->level;
    INTENSITY_BACKGROUND
}

void Player::display_points() const {
    go_to_x_y(12, 26);
    WHITE_TEXT_BLACK_BACKGROUND
    if (this->points_multiplier > 1) {
        cout << this->points;
        GREEN_TEXT
        cout << " x" << this->points_multiplier << ' ';
        go_to_x_y(51, 26);
        cout << this->points_multiplier_time << ' ';
    } else {
        cout << this->points << string(6, ' ');
        go_to_x_y(51, 26);
        cout << "  ";
    }
    INTENSITY_BACKGROUND
}

void Player::display_hunger() const {
    if (this->hunger) {
        go_to_x_y(42, 26);
        RED_TEXT
        cout << this->hunger << ' ';
        INTENSITY_BACKGROUND
    }
}

void Player::display_elixir_time() const {
    go_to_x_y(45, 26);
    if (this->elixir) {
        PURPLE_TEXT
        cout << this->elixir << ' ';
    } else {
        WHITE_TEXT_BLACK_BACKGROUND
        cout << "  ";
    }
    INTENSITY_BACKGROUND
}

void Player::display_frozen_time() const {
    go_to_x_y(54, 26);
    if (this->freeze) {
        LIGHT_BLUE_TEXT
        cout << this->freeze_time << ' ';
    } else if (this->is_frozen) {
        BLUE_TEXT
        cout << this->frozen_time << ' ';
    } else {
        WHITE_TEXT_BLACK_BACKGROUND
        cout << "  ";
    }
    INTENSITY_BACKGROUND
}

void Player::set_easy_difficulty() {
    this->difficulty = DIFFICULTIES_EASY;
    this->lives = EASY_LIVES;
    this->hunger_speed = EASY_HUNGER_SPEED;
    this->hunger_reduce = EASY_HUNGER_REDUCE;
    this->points_multiplier_speed = EASY_DOLLAR_SPEED;
    this->add_points_for_monster = EASY_ADD_POINTS_FOR_MONSTER;
    this->points_gap = EASY_POINTS_GAP;
    this->floor_points = this->points_gap;
    this->ceil_points = 2 * this->points_gap;
    this->freeze_delay = EASY_FREEZE_DELAY;
    this->freeze_reduce_speed = EASY_FREEZE_REDUCE_SPEED;
}

void Player::set_medium_difficulty() {
    this->difficulty = DIFFICULTIES_MEDIUM;
    this->lives = MEDIUM_LIVES;
    this->hunger_speed = MEDIUM_HUNGER_SPEED;
    this->hunger_reduce = MEDIUM_HUNGER_REDUCE;
    this->points_multiplier_speed = MEDIUM_DOLLAR_SPEED;
    this->add_points_for_monster = MEDIUM_ADD_POINTS_FOR_MONSTER;
    this->points_gap = MEDIUM_POINTS_GAP;
    this->floor_points = this->points_gap;
    this->ceil_points = 2 * this->points_gap;
    this->freeze_delay = MEDIUM_FREEZE_DELAY;
    this->freeze_reduce_speed = MEDIUM_FREEZE_REDUCE_SPEED;
}

void Player::set_hard_difficulty() {
    this->difficulty = DIFFICULTIES_HARD;
    this->lives = HARD_LIVES;
    this->hunger_speed = HARD_HUNGER_SPEED;
    this->hunger_reduce = HARD_HUNGER_REDUCE;
    this->points_multiplier_speed = HARD_DOLLAR_SPEED;
    this->add_points_for_monster = HARD_ADD_POINTS_FOR_MONSTER;
    this->points_gap = HARD_POINTS_GAP;
    this->floor_points = this->points_gap;
    this->ceil_points = 2 * this->points_gap;
    this->freeze_delay = HARD_FREEZE_DELAY;
    this->freeze_reduce_speed = HARD_FREEZE_REDUCE_SPEED;
}

void Player::set_hardcore_difficulty() {
    this->difficulty = DIFFICULTIES_HARDCORE;
    this->lives = HARDCORE_LIVES;
    this->hunger_speed = HARDCORE_HUNGER_SPEED;
    this->hunger_reduce = HARDCORE_HUNGER_REDUCE;
    this->points_multiplier_speed = HARDCORE_DOLLAR_SPEED;
    this->add_points_for_monster = HARDCORE_ADD_POINTS_FOR_MONSTER;
    this->points_gap = HARDCORE_POINTS_GAP;
    this->floor_points = this->points_gap;
    this->ceil_points = 2 * this->points_gap;
    this->freeze_delay = HARDCORE_FREEZE_DELAY;
    this->freeze_reduce_speed = HARDCORE_FREEZE_REDUCE_SPEED;
}

void Player::reset_properties() {
    this->x = this->x_start;
    this->y = this->y_start;
    this->hunger = 0;
    this->points_multiplier = 1;
    this->points_multiplier_time = 0;
    this->elixir = 0;
    this->is_frozen = false;
    this->frozen_time = 0;
    this->freeze = false;
    this->freeze_time = 0;
}
