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

TRANSFORM next_move(PLAYER *player, DIRECTION dir)
{
    TRANSFORM new_pos = {.x=0, .y=0, .r=0};
    uint8_t button_presses = 0;

    /* calculate direction */
    if (dir & FORWARD) {
        new_pos.x -= sin(player->t.r) * player->spd;
        new_pos.y += cos(player->t.r) * player->spd;
        button_presses++;
    }
    else if (dir & BACKWARD) {
        new_pos.x += sin(player->t.r) * player->spd;
        new_pos.y -= cos(player->t.r) * player->spd;
        button_presses++;
    }
    if (dir & LEFT) {
        new_pos.x -= sin(player->t.r - PI/2) * player->spd;
        new_pos.y += cos(player->t.r - PI/2) * player->spd;
        button_presses++;
    }
    else if (dir & RIGHT) {
        new_pos.x -= sin(player->t.r + PI/2) * player->spd;
        new_pos.y += cos(player->t.r + PI/2) * player->spd;
        button_presses++;
    }

    /* normalize direction vector (if there's a direction to go) */
    if (button_presses > 1) {
        new_pos.x *= ISR2;
        new_pos.y *= ISR2;
    }

    /* add to the previous position (multiplied by the player's velocity) */
    new_pos.x = player->t.x + new_pos.x;
    new_pos.y = player->t.y + new_pos.y;

    /* return new position */
    return new_pos;
}

void move(PLAYER *player, TRANSFORM position)
{
    player->t.x = position.x;
    player->t.y = position.y;
}
