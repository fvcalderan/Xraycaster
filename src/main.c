/* This is the main source code for Xraycaster
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

#include <main.h>

Entity player;

void game_ready()
{
    player.x = PLAYER_START_POS_X;
    player.y = PLAYER_START_POS_Y;
    player.r = PLAYER_START_ROT;
}

void game_loop()
{
    uint32_t key_presses[256] = {0};
    int x = 0;
    int y = 0;
    while(1) {                      /* keeps checking for events */
        event_loop(key_presses);
        if (key_presses[119]) { y -= 10; }
        if (key_presses[115]) { y += 10; }
        if (key_presses[97])  { x -= 10; }
        if (key_presses[100]) { x += 10; }
        Rect2 rect = {.x = x, .y = y, .width = 100, .height = 150};
        clear_window();
        draw_rect(rect, 0xadd9e5);
        flush_window();
    }
}

int32_t main (int argc, char **argv)
{
    init_window("Xraycaster", SCR_WIDTH, SCR_HEIGHT);
    game_ready();
    game_loop();
    destroy_window();
}
