#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "intro.h"
#include "gfx.h"
#include "game.h"

// We use static variables to keep the data alive between init and draw
static int current_category_id = 0;
static char pending_filename[64];

void intro_init(const char* filename) 
{
    // Copy the full path to use when the game actually starts
    strncpy(pending_filename, filename, sizeof(pending_filename) - 1);

    // Reset ID to default (Random Mix)
    current_category_id = 0;

    // Use strstr to find the puzzle number in the path (e.g., "data/puzzle1.txt")
    if (strstr(filename, "puzzle1.txt") != NULL) 
    {
        current_category_id = 1;
    } 
    else if (strstr(filename, "puzzle2.txt") != NULL) 
    {
        current_category_id = 2;
    } 
    else if (strstr(filename, "puzzle3.txt") != NULL) 
    {
        current_category_id = 3;
    }
    
}

void draw_intro() 
{
    int w = gfx_xsize();
    int h = gfx_ysize();

    // Clear background to dark blue/grey for visibility
    gfx_clear_color(30, 30, 50);
    gfx_clear();

    // Text Alignment Helpers
    int centerX = w / 2;

    // ===== CATEGORY TITLE =====
    gfx_color(255, 255, 0); // Bright Yellow
    if (current_category_id == 1) {
        gfx_text("HOME & COLORS", centerX - 100, 150, 2);
    } else if (current_category_id == 2) {
        gfx_text("NATURE & SCHOOL", centerX - 120, 150, 2);
    } else if (current_category_id == 3) {
        gfx_text("TECH & SCIENCE", centerX - 110, 150, 2);
    } else {
        gfx_text("RANDOM MIX", centerX - 80, 150, 2);
    }

    // ===== STORY MESSAGE =====
    gfx_color(255, 255, 255); // White
    if (current_category_id == 1) {
        gfx_text("You are in a magic house!", centerX - 130, 240, 1);
        gfx_text("Find things and colors!", centerX - 115, 270, 1);
    } else if (current_category_id == 2) {
        gfx_text("You are in a forest behind your school!", centerX - 180, 240, 1);
        gfx_text("Find nature and school things!", centerX - 145, 270, 1);
    } else if (current_category_id == 3) {
        gfx_text("You are in a computer lab!", centerX - 135, 240, 1);
        gfx_text("Help fix the robot!", centerX - 90, 270, 1);
    } else {
        gfx_text("A mix of everything!", centerX - 100, 240, 1);
        gfx_text("Are you ready for the challenge?", centerX - 150, 270, 1);
    }

    // ===== START BUTTON =====
    int btnW = 200;
    int btnH = 50;
    int btnX = centerX - (btnW / 2);
    int btnY = 400;

    gfx_color(0, 200, 100); // Green
    gfx_fillrectangle(btnX, btnY, btnW, btnH);

    gfx_color(255, 255, 255); // White Text
    gfx_text("I'M READY", btnX + 55, btnY + 32, 1);
}

GameState intro_handle_click(int mx, int my) 
{
    int w = gfx_xsize();
    int btnW = 200;
    int btnH = 50;
    int btnX = (w / 2) - (btnW / 2);
    int btnY = 400;

    // Check if user clicked inside the button bounds
    if (mx >= btnX && mx <= btnX + btnW && my >= btnY && my <= btnY + btnH) 
    {
        // Now we actually load the word file and start
        game_init_with_file(pending_filename);
        return STATE_PLAYING;
    }

    return STATE_INTRO;
}