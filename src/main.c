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

/* important entities */
PLAYER player;
MAP map;

/* important variables for the game loop */
INPUT key_presses[KEY_BUF_LEN] = {0};
TRANSFORM next_pos = {.x=0, .y=0, .r=0};
DIRECTION dir = IDLE;

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
    printf("plr transform: (%f %f %f)\n", player.t.x, player.t.y, player.t.r);

    printf("\nNEXT MOVE\n");
    printf("%lf\n", next_move(&player, IDLE).x);
    printf("%lf\n", next_move(&player, IDLE).y);
}

void game_ready()
{
    /* setup the map */
    map = new_map(THE_MAP, MAP_WIDTH, MAP_HEIGHT, SCR_WIDTH, SCR_HEIGHT);

    /* setup the player and start position*/
    TRANSFORM start_pos = tile2world(map, (TILE){.x=PLR_POS_X, .y=PLR_POS_Y});
    player = new_player(
        start_pos.x, start_pos.y, PLR_ROT, PLR_SPEED, PLR_RSPEED, PLR_FOV
    );

    /* the immediate next position is the starting position */
    memcpy(&next_pos, &player.t, sizeof(TRANSFORM));

    /* run tests */
    run_tests();
}

void game_loop()
{
    while(1) {
        /* reset previous input direction */
        dir = IDLE;

        /* check for inputs */
        get_input(key_presses);
        if (key_presses['w']) { dir |= FORWARD;  }
        if (key_presses['s']) { dir |= BACKWARD; }
        if (key_presses['a']) { dir |= LEFT;     }
        if (key_presses['d']) { dir |= RIGHT;    }

        /* compute collision for the next move. If it's a valid move, move. */
        next_pos = next_move(&player, dir);
        if (val_in(map, world2tile(map, next_pos)) == 0) {
            move(&player, next_pos);
        }

        /* draw the player */
        RECT rect = new_rect(player.t.x, player.t.y, 50, 50);
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
