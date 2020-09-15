//This file contains all algorithms to render
//the image. This includes downsizing the
//resolution of an image, finding the
//luminosity of each pixel, and finding the
//color for each pixel.

#include "viewer.h"

//scale pixels and get new value
Pixel downSize(Pixel** image, int m, int n, format header){
	Pixel nPixel; //downsized pixel to return
	//average of all RGB values
	int nRed = 0;
	int nGreen = 0;
	int nBlue = 0;

	//Get the sum of RGB values
	for(int i = 0; i < 8; ++i){
		for(int j = 0; j < 4; ++j){
			if(((m+i) < header.height) && ((n+j) < header.width)){
				nRed += (unsigned char)image[m+i][n+j].Red;
				nGreen += (unsigned char)image[m+i][n+j].Green;
				nBlue += (unsigned char)image[m+i][n+j].Blue;
			}
		}
	}

	//get average of RGB values
	nRed = nRed / 32;
	nGreen = nGreen / 32;
	nBlue = nBlue / 32;

	//store average values to downsized pixel
	nPixel.Red = (unsigned char)nRed;
	nPixel.Green = (unsigned char)nGreen;
	nPixel.Blue = (unsigned char)nBlue;

	return nPixel;
}

//Find pixel's luminosity
char getLumi(Pixel p){
	char list[] = ASCII_MAP_STRING; //luminance char ramp
	int size = strlen(list); //scale of ASCII map
	int Y; //luminance value
	char c; //luminance character

	int R = 0.21 * (unsigned char)p.Red;
	int G = 0.71 * (unsigned char)p.Green;
	int B = 0.08 * (unsigned char)p.Blue;

	//obtain luminosity value
	Y = (R + G + B) / 3;

	//luminosity is greater than scale
	if(Y > size){c = list[size - 1];}
	//luminosity is less than scale
	else if(Y < 0){c = list[0];}
	//luminosity is within scale
	else{c = list[Y];}

	return c;
}

//Obtain accurate color for pixel
enum Ansi_Color getColor(Pixel p){

	int close; //shortest Euclidean distance for RGB values
	enum Ansi_Color color = BrightBlue; //accurate color of pixel to return

	//get base distance of closest color
	int R = (unsigned char)ANSI_COLORS[0].Red - (unsigned char)p.Red;
	int G = (unsigned char)ANSI_COLORS[0].Green - (unsigned char)p.Green;
	int B = (unsigned char)ANSI_COLORS[0].Blue - (unsigned char)p.Blue;
	int temp = pow(R, 2) + pow(G, 2) + pow(B, 2);
	close = sqrt(temp);

	//determine shortest RGB value distance of each color
	for(int i = 1; i < NUM_ANSI_COLORS; ++i){
		int R = (unsigned char)ANSI_COLORS[i].Red - (unsigned char)p.Red;
		int G = (unsigned char)ANSI_COLORS[i].Green - (unsigned char)p.Green;
		int B = (unsigned char)ANSI_COLORS[i].Blue - (unsigned char)p.Blue;

		int temp = pow(R, 2) + pow(G, 2) + pow(B, 2);
		temp = sqrt(temp);

		if(temp < close){
			close = temp;
			color = BrightBlue + i;}
	}

	return color;
}
