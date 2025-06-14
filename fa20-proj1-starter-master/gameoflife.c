/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				Sean
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"
int countNeighbor(Image *image, int row, int col);
int isAlive(Image *image, int row, int col);

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
    int numOfNei = countNeighbor(image, row, col);

    int status;
    if (isAlive(image, row, col)) {
        status = (rule >> (9 + numOfNei)) & 1;
    } else {
        status = (rule >> numOfNei) & 1;
    }

    Color *c = malloc(sizeof(Color));
    if (status == 1) {
        c->R = 255;
        c->G = 255;
        c->B = 255;
    } else {
        c->R = 0;
        c->G = 0;
        c->B = 0;
    }

    return c;
}

//Determine if the given coordinate is alive.
int isAlive(Image *image, int row, int col) {
    if (image->image[row][col].R == 255 && image->image[row][col].G == 255 &&
        image->image[row][col].B == 255) {
        return 1;
    }
    return 0;
}

//Return the number of neighbors alive.
int countNeighbor(Image *image, int row, int col) {
    uint32_t rows = image->rows;
    uint32_t cols = image->cols;

    int up    = (row - 1 + rows) % rows;
    int down  = (row + 1) % rows;
    int left  = (col - 1 + cols) % cols;
    int right = (col + 1) % cols;

    int alive = 0;
    alive += isAlive(image, up   , left );
    alive += isAlive(image, up   , col  );
    alive += isAlive(image, up   , right);
    alive += isAlive(image, row  , left );
    alive += isAlive(image, row  , right);
    alive += isAlive(image, down , left );
    alive += isAlive(image, down , col  );
    alive += isAlive(image, down , right);

    return alive;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	uint32_t row = image->rows;
    uint32_t col = image->cols;

    Image *img = (Image *) malloc(sizeof(Image));
    img->rows = row;
    img->cols = col;
    img->image = (Color **) malloc(row * sizeof(Color *));
    for (uint32_t i = 0; i < row; i++) {
        img->image[i] = (Color *) malloc(col * sizeof(Color));
    }

    for (uint32_t i = 0; i < row; i++) {
        for (uint32_t j = 0; j < col; j++) {
            Color *c = evaluateOneCell(image, i, j, rule);
            img->image[i][j] = *c;
            free(c);
        }
    }

    return img;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{
	if (argc != 3) {
        printf("usage: ./gameOfLife filename rule\n");
        printf("filename is an ASCII PPM file (type P3) with maximum value 255.\n");
        printf("rule is a hex number beginning with 0x; Life is 0x1808.\n");
        return -1;
    }

    Image *img = readData(argv[1]);
    if (img == NULL) {
        return -1;
    }

    uint32_t rule = strtol(argv[2], NULL, 0);
    Image *game = life(img, rule);
    if (game == NULL) {
        freeImage(img);
        return -1;
    }

    writeData(game);

    freeImage(game);
    freeImage(img);
    return 0;
}
