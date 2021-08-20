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

/* this will be ran by the created threads */
void *_thread_worker(void *ptr)
{
    /* unpack the void pointer */
    THREAD_FEED *feed = (THREAD_FEED *)ptr;
    uint32_t t = feed->id;
    RAYCASTER *rc = feed->rc;
    MAP *map = rc->map;
    PLAYER *player = rc->player;
    WALL *walls = rc->walls;

    /* variables for the raycasting procedure */
    float angle = player->t.r + player->fov * ((float)t/rc->thread_num - 0.5);
    uint32_t count = 0;
    /* these will be initialized inside the for loops */
    float target_x, target_y;
    TILE m_pos;
    uint8_t place_hit;
    uint32_t index;

    for (uint16_t ray = 0; ray < rc->n_rays/rc->thread_num; ray++) {
        for (uint32_t depth = 0; depth < rc->max_depth; depth++) {
            /* shoot ray */
            target_x = player->t.x - sin(angle) * depth;
            target_y = player->t.y + cos(angle) * depth;

            /* convert targets world position to tile position */
            m_pos = world2tile(map, (TRANSFORM){.x=target_x, .y=target_y});

            /* if a ray hits a wall, add new wall to walls array */
            place_hit = val_in(map, m_pos);
            if (place_hit) {
                index = (uint32_t)(count + t * rc->n_rays/rc->thread_num);
                walls[index] = (WALL){
                    .distance = depth * cos(player->t.r - angle) + 0.0001,
                    .color_index = place_hit
                };
                break;
            }
        }
        count++;
        angle += rc->step_angle;
    }
    free(feed);
    return NULL;
}

void cast_rays(RAYCASTER *rc)
{
    pthread_t thread_pool[rc->thread_num];
    THREAD_FEED *t;

    /* create threads and pass its id and walls array to the function*/
    for (uint32_t i = 0; i < rc->thread_num; i++) {
        t = malloc(sizeof(THREAD_FEED));
        t->id = i;
        t->rc = rc;
        pthread_create(&thread_pool[i], NULL, _thread_worker, t);
    }

    /* join all threads in the pool */
    for (uint32_t i = 0; i < rc->thread_num; i++)
        pthread_join(thread_pool[i], NULL);
}

WALL new_wall(float distance, int32_t color_index)
{
    return (WALL){.distance=distance, .color_index=color_index};
}

THREAD_FEED new_thread_feed(uint32_t id, RAYCASTER *rc)
{
    return (THREAD_FEED){.id=id, .rc=rc};
}
