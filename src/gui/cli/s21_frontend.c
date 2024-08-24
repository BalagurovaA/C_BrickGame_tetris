#include "s21_frontend.h"
///////////------------OTHERS------------///////////
void settings() {
  initscr();
  curs_set(0);
  noecho();
  initialization_of_colors();
}

//увеличить масштаб
void measure(windows *wind_s, int i, int j) {
  for (int a = 1; a <= 2; a++) {
    for (int b = 1; b <= 4; b++) {
      mvwaddch(wind_s->win, i + a, j + b, ' ');
    }
  }
}

///////////------------WINDOWS------------///////////
void initialization_of_windows(windows *wind_s) {
  wind_s->win = newwin(42, 42, 0, 0);
  wind_s->menu = newwin(MENU_HIGHT + 2, MENU_WIDTH + 2, 0, 0);
  wind_s->pause = newwin(MENU_HIGHT + 2, MENU_WIDTH + 2, 0, 0);
  wind_s->add_win = newwin(42, 20, 0, 45);
  wind_s->game_ov = newwin(MENU_HIGHT + 2, MENU_WIDTH + 2, 0, 0);
}

/////////------------COLORS------------///////////
void initialization_of_colors() {
  start_color();
  // 1 - номер пары  2 - символов 3 -фон
  init_color(COLOR_BLACK, 0, 100, 300);  //темно синий
  init_color(COLOR_RED, 500, 0, 0);      //темно синий

  init_pair(1, COLOR_BLACK, COLOR_BLACK);  //фон
  init_pair(2, COLOR_BLUE, COLOR_BLUE);  //двигающиеся фигурки
  init_pair(3, COLOR_WHITE, COLOR_WHITE);  // упавшие фигурки + кнопки + рамки

  //     пары для меню
  init_pair(4, COLOR_WHITE, COLOR_BLACK);  //фон + рамка
  init_pair(5, COLOR_BLACK, COLOR_WHITE);  //горящая кнопка
  init_pair(7, COLOR_RED, COLOR_RED);
}

///////////------------FIELD------------///////////
//создание рамки
void frame(gameplay *game, windows *wind_s) {
  wattron(wind_s->win, COLOR_PAIR(4));
  box(wind_s->win, '!', '-');
  wattroff(wind_s->win, COLOR_PAIR(4));

  field(game, wind_s);

  additional_win(wind_s, game);
  wrefresh(wind_s->add_win);
}
//поле
void field(gameplay *game, windows *wind_s) {
  for (int i = 0; i < HIGH; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (game->field_[i][j] == 0) {
        wattron(wind_s->win, COLOR_PAIR(1));
        measure(wind_s, i * 2, j * 4);
        wattroff(wind_s->win, COLOR_PAIR(1));
      } else if (game->field_[i][j] == 2) {
        wattron(wind_s->win, COLOR_PAIR(3));
        measure(wind_s, i * 2, j * 4);
        wattroff(wind_s->win, COLOR_PAIR(3));
      } else {
        wattron(wind_s->win, COLOR_PAIR(2));
        measure(wind_s, i * 2, j * 4);
        wattroff(wind_s->win, COLOR_PAIR(2));
      }
    }
  }
  wrefresh(wind_s->win);
}

/////////------------MAIN-MENU------------///////////
int main_menu(windows *wind_s, int *window_flag) {
  timeout(-1);
  int old_key = 0;
  int key = 0;
  while (*window_flag == 0) {
    box(wind_s->menu, '!', '-' | COLOR_PAIR(4));
    wbkgd(wind_s->menu, COLOR_PAIR(4));
    labels(wind_s);

    key = getch();
    if (key == KEY_UP) {
      wattron(wind_s->menu, COLOR_PAIR(5));
      start_menu(wind_s);
      wattroff(wind_s->menu, COLOR_PAIR(5));
      exit_menu(wind_s);

    } else if (key == KEY_DOWN) {
      wattron(wind_s->menu, COLOR_PAIR(5));
      exit_menu(wind_s);
      wattroff(wind_s->menu, COLOR_PAIR(5));
      start_menu(wind_s);

    } else if (key == 10 && old_key == KEY_DOWN) {
      *window_flag = 3;
    }
    wrefresh(wind_s->menu);

    if (key == 10 && old_key == KEY_UP) {
      *window_flag = 1;
    }
    old_key = key;
  }
  return *window_flag;
}

void start_menu(windows *wind_s) {
  mvwprintw(wind_s->menu, 20, 16, "- - - - - -");
  mvwprintw(wind_s->menu, 21, 16, " S T A R T ");
  mvwprintw(wind_s->menu, 22, 16, "- - - - - -");
}

void exit_menu(windows *wind_s) {
  mvwprintw(wind_s->menu, 24, 16, "- - - - - -");
  mvwprintw(wind_s->menu, 25, 16, "  E X I T  ");
  mvwprintw(wind_s->menu, 26, 16, "- - - - - -");
}

void labels(windows *wind_s) {
  mvwprintw(wind_s->menu, 4, 13, "+");
  mvwprintw(wind_s->menu, 4, 29, "+");

  mvwprintw(wind_s->menu, 5, 14, "+");
  mvwprintw(wind_s->menu, 5, 28, "+");

  mvwprintw(wind_s->menu, 6, 15, ".");
  mvwprintw(wind_s->menu, 6, 27, ".");

  mvwprintw(wind_s->menu, 7, 15, " \\ (^ v ^) /");

  mvwprintw(wind_s->menu, 10, 15, " T E T R I S ");
  mvwprintw(wind_s->menu, 11, 16, "-----------");

  mvwprintw(wind_s->menu, 15, 18, "M E N U");
  mvwprintw(wind_s->menu, 16, 17, "---------");

  mvwprintw(wind_s->menu, 20, 16, "- - - - - -");
  mvwprintw(wind_s->menu, 21, 16, " S T A R T ");
  mvwprintw(wind_s->menu, 22, 16, "- - - - - -");

  mvwprintw(wind_s->menu, 24, 16, "- - - - - -");
  mvwprintw(wind_s->menu, 25, 16, "  E X I T  ");
  mvwprintw(wind_s->menu, 26, 16, "- - - - - -");
}

/////////------------PAUSE-MENU------------///////////
int pause_menu(windows *wind_s) {
  int pause_flag = 0;
  timeout(-1);
  int old_key = 0;
  int key = 0;
  while (pause_flag == 0) {
    box(wind_s->pause, '!', '-');
    wbkgd(wind_s->pause, COLOR_PAIR(4));
    labels_pause(wind_s);
    key = getch();
    if (key == KEY_UP) {
      wattron(wind_s->pause, COLOR_PAIR(2));
      pause_continue(wind_s);
      wattroff(wind_s->pause, COLOR_PAIR(4));
      pause_exit(wind_s);
    } else if (key == KEY_DOWN) {
      wattron(wind_s->pause, COLOR_PAIR(2));
      pause_exit(wind_s);
      wattroff(wind_s->pause, COLOR_PAIR(4));
      pause_continue(wind_s);
    } else if (key == 10 && old_key == KEY_DOWN) {
      pause_flag = 3;
    }
    wrefresh(wind_s->pause);

    if (key == 10 && old_key == KEY_UP) {
      pause_flag = 1;
    }
    old_key = key;
  }
  return pause_flag;
}

void labels_pause(windows *wind_s) {
  mvwprintw(wind_s->pause, 7, 15, " \\ (~ _ ~) /");

  mvwprintw(wind_s->pause, 10, 16, "- - - - - -");
  mvwprintw(wind_s->pause, 11, 16, " P A U S E ");
  mvwprintw(wind_s->pause, 12, 16, "- - - - - -");

  pause_continue(wind_s);
  pause_exit(wind_s);
}

void pause_continue(windows *wind_s) {
  mvwprintw(wind_s->pause, 20, 13, "- - - - - - - - -");
  mvwprintw(wind_s->pause, 21, 13, "C O N T I N U E ?");
  mvwprintw(wind_s->pause, 22, 13, "- - - - - - - - -");
}

void pause_exit(windows *wind_s) {
  mvwprintw(wind_s->pause, 24, 13, "- - - - - - - - -");
  mvwprintw(wind_s->pause, 25, 13, "     E X I T     ");
  mvwprintw(wind_s->pause, 26, 13, "- - - - - - - - -");
}

/////////------------ADDICTIONAL-WIN------------///////////
void additional_win(windows *wind_s, gameplay *game) {
  box(wind_s->add_win, '!', '-');
  wbkgd(wind_s->add_win, COLOR_PAIR(4));

  mvwprintw(wind_s->add_win, 4, 6, "L E V E L");
  mvwprintw(wind_s->add_win, 5, 5, "-----------");
  mvwprintw(wind_s->add_win, 6, 10, "%d", game->level);

  mvwprintw(wind_s->add_win, 9, 6, "S P E E D");
  mvwprintw(wind_s->add_win, 10, 5, "-----------");
  mvwprintw(wind_s->add_win, 11, 9, "%d", game->speed);

  mvwprintw(wind_s->add_win, 20, 5, "R E C O R D");
  mvwprintw(wind_s->add_win, 21, 5, "-----------");
  mvwprintw(wind_s->add_win, 23, 9, "%d", game->record);

  mvwprintw(wind_s->add_win, 27, 7, "N E X T");
  mvwprintw(wind_s->add_win, 29, 5, "F I G U R E");
  mvwprintw(wind_s->add_win, 30, 5, "-----------");

  mvwprintw(wind_s->add_win, 15, 6, "S C O R E");
  mvwprintw(wind_s->add_win, 16, 5, "-----------");
  mvwprintw(wind_s->add_win, 17, 10, "%d", game->score);

  mvwprintw(wind_s->add_win, 38, 7, "T Y P E");
  mvwprintw(wind_s->add_win, 39, 5, "-----------");
  mvwprintw(wind_s->add_win, 40, 10, "%d", game->type_next_f);

  int next_fig[4][4] = {0};

  print_next_fig(game, next_fig);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (next_fig[i][j] == 1) {
        next_measure(wind_s->add_win, i * 2 + 31, j * 4 + 2);
      }
    }
  }
}

void print_next_fig(gameplay *game, int next_fig[4][4]) {
  next_fig_null(next_fig);
  if (game->type_next_f == STICK) {
    next_stick(next_fig);
  } else if (game->type_next_f == CUBE) {
    next_cube(next_fig);
  } else if (game->type_next_f == L_WING) {
    next_left_wing(next_fig);
  } else if (game->type_next_f == R_WING) {
    next_right_wing(next_fig);
  } else if (game->type_next_f == L_SNAKE) {
    next_left_snake(next_fig);
  } else if (game->type_next_f == R_SNAKE) {
    next_right_snake(next_fig);
  } else if (game->type_next_f == PYRAMIDE) {
    next_pyramide(next_fig);
  }
}

/////////------------GAMEOVER------------///////////
void game_over_(windows *wind_s, int *window_flag) {
  box(wind_s->game_ov, '!', '-');
  int key = 0;

  while ((key = getch()) != 'q') {
    game_ov_labels(wind_s);
    wrefresh(wind_s->game_ov);
    *window_flag = 4;
  }
  werase(wind_s->game_ov);
  wrefresh(wind_s->game_ov);
  delwin(wind_s->game_ov);
  // endwin();
}

void game_ov_labels(windows *wind_s) {
  // wbkgd(wind_s->game_ov, COLOR_PAIR(7));
  mvwprintw(wind_s->game_ov, 10, 15, " F O R  Y O U ");
  mvwprintw(wind_s->game_ov, 12, 14, " T H E  G A M E ");
  wattron(wind_s->game_ov, COLOR_PAIR(7));
  mvwprintw(wind_s->game_ov, 14, 15, " I S  O V E R ");
  wattroff(wind_s->game_ov, COLOR_PAIR(7));

  mvwprintw(wind_s->game_ov, 39, 12, "press 'q' to exit");
}