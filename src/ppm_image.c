#include "../includes/common.h"
#include "../includes/ppm_image.h"

ImgPPM loadPPM(char *filename){
	ImgPPM img;

	// open file for reading
	FILE *file = fopen(filename, "rb");
	if(!file){
		fprintf(stderr, "Error opening image: '%s'\n", filename);
		exit(1);
	}

	// read image header
	fscanf(file, "%s", img.type);
	if(img.type[0] != 'P' || img.type[1] != '6'){
		error("Image format error, not is 'P6'\n");
	}
	fscanf(file, "%u %u", &img.x, &img.y);
	fscanf(file, "%u\n", &img.max);

	// memory allocation for image reading
	img.data = (Pixel*) malloc(img.x * img.y * sizeof(Pixel));
	if(!img.data){
		fprintf(stderr, "Error allocating memory for reading image\n");
		exit(1);
	}

	// read image pixel list
	if(fread(img.data, 3 * img.x, img.y, file) != img.y){
		fprintf(stderr, "Error reading image content: '%s'\n", filename);
		exit(1);
	}

	// close file
	fclose(file);

	return img;
}

void savePPM(char *filename, ImgPPM img){
	// opening or creating image for writing
	FILE *file = fopen(filename, "wb");
	if(!file) {
		fprintf(stderr, "Error opening or creating image: '%s'\n", filename);
		exit(1);
	}

	// write image header
	fprintf(file, "%s\n", img.type);
	fprintf(file, "%d %d\n",img.x,img.y);
	fprintf(file, "%d\n", img.max);

	// write image data
	fwrite(img.data, 3 * img.x, img.y, file);

	// close file
	fclose(file);
}
