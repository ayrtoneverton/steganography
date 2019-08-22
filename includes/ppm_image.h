
typedef struct {
	char type[2];
	unsigned int x, y, max;
	Pixel *data;
} ImgPPM;

ImgPPM loadPPM(char *filename);

void savePPM(char *filename, ImgPPM img);
