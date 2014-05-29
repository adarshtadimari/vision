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

float storedHogFeatures[225][9]={0};
void drawLine(Mat img,Point p,int bin,int magnitude)    //bin number from 0 to 8
{
    line(img,Point(p.x-4*cos(float(bin*PI/9)),p.y+4*sin(float(bin*PI/9))),Point(p.x+4*cos(float(bin*PI/9)),p.y-4*sin(float(bin*PI/9))),magnitude,1);    
}

void drawrhog(Mat image)
{
    Mat img= Mat::zeros(128,128,CV_8U);
    //drawLine(img,Point(img.rows/2,img.cols/2),2,255);
    for(int i=0;i<225;i++)
    {
        int px= 8+(i%15)*8;
        int py= 8+(int)(i/15)*16;
        for(int j=0;j<9;j++)
        {

            drawLine(img,Point(px,py),j,(int)255*storedHogFeatures[i][j]);
        }

    }
    
    
    imshow("drawhog",img);

    imshow("image",image);
    waitKey(0);
}

int main(int argc,char *argv[])
{
    Mat image = imread(argv[1],0);
    Mat imageData;
    imshow("Image",image);
    waitKey(0);
    resize(image,imageData,Size(128,128));

    HOGDescriptor hog(Size(128, 128),Size(16, 16),Size(8, 8),Size(8, 8),9,-1,0.2,true,64);
    vector<float> featureVector;
    featureVector.clear();
    vector<Point> locations;
    hog.compute(imageData, featureVector, Size(8,8), Size(0,0), locations);
    float max=0,min=1;
    float sum=0;
    int blockSize = 36;
    int a[105]={0};
    float innersum[9]={0};
    /*for (unsigned int feature = 0; feature < featureVector.size(); ++feature) 
    {
        cout << " " << (feature + 1) << ":" << featureVector.at(feature);
    }
    */
    
    //cout<<"\n\n";
    for(int i=0;i<225;i++)
    {   
        for(int j=0;j<9;j++)
        {
            innersum[j]=0;
        }
        for(int j=0; j<36;j++)
        {
            
            //cout<<" " <<i*36+1+j<<":"<<featureVector.at(i*36+j);
            //innersum[j%9]+=featureVector.at(i*36+j)*featureVector.at(i*36+j);
            storedHogFeatures[i][j%9]+=featureVector.at(i*36+j)*featureVector.at(i*36+j);
   
        }
       /* 
        for(int j=0;j<9;j++)
        {
            storedHogFeatures[i][j]=innersum[j];
            
            //cout<<j<<"::"<<innersum[j]<<"\n";
            if(innersum[j]>max)
                max=j;
        }
       // cout<<"max:"<<max<<";"; 
        */
    }
    drawrhog(imageData); 
}

