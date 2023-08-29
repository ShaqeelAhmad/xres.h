// generates a list of struct entries that contain the name and the colors from
// the rgb.txt file.
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdint.h>

uint8_t
parse_color(char **s)
{
	char *endptr = *s;
	unsigned long c = strtoul(*s, &endptr, 10);
	if (endptr == *s || c > 255) {
		fprintf(stderr, "invalid digit\n");
		exit(1);
	}
	*s = endptr;
	while (isspace(**s))
		*s += 1;
	return (uint8_t)c;
}

int
main(void)
{
	char *file = "rgb.txt";
	char *out = "rgb.h";
	FILE *f = fopen(file, "r");
	if (f == NULL) {
		perror(file);
		exit(1);
	}
	FILE *w = fopen(out, "w");
	if (w == NULL) {
		perror(out);
		exit(1);
	}
	fprintf(w, "#include <stdint.h>\n");
	fprintf(w, "struct { char *name; uint8_t r; uint8_t g; uint8_t b;} xres_colors[] = {\n");

	char *line = NULL;
	size_t linelen = 0;
	while (getline(&line, &linelen, f) >= 0) {
		char *s = line;
		char *endptr = NULL;

		while (isspace(*s))
			s++;
		if (*s == '#' || *s == '\0')
			continue;

		uint8_t r = parse_color(&s);
		uint8_t g = parse_color(&s);
		uint8_t b = parse_color(&s);

		if (*s == '\0') {
			fprintf(stderr, "invalid name\n");
			exit(1);
		}

		for (fputs("{\"", w); *s != '\n' && *s != '\0'; s++)
			fputc(*s, w);
		fprintf(w, "\", %u, %u, %u},\n", r, g, b);
	}
	fprintf(w, "};\n");
	fprintf(w, "#define xres_colors xres_colors\n");

	fclose(f);
	fclose(w);
}
