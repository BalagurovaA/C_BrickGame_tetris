#include "s21_backend.h"

#include "s21_controller.h"

///////////------------STRUCT------------///////////
//зануление поля
void zeroing_struct(gameplay *game) {
  game->state = 0;
  game->score = 0;
  game->record = 0;
  game->level = 0;
  game->type_fig = 0;
  game->type_next_f = 0;
  game->level = 0;
  game->speed = 0;

  for (int i = 0; i < HIGH; i++) {
    for (int j = 0; j < WIDTH; j++) {
      game->field_[i][j] = 0;
    }
  }
  game->state = BEGIN;
}

///////////------------SPAWN------------///////////
//появление фигуры в поле
void spawn(figures *ST, gameplay *game, coor *co, int *window_flag) {
  game->type_fig = game->type_next_f;
  game->type_next_f = NEW_RAND_FIG;
  int n = 0;
  int m = 0;
  filling_figure_(ST, game->type_fig);
  for (int a = 0; a <= 3; a++) {
    m = 0;
    for (int b = 3; b < 7; b++) {
      if (game->type_fig == STICK && ST->stick[n][m] == 1) {
        game->field_[a][b] = ST->stick[n][m];
      } else if (game->type_fig == CUBE && ST->cube[n][m] == 1) {
        game->field_[a][b] = ST->cube[n][m];
      } else if (game->type_fig == L_WING && ST->left_wing[n][m] == 1) {
        game->field_[a][b] = ST->left_wing[n][m];
      } else if (game->type_fig == R_WING && ST->right_wing[n][m] == 1) {
        game->field_[a][b] = ST->right_wing[n][m];
      } else if (game->type_fig == L_SNAKE && ST->left_snake[n][m]) {
        game->field_[a][b] = ST->left_snake[n][m];
      } else if (game->type_fig == R_SNAKE && ST->right_snake[n][m]) {
        game->field_[a][b] = ST->right_snake[n][m];
      } else if (game->type_fig == PYRAMIDE && ST->pyramide[n][m] == 1) {
        game->field_[a][b] = ST->pyramide[n][m];
      }
      m++;
      co->j = b;
      co->i = a;

      for (int jj = 0; jj < WIDTH; jj++) {
        if (game->field_[0][jj] == 1 && game->field_[2][jj] == 2) {
          game->state = GAMEOVER;
          *window_flag = 3;
        }
      }
    }
    n++;
    m = 0;
  }
}

///////////------------MOVING------------///////////
void right_move(gameplay *game, coor *co) {
  int state_fig = 1;
  if (check_the_field(game) != 1) {
    for (int i = HIGH - 1; i >= 0 && state_fig == 1; i--) {
      for (int j = WIDTH - 1; j >= 0 && state_fig == 1; j--) {
        if (game->field_[i][j] == 1 && j == WIDTH - 1) {
          state_fig = 2;
        } else if (i != 0 && j != 0 && game->field_[i - 1][j] == 1 &&
                   j + 1 == WIDTH && game->field_[i + 1][j] == 0 &&
                   game->field_[i][j - 1] == 1) {
          state_fig = 2;
        } else if (game->field_[i][j] == 1 && j < WIDTH - 1 &&
                   game->field_[i][j + 1] != 2) {
          game->field_[i][j] = 0;
          game->field_[i][j + 1] = 1;
          state_fig = 1;
        }
      }
    }

    if (state_fig == 1) co->j++;
  }
}

void left_move(gameplay *game, coor *co) {
  int state_fig = 1;
  if (check_the_field(game) != 1) {
    for (int i = HIGH - 1; i >= 0 && state_fig == 1; i--) {
      for (int j = 0; j < WIDTH && state_fig == 1; j++) {
        if (game->field_[i][j] == 1 && j == 0) {
          state_fig = 2;
          //   // чтобы фигура не меняла форму рядом с границей
        } else if (i != 0 && j != 0 && game->field_[i - 1][j] == 1 &&
                   game->field_[i][j + 1] == 1 && game->field_[i + 1][j] == 0 &&
                   j == 0) {
          state_fig = 2;
        } else if (game->field_[i][j] == 1 && j >= 0) {
          game->field_[i][j] = 0;
          game->field_[i][j - 1] = 1;
          state_fig = 1;
        }
      }
    }
    if (state_fig == 1) co->j = co->j - 1;
  }
}

///////////------------SHIFTING------------///////////
int acceleration(gameplay *game, coor *co) {
  //состояние фигуры 0 = начало, 1 = движется, 2 =упала, 3 = достигла верхней гр
  //поля
  int state_fig = 0;
  int i = 0;
  int j = 0;
  if (check_the_field(game) == 0) {
    for (i = HIGH - 1; i >= 0 && state_fig != 2; i--) {
      for (j = 0; j < WIDTH && state_fig != 2; j++) {
        if (game->field_[i][j] == 1 &&
            (i == HIGH - 1 || game->field_[i + 1][j] == 2)) {
          filling_fig_two(game);
          state_fig = 2;

        } else if (game->field_[i][j] == 1 && i + 1 < HIGH) {
          game->field_[i][j] = 0;
          game->field_[i + 1][j] = 1;
          state_fig = 1;
        }
      }
    }
    if (state_fig == 1) {
      co->i++;
    }
  }

  return state_fig;
}

//проверка поля на состояние фигуры
int check_the_field(gameplay *game) {  // 0 - фигуры нет
  int flag = 0;                        // 1 - фигура есть
  for (int i = HIGH - 1; i >= 0; i--) {
    for (int j = 0; j < WIDTH; j++) {
      if (game->field_[i][j] == 1 && i + 1 < HIGH &&
          game->field_[i + 1][j] == 2) {
        flag = 1;
        filling_fig_two(game);
      }
    }
  }
  return flag;
}
//заполнение фигуры двойками
void filling_fig_two(gameplay *game) {
  for (int i = HIGH - 1; i >= 0; i--) {
    for (int j = 0; j < WIDTH; j++) {
      if (game->field_[i][j] == 1) game->field_[i][j] = 2;
    }
  }
}

///////////------------ATTACHING------------///////////
int delete_the_line(gameplay *game) {
  int deleted_lines = 0;
  int is_line_full = 0;
  for (int i = HIGH - 1; i >= 0; i--) {
    is_line_full = true;
    for (int j = 0; j < WIDTH; j++) {
      if (game->field_[i][j] != 2) {
        is_line_full = false;
        break;
      }
    }
    if (is_line_full == true) {
      deleted_lines++;
      for (int x = i; x > 0; x--) {
        for (int z = 0; z < WIDTH; z++) {
          game->field_[x][z] = game->field_[x - 1][z];
        }
      }
      i++;
    }
  }
  // Обновляем счет и рекорд
  if (deleted_lines > 0) {
    updating_score(deleted_lines, game);
  }
  return deleted_lines;
}

// обновляем счет и рекорд
void updating_score(int deleted_lines, gameplay *game) {
  switch (deleted_lines) {
    case 4:
      game->score += 1500;
      break;
    case 3:
      game->score += 700;
      break;
    case 2:
      game->score += 300;
      break;
    case 1:
      game->score += 100;
      break;
    default:
      break;
  }
  if (game->score > game->record) {
    game->record = game->score;
  }
}

// уровни
int system_of_levels(gameplay *game) {
  game->level = game->score / 600;
  return game->level;
}

int system_of_timeout(gameplay *game) {
  game->speed = (BEGIN_TIMEOUT - (game->level * 100));
  return game->speed;
}

/////////------------ROTATION------------///////////
void figures_rotation(gameplay *game, coor *co) {
  int rota_matrix[4][4] = {0};
  int cut_matrix[4][4] = {0};
  cut_matrix_from_field(game, co, cut_matrix);
  rotation(rota_matrix, cut_matrix, game);
  writig_in_field(rota_matrix, game, co);
}

// вырезаю матрицу из поля
void cut_matrix_from_field(gameplay *game, coor *co, int cut_matrix[4][4]) {
  int c_i = co->i;
  int c_j = co->j;

  for (int i = 3; i >= 0; i--) {
    c_j = co->j;
    for (int j = 3; j >= 0; j--) {
      if (game->field_[c_i][c_j] == 1) {
        cut_matrix[i][j] = game->field_[c_i][c_j];
      }
      c_j--;
    }
    c_i--;
  }
}

// переворачиваю
void rotation(int rota_matrix[4][4], int cut_matrix[4][4], gameplay *game) {
  for (int rota_i = 0; rota_i < 4; rota_i++) {
    for (int rota_j = 0; rota_j < 4 && rota_matrix[rota_i][rota_j] != 2;
         rota_j++) {
      rota_matrix[rota_i][rota_j] = cut_matrix[3 - rota_j][rota_i];
    }
  }
  // свдигаю немного влево чтобы аккуратно вращался
  for (int i = 0; i < 4 && game->type_fig != 1; i++) {
    for (int j = 1; j < 4; j++) {
      rota_matrix[i][j - 1] = rota_matrix[i][j];
      rota_matrix[i][j] = 0;
    }
  }
}

//записываю в поле
void writig_in_field(int rota_matrix[4][4], gameplay *game, coor *co) {
  int c_i = co->i;
  int c_j = co->j;
  int flag = 0;
  if (c_j >= WIDTH) {
    flag = 1;
  } else if (c_j <= 3) {
    //здесь может быть ошибка
    flag = 1;
  } else {
    for (int r_i = 3; r_i >= 0 && flag != 1; r_i--) {
      for (int r_j = 3; r_j >= 0 && flag != 1; r_j--) {
        if (rota_matrix[r_i][r_j] == 1 && game->field_[c_i][c_j] == 2) flag = 1;
      }
    }
    for (int r_i = 3; r_i >= 0 && flag != 1; r_i--) {
      for (int r_j = 3; r_j >= 0 && flag != 1; r_j--) {
        ///

        if (game->field_[c_i][c_j] == 1) {
          game->field_[c_i][c_j] = 0;
        }

        if (c_j > 0 && c_j < WIDTH && rota_matrix[r_i][r_j] == 1 &&
            game->field_[c_i][c_j] != 2) {
          game->field_[c_i][c_j] = rota_matrix[r_i][r_j];
        }
        c_j--;
      }
      c_i--;
      c_j = co->j;
    }
  }
}

/////////------------SCORE AND RECORD------------///////////
int reading_from_file() {
  FILE *file;
  int old_record = 0;
  file = fopen("score.txt", "r");
  if (file != NULL) {
    fscanf(file, "%d", &old_record);
  }
  return old_record;
}

void writing_in_file(int record) {
  FILE *file;
  file = fopen("score.txt", "w");
  if (file != NULL) fprintf(file, "%d", record);
}