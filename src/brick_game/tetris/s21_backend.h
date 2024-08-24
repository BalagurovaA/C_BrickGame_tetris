#ifndef S21_BACKEND_H
#define S21_BACKEND_H

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HIGH 20  // для масштаба умножила 20 * 2  было 20!
#define WIDTH 10  // для масштаба умножила 10 * 4    было 10!

#define BEGIN_TIMEOUT 1200

#define MENU_HIGHT 40
#define MENU_WIDTH 40

#define NEW_RAND_FIG 1 + rand() % (7)

typedef struct GAME_PLAY {
  int field_[HIGH][WIDTH];
  int state;
  int score;
  int record;
  int type_fig;
  int type_next_f;
  int level;
  int speed;
} gameplay;

typedef struct ALL_WINDOWS {
  WINDOW *win;
  WINDOW *menu;
  WINDOW *pause;
  WINDOW *game_ov;
  WINDOW *add_win;
} windows;

typedef struct ALL_FIGURES {
  int stick[4][4];
  int cube[4][4];
  int left_wing[4][4];
  int right_wing[4][4];
  int left_snake[4][4];
  int right_snake[4][4];
  int pyramide[4][4];
} figures;

typedef struct COORDINATES {
  int i;
  int j;
} coor;

//флаги для определения состояния игры
enum state { BEGIN, SPAWN, MOVING, SHIFTING, ATTACHING, GAMEOVER };

//флаги для определения типа фигуры
enum figure { STICK = 1, CUBE, L_WING, R_WING, L_SNAKE, R_SNAKE, PYRAMIDE };

///////////------------SETTINGS GAME------------/////////////

///////////------------FINITE STATE MACHINE------------///////////
void finite_state_machine(gameplay *game, figures *ST, coor *co,
                          windows *wind_s, int *window_flag);
void FSM_moving(gameplay *game, coor *co, windows *wind_s, int *window_flag);
void FSM_shifting_attaching(gameplay *game, coor *co);

///////////------------STRUCT------------///////////
void zeroing_struct(gameplay *game);

///////////------------SPAWN------------///////////
void spawn(figures *ST, gameplay *game, coor *co, int *window_flag);

///////////------------MOVING------------///////////
void right_move(gameplay *game, coor *co);
void left_move(gameplay *game, coor *co);

///////////------------SHIFTING------------///////////
int acceleration(gameplay *game, coor *co);
int check_the_field(gameplay *game);
void filling_fig_two(gameplay *game);

///////////------------ATTACHING------------///////////
int delete_the_line(gameplay *game);

///////////------------LEVEL-SCORE-RECORD-SPEED------------///////////
void updating_score(int deleted_lines, gameplay *game);
int system_of_levels(gameplay *game);
int system_of_timeout(gameplay *game);

///////////------------ROTATION------------///////////
void figures_rotation(gameplay *game, coor *co);
void cut_matrix_from_field(gameplay *game, coor *co, int cut_matrix[4][4]);
void rotation(int rota_matrix[4][4], int cut_matrix[4][4], gameplay *game);
void writig_in_field(int rota_matrix[4][4], gameplay *game, coor *co);

/////////------------SCORE AND RECORD------------///////////
int reading_from_file();
void writing_in_file(int record);

///////////------------MEASURE------------///////////
void measure(windows *wind_s, int i, int j);

///////////------------WORK WITH THE FIGURES------------///////////
figures *fill_with_cycle(figures *fig_fill);
void filling_figure_(figures *fig_fill, int name_fig);
figures *stick_fill(figures *fig_fill);
figures *cube_fill(figures *fig_fill);
figures *left_wing_fill(figures *fig_fill);
figures *right_wing_fill(figures *fig_fill);
figures *left_snake_fill(figures *fig_fill);
figures *right_snake_fill(figures *fig_fill);
figures *pyramide_fill(figures *fig_fill);
void next_measure(WINDOW *add_win, int i, int j);

///////////------------NEXT FIGURES------------///////////
void next_fig_null(int next_fig[4][4]);
void next_stick(int next_fig[4][4]);
void next_cube(int next_fig[4][4]);
void next_left_wing(int next_fig[4][4]);
void next_right_wing(int next_fig[4][4]);
void next_left_snake(int next_fig[4][4]);
void next_right_snake(int next_fig[4][4]);
void next_pyramide(int next_fig[4][4]);
void next_measure(WINDOW *add_win, int i, int j);
#endif