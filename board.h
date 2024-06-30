#ifndef PAC_MAN_BOARD_H
#define PAC_MAN_BOARD_H

#include "defs.h"
#include "player.h"
#include "monster.h"

class Board {
private:
    char map[SCREEN_HEIGHT][SCREEN_WIDTH];
    int16_t map_nr;

public:
    void set_field(int16_t x, int16_t y, char c);

    [[nodiscard]] char get_field(int16_t x, int16_t y) const;

    void load(const char *filename);

    void display_start_game_screen();

    void display_next_map(const class Player &player, const class Monster (&monsters)[], int monsters_in_game);

    bool display_confirmation_screen();

    enum menu_options_t display_menu_screen();

    enum difficulties_t display_choose_difficulty_screen();

    void display_help_screen();

    enum scoreboard_menu_options_t display_scoreboard_menu_screen();

    void display_scoreboard(const char *filename, enum difficulties_t difficulty);

    void display_high_scores();

    void display_credits_screen();

    enum settings_options_t display_settings_screen();

    bool display_game_over_screen(const class Player &player, unsigned long long high_score, bool high_score_beaten);

    void display_goodbye_screen();
};

#endif
