#include"cv.h"
#include"highgui.h"

int main(int argc,char* argv[])
{
    IplImage* img=cvLoadImage("min2.jpg",0);
    IplImage * panto=cvLoadImage(argv[1],0);
    IplImage * colour=cvCreateImage(cvSize(640,480),8,3);
    int x,y;
    for(y=0;y<img->height;y++)
    {
        uchar *ptr=(uchar*)(img->imageData + y*img->widthStep);
        uchar *ptr2=(uchar*)(panto->imageData + y*panto->widthStep);
        uchar *ptr3=(uchar*)(colour->imageData + y*colour->widthStep);
        
        for(x=0;x<img->width;x++)
        {
            if(ptr[x]==0)
            {
                ptr3[3*x]=0;
                ptr3[3*x+1]=255;
                ptr3[3*x+2]=0;
                
            }
            else
            {
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
    
    }
cvSaveImage("coloured.jpg",colour);
cvShowImage("coloured",colour);
cvWaitKey(0);
}


    
    
