#ifndef PAC_MAN_DEFS_H
#define PAC_MAN_DEFS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdint>
#include <ctime>
#include <conio.h>
#include <cwchar>
#include <windows.h>
#include <winuser.h>

#define SCREEN_WIDTH 98
#define SCREEN_HEIGHT 27
#define MAP_X_CENTER 48
#define MAP_Y_CENTER 13
#define SET_TIME 99

/// portals
#define FIRST_UPPER_X 31
#define FIRST_UPPER_Y 2
#define SECOND_UPPER_X 65
#define SECOND_UPPER_Y 2
#define MIDDLE_UPPER_LEFT_X 3
#define MIDDLE_UPPER_LEFT_Y 8
#define MIDDLE_UPPER_RIGHT_X 93
#define MIDDLE_UPPER_RIGHT_Y 8
#define MIDDLE_LOWER_LEFT_X 3
#define MIDDLE_LOWER_LEFT_Y 18
#define MIDDLE_LOWER_RIGHT_X 93
#define MIDDLE_LOWER_RIGHT_Y 18
#define FIRST_LOWER_X 31
#define FIRST_LOWER_Y 24
#define SECOND_LOWER_X 65
#define SECOND_LOWER_Y 24

/// difficulties properties
#define EASY_LIVES 3
#define MEDIUM_LIVES 3
#define HARD_LIVES 3
#define HARDCORE_LIVES 1
#define EASY_TICK_SPEED 60
#define MEDIUM_TICK_SPEED 55
#define HARD_TICK_SPEED 50
#define HARDCORE_TICK_SPEED 50
#define EASY_MONSTER_SPEED 4
#define MEDIUM_MONSTER_SPEED 3
#define HARD_MONSTER_SPEED 2
#define HARDCORE_MONSTER_SPEED 2
#define EASY_MONSTERS_IN_GAME 8
#define MEDIUM_MONSTERS_IN_GAME 8
#define HARD_MONSTERS_IN_GAME 8
#define HARDCORE_MONSTERS_IN_GAME 8
#define EASY_HUNGER_SPEED 4
#define MEDIUM_HUNGER_SPEED 3
#define HARD_HUNGER_SPEED 3
#define HARDCORE_HUNGER_SPEED 3
#define EASY_DOLLAR_SPEED 4
#define MEDIUM_DOLLAR_SPEED 3
#define HARD_DOLLAR_SPEED 3
#define HARDCORE_DOLLAR_SPEED 2
#define EASY_POINTS_GAP 500
#define MEDIUM_POINTS_GAP 750
#define HARD_POINTS_GAP 1000
#define HARDCORE_POINTS_GAP 1000
#define EASY_HUNGER_REDUCE 30
#define MEDIUM_HUNGER_REDUCE 25
#define HARD_HUNGER_REDUCE 20
#define HARDCORE_HUNGER_REDUCE 20
#define EASY_ADD_POINTS_FOR_MONSTER 25
#define MEDIUM_ADD_POINTS_FOR_MONSTER 20
#define HARD_ADD_POINTS_FOR_MONSTER 15
#define HARDCORE_ADD_POINTS_FOR_MONSTER 15
#define EASY_FREEZE_DELAY 2
#define MEDIUM_FREEZE_DELAY 3
#define HARD_FREEZE_DELAY 3
#define HARDCORE_FREEZE_DELAY 3
#define EASY_FREEZE_REDUCE_SPEED 2
#define MEDIUM_FREEZE_REDUCE_SPEED 3
#define HARD_FREEZE_REDUCE_SPEED 4
#define HARDCORE_FREEZE_REDUCE_SPEED 4

#define MAP1 "../maps/map1.txt"
#define MAP2 "../maps/map2.txt"
#define MAP3 "../maps/map3.txt"
#define MAP4 "../maps/map4.txt"

#define FILE_START_GAME_SCREEN "../screens/start_game_screen.txt"
#define FILE_MENU_SCREEN "../screens/menu_screen.txt"
#define FILE_CONFIRMATION_SCREEN "../screens/confirmation_screen.txt"
#define FILE_CHOOSE_DIFFICULTY_SCREEN "../screens/choose_difficulty_screen.txt"
#define FILE_HIGH_SCORES_SCREEN "../screens/high_scores_screen.txt"
#define FILE_SCOREBOARD_MENU_SCREEN "../screens/scoreboard_menu_screen.txt"
#define FILE_SCOREBOARD_SCREEN "../screens/scoreboard_screen.txt"
#define FILE_SETTINGS_SCREEN "../screens/settings_screen.txt"
#define FILE_CREDITS_SCREEN "../screens/credits_screen.txt"
#define FILE_GAME_OVER_SCREEN "../screens/game_over_screen.txt"
#define FILE_GOODBYE_SCREEN "../screens/goodbye_screen.txt"
#define FILE_HELP_SCREEN "../screens/help_screen.txt"

#define FILE_HIGH_SCORE_EASY "../scores/high_score_easy.txt"
#define FILE_HIGH_SCORE_MEDIUM "../scores/high_score_medium.txt"
#define FILE_HIGH_SCORE_HARD "../scores/high_score_hard.txt"
#define FILE_HIGH_SCORE_HARDCORE "../scores/high_score_hardcore.txt"
#define FILE_SCOREBOARD_EASY "../scores/scoreboard_easy.txt"
#define FILE_SCOREBOARD_MEDIUM "../scores/scoreboard_medium.txt"
#define FILE_SCOREBOARD_HARD "../scores/scoreboard_hard.txt"
#define FILE_SCOREBOARD_HARDCORE "../scores/scoreboard_hardcore.txt"

#define hOutput (GetStdHandle(STD_OUTPUT_HANDLE))

#define WHITE_TEXT_BLACK_BACKGROUND SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#define RED_TEXT_INTENSITY_BACKGROUND SetConsoleTextAttribute(hOutput, FOREGROUND_RED | BACKGROUND_INTENSITY);
#define GREEN_TEXT_INTENSITY_BACKGROUND SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | BACKGROUND_INTENSITY);
#define BLUE_TEXT_INTENSITY_BACKGROUND SetConsoleTextAttribute(hOutput, FOREGROUND_BLUE | BACKGROUND_INTENSITY);
#define LIGHT_BLUE_TEXT_INTENSITY_BACKGROUND SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_INTENSITY);
#define PURPLE_TEXT_INTENSITY_BACKGROUND SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_BLUE | BACKGROUND_INTENSITY);
#define BLACK_TEXT_YELLOW_BACKGROUND SetConsoleTextAttribute(hOutput, BACKGROUND_RED | BACKGROUND_GREEN);
#define RED_TEXT_LIGHT_BLUE_BACKGROUND SetConsoleTextAttribute(hOutput, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
#define BLUE_TEXT_LIGHT_BLUE_BACKGROUND SetConsoleTextAttribute(hOutput, FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_BLUE);

#define RED_TEXT SetConsoleTextAttribute(hOutput, FOREGROUND_RED);
#define GREEN_TEXT SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN);
#define BLUE_TEXT SetConsoleTextAttribute(hOutput, FOREGROUND_BLUE);
#define YELLOW_TEXT SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_GREEN);
#define PURPLE_TEXT SetConsoleTextAttribute(hOutput, FOREGROUND_RED | FOREGROUND_BLUE);
#define LIGHT_BLUE_TEXT SetConsoleTextAttribute(hOutput, FOREGROUND_GREEN | FOREGROUND_BLUE);

#define INTENSITY_BACKGROUND SetConsoleTextAttribute(hOutput, BACKGROUND_INTENSITY);
#define RED_BACKGROUND SetConsoleTextAttribute(hOutput, BACKGROUND_RED);
#define GREEN_BACKGROUND SetConsoleTextAttribute(hOutput, BACKGROUND_GREEN);
#define BLUE_BACKGROUND SetConsoleTextAttribute(hOutput, BACKGROUND_BLUE);
#define YELLOW_BACKGROUND SetConsoleTextAttribute(hOutput, BACKGROUND_RED | BACKGROUND_GREEN);
#define PURPLE_BACKGROUND SetConsoleTextAttribute(hOutput, BACKGROUND_RED | BACKGROUND_BLUE);
#define LIGHT_BLUE_BACKGROUND SetConsoleTextAttribute(hOutput, BACKGROUND_GREEN | BACKGROUND_BLUE);
#define WHITE_BACKGROUND SetConsoleTextAttribute(hOutput, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

#define HUNGER_DEATH_SOUND Beep(440, 300); Beep(370, 300); Beep(312, 300); Beep(262, 300);
#define GAME_OVER_SOUND Beep(880, 300); Beep(740, 300); Beep(624, 300); Beep(530, 500);
#define NEW_LEVEL_SOUND Beep(524, 200); Beep(660, 200); Beep(784, 200); Beep(1048, 200); Beep(524, 200);
#define PLAYER_EATEN_SOUND Beep(370, 300); Beep(312, 300); Beep(262, 300);
#define MONSTER_EATEN_SOUND Beep(262, 300); Beep(312, 300); Beep(370, 300);
#define DOLLAR_SOUND Beep(880, 200);
#define ELIXIR_SOUND Beep(550, 200);
#define FROZEN_SOUND Beep(1200, 300);
#define BOMB_SOUND Beep(300, 200);

using namespace std;

enum difficulties_t {
    DIFFICULTIES_EASY,
    DIFFICULTIES_MEDIUM,
    DIFFICULTIES_HARD,
    DIFFICULTIES_HARDCORE,
    DIFFICULTIES_RETURN = VK_ESCAPE,
};

enum menu_options_t {
    MENU_START_GAME,
    MENU_SHOW_SCOREBOARD,
    MENU_SETTINGS,
    MENU_HELP,
    MENU_CREDITS,
    MENU_QUIT_GAME,
};

enum scoreboard_menu_options_t {
    SCOREBOARD_MENU_EASY,
    SCOREBOARD_MENU_MEDIUM,
    SCOREBOARD_MENU_HARD,
    SCOREBOARD_MENU_HARDCORE,
    SCOREBOARD_MENU_HIGH_SCORES,
    SCOREBOARD_MENU_RETURN = VK_ESCAPE,
};

enum settings_options_t {
    SETTINGS_CLEAR_SCOREBOARD,
    SETTINGS_CLEAR_HIGH_SCORES,
    SETTINGS_RETURN = VK_ESCAPE,
};

void go_to_x_y(int16_t x, int16_t y);

void hide_cursor();

void set_fullscreen();

void display_dark_screen();

void create_high_score_files(const char *filename);

bool save_score(const char *filename_high_score, const char *filename_score, size_t *high_score, size_t points);

void check_pause(bool &pause);

#endif
