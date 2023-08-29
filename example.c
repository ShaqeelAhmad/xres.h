#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdint.h>

#define XRES_CPP "cpp"
#define XRES_IMPLEMENTATION
#include "rgb.h"
#include "xres.h"

int
main(int argc, char *argv[])
{
	xres_load("./example.Xresources");

	// The default value in case xres_color or xres_get fail.
	uint8_t r = 255, g = 255, b = 255, a = 255;

	xres_color(xres_get(".foreground"), &r, &g, &b, &a);
	printf("foreground color is #%02x%02x%02x%02x\n", r, g, b, a);

	r = 0, g = 0, b = 0, a = 255;
	xres_color(xres_get(".background"), &r, &g, &b, &a);
	printf("background color is #%02x%02x%02x%02x\n", r, g, b, a);

	char *font = xres_get(".font");
	if (font == NULL)
		font = "monospace";
	printf("font is %s\n", font);

	xres_unload();
}
