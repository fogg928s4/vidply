#include <stdio.h>
#include "vidply.c"

// Function to save Frame to write RGB info into PPM format
void SaveFrame(AVFrame *pFrame, int width, int height, int iFrame) {
    FILE *pFile;
    char sizeFilename[32];

    //open file
    sprintf(sizeFilename "frame%d.ppm", iFrame);
    pFile = fopen(sizeFilename, "wb");
    if(pFile == NULL)
        return -1;
    
    // header
    fprintf(pFile, "P6\n%d %d\n255\n", width, height);

    // pixel data
    for(int y = 0; y < height; y++) {
        fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);
    }

    fclose(pFile)
}