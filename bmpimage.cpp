#include "bmpimage.h"

BMPImage::BMPImage()
{
    RGBDataExist = false;
    GrayDataExist = false;
    RGBHeaderExist = false;
    GrayHeaderExist = false;
    colourtableexist = false;
}

template<> BMPImage::BITMAPFILEHEADER BMPImage::GetBMPFileHeader<BMPImage::RGB>()
{
    if(RGBDataExist)
    {
        return RGBfh;
    }
    else
    {
        cout << "RGB Data are not set!\n";
        throw -1;
    }
}

template<> BMPImage::BITMAPFILEHEADER BMPImage::GetBMPFileHeader<BMPImage::Gray>()
{
    if(GrayDataExist)
    {
        return Grayfh;
    }
    else
    {
        cout << "Grayscale Data are not set!\n";
        throw -2;
    }
}

template<> BMPImage::BITMAPINFOHEADER BMPImage::GetBMPInfoHeader<BMPImage::RGB>()
{
    if(RGBDataExist)
    {
        return RGBih;
    }
    else
    {
        cout << "RGB Data are not set!\n";
        throw -3;
    }
}

template<> BMPImage::BITMAPINFOHEADER BMPImage::GetBMPInfoHeader<BMPImage::Gray>()
{
    if(GrayDataExist)
    {
        return Grayih;
    }
    else
    {
        cout << "Grayscale Data are not set!\n";
        throw -4;
    }
}

template<> BMPImage::RGB BMPImage::GetImageData<BMPImage::RGB>()
{
    if(RGBDataExist)
    {
        return RGBData;
    }
    else
    {
        cout << "RGB Data are not set!\n";
        throw -5;
    }
}

template<> BMPImage::Gray BMPImage::GetImageData<BMPImage::Gray>()
{
    if(GrayDataExist)
    {
        return GrayData;
    }
    else
    {
        cout << "Gray Data are not set!\n";
        throw -6;
    }
}

int BMPImage::GetImageHeight()
{
    if(RGBDataExist || GrayDataExist)
    {
        return height;
    }
    else
    {
        cout << "Image Data are not set!\n";
        throw -7;
    }
}

int BMPImage::GetImageWidth()
{
    if(RGBDataExist || GrayDataExist)
    {
        return width;
    }
    else
    {
        cout << "Image Data are not set!\n";
        throw -8;
    }
}

template<> int BMPImage::SetBMPFileHeader<BMPImage::RGB>(BMPImage::BITMAPFILEHEADER fhin)
{

    RGBfh = fhin;
    return 0;
}

template<> int BMPImage::SetBMPFileHeader<BMPImage::Gray>(BMPImage::BITMAPFILEHEADER fhin)
{
    Grayfh = fhin;
    return 0;
}

template<> int BMPImage::SetBMPInfoHeader<BMPImage::RGB>(BMPImage::BITMAPINFOHEADER ihin)
{
    RGBih = ihin;
    height = RGBih.biHeight;
    width = RGBih.biWidth;
    RGBHeaderExist = true;
    return 0;
}

template<> int BMPImage::SetBMPInfoHeader<BMPImage::Gray>(BMPImage::BITMAPINFOHEADER ihin)
{
    Grayih = ihin;
    height = RGBih.biHeight;
    width = RGBih.biWidth;
    GrayHeaderExist = true;
    return 0;
}

template<> int BMPImage::SetImageData<BMPImage::RGB>(BMPImage::RGB datin)
{
    if(RGBHeaderExist)
    {
        RGBData = datin;
        RGBDataExist = true;
        return 0;
    }
    else
    {
        cout << "RGB image header is not set yet!\n";
        throw -9;
    }
}

template<> int BMPImage::SetImageData<BMPImage::Gray>(BMPImage::Gray datin)
{
    if(GrayHeaderExist)
    {
        GrayData = datin;
        GrayDataExist = true;
        return 0;
    }
    else
    {
        cout << "Grascale image header is not set!\n";
        throw -10;
    }
}

int BMPImage::SetImageHeight(int x)
{
    height = x;
    return 0;
}

int BMPImage::SetImageWidth(int y)
{
    width = y;
    return 0;
}

int BMPImage::CreateColourTable()
{
    if(colourtableexist)
    {
        cout << "Colour table already exisits.\nOverwriting the exisiting...\n";
    }
    else
    {
        cout << "Colour table doesn't exist.\nCreating a new one...\n";
    }
    for(int i=0;i<256;++i)
    {
        colourtable.push_back((unsigned char)i);
        colourtable.push_back((unsigned char)i);
        colourtable.push_back((unsigned char)i);
        colourtable.push_back((unsigned char)0);
    }
    colourtableexist = true;
    return 0;
}

vector <unsigned char> BMPImage::GetColourTable()
{
    if(colourtableexist)
    {
        return colourtable;
    }
    else
    {
        cout << "Colour table is not set yet!\n";
        throw -11;
    }
}
