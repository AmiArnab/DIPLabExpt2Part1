#include "convertflipgrayscale.h"

int ConvertFlipGrayscale(BMPImage *image)
{
    unsigned char*** colour = image->GetImageData<BMPImage::RGB>();  //---Variable to store RGB data----
    unsigned char** gray = new unsigned char*[image->GetImageHeight()];  //----Variable to store grayscale data----
    unsigned char** flippedgray = new unsigned char*[image->GetImageHeight()]; //----Variable to store flipped grayscale data----

    int height = image->GetImageHeight();
    int width = image->GetImageHeight();

    for(int i=0;i<height;++i) //----Creating the 2d data matrices
    {
        *(gray+i) = new unsigned char[width];
        *(flippedgray+i) = new unsigned char[width];
    }

    for(int i=0;i<height;i++)  //----Converting to grayscale------
    {
        for(int j=0;j<width;j++)
        {
            gray[i][j] = (0.0722*colour[height-i-1][width-j-1][0]) + (0.7152*colour[height-i-1][width-j-1][1]) + (0.2126*colour[height-i-1][width-j-1][2]);
            // Weighted grayscale conversion 0.2126(R),0.7152(G),0.0722(B)
        }
    }
    cout << "Grayscale conversion done!\n";

    BMPImage::BITMAPFILEHEADER gfh = image->GetBMPFileHeader<BMPImage::RGB>();  //----Copying the headers for modification
    BMPImage::BITMAPINFOHEADER gih = image->GetBMPInfoHeader<BMPImage::RGB>();
    gih.biBitCount = 8; //----Modifying bits per pixel----
    gih.biClrImportant = 256;
    gih.biClrUsed = 256;
    gfh.bfSize = 1078 + gih.biWidth*gih.biHeight;
    gfh.bfOffBits = 1078; //----Modifying offset----
    gih.biSizeImage = gih.biHeight*gih.biWidth; //----Setting the image size----
    try //---Set the modified BMP file header------
    {
        image->SetBMPFileHeader<BMPImage::Gray>(gfh);
    }
    catch(int e)
    {
        cout << "Error code " << e << endl;
        return -100;
    }

    try //---Set the modified BMP file info header----
    {
        image->SetBMPInfoHeader<BMPImage::Gray>(gih);
    }
    catch(int e)
    {
        cout << "Error code " << e << endl;
        return -100;
    }
    //-----This step is redundant, can be omitted-----------------
    try //----Set the grayscale image data-----
    {
        image->SetImageData<BMPImage::Gray>(gray);
    }
    catch(int e)
    {
        cout << "Error code " << e << endl;
        return -100;
    }

    //------Create the colour table for grayscale image--------
    image->CreateColourTable();
    //----Transpose the grayscale image-----------
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            flippedgray[j][i] = gray[i][j]; //Transposing the image;
        }
    }

    try //----Set the transposed image data-----------
    {
        image->SetImageData<BMPImage::Gray>(flippedgray);
    }
    catch(int e)
    {
        cout << "Error code " << e << endl;
        return -100;
    }

    cout << "Transposition complete!\nExecution of ConvertFlipGrayscale complete!\n------------------------------\n";
    return 0;
}
