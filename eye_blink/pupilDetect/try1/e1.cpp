#include<stdio.h>
#include"cv.h"
#include"highgui.h"
using namespace cv;
int main(int argc,char *argv[])
{
  Mat img= imread(argv[1]);
  imshow("Image",img);
  printf("Hello World");
  waitKey(0);
}

