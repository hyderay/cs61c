/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				Sean
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No such file exists.\n");
        return NULL;
    }

    char isP3[3];
    fscanf(fp, "%2s", isP3);
    if (strcmp(isP3, "P3") != 0) {
        printf("Not in the P3 format.\n");
        fclose(fp);
        return NULL;
    }

    int col, row, maxval;
    fscanf(fp, "%d %d", &col, &row);
    fscanf(fp, "%d", &maxval);

    Image *img = malloc(sizeof(Image));
    img->cols = col;
    img->rows = row;
    img->image = malloc(row * sizeof(Color *));
    for (int i = 0; i < row; i++) {
        img->image[i] = malloc(col * sizeof(Color));
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int r, g, b;
            fscanf(fp, "%d %d %d", &r, &g, &b);
            img->image[i][j].R = r;
            img->image[i][j].G = g;
            img->image[i][j].B = b;
        }
    }

    fclose(fp);
    return img;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	uint32_t row = image->rows;
    uint32_t col = image->cols;

    printf("P3\n");
    printf("%d %d\n", col, row);
    printf("255\n");

    for (uint32_t i = 0; i < row; i++) {
        for (uint32_t j = 0; j < col; j++) {
            Color c = image->image[i][j];
            printf("%3d %3d %3d", c.R, c.G, c.B);
            if (j < col - 1) {
                printf("   ");
            }
        }
        printf("\n");
    }
}

//Frees an image
void freeImage(Image *image)
{
	uint32_t row = image->rows;

    for (uint32_t i = 0; i < row; i++) {
        free(image->image[i]);
    }

    free(image->image);
    free(image);
}