//This file will be the main operation
//to read and render images. It will
//utilize all functions needed to
//produce an image.

#include "viewer.h"

int main(int argc, char* argv[]){
	//image size of PPM for array allocation
	format header;
	//create array for PPM file
	Pixel** image;

	//load in PPM file
	int headerLines; //the number of lines in the header info
	//read in header info if given a file to read
	if(argv[1]){
		headerLines = readFile(&argv[1], &header);}
	else{printf("No PPM file was given\n"); return 0;}

	//allocate size of image for pixels
	image = (Pixel**)malloc(sizeof(Pixel*) * header.height);
	for(int i = 0; i < header.height; ++i){
		image[i] = (Pixel*)malloc(sizeof(Pixel) * header.width);}

	//fill in image with pixels
	fillImage(&argv[1], header, headerLines, image);

	//render image
	Pixel newPixel;
	for(int i = 0; i <= header.height; i+=8){
		//print each pixel
		for(int j = 0; j <= header.width; j+=4){
			//get downsized pixel
			newPixel = downSize(image, i, j, header);

			//get character of luminance
			char C = getLumi(newPixel);

			//get color of pixel
			enum Ansi_Color S = getColor(newPixel);

			//print color and character as a pixel
			PrintASCIIChar(S, C);
		}
		printf("\n"); //print new line of pixels to align to image
	}

	//free 2D Pixel array
	for(int i = 0; i < header.height; ++i){
		free(image[i]);
	}
	free(image);

	return 0;
}

