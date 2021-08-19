/* This is the raycaster header file for Xraycaster
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

#ifndef _RAYCASTER_H
#define _RAYCASTER_H

/* standard headers */
#include <stdint.h>
#include <math.h>
#include <pthread.h>

/* Xraycaster headers */
#include <map.h>
#include <player.h>
#include <datatypes.h>

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

typedef struct {
    float distance;
    int32_t color_index;
} WALL;

typedef struct {
    /* received as parameters */
    MAP *map;
    PLAYER *player;
    WALL *walls;
    float resolution;       // how detailed will be the pseudo-3D walls?
    uint32_t thread_num;
    uint16_t scr_width;
    uint16_t scr_height;
    /* calculated with the above values */
    uint16_t n_rays;        // number of rays to be cast
    float step_angle;       // how many rads the rays will be apart
    uint32_t max_depth;     // how far the rays can reach
    float stripe_scale;     // how much of the screen should a ray occupy?
} RAYCASTER;

typedef struct {
    uint32_t id;
    RAYCASTER *rc;
} THREAD_FEED;

RAYCASTER new_raycaster(
        MAP *map, PLAYER *player, WALL *walls, float resolution,
        uint32_t thread_num, uint16_t scr_width, uint16_t scr_height
);

void *_thread_worker(void *ptr);

void cast_rays(RAYCASTER *rc);

WALL new_wall(float distance, int32_t color_index);

THREAD_FEED new_thread_feed(uint32_t id, RAYCASTER *rc);

#endif
