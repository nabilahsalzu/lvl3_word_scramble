#ifndef INTRO_H
#define INTRO_H

#include "game.h"

// Called when category is chosen to set up the text
void intro_init(const char* filename);

// Draws the intro screen
void draw_intro();

// Handles the "I'm Ready" click
GameState intro_handle_click(int mx, int my);

#endif