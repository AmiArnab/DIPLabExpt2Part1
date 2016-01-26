#include "readbmp.h"
int ReadBMP(char *filename, BMPImage *image)
{
    fstream bmpfile;
    BMPImage::BITMAPFILEHEADER fh;
    BMPImage::BITMAPINFOHEADER fi;
    bmpfile.open(filename,ios_base::in|ios_base::binary);
    if(bmpfile.is_open())
    {
        cout << "Input file "<< filename << " opened successfully!\n";
        //------Reading data from file---------
        vector<unsigned char> buffer((std::istreambuf_iterator<char>(bmpfile)),(std::istreambuf_iterator<char>()));
        //------ Parsing BMPFILEHEADER---------
        memcpy(&fh,buffer.data(),14);
        image->SetBMPFileHeader<BMPImage::RGB>(fh);
        //------ Parsing BMPINFOHEADER--------
        memcpy(&fi,buffer.data()+14,40);
        image->SetBMPInfoHeader<BMPImage::RGB>(fi);

        //------ Parsing BMP Image Data ------
        vector<unsigned char>::const_iterator first = buffer.begin()+54;
        vector<unsigned char>::const_iterator last = buffer.end();
        vector<unsigned char> bmpdata(first, last);

        //------Creating the data matrix to store image data-------
        unsigned char***imgdata = new unsigned char** [fi.biHeight];
        for(int i=0;i<fi.biHeight;++i)
        {
            *(imgdata+i) = new unsigned char* [fi.biWidth];
            for(int j=0;j<fi.biWidth;++j)
            {
                *(*(imgdata+i)+j) = new unsigned char [3];
            }
        }

        int k = 0;

        for(int i = 0;i<fi.biHeight;i++)
        {
            for(int j = 0;j<fi.biWidth;j++)
            {
                imgdata[i][fi.biWidth-j-1][0] = bmpdata.at(k); //B
                imgdata[i][fi.biWidth-j-1][1] = bmpdata.at(k+1); //G  // Copying image data to 3d matrix
                imgdata[i][fi.biWidth-j-1][2] = bmpdata.at(k+2); //R
                k = k+3;
            }
        }
        cout << "Image data copied!\n";
        try //-----Setting BMP RGB image data-----------
        {
            image->SetImageData<BMPImage::RGB>(imgdata);
        }
        catch(int e)
        {
            cout << "Error code " << e << endl;
            return -100;
        }
        try //----Setting BMP RGB file header---------
        {
            image->SetBMPFileHeader<BMPImage::RGB>(fh);
        }
        catch(int e)
        {
            cout << "Error code " << e << endl;
            return -100;
        }
        try //----Setting BMP RGB file info header--------
        {
            image->SetBMPInfoHeader<BMPImage::RGB>(fi);
        }
        catch(int e)
        {
            cout << "Error code " << e << endl;
            return -100;
        }
        cout << "Parsing complete!\nClosing input file...\n";
        bmpfile.close();
    }
    else
    {
        cout << "Error opening input file!\n";
        return -100;
    }
    cout << "Execution of ReadBMP complete!\n------------------------------\n";
    return 0;
}

