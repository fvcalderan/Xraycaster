/* This is the drawing_api header file for Xraycaster
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

#ifndef _WINDOW_API_H
#define _WINDOW_API_H

/* X11 headers */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/keysym.h>

/* standard headers */
#include <stdlib.h>
#include <stdint.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

/* which characters to consider */
#define ALPHABET_SIZE 256

/* X variables */
Display *dis;
int32_t screen;
Window win;
GC gc;

void _init_window(const char *title, uint16_t width, uint16_t height);
void _destroy_window();
void _clear_window();
void _flush_window();
void _draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint64_t color);
void _get_input(uint32_t *arrow_keys);

#endif
