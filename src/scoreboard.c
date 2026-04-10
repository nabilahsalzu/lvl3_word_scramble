#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scoreboard.h"
#include "gfx.h"
#include "player.h"

#define MAX_SCORES 100

static int scores[MAX_SCORES];
static int score_count = 0;
static int latest_score = -1; // To track the last score achieved

// ---------------- LOAD CURRENT PLAYER SCORES ----------------
static void load_scores()
{
    score_count = 0;
    latest_score = -1;

    char path[64];
    sprintf(path, "players/%s.txt", current_player.name);

    FILE *f = fopen(path, "r");
    if (!f) return;

    int val;
    // Read all scores
    while (score_count < MAX_SCORES && fscanf(f, "%d", &val) == 1)
    {
        scores[score_count++] = val;
    }
    
    // The last score in the file is the "latest" one played
    if (score_count > 0) {
        latest_score = scores[score_count - 1];
    }

    fclose(f);

    // ---------------- SORT DESCENDING ----------------
    for (int i = 0; i < score_count - 1; i++)
    {
        for (int j = i + 1; j < score_count; j++)
        {
            if (scores[j] > scores[i])
            {
                int temp = scores[i];
                scores[i] = scores[j];
                scores[j] = temp;
            }
        }
    }

    // keep only top 10
    if (score_count > 10)
        score_count = 10;
}

// ---------------- DRAW SCOREBOARD ----------------
void draw_scoreboard()
{
    int w = gfx_xsize();

    gfx_color(0, 0, 0);
    gfx_text("MY SCORES", w/2 - 70, 80, 2);

    load_scores();

    if (score_count == 0)
    {
        gfx_text("No scores yet. Play a game!", w/2 - 120, 200, 1);
    }
    else
    {
        gfx_text("TOP 10 BEST SCORES", w/2 - 120, 120, 1);

        int y = 170;
        int found_latest = 0; // Ensure we only highlight the latest once if there are duplicates

        for (int i = 0; i < score_count; i++)
        {
            // Default color: Black
            gfx_color(0, 0, 0);
            char suffix[20] = "";

            // 1. Highlight Best Score (Gold/Yellow)
            if (i == 0) {
                gfx_color(212, 175, 55); // Gold color
                strcpy(suffix, " (BEST)");
            } 
            
            // 2. Highlight Latest Score (Blue)
            // We check if this entry matches the latest_score value 
            // and if we haven't highlighted a "latest" tag yet in this session
            if (scores[i] == latest_score && !found_latest) {
                gfx_color(0, 100, 255); // Blue color
                strcat(suffix, " (LATEST)");
                found_latest = 1;
            }

            char line[128];
            sprintf(line, "%d. %d%s", i + 1, scores[i], suffix);

            gfx_text(line, w/2 - 60, y, 1);
            y += 30;
        }
    }

    // BACK BUTTON
    gfx_color(180, 180, 180);
    gfx_fillrectangle(w/2 - 50, 420, 100, 40);

    gfx_color(0, 0, 0);
    gfx_text("BACK", w/2 - 20, 445, 1);
}

// ---------------- CLICK HANDLER ----------------
GameState scoreboard_handle_click(int mx, int my)
{
    int w = gfx_xsize();

    // Adjusted Y to match the new draw position (420 instead of 380)
    if (mx >= w/2 - 50 && mx <= w/2 + 50 &&
        my >= 420 && my <= 460)
    {
        return STATE_MENU;
    }

    return STATE_SCOREBOARD;
}