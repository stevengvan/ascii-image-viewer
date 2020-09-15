CFLAGS =  -O0 -std=c11 -pedantic -Wall

all: test test2

test: viewer.c color.c read.c render.c
	gcc $(CFLAGS) -o viewer viewer.c color.c read.c render.c -lm

test2: viewer.o color.o read.o render.o
		gcc -o viewer viewer.o color.o read.o render.o -lm
viewer.o: viewer.c
	gcc -c -o viewer.o viewer.c
color.o: color.c
	gcc -c -o color.o color.c
read.o: read.c
	gcc -c -o read.o read.c
render.o: render.c
	gcc -c -o render.o render.c

clean:
	rm -f *.o test test2 viewer
