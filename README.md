# DREAMVIEWER
Made in C using Raylib, DREAMVIEWER is a WIP custom ASCII rendering engine built on DDA raycasting.

##### compile:
```
gcc src/*.c -Iinclude -o build/dreamviewer \
    $(pkg-config --cflags --libs raylib) -lm
```