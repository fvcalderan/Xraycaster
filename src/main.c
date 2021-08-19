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
RAYCASTER rc;

/* important variables for the game loop */
INPUT key_presses[KEY_BUF_LEN] = {0};
TRANSFORM next_pos = {.x=0, .y=0, .r=0};
DIRECTION dir = IDLE;
WALL *walls;

void process_input()
{
    /* reset previous input direction */
    dir = IDLE;

    /* check for walking inputs */
    if (key_presses['w']) dir |= FORWARD;
    if (key_presses['s']) dir |= BACKWARD;
    if (key_presses['a']) dir |= LEFT;
    if (key_presses['d']) dir |= RIGHT;

    /* compute collision for the next move. If it's a valid move, move. */
    next_pos = next_move(&player, dir);
    if (val_in(&map, world2tile(&map, next_pos)) == FLOOR)
        move(&player, &next_pos);

    /* check for turning inputs */
    if (key_presses['q']) turn(&player, LEFT);
    if (key_presses['e']) turn(&player, RIGHT);
}

void draw()
{
    /* draw the floor and the sky/ceiling */
    RECT sky_rect   = new_rect(0, 0, SCR_WIDTH, SCR_HEIGHT/2);
    RECT floor_rect = new_rect(0, SCR_HEIGHT/2, SCR_WIDTH, SCR_HEIGHT/2);
    draw_rect(&sky_rect,   new_color_hex(COLORS[SKY_COLOR])  );
    draw_rect(&floor_rect, new_color_hex(COLORS[FLOOR_COLOR]));

    /* draw the pseudo-3D walls */
    uint32_t count = 0;
    for (uint32_t i = 0; i < SCR_WIDTH * RESOLUTION; i++) {
        /* wall rectangle */
        RECT wall_rect = new_rect(
            count*rc.stripe_scale,
            SCR_HEIGHT/2 - WALL_HEIGHT/(2*walls[i].distance),
            rc.stripe_scale,
            WALL_HEIGHT/walls[i].distance
        );

        /* color with shadow decay */
        COLOR wall_color = new_color_hex(COLORS[walls[i].color_index]);
        wall_color.r /= 1 + pow(walls[i].distance, 2)/SHADOW_DECAY;
        wall_color.g /= 1 + pow(walls[i].distance, 2)/SHADOW_DECAY;
        wall_color.b /= 1 + pow(walls[i].distance, 2)/SHADOW_DECAY;

        /* draw the rectangle with the correct color */
        draw_rect(&wall_rect, wall_color);
        count++;
    }
}

void game_ready()
{
    /* setup the map */
    map = new_map(THE_MAP, MAP_WIDTH, MAP_HEIGHT, SCR_WIDTH, SCR_HEIGHT);

    /* setup the player and start position*/
    TRANSFORM start_pos = tile2world(&map, (TILE){.x=PLR_POS_X, .y=PLR_POS_Y});
    player = new_player(
        start_pos.x, start_pos.y, PLR_ROT, PLR_SPEED, PLR_RSPEED, PLR_FOV
    );

    /* the immediate next position is the starting position */
    memcpy(&next_pos, &player.t, sizeof(TRANSFORM));

    /* allocate the walls array */
    walls = malloc((uint32_t)(SCR_WIDTH * RESOLUTION) * sizeof(WALL));

    /* setup the raycasterc */
    rc = new_raycaster(
        &map, &player, walls, RESOLUTION, THREAD_NUM, SCR_WIDTH, SCR_HEIGHT
    );
}

void game_loop()
{
    while(1) {
        get_input(key_presses);
        process_input();
        cast_rays(&rc);
        draw();
        flush_window();
    }
}

void game_cleanup()
{
    free(walls);
}

int32_t main()
{
    init_window("Xraycaster", SCR_WIDTH, SCR_HEIGHT);
    game_ready();
    game_loop();
    game_cleanup();
    destroy_window();
}
