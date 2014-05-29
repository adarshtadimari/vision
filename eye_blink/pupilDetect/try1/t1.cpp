#include"cv.h"
#include"highgui.h"

using namespace cv;
int main(int argc,char *argv[])
{
	Mat img=imread(argv[1],0);
	Mat xder,yder,t1,t2;
	Sobel(img,xder,CV_32F,1,0,3);
	Sobel(img,yder,CV_32F,0,1,3);
	
	//t1=xder+yder;
	
	imshow("Eye",img);
	imshow("X",xder);
	normalize(xder,xder,0,1,NORM_MINMAX);
	imshow("X_norm", xder);
	imshow("Y",yder);
	//imshow("X+Y",t1);
	cvWaitKey(0);
}
