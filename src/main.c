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
RAYCASTER raycaster;

/* important variables for the game loop */
INPUT key_presses[KEY_BUF_LEN] = {0};
TRANSFORM next_pos = {.x=0, .y=0, .r=0};
DIRECTION dir = IDLE;
WALL *walls;

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
    if (val_in(map, world2tile(map, next_pos)) == FLOOR)
        move(&player, next_pos);

    /* check for turning inputs */
    if (key_presses['q']) turn(&player, LEFT);
    if (key_presses['e']) turn(&player, RIGHT);
}

void draw()
{
    /* draw the floor and the sky/ceiling */
    RECT sky_rect   = new_rect(0, 0, SCR_WIDTH, SCR_HEIGHT/2);
    RECT floor_rect = new_rect(0, SCR_HEIGHT/2, SCR_WIDTH, SCR_HEIGHT/2);
    draw_rect(sky_rect,   new_color(SKY_COLOR)  );
    draw_rect(floor_rect, new_color(FLOOR_COLOR));

    /* draw the player */
    RECT rect = new_rect(player.t.x, player.t.y, 50, 50);
    draw_rect(rect, new_color(WALL1_COLOR));
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

    /* allocate the walls array */
    walls = malloc((uint32_t)(SCR_WIDTH * RESOLUTION) * sizeof(WALL));

    /* setup the raycaster */
    raycaster = new_raycaster(
        &map, &player, walls, RESOLUTION, THREAD_NUM, SCR_WIDTH, SCR_HEIGHT
    );

    /* run tests */
    run_tests();
}

void game_loop()
{
    while(1) {
        get_input(key_presses);
        process_input();
        clear_window();
        cast_rays(&raycaster);
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
