#include "s21_controller.h"

#include "../../gui/cli/s21_frontend.h"
#include "s21_backend.h"
void tetris_the_game() {
  figures ST;
  gameplay game;
  coor co;
  windows wind_s;
  initialization_of_windows(&wind_s);
  co.i = 0;
  co.j = 0;
  zeroing_struct(&game);
  game.record = reading_from_file();
  keypad(stdscr, 1);
  nodelay(wind_s.win, true);
  srand(time(NULL));
  int window_flag = 0;
  main_menu(&wind_s, &window_flag);
  while (window_flag == 1) {
    timeout(game.speed);
    finite_state_machine(&game, &ST, &co, &wind_s, &window_flag);
  }
  game_over_(&wind_s, &window_flag);
  writing_in_file(game.record);
  endwin();
}
///////////------------FINITE STATE MACHINE------------///////////
void finite_state_machine(gameplay *game, figures *ST, coor *co,
                          windows *wind_s, int *window_flag) {
  if (game->level <= 10 && game->level >= 0) {
    system_of_levels(game);
    system_of_timeout(game);
  }
  frame(game, wind_s);
  if (game->state == BEGIN) {
    game->state = SPAWN;
  } else if (game->state == SPAWN) {
    spawn(ST, game, co, window_flag);
    game->state = MOVING;
  } else if (game->state == MOVING) {
    FSM_moving(game, co, wind_s, window_flag);
  } else if (game->state == SHIFTING) {
    FSM_shifting_attaching(game, co);
  } else if (game->level >= 10) {
    game->state = GAMEOVER;
  } else if (game->state == GAMEOVER) {
    game_over_(wind_s, window_flag);
  }
}

//движение право лево поворот
void FSM_moving(gameplay *game, coor *co, windows *wind_s, int *window_flag) {
  int key = 0;
  key = getch();
  if (key == KEY_RIGHT) {
    right_move(game, co);
  } else if (key == KEY_LEFT) {
    left_move(game, co);
  } else if (key == KEY_UP) {
    figures_rotation(game, co);
  } else if (key == KEY_DOWN) {
    acceleration(game, co);
  } else if (key == 'p') {
    if (pause_menu(wind_s) == 3) {
      *window_flag = 3;
    }
  }
  game->state = SHIFTING;
}

//падение удаление линий
void FSM_shifting_attaching(gameplay *game, coor *co) {
  if (acceleration(game, co) == 1) {
    game->state = MOVING;
  } else
    game->state = ATTACHING;
  if (game->state == ATTACHING) {
    if (acceleration(game, co) != 1) {
      delete_the_line(game);
      game->state = SPAWN;
    }
  }
}
