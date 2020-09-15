//This file contains all PPM reading algorithms.
//Functions include reading the header information
//and reading in the pixels.

#include "viewer.h"

//read PPM's header and save info
int readFile(char** argv, format* header){
	int count = 0; //count # of lines in header

	//attempt to open PPM file
	FILE* img = fopen(argv[0], "rb");

	//error in opening PPM file
	if (img == NULL){printf("Error in opening image"); return 0;}

	//success in opeing PPM file
	else{
		char buff[250]; //buffer to read lines in file
		char* ptr;

		//get PPM format
		fgets(buff, 250, img);

		//PPM file is not in binary or ASCII format
		if(buff[0] == 'P' && (buff[1] == '6'|| buff[1] == '3')){
			++count; //count PPM format
			//copy PPM format to header info
			strncpy(header->type, buff, 2);
			header->type[2] = '\0';
			printf("Is in correct format: %s\n", header->type);
		}
		else{
			printf("File not in proper format: %s\n", buff); return 0;}

		//check second line for comment line after PPM format
		fgets(buff, 250, img);

		//comment line found
		if(buff[0] == '#'){
			count += 2; //count comment line and count the image size

			//copy image size to header info
			fgets(buff, 250, img);
			header->width = strtol(buff, &ptr, 10);
			header->height = strtol(ptr, NULL, 10);
			printf("Image size: %d x %d\n", header->width, header->height);
		}
		//comment line not found, grab image size
		else{
			++count; //count image size

			//copy image size to header info
			header->width = strtol(buff, &ptr, 10);
			header->height = strtol(ptr, NULL, 10);
			printf("Image size: %d x %d\n", header->width, header->height);
		}

		//ensure max color value is 255
		fgets(buff, sizeof(buff), img);

		//max color is not at 255
		if(strncmp(buff, "255", sizeof(buff) == 0)){
			printf("Max color value is not at 255\n"); return 0;}
		//max color is at 255
		else{
			++count; //count max color

			//copy max color to header info
			header->max_color = strtol(buff, NULL, 10);
			printf("Max color is correct: %d\n", header->max_color);
		}
		fclose(img);
		return count;
	}
}

//fill image using PPM's header info
void fillImage(char** argv, format header, int count, Pixel** image){
	//image size does not exists
	if(!image){
		printf("\nCannot allocate for image"); return;}

	//image size exists
	else{
		//attempt to open PPM file
		FILE* img = fopen(argv[0], "rb");

		//error in opening PPM file
		if (img == NULL){
			printf("Error in opening image"); return;}
		char buff[250]; //buffer for reading lines in file

		//skip header information
		for(int i = 0; i < count; ++i){
			fgets(buff, sizeof(buff), img);}

		//fill in pixels in ASCII format
		if(strcmp(header.type, "P3") == 0){
			for(int i = 0; i < header.height; ++i){
				for(int j = 0; j < header.width; ++j){
					fgets(buff, 250,img);
					image[i][j].Red = strtol(buff, NULL, 10);
					fgets(buff, 250,img);
					image[i][j].Green = strtol(buff, NULL, 10);
					fgets(buff, 250,img);
					image[i][j].Blue = strtol(buff, NULL, 10);
				}
			}
		}
		//fill in pixels in binary format
		if(strcmp(header.type, "P6") == 0){
			for(int i = 0; i < header.height; ++i){
				for(int j = 0; j < header.width; ++j){
					fread(&image[i][j].Red, sizeof(unsigned char), 1, img);
					fread(&image[i][j].Green, sizeof(unsigned char), 1, img);
					fread(&image[i][j].Blue, sizeof(unsigned char), 1, img);
				}
			}
		}
		fclose(img);
	}
}
