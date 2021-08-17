/* This is the utils source code for Xraycaster
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

#include <utils.h>

uint64_t RGB_vector(uint8_t r, uint8_t g, uint8_t b)
{
    return b + (g<<8) + (r<<16);
}

uint64_t RGB_hex(const char *hex)
{
    uint64_t decimal = 0, val = 0, len;
    uint8_t i;

    len = strlen(hex);
    len--;

    for(i=0; hex[i]!='\0'; i++) {
        if(hex[i]>='0' && hex[i]<='9')      { val = hex[i] - 48;      }
        else if(hex[i]>='a' && hex[i]<='f') { val = hex[i] - 97 + 10; }
        else if(hex[i]>='A' && hex[i]<='F') { val = hex[i] - 65 + 10; }
        decimal += val * pow(16, len);
        len--;
    }

    return decimal;
}
