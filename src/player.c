/* This is the player source code for Xraycaster
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

#include <player.h>

PLAYER new_player(float x, float y, float r, float spd, float rspd, float fov)
{
    return (PLAYER){
        .t=(TRANSFORM){.x=x, .y=y, .r=r}, .spd=spd, .rspd=rspd, .fov=fov
    };
}
