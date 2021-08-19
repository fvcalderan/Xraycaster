/* This is the map header file for Xraycaster
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

#ifndef _MAP_H
#define _MAP_H

/* standard headers */
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/* Xraycaster headers */
#include <datatypes.h>

#define FLOOR 0

typedef struct {
    TILETYPE *tiles;    // map array
    uint8_t w;          // width
    uint8_t h;          // height
    float tile_w;       // tile width
    float tile_h;       // tile height
} MAP;

MAP new_map(
        uint8_t *map, uint8_t w, uint8_t h,
        uint16_t scr_width, uint16_t scr_height
);

TILETYPE val_in(MAP map, TILE tile);
TILE world2tile(MAP map, TRANSFORM t);
TRANSFORM tile2world(MAP map, TILE tile);

#endif
