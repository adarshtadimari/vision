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

#define videofile "/home/vignesh/Videos/run2/video_kin.avi"
#define rgbfile "/home/vignesh/Videos/run2/video.avi"

#define videotimefile "/home/vignesh/Videos/run2/videotime.txt"
#define gpstimefile "/home/vignesh/Videos/run2/gpstime.txt"
#define csvfile "data3.csv"

#define pantofile "t2.jpg"
#define pwidth 640
#define pheight 144
#define stzoom 1.00
#define ezoom 1.5
#define sti 0
#define ei 450
#define plx 99.0
#define ply 26.0
#define prx 500.0
#define pry 22.0

#define actualw 100

#define mode 2

#define frameoffset 25*938

float distan[2048];
uint16_t t_gamma[2048];
uint16_t inv_t_gamma[10000] = {0};
IplImage* minimage;
IplImage* mask;
IplImage* panto;
IplImage* finimg;
char saveend[20];

void vertical();
void shift();
void colour();
int teplx=plx,teply=ply,teprx=prx,tepry=pry;


int main(int argc,char *argv[])
{
    panto = cvLoadImage("t2.jpg", 0);
    mask = cvLoadImage(argv[1],0);
    strcpy(saveend,argv[1]);
    vertical();
    shift();
    colour();
}


void vertical()
{
        int templx=plx,temply=ply,temprx=prx,tempry=pry;
        int mplx=plx,mply=ply,mprx=prx,mpry=pry;       
        float startzoom = stzoom, endzoom = ezoom, zoom=stzoom, minzoom;
        int width = pwidth, height = pheight;
        int w,h;
        int starti = 0, endi = 450;
        IplImage* white = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage* operand = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage*  andimg = cvCreateImage(cvSize(640, 480), 8, 1);
        minimage = cvCreateImage(cvSize(640, 480), 8, 1);
        cvSet(white, CV_RGB(255, 255, 255));
        int min = 640*480, mini = 0;
        
        while(zoom <= endzoom)
        {
            templx=plx;
            temply=ply;
            temprx=prx;
            tempry=pry;
			w = width * zoom;
			h = height * zoom;
			IplImage* resized = cvCreateImage(cvSize(w, h), 8, 1);
			cvResize(panto, resized);
			templx*=zoom;
			temply*=zoom;
			temprx*=zoom;
			tempry*=zoom;
			
			CvRect roi = cvRect(w/2-320, 0, 640, h);

			templx-=(w/2)-320;
			temprx-=(w/2)-320;
			cvSetImageROI(resized, roi);
			
			//cvShowImage("Zoom",resized);
			//cvWaitKey(0);
			
            int tempilx,tempily,tempirx,tempiry;
			
			
			int i;
			for(i=starti; i<endi; i++)
			{
				tempilx=templx;
				tempily=temply;
				tempirx=temprx;
				tempiry=tempry;
				
				int tf = 0;
				cvCopy(white, operand);
				if(i+h > 480)
				{
				    
					tf = 1;
					cvSetImageROI(operand, cvRect(0, i, 640, 480-i));
					cvSetImageROI(resized, cvRect(w/2 - 320, 0, 640, 480-i));
					
					}
				else
					{
					    cvSetImageROI(operand, cvRect(0, i, 640, h));
				        }
				cvCopy(resized, operand);
				    tempily+=i;
    			    tempiry+=i;
                    				
					
				cvResetImageROI(operand);
				
				if(tf)
					cvResetImageROI(resized);
				//cvThreshold(mask, mask, 128, 255, CV_THRESH_BINARY_INV);
				cvXor(mask, operand, andimg);
				//cvThreshold(mask, mask, 128, 255, CV_THRESH_BINARY_INV);
				int count = cvCountNonZero(andimg);
			    //cout<<" "<<count<<" ";	
				if(count < min)
				{
					min = count;
					mini = i;
					minzoom = zoom;
					cvCopy(operand, minimage);
					mplx=tempirx;
					mply=tempiry;
					mprx=tempilx;
					mpry=tempily;
				}
			
			}
            
	    	cvResetImageROI(resized);
			cvReleaseImage(&resized);
			zoom += 0.01;
			//cout<<"\n";

		}
        //cout<<min;
        IplImage* tempmin=cvCreateImage(cvSize(640,480),8,1);
        cvCopy(minimage,tempmin);
        cvCircle(tempmin,cvPoint(mplx,mply), 30, CV_RGB(0,0,0), 20, 8, 0);
        cvCircle(tempmin,cvPoint(mprx,mpry), 30, CV_RGB(0,0,0), 20, 8, 0);
        //cout<<mplx<<','<<mply<<'\n';
        //cout<<mprx<<','<<mpry;
        //cvShowImage("minimage",tempmin);
        //cvWaitKey(0);
        teplx=mplx;
        teply=mply;
        teprx=mprx;
        tepry=mpry;

}

void shift()
{
    int templx=teplx,temply=teply,temprx=teprx,tempry=tepry;
    
    int i;
    IplImage* panto=cvCreateImage(cvSize(640,480),8,1);
    IplImage* img= cvCreateImage(cvSize(640,480),8,1);
    cvCopy(minimage,img);
    cvCopy(mask,panto);
    IplImage* full = cvCreateImage(cvSize(800,480),8,1);
    IplImage* andimg=cvCreateImage(cvSize(640,480),8,1);
    finimg=cvCreateImage(cvSize(640,480),8,1);
    cvSet(full,CV_RGB(255,255,255));
    cvThreshold(panto, panto, 128, 255, CV_THRESH_BINARY_INV);
    cvSetImageROI(full,cvRect(80,0,640,480));
    cvCopy(img,full);
    cvResetImageROI(full);
    
    templx+=80;
    temprx+=80;
    //cvShowImage("Panto inverse",panto);
    //cvShowImage("Full",full);
    //cvWaitKey(0);
    int ttlx,ttly,ttrx,ttry,mlx,mly,mrx,mry;
    int count,max=0;   
    for(i=0;i<=160;i++)
    {
        ttlx=templx;
        ttrx=temprx;
        cvSetImageROI(full,cvRect(i,0,640,480));
        //cvShowImage("Move",full);
        //cvWaitKey(50);
        ttlx-=i;
        ttrx-=i;
        cvXor(full,panto,andimg);
        count=cvCountNonZero(andimg);
        
        if(count>max)
        {
            max=count;
            cvCopy(full,finimg);
            mlx=ttlx;
            mrx=ttrx;
            
        }
               cvResetImageROI(full);
        
                      
        
    
    }    
    
  //  cvShowImage("finalImage",finimg);
    //cvWaitKey(0);
    teplx=mlx;
    teprx=mrx;
   
    
}

void colour()
{
    IplImage* img=cvCreateImage(cvSize(640,480),8,1);
    IplImage* panto=cvCreateImage(cvSize(640,480),8,1);
    cvCopy(mask,panto);
    cvCopy(finimg,img);
    IplImage * colour=cvCreateImage(cvSize(640,480),8,3);
    int x,y;
    
    
    for(y=0;y<img->height;y++)
    {
        uchar *ptr=(uchar*)(img->imageData + y*img->widthStep);
        uchar *ptr2=(uchar*)(panto->imageData + y*panto->widthStep);
        uchar *ptr3=(uchar*)(colour->imageData + y*colour->widthStep);
        
        for(x=0;x<img->width;x++)
        {
            /*
            if(ptr[x]==0)
            {
                ptr3[3*x]=0;
                ptr3[3*x+1]=255;
                ptr3[3*x+2]=0;
                
            }
            */
                if(ptr2[x]==0)
                {   
                    ptr3[3*x]=255;
                    ptr3[3*x+1]=255;
                    ptr3[3*x+2]=255;
                
                    
                }
                else
                {
                    ptr3[3*x]=0;
                    ptr3[3*x+1]=0;
                    ptr3[3*x+2]=0;
                
                
                }
            
            
        }
    }   
    
    
    cvCircle(colour,cvPoint(teplx,teply), 5, CV_RGB(255,0,0), 2, 8, 0);
    cvCircle(colour,cvPoint(teprx,tepry), 5, CV_RGB(255,0,0), 2, 8, 0);
    
    char save[50]="save/";
    strcat(save,saveend);
    //cout<<save;
    cvSaveImage(save,colour);    
    cvSaveImage("coloured.jpg",colour);
    cvShowImage("coloured",colour);
    cvWaitKey(0);

}

