#ifndef PAC_MAN_PLAYER_H
#define PAC_MAN_PLAYER_H

#include "defs.h"
#include "board.h"

class Player {
private:
    enum difficulties_t difficulty;
    int16_t x_start;
    int16_t y_start;
    int16_t x;
    int16_t y;
    int16_t lives;
    int16_t level;
    bool is_frozen;
    int16_t frozen_time;
    bool freeze;
    int16_t freeze_time;
    int16_t freeze_reduce_speed;
    int16_t freeze_delay;
    int16_t points_multiplier;
    int16_t points_multiplier_speed;
    int16_t points_multiplier_time;
    int16_t elixir;
    int16_t hunger;
    int16_t hunger_speed;
    int16_t hunger_reduce;
    int16_t add_points_for_monster;
    size_t points;
    size_t floor_points;
    size_t ceil_points;
    size_t points_gap;
public:
    Player() {
        difficulty = DIFFICULTIES_EASY;
        x_start = MAP_X_CENTER;
        y_start = MAP_Y_CENTER;
        x = x_start;
        y = y_start;
        lives = EASY_LIVES;
        level = 1;
        is_frozen = false;
        frozen_time = 0;
        freeze = false;
        freeze_time = 0;
        freeze_reduce_speed = EASY_FREEZE_REDUCE_SPEED;
        freeze_delay = EASY_FREEZE_DELAY;
        points_multiplier = 1;
        points_multiplier_speed = EASY_DOLLAR_SPEED;
        points_multiplier_time = 0;
        elixir = 0;
        hunger = 0;
        hunger_speed = EASY_HUNGER_SPEED;
        hunger_reduce = EASY_HUNGER_REDUCE;
        add_points_for_monster = EASY_ADD_POINTS_FOR_MONSTER;
        points = 0;
        floor_points = EASY_POINTS_GAP;
        ceil_points = EASY_POINTS_GAP * 2;
        points_gap = EASY_POINTS_GAP;
    }

    [[nodiscard]] size_t get_points() const;

    [[nodiscard]] enum difficulties_t get_difficulty() const;

    [[nodiscard]] int16_t get_level() const;

    [[nodiscard]] int16_t get_lives() const;

    [[nodiscard]] int16_t get_elixir() const;

    [[nodiscard]] int16_t get_x() const;

    [[nodiscard]] int16_t get_y() const;

    void display() const;

    void display_statistics() const;

    void display_lives() const;

    void display_level() const;

    void display_points() const;

    void display_hunger() const;

    void display_elixir_time() const;

    void display_frozen_time() const;

    void make_move(class Board &board);

    void move_up(class Board &board);

    void move_down(class Board &board);

    void move_left(class Board &board);

    void move_right(class Board &board);

    void collect_effect_from_field(class Board &board);

    void reduce_frozen_time();

    void reduce_freeze_time(int16_t tick);

    void reduce_elixir();

    void reduce_points_multiplier_time(int16_t time_tick);

    void increase_hunger(int16_t time_tick, class Monster (&monsters)[], int16_t monsters_in_game, bool &pause);

    void check_if_eaten(class Monster (&monsters)[], int16_t monsters_in_game, bool &pause);

    void check_next_level(class Board &board, class Monster (&monsters)[], int16_t monsters_in_game, bool &pause);

    void set_easy_difficulty();

    void set_medium_difficulty();

    void set_hard_difficulty();

    void set_hardcore_difficulty();

    void reset_properties();
};

#endif
