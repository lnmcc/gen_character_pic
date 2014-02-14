#include "saveBmp.h"

void Snapshot(BYTE *pData, int width, int height, char *fileName, DWORD size) {
    BMPFILEHEADER_T bfh = { 0 };
    bfh.bfType = (WORD)0x4d42;
    bfh.bfSize = (DWORD)(size + 54);
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = 54;

    BMPINFOHEADER_T bih = { 0 };
    bih.biSize = 40;
    bih.biWidth = width;
    bih.biHeight = height;
    bih.biPlanes = 1;
    bih.biBitCount = 24;
    bih.biCompression = 0;
    bih.biSizeImage = 0;
    bih.biXPelsPerMeter = 0;
    bih.biYPelsPerMeter = 0;
    bih.biClrUsed = 0;
    bih.biClrImportant = 0;

    FILE *fp = fopen(fileName, "wb");
    if(!fp) {
        fprintf(stderr, "open file: %s error\n", fileName);
        return;
    }

    fwrite(&bfh.bfType, 1, 2, fp);
    fwrite(&bfh.bfSize, 1, 4, fp);
    fwrite(&bfh.bfReserved1, 1, 2, fp);
    fwrite(&bfh.bfReserved2, 1, 2, fp);
    fwrite(&bfh.bfOffBits, 1, 4, fp);
    fwrite(&bih, 1, sizeof(BMPINFOHEADER_T), fp);
    fwrite(pData, 1, size, fp);
    fclose(fp);
}
