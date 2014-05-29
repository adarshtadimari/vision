#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>

using namespace cv;
using namespace std;

#define szoom 1
#define ezoom 1.01


int main(int argc,char *argv[])
{
    IplImage* panto= cvLoadImage("min.jpg",0);
    IplImage* frame= cvLoadImage(argv[1],0);
    float zoom=szoom,startzoom=szoom,endzoom=ezoom;
    int width= 640;
    int height= 480;
    float w=width,h;
    IplImage* andimg=cvCreateImage(cvSize(640,480),8,1);
    IplImage* minimg=cvCreateImage(cvSize(640,480),8,1);

    int count=640*480;
    int count1=0;
    
    while(zoom<=endzoom)
    {
        w*=zoom;
        IplImage* resized=cvCreateImage(cvSize(w,480),8,1);
        cvResize(panto,resized);
        cvShowImage("Zoom",resized);

        
        
        
        int roisize=640;
        int i;
        int min=480*640;
        
           
            for(i=0;i<=w-roisize;i+=10)
            {
                
                cvSetImageROI(resized,cvRect(i,0,roisize,480));
                cvThreshold(resized, resized, 128, 255, CV_THRESH_BINARY_INV);
                cvShowImage("Resized",resized);
                cvXor(frame,resized,andimg);
                count=cvCountNonZero(andimg);
                
                cvThreshold(resized, resized, 128, 255, CV_THRESH_BINARY_INV);
                
                if(count<min)
                {
                    min=count;
                    cvCopy(resized,minimg);
                    
                }
                
         //               cvWaitKey(0);
                
                cvResetImageROI(resized);
                cout<<count<<"\n";
            }
            
        
        
      
        cvReleaseImage(&resized);    
        zoom+=0.001;
        
    }    
    
    cvShowImage("min",minimg);
    cvSaveImage("minfinal.jpg",minimg);
    cvWaitKey(0);
    
    
}

