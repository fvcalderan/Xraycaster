/* This is the window_api source code for Xraycaster
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

#include <window_api.h>

void _init_window(const char *title, uint16_t width, uint16_t height)
{
    uint64_t black, white;
    dis    = XOpenDisplay((char *)0);
    screen = DefaultScreen(dis);
    black  = BlackPixel(dis, screen),
    white  = WhitePixel(dis, screen);
    win    = XCreateSimpleWindow(
                dis, DefaultRootWindow(dis), 0, 0,
                width, height, 5, white, black
            );
    gc     = XCreateGC(dis, win, 0,0);
    XSetStandardProperties(dis, win, title, "icon", None, NULL, 0, NULL);
    XSelectInput(
            dis, win, ExposureMask|ButtonPressMask|KeyPressMask|KeyReleaseMask
    );
    XSetBackground(dis, gc, black);
    XSetForeground(dis, gc, white);
    XClearWindow(dis, win);
    XMapRaised(dis, win);
}

void _destroy_window()
{
    XFreeGC(dis, gc);
    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    exit(0);
}

void _clear_window()
{
    XClearWindow(dis, win);
}

void _flush_window()
{
    XFlush(dis);
}

void _draw_rect(int32_t x, int32_t y, int32_t w, int32_t h, uint64_t color)
{
    XSetForeground(dis, gc, color);
    XFillRectangle(dis, win, gc, x, y, w, h);
}

void _get_input(uint32_t *key_presses)
{
    XEvent event;
    KeySym keysym;
    XNextEvent(dis, &event);

    switch (event.type) {
        case KeyPress:
            keysym = XLookupKeysym(&event.xkey, 0);
            key_presses[MIN(keysym, ALPHABET_SIZE)] = 1;
            break;
        case KeyRelease:
            keysym = XLookupKeysym(&event.xkey, 0);
            key_presses[MIN(keysym, ALPHABET_SIZE)] = 0;
            break;
    }
}
