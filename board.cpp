#include "board.h"

char Board::get_field(int16_t x, int16_t y) const {
    return this->map[y][x];
}

void Board::set_field(int16_t x, int16_t y, char c) {
    this->map[y][x] = c;
}

void Board::load(const char *filename) {
    fstream fin(filename, ios::in);
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        string line;
        getline(fin, line);
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            *(*(this->map + y) + x) = line[x];
        }
    }
    fin.close();
}

void Board::display_start_game_screen() {
    this->load(FILE_START_GAME_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '/':
                    BLUE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '^':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                default:
                    INTENSITY_BACKGROUND
                    cout << c;
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
            }
        }
        cout << endl;
    }
    YELLOW_TEXT
    go_to_x_y(28, 22);
    cout << " NACISNIJ DOWOLNY KLAWISZ, ABY ROZPOCZAC ";
    WHITE_TEXT_BLACK_BACKGROUND
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    while (!kbhit());
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

enum menu_options_t Board::display_menu_screen() {
    this->load(FILE_MENU_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '/':
                    BLUE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '^':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case ' ':
                    INTENSITY_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                default:
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    static int16_t choice = MENU_START_GAME;
    WHITE_TEXT_BLACK_BACKGROUND
    go_to_x_y(34, 14);
    cout << "GRAJ";
    go_to_x_y(34, 15);
    cout << "RANKING";
    go_to_x_y(34, 16);
    cout << "USTAWIENIA";
    go_to_x_y(34, 17);
    cout << "POMOC";
    go_to_x_y(34, 18);
    cout << "AUTOR";
    go_to_x_y(34, 19);
    cout << "WYJSCIE";
    go_to_x_y(32, int16_t(14 + choice));
    YELLOW_TEXT
    switch (choice) {
        case MENU_START_GAME:
            cout << "> GRAJ";
            break;
        case MENU_SHOW_SCOREBOARD:
            cout << "> RANKING";
            break;
        case MENU_SETTINGS:
            cout << "> USTAWIENIA";
            break;
        case MENU_HELP:
            cout << "> POMOC";
            break;
        case MENU_CREDITS:
            cout << "> AUTOR";
            break;
        case MENU_QUIT_GAME:
            cout << "> WYJSCIE";
            break;
        default:
            break;
    }
    GetAsyncKeyState(VK_ESCAPE);
    GetAsyncKeyState(VK_SPACE);
    GetAsyncKeyState(VK_RETURN);
    GetAsyncKeyState(VK_DOWN);
    GetAsyncKeyState(VK_UP);
    GetAsyncKeyState('W');
    GetAsyncKeyState('S');
    bool eyes_closed = false;
    int blink_tick = 0;
    while (true) {
        if (GetAsyncKeyState(VK_DOWN) or GetAsyncKeyState('S')) {
            GetAsyncKeyState(VK_DOWN);
            GetAsyncKeyState('S');
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(32, int16_t(14 + choice));
            cout << "  ";
            switch (choice) {
                case MENU_START_GAME:
                    cout << "GRAJ";
                    break;
                case MENU_SHOW_SCOREBOARD:
                    cout << "RANKING";
                    break;
                case MENU_SETTINGS:
                    cout << "USTAWIENIA";
                    break;
                case MENU_HELP:
                    cout << "POMOC";
                    break;
                case MENU_CREDITS:
                    cout << "AUTOR";
                    break;
                case MENU_QUIT_GAME:
                    cout << "WYJSCIE";
                    break;
                default:
                    break;
            }
            if (choice == MENU_QUIT_GAME) {
                choice = MENU_START_GAME;
            } else {
                ++choice;
            }
            YELLOW_TEXT
            go_to_x_y(32, int16_t(14 + choice));
            cout << "> ";
            switch (choice) {
                case MENU_START_GAME:
                    cout << "GRAJ";
                    break;
                case MENU_SHOW_SCOREBOARD:
                    cout << "RANKING";
                    break;
                case MENU_SETTINGS:
                    cout << "USTAWIENIA";
                    break;
                case MENU_HELP:
                    cout << "POMOC";
                    break;
                case MENU_CREDITS:
                    cout << "AUTOR";
                    break;
                case MENU_QUIT_GAME:
                    cout << "WYJSCIE";
                    break;
                default:
                    break;
            }
        } else if (GetAsyncKeyState(VK_UP) or GetAsyncKeyState('W')) {
            GetAsyncKeyState(VK_UP);
            GetAsyncKeyState('W');
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(32, int16_t(14 + choice));
            cout << "  ";
            switch (choice) {
                case MENU_START_GAME:
                    cout << "GRAJ";
                    break;
                case MENU_SHOW_SCOREBOARD:
                    cout << "RANKING";
                    break;
                case MENU_SETTINGS:
                    cout << "USTAWIENIA";
                    break;
                case MENU_HELP:
                    cout << "POMOC";
                    break;
                case MENU_CREDITS:
                    cout << "AUTOR";
                    break;
                case MENU_QUIT_GAME:
                    cout << "WYJSCIE";
                    break;
                default:
                    break;
            }
            if (choice == MENU_START_GAME) {
                choice = MENU_QUIT_GAME;
            } else {
                --choice;
            }
            YELLOW_TEXT
            go_to_x_y(32, int16_t(14 + choice));
            cout << "> ";
            switch (choice) {
                case MENU_START_GAME:
                    cout << "GRAJ";
                    break;
                case MENU_SHOW_SCOREBOARD:
                    cout << "RANKING";
                    break;
                case MENU_SETTINGS:
                    cout << "USTAWIENIA";
                    break;
                case MENU_HELP:
                    cout << "POMOC";
                    break;
                case MENU_CREDITS:
                    cout << "AUTOR";
                    break;
                case MENU_QUIT_GAME:
                    cout << "WYJSCIE";
                    break;
                default:
                    break;
            }
        }
        if (GetAsyncKeyState(VK_RETURN) or GetAsyncKeyState(VK_SPACE)) {
            return (enum menu_options_t) choice;
        }
        if ((blink_tick % 4 == 0 and !eyes_closed) or (blink_tick % 18 == 0 and eyes_closed)) {
            if (eyes_closed) {
                WHITE_TEXT_BLACK_BACKGROUND
                eyes_closed = false;
            } else {
                WHITE_BACKGROUND
                eyes_closed = true;
            }
            go_to_x_y(58, 15);
            cout << ' ';
            go_to_x_y(63, 15);
            cout << ' ';
        }
        ++blink_tick;
        Sleep(100);
    }
}

enum difficulties_t Board::display_choose_difficulty_screen() {
    this->load(FILE_CHOOSE_DIFFICULTY_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '/':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '@':
                    PURPLE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '^':
                    RED_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '%':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '$':
                    GREEN_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case ' ':
                    INTENSITY_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                default:
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    YELLOW_TEXT
    go_to_x_y(36, 11);
    cout << "> ";
    GREEN_TEXT
    cout << "LATWY  \t    3 ZDROWIA";
    WHITE_TEXT_BLACK_BACKGROUND
    go_to_x_y(38, 12);
    cout << "SREDNI";
    go_to_x_y(38, 13);
    cout << "TRUDNY";
    go_to_x_y(38, 14);
    cout << "HARDKOR";
    WHITE_TEXT_BLACK_BACKGROUND
    int choice = DIFFICULTIES_EASY;
    bool eyes_closed = false;
    int blink_tick = 0;
    GetAsyncKeyState(VK_ESCAPE);
    GetAsyncKeyState(VK_RETURN);
    GetAsyncKeyState(VK_SPACE);
    GetAsyncKeyState(VK_UP);
    GetAsyncKeyState(VK_DOWN);
    GetAsyncKeyState('W');
    GetAsyncKeyState('S');
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return DIFFICULTIES_RETURN;
        }
        if (GetAsyncKeyState(VK_DOWN) or GetAsyncKeyState('S')) {
            GetAsyncKeyState(VK_DOWN);
            GetAsyncKeyState('S');
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(36, int16_t(11 + choice));
            cout << "  ";
            switch (choice) {
                case DIFFICULTIES_EASY:
                    cout << "LATWY" << string(19, ' ');
                    break;
                case DIFFICULTIES_MEDIUM:
                    cout << "SREDNI" << string(18, ' ');
                    break;
                case DIFFICULTIES_HARD:
                    cout << "TRUDNY" << string(18, ' ');
                    break;
                case DIFFICULTIES_HARDCORE:
                    cout << "HARDKOR" << string(17, ' ');
                    break;
                default:
                    break;
            }
            if (choice == DIFFICULTIES_HARDCORE) {
                choice = DIFFICULTIES_EASY;
            } else {
                ++choice;
            }
            YELLOW_TEXT
            go_to_x_y(36, int16_t(11 + choice));
            cout << "> ";
            switch (choice) {
                case DIFFICULTIES_EASY:
                    GREEN_TEXT
                    cout << "LATWY  \t    3 ZDROWIA";
                    break;
                case DIFFICULTIES_MEDIUM:
                    cout << "SREDNI \t    3 ZDROWIA";
                    break;
                case DIFFICULTIES_HARD:
                    RED_TEXT
                    cout << "TRUDNY \t    3 ZDROWIA";
                    break;
                case DIFFICULTIES_HARDCORE:
                    PURPLE_TEXT
                    cout << "HARDKOR\t    1 ZDROWIE";
                    break;
                default:
                    break;
            }
        }
        if (GetAsyncKeyState(VK_UP) or GetAsyncKeyState('W')) {
            GetAsyncKeyState(VK_UP);
            GetAsyncKeyState('W');
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(36, int16_t(11 + choice));
            cout << "  ";
            switch (choice) {
                case DIFFICULTIES_EASY:
                    cout << "LATWY" << string(19, ' ');
                    break;
                case DIFFICULTIES_MEDIUM:
                    cout << "SREDNI" << string(18, ' ');
                    break;
                case DIFFICULTIES_HARD:
                    cout << "TRUDNY" << string(18, ' ');
                    break;
                case DIFFICULTIES_HARDCORE:
                    cout << "HARDKOR" << string(17, ' ');
                    break;
                default:
                    break;
            }
            if (choice == DIFFICULTIES_EASY) {
                choice = DIFFICULTIES_HARDCORE;
            } else {
                --choice;
            }
            YELLOW_TEXT
            go_to_x_y(36, int16_t(11 + choice));
            cout << "> ";
            switch (choice) {
                case DIFFICULTIES_EASY:
                    GREEN_TEXT
                    cout << "LATWY  \t    3 ZDROWIA";
                    break;
                case DIFFICULTIES_MEDIUM:
                    cout << "SREDNI \t    3 ZDROWIA";
                    break;
                case DIFFICULTIES_HARD:
                    RED_TEXT
                    cout << "TRUDNY \t    3 ZDROWIA";
                    break;
                case DIFFICULTIES_HARDCORE:
                    PURPLE_TEXT
                    cout << "HARDKOR\t    1 ZDROWIE";
                    break;
                default:
                    break;
            }
        }
        if (GetAsyncKeyState(VK_RETURN) or GetAsyncKeyState(VK_SPACE)) {
            return (enum difficulties_t) choice;
        }
        if ((blink_tick % 4 == 0 and !eyes_closed) or (blink_tick % 18 == 0 and eyes_closed)) {
            if (eyes_closed) {
                WHITE_TEXT_BLACK_BACKGROUND
                eyes_closed = false;
            } else {
                WHITE_BACKGROUND
                eyes_closed = true;
            }
            go_to_x_y(14, 6);
            cout << ' ';
            go_to_x_y(19, 6);
            cout << ' ';
            go_to_x_y(77, 6);
            cout << ' ';
            go_to_x_y(82, 6);
            cout << ' ';
            go_to_x_y(19, 16);
            cout << ' ';
            go_to_x_y(24, 16);
            cout << ' ';
            go_to_x_y(72, 16);
            cout << ' ';
            go_to_x_y(77, 16);
            cout << ' ';
        }
        --blink_tick;
        Sleep(100);
    }
}

void Board::display_help_screen() {
    this->load(FILE_HELP_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '/':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case ' ':
                    INTENSITY_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case '&':
                    LIGHT_BLUE_TEXT
                    cout << '*';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case '%':
                    RED_TEXT
                    cout << '*';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case '$':
                    GREEN_TEXT
                    cout << '$';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case '+':
                    PURPLE_TEXT
                    cout << '+';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                default:
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    GetAsyncKeyState(VK_ESCAPE);
    bool eyes_closed = false;
    int blink_tick = 0;
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return;
        }
        if ((blink_tick % 2 == 0 and !eyes_closed) or (blink_tick % 9 == 0 and eyes_closed)) {
            if (eyes_closed) {
                WHITE_TEXT_BLACK_BACKGROUND
                eyes_closed = false;
            } else {
                WHITE_BACKGROUND
                eyes_closed = true;
            }
            go_to_x_y(17, 15);
            cout << ' ';
            go_to_x_y(20, 15);
            cout << ' ';
        }
        ++blink_tick;
        Sleep(200);
    }
}

enum scoreboard_menu_options_t Board::display_scoreboard_menu_screen() {
    this->load(FILE_SCOREBOARD_MENU_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case ' ':
                    INTENSITY_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case '/':
                    BLUE_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case '^':
                    WHITE_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case '$':
                    RED_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                default:
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    static int choice = SCOREBOARD_MENU_EASY;
    WHITE_TEXT_BLACK_BACKGROUND
    go_to_x_y(42, 11);
    cout << "LATWY";
    go_to_x_y(42, 12);
    cout << "SREDNI";
    go_to_x_y(42, 13);
    cout << "TRUDNY";
    go_to_x_y(42, 14);
    cout << "HARDKOR";
    go_to_x_y(42, 15);
    cout << "REKORDY";
    YELLOW_TEXT
    go_to_x_y(40, int16_t(11 + choice));
    cout << "> ";
    switch (choice) {
        case SCOREBOARD_MENU_EASY:
            GREEN_TEXT
            cout << "LATWY";
            break;
        case SCOREBOARD_MENU_MEDIUM:
            YELLOW_TEXT
            cout << "SREDNI";
            break;
        case SCOREBOARD_MENU_HARD:
            RED_TEXT
            cout << "TRUDNY";
            break;
        case SCOREBOARD_MENU_HARDCORE:
            PURPLE_TEXT
            cout << "HARDKOR";
            break;
        case SCOREBOARD_MENU_HIGH_SCORES:
            LIGHT_BLUE_TEXT
            cout << "REKORDY";
            break;
        default:
            break;
    }
    GetAsyncKeyState(VK_ESCAPE);
    GetAsyncKeyState(VK_SPACE);
    GetAsyncKeyState(VK_RETURN);
    GetAsyncKeyState(VK_UP);
    GetAsyncKeyState(VK_DOWN);
    GetAsyncKeyState('S');
    GetAsyncKeyState('W');
    bool eyes_closed = false;
    int blink_tick = 0;
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            choice = SCOREBOARD_MENU_EASY;
            return SCOREBOARD_MENU_RETURN;
        }
        if (GetAsyncKeyState(VK_DOWN) or GetAsyncKeyState('S')) {
            GetAsyncKeyState(VK_DOWN);
            GetAsyncKeyState('S');
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(40, int16_t(11 + choice));
            cout << "  ";
            switch (choice) {
                case SCOREBOARD_MENU_EASY:
                    cout << "LATWY";
                    break;
                case SCOREBOARD_MENU_MEDIUM:
                    cout << "SREDNI";
                    break;
                case SCOREBOARD_MENU_HARD:
                    cout << "TRUDNY";
                    break;
                case SCOREBOARD_MENU_HARDCORE:
                    cout << "HARDKOR";
                    break;
                case SCOREBOARD_MENU_HIGH_SCORES:
                    cout << "REKORDY";
                    break;
                default:
                    break;
            }
            if (choice == SCOREBOARD_MENU_HIGH_SCORES) {
                choice = SCOREBOARD_MENU_EASY;
            } else {
                ++choice;
            }
            YELLOW_TEXT
            go_to_x_y(40, int16_t(11 + choice));
            cout << "> ";
            switch (choice) {
                case SCOREBOARD_MENU_EASY:
                    GREEN_TEXT
                    cout << "LATWY";
                    break;
                case SCOREBOARD_MENU_MEDIUM:
                    YELLOW_TEXT
                    cout << "SREDNI";
                    break;
                case SCOREBOARD_MENU_HARD:
                    RED_TEXT
                    cout << "TRUDNY";
                    break;
                case SCOREBOARD_MENU_HARDCORE:
                    PURPLE_TEXT
                    cout << "HARDKOR";
                    break;
                case SCOREBOARD_MENU_HIGH_SCORES:
                    LIGHT_BLUE_TEXT
                    cout << "REKORDY";
                    break;
                default:
                    break;
            }
        }
        if (GetAsyncKeyState(VK_UP) or GetAsyncKeyState('W')) {
            GetAsyncKeyState(VK_UP);
            GetAsyncKeyState('W');
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(40, int16_t(11 + choice));
            cout << "  ";
            switch (choice) {
                case SCOREBOARD_MENU_EASY:
                    cout << "LATWY";
                    break;
                case SCOREBOARD_MENU_MEDIUM:
                    cout << "SREDNI";
                    break;
                case SCOREBOARD_MENU_HARD:
                    cout << "TRUDNY";
                    break;
                case SCOREBOARD_MENU_HARDCORE:
                    cout << "HARDKOR";
                    break;
                case SCOREBOARD_MENU_HIGH_SCORES:
                    cout << "REKORDY";
                    break;
                default:
                    break;
            }
            if (choice == SCOREBOARD_MENU_EASY) {
                choice = SCOREBOARD_MENU_HIGH_SCORES;
            } else {
                --choice;
            }
            YELLOW_TEXT
            go_to_x_y(40, int16_t(11 + choice));
            cout << "> ";
            switch (choice) {
                case SCOREBOARD_MENU_EASY:
                    GREEN_TEXT
                    cout << "LATWY";
                    break;
                case SCOREBOARD_MENU_MEDIUM:
                    YELLOW_TEXT
                    cout << "SREDNI";
                    break;
                case SCOREBOARD_MENU_HARD:
                    RED_TEXT
                    cout << "TRUDNY";
                    break;
                case SCOREBOARD_MENU_HARDCORE:
                    PURPLE_TEXT
                    cout << "HARDKOR";
                    break;
                case SCOREBOARD_MENU_HIGH_SCORES:
                    LIGHT_BLUE_TEXT
                    cout << "REKORDY";
                    break;
                default:
                    break;
            }
        }
        if (GetAsyncKeyState(VK_RETURN) or GetAsyncKeyState(VK_SPACE)) {
            return (enum scoreboard_menu_options_t) choice;
        }
        if ((blink_tick % 4 == 0 and !eyes_closed) or (blink_tick % 18 == 0 and eyes_closed)) {
            if (eyes_closed) {
                WHITE_TEXT_BLACK_BACKGROUND
                eyes_closed = false;
            } else {
                WHITE_BACKGROUND
                eyes_closed = true;
            }
            go_to_x_y(19, 11);
            cout << ' ';
            go_to_x_y(24, 11);
            cout << ' ';
            go_to_x_y(72, 11);
            cout << ' ';
            go_to_x_y(77, 11);
            cout << ' ';
        }
        ++blink_tick;
        Sleep(100);
    }
}

void Board::display_scoreboard(const char *filename, enum difficulties_t difficulty) {
    this->load(FILE_SCOREBOARD_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("CLS");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '/':
                    switch (difficulty) {
                        case DIFFICULTIES_EASY:
                            GREEN_BACKGROUND
                            break;
                        case DIFFICULTIES_MEDIUM:
                            YELLOW_BACKGROUND
                            break;
                        case DIFFICULTIES_HARD:
                            RED_BACKGROUND
                            break;
                        case DIFFICULTIES_HARDCORE:
                            PURPLE_BACKGROUND
                            break;
                        default:
                            break;
                    }
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '^':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case ' ':
                    INTENSITY_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                default:
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    go_to_x_y(42, 5);
    switch (difficulty) {
        case DIFFICULTIES_EASY:
            GREEN_TEXT
            cout << "LATWY";
            break;
        case DIFFICULTIES_MEDIUM:
            YELLOW_TEXT
            cout << "SREDNI";
            break;
        case DIFFICULTIES_HARD:
            RED_TEXT
            cout << "TRUDNY";
            break;
        case DIFFICULTIES_HARDCORE:
            PURPLE_TEXT
            cout << "HARDKOR";
            break;
        default:
            break;
    }
    WHITE_TEXT_BLACK_BACKGROUND
    fstream scoreboard(filename, ios::in);
    string scoreboard_array[1000];
    int lines = 0;
    while (true) {
        string line;
        getline(scoreboard, line);
        scoreboard_array[lines] = line;
        if (line.length() == 0) {
            break;
        }
        ++lines;
    }
    for (int i = 0; i < lines / 2; ++i) {
        string temp = scoreboard_array[i];
        scoreboard_array[i] = scoreboard_array[lines - 1 - i];
        scoreboard_array[lines - 1 - i] = temp;
    }
    int max_lines = 10;
    for (int i = 0; i < max_lines; ++i) {
        go_to_x_y(24, int16_t(9 + i));
        if (scoreboard_array[i].contains("NOWY REKORD")) {
            cout << scoreboard_array[i].substr(0, scoreboard_array[i].length() - 11);
            go_to_x_y(61, int16_t(9 + i));
            GREEN_TEXT
            cout << "NOWY REKORD!";
            WHITE_TEXT_BLACK_BACKGROUND
        } else {
            cout << scoreboard_array[i] << endl;
        }
    }
    int max_page_nr = lines % max_lines ? lines / max_lines + 1 : lines / max_lines;
    int page_nr = 0;
    if (max_page_nr > 1) {
        YELLOW_TEXT
        go_to_x_y(57, 20);
        cout << "STARSZE ZAPISY >";
        WHITE_TEXT_BLACK_BACKGROUND
        go_to_x_y(48, 20);
        cout << page_nr + 1 << '/' << max_page_nr << ' ';
    }
    if (lines) {
        go_to_x_y(57, 5);
        cout << "LICZBA GIER: " << lines;
        go_to_x_y(24, 7);
        cout << "DATA:        GODZINA:    PUNKTY:";
    } else {
        go_to_x_y(32, 13);
        cout << "NIE ROZEGRANO JESZCZE ZADNYCH GIER";
        go_to_x_y(36, 14);
        cout << "NA TYM POZIOMIE TRUDNOSCI";
    }
    GetAsyncKeyState(VK_RIGHT);
    GetAsyncKeyState('D');
    GetAsyncKeyState(VK_LEFT);
    GetAsyncKeyState('A');
    GetAsyncKeyState(VK_ESCAPE);
    while (true) {
        if (GetAsyncKeyState(VK_ESCAPE)) {
            break;
        }
        bool page_changed = false;
        if (GetAsyncKeyState(VK_RIGHT) or GetAsyncKeyState('D')) {
            if (page_nr < max_page_nr - 1) {
                ++page_nr;
                page_changed = true;
            }
        } else if (GetAsyncKeyState(VK_LEFT) or GetAsyncKeyState('A')) {
            if (page_nr > 0) {
                --page_nr;
                page_changed = true;
            }
        }
        Sleep(100);
        if (page_changed) {
            for (int i = 0; i < max_lines; i++) {
                go_to_x_y(24, int16_t(9 + i));
                cout << string(49, ' ');
            }
            go_to_x_y(47, 20);
            if (page_nr > 8) {
                cout << page_nr + 1;
            } else {
                cout << ' ' << page_nr + 1;
            }
            go_to_x_y(49, 20);
            cout << "/" << max_page_nr;
            if (page_nr > 0) {
                YELLOW_TEXT
                go_to_x_y(24, 20);
                cout << "< NOWSZE ZAPISY";
                WHITE_TEXT_BLACK_BACKGROUND
            } else {
                go_to_x_y(24, 20);
                cout << string(15, ' ');
            }
            if (page_nr < max_page_nr - 1) {
                YELLOW_TEXT
                go_to_x_y(57, 20);
                cout << "STARSZE ZAPISY >";
                WHITE_TEXT_BLACK_BACKGROUND
            } else {
                go_to_x_y(57, 20);
                cout << string(16, ' ');
            }
            for (int i = page_nr * max_lines; i < (page_nr + 1) * max_lines; ++i) {
                go_to_x_y(24, int16_t(9 + i - page_nr * max_lines));
                if (scoreboard_array[i].contains("NOWY REKORD")) {
                    cout << scoreboard_array[i].substr(0, scoreboard_array[i].length() - 11);
                    go_to_x_y(61, int16_t(9 + i - page_nr * max_lines));
                    GREEN_TEXT
                    cout << "NOWY REKORD!";
                    WHITE_TEXT_BLACK_BACKGROUND
                } else {
                    cout << scoreboard_array[i] << endl;
                }
            }
        }
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void Board::display_high_scores() {
    this->load(FILE_HIGH_SCORES_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '^':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '/':
                    LIGHT_BLUE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case ' ':
                    INTENSITY_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                default:
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    GREEN_TEXT
    go_to_x_y(45, 5);
    cout << "LATWY";
    WHITE_TEXT_BLACK_BACKGROUND
    string points;
    string date;
    fstream file(FILE_HIGH_SCORE_EASY, ios::in);
    getline(file, points);
    getline(file, date);
    file.close();
    go_to_x_y(30, 7);
    if (points[0] == '0') {
        cout << '0';
    } else {
        cout << date << "   " << " * " << points << " * ";
    }
    YELLOW_TEXT
    go_to_x_y(45, 9);
    cout << "SREDNI";
    WHITE_TEXT_BLACK_BACKGROUND
    file.open(FILE_HIGH_SCORE_MEDIUM, ios::in);
    getline(file, points);
    getline(file, date);
    file.close();
    go_to_x_y(30, 11);
    if (points[0] == '0') {
        cout << '0';
    } else {
        cout << date << "   " << " * " << points << " * ";
    }
    RED_TEXT
    go_to_x_y(45, 13);
    cout << "TRUDNY";
    WHITE_TEXT_BLACK_BACKGROUND
    file.open(FILE_HIGH_SCORE_HARD, ios::in);
    getline(file, points);
    getline(file, date);
    file.close();
    go_to_x_y(30, 15);
    if (points[0] == '0') {
        cout << '0';
    } else {
        cout << date << "   " << " * " << points << " * ";
    }
    PURPLE_TEXT
    go_to_x_y(45, 17);
    cout << "HARDKOR";
    WHITE_TEXT_BLACK_BACKGROUND
    file.open(FILE_HIGH_SCORE_HARDCORE, ios::in);
    getline(file, points);
    getline(file, date);
    file.close();
    go_to_x_y(30, 19);
    if (points[0] == '0') {
        cout << '0';
    } else {
        cout << date << "   " << " * " << points << " * ";
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    while (getch() != VK_ESCAPE);
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

void Board::display_credits_screen() {
    this->load(FILE_CREDITS_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '^':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case ' ':
                    INTENSITY_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case '.':
                    INTENSITY_BACKGROUND
                    cout << '.';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                default:
                    YELLOW_TEXT
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    YELLOW_TEXT
    go_to_x_y(40, 15);
    cout << "JAKUB JAGODZINSKI";
    go_to_x_y(46, 17);
    cout << "2023";
    go_to_x_y(43, 19);
    cout << "[ESC] WROC";
    int16_t player_x = 60;
    int16_t player_y = 13;
    int16_t monster_x = 35;
    int16_t monster_y = 13;
    BLUE_TEXT
    go_to_x_y(player_x, player_y);
    cout << '0';
    RED_TEXT
    go_to_x_y(monster_x, monster_y);
    cout << 'X';
    GetAsyncKeyState(VK_ESCAPE);
    while (!GetAsyncKeyState(VK_ESCAPE)) {
        if (this->get_field(int16_t(player_x + 1), player_y) == '.') {
            go_to_x_y(player_x++, player_y);
        } else if (this->get_field(player_x, int16_t(player_y + 1)) == '.') {
            go_to_x_y(player_x, player_y++);
        } else if (this->get_field(int16_t(player_x - 1), player_y) == '.') {
            go_to_x_y(player_x--, player_y);
        } else if (this->get_field(player_x, int16_t(player_y - 1)) == '.') {
            go_to_x_y(player_x, player_y--);
        }
        INTENSITY_BACKGROUND
        cout << ' ';
        this->set_field(player_x, player_y, ' ');
        BLUE_TEXT_INTENSITY_BACKGROUND
        go_to_x_y(player_x, player_y);
        cout << '0';
        if (this->get_field(int16_t(monster_x + 1), monster_y) == ' ') {
            go_to_x_y(monster_x++, monster_y);
        } else if (this->get_field(monster_x, int16_t(monster_y + 1)) == ' ') {
            go_to_x_y(monster_x, monster_y++);
        } else if (this->get_field(int16_t(monster_x - 1), monster_y) == ' ') {
            go_to_x_y(monster_x--, monster_y);
        } else if (this->get_field(monster_x, int16_t(monster_y - 1)) == ' ') {
            go_to_x_y(monster_x, monster_y--);
        }
        INTENSITY_BACKGROUND
        cout << '.';
        this->set_field(monster_x, monster_y, '.');
        RED_TEXT_INTENSITY_BACKGROUND
        go_to_x_y(monster_x, monster_y);
        cout << 'X';
        Sleep(100);
    }
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
}

bool Board::display_confirmation_screen() {
    this->load(FILE_CONFIRMATION_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '/':
                    GREEN_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '^':
                    RED_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '@':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case ' ':
                    INTENSITY_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                default:
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    GetAsyncKeyState(VK_RETURN);
    GetAsyncKeyState(VK_ESCAPE);
    bool eyes_closed = false;
    int blink_tick = 0;
    while (true) {
        if (GetAsyncKeyState(VK_RETURN)) {
            return true;
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            return false;
        }
        if ((blink_tick % 2 == 0 and !eyes_closed) or (blink_tick % 9 == 0 and eyes_closed)) {
            if (eyes_closed) {
                WHITE_TEXT_BLACK_BACKGROUND
                eyes_closed = false;
            } else {
                WHITE_BACKGROUND
                eyes_closed = true;
            }
            go_to_x_y(27, 16);
            cout << ' ';
            go_to_x_y(32, 16);
            cout << ' ';
            go_to_x_y(64, 16);
            cout << ' ';
            go_to_x_y(69, 16);
            cout << ' ';
        }
        ++blink_tick;
        Sleep(200);
    }
}

void Board::display_goodbye_screen() {
    this->load(FILE_GOODBYE_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '/':
                    BLUE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '^':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                default:
                    INTENSITY_BACKGROUND
                    cout << c;
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
            }
        }
        cout << endl;
    }
    Sleep(1250);
}

enum settings_options_t Board::display_settings_screen() {
    this->load(FILE_SETTINGS_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    YELLOW_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case ' ':
                    INTENSITY_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                case '^':
                    WHITE_BACKGROUND
                    cout << ' ';
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
                default:
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    static int choice = 0;
    WHITE_TEXT_BLACK_BACKGROUND
    go_to_x_y(42, 10);
    cout << "WYCZYSC RANKING";
    go_to_x_y(42, 11);
    cout << "WYCZYSC REKORDY";
    YELLOW_TEXT
    go_to_x_y(40, int16_t(10 + choice));
    switch (choice) {
        case SETTINGS_CLEAR_SCOREBOARD:
            cout << "> WYCZYSC RANKING";
            break;
        case SETTINGS_CLEAR_HIGH_SCORES:
            cout << "> WYCZYSC REKORDY";
            break;
        default:
            break;
    }
    GetAsyncKeyState(SETTINGS_CLEAR_SCOREBOARD);
    GetAsyncKeyState(SETTINGS_CLEAR_HIGH_SCORES);
    GetAsyncKeyState(SETTINGS_RETURN);
    GetAsyncKeyState(VK_RETURN);
    GetAsyncKeyState(VK_SPACE);
    GetAsyncKeyState(VK_UP);
    GetAsyncKeyState(VK_DOWN);
    GetAsyncKeyState('W');
    GetAsyncKeyState('S');
    bool eyes_closed = false;
    int blink_tick = 0;
    while (true) {
        if (GetAsyncKeyState(VK_DOWN) or GetAsyncKeyState('S')) {
            GetAsyncKeyState(VK_UP);
            GetAsyncKeyState('W');
            go_to_x_y(40, int16_t(10 + choice));
            WHITE_TEXT_BLACK_BACKGROUND
            switch (choice) {
                case SETTINGS_CLEAR_SCOREBOARD:
                    cout << "  WYCZYSC RANKING";
                    break;
                case SETTINGS_CLEAR_HIGH_SCORES:
                    cout << "  WYCZYSC REKORDY";
                    break;
                default:
                    break;
            }
            if (choice == SETTINGS_CLEAR_HIGH_SCORES) {
                choice = SETTINGS_CLEAR_SCOREBOARD;
            } else {
                ++choice;
            }
            go_to_x_y(40, int16_t(10 + choice));
            YELLOW_TEXT
            switch (choice) {
                case SETTINGS_CLEAR_SCOREBOARD:
                    cout << "> WYCZYSC RANKING";
                    break;
                case SETTINGS_CLEAR_HIGH_SCORES:
                    cout << "> WYCZYSC REKORDY";
                    break;
                default:
                    break;
            }
        }
        if (GetAsyncKeyState(VK_UP) or GetAsyncKeyState('W')) {
            GetAsyncKeyState(VK_DOWN);
            GetAsyncKeyState('S');
            go_to_x_y(40, int16_t(10 + choice));
            WHITE_TEXT_BLACK_BACKGROUND
            switch (choice) {
                case SETTINGS_CLEAR_SCOREBOARD:
                    cout << "  WYCZYSC RANKING";
                    break;
                case SETTINGS_CLEAR_HIGH_SCORES:
                    cout << "  WYCZYSC REKORDY";
                    break;
                default:
                    break;
            }
            if (choice == SETTINGS_CLEAR_SCOREBOARD) {
                choice = SETTINGS_CLEAR_HIGH_SCORES;
            } else {
                --choice;
            }
            go_to_x_y(40, int16_t(10 + choice));
            YELLOW_TEXT
            switch (choice) {
                case SETTINGS_CLEAR_SCOREBOARD:
                    cout << "> WYCZYSC RANKING";
                    break;
                case SETTINGS_CLEAR_HIGH_SCORES:
                    cout << "> WYCZYSC REKORDY";
                    break;
                default:
                    break;
            }
        }
        if (GetAsyncKeyState(SETTINGS_RETURN)) {
            choice = SETTINGS_CLEAR_SCOREBOARD;
            return SETTINGS_RETURN;
        }
        if (GetAsyncKeyState(VK_RETURN) or GetAsyncKeyState(VK_SPACE)) {
            bool clear = this->display_confirmation_screen();
            if (clear) {
                fstream file;
                switch (choice) {
                    case SETTINGS_CLEAR_HIGH_SCORES:
                        file.open(FILE_HIGH_SCORE_EASY, ios::out);
                        file << "0\n--.--.---- --:--:--";
                        file.close();
                        file.open(FILE_HIGH_SCORE_MEDIUM, ios::out);
                        file << "0\n--.--.---- --:--:--";
                        file.close();
                        file.open(FILE_HIGH_SCORE_HARD, ios::out);
                        file << "0\n--.--.---- --:--:--";
                        file.close();
                        file.open(FILE_HIGH_SCORE_HARDCORE, ios::out);
                        file << "0\n--.--.---- --:--:--";
                        file.close();
                        break;
                    case SETTINGS_CLEAR_SCOREBOARD:
                        file.open(FILE_SCOREBOARD_EASY, ios::out);
                        file.close();
                        file.open(FILE_SCOREBOARD_MEDIUM, ios::out);
                        file.close();
                        file.open(FILE_SCOREBOARD_HARD, ios::out);
                        file.close();
                        file.open(FILE_SCOREBOARD_HARDCORE, ios::out);
                        file.close();
                        break;
                    default:
                        break;
                }
            }
            return (enum settings_options_t) choice;
        }
        if ((blink_tick % 2 == 0 and !eyes_closed) or (blink_tick % 9 == 0 and eyes_closed)) {
            if (eyes_closed) {
                WHITE_TEXT_BLACK_BACKGROUND
                eyes_closed = false;
            } else {
                WHITE_BACKGROUND
                eyes_closed = true;
            }
            go_to_x_y(17, 11);
            cout << ' ';
            go_to_x_y(79, 11);
            cout << ' ';
        }
        ++blink_tick;
        Sleep(200);
    }
}

void Board::display_next_map(const Player &player, const Monster (&monsters)[], int monsters_in_game) {
    switch (this->map_nr) {
        case 0:
        case 4:
            this->load(MAP1);
            this->map_nr = 0;
            break;
        case 1:
            this->load(MAP2);
            break;
        case 2:
            this->load(MAP3);
            break;
        case 3:
            this->load(MAP4);
            break;
        default:
            break;
    }
    ++this->map_nr;
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '.':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << '.';
                    INTENSITY_BACKGROUND
                    break;
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                case '$':
                    GREEN_TEXT_INTENSITY_BACKGROUND
                    cout << '$';
                    INTENSITY_BACKGROUND
                    break;
                case '+':
                    PURPLE_TEXT_INTENSITY_BACKGROUND
                    cout << '+';
                    INTENSITY_BACKGROUND
                    break;
                case '*':
                    LIGHT_BLUE_TEXT_INTENSITY_BACKGROUND
                    cout << '*';
                    INTENSITY_BACKGROUND
                    break;
                case '&':
                    RED_TEXT_INTENSITY_BACKGROUND
                    cout << '*';
                    INTENSITY_BACKGROUND
                    break;
                default:
                    INTENSITY_BACKGROUND
                    cout << c;
                    WHITE_TEXT_BLACK_BACKGROUND
                    break;
            }
        }
        cout << endl;
    }
    BLACK_TEXT_YELLOW_BACKGROUND
    go_to_x_y(FIRST_UPPER_X, FIRST_UPPER_Y - 1);
    cout << '^';
    go_to_x_y(SECOND_UPPER_X, SECOND_UPPER_Y - 1);
    cout << '^';
    go_to_x_y(MIDDLE_UPPER_LEFT_X - 1, MIDDLE_UPPER_LEFT_Y);
    cout << '<';
    go_to_x_y(MIDDLE_UPPER_RIGHT_X + 1, MIDDLE_UPPER_RIGHT_Y);
    cout << '>';
    go_to_x_y(MIDDLE_LOWER_LEFT_X - 1, MIDDLE_LOWER_LEFT_Y);
    cout << '<';
    go_to_x_y(MIDDLE_LOWER_RIGHT_X + 1, MIDDLE_LOWER_RIGHT_Y);
    cout << '>';
    go_to_x_y(FIRST_LOWER_X, FIRST_LOWER_Y + 1);
    cout << 'v';
    go_to_x_y(SECOND_LOWER_X, SECOND_LOWER_Y + 1);
    cout << 'v';
    WHITE_TEXT_BLACK_BACKGROUND
    go_to_x_y(5, 1);
    cout << "POZIOM";
    YELLOW_TEXT
    go_to_x_y(45, 1);
    cout << "PAC-MAN";
    switch (player.get_difficulty()) {
        case DIFFICULTIES_EASY:
            GREEN_TEXT
            go_to_x_y(87, 1);
            cout << "LATWY";
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(89, 26);
            cout << player.get_lives() << '/' << EASY_LIVES;
            break;
        case DIFFICULTIES_MEDIUM:
            YELLOW_TEXT
            go_to_x_y(86, 1);
            cout << "SREDNI";
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(89, 26);
            cout << player.get_lives() << '/' << MEDIUM_LIVES;
            break;
        case DIFFICULTIES_HARD:
            RED_TEXT
            go_to_x_y(86, 1);
            cout << "TRUDNY";
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(89, 26);
            cout << player.get_lives() << '/' << HARD_LIVES;
            break;
        case DIFFICULTIES_HARDCORE:
            PURPLE_TEXT
            go_to_x_y(85, 1);
            cout << "HARDKOR";
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(89, 26);
            cout << player.get_lives() << '/' << HARDCORE_LIVES;
            break;
        default:
            break;
    }
    go_to_x_y(81, 26);
    cout << "ZDROWIE";
    go_to_x_y(5, 26);
    cout << "PUNKTY";
    for (int i = 0; i < monsters_in_game; ++i) {
        monsters[i].display(player.get_elixir());
    }
    player.display();
    player.display_statistics();
}

bool Board::display_game_over_screen(const Player &player, unsigned long long high_score, bool high_score_beaten) {
    this->load(FILE_GAME_OVER_SCREEN);
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        for (int16_t x = 0; x < SCREEN_WIDTH; ++x) {
            char c = this->get_field(x, y);
            switch (c) {
                case '#':
                    WHITE_TEXT_BLACK_BACKGROUND
                    cout << ' ';
                    break;
                case '*':
                    RED_BACKGROUND
                    cout << ' ';
                    break;
                case '^':
                    WHITE_BACKGROUND
                    cout << ' ';
                    INTENSITY_BACKGROUND
                    break;
                default:
                    INTENSITY_BACKGROUND
                    cout << c;
                    break;
            }
        }
        cout << endl;
    }
    WHITE_TEXT_BLACK_BACKGROUND
    go_to_x_y(51, 14);
    switch (player.get_difficulty()) {
        case DIFFICULTIES_EASY:
            GREEN_TEXT
            cout << "LATWY ";
            break;
        case DIFFICULTIES_MEDIUM:
            YELLOW_TEXT
            cout << "SREDNI ";
            break;
        case DIFFICULTIES_HARD:
            RED_TEXT
            cout << "TRUDNY ";
            break;
        case DIFFICULTIES_HARDCORE:
            PURPLE_TEXT
            cout << "HARDKOR ";
            break;
        default:
            break;
    }
    WHITE_TEXT_BLACK_BACKGROUND
    cout << "POZIOM " << player.get_level();
    go_to_x_y(51, 15);
    cout << "WYNIK: " << player.get_points();
    if (high_score_beaten) {
        GREEN_TEXT
        go_to_x_y(51, 16);
        cout << "NOWY REKORD!";
        WHITE_TEXT_BLACK_BACKGROUND
    }
    GAME_OVER_SOUND
    YELLOW_TEXT
    go_to_x_y(49, 18);
    cout << "> WROC DO MENU";
    WHITE_TEXT_BLACK_BACKGROUND
    go_to_x_y(49, 19);
    cout << "  ZAGRAJ PONOWNIE";
    GetAsyncKeyState(VK_RETURN);
    GetAsyncKeyState(VK_SPACE);
    GetAsyncKeyState(VK_UP);
    GetAsyncKeyState(VK_DOWN);
    GetAsyncKeyState('W');
    GetAsyncKeyState('S');
    bool start_again = false;
    while (true) {
        if (GetAsyncKeyState(VK_UP) or GetAsyncKeyState('W')) {
            GetAsyncKeyState(VK_DOWN);
            GetAsyncKeyState('S');
            if (start_again) {
                YELLOW_TEXT
                go_to_x_y(49, 18);
                cout << "> WROC DO MENU";
                WHITE_TEXT_BLACK_BACKGROUND
                go_to_x_y(49, 19);
                cout << "  ZAGRAJ PONOWNIE";
                start_again = false;
            } else {
                WHITE_TEXT_BLACK_BACKGROUND
                go_to_x_y(49, 18);
                cout << "  WROC DO MENU";
                YELLOW_TEXT
                go_to_x_y(49, 19);
                cout << "> ZAGRAJ PONOWNIE";
                start_again = true;
            }
        }
        if (GetAsyncKeyState(VK_DOWN) or GetAsyncKeyState('S')) {
            GetAsyncKeyState(VK_UP);
            GetAsyncKeyState('W');
            if (start_again) {
                YELLOW_TEXT
                go_to_x_y(49, 18);
                cout << "> WROC DO MENU";
                WHITE_TEXT_BLACK_BACKGROUND
                go_to_x_y(49, 19);
                cout << "  ZAGRAJ PONOWNIE";
                start_again = false;
            } else {
                WHITE_TEXT_BLACK_BACKGROUND
                go_to_x_y(49, 18);
                cout << "  WROC DO MENU";
                YELLOW_TEXT
                go_to_x_y(49, 19);
                cout << "> ZAGRAJ PONOWNIE";
                start_again = true;
            }
        }
        if (GetAsyncKeyState(VK_RETURN) or GetAsyncKeyState(VK_SPACE)) {
            return start_again;
        }
        Sleep(100);
    }
}
