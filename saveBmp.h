#ifndef SAVEBMP_H
#define SAVEBMP_H

#include <stdio.h>
#include <stdlib.h>

typedef long LONG;
typedef unsigned char BYTE;
typedef unsigned int DWORD;
typedef unsigned short WORD;

typedef struct {
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BMPFILEHEADER_T;

typedef struct {
    DWORD biSize;
    DWORD biWidth;
    DWORD biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    DWORD biXPelsPerMeter;
    DWORD biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BMPINFOHEADER_T;

void Snapshot(BYTE *pData, int width, int height, char *fileName, DWORD size);

#endif // SAVEBMP_H
