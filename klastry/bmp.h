#pragma once

#include <fstream>

void write_bmp(const char* path, const unsigned width, const unsigned height, const int* const data) {
    const unsigned pad=(4-(3*width)%4)%4, filesize=54+(3*width+pad)*height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
    char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
    for(unsigned i=0; i<4; i++) {
        header[ 2+i] = (char)((filesize>>(8*i))&255);
        header[18+i] = (char)((width   >>(8*i))&255);
        header[22+i] = (char)((height  >>(8*i))&255);
    }
    char* img = new char[filesize];
    for(unsigned i=0; i<54; i++) img[i] = header[i];
    for(unsigned y=0; y<height; y++) {
        for(unsigned x=0; x<width; x++) {
            const int color = data[x+(height-1-y)*width];
            const int i = 54+3*x+y*(3*width+pad);
            img[i  ] = (char)( color     &255);
            img[i+1] = (char)((color>> 8)&255);
            img[i+2] = (char)((color>>16)&255);
        }
        for(unsigned p=0; p<pad; p++) img[54+(3*width+p)+y*(3*width+pad)] = 0;
    }
    std::ofstream file(path, std::ios::out|std::ios::binary);
    file.write(img, filesize);
    file.close();
    delete[] img;
}

void write_bmp(const char* path, const unsigned width, const unsigned height, const bool* const data) {
    const unsigned pad=(4-(3*width)%4)%4, filesize=54+(3*width+pad)*height; // horizontal line must be a multiple of 4 bytes long, header is 54 bytes
    char header[54] = { 'B','M', 0,0,0,0, 0,0,0,0, 54,0,0,0, 40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0 };
    for(unsigned i=0; i<4; i++) {
        header[ 2+i] = (char)((filesize>>(8*i))&255);
        header[18+i] = (char)((width   >>(8*i))&255);
        header[22+i] = (char)((height  >>(8*i))&255);
    }
    char* img = new char[filesize];
    for(unsigned i=0; i<54; i++) img[i] = header[i];
    for(unsigned y=0; y<height; y++) {
        for(unsigned x=0; x<width; x++) {
            const int color = (data[x+(height-1-y)*width] ? ((((255) << 8) + 255) << 8) + 255  :  0 );
            const int i = 54+3*x+y*(3*width+pad);
            img[i  ] = (char)( color     &255);
            img[i+1] = (char)((color>> 8)&255);
            img[i+2] = (char)((color>>16)&255);
        }
        for(unsigned p=0; p<pad; p++) img[54+(3*width+p)+y*(3*width+pad)] = 0;
    }
    std::ofstream file(path, std::ios::out|std::ios::binary);
    file.write(img, filesize);
    file.close();
    delete[] img;
}