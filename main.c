#include "includes/common.h"
#include "includes/ppm_image.h"
#include "includes/bmp_image.h"

int main(int argc, char *argv[]){
	int opt;
	Bool decoder = false, encoder = false, help = false;
	char *input = false, *file = false, *output = false, *type = false;

	// getting all parameters and arguments for execution
	while((opt = getopt(argc, argv, "edi:t:o:f:h")) != -1){
		switch(opt){
			case 'e':
				encoder = true; break;
			case 'd':
				decoder = true; break;
			case 'i':
				input = optarg; break;
			case 'o':
				output = optarg; break;
			case 'f':
				file = optarg; break;
			case 't':
				type = optarg; break;
			case 'h':
				help = true; break;
		}
	}

	// validation of parameters and past arguments
	if(help){
		error("parameters:\n -e (encode) or -d (decode)\n -t (image type)\n -f (image origin)\n -i (input file)\n -o (output file)");
	}
	if(decoder == encoder) error("Argument error: -e (encode) or -d (decode), you must enter exactly one of them");
	if(!type) error("Argument error: -t (image type), invalid format");
	if(!file) error("Argument error: -f (image origin), invalid format");
	if(encoder && !input) error("Argument error: -i (input file), invalid format");
	if(decoder && !output) error("Argument error: -o (output file), invalid format");

	// performs desired operation for image type
	if(!strcmp(type, "bmp")){ // is BMP
		ImgBMP img = loadBMP(file);
		if(decoder){
			saveTXT(output, decode(img.data, img.head.width * img.head.height));
		}else{
			encode(img.data, img.head.width * img.head.height, loadTXT(input));
			saveBMP(output, img);
		}
	}else if(!strcmp(type, "ppm")){ // is PPM
		ImgPPM img = loadPPM(file);
		if(decoder){
			saveTXT(output, decode(img.data, img.x * img.y));
		}else{
			encode(img.data, img.x * img.y, loadTXT(input));
			savePPM(output, img);
		}
	}else{
		error("Argument error: -t, unsupported image type, use .bmp ou .ppm");
	}

	printf("OK\n");
	return 0;
}
