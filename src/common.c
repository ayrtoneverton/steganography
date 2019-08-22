#include "../includes/common.h"

// potentiation
int pot(int b, int e){
	int i, t=1;
	for(i=0; i < e; i++){
		t *= b;
	}
	return t;
}

// show error
void error(char *s){
	fprintf(stderr, "%s\n", s);
	exit(1);
}

char *loadTXT(char *filename){
	char *text;
	long int size;

	// open file
	FILE *file = fopen(filename, "r");
	if(!file){
		fprintf(stderr, "Error opening file: '%s'\n", filename);
		exit(1);
	}

	// get size text
	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fseek(file, 0, SEEK_SET);

	// allocate memory
	text = malloc((size + 2) * sizeof(char));

	// load text file
	fread(text, 1, size, file);

	// delimiter end file
	text[size] = '!';
	text[size+1] = '^';
	text[size+2] = '\0';

	// close file
	fclose(file);

	return text;
}

void saveTXT(char *filename, char *text){
	int size = 0;

	// create and open file
	FILE *file = fopen(filename, "w");
	if(!file){
		fprintf(stderr, "Error create or open file: '%s'\n", filename);
		exit(1);
	}

	// count size file
	while(text[size] != '!' && text[size + 1] != '^') size++;

	// write text in file
	fwrite(text, 1, size * sizeof(char), file);

	// close file
	fclose(file);
}

// inserts text into pixels using the least significant bit of each color in sequence
void encode(Pixel *data, unsigned int size, char *str){
	unsigned int i, b = 0, s = 0;

	for(i = 0; (s < 2 || (str[s-1] != '!' && str[s] != '^')) && i < size; ++i){
		data[i].r = str[s] & pot(2, b) ? data[i].r | 1 : data[i].r & 254;
		if(++b > 7){ b = 0; s++; }

		data[i].g = str[s] & pot(2, b) ? data[i].g | 1 : data[i].g & 254;
		if(++b > 7){ b = 0; s++; }

		data[i].b = str[s] & pot(2, b) ? data[i].b | 1 : data[i].b & 254;
		if(++b > 7){ b = 0; s++; }
	}
}

// retrieves text in pixels using the least significant bit of each color in sequence
char *decode(Pixel *data, unsigned int size){
	unsigned int i, b = 0, s = 0;
	char *str = malloc((size / 8) * sizeof(char));

	for(i = 0; (s < 2 || (str[s-1] != '!' && str[s] != '^')) && i < size; ++i){
		if(data[i].r & 1) str[s] |= pot(2, b);
		if(++b > 7){ b = 0; s++; str[s] = 0; }

		if(data[i].g & 1) str[s] |= pot(2, b);
		if(++b > 7){ b = 0; s++; str[s] = 0; }

		if(data[i].b & 1) str[s] |= pot(2, b);
		if(++b > 7){ b = 0; s++; str[s] = 0; }
	}
	return str;
}
