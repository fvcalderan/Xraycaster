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
#include <stdio.h>

MAP new_map(
        uint8_t *the_map, uint8_t w, uint8_t h,
        uint16_t scr_width, uint16_t scr_height
)
{
    //printf("%d %d \n", the_map[w*3+3], w);
    return (MAP){
        .tiles=the_map, .w=w, .h=h,
        .tile_w=(float)scr_width/(float)w,
        .tile_h=(float)scr_height/(float)h
    };
}
