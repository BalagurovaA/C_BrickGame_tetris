#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "s21_backend.h"

void tetris_the_game();
void finite_state_machine(gameplay *game, figures *ST, coor *co,
                          windows *wind_s, int *window_flag);
void FSM_moving(gameplay *game, coor *co, windows *wind_s, int *window_flag);
void FSM_shifting_attaching(gameplay *game, coor *co);

#endif