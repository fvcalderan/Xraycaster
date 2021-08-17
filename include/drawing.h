/* This is the drawing header file for Xraycaster
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

#ifndef _DRAWING_H
#define _DRWAING_H

/* standard headers */
#include <stdint.h>

/* Xraycaster headers */
#include <datatypes.h>
#include <window_api.h>

void draw_rect(RECT rect, COLOR color);

#endif
