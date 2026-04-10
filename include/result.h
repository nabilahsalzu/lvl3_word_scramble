#ifndef RESULT_H
#define RESULT_H

#include "game.h"

// store final score before showing result screen
void result_set_score(int final_score);

// draw result screen
void draw_result();

// handle button clicks
GameState result_handle_click(int mx, int my);

#endif