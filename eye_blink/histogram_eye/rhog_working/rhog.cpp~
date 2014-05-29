#include <stdio.h>
#include <dirent.h>
#include <ios>
#include <fstream>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include<math.h>
using namespace std;
using namespace cv;
#define PI 3.14159625

void drawLine(Mat img,Point p,int bin,int magnitude)    //bin number from 0 to 8
{
    line(img,Point(p.x-4*cos(float(bin*PI/9+PI/2)),p.y+4*sin(float(bin*PI/9+PI/2))),Point(p.x+4*cos(float(bin*PI/9+PI/2)),p.y-4*sin(float(bin*PI/9+PI/2))),magnitude,1);    
}

Mat drawrhog(Mat image)
{
    float storedHogFeatures[225][9]={0};
    Mat imageData;
    resize(image,imageData,Size(128,128));
    HOGDescriptor hog(Size(128, 128),Size(16, 16),Size(8, 8),Size(8, 8),9,-1,0.2,true,64);
    vector<float> featureVector;
    featureVector.clear();
    vector<Point> locations;
    hog.compute(imageData, featureVector, Size(8,8), Size(0,0), locations);
    for(int i=0;i<225;i++)
        for(int j=0; j<36;j++)
           storedHogFeatures[i][j%9]+=featureVector.at(i*36+j)*featureVector.at(i*36+j);

    Mat img= Mat::zeros(128,128,CV_8U);
    int px,py;
    for(int i=0;i<225;i++)
    {
        py= 8+(i%15)*8;
        px= 8+(int)(i/15)*8;
        for(int j=0;j<9;j++)
        {
            drawLine(img,Point(px,py),j,round(255*sqrt(storedHogFeatures[i][j])));
            //cout<<storedHogFeatures[i][j]<<endl;
            //imshow("image",img);
            //waitKey(0);
        }
    }
    normalize(img,img,0,255,NORM_MINMAX);
    return img;
    
}

/*int main(int argc,char *argv[])
{
    Mat image = imread(argv[1],0);
    imshow("hog",drawrhog(image)); 
    waitKey(0);
}*/

