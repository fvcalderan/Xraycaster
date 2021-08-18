/* This is the config header file for Xraycaster
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

#ifndef _CONFIG_H
#define _CONFIG_H

/* Screen */
#define SCR_WIDTH  480
#define SCR_HEIGHT 480

/* Colors */
#define SKY_COLOR   0xadd9e5
#define FLOOR_COLOR 0x333333
#define WALL1_COLOR 0xffaaaa
#define WALL2_COLOR 0xaaffaa
#define WALL3_COLOR 0xaaaaff

/* Player */
#define PLR_POS_X   1
#define PLR_POS_Y   1
#define PLR_ROT     0
#define PLR_SPEED   10
#define PLR_RSPEED  0.104719
#define PLR_FOV     1.047197

/* Map */
#define MAP_WIDTH  10
#define MAP_HEIGHT 10
uint8_t THE_MAP[MAP_WIDTH*MAP_HEIGHT] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 2, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

#endif
