#include"cv.h"
#include"highgui.h"


using namespace cv;
using namespace std;
Mat xder,yder,t1,t2,con,img;

float computedot(int x,int y)
{
	
}


int main(int argc,char *argv[])
{
	img=imread(argv[1],0);
	Mat inv=255-img;
	int i1,j1,i2,j2;
	Mat m= Mat::zeros(img.rows,img.cols,CV_32F);
	Mat vx= Mat::zeros(img.rows,img.cols,CV_32F);
	Mat vy= Mat::zeros(img.rows,img.cols,CV_32F);
	Point maxP;
	
	
	
	Sobel(img,xder,CV_32F,1,0,3);
	Sobel(img,yder,CV_32F,0,1,3);
	equalizeHist(inv,inv);
	threshold(inv,inv,150,255,CV_THRESH_BINARY);
	vector<vector<Point> > contours;
  	vector<Vec4i> hierarchy;
	
	//t1=xder+yder;
	imshow("inv",inv);
	imshow("Eye",img);
	imshow("X",xder);
	//normalize(xder,xder,0,1,NORM_MINMAX);
	//imshow("X_norm", xder);
	imshow("Y",yder);
	imshow("m",m);
	float vecx,vecy,gradx,grady;
	float dot;
	long int count=0;
	float max=0;
	Canny(img,con,50,100,3);
	 findContours( con, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	  Mat drawing = Mat::zeros( con.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar(100,100,100);
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
       printf(" %f ",arcLength(contours[i],0));
     }
     printf("\n");
     Point p;

	
	for(int i=0;i<contours.size();i++)
	{
		for(int j=0;j<contours[i].size();j++)
		{
			p=contours[i][j];
			cout<<p<<endl;
		}
	}	
	
	
}
	
