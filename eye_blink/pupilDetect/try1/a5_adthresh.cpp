#include"cv.h"
#include"highgui.h"
#include<iostream>
using namespace cv;

Mat threshImage,img;
int levels=50;
int blockSize=3;

static void on_trackbar(int, void*)
{
 
    int _constant = levels-100 ;
    int _blockSize = blockSize ;
    
	adaptiveThreshold(img,threshImage,255,ADAPTIVE_THRESH_GAUSSIAN_C
,THRESH_BINARY,_blockSize*2+1,_constant);
    imshow("Threshold",threshImage);
}

int main(int argc,char *argv[])
{
	img=imread(argv[1],0);
	equalizeHist(img,img);
	
	namedWindow("contours",CV_WINDOW_NORMAL);
	imshow("Image",img);
	
	createTrackbar( "constant-100", "contours", &levels, 200, on_trackbar );
	createTrackbar( "blockSize", "contours", &blockSize, 201, on_trackbar );

    on_trackbar(0,0);
	waitKey(0);

	
	
	
	
}
