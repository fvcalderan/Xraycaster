/* This is the map source code for Xraycaster
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

#include <map.h>

MAP new_map(
        TILETYPE *map, uint8_t w, uint8_t h,
        uint16_t scr_width, uint16_t scr_height
)
{
    return (MAP){
        .tiles=map, .w=w, .h=h,
        .tile_w=scr_width/w,
        .tile_h=scr_height/h
    };
}

/* returns the tile type at tile.x tile.y coords */
TILETYPE val_in(MAP map, TILE tile)
{
    return map.tiles[tile.y * map.w + tile.x];
}

/* convert world coordinates to tile coordinates */
TILE world2tile(MAP map, TRANSFORM t)
{
    return (TILE){
        .x = t.x/map.tile_w,
        .y = t.y/map.tile_h
    };
}

/* convert tile coordinates to world coordinates */
TRANSFORM tile2world(MAP map, TILE tile)
{
    return (TRANSFORM){
        .x = (tile.x + 0.5f) * map.tile_w,
        .y = (tile.y + 0.5f) * map.tile_h,
        .r = 0.0f
    };
}
