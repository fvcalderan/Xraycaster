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
#include <stdio.h>

PLAYER player;
MAP map;

void run_tests()
{
    printf("\nGET TILE VALUE\n");
    printf("%d\n", val_in(map, (TILE){.x=4, .y=3}));
    printf("%d\n", val_in(map, (TILE){.x=3, .y=4}));

    printf("\nTILE AND WORLD CONVERSIONS\n");
    TILE tile1 = world2tile(map, (TRANSFORM){.x=72, .y=120, .r=0});
    TRANSFORM t1 = tile2world(map, (TILE){.x=1, .y=2});
    printf("TILE: (%d, %d)\n", tile1.x, tile1.y);
    printf("TRANSFORM: (%f, %f, %f)\n", t1.x, t1.y, t1.r);

    printf("\nPLAYER START POSITION\n");
    printf("Player transform: (%f %f %f)", player.t.x, player.t.y, player.t.r);
}


void game_ready()
{
    /* setup the map */
    map = new_map(THE_MAP, MAP_WIDTH, MAP_HEIGHT, SCR_WIDTH, SCR_HEIGHT);

    /* setup the player */
    TRANSFORM start_pos = tile2world(map, (TILE){.x=PLR_POS_X, .y=PLR_POS_Y});
    player = new_player(
        start_pos.x, start_pos.y, start_pos.r, PLR_SPEED, PLR_RSPEED, PLR_FOV
    );

    /* run tests */
    run_tests();
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
