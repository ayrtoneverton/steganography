
#pragma pack(2) // 2 byte packing
typedef struct {
	unsigned short int type;
	unsigned int hsize;
	unsigned short int reserved1, reserved2;
	unsigned int offset;

	unsigned int size, width, height;
	unsigned short int bits;

	unsigned int compression;
	unsigned int pixelsize;
	unsigned int xResolution, yResolution;
	unsigned int nColors;
	unsigned int importantcolors;
} HeadImgBMP;

typedef struct {
	HeadImgBMP head;
	Pixel *data;
} ImgBMP;

ImgBMP loadBMP(char *filename);

void saveBMP(char *filename, ImgBMP img);
