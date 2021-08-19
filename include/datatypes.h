/* This is the datatypes header file for Xraycaster
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

#ifndef _DATATYPES_H
#define _DATATYPES_H

/* standard headers */
#include <stdint.h>

#define PI 3.1415926436

typedef union {
    struct {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    };
    uint64_t hex;
} COLOR;

typedef uint8_t TILETYPE;

typedef struct {
    int32_t x;      // x screen position
    int32_t y;      // y screen position
    int32_t w;      // rectangle's width
    int32_t h;      // rectangle's height
} RECT;

typedef struct {
    int32_t x;      // x tile position
    int32_t y;      // y tile position
} TILE;

typedef struct {
    float x;        // x world position
    float y;        // y world position
    float r;        // rotation (rad)
} TRANSFORM;

COLOR new_color_hex(uint64_t color);
COLOR new_color_rgb(uint8_t r, uint8_t g, uint8_t b);
TILETYPE new_tiletype(uint8_t tiletype);
RECT new_rect(int32_t x, int32_t y, int32_t w, int32_t h);
TILE new_tile(int32_t x, int32_t y);
TRANSFORM new_transform(float x, float y, float r);

#endif
