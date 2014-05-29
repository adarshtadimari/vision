#include"cv.h"
#include"highgui.h"

CvPoint a,b;
int count=0;



void on_mouse( int event, int x, int y, int flags, void* param )
{
        //Select mouse Event

	if(event==CV_EVENT_LBUTTONDOWN)
    {
        a=cvPoint(x,y);
        count++;
	}

    else if(event==CV_EVENT_LBUTTONDOWN&&count==1)
	{
	    b=cvPoint(x,y);
	    count++;
	}

	else if(event == CV_EVENT_MOUSEMOVE  &&  flags & CV_EVENT_FLAG_LBUTTON)

	{
	}

}

int main(int argc,char* argv[])
{
    IplImage* img= cvLoadImage("../pics/A/001.jpg");
    IplImage* temp=cvCreateImage(cvSize(img->width,img->height),8,3);
    cvCopy(img,temp);
    cvNamedWindow("Demo",CV_WINDOW_AUTOSIZE);
    cvSetMouseCallback("Demo",&on_mouse,0);
    
    while(1)
    {   
    
    
        cvCopy(img,temp);
        cvShowImage("Demo",temp);
        if(count==2)
        {
            cvSetImageROI(temp, cvRect(a.x,a.y,b.x-a.x,b.y-a.y));  
            break;
        }
        
    }
    cvShowImage("Cropped",temp);
    cvWaitKey(0);    
    
}


