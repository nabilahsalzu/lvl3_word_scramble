#ifndef GAME_H
#define GAME_H

#include "state.h"

extern int score;
extern int lives;

void draw_game();
void game_init();
void draw_timer_only();
void save_final_score();
void game_init_with_file(const char *filename);

GameState game_handle_input(char c);
GameState game_update();

#endif
