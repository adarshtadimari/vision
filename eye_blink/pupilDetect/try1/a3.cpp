#include"cv.h"
#include"highgui.h"
#include<iostream>
using namespace cv;
int THRESHOLD1=100;
int THRESHOLD2=3*100;
Mat src,srcInv,srcBlur,xDerivative,yDerivative;
vector<vector<Point> > contours;
vector<Vec4i> hierarchy;

int main(int argc,char* argv[])
{
	Mat xNorm,yNorm,canny_output,drawing,values,valuesNorm;
	float vecx,vecy,gradx,grady,maxValue=0;
	Point maxPoint;	
	
		
	
	src=imread(argv[1],0);
	values=Mat::zeros(src.rows,src.cols,CV_32FC1);
	equalizeHist(src,src);
	imwrite("lefte.jpg",src);
	
	
	
	
	
	drawing = Mat::zeros(src.size(), CV_8UC1);
	threshold(src,srcInv,50,255,THRESH_BINARY_INV);
	
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
 	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	
  	for( int i = 0; i< contours.size(); i++ )
       	drawContours( drawing, contours, i, Scalar(255), 1, 8, hierarchy, 0, Point() );
      	
    imshow("Contour",drawing);
		
	
	for(int j1=0;j1<src.rows;j1++)
		for(int i1=0;i1<src.cols;i1++)
		{
			if(srcInv.at<uchar>(j1,i1))
			{
				float dot=0;
				for(int j2=0;j2<contours.size();j2++)
				{
					for(int i2=0;i2<contours[j2].size();i2++)
					{
						Point p= contours[j2][i2];
						vecx=p.x-i1;
						vecy=p.y-j1;
						vecx=(float)vecx/sqrt(vecx*vecx+vecy*vecy);	
						vecy=(float)vecy/sqrt(vecx*vecx+vecy*vecy);						
						gradx=xDerivative.at<float>(p.y,p.x);
						grady=yDerivative.at<float>(p.y,p.x);	
						gradx=(float)gradx/sqrt(gradx*gradx+grady*grady);	
						grady=(float)grady/sqrt(gradx*gradx+grady*grady);	
						float dotp=vecx*gradx+vecy*grady;
					//printf("%f at(%d,%d)",p,i2,j2); 			
						dot+=dotp;
					}
				}
				
				if(dot>maxValue)
				{
					maxValue=dot;
					maxPoint.x=i1;
					maxPoint.y=j1;
				}
				
				
				values.at<float>(j1,i1)=dot;
			}
		
				
		}
	
	normalize(values,valuesNorm,0,1,NORM_MINMAX);
	
	imshow("values",valuesNorm);	
	std::cout<<maxPoint;
	
	
	waitKey(0);
}
