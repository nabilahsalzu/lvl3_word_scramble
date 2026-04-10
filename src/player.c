#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "player.h"
#include "gfx.h"

// Sub-states for the selection screen
typedef enum {
    MODE_CHOICE,    // Buttons: New or Old
    MODE_NEW,       // Input name
    MODE_OLD        // List files
} SelectionMode;

Player current_player = {"", 0};
static SelectionMode current_mode = MODE_CHOICE;

// Buffer for new player input
static char input_buffer[32] = "";
static int input_index = 0;

// List for old players
static char existing_players[10][32];
static int player_count = 0;

// Ensure players directory exists
void check_dir() {
    struct stat st = {0};
    if (stat("players", &st) == -1) {
        mkdir("players", 0700);
    }
}

void load_existing_players() {
    check_dir();
    player_count = 0;
    DIR *d = opendir("players");
    if (d) {
        struct dirent *dir;
        while ((dir = readdir(d)) != NULL && player_count < 10) {
            // Only take .txt files
            if (strstr(dir->d_name, ".txt")) {
                char *ext = strstr(dir->d_name, ".txt");
                int len = ext - dir->d_name;
                strncpy(existing_players[player_count], dir->d_name, len);
                existing_players[player_count][len] = '\0';
                player_count++;
            }
        }
        closedir(d);
    }
}

void save_player_data() {
    if (strlen(current_player.name) == 0) return;
    char path[64];
    sprintf(path, "players/%s.txt", current_player.name);
    FILE *f = fopen(path, "w");
    if (f) {
        fprintf(f, "%d", current_player.high_score);
        fclose(f);
    }
}

void load_player_data(const char* name) {
    strncpy(current_player.name, name, 31);
    char path[64];
    sprintf(path, "players/%s.txt", name);
    FILE *f = fopen(path, "r");
    if (f) {
        fscanf(f, "%d", &current_player.high_score);
        fclose(f);
    } else {
        current_player.high_score = 0;
    }
}

void draw_player_select() {
    int w = gfx_xsize();
    int btn_w = 300;
    int btn_h = 40;
    int x = (w - btn_w) / 2;

    gfx_color(0, 0, 0);
    
    if (current_mode == MODE_CHOICE) {
        gfx_text("WELCOME TO WORD SCRAMBLE", w/2 - 150, 100, 2);
        
        gfx_color(200, 200, 200);
        gfx_fillrectangle(x, 200, btn_w, btn_h); // New Player
        gfx_fillrectangle(x, 260, btn_w, btn_h); // Old Player

        gfx_color(0, 0, 0);
        gfx_text("NEW PLAYER", x + 90, 225, 1);
        gfx_text("OLD PLAYER", x + 90, 285, 1);
    } 
    else if (current_mode == MODE_NEW) {
        gfx_text("ENTER YOUR NAME", w/2 - 100, 100, 2);
        
        // Input Box
        gfx_color(240, 240, 240);
        gfx_fillrectangle(x, 200, btn_w, btn_h);
        
        gfx_color(0, 0, 0);
        gfx_text(input_buffer, x + 10, 225, 1);
        
        // Confirm Button
        gfx_color(180, 255, 180);
        gfx_fillrectangle(x, 280, btn_w, btn_h);
        gfx_color(0, 0, 0);
        gfx_text("CONFIRM & START", x + 70, 305, 1);

        // Back button
        gfx_color(255, 200, 200);
        gfx_fillrectangle(20, 20, 100, 30);
        gfx_color(0, 0, 0);
        gfx_text("BACK", 50, 40, 1);
    } 
    else if (current_mode == MODE_OLD) {
        gfx_text("SELECT YOUR PROFILE", w/2 - 130, 80, 2);
        
        if (player_count == 0) {
            gfx_text("No existing players found.", x + 40, 200, 1);
        }

        for (int i = 0; i < player_count; i++) {
            gfx_color(220, 220, 220);
            gfx_fillrectangle(x, 150 + (i * 50), btn_w, btn_h);
            gfx_color(0, 0, 0);
            gfx_text(existing_players[i], x + 20, 150 + (i * 50) + 25, 1);
        }

        // Back button
        gfx_color(255, 200, 200);
        gfx_fillrectangle(20, 20, 100, 30);
        gfx_color(0, 0, 0);
        gfx_text("BACK", 50, 40, 1);
    }
}

GameState player_handle_click(int mx, int my) {
    int w = gfx_xsize();
    int btn_w = 300;
    int btn_h = 40;
    int x = (w - btn_w) / 2;

    if (current_mode == MODE_CHOICE) {
        if (mx >= x && mx <= x + btn_w) {
            if (my >= 200 && my <= 240) {
                input_index = 0;
                input_buffer[0] = '\0';
                current_mode = MODE_NEW;
            } else if (my >= 260 && my <= 300) {
                load_existing_players();
                current_mode = MODE_OLD;
            }
        }
    } 
    else if (current_mode == MODE_NEW) {
        // Confirm Button
        if (mx >= x && mx <= x + btn_w && my >= 280 && my <= 320) {
            if (strlen(input_buffer) > 0) {
                load_player_data(input_buffer);
                save_player_data(); // Create file immediately
                return STATE_MENU;
            }
        }
        // Back Button
        if (mx >= 20 && mx <= 120 && my >= 20 && my <= 50) {
            current_mode = MODE_CHOICE;
        }
    } 
    else if (current_mode == MODE_OLD) {
        // Check if a player name was clicked
        for (int i = 0; i < player_count; i++) {
            int py = 150 + (i * 50);
            if (mx >= x && mx <= x + btn_w && my >= py && my <= py + btn_h) {
                load_player_data(existing_players[i]);
                return STATE_MENU;
            }
        }
        // Back Button
        if (mx >= 20 && mx <= 120 && my >= 20 && my <= 50) {
            current_mode = MODE_CHOICE;
        }
    }

    return STATE_SELECT_PLAYER;
}

void player_handle_key(char c) {
    if (current_mode == MODE_NEW) {
        if (c == 8 || c == 127) { // Backspace
            if (input_index > 0) {
                input_buffer[--input_index] = '\0';
            }
        } else if (input_index < 31 && c >= 32 && c <= 126) {
            // Basic printable ASCII characters
            input_buffer[input_index++] = c;
            input_buffer[input_index] = '\0';
        }
    }
}