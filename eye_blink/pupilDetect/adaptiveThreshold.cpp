#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include"cv.h"
#include <iostream>
#include<stdio.h>


using namespace std;
using namespace cv;
int main(int argc,char *argv[])
{
	Mat img= imread(argv[1],0);
	Mat t1,t2,t3;
	
	imshow("Left",img);
	waitKey(0);
	equalizeHist(img,t1);
	imshow("AT",t1);
	Mat element=getStructuringElement(MORPH_RECT,Size(3,3));
	//dilate(t1,t1,element,Point(-1,-1),4);
	

	threshold(t1,t2,100,255,CV_THRESH_BINARY);
	
	imshow("threshold",t2);
		waitKey(0);
	imwrite("t.png",t2);
	//dilate(at,at,element,Point(-1,-1),4);
	//imshow("Dilated",at);
	
	//adaptiveThreshold(t1,t2,255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,5,2);
	
	
	Canny(t1,t3,50,50);
	imshow("AT2",t3);
	waitKey(0);
	
	
	
	
}
