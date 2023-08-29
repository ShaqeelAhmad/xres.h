## xres.h

A simple stb style single header library to read xresources file.

This is mainly intended for wayland applications, since there is no theme or
colors exposed to pure wayland applications and each of them will need their
own way of getting values for something trivial like foreground and background
colors.

Look at [example.c](example.c) on how to use it.

# LICENSE

public domain http://unlicense.org/
