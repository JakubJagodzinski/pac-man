#include "monster.h"

void Monster::display(bool is_chasing) const {
    if (!this->is_eaten) {
        go_to_x_y(this->x, this->y);
        if (is_chasing) {
            RED_TEXT_INTENSITY_BACKGROUND
        } else {
            BLUE_TEXT_INTENSITY_BACKGROUND
        }
        cout << 'X';
        INTENSITY_BACKGROUND
    }
}

int16_t Monster::get_x() const {
    return this->x;
}

int16_t Monster::get_y() const {
    return this->y;
}

bool Monster::get_eaten_info() const {
    return this->is_eaten;
}

void Monster::set_eaten_flag(bool value) {
    this->is_eaten = value;
}

void Monster::set_respawn_cool_down(int16_t value) {
    this->respawn_cool_down = value;
}

void Monster::set_x_y(int16_t new_x, int16_t new_y) {
    this->x = new_x;
    this->y = new_y;
}

void Monster::make_move(class Board &board, class Player &player) {
    int16_t player_x = player.get_x();
    int16_t player_y = player.get_y();
    if (!this->is_eaten and !(this->x == player_x and this->y == player_y)) {
        go_to_x_y(this->x, this->y);
        switch (board.get_field(this->x, this->y)) {
            case '$':
                GREEN_TEXT_INTENSITY_BACKGROUND
                cout << '$';
                break;
            case '+':
                PURPLE_TEXT_INTENSITY_BACKGROUND
                cout << '+';
                break;
            case '*':
                LIGHT_BLUE_TEXT_INTENSITY_BACKGROUND
                cout << '*';
                break;
            case '&':
                RED_TEXT_INTENSITY_BACKGROUND
                cout << '*';
                break;
            case '.':
                INTENSITY_BACKGROUND
                cout << '.';
                break;
            case ' ':
                INTENSITY_BACKGROUND
                board.set_field(this->x, this->y, '.');
                cout << '.';
                break;
            default:
                break;
        }
        if (player.get_elixir()) {
            this->make_fleeing_move(board, player_x, player_y);
        } else {
            this->make_chasing_move(board, player_x, player_y);
        }
    }
}

void Monster::make_chasing_move(class Board &board, int16_t player_x, int16_t player_y) {
    if (this->main_direction == HORIZONTALLY) {
        if (this->x < player_x) {
            if (board.get_field(int16_t(this->x + 1), this->y) != '#') {
                ++this->x;
                this->secondary_direction = UNSET;
            } else if (this->secondary_direction == DOWN or this->secondary_direction == UNSET) {
                if (board.get_field(this->x, int16_t(this->y + 1)) != '#') {
                    ++this->y;
                    this->secondary_direction = DOWN;
                } else if (board.get_field(this->x, int16_t(this->y - 1)) != '#') {
                    --this->y;
                    this->secondary_direction = UP;
                }
            } else if (this->secondary_direction == UP) {
                if (board.get_field(this->x, int16_t(this->y - 1)) != '#') {
                    --this->y;
                } else if (board.get_field(this->x, int16_t(this->y + 1)) != '#') {
                    ++this->y;
                    this->secondary_direction = DOWN;
                }
            }
        } else if (this->x > player_x) {
            if (board.get_field(int16_t(this->x - 1), this->y) != '#') {
                --this->x;
                this->secondary_direction = UNSET;
            } else if (this->secondary_direction == DOWN or this->secondary_direction == UNSET) {
                if (board.get_field(this->x, int16_t(this->y + 1)) != '#') {
                    ++this->y;
                    this->secondary_direction = DOWN;
                } else if (board.get_field(this->x, int16_t(this->y - 1)) != '#') {
                    --this->y;
                    this->secondary_direction = UP;
                }
            } else if (this->secondary_direction == UP) {
                if (board.get_field(this->x, int16_t(this->y - 1)) != '#') {
                    --this->y;
                } else if (board.get_field(this->x, int16_t(this->y + 1)) != '#') {
                    ++this->y;
                    this->secondary_direction = DOWN;
                }
            }
        } else {
            this->main_direction = VERTICALLY;
            this->secondary_direction = UNSET;
            this->make_chasing_move(board, player_x, player_y);
        }
    } else {
        if (this->y < player_y) {
            if (board.get_field(this->x, int16_t(this->y + 1)) != '#') {
                ++this->y;
                this->secondary_direction = UNSET;
            } else if (this->secondary_direction == RIGHT or this->secondary_direction == UNSET) {
                if (board.get_field(int16_t(this->x + 1), this->y) != '#') {
                    ++this->x;
                    this->secondary_direction = RIGHT;
                } else if (board.get_field(int16_t(this->x - 1), this->y) != '#') {
                    --this->x;
                    this->secondary_direction = LEFT;
                }
            } else if (this->secondary_direction == LEFT) {
                if (board.get_field(int16_t(this->x - 1), this->y) != '#') {
                    --this->x;
                } else if (board.get_field(int16_t(this->x + 1), this->y) != '#') {
                    ++this->x;
                    this->secondary_direction = RIGHT;
                }
            }
        } else if (this->y > player_y) {
            if (board.get_field(this->x, int16_t(this->y - 1)) != '#') {
                --this->y;
                this->secondary_direction = UNSET;
            } else if (this->secondary_direction == RIGHT or this->secondary_direction == UNSET) {
                if (board.get_field(int16_t(this->x + 1), this->y) != '#') {
                    ++this->x;
                    this->secondary_direction = RIGHT;
                } else if (board.get_field(int16_t(this->x - 1), this->y) != '#') {
                    --this->x;
                    this->secondary_direction = LEFT;
                }
            } else if (this->secondary_direction == LEFT) {
                if (board.get_field(int16_t(this->x - 1), this->y) != '#') {
                    --this->x;
                } else if (board.get_field(int16_t(this->x + 1), this->y) != '#') {
                    ++this->x;
                    this->secondary_direction = RIGHT;
                }
            }
        } else {
            this->main_direction = HORIZONTALLY;
            this->secondary_direction = UNSET;
            this->make_chasing_move(board, player_x, player_y);
        }
    }
}

void Monster::make_fleeing_move(class Board &board, int16_t player_x, int16_t player_y) {
    if (this->main_direction == HORIZONTALLY) {
        if (this->x > player_x) {
            if (board.get_field(int16_t(this->x + 1), this->y) != '#' and this->x + 1 != 93) {
                ++this->x;
                this->secondary_direction = UNSET;
            } else if (this->secondary_direction == DOWN or this->secondary_direction == UNSET) {
                if (board.get_field(this->x, int16_t(this->y + 1)) != '#' and this->y + 1 != 24) {
                    ++this->y;
                    this->secondary_direction = DOWN;
                } else if (board.get_field(this->x, int16_t(this->y - 1)) != '#' and this->y - 1 != 2) {
                    --this->y;
                    this->secondary_direction = UP;
                }
            } else if (this->secondary_direction == UP) {
                if (board.get_field(this->x, int16_t(this->y - 1)) != '#' and this->y - 1 != 2) {
                    --this->y;
                } else if (board.get_field(this->x, int16_t(this->y + 1)) != '#' and this->y + 1 != 24) {
                    ++this->y;
                    this->secondary_direction = DOWN;
                }
            }
        } else if (this->x < player_x) {
            if (board.get_field(int16_t(this->x - 1), this->y) != '#' and this->x - 1 != 3) {
                --this->x;
                this->secondary_direction = UNSET;
            } else if (this->secondary_direction == DOWN or this->secondary_direction == UNSET) {
                if (board.get_field(this->x, int16_t(this->y + 1)) != '#' and this->y + 1 != 24) {
                    ++this->y;
                    this->secondary_direction = DOWN;
                } else if (board.get_field(this->x, int16_t(this->y - 1)) != '#' and this->y - 1 != 2) {
                    --this->y;
                    this->secondary_direction = UP;
                }
            } else if (this->secondary_direction == UP) {
                if (board.get_field(this->x, int16_t(this->y - 1)) != '#' and this->y - 1 != 2) {
                    --this->y;
                } else if (board.get_field(this->x, int16_t(this->y + 1)) != '#' and this->y + 1 != 24) {
                    ++this->y;
                    this->secondary_direction = DOWN;
                }
            }
        } else {
            this->main_direction = VERTICALLY;
            this->secondary_direction = UNSET;
            this->make_fleeing_move(board, player_x, player_y);
        }
    } else {
        if (this->y > player_y) {
            if (board.get_field(this->x, int16_t(this->y + 1)) != '#' and this->y + 1 != 24) {
                ++this->y;
                this->secondary_direction = UNSET;
            } else if (this->secondary_direction == RIGHT or this->secondary_direction == UNSET) {
                if (board.get_field(int16_t(this->x + 1), this->y) != '#' and this->x + 1 != 93) {
                    ++this->x;
                    this->secondary_direction = RIGHT;
                } else if (board.get_field(int16_t(this->x - 1), this->y) != '#' and this->x - 1 != 3) {
                    --this->x;
                    this->secondary_direction = LEFT;
                }
            } else if (this->secondary_direction == LEFT) {
                if (board.get_field(int16_t(this->x - 1), this->y) != '#' and this->x - 1 != 3) {
                    --this->x;
                } else if (board.get_field(int16_t(this->x + 1), this->y) != '#' and this->x + 1 != 93) {
                    ++this->x;
                    this->secondary_direction = RIGHT;
                }
            }
        } else if (this->y < player_y) {
            if (board.get_field(this->x, int16_t(this->y - 1)) != '#' and this->y - 1 != 2) {
                --this->y;
                this->secondary_direction = UNSET;
            } else if (this->secondary_direction == RIGHT or this->secondary_direction == UNSET) {
                if (board.get_field(int16_t(this->x + 1), this->y) != '#' and this->x + 1 != 93) {
                    ++this->x;
                    this->secondary_direction = RIGHT;
                } else if (board.get_field(int16_t(this->x - 1), this->y) != '#' and this->x - 1 != 3) {
                    --this->x;
                    this->secondary_direction = LEFT;
                }
            } else if (this->secondary_direction == LEFT) {
                if (board.get_field(int16_t(this->x - 1), this->y) != '#' and this->x - 1 != 3) {
                    --this->x;
                } else if (board.get_field(int16_t(this->x + 1), this->y) != '#' and this->x + 1 != 93) {
                    ++this->x;
                    this->secondary_direction = RIGHT;
                }
            }
        } else {
            this->main_direction = HORIZONTALLY;
            this->secondary_direction = UNSET;
            this->make_fleeing_move(board, player_x, player_y);
        }
    }
}

void Monster::reduce_respawn_cool_down() {
    if (this->respawn_cool_down) {
        --this->respawn_cool_down;
        if (!this->respawn_cool_down) {
            this->reset_properties();
        }
    }
}

void Monster::set_start_coordinates(int16_t new_x, int16_t new_y) {
    this->x_start = new_x;
    this->y_start = new_y;
}

void Monster::reset_properties() {
    if (!this->is_eaten) {
        go_to_x_y(this->x, this->y);
        cout << ' ';
    }
    this->is_eaten = false;
    this->x = this->x_start;
    this->y = this->y_start;
    this->respawn_cool_down = 0;
    this->secondary_direction = UNSET;
    this->main_direction = HORIZONTALLY;
}
