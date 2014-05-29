#include"cv.h"
#include"highgui.h"

int main(int argc, char* argv[])
{
    int i;
    IplImage* panto=cvLoadImage(argv[2],0);
    IplImage* img= cvLoadImage(argv[1],0);
    IplImage* full = cvCreateImage(cvSize(800,480),8,1);
    IplImage* andimg=cvCreateImage(cvSize(640,480),8,1);
    IplImage* finimg=cvCreateImage(cvSize(640,480),8,1);
    cvSet(full,CV_RGB(255,255,255));
    cvThreshold(panto, panto, 128, 255, CV_THRESH_BINARY_INV);
    cvSetImageROI(full,cvRect(80,0,640,480));
    cvCopy(img,full);
    cvResetImageROI(full);
    
    cvShowImage("Panto inverse",panto);
    cvShowImage("Full",full);
    //cvWaitKey(0);
    int count,max=0;   
    for(i=0;i<=160;i++)
    {
        cvSetImageROI(full,cvRect(i,0,640,480));
        cvShowImage("Move",full);
        //cvWaitKey(50);
        cvXor(full,panto,andimg);
        count=cvCountNonZero(andimg);
        
        if(count>max)
        {
            max=count;
            cvCopy(full,finimg);
        }
               cvResetImageROI(full);
        
                      
        
    
    }    
    
    cvShowImage("finalImage",finimg);
    //cvWaitKey(0);
    cvSaveImage("min2.jpg",finimg);



}
