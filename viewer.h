#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//structure to keep PPM's header information
typedef struct format{
	char type[3];
	int width;
	int height;
	int max_color;
} format;

//read in header info of PPM
int readFile(char** argv, format* header);

//read RGB values into pixels
void fillImage(char** argv, format header, int count, Pixel** image);

//get scaled down pixel
Pixel downSize(Pixel** image, int m, int n, format header);

//obtain relative luminance as ASCII characters
char getLumi(Pixel p);

//get accurate color of pixel
enum Ansi_Color getColor(Pixel p);
