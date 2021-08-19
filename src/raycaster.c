/* This is the raycaster source code for Xraycaster
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

#include <raycaster.h>
#include <stdio.h>

RAYCASTER new_raycaster(
        MAP *map, PLAYER *player, WALL *walls, float resolution,
        uint32_t thread_num, uint16_t scr_width, uint16_t scr_height
)
{
    /* calculate remaining values */
    uint16_t n_rays = (uint16_t)(scr_width * resolution);
    float step_angle = player->fov/n_rays;
    uint32_t max_depth = (uint32_t)(
            MAX(map->w, map->h) * MAX(map->tile_w, map->tile_h)
    );
    float stripe_scale = scr_width/n_rays;

    /* return raycaster structure with all the values */
    return (RAYCASTER){
        .map=map, .player=player, .walls=walls, .resolution=resolution,
        .thread_num=thread_num, .scr_width=scr_width, .scr_height=scr_height,
        .n_rays=n_rays, .step_angle=step_angle, .max_depth=max_depth,
        .stripe_scale = stripe_scale
    };
}

void *_thread_worker(void *ptr)
{
    /* unpack the void pointer */
    THREAD_FEED *feed = (THREAD_FEED *)ptr;
    uint32_t t = feed->id;
    RAYCASTER *rc = feed->rc;
    MAP *map = rc->map;
    PLAYER *player = rc->player;
    WALL *walls = rc->walls;

    printf("%f\n", rc->resolution);

    return NULL;
}

void cast_rays(RAYCASTER *rc)
{
    pthread_t thread_pool[rc->thread_num];

    /* create threads and pass its id and walls array to the function*/
    for (uint32_t i = 0; i < rc->thread_num; i++) {
        THREAD_FEED t = new_thread_feed(i, rc);
        THREAD_FEED *t_addr = &t;
        pthread_create( &thread_pool[i], NULL, _thread_worker, (void *)t_addr);
    }

    /* join all threads in the pool */
    for (uint32_t i = 0; i < rc->thread_num; i++)
        pthread_join(thread_pool[i], NULL);
}

WALL new_wall(float distance, COLOR color)
{
    return (WALL){.distance=distance, .color=color};
}

THREAD_FEED new_thread_feed(uint32_t id, RAYCASTER *rc)
{
    return (THREAD_FEED){.id=id, .rc=rc};
}
