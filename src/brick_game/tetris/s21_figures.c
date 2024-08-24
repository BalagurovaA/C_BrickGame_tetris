#include "s21_backend.h"

//заполнение фигур нулем по циклу
figures *fill_with_cycle(figures *fig_fill) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      fig_fill->stick[i][j] = 0;
      fig_fill->cube[i][j] = 0;
      fig_fill->left_wing[i][j] = 0;
      fig_fill->right_wing[i][j] = 0;
      fig_fill->left_snake[i][j] = 0;
      fig_fill->right_snake[i][j] = 0;
      fig_fill->pyramide[i][j] = 0;
    }
  }
  return fig_fill;
}

void filling_figure_(figures *fig_fill, int name_fig) {
  fill_with_cycle(fig_fill);

  if (name_fig == STICK) {
    stick_fill(fig_fill);
  } else if (name_fig == CUBE) {
    cube_fill(fig_fill);
  } else if (name_fig == L_WING) {
    left_wing_fill(fig_fill);
  } else if (name_fig == R_WING) {
    right_wing_fill(fig_fill);
  } else if (name_fig == L_SNAKE) {
    left_snake_fill(fig_fill);
  } else if (name_fig == R_SNAKE) {
    right_snake_fill(fig_fill);
  } else if (name_fig == PYRAMIDE) {
    pyramide_fill(fig_fill);
  }
}

// //палочка
figures *stick_fill(figures *fig_fill) {
  fig_fill->stick[0][0] = 1;
  fig_fill->stick[0][1] = 1;
  fig_fill->stick[0][2] = 1;
  fig_fill->stick[0][3] = 1;
  return fig_fill;
}

// куб
figures *cube_fill(figures *fig_fill) {
  fig_fill->cube[1][1] = 1;
  fig_fill->cube[1][2] = 1;
  fig_fill->cube[2][1] = 1;
  fig_fill->cube[2][2] = 1;
  return fig_fill;
}
//левое крыло
figures *left_wing_fill(figures *fig_fill) {
  fig_fill->left_wing[0][0] = 1;
  fig_fill->left_wing[1][0] = 1;
  fig_fill->left_wing[1][1] = 1;
  fig_fill->left_wing[1][2] = 1;
  return fig_fill;
}
//правое крыло
figures *right_wing_fill(figures *fig_fill) {
  fig_fill->right_wing[0][2] = 1;
  fig_fill->right_wing[1][0] = 1;
  fig_fill->right_wing[1][1] = 1;
  fig_fill->right_wing[1][2] = 1;
  return fig_fill;
}
//левая змея
figures *left_snake_fill(figures *fig_fill) {
  fig_fill->left_snake[0][0] = 1;
  fig_fill->left_snake[0][1] = 1;
  fig_fill->left_snake[1][1] = 1;
  fig_fill->left_snake[1][2] = 1;
  return fig_fill;
}
//правая змея
figures *right_snake_fill(figures *fig_fill) {
  fig_fill->right_snake[0][1] = 1;
  fig_fill->right_snake[0][2] = 1;
  fig_fill->right_snake[1][0] = 1;
  fig_fill->right_snake[1][1] = 1;
  return fig_fill;
}
//пирамида
figures *pyramide_fill(figures *fig_fill) {
  fig_fill->pyramide[0][1] = 1;
  fig_fill->pyramide[1][0] = 1;
  fig_fill->pyramide[1][2] = 1;
  fig_fill->pyramide[1][1] = 1;
  return fig_fill;
}

///////////------------NEXT FIGURES------------///////////

void next_fig_null(int next_fig[4][4]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      next_fig[i][j] = 0;
    }
  }
}

void next_stick(int next_fig[4][4]) {
  next_fig[0][0] = 1;
  next_fig[0][1] = 1;
  next_fig[0][2] = 1;
  next_fig[0][3] = 1;
}

void next_cube(int next_fig[4][4]) {
  next_fig[1][1] = 1;
  next_fig[1][2] = 1;
  next_fig[2][1] = 1;
  next_fig[2][2] = 1;
}

void next_left_wing(int next_fig[4][4]) {
  next_fig[0][0] = 1;
  next_fig[1][0] = 1;
  next_fig[1][1] = 1;
  next_fig[1][2] = 1;
}

void next_right_wing(int next_fig[4][4]) {
  next_fig[0][2] = 1;
  next_fig[1][0] = 1;
  next_fig[1][1] = 1;
  next_fig[1][2] = 1;
}

void next_left_snake(int next_fig[4][4]) {
  next_fig[0][0] = 1;
  next_fig[0][1] = 1;
  next_fig[1][1] = 1;
  next_fig[1][2] = 1;
}

void next_right_snake(int next_fig[4][4]) {
  next_fig[0][1] = 1;
  next_fig[0][2] = 1;
  next_fig[1][0] = 1;
  next_fig[1][1] = 1;
}

void next_pyramide(int next_fig[4][4]) {
  next_fig[0][1] = 1;
  next_fig[1][0] = 1;
  next_fig[1][2] = 1;
  next_fig[1][1] = 1;
}

void next_measure(WINDOW *add_win, int i, int j) {
  for (int a = 1; a <= 2; a++) {
    for (int b = 1; b <= 4; b++) {
      wattron(add_win, COLOR_PAIR(2));
      mvwprintw(add_win, i + a, j + b, " ");
    }
  }
}