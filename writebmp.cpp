#include "writebmp.h"

int WriteBMP(char *filename,BMPImage *image)
{
    ofstream bmpfile;
    BMPImage::BITMAPFILEHEADER fh;
    BMPImage::BITMAPINFOHEADER  fi;
    try
    {
      fh = image->GetBMPFileHeader<BMPImage::Gray>();
    }
    catch(int e)
    {
        cout << "Error code "<< e <<endl;
        return -100;
    }
    try
    {
        fi = image->GetBMPInfoHeader<BMPImage::Gray>();
    }
    catch(int e)
    {
        cout << " Error code "<< e << endl;
        return -100;
    }
    bmpfile.open(filename,ios_base::out|ios_base::binary);
    if(bmpfile.is_open())
    {
        cout << "Saving to file " << filename << " ...\n";
        int totalsize = sizeof(fh)+sizeof(fi)+(fi.biHeight*fi.biWidth)+1024; //Total size of data in bytes
        vector<unsigned char> buffer(totalsize); // Create a buffer of that size
        int k = fh.bfOffBits; // Offset after header and colour table

        for(int i = 0;i<fi.biHeight;i++) // Copy image data to buffer
        {
            for(int j = 0;j<fi.biWidth;j++)
            {
                buffer.at(k) = (image->GetImageData<BMPImage::Gray>()[fi.biWidth-i-1][j]);
                k++;
            }
        }

        memcpy(buffer.data()+54,image->GetColourTable().data(),image->GetColourTable().size());// Copying the colour table to buffer
        memcpy(buffer.data(),&fh,sizeof(fh)); // Copying BMPFILEHEADER to buffer
        memcpy(buffer.data()+14,&fi,sizeof(fi)); // Copying BMPINFOHEADER to buffer
        copy(buffer.begin(),buffer.end(),ostreambuf_iterator<char>(bmpfile)); // Wrting data to file

        cout << "File saved!\n";

        bmpfile.close();
    }
    else
    {
        cout << "Could not open output file!\n";
        return -100;
    }
    cout << "Execution of WriteBMP complete!\n------------------------------\n";
    return 0;
}

