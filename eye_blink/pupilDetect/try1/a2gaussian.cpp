#include"cv.h"
#include"highgui.h"
using namespace cv;
int DISTANCETHRESHOLD=101;
void MyFilledCircle( Mat img, Point center )
{
 int thickness = -1;
 int lineType = 8;

 circle( img,
         center,
         1,
         Scalar( 0, 255, 0 ),
         thickness,
         lineType );
}
int main(int argc,char *argv[])
{
	Mat img1=imread(argv[1]),img;
	cvtColor(img1,img,CV_BGR2GRAY);
	Mat inv,gau;
	inv=255-img;
	double minValue,maxValue;
	Point minLoc,maxLoc;
	GaussianBlur(inv,gau,Size(DISTANCETHRESHOLD,DISTANCETHRESHOLD),0,0);
	minMaxLoc(gau,&minValue,&maxValue,&minLoc,&maxLoc);
	MyFilledCircle(img1,maxLoc);
	imshow("src",inv);
	imshow("blur",gau);
	imshow("IMage",img1);
	imwrite("i.jpg",gau);
	waitKey(0);
}
