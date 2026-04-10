#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "gfx.h"
#include "player.h"


void draw_menu() 
{
    int w = gfx_xsize();
    int h = gfx_ysize();

    gfx_color(0, 0, 0);

    // Main Title
    gfx_text("WORD SCRAMBLE GAME", w/2 - 150, 80, 2);

    // Personalized Greeting
    char greeting[64];
    sprintf(greeting, "Hai %s", current_player.name);
    gfx_color(50, 50, 150); // Dark blue color for greeting
    gfx_text(greeting, w/2 - (strlen(greeting) * 5), 130, 1);

    int btn_w = 300;
    int btn_h = 40;
    int x = (w - btn_w) / 2;

    int y1 = 200;
    int y2 = 260;
    int y3 = 320;

    // Buttons
    gfx_color(200, 200, 200);
    gfx_fillrectangle(x, y1, btn_w, btn_h);
    gfx_fillrectangle(x, y2, btn_w, btn_h);
    gfx_fillrectangle(x, y3, btn_w, btn_h);

    gfx_color(0, 0, 0);
    gfx_text("New Game", x + 100, y1 + 25, 1);
    gfx_text("Help", x + 120, y2 + 25, 1);
    gfx_text("Exit", x + 120, y3 + 25, 1);
}

GameState menu_handle_click(int mx, int my) 
{
    int w = gfx_xsize();
    int btn_w = 300;
    int btn_h = 40;
    int x = (w - btn_w) / 2;

    // New Game
    if (mx >= x && mx <= x + btn_w && my >= 200 && my <= 240)
    {
    	game_init();
		return STATE_PLAYING;
    }

    // Help
    if (mx >= x && mx <= x + btn_w && my >= 260 && my <= 300)
    {
    	return STATE_HELP;
    }

    // Exit
    if (mx >= x && mx <= x + btn_w && my >= 320 && my <= 360)
    {
        return STATE_EXIT;
    }

    return STATE_MENU;
}

// -------- HELP --------
void draw_help() 
{
    int w = gfx_xsize();
    gfx_color(0, 0, 0);
    gfx_text("HOW TO PLAY", w/2 - 70, 100, 2);
    
    gfx_text("- Scrambled letters appear on screen.", 100, 180, 1);
    gfx_text("- Click letters to build the word.", 100, 210, 1);
    gfx_text("- Click SUBMIT to check your answer.", 100, 240, 1);
    gfx_text("- Each correct word gives you points.", 100, 270, 1);
    
    gfx_color(150, 150, 150);
    gfx_fillrectangle(w/2 - 50, 350, 100, 40);
    gfx_color(0, 0, 0);
    gfx_text("BACK", w/2 - 25, 375, 1);
}

GameState help_handle_click(int mx, int my) 
{
    int w = gfx_xsize();
    if (mx >= w/2 - 50 && mx <= w/2 + 50 && my >= 350 && my <= 390) {
        return STATE_MENU;
    }
    return STATE_HELP;
}