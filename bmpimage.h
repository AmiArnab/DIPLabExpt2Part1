#ifndef BMPIMAGE_H
#define BMPIMAGE_H

#  define BF_TYPE 0x4D42

#include <iostream>
#include <vector>
#include <string>
#include <exception>
using namespace std;

class BMPImage
{

public:

#pragma pack(push, 1)

typedef struct                       /**** BMP file header structure ****/
{
    unsigned short bfType;           /* Magic number for file */
    unsigned int   bfSize;           /* Size of file */
    unsigned short bfReserved1;      /* Reserved */
    unsigned short bfReserved2;      /* ... */
    unsigned int   bfOffBits;        /* Offset to bitmap data */
} BITMAPFILEHEADER;

                                     /* "MB" */

typedef struct                       /**** BMP file info structure ****/
{
    unsigned int   biSize;           /* Size of info header */
    int            biWidth;          /* Width of image */
    int            biHeight;         /* Height of image */
    unsigned short biPlanes;         /* Number of colour planes */
    unsigned short biBitCount;       /* Number of bits per pixel */
    unsigned int   biCompression;    /* Type of compression to use */
    unsigned int   biSizeImage;      /* Size of image data */
    int            biXPelsPerMeter;  /* X pixels per meter */
    int            biYPelsPerMeter;  /* Y pixels per meter */
    unsigned int   biClrUsed;        /* Number of colours used */
    unsigned int   biClrImportant;   /* Number of important colours */
} BITMAPINFOHEADER;

#pragma pack(pop)


    typedef unsigned char*** RGB;
    typedef unsigned char** Gray;

    BMPImage();
    template<typename T> BITMAPFILEHEADER GetBMPFileHeader();
    template<typename T> BITMAPINFOHEADER GetBMPInfoHeader();
    template<typename T> T GetImageData();
    int GetImageHeight();
    int GetImageWidth();
    template<typename T> int SetBMPFileHeader(BITMAPFILEHEADER);
    template<typename T> int SetBMPInfoHeader(BITMAPINFOHEADER);
    template<typename T> int SetImageData(T);
    int SetImageHeight(int);
    int SetImageWidth(int);
    int CreateColourTable();
    vector<unsigned char> GetColourTable();

private:

    BITMAPFILEHEADER RGBfh,Grayfh;
    BITMAPINFOHEADER RGBih,Grayih;
    unsigned char*** RGBData = NULL;
    unsigned char** GrayData = NULL;
    int height,width;
    bool RGBDataExist, GrayDataExist;
    bool RGBHeaderExist, GrayHeaderExist;
    bool colourtableexist;
    vector <unsigned char> colourtable;
};

#endif // BMPIMAGE_H
