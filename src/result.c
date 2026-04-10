#include <stdio.h>
#include "result.h"
#include "gfx.h"
#include "player.h"

// -------- DATA --------
static int final_score = 0;

// Buttons
typedef struct 
{
    int x, y, w, h;
} Button;

static Button play_again_btn;
static Button menu_btn;

// -------- SET SCORE --------
void result_set_score(int score)
{
    final_score = score;
}

// -------- DRAW RESULT SCREEN --------
void draw_result()
{
    int w = gfx_xsize();
    int h = gfx_ysize();

    // Title
    gfx_color(0, 0, 0);
    gfx_text("GAME RESULT", w/2 - 100, 100, 2);

    // Player Name
    char name_text[100];
    sprintf(name_text, "Player: %s", current_player.name);
    gfx_text(name_text, w/2 - 120, 180, 1);

    // Final Score
    char score_text[100];
    sprintf(score_text, "Final Score: %d", final_score);

    gfx_color(0, 100, 255); // blue
    gfx_text(score_text, w/2 - 120, 220, 2);

    // Buttons position
    play_again_btn.x = w/2 - 150;
    play_again_btn.y = 320;
    play_again_btn.w = 120;
    play_again_btn.h = 50;

    menu_btn.x = w/2 + 30;
    menu_btn.y = 320;
    menu_btn.w = 120;
    menu_btn.h = 50;

    // PLAY AGAIN button
    gfx_color(100, 200, 100);
    gfx_fillrectangle(play_again_btn.x, play_again_btn.y, play_again_btn.w, play_again_btn.h);

    gfx_color(0, 0, 0);
    gfx_text("PLAY AGAIN", play_again_btn.x + 10, play_again_btn.y + 30, 1);

    // MAIN MENU button
    gfx_color(200, 100, 100);
    gfx_fillrectangle(menu_btn.x, menu_btn.y, menu_btn.w, menu_btn.h);

    gfx_color(0, 0, 0);
    gfx_text("MAIN MENU", menu_btn.x + 10, menu_btn.y + 30, 1);
}

// -------- HANDLE CLICK --------
GameState result_handle_click(int mx, int my)
{
    // Play Again
    if (mx >= play_again_btn.x && mx <= play_again_btn.x + play_again_btn.w && my >= play_again_btn.y && my <= play_again_btn.y + play_again_btn.h)
    {
        return STATE_CATEGORY;
    }

    // Back to Menu
    if (mx >= menu_btn.x && mx <= menu_btn.x + menu_btn.w && my >= menu_btn.y && my <= menu_btn.y + menu_btn.h)
    {
        return STATE_MENU;
    }

    return STATE_RESULT;
}