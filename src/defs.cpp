#include "defs.h"

void create_high_score_files(const char *filename) {
    FILE *fin = fopen(filename, "r");
    if (fin == nullptr) {
        fin = fopen(filename, "w");
        fprintf(fin, "0\n--.--.---- --:--:--");
    }
    fclose(fin);
}

bool save_score(const char *filename_high_score, const char *filename_score, size_t *high_score, size_t points) {
    fstream scoreboard_file(filename_score, ios::app);
    fstream high_score_file(filename_high_score, ios::in);
    time_t t = time(nullptr);
    tm *now = localtime(&t);
    bool high_score_beaten = false;
    scoreboard_file << setw(2) << setfill('0') << now->tm_mday << '.' << setfill('0') << setw(2) << (now->tm_mon + 1)
                    << '.' << setw(4) << setfill('0') << (now->tm_year + 1900) << "   " << setw(2) << setfill('0')
                    << now->tm_hour << ':' << setw(2) << setfill('0') << now->tm_min << ':'
                    << setw(2) << setfill('0') << now->tm_sec << string(4, ' ') << points;
    high_score_file >> *high_score;
    high_score_file.close();
    if (points > *high_score) {
        scoreboard_file << " NOWY REKORD";
        high_score_beaten = true;
        *high_score = points;
        high_score_file.open(filename_high_score, ios::out);
        high_score_file << *high_score << endl << setw(2) << setfill('0') << now->tm_mday << '.' << setfill('0')
                        << setw(2)
                        << (now->tm_mon + 1) << '.' << setw(4) << setfill('0') << (now->tm_year + 1900) << ' '
                        << setw(2) << setfill('0') << now->tm_hour << ':' << setw(2) << setfill('0') << now->tm_min
                        << ':' << setw(2) << setfill('0') << now->tm_sec;
        high_score_file.close();
    }
    scoreboard_file << endl;
    scoreboard_file.close();
    return high_score_beaten;
}

void go_to_x_y(int16_t x, int16_t y) {
    SetConsoleCursorPosition(hOutput, {x, y});
}

void set_fullscreen() {
    keybd_event(VK_MENU, 0x38, 0, 0);
    keybd_event(VK_RETURN, 0x1c, 0, 0);
    keybd_event(VK_RETURN, 0x1c, KEYEVENTF_KEYUP, 0);
    keybd_event(VK_MENU, 0x38, KEYEVENTF_KEYUP, 0);
}

void display_dark_screen() {
    WHITE_TEXT_BLACK_BACKGROUND
    system("cls");
    for (int16_t y = 0; y < SCREEN_HEIGHT; ++y) {
        cout << string(SCREEN_WIDTH, ' ') << endl;
    }
    Sleep(500);
}

void hide_cursor() {
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(hOutput, &info);
}

void check_pause(bool &pause) {
    if (pause or GetAsyncKeyState(VK_SPACE)) {
        pause = true;
        go_to_x_y(42, 25);
        WHITE_TEXT_BLACK_BACKGROUND
        cout << "    PAUZA    ";
        go_to_x_y(42, 27);
        cout << "[SPACJA] START";
        Sleep(500);
    }
    while (pause) {
        if (GetAsyncKeyState(VK_SPACE)) {
            pause = false;
            GetAsyncKeyState(VK_UP);
            GetAsyncKeyState(VK_DOWN);
            GetAsyncKeyState(VK_LEFT);
            GetAsyncKeyState(VK_RIGHT);
            GetAsyncKeyState('W');
            GetAsyncKeyState('S');
            GetAsyncKeyState('A');
            GetAsyncKeyState('D');
            WHITE_TEXT_BLACK_BACKGROUND
            go_to_x_y(40, 25);
            cout << string(18, ' ');
            go_to_x_y(42, 27);
            cout << string(16, ' ');
            Sleep(100);
        }
    }
}
