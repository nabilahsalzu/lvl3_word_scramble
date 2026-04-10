#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <X11/Xlib.h>
#include "gfx.h"
#include "game.h"
#include "menu.h"
#include "player.h"
#include "scoreboard.h"
#include "result.h"
#include "category.h"
#include "intro.h"

int main() 
{
    // Get screen size
    Display *d = XOpenDisplay(NULL);
    int screen = DefaultScreen(d);
    int screen_width = DisplayWidth(d, screen);
    int screen_height = DisplayHeight(d, screen);

    // 3/4 window size
    int win_width = screen_width * 3 / 4;
    int win_height = screen_height * 3 / 4;

    gfx_open(win_width, win_height, "WORD SCRAMBLE GAME");

    GameState state = STATE_SELECT_PLAYER;
    int needs_redraw = 1;

    // For controlling timer redraw (once per second)
    time_t last_redraw_time = 0;

    while (state != STATE_EXIT) 
    {
        time_t now = time(NULL);

        // -------- INPUT --------
        while (gfx_event_waiting()) {
            char event = gfx_wait();

            // Mouse click
            if (event == 1) 
            {
                int mx = gfx_xpos();
                int my = gfx_ypos();

                if (state == STATE_SELECT_PLAYER) 
                {
                    state = player_handle_click(mx, my);
                }

                else if (state == STATE_MENU) 
                {
                    state = menu_handle_click(mx, my);
                }

                else if (state == STATE_CATEGORY) 
                {
                    state = category_handle_click(mx, my);
                }

                else if (state == STATE_INTRO) 
                {
                    state = intro_handle_click(mx, my);
                }

                else if (state == STATE_HELP) 
                {
                    state = help_handle_click(mx, my);
                }

                else if (state == STATE_PLAYING) 
                {
                    state = game_handle_input(event);
                }

                else if (state == STATE_SCOREBOARD)
                {
                    state = scoreboard_handle_click(mx, my);
                }

                else if (state == STATE_RESULT)
                {
                    state = result_handle_click(mx, my);

                    if (state == STATE_PLAYING)
                    {
                        game_init(); // restart game
                    }
                }

                needs_redraw = 1;
            }

            // KEYBOARD INPUT
            else 
            {
                if (state == STATE_SELECT_PLAYER) 
                {
                    player_handle_key(event);
                    needs_redraw = 1;
                }

                else if (state == STATE_PLAYING) 
                {
                    state = game_handle_input(event);
                }
            }
        }

        // -------- UPDATE GAME --------
        if (state == STATE_PLAYING) 
        {
            state = game_update();
            // Redraw once per second for timer
            if (now != last_redraw_time) {
                needs_redraw = 1;
                last_redraw_time = now;
            }
        }

        // -------- DRAW --------
        if (needs_redraw) 
        {
            gfx_color(255, 255, 255);
            gfx_fillrectangle(0, 0, win_width, win_height);

            if (state == STATE_SELECT_PLAYER)
            {
                draw_player_select();
            }

            else if (state == STATE_MENU)
            {
                draw_menu();
            }

            else if (state == STATE_CATEGORY)
            {
                draw_category_menu();
            }

            else if (state == STATE_INTRO)
            {
                draw_intro();
            }

            else if (state == STATE_HELP)
            {
                draw_help();
            }

            else if (state == STATE_PLAYING)
            {
                draw_game();
            }

            else if (state == STATE_SCOREBOARD)
            {
                draw_scoreboard();
            }

            else if (state == STATE_RESULT)
            {
                draw_result();
            }
            
            gfx_flush();
            needs_redraw = 0;
        }

        usleep(10000);
    }

    return 0;
}
