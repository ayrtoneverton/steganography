## Prerequisites
Any C language compiler (GCC or similar).

## Compiling
If you have Makefile installed, just run the “make” command from within the project root directory, if not, run the following commands from the same directory:
```SHELL
$ mkdir compiled
$ gcc -c src/common.c -o compiled/common.o
$ gcc -c src/ppm_image.c -o compiled/ppm_image.o
$ gcc -c src/bmp_image.c -o compiled/bmp_image.o
$ gcc main.c compiled/common.o compiled/ppm_image.o compiled/bmp_image.o -o steg
```

## Using the steganography
After compilation will be generated the executable "steg", to use it just run it passing the desired parameters. Example of use:
```SHELL
$ ./steg -h
$ ./steg -e -i tests/text.txt -t bmp -f tests/img.bmp -o img.bmp
$ ./steg -d -t bmp -f img.bmp -o text.txt mkn
```