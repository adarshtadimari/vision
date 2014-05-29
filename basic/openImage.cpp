
#include "opencv2/highgui.hpp"
#include<iostream>
using namespace cv;
using namespace std;

int main(int argc,char* argv[])
{
	
	cout<<"Usage: ./openImage [filename] [grayscale]\n";
	Mat src;
	if(argc==1)
		src=imread("lena.jpg");
	else if(argc==2)
		src=imread(argv[1]);
	else if(argc==3&&atoi(argv[2])==1)
		src=imread(argv[1],0);
	else if(argc==3)
		src=imread(argv[1]);
	
	
	namedWindow("Source",WINDOW_NORMAL);
	imshow("Source",src);
	waitKey(0);
}
