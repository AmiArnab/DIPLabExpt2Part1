#include <iostream>
#include <string>
#include <core.hpp>
#include <highgui.hpp>
#include <cv.hpp>

using namespace std;
using namespace cv;

int main(int argc,char *argv[])
{
    cout << "Starting program..." << endl;

    int hist[256];
    int cumulhist[256];
    int eqhist[256];

    if(argc!=3)
    {
        cout << "Invalid number of arguments!\n";
        return 1;
    }

    cout << "Initializing the arrays...\n";

    for(int i = 0;i<256;++i)
    {
        hist[i] = 0;
        cumulhist[i] = 0;
        eqhist[i] = 0;
    }

    cout << "Reading the input file...\n";
    Mat input = imread(argv[1]);

    if(input.empty())
    {
        cout << "Error reading input file!\nClosing program.\n";
        return 1;
    }
    else
    {
        if(input.type() == CV_8UC3 || input.type() == CV_8UC4)
        {
            cout << "Image is RGB coloured, converting to grayscale...\n";
            cvtColor(input,input,CV_BGR2GRAY);
        }

        Mat output;

        input.copyTo(output);

        int height = input.rows;
        int width = input.cols;

        cout << "Creating the histogram of the input image...\n";

        for(int i = 0;i<height;++i)
        {
            for(int j = 0;j<width;++j)
            {
                hist[(int)input.at<uchar>(i,j)]++;
            }
        }

        cout << "Creating the cumulative histogram...\n";

        for(int i = 0;i<256;++i)
        {
            if(i==0)
            {
                cumulhist[0] = hist[0];
            }
            else
            {
                cumulhist[i] = cumulhist[i-1]+hist[i];
            }
        }

        cout << "Performing equalization...\n";

        for(int i=0;i<256;i++)
        {
            eqhist[i] = (cumulhist[i]*255)/(height*width);
        }

        cout << "Creating the output...\n";

        for(int i = 0;i<height;++i)
        {
            for(int j = 0;j<width;++j)
            {
                output.at<uchar>(i,j) = (uchar)eqhist[(int)input.at<uchar>(i,j)];
            }
        }

        Mat inhistplot(200,256,CV_8UC3);
        Mat outhistplot;
        inhistplot.copyTo(outhistplot);

        for(int i = 0; i < 256; i++)
        {
            int inmag = hist[i];
            int outmag = eqhist[i];
            line(inhistplot,Point(i,inhistplot.rows-1),Point(i,inhistplot.rows-1-inmag/100),Scalar(255,0,0));
            line(outhistplot,Point(i,outhistplot.rows-1),Point(i,outhistplot.rows-1-outmag/100),Scalar(255,0,0));
        }

        imshow("Original (Converted to Gray)",input);
        imshow("Equalized",output);
        imshow("Input Hist",inhistplot);
        imshow("Output Hist",outhistplot);

        imwrite(argv[2],output);
        imwrite("InputHist.jpg",inhistplot);
        imwrite("OutputHist.jpg",outhistplot);

        cout << "Press ESC to exit, while the image windows are open.\n";

        while(int key = waitKey(1000))
        {
            if(key == 27){
                exit(0);
            }
        }

        return 0;
    }
}
