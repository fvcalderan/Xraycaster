# Xraycaster
A X11 Raycaster, because OpenGL is bloat!

![image](https://github.com/fvcalderan/Xraycaster/blob/main/images/Xraycaster.png?raw=true)

## Features

Basically none, but here you go:

- Made in C
- Multithread support
- Simple configuration file

## Dependencies

The only dependency is `X11`. The other things, like `pthread` and `math`
should be inside any desktop Linux distribution.

## Build from source

`make` inside the root folder. The binary `Xraycaster` will be built inside the
`bin` folder.

## Default controls

```
w : walk forward
s : walk backwards
a : strafe left
d : strafe right
q : turn left
e : turn right
b : quit game
```

## Change the game settings

Edit `include/config.h` and recompile the program with `make clean && make`.

## How is Xraycaster structured?

![image](https://github.com/fvcalderan/Xraycaster/blob/main/images/UML.png?raw=true)

## Janky stuff

- The movement is awful, since I used basic `X11` keyboard input functions.
This makes continuous inputs work like when typing (first key press is instant,
then there's a delay, and then comes the repetitions). To further worsen the
situation, the movement is not normalized at all.
- There is no double buffer here, so sometimes the walls flicker.

## Future plans
- Since the only module that talks to `X11` is `<window_api.h>`, a nice little
project is to make a version of `Xraycaster` for Windows, using the `windows.h`
library. This is extremely cursed, but cool regardless.
- Fix the janky stuff.

## License (GPL v3.0)
```
Copyright (C) 2021 Felipe V. Calderan <fvcalderan@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
