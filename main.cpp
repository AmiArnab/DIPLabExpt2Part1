#include <iostream>
#include <bmpimage.h>
#include <readbmp.h>
#include <convertflipgrayscale.h>
#include <writebmp.h>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    BMPImage myImage;

    if(argc != 3)
    {
        cout << "Invalid argument format!\nClosing program...\n";
        return 1;
    }

    cout << "Starting program...\n";

    if(ReadBMP(argv[1],&myImage))      //----Change the input filename here, if using different file----
    {
        cout << "ReadBMP failed!\nClosing program...\n";
        return 1;
    }

    //-----------------------Displaying Header of RGB----------------------
    BMPImage::BITMAPFILEHEADER fh = myImage.GetBMPFileHeader<BMPImage::RGB>();
    BMPImage::BITMAPINFOHEADER fi = myImage.GetBMPInfoHeader<BMPImage::RGB>();

    cout << "----------------------------------------------\n";
    cout << "Displaying BMP RGB File header...\n";
    cout << "Magic Number: " << fh.bfType << endl;
    cout << "Size of file: " << fh.bfSize << endl;
    cout << "Reserved: " << fh.bfReserved1 << endl;
    cout << "Reserved: " << fh.bfReserved2 << endl;
    cout << "Offset: " << fh.bfOffBits << endl;

    cout << "Displaying BMP RGB File Info header...\n";
    cout << "Size of Info header: " << fi.biSize << endl;
    cout << "Width: " << fi.biWidth << endl;
    cout << "Height: " << fi.biHeight << endl;
    cout << "Colour Planes: " << fi.biPlanes << endl;
    cout << "Number of bits per pixel: " << fi.biBitCount << endl;
    cout << "Type of compression: " << fi.biCompression << endl;
    cout << "Size of image data: " << fi.biSizeImage << endl;
    cout << "X pixels per meter: " << fi.biXPelsPerMeter << endl;
    cout << "Y pixels per meter: " << fi.biYPelsPerMeter << endl;
    cout << "Number of colours used: " << fi.biClrUsed << endl;
    cout << "Number of colours important: " << fi.biClrImportant << endl;
    cout << "----------------------------------------------\n";
    if(ConvertFlipGrayscale(&myImage))
    {
        cout << "ConvertFlipGrayscale failed!\nClosing program...\n";
        return 1;
    }

    //-----------------------Displaying Header of Gray----------------------
    fh = myImage.GetBMPFileHeader<BMPImage::Gray>();
    fi = myImage.GetBMPInfoHeader<BMPImage::Gray>();

    cout << "----------------------------------------------\n";
    cout << "Displaying BMP Gray File header...\n";
    cout << "Magic Number: " << fh.bfType << endl;
    cout << "Size of file: " << fh.bfSize << endl;
    cout << "Reserved: " << fh.bfReserved1 << endl;
    cout << "Reserved: " << fh.bfReserved2 << endl;
    cout << "Offset: " << fh.bfOffBits << endl;

    cout << "Displaying BMP Gray File Info header...\n";
    cout << "Size of Info header: " << fi.biSize << endl;
    cout << "Width: " << fi.biWidth << endl;
    cout << "Height: " << fi.biHeight << endl;
    cout << "Colour Planes: " << fi.biPlanes << endl;
    cout << "Number of bits per pixel: " << fi.biBitCount << endl;
    cout << "Type of compression: " << fi.biCompression << endl;
    cout << "Size of image data: " << fi.biSizeImage << endl;
    cout << "X pixels per meter: " << fi.biXPelsPerMeter << endl;
    cout << "Y pixels per meter: " << fi.biYPelsPerMeter << endl;
    cout << "Number of colours used: " << fi.biClrUsed << endl;
    cout << "Number of colours important: " << fi.biClrImportant << endl;
    cout << "----------------------------------------------\n";

    if(WriteBMP(argv[2],&myImage))   //----Change the output filename here------
    {
        cout << "ConvertFlipGrayscale failed!\nClosing program...\n";
        return 1;
    }

    cout << "Closing program...\n";
    return 0;
}
