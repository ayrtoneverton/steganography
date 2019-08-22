#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef enum {
	false = 0,
	true = 1
} Bool;

// Red, Green, Blue, 0 -> 255
typedef struct {
	unsigned char r, g, b;
} Pixel;

int pot(int b, int e);

void error(char *s);

char *loadTXT(char *filename);

void saveTXT(char *filename, char *text);

void encode(Pixel *data, unsigned int size, char *str);

char *decode(Pixel *data, unsigned int size);
