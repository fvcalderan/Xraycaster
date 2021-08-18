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

PLAYER player;
MAP map;

void game_ready()
{
    /* setup the player */
    player = new_player(
        PLR_POS_X, PLR_POS_Y, PLR_ROT, PLR_SPEED, PLR_RSPEED, PLR_FOV
    );
    /* setup the map */
    map = new_map(THE_MAP, MAP_WIDTH, MAP_HEIGHT, SCR_WIDTH, SCR_HEIGHT);
}

void game_loop()
{
    INPUT key_presses[KEY_BUF_LEN] = {0};
    int x = 0;
    int y = 0;
    while(1) {                      /* keeps checking for events */
        get_input(key_presses);
        if (key_presses['w']) { y -= 10; }
        if (key_presses['s']) { y += 10; }
        if (key_presses['a']) { x -= 10; }
        if (key_presses['d']) { x += 10; }
        RECT rect = new_rect(x, y, 100, 150);
        clear_window();
        draw_rect(rect, new_color(0xadd9e5));
        flush_window();
    }
}

int32_t main ()
{
    init_window("Xraycaster", SCR_WIDTH, SCR_HEIGHT);
    game_ready();
    game_loop();
    destroy_window();
}
