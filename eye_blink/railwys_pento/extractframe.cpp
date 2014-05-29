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


#define videofile "video_kin.avi"
int main()
{
    
    CvCapture *capture = cvCreateFileCapture("video_kin.avi");
    
    
    cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, 25);
    printf("Hello");
    IplImage* frame;
    char c=0;
    
    while(c!='q')
    {
        frame=cvQueryFrame(capture);    
        cvShowImage("video",frame);
        c=cvWaitKey(33);
       
    }
    
    cvReleaseCapture(&capture);
    
}

