#ifndef PAC_MAN_MONSTER_H
#define PAC_MAN_MONSTER_H

#include "defs.h"
#include "board.h"
#include "player.h"

enum main_directions_t {
    HORIZONTALLY,
    VERTICALLY
};

enum secondary_directions_t {
    UNSET,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Monster {
private:
    bool is_eaten;
    int16_t x_start;
    int16_t y_start;
    int16_t x;
    int16_t y;
    int16_t respawn_cool_down;
    enum main_directions_t main_direction;
    enum secondary_directions_t secondary_direction;

public:
    void display(bool is_chasing) const;

    [[nodiscard]] int16_t get_x() const;

    [[nodiscard]] int16_t get_y() const;

    [[nodiscard]] bool get_eaten_info() const;

    void set_eaten_flag(bool value);

    void set_respawn_cool_down(int16_t value);

    void set_x_y(int16_t new_x, int16_t new_y);

    void make_move(class Board &board, class Player &player);

    void make_chasing_move(class Board &board, int16_t player_x, int16_t player_y);

    void make_fleeing_move(class Board &board, int16_t player_x, int16_t player_y);

    void reduce_respawn_cool_down();

    void set_start_coordinates(int16_t new_x, int16_t new_y);

    void reset_properties();

    friend void check_monsters_collisions(class Monster (&monsters)[], int16_t monsters_in_game) {
        for (int16_t i = 0; i < monsters_in_game - 1; ++i) {
            for (auto j = int16_t(i + 1); j < monsters_in_game; ++j) {
                if (!monsters[i].is_eaten and monsters[i].x == monsters[j].x and monsters[i].y == monsters[j].y) {
                    monsters[i].is_eaten = true;
                    monsters[i].respawn_cool_down = SET_TIME;
                    monsters[i].set_x_y(0, 0);
                }
            }
        }
    }
};

#endif
