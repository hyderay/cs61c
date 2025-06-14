/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	Color *c = malloc(sizeof(Color));
    int lsb = image->image[row][col].B & 1;
    if (lsb == 0) {
        c->R = 0;
        c->G = 0;
        c->B = 0;
    } else {
        c->R = 255;
        c->G = 255;
        c->B = 255;
    }
    return c;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image *img = malloc(sizeof(Image));
    img->rows = image->rows;
    img->cols = image->cols;
    img->image = malloc(image->rows * sizeof(Color *));
    for (uint32_t i = 0; i < image->rows; i++) {
        img->image[i] = malloc(image->cols * sizeof(Color));
    }

    for (uint32_t i = 0; i < img->rows; i++) {
        for (uint32_t j = 0; j < img->cols; j++) {
            Color *color = evaluateOnePixel(image, i, j);
            img->image[i][j] = *color;
            free(color);
        }
    }

    return img;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	if (argc != 2) {
        return -1;
    }

    Image *img = readData(argv[1]);
    if (img == NULL) {
        return -1;
    }

    Image *newImg = steganography(img);

    writeData(newImg);
    freeImage(newImg);
    freeImage(img);

    return 0;
}
