#include"cv.h"
#include"highgui.h"

using namespace cv;
int main()
{
	
	Mat m= Mat::Mat(Size(3,4),CV_32F,);
	printf("%f %f",m.at<float>(2,3),m.at<float>(3,2));
}
