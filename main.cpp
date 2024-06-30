#include "defs.h"
#include "board.h"
#include "player.h"
#include "monster.h"

using namespace std;

int main() {
    create_high_score_files(FILE_HIGH_SCORE_EASY);
    create_high_score_files(FILE_HIGH_SCORE_MEDIUM);
    create_high_score_files(FILE_HIGH_SCORE_HARD);
    create_high_score_files(FILE_HIGH_SCORE_HARDCORE);
    set_fullscreen();
    hide_cursor();
    display_dark_screen();
    class Board board{};
    board.display_start_game_screen();
    bool repeat_game = false;
    enum difficulties_t difficulty;
    while (true) {
        if (!repeat_game) {
            bool start_game = false;
            while (!start_game) {
                switch (board.display_menu_screen()) {
                    case MENU_START_GAME:
                        difficulty = board.display_choose_difficulty_screen();
                        if (difficulty != DIFFICULTIES_RETURN) {
                            start_game = true;
                        }
                        break;
                    case MENU_SHOW_SCOREBOARD:
                        while (true) {
                            bool exit_scoreboard_menu = false;
                            switch (board.display_scoreboard_menu_screen()) {
                                case SCOREBOARD_MENU_EASY:
                                    board.display_scoreboard(FILE_SCOREBOARD_EASY, DIFFICULTIES_EASY);
                                    break;
                                case SCOREBOARD_MENU_MEDIUM:
                                    board.display_scoreboard(FILE_SCOREBOARD_MEDIUM, DIFFICULTIES_MEDIUM);
                                    break;
                                case SCOREBOARD_MENU_HARD:
                                    board.display_scoreboard(FILE_SCOREBOARD_HARD, DIFFICULTIES_HARD);
                                    break;
                                case SCOREBOARD_MENU_HARDCORE:
                                    board.display_scoreboard(FILE_SCOREBOARD_HARDCORE, DIFFICULTIES_HARDCORE);
                                    break;
                                case SCOREBOARD_MENU_HIGH_SCORES:
                                    board.display_high_scores();
                                    break;
                                case SCOREBOARD_MENU_RETURN:
                                    exit_scoreboard_menu = true;
                                default:
                                    break;
                            }
                            if (exit_scoreboard_menu) {
                                break;
                            }
                        }
                        break;
                    case MENU_SETTINGS:
                        while (board.display_settings_screen() != SETTINGS_RETURN);
                        break;
                    case MENU_HELP:
                        board.display_help_screen();
                        break;
                    case MENU_CREDITS:
                        board.display_credits_screen();
                        break;
                    case MENU_QUIT_GAME:
                        if (board.display_confirmation_screen()) {
                            board.display_goodbye_screen();
                            system("cls");
                            return 0;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
        class Player player;
        int16_t tick = 0;
        int16_t tick_speed;
        int16_t monsters_in_game;
        int16_t monsters_speed;
        switch (difficulty) {
            case DIFFICULTIES_EASY:
                player.set_easy_difficulty();
                monsters_in_game = EASY_MONSTERS_IN_GAME;
                monsters_speed = EASY_MONSTER_SPEED;
                tick_speed = EASY_TICK_SPEED;
                break;
            case DIFFICULTIES_MEDIUM:
                player.set_medium_difficulty();
                monsters_in_game = MEDIUM_MONSTERS_IN_GAME;
                monsters_speed = MEDIUM_MONSTER_SPEED;
                tick_speed = MEDIUM_TICK_SPEED;
                break;
            case DIFFICULTIES_HARD:
                player.set_hard_difficulty();
                monsters_in_game = HARD_MONSTERS_IN_GAME;
                monsters_speed = HARD_MONSTER_SPEED;
                tick_speed = HARD_TICK_SPEED;
                break;
            case DIFFICULTIES_HARDCORE:
                player.set_hardcore_difficulty();
                monsters_in_game = HARDCORE_MONSTERS_IN_GAME;
                monsters_speed = HARDCORE_MONSTER_SPEED;
                tick_speed = HARDCORE_TICK_SPEED;
                break;
            default:
                break;
        }
        class Monster monsters[8];
        monsters[0].set_start_coordinates(4, 3);
        monsters[1].set_start_coordinates(92, 3);
        monsters[2].set_start_coordinates(4, 23);
        monsters[3].set_start_coordinates(92, 23);
        monsters[4].set_start_coordinates(48, 3);
        monsters[5].set_start_coordinates(48, 23);
        monsters[6].set_start_coordinates(12, 13);
        monsters[7].set_start_coordinates(84, 13);
        for (int16_t i = 0; i < monsters_in_game; ++i) {
            monsters[i].reset_properties();
        }
        board.display_next_map(player, monsters, monsters_in_game);
        GetAsyncKeyState(VK_SPACE);
        bool pause = true;
        while (player.get_lives()) {
            check_pause(pause);
            player.make_move(board);
            if (tick % monsters_speed == 0) {
                for (int i = 0; i < monsters_in_game; ++i) {
                    monsters[i].make_move(board, player);
                }
            }
            player.check_if_eaten(monsters, monsters_in_game, pause);
            player.check_next_level(board, monsters, monsters_in_game, pause);
            player.increase_hunger(tick, monsters, monsters_in_game, pause);
            player.reduce_points_multiplier_time(tick);
            player.reduce_freeze_time(tick);
            player.reduce_frozen_time();
            player.reduce_elixir();
            player.display();
            check_monsters_collisions(monsters, monsters_in_game);
            for (int i = 0; i < monsters_in_game; ++i) {
                monsters[i].reduce_respawn_cool_down();
                monsters[i].display(player.get_elixir());
            }
            Sleep(tick_speed);
            ++tick;
        }
        size_t high_score;
        bool high_score_beaten = false;
        switch (player.get_difficulty()) {
            case DIFFICULTIES_EASY:
                high_score_beaten = save_score(FILE_HIGH_SCORE_EASY, FILE_SCOREBOARD_EASY, &high_score,
                                               player.get_points());
                break;
            case DIFFICULTIES_MEDIUM:
                high_score_beaten = save_score(FILE_HIGH_SCORE_MEDIUM, FILE_SCOREBOARD_MEDIUM, &high_score,
                                               player.get_points());
                break;
            case DIFFICULTIES_HARD:
                high_score_beaten = save_score(FILE_HIGH_SCORE_HARD, FILE_SCOREBOARD_HARD, &high_score,
                                               player.get_points());
                break;
            case DIFFICULTIES_HARDCORE:
                high_score_beaten = save_score(FILE_HIGH_SCORE_HARDCORE, FILE_SCOREBOARD_HARDCORE, &high_score,
                                               player.get_points());
                break;
            default:
                break;
        }
        repeat_game = board.display_game_over_screen(player, high_score, high_score_beaten);
    }
}
