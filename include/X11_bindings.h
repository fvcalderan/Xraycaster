/* This is the X11 bindings header file for Xraycaster
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

#ifndef _WINDOW_MANAGER_H
#define _WINDOW_MANAGER_H

#include <global.h>
#include <primitives.h>

void init_window(const char *title, uint16_t width, uint16_t height);
void destroy_window();
void clear_window();
void flush_window();
void draw_rect(Rect2 rect, uint64_t color);
char get_key();
void event_loop(uint32_t *arrow_keys);

#endif
