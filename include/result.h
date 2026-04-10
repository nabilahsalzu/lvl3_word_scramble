#ifndef RESULT_H
#define RESULT_H

#include "state.h"

void result_set_score(int final_score);
void draw_result();

GameState result_handle_click(int mx, int my);

#endif