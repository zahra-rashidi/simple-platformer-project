#ifndef PLAYER_H
#define PLAYER_H

#include "globals.h"

void spawn_player() {
    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            char cell = current_level.data[row * current_level.columns + column];
            if (cell == PLAYER) {
                player_pos.x = static_cast<float>(column);
                player_pos.y = static_cast<float>(row);
                return;
            }
        }
    }
}

void move_player_horizontally(float delta) {
    float next_x = player_pos.x + delta;
    if (!is_colliding({next_x, player_pos.y}, WALL)) {
        player_pos.x = next_x;
    } else {
        player_pos.x = roundf(player_pos.x);
    }
}

void update_player() {
    player_pos.y += player_y_velocity;
    player_y_velocity += GRAVITY_FORCE;

    is_player_on_ground = is_colliding({ player_pos.x, player_pos.y + 0.1f }, WALL);
    if (is_player_on_ground) {
        player_y_velocity = 0;
        player_pos.y = roundf(player_pos.y);
    }

    if (is_colliding(player_pos, ENEMY)) {
        get_collider(player_pos, ENEMY) = ' ';
        player_score -= 50;
        if (player_score < 0) player_score = 0;
        PlaySound(enemy_sound);
    } else if (is_colliding(player_pos, ENEMY_2)) {
        get_collider(player_pos, ENEMY_2) = ' ';
        player_score -= 100;
        if (player_score < 0) player_score = 0;
        PlaySound(enemy_2_sound);
    } else if (is_colliding(player_pos, COIN)) {
        get_collider(player_pos, COIN) = ' ';
        player_score += 10;
        PlaySound(coin_sound);
    } else if (is_colliding(player_pos, GEM)) {
        get_collider(player_pos, GEM) = ' ';
        player_score += 100;
        PlaySound(gem_sound);
    } else if (is_colliding(player_pos, FLOWER)) {
        get_collider(player_pos, FLOWER) = ' ';
        player_score += 50;
        PlaySound(flower_sound);
    }
    if (is_colliding(player_pos, EXIT)) {
        load_level(1);
        PlaySound(exit_sound);
    }
}

#endif // PLAYER_H
