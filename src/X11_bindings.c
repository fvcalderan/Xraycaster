/* This is the X11 bindings source code for Xraycaster
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

#include <X11_bindings.h>

void init_window(const char *title, uint16_t width, uint16_t height)
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
    XSetStandardProperties(dis, win, title, "icon", None, NULL,0, NULL);
    XSelectInput(
            dis, win, ExposureMask|ButtonPressMask|KeyPressMask|KeyReleaseMask
    );
    XSetBackground(dis, gc, black);
    XSetForeground(dis, gc, white);
    XClearWindow(dis, win);
    XMapRaised(dis, win);
}

void destroy_window()
{
    XFreeGC(dis, gc);
    XDestroyWindow(dis, win);
    XCloseDisplay(dis);
    exit(0);
}

void clear_window()
{
    XClearWindow(dis, win);
}

void flush_window()
{
    XFlush(dis);
}

void draw_rect(Rect2 rect, uint64_t color)
{
    XSetForeground(dis, gc, color);
    XFillRectangle(dis, win, gc, rect.x, rect.y, rect.width, rect.height);
}

void event_loop(uint32_t *key_presses)
{
    XEvent event;
    KeySym keysym;
    XNextEvent(dis, &event);

    switch (event.type) {
        case KeyPress:
            keysym = XLookupKeysym(&event.xkey, 0);
            key_presses[keysym] = 1;
            break;
        case KeyRelease:
            keysym = XLookupKeysym(&event.xkey, 0);
            key_presses[keysym] = 0;
            break;
    }
}
