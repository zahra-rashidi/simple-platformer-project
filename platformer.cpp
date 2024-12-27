#include "raylib.h"

#include "globals.h"
#include "level.h"
#include "player.h"
#include "graphics.h"
#include "assets.h"
#include "utilities.h"

void update_game() {
    game_frame++;

    switch (game_state) {
        case MENU_STATE:
            if (IsKeyPressed(KEY_ENTER)) {
                game_state = GAME_STATE;
                load_level(0); // Start the game at the first level
            }
            break;

        case GAME_STATE:
            if (IsKeyPressed(KEY_SPACE)) {
                game_state = PAUSE_STATE; // Pause the game
            }

            // Handle player movement
            if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
                move_player_horizontally(MOVEMENT_SPEED);
            }
            if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
                move_player_horizontally(-MOVEMENT_SPEED);
            }

            // Jumping logic
            is_player_on_ground = is_colliding({player_pos.x, player_pos.y + 0.1f}, WALL);
            if ((IsKeyDown(KEY_UP) || IsKeyDown(KEY_W) || IsKeyDown(KEY_W)) && is_player_on_ground) {
                player_y_velocity = -JUMP_STRENGTH;
            }

            update_player();
            break;

        case PAUSE_STATE:
            if (IsKeyPressed(KEY_SPACE)) {
                game_state = GAME_STATE; // Resume the game
            }
            break;

        case GAME_OVER_STATE:
            if (IsKeyPressed(KEY_ENTER)) {
                game_state = MENU_STATE; // Return to the menu
            }
            break;

        case VICTORY_STATE:
            if (IsKeyPressed(KEY_ENTER)) {
                game_state = MENU_STATE; // Return to the menu
            }
            break;
    }
}

void draw_game() {
    switch (game_state) {
        case MENU_STATE:
            ClearBackground(BLACK);
            draw_menu();
            break;

        case GAME_STATE:
            ClearBackground(BLACK);
            draw_level();
            draw_game_overlay();
            break;

        case PAUSE_STATE:
            ClearBackground(BLACK);
            draw_pause_menu();
            break;

        case GAME_OVER_STATE:
            ClearBackground(BLACK);
            draw_game_overlay();
            break;

        case VICTORY_STATE:
            draw_victory_menu();
            break;
    }
}

int main() {
    InitWindow(1024, 480, "Platformer");
    SetTargetFPS(60);

    // Load assets
    load_fonts();
    load_images();
    load_sounds();
    load_level();

    while (!WindowShouldClose()) {
        BeginDrawing();

        update_game();
        draw_game();

        EndDrawing();
    }

    // Unload assets
    unload_level();
    unload_sounds();
    unload_images();
    unload_fonts();

    CloseAudioDevice();
    CloseWindow();

    return 0;
}

