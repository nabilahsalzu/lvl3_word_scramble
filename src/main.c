#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <X11/Xlib.h>
#include "gfx.h"
#include "game.h"
#include "menu.h"
#include "player.h"
#include "scoreboard.h"

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

    while (state != STATE_EXIT) {
        time_t now = time(NULL);

    // -------- INPUT --------
    while (gfx_event_waiting()) {
        char event = gfx_wait();

        // Mouse click
        if (event == 1) {
            int mx = gfx_xpos();
            int my = gfx_ypos();

            if (state == STATE_SELECT_PLAYER) {
                state = player_handle_click(mx, my);
            }
            else if (state == STATE_MENU) {
                state = menu_handle_click(mx, my);
            }
            else if (state == STATE_HELP) {
                state = help_handle_click(mx, my);
            }
            else if (state == STATE_PLAYING) {
                state = game_handle_input(event);
            }
            else if (state == STATE_SCOREBOARD)
            {
                state = scoreboard_handle_click(mx, my);
            }

            needs_redraw = 1;
        }

        // KEYBOARD INPUT (THIS IS WHAT YOU WERE MISSING)
        else {
            if (state == STATE_SELECT_PLAYER) {
                player_handle_key(event);
                needs_redraw = 1;
            }
            else if (state == STATE_PLAYING) {
                state = game_handle_input(event);
            }
        }
    }
        // -------- UPDATE GAME --------
        if (state == STATE_PLAYING) {
            state = game_update();

            // Redraw once per second for timer
            if (now != last_redraw_time) {
                needs_redraw = 1;
                last_redraw_time = now;
            }
        }

        // -------- DRAW --------
        if (needs_redraw) {
            // FIX: Instead of gfx_clear() which causes screen tearing/flickering,
            // we draw a filled rectangle over the screen. This queues the background 
            // color with the rest of the frame so it draws smoothly.
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
            

            gfx_flush();
            needs_redraw = 0;
        }

        // Sleep a short time to reduce CPU usage
        usleep(10000); // ~100fps max, smooth enough
    }

    return 0;
}
