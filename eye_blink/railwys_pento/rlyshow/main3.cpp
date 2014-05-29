#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include"rlyy.cpp"
#include <iostream>

using namespace cv;
using namespace std;

#define videofile "/home/adarsh/Dropbox/railways/video_kin.avi"
#define rgbfile "/home/adarsh/Dropbox/railways/video_kin.avi"

#define videotimefile "videotime.txt"
#define gpstimefile "gpstime.txt"
#define csvfile "data3.csv"

#define pantofile "least.jpg"
#define pwidth 640
#define pheight 480
#define stzoom 1.00
#define ezoom 1.50
#define sti 0
#define ei 450

#define actualw 100

#define mode 1

#define frameoffset 25*1

float distan[2048];
uint16_t t_gamma[2048];
uint16_t inv_t_gamma[10000] = {0};


int findifclose(CvPoint a, CvPoint x, CvPoint y)
{
	float m = (float)(y.y - x.y)/(y.x - x.x);
	float c = y.y - m*y.x;
	float d = (a.y - m*a.x - c)/sqrt(m*m + 1);
	return (int)d;
}

int min(int a, int b)
{
	return a<b?a:b;
}

CvPoint findintersection(CvPoint a, CvPoint b, CvPoint c, CvPoint d)
{
	float m1 = (float)(b.y - a.y)/(b.x - a.x);
	float c1 = b.y - m1*b.x;
	if(d.x==c.x)
		return cvPoint((int)d.x, (int)(m1*d.x + c1));
	float m2 = (float)(d.y - c.y)/(d.x - c.x);
	float c2 = d.y - m2*d.x;
	if(m1==m2)
		return cvPoint(-1, -1);
	float x = (c2 - c1)/(m1 - m2);
	float y = m1*x + c1;
	return cvPoint((int)x, (int)y);
}

double fetchdistance(IplImage* img, CvPoint pt, int stagger)
{
	int xmin = pt.x-10, xmax = pt.x+10, ymin = pt.y+10, ymax = pt.y+30;
	uchar* ptr = (uchar*)img->imageData;
	int i,j;
	int num = 0;
	double dist = 0.0;

	for(i=ymin; i<ymax; i++)
	{
		for(j=xmin; j<xmax; j++)
		{
			int b = ptr[i*3*640 + j*3];
			int g = ptr[i*3*640 + j*3 + 1];
			int r = ptr[i*3*640 + j*3 + 2];

			if(b+g+r == 0)
				continue;

			uint8_t u,l;

			if(r==255 && b==0)
			{
				u = 1;
				l = g;
			}
			else if(g==255 && b==0)
			{
				u = 2;
				l = 255 - r;
			}
			else if(r==0 && g==255)
			{
				u = 3;
				l = b;
			}
			else if(r==0 && b==255)
			{
				u = 4;
				l = 255 - g;
			}
			else
				continue;

			uint16_t val = (u<<8) + l;
			uint16_t d = inv_t_gamma[val];
			int td = distan[d]*100;
			if(td < 50)
				continue;
			int td1 = sqrt((td*td) - (stagger*stagger) - 900);
			//printf("td %d stagger %d td1 %d\n", td, stagger, td1);
			dist = dist + td1;
			num++;
		}
	}

	if(num==0)
		return 0.0;

//	cvRectangle(img, cvPoint(xmin, ymin), cvPoint(xmax, ymax), CV_RGB(255, 0, 0));
	return dist/(double)num;
}

int main(int argc, char** argv)
{
	CvCapture *capture = cvCreateFileCapture(videofile);
	CvCapture *cap2 = cvCreateFileCapture(rgbfile);
	cvSetCaptureProperty(capture, CV_CAP_PROP_FPS, 25);
	cvSetCaptureProperty(cap2, CV_CAP_PROP_FPS, 25);
	char str[10] = "m1.jpg";
	char nstr[10] = "p1.jpg";
	int idx = 1;
	int fpc = 0;
	int width = pwidth, height = pheight;
	int x, y, w, h;
	int min = 640*480, mini = 0;
	long long frameno = 1;
	int starti = 0, endi = 450;
	float startzoom = stzoom, endzoom = ezoom, zoom, minzoom;
	int stagger;
	double dist;
	FILE *gps, *vid;
	char *gpsline, *videoline, *gpstime, *videotime, *lat, *lon, *lati, *longi;
	CvPoint previntersect = cvPoint(-1, -1);
	Mat tdst(1280, 960, CV_32F);
	Mat dst(1280, 960, CV_8U);
	Mat rdst(1280, 960, CV_8U);
	Mat temask(640, 480, CV_8U);
	CvFont fon;
	CvFont* font = &fon;
	cvInitFont(font, CV_FONT_HERSHEY_PLAIN, 1, 1, 0, 2);	
		IplImage* white = cvCreateImage(cvSize(640, 480), 8, 1);
	FILE* csv = fopen(csvfile, "w");
		
	CvSize size= cvSize(1280,480);
	CvVideoWriter *video = cvCreateVideoWriter("video_out5.avi", CV_FOURCC('D', 'I', 'V', 'X'), 25, size, 1);
	cvSet(white, CV_RGB(255, 255, 255));

	if(capture == NULL)
	{
		printf("Could not initialize video capture\n");
		return 0;
	}

	if(mode==2)
	{
		gps = fopen(gpstimefile, "r");
		vid = fopen(videotimefile, "r");
		gpsline = (char*)malloc(100);
		videoline = (char*)malloc(100);
		gpstime = (char*)malloc(30);
		videotime = (char*)malloc(30);
		lat = (char*)malloc(30);
		lon = (char*)malloc(30);
		lati = (char*)malloc(30);
		longi = (char*)malloc(30);

		gpsline = fgets(gpsline, 100, gps);
		gpsline = fgets(gpsline, 100, gps);
		gpsline = fgets(gpsline, 100, gps);
		gpsline = fgets(gpsline, 100, gps);
		gpsline = fgets(gpsline, 100, gps);
		gpsline = fgets(gpsline, 100, gps);
		videoline = fgets(videoline, 100, vid);

		strncpy(videotime, videoline+11, 8);
		videotime[8] = '\0';

		strncpy(gpstime, gpsline+56, 8);
		gpstime[8] = '\0';
		
		//printf("%s\n", videotime);
		//printf("%s\n", gpstime);
		int j;
		for(j=0; j<frameoffset; j++)
		{
			videoline = fgets(videoline, 100, vid);
		}

		strncpy(videotime, videoline+11, 8);
		videotime[8] = '\0';

		while(strcmp(gpstime, videotime))
		{
			gpsline = fgets(gpsline, 100, gps);
			gpsline = fgets(gpsline, 100, gps);
			gpsline = fgets(gpsline, 100, gps);
			strncpy(lat, gpsline+28, 21);
			lat[21] = '\0';
			gpsline = fgets(gpsline, 100, gps);
			strncpy(lon, gpsline+28, 22);
			lon[22] = '\0';
			gpsline = fgets(gpsline, 100, gps);
			gpsline = fgets(gpsline, 100, gps);
			strncpy(gpstime, gpsline+56, 8);
			gpstime[8] = '\0';
		}

	}

	IplImage* tmask = cvCreateImage(cvSize(640, 480), 8, 3);
	IplImage* cmask = cvCreateImage(cvSize(640, 480), 8, 3);
	IplImage* frame = cvCreateImage(cvSize(640, 480), 8, 3);
	IplImage* frame2 = cvCloneImage(frame);
	IplImage* disp = cvCreateImage(cvSize(640, 480), 8, 3);
	IplImage* mask = cvCreateImage(cvSize(640, 480), 8, 1);
	IplImage* r_img = cvCreateImage(cvSize(640, 480), 8, 1);
	IplImage* g_img = cvCreateImage(cvSize(640, 480), 8, 1);
	IplImage* b_img = cvCreateImage(cvSize(640, 480), 8, 1);
	
	IplImage *wpanto, *andimg, *operand, *minimage, *minmask;
	operand = cvCreateImage(cvSize(640, 480), 8, 1);
	minimage = cvCreateImage(cvSize(640, 480), 8, 1);
	andimg = cvCreateImage(cvSize(640, 480), 8, 1);
	wpanto = cvCreateImage(cvSize(640, 480), 8, 1);
	frame = cvQueryFrame(capture);
	frame2 = cvQueryFrame(cap2);

	int i;
	for(i=0; i<2048; i++)
	{
		const float k1 = 1.1863;
		const float k2 = 2842.5;
		const float k3 = 0.1236;
		const float depth = k3 * tanf(i/k2 + k1);// - 0.037;
		distan[i] = depth;
	}

	for(i=0; i<2048; i++)
	{
		float v = i/2048.0;
		v = powf(v, 3)* 6;
		t_gamma[i] = v*6*256;
		inv_t_gamma[t_gamma[i]] = i;
	}
	
	int flagtemplate=0;
    
    
    
	
	while(frame != NULL)
	{
		if(frameno < frameoffset)
		{
			frameno++;
			frame = cvQueryFrame(capture);
			frame2 = cvQueryFrame(cap2);
			continue;
		}

		uchar* ptr = (uchar *)frame->imageData;
		uchar* maskptr = (uchar *)mask->imageData;
		min = 640*480, mini = 0;
		zoom = startzoom;

		for(x = 0; x<480; x++)
		{
			for(y = 0; y<640; y++)
			{
				if(*(ptr+1)>=128 && *ptr<70 && ((*(ptr+2)<255) || (*(ptr+2)==255 && *ptr==0)))
				{
					*maskptr = 255;
				}
				ptr += 3;
				maskptr++;
			}
		}
		
		
		if(flagtemplate==0)
		{
		    IplImage* imask = cvCreateImage(cvSize(640, 480), 8, 1);
		
		
		    cvCopy(mask,imask);
		
		    cvDilate(imask, imask, NULL, 1);
		    cvErode(imask,imask,NULL,1);
						    cvThreshold(imask, imask, 128, 255, CV_THRESH_BINARY_INV);
		
		
		                    
		
						
        	cvSaveImage("imask5.jpg", imask);
		    templatefind("imask5.jpg");
		    flagtemplate++;
            
        }
        IplImage* panto = cvLoadImage(pantofile, 0);

		cvErode(mask, mask, NULL, 1);
		cvDilate(mask, mask, NULL, 1);
		
		
		if(mode == 0)
		{
			cvShowImage("Mask", mask);
			cvShowImage("Depth", frame);
			char c = cvWaitKey(10);
			if(c==27)
				break;
			else if(c==' ')
			{
				while(1)
				{
					char ch = cvWaitKey(10);
					if(ch=='s')
					{
						str[1] = idx+48;
						nstr[1] = idx+48;
						IplImage* imask = cvCreateImage(cvSize(640, 480), 8, 1);
						cvThreshold(mask, imask, 128, 255, CV_THRESH_BINARY_INV);
						cvSaveImage(str, imask);
						idx++;
						cvReleaseImage(&imask);
						break;
					}
					else if(ch==27)
						break;
				}
			}
			cvZero(mask);
			frame = cvQueryFrame(capture);	
			frame2 = cvQueryFrame(cap2);	
			continue;

		}

		while(zoom <= endzoom)
		{
			w = width * zoom;
			h = height * zoom;
			IplImage* resized = cvCreateImage(cvSize(w, h), 8, 1);
			cvResize(panto, resized);
			CvRect roi = cvRect(w/2 - 320, 0, 640, h);

			cvSetImageROI(resized, roi);

			int i;
			for(i=starti; i<endi; i++)
			{
				int tf = 0;
				cvCopy(white, operand);
				if(i+h > 480)
				{
					tf = 1;
					cvSetImageROI(operand, cvRect(0, i, 640, 480-i));
					cvSetImageROI(resized, cvRect(w/2 - 320, 0, 640, 480-i));
				}
				else
					cvSetImageROI(operand, cvRect(0, i, 640, h));
				cvCopy(resized, operand);
				cvResetImageROI(operand);
				if(tf)
					cvResetImageROI(resized);
				cvThreshold(mask, mask, 128, 255, CV_THRESH_BINARY_INV);
				cvXor(mask, operand, andimg);
				cvThreshold(mask, mask, 128, 255, CV_THRESH_BINARY_INV);
				int count = cvCountNonZero(andimg);
				
				if(count<min)
				{
					min = count;
					mini = i;
					minzoom = zoom;
					cvCopy(operand, minimage);
				}
			}

			cvResetImageROI(resized);
			cvReleaseImage(&resized);
			zoom += 0.01;
		}

		starti = (mini - 5 < sti ? sti : mini-5);
		endi = (mini + 5 > ei ? ei : mini+5);
		startzoom = (minzoom - 0.04 < stzoom ? stzoom : minzoom-0.04);
		endzoom = (minzoom + 0.04 > ezoom ? ezoom : minzoom+0.04);

		int lx = pwidth/2 - (pwidth/2 - plx)*minzoom;
		int ly = mini + pheight/2 - (pheight/2 - ply)*minzoom;
		int rx = pwidth/2 + (prx - pwidth/2)*minzoom;
		int ry = mini + pheight/2 - (pheight/2 - pry)*minzoom;
		
		CvPoint le = cvPoint(lx, ly);
		CvPoint r = cvPoint(rx, ry);
		
		cvCopy(mask, wpanto);
	
		Mat roi(mask, Rect(0, max(ry, ly), 640, 480-max(ry, ly)));
		roi = Scalar(0);
		temask = Mat(mask);
		resize(temask, dst, Size(1280, 960));
		Sobel(dst, tdst, CV_32F, 1, 0);
		convertScaleAbs(tdst, rdst);
		vector<Vec4i> lines;
		HoughLinesP(rdst, lines, 1, CV_PI/180, 50, 50, 10);
		temask.release();
		tdst.release();
		rdst.release();
		dst.release();

		cvNot(minimage, minimage);
		//cvSet(wpanto, CV_RGB(200, 200, 200), minimage);

		CvPoint* toplist = new CvPoint[lines.size()];
		CvPoint* bottomlist = new CvPoint[lines.size()];
		int no_pts = 0, i;

		cvCvtColor(wpanto, disp, CV_GRAY2BGR);
		
		for(i = 0; i<lines.size(); i++)
		{
			Vec4i l = lines[i];
			CvPoint a = cvPoint(320+(l[0]-640)/2, 240+(l[1]-480)/2);
			CvPoint b = cvPoint(320+(l[2]-640)/2, 240+(l[3]-480)/2);
			int d1 = findifclose(a, le, r);
			int d2 = findifclose(b, le, r);
			CvPoint farpt, nearpt;
			int min;
			if(d1<d2)
			{
				farpt = a;
				nearpt = b;
				min = d1;
			}
			else
			{
				farpt = b;
				nearpt = a;
				min = d2;
			}

			if(min > -5)
				continue;
			
			double slope = ((double)a.y - b.y)/(a.x - b.x);
			if(a.x==b.x)
				slope = 100.0;

			if(slope<0)
				slope = -1.0*slope;
			if(slope<1.0)
				continue;

			CvPoint intersect;
			intersect = findintersection(le, r, a, b);
			/*if(previntersect.x!=-1)
			{
				if(abs(previntersect.x - intersect.x) > 20)
					continue;
			}*/
			toplist[no_pts] = farpt;
			bottomlist[no_pts] = intersect;
			no_pts++;
		}

		//printf("minzoom : %lf\n", minzoom);
		int maxd = -500;
		CvPoint intersect, farp;
		for(i=0; i<no_pts; i++)
		{
			cvZero(tmask);
			cvLine(tmask, toplist[i], bottomlist[i], CV_RGB(255, 255, 255), 3);
			cvAnd(frame, tmask, cmask);
			cvSplit(cmask, b_img, g_img, r_img, NULL);
			int val = cvCountNonZero(r_img) - cvCountNonZero(g_img) - 2*cvCountNonZero(b_img);
			if(val>maxd)
			{
				maxd = val;
				intersect = bottomlist[i];
				farp = toplist[i];
			}
		}

		previntersect = intersect;

		if(toplist!=NULL)
		{
			free(toplist);
			free(bottomlist);
		}

		IplImage* im2write = cvCreateImage(cvSize(1280, 480), 8, 3);

		if(no_pts)
		{	
			cvLine(disp, farp, intersect, CV_RGB(0, 255, 255), 3, CV_AA);
			cvCircle(disp, intersect, 10, CV_RGB(255, 0, 255), 3);
			stagger = (((intersect.x - lx)*actualw)/(rx - lx)) - (actualw/2);
			dist = fetchdistance(frame, intersect, stagger);
			printf("stagger : %d distance : %lf\n", stagger, dist);
			char* sta = new char[30];
			char* hei = new char[30];
			sprintf(sta, "stagger : %d", stagger);
			sprintf(hei, "height : %d", (int)dist);

			if(mode==2)
			{
				cvPutText(disp, sta, cvPoint(20, 20), font, CV_RGB(255, 0, 0));
				cvPutText(disp, hei, cvPoint(20, 35), font, CV_RGB(255, 0, 0));
				if(hei==0)
					fprintf(csv, "%d,,", stagger);
				else
					fprintf(csv, "%d,%d,", stagger, (int)dist);
			}
		}
		else
		{
			if(mode==2)
			{
				cvPutText(disp, "stagger :", cvPoint(20, 20), font, CV_RGB(255, 0, 0));
				cvPutText(disp, "height :", cvPoint(20, 35), font, CV_RGB(255, 0, 0));
				fprintf(csv, ",,");
			}
	
		}
		cvCircle(disp, le, 10, CV_RGB(255, 0, 0));
		cvCircle(disp, r, 10, CV_RGB(255, 0, 0));
		
		int fileflag = 0;
		if(mode==2)
		{
			/*if(strcmp(gpstime, videotime)==0)
			{
				cvPutText(frame2, gpstime, cvPoint(20, 20), font, CV_RGB(255, 255, 255));
				cvPutText(frame2, lat, cvPoint(20, 35), font, CV_RGB(255, 255, 255));
				cvPutText(frame2, lon, cvPoint(20, 50), font, CV_RGB(255, 255, 255));
			}
			else
			{
				while(strcmp(gpstime, videotime)<0)
				{
					gpsline = fgets(gpsline, 100, gps);
					if(gpsline==NULL)
					{
						fileflag = 1;
						break;
					}
					gpsline = fgets(gpsline, 100, gps);
					gpsline = fgets(gpsline, 100, gps);
					strncpy(lat, gpsline+28, 19);
					lat[19] = '\0';
					gpsline = fgets(gpsline, 100, gps);
					strncpy(lon, gpsline+28, 20);
					lon[20] = '\0';
					gpsline = fgets(gpsline, 100, gps);
					gpsline = fgets(gpsline, 100, gps);
					strncpy(gpstime, gpsline+56, 8);
					gpstime[8] = '\0';
				}
				if(strcmp(gpstime, videotime)==0)
				{
					cvPutText(frame2, gpstime, cvPoint(20, 20), font, CV_RGB(255, 255, 255));
					cvPutText(frame2, lat, cvPoint(20, 35), font, CV_RGB(255, 255, 255));
					cvPutText(frame2, lon, cvPoint(20, 50), font, CV_RGB(255, 255, 255));
				}
				else
				{
					cvPutText(frame2, videotime, cvPoint(20, 20), font, CV_RGB(255, 255, 255));
					cvPutText(frame2, lat, cvPoint(20, 35), font, CV_RGB(255, 255, 255));
					cvPutText(frame2, lon, cvPoint(20, 50), font, CV_RGB(255, 255, 255));
				}
			}

			videoline = fgets(videoline, 100, vid);
			if(videoline == NULL)
				break;
			strncpy(videotime, videoline+11, 8);
			videotime[8] = '\0';
*/
			if(fpc%25==0)
			{
				fpc=1;
				gpsline = fgets(gpsline, 100, gps);
				if(gpsline==NULL)
				{
					fileflag = 1;
					printf("gps file empty\n");
					break;
				}
				gpsline = fgets(gpsline, 100, gps);
				gpsline = fgets(gpsline, 100, gps);
				strncpy(lat, gpsline+28, 21);
				lat[21] = '\0';
				gpsline = fgets(gpsline, 100, gps);
				strncpy(lon, gpsline+28, 22);
				lon[22] = '\0';
				gpsline = fgets(gpsline, 100, gps);
				gpsline = fgets(gpsline, 100, gps);
				strncpy(gpstime, gpsline+56, 8);
				gpstime[8] = '\0';
			}
			else
				fpc++;

			cvPutText(frame2, gpstime, cvPoint(20, 20), font, CV_RGB(255, 255, 255));
			cvPutText(frame2, lat, cvPoint(20, 35), font, CV_RGB(255, 255, 255));
			cvPutText(frame2, lon, cvPoint(20, 50), font, CV_RGB(255, 255, 255));
			strcpy(lati, lat+10);
			strcpy(longi, lon+11);
			fprintf(csv, "%s,%s,%s\n", gpstime, lati, longi);	
		}	

		cvShowImage("Detected", disp);
		cvShowImage("Mask", mask);
		cvShowImage("Depth", frame);
		cvShowImage("RGB", frame2);	
		cvSetImageROI(im2write, cvRect(0, 0, 640, 480));
		cvCopy(frame2, im2write);
		cvResetImageROI(im2write);
		cvSetImageROI(im2write, cvRect(640, 0, 640, 480));
		cvCopy(disp, im2write);
		cvResetImageROI(im2write);

		if(mode==2)
		{
			cvWriteFrame(video, im2write);
		}

		cvReleaseImage(&im2write);

		char c = cvWaitKey(1);
		if(c==27)
			break;
		else if(c==' ')
		{
			while(1)
			{
				char ch = cvWaitKey(10);
				if(ch=='s')
				{
					str[1] = idx+48;
					nstr[1] = idx+48;
					cvSaveImage(str, mask);
					idx++;
					break;
				}
				else if(ch==27)
					break;
			}
		}
		cvZero(mask);
		frame = cvQueryFrame(capture);
		frame2 = cvQueryFrame(cap2);
	}

	cvReleaseVideoWriter(&video);
	fclose(csv);
	return 0;
}

