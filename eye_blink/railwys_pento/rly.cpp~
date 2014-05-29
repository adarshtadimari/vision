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
#define ezoom 1.50
#define sti 0
#define ei 450
#define plx 99.0
#define ply 27.0
#define prx 487.0
#define pry 23.0

#define actualw 100

#define mode 2

#define frameoffset 25*938

float distan[2048];
uint16_t t_gamma[2048];
uint16_t inv_t_gamma[10000] = {0};




int main(int argc,char *argv[])
{
        IplImage* panto = cvLoadImage("t2.jpg", 0);
        
        IplImage* mask = cvLoadImage("m1.jpg",0);
        
        
        float startzoom = stzoom, endzoom = ezoom, zoom=stzoom, minzoom;
        int width = pwidth, height = pheight;
        int w,h;
        int starti = 0, endi = 450;
        IplImage* white = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage* operand = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage*  andimg = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage* minimage = cvCreateImage(cvSize(640, 480), 8, 1);
        cvSet(white, CV_RGB(255, 255, 255));
        int min = 640*480, mini = 0;
        
        while(zoom <= endzoom)
        {
			w = width * zoom;
			h = height * zoom;
			IplImage* resized = cvCreateImage(cvSize(w, h), 8, 1);
			cvResize(panto, resized);
			
			CvRect roi = cvRect(w/2 - 320, 0, 640, h);

			cvSetImageROI(resized, roi);
			
			cvShowImage("Zoom",resized);
			cvWaitKey(0);
			

			
			int i;
			for(i=starti; i<endi; i++)
			{
				int tf = 0;
				cvCopy(white, operand);
				if(i+h > 480)
				{
					tf = 1;
					cvSetImageROI(operand, cvRect(0, i, 640, 480-i));
					cvSetImageROI(resized, cvRect(w/2 - 320, 0, 640, 480-i));
					
					}
				else
					cvSetImageROI(operand, cvRect(0, i, 640, h));
				cvCopy(resized, operand);
				
                				
					
				cvResetImageROI(operand);
				
				if(tf)
					cvResetImageROI(resized);
				//cvThreshold(mask, mask, 128, 255, CV_THRESH_BINARY_INV);
				cvXor(mask, operand, andimg);
				cvThreshold(mask, mask, 128, 255, CV_THRESH_BINARY_INV);
				int count = cvCountNonZero(andimg);
			    cout<<" "<<count<<" ";	
				if(count < min)
				{
					min = count;
					mini = i;
					minzoom = zoom;
					cvCopy(operand, minimage);
				}
			
			}
            
	    	cvResetImageROI(resized);
			cvReleaseImage(&resized);
			zoom += 0.01;
			cout<<"\n";
		}
        cout<<min;
        cvShowImage("minimage",minimage);
        cvSaveImage("min.jpg",minimage);

}

