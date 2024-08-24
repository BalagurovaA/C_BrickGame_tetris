#ifndef S21_FRONTEND_H
#define S21_FRONTEND_H
#include "../../brick_game/tetris/s21_backend.h"

// #define ENTER 10
void settings();
void tetris_the_game();
///////////------------OTHERS------------///////////
void measure(windows *wind_s, int i, int j);
///////////------------COLORS------------///////////
void initialization_of_colors();
///////////------------WINDOWS------------///////////
void initialization_of_windows(windows *wind_s);

///////////------------FIELD------------///////////
void frame(gameplay *game, windows *wind_s);
void field(gameplay *game, windows *wind_s);

/////////------------MAIN-MENU------------///////////
int main_menu(windows *wind_s, int *window_flag);
void start_menu(windows *wind_s);
void exit_menu(windows *wind_s);
void labels(windows *wind_s);

/////////------------PAUSE-MENU------------///////////
int pause_menu(windows *wind_s);
void labels_pause(windows *wind_s);
void pause_continue(windows *wind_s);
void pause_exit(windows *wind_s);

/////////------------ADDICTIONAL-WIN------------///////////
void additional_win(windows *wind_s, gameplay *game);
void print_next_fig(gameplay *game, int next_fig[4][4]);

/////////------------GAMEOVER------------///////////
void game_over_(windows *wind_s, int *window_flag);
void game_ov_labels(windows *wind_s);
#endif