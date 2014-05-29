#include"opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc,char *argv[])
{
    Mat img=imread(argv[1]);
    Mat imgHSV;
    Mat imgC;
    Mat imgCreshaped;
    Mat reshaped;
    stringstream s;
    cvtColor(img,imgHSV,COLOR_BGR2HSV);
    //cout<<imgHSV;
    double spower,vpower;
    Mat imgfloat; 
    imgHSV.convertTo(imgfloat,CV_32F,1.0/255);
    //cout<<imgfloat;
    string filename(argv[1]);
    string subname;
    string cname;
    int pos=filename.find(".jpg");
    subname=filename.substr(0,pos);
 

    char count='a'; 
    for(spower=0.5;spower<=1.5;spower+=0.5)
    for(vpower=0.5;vpower<=1.5;vpower+=0.5)
    {
        
        reshaped=imgfloat.reshape(1,imgHSV.rows*imgHSV.cols);
        reshaped.copyTo(imgC);
        cv::pow(reshaped.col(1),spower,imgC.col(1));
        cv::pow(reshaped.col(2),vpower,imgC.col(2));
        imgCreshaped=imgC.reshape(3,imgHSV.rows);
        imgCreshaped.convertTo(imgCreshaped,CV_8U,255.0);
        cvtColor(imgCreshaped,imgCreshaped,COLOR_HSV2BGR);  
      // imshow("imgRe",imgCreshaped);
      // waitKey(0);
        s.str(std::string());
        s<<count;
        count++;
        cname=subname+s.str()+".jpg";
        imwrite(cname,imgCreshaped);
    }
    


}
