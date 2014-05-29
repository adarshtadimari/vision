#include"cv.h"
#include"highgui.h"

using namespace cv;
using namespace std;
int main(int argc,char *argv[])
{
	Mat img=imread(argv[1],0);
	Mat inv=255-img;
	int i1,j1,i2,j2;
	Mat m= Mat::zeros(img.rows,img.cols,CV_32F);
	Mat vx= Mat::zeros(img.rows,img.cols,CV_32F);
	Mat vy= Mat::zeros(img.rows,img.cols,CV_32F);
	Point maxP;
	
	
	Mat xder,yder,t1,t2;
	Sobel(img,xder,CV_32F,1,0,3);
	Sobel(img,yder,CV_32F,0,1,3);
	equalizeHist(inv,inv);
	threshold(inv,inv,150,255,CV_THRESH_BINARY);
	
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

	for(j1=20;j1<img.rows-20;j1++)
		for(i1=20;i1<img.cols-20;i1++)
		{
			count++;
			dot=0;
			for(j2=j1-20;j2<j1+20;j2++)
				for(i2=i1-20;i2<i1+20;i2++)
				{
					vecx=i2-i1;
					vecy=j2-j1;
					vecx=(float)vecx/sqrt(vecx*vecx+vecy*vecy);	
					vecy=(float)vecy/sqrt(vecx*vecx+vecy*vecy);						
					gradx=xder.at<float>(j2,i2);
					grady=yder.at<float>(j2,i2);	
					
					
					gradx=(float)gradx/sqrt(gradx*gradx+grady*grady);	
					grady=(float)grady/sqrt(gradx*gradx+grady*grady);	
					
					float p=vecx*gradx+vecy*grady;
					//printf("%f at(%d,%d)",p,i2,j2); 			
					if(p>0)
						dot+=p*p/(40*40);
				}
				
				
				m.at<float>(j1,i1)=dot;
				//printf("%f at (%d,%d)",inv.at<int>(j1,i1),i1,j1);
				
			if(max<dot)
			{
				max=m.at<float>(j1,i1);
				maxP.x=i1;
				maxP.y=j1;	
			
			}
			if(count%50==0)
			{
				printf("%ld\n",count);
			}
		}
		
		imshow("final",m);
		cout<<maxP<<endl;
	
	
	//imshow("X+Y",t1);
	/*for(j1=0;j1<img.rows;j1++)
		for(i1=0;i1<img.cols;i1++)
		{	
			dot=0;
			for(j2=0;j2<img.rows;j2++)
				for(i2=0;i2<img.cols;i2++)
				{
					vecx=i2-i1;
					vecy=j2-j1;
					vecx/=sqrt(vecx*vecx+vecy*vecy);
					vecy/=sqrt(vecx*vecx+vecy*vecy);
					
					gradx = xder.at<float>(j2,i2);
					grady= yder.at<float>(j2,i2);
					
					gradx/= sqrt(gradx*gradx+grady*grady);
					grady/= sqrt(gradx*gradx+grady*grady);
					
					
					float p=gradx*vecx+grady*vecy;
					if(p>0)
						dot+=inv.at<int>(j1,i1)*p;
					
								
					
					
				}
			m.at<float>(j1,i1)=dot;
			printf("1");
		}
	*/

	normalize(m,m,0,1,NORM_MINMAX);
	imshow("out",m);
	imwrite("out.jpg",m);
	
	cvWaitKey(0);
}
