#include "../includes/common.h"
#include "../includes/bmp_image.h"

ImgBMP loadBMP(char *filename){
	ImgBMP img;

	// open file for reading
	FILE *file = fopen(filename,"rb");
	if(!file){
		fprintf(stderr, "Error opening image: '%s'\n", filename);
		exit(1);
	}

	// read image header
	fread(&img.head, 1, sizeof(img.head), file);

	// memory allocation for image reading
	img.data = (Pixel*) malloc(img.head.width * img.head.height * sizeof(Pixel));
	if(!img.data){
		fprintf(stderr, "Error allocating memory for reading image\n");
		exit(1);
	}

	// read image pixel list
	if(fread(img.data, 3 * img.head.width, img.head.height, file) != img.head.height){
		fprintf(stderr, "Error reading image content: '%s'\n", filename);
		exit(1);
	}

	//  close file
	fclose(file);

	return img;
}

void saveBMP(char *filename, ImgBMP img){
	// opening or creating image for writing
	FILE *file = fopen(filename, "wb");
	if(!file) {
		fprintf(stderr, "Error opening or creating image: '%s'\n", filename);
		exit(1);
	}

	// write image header
	fwrite(&img.head, 1, sizeof(img.head), file);

	// write image data
	fwrite(img.data, 3 * img.head.width, img.head.height, file);

	// close file
	fclose(file);
}
