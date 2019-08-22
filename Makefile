NAME = steg
ARGS = -W -Wall -pedantic

main : main.c compiled compiled/common.o compiled/ppm_image.o compiled/bmp_image.o
	gcc ${ARGS} main.c compiled/common.o compiled/ppm_image.o compiled/bmp_image.o -o ${NAME}

compiled/ppm_image.o : src/ppm_image.c
	gcc ${ARGS} -c src/ppm_image.c -o compiled/ppm_image.o

compiled/bmp_image.o : src/bmp_image.c
	gcc ${ARGS} -c src/bmp_image.c -o compiled/bmp_image.o

compiled/common.o : src/common.c
	gcc ${ARGS} -c src/common.c -o compiled/common.o

compiled :
	mkdir compiled

clean : 
	rm ${NAME}*

clean-all : 
	rm -rf compiled ${NAME}*
