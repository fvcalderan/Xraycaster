/* This is the datatypes source code for Xraycaster
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

#include <datatypes.h>


COLOR new_color_hex(uint64_t color)
{
    return (COLOR){.hex=color};
}

COLOR new_color_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    return (COLOR){.r=r, .g=g, .b=b};
}

TILETYPE new_tiletype(uint8_t tiletype)
{
    return (TILETYPE)tiletype;
}

RECT new_rect(int32_t x, int32_t y, int32_t w, int32_t h)
{
    return (RECT){.x=x, .y=y, .w=w, .h=h};
}

TILE new_tile(int32_t x, int32_t y)
{
    return (TILE){.x=x, .y=y};
}

TRANSFORM new_transform(float x, float y, float r)
{
    return (TRANSFORM){.x=x, .y=y, .r=r};
}

