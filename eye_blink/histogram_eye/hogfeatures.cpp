#include <stdio.h>
#include <dirent.h>
#include <ios>
#include <fstream>
#include <stdexcept>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using namespace std;
using namespace cv;

int main(int argc,char *argv[])
{
    Mat image = imread(argv[1],0);
    Mat imageData;
    imshow("Image",image);
    waitKey(0);
    resize(image,imageData,Size(64,128));

    HOGDescriptor hog(Size(64, 128),Size(16, 16),Size(8, 8),Size(8, 8),9,-1,0.2,true,64);
    vector<float> featureVector;
    featureVector.clear();
    vector<Point> locations;
    hog.compute(imageData, featureVector, Size(8,8), Size(0,0), locations);
    float max=0,min=1;
    float sum=0;
    int blockSize = 36;
    int a[105]={0};
    float innersum[9]={0};
    for (unsigned int feature = 0; feature < featureVector.size(); ++feature) 
    {
        cout << " " << (feature + 1) << ":" << featureVector.at(feature);
    }
    
    cout<<"\n\n";
    for(int i=0;i<105;i++)
    {   
        for(int j=0;j<9;j++)
        {
            innersum[j]=0;
        }
        for(int j=0; j<36;j++)
        {
            
            cout<<" " <<i*36+1+j<<":"<<featureVector.at(i*36+j);
            innersum[j%9]+=featureVector.at(i*36+j);
            
        } 
        for(int j=0;j<9;j++)
        {
            cout<<j<<"::"<<innersum[j]<<"\n";
            if(innersum[j]>max)
                max=j;
        }
        cout<<"max:"<<max<<";"; 

    }
    cout<<"hello";
    
}

