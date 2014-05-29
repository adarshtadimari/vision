#include"opencv2/opencv.hpp"
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace cv;
using namespace std;

int main(int argc,char *argv[])
{
    Mat img=imread(argv[1]);
    Mat projected;
    float c1,c2,c3;
    //cout<<img.cols;
    Mat reshaped=img.reshape(1,img.rows*img.cols);
    
    //cout<<reshaped;
    PCA pca(reshaped,Mat(),CV_PCA_DATA_AS_ROW,3);
    projected=pca.project(reshaped);
    //cout<<projected;

    //Multiplying the projection of each patch pixel onto principal components
    Mat mCompImage;
    Mat reconImage,rIrounded;
        
    
    //Creating 12 new images
    string filename(argv[1]);
    string subname;
    string cname;
    stringstream s; 
    int pos=filename.find(".jpg");
    subname=filename.substr(0,pos);
 
    int count=0;
    
    for(float c1=0.5;c1<=2;c1+=0.5)
    for(float c2=0.5;c2<=2;c2+=0.5)
    for(float c3=0.5;c3<=2;c3+=0.5)
    {
        count++;
        projected.copyTo(mCompImage);
        mCompImage.col(0)=projected.col(0)*c1;
        mCompImage.col(1)=projected.col(1)*c2;
        mCompImage.col(2)=projected.col(2)*c3;
        reconImage=pca.backProject(mCompImage);
        Mat reconImageReshaped=reconImage.reshape(3,img.rows);
        reconImageReshaped.convertTo(rIrounded,CV_8U);
        s.str(std::string());
        s<<count;
        //Saving it onto the file
        cname=subname+s.str()+".jpg";
        
        imwrite(cname,rIrounded);

    }
    
    //cout<<reconImageReshaped;
    //imshow("recon",rIrounded);
    //waitKey(0);
    



}
