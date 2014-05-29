#include"opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc,char *argv[])
{
    Mat img=imread(argv[1]);
    Mat resized;
    Mat translated;
    unsigned pos;
    string filename(argv[1]);
    string subname;
    string cname;

    pos=filename.find(".jpg");
    subname=filename.substr(0,pos);
    
    
    //Resize it to 128x128
    resize(img,resized,Size(128,128));
     
    //Top left 120*120
    translated=resized(Rect(0,0,120,120));
    cname=subname+"tl.jpg";
    imwrite(cname,translated);
    
    //Top right 120*120
    translated=resized(Rect(8,0,120,120));
    cname=subname+"tr.jpg";
    imwrite(cname,translated);
    
    //Bottom Left 
    translated=resized(Rect(0,8,120,120));
    cname=subname+"bl.jpg";
    imwrite(cname,translated);

    //Bottom Right
    translated=resized(Rect(8,8,120,120));
    cname=subname+"br.jpg";
    imwrite(cname,translated);
    
    //Center 
    translated=img(Rect(4,4,120,120));
    cname=subname+"c.jpg";
    imwrite(cname,translated);
    
 

    
    //imshow("resized",resized);
    //imwrite("resized.jpg",resized);
    //waitKey(0);
    



}
