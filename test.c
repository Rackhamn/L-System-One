#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define WIDTH		2048
#define HEIGHT		2048
#define MAX_LEN		1000000
#define STACK_SIZE	100000
#define MAX_DEPTH	10000

typedef struct {
	double x, y;
	double angle;
	int depth;
} Turtle;

typedef struct {
	unsigned char r, g, b;
} Pixel;

Pixel image[HEIGHT][WIDTH];

void set_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
		image[y][x].r = r;
		image[y][x].g = g;
		image[y][x].b = b;
	}
}

void get_branch_color(int depth, int max_depth, unsigned char * r, unsigned char * g, unsigned char * b) {
	double t = max_depth > 0 ? (double)depth / max_depth : 0;
	double it = 1.0 - t;
	*r = (unsigned char)(it * 139 + t * 0);
	*g = (unsigned char)(it * 69 + t * 128);
	*b = (unsigned char)(it * 19 + t * 0);
}

void draw_line(double x0, double y0, double x1, double y1, int depth, int max_depth) {
	int steps = (int)hypot(x1 - x0, y1 - y0);
	unsigned char r, g, b;
	get_branch_color(depth, max_depth, &r, &g, &b);
	for (int i = 0; i <= steps; ++i) {
		double t = (double)i / steps;
		int x = (int)(x0 + t * (x1 - x0));
		int y = (int)(y0 + t * (y1 - y0));
		set_pixel(x, y, r, g, b);
	}
}

void draw_dot(int cx, int cy, int radius, unsigned char r, unsigned char g, unsigned char b) {
	int radius2 = radius * radius;
	for(int dy = -radius; dy <= radius; ++dy) {
		for(int dx = -radius; dx <= radius; ++dx) {
			int x = cx + dx;
			int y = cy + dy;
			if(dx*dx + dy*dy <= radius2) {
				set_pixel(x, y, r, g, b);
			}
		}
	}
}

char* apply_rules(const char *input, char * rule) {
	char *output = malloc(MAX_LEN);
	output[0] = '\0';

	for (size_t i = 0; input[i]; ++i) {
		if (input[i] == 'F') {
			strcat(output, rule); // "FF+[+F-X-F-F]-[-F+F+F+X]");
		} else {
			strncat(output, &input[i], 1);
		}
	}

	return output;
}

void save_ppm(const char *filename) {
	FILE *f = fopen(filename, "wb");
	fprintf(f, "P6\n%d %d\n255\n", WIDTH, HEIGHT);
	for (int y = 0; y < HEIGHT; ++y)
		for (int x = 0; x < WIDTH; ++x)
			fwrite(&image[y][x], 1, 3, f);
	fclose(f);
}

void interpret(const char *commands, double angle_deg, double step_len, int max_depth) {
	Turtle turtle = { WIDTH / 2, HEIGHT / 2, -90, 0}; // Start at bottom center, pointing up
	Turtle stack[STACK_SIZE];
	int sp = 0;

	for (size_t i = 0; commands[i]; ++i) {
		char c = commands[i];
		switch (c) {
			case 'F': {
				double rad = turtle.angle * M_PI / 180.0;
				double nx = turtle.x + cos(rad) * step_len;
				double ny = turtle.y + sin(rad) * step_len;
				draw_line(turtle.x, turtle.y, nx, ny, turtle.depth, max_depth);
				turtle.x = nx;
				turtle.y = ny;
				break;
			}
		case 'X': {
			int x = rand() % 10;
			if(x > 5) {
				draw_dot(turtle.x, turtle.y, 1, 255, 0, 0);
			} else {
				draw_dot(turtle.x, turtle.y, 1, 0, 0, 255);
			}
		}
			case '+':
				turtle.angle += angle_deg;
				break;
			case '-':
				turtle.angle -= angle_deg;
				break;
			case '[':
				if (sp < STACK_SIZE)
					stack[sp++] = turtle;
		turtle.depth++;
				break;
			case ']':
				if (sp > 0)
					turtle = stack[--sp];
				break;
		}
	}
}

int main(int argc, char ** argv) {
	
	if(argc < 2) {
		printf("Give a ruleset to the program!\n");
		printf("Rules: F-+[]X\n");
	}

	char rule_buf[1024] = { 0 };
	memcpy(rule_buf, argv[1], strlen(argv[1]));

	char path[8192] = { 0 };

	// TODO: make option
	double degree = 1;
	double step = 1;
	double degree_inc = 0.3612;
	double step_inc = 0.075;

	int index = 0;

	for(index = 0; index < 120; index++) {
		printf("L-System image %i\n", index);
		memset(image, 255, sizeof(image));

		char *state = strdup("F");
		int iterations = 4;

		for (int i = 0; i < iterations; ++i) {
			char *next = apply_rules(state, rule_buf);
			free(state);
			state = next;
		}

		interpret(state, (double)degree, (double)step, iterations * 2);
		snprintf(path, 8191, 
			"output/A%f_S%f_RS_%s_%i.ppm", 
			degree, step, rule_buf, index);
		// save_ppm("tree.ppm");
		save_ppm(path);
		free(state);

		degree += degree_inc;
		step += step_inc;
	}

	return 0;
}

