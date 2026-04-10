#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "category.h"
#include "gfx.h"
#include "intro.h"
#include "game.h"

void draw_category_menu() 
{
    int w = gfx_xsize();
    int h = gfx_ysize();

    gfx_color(0, 0, 0);
    gfx_text("SELECT CATEGORY", w/2 - 110, 80, 2);

    int btn_w = 350;
    int btn_h = 45;
    int x = (w - btn_w) / 2;

    int y_start = 180;
    int spacing = 60;

    char *labels[] = 
    {
        "1. HOME & COLORS",
        "2. NATURE & SCHOOL",
        "3. TECH & SCIENCE",
        "4. RANDOM"
    };

    for(int i = 0; i < 4; i++) 
    {
        gfx_color(220, 220, 220); 
        gfx_fillrectangle(x, y_start + (i * spacing), btn_w, btn_h);
        
        gfx_color(0, 0, 0);
        gfx_text(labels[i], x + 20, y_start + (i * spacing) + 30, 1);
    }

    gfx_color(180, 100, 100);
    gfx_fillrectangle(w/2 - 50, 450, 100, 40);
    gfx_color(255, 255, 255);
    gfx_text("BACK", w/2 - 25, 475, 1);
}

GameState category_handle_click(int mx, int my) 
{
    int w = gfx_xsize();
    int btn_w = 350;
    int btn_h = 45;
    int x = (w - btn_w) / 2;
    int y_start = 180;
    int spacing = 60;

    for(int i = 0; i < 4; i++) 
    {
        int ty = y_start + (i * spacing);

        if (mx >= x && mx <= x + btn_w && my >= ty && my <= ty + btn_h) 
        {
            char filename[32];

            if (i == 3) 
            {
                int r = rand() % 3 + 1;
                sprintf(filename, "data/puzzle%d.txt", r);
            } 
            else 
            {
                sprintf(filename, "data/puzzle%d.txt", i + 1);
            }

            intro_init(filename); 
            return STATE_INTRO;
        }
    }

    if (mx >= w/2 - 50 && mx <= w/2 + 50 && my >= 450 && my <= 490) 
    {
        return STATE_MENU;
    }

    return STATE_CATEGORY;
}