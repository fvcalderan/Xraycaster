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

#include "main.h"

int32_t main (int argc, char **argv)
{

    init_window("Xraycaster", SCR_WIDTH, SCR_HEIGHT);

    uint32_t arrow_keys[4] = {0};
    int x = 0;
    int y = 0;
    while(1) {                      /* keeps checking for events */
        event_loop(arrow_keys);
        if (arrow_keys[0]) { y -= 10; }
        if (arrow_keys[1]) { y += 10; }
        if (arrow_keys[2]) { x -= 10; }
        if (arrow_keys[3]) { x += 10; }
        Rect2 rect = {.x = x, .y = y, .width = 100, .height = 150};
        clear_window();
        draw_rect(rect, RGB(0,255,0));
        flush_window();
    }
    return 0;
}
