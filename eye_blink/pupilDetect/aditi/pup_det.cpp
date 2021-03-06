#include"opencv2/opencv.hpp"
#include "opencv2/objdetect.hpp"
//#include "highgui.h"
#include "opencv2/imgproc.hpp"
//#include "cv.h"
#include<iostream>
#include <vector>
#include "math.h"
using namespace std;
using namespace cv;
int THRESHOLD1=20;
int THRESHOLD2=3*20;
Mat src,srcInv,srcBlur,xDerivative,yDerivative;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

int main(int argc,char* argv[])
{
  //  cout<<"Debug1"<<endl;
	Mat xNorm,yNorm,canny_output,drawing,values,valuesNorm;
	float vecx,vecy,gradx,grady,maxValue=0;
	Point maxPoint;	
	//	int array[200][200];
		
	
	src=imread(argv[1],0);
	values=Mat::zeros(src.rows,src.cols,CV_32FC1);
	equalizeHist(src,src);
	imwrite("lefte.jpg",src);
	//	cout<<"Debug"<<endl;
	
	
	
	
	drawing = Mat::zeros(src.size(), CV_8UC1);
	threshold(src,srcInv,10,255,THRESH_BINARY_INV);
	

	//	erode(srcInv, srcInv);
       
	imshow("Original Image",src);
	imshow("Inverted Original",srcInv);
	
	
	Sobel(src,xDerivative,CV_32F,1,0,3);
	Sobel(src,yDerivative,CV_32F,0,1,3);
	
	normalize(xDerivative,xNorm,0,1,NORM_MINMAX);
	normalize(yDerivative,yNorm,0,1,NORM_MINMAX);
	
	imshow("X derivative",xNorm);
	imshow("Y derivative",yNorm);	
	
	blur(src,srcBlur,Size(3,3));
	Canny(srcBlur,canny_output,THRESHOLD1,3*THRESHOLD1,3);
	
	imshow("Canny Output",canny_output);
 	findContours(canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
	
  	for( int i = 0; i< contours.size(); i++ )
       	drawContours( drawing, contours, i, Scalar(255), 1, 8, hierarchy, 0, Point() );
      	
    imshow("Contour",drawing);
		
    cout<<src.rows<<'\t'<<src.cols<<endl;

    //Restricting the centers to be near centre
    float x_b_max=0;
    float x_b_min=src.cols;
   
    for(int j1=0;j1<src.rows;j1++){
      for(int i1=0;i1<src.cols;i1++){
	if(srcInv.at<uchar>(j1,i1)){
	    if(i1>x_b_max)
	      x_b_max=i1;
	    else  if(i1<x_b_min)
	      x_b_min=i1;
	  }
	  
      }
    }	  
	  
    cout<<"Max"<<x_b_max<<endl;
    cout<<"Min"<<x_b_min<<endl;
      float range = (x_b_max - x_b_min)/4;
      float mid = (x_b_max + x_b_min)/2;
      cout<<"RANGE"<<range<<endl;
      cout<<"MID"<<mid<<endl;
	   


	for(int j1=0;j1<src.rows;j1++)
		for(int i1=0;i1<src.cols;i1++)
		{
		  if(srcInv.at<uchar>(j1,i1)&& abs(i1-mid)<range)
		  	{
				float dot=0;
				for(int j2=0;j2<src.rows;j2++)
				{
					for(int i2=0;i2<src.cols;i2++)
					{
					 
					  if((canny_output.at<uchar>(j2,i2)))
					  	{
							vecx=i2-i1;
							vecy=j2-j1;
							vecx=(float)vecx/sqrt(vecx*vecx+vecy*vecy);	
							vecy=(float)vecy/sqrt(vecx*vecx+vecy*vecy);						
							gradx=xDerivative.at<float>(j2,i2);
							grady=yDerivative.at<float>(j2,i2);	
							//gradx=(float)gradx/sqrt(gradx*gradx+grady*grady);	
							//grady=(float)grady/sqrt(gradx*gradx+grady*grady);	
							float dotp=vecx*gradx+vecy*grady;
						//printf("%f at(%d,%d)",p,i2,j2); 			
							if(dotp>0)
								dot+=dotp*dotp;
								}
					}
				}
				
				if(dot>maxValue)
				{
					maxValue=dot;
					maxPoint.x=i1;
					maxPoint.y=j1;
				}
				
				
				values.at<float>(j1,i1)=dot;
				//				cout<<j1<<'\t'<<i1<<'\t'<<dot<<endl;
			}
		
				
		}
	
	normalize(values,valuesNorm,0,1,NORM_MINMAX);
	
	imshow("values",valuesNorm);	
	cout<<"Coordinates"<<maxPoint.x<<maxPoint.y;
	circle(src, maxPoint,1, Scalar(255, 0 , 0),-1);
	imshow("Center",src);
	waitKey(0);
}
