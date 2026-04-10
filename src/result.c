#include <stdio.h>
#include "result.h"
#include "gfx.h"
#include "player.h"

// -------- DATA --------
static int final_score = 0;
static int end_reason = 0; // 0: Finish, 1: Lives, 2: Quit

// Buttons
typedef struct 
{
    int x, y, w, h;
} Button;

static Button play_again_btn;
static Button menu_btn;

// -------- SET DATA --------
void result_set_score(int score)
{
    final_score = score;
}

void result_set_end_reason(int reason)
{
    end_reason = reason;
}

// -------- DRAW RESULT SCREEN --------
void draw_result()
{
    int w = gfx_xsize();
    int h = gfx_ysize();

    // Clear Screen (Recommended for state transitions)
    gfx_clear_color(240, 240, 240);
    gfx_clear();

    // Title
    gfx_color(0, 0, 0);
    gfx_text("GAME RESULT", w/2 - 100, 60, 2);

    // MESSAGE BASED ON REASON
    gfx_color(50, 50, 50);
    if (end_reason == 0) // Finish all words
    {
        gfx_text("Great job, Detective!", w/2 - 130, 120, 1);
        gfx_text("You solved all clues!", w/2 - 125, 145, 1);
    }
    else if (end_reason == 1) // Zero lives
    {
        gfx_text("Oh no, Detective!", w/2 - 100, 120, 1);
        gfx_text("You ran out of tries!", w/2 - 120, 145, 1);
    }
    else // Quit game
    {
        gfx_text("Mission ended.", w/2 - 80, 120, 1);
        gfx_text("Good work!", w/2 - 60, 145, 1);
    }

    // Player Name
    char name_text[100];
    sprintf(name_text, "Player: %s", current_player.name);
    gfx_color(0, 0, 0);
    gfx_text(name_text, w/2 - 120, 200, 1);

    // Final Score
    char score_text[100];
    sprintf(score_text, "Final Score: %d", final_score);
    gfx_color(0, 100, 255); // blue
    gfx_text(score_text, w/2 - 120, 240, 2);

    // Buttons position
    play_again_btn.x = w/2 - 150;
    play_again_btn.y = 350;
    play_again_btn.w = 120;
    play_again_btn.h = 50;

    menu_btn.x = w/2 + 30;
    menu_btn.y = 350;
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
    if (mx >= play_again_btn.x && mx <= play_again_btn.x + play_again_btn.w && 
        my >= play_again_btn.y && my <= play_again_btn.y + play_again_btn.h)
    {
        return STATE_CATEGORY;
    }

    // Back to Menu
    if (mx >= menu_btn.x && mx <= menu_btn.x + menu_btn.w && 
        my >= menu_btn.y && my <= menu_btn.y + menu_btn.h)
    {
        return STATE_MENU;
    }

    return STATE_RESULT;
}