/* This is the player header file for Xraycaster
 * Copyright (C) 2021 Felipe V. Calderan <fvcalderan@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

#ifndef _PLAYER_H
#define _PLAYER_H

/* standard headers */
#include <stdint.h>
#include <math.h>

/* Xraycaster headers */
#include <datatypes.h>

/* Direction bits */
#define IDLE     0b0000
#define FORWARD  0b0001
#define BACKWARD 0b0010
#define LEFT     0b0100
#define RIGHT    0b1000

/* inverse sqrt of 2 */
#define ISR2     0.707107

typedef uint8_t DIRECTION;

typedef struct {
    TRANSFORM t;    // position & rotation
    float spd;      // walk speed
    float rspd;     // turn speed
    float fov;      // field of view
} PLAYER;

PLAYER new_player(float x, float y, float r, float spd, float rspd, float fov);
TRANSFORM next_move(PLAYER *player, DIRECTION dir);
void move(PLAYER *player, TRANSFORM position);
void turn(PLAYER *player, DIRECTION dir);

#endif
