#ifndef CATEGORY_H
#define CATEGORY_H

#include "game.h" // Assuming GameState is defined here

// Function to draw the category selection screen
void draw_category_menu();

// Function to handle clicks on the category selection screen
// Returns the next state of the game
GameState category_handle_click(int mx, int my);

#endif