
IplImage* vertical(IplImage* panto,IplImage* mask,int &teplx, int &teply ,int &teprx,int &tepry,int stzoom, int ezoom)
{
        int templx=teplx,temply=teply,temprx=teprx,tempry=tepry;
        int mplx=teplx,mply=teply,mprx=teprx,mpry=tepry;       
        float startzoom = stzoom, endzoom = ezoom, zoom=stzoom, minzoom;
        int width = pwidth, height = pheight;
        int w,h;
        int starti = 0, endi = 450;
        IplImage* white = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage* operand = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage*  andimg = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage* minimage = cvCreateImage(cvSize(640, 480), 8, 1);
        cvSet(white, CV_RGB(255, 255, 255));
        int min = 640*480, mini = 0;
        
        while(zoom <= endzoom)
        {
            templx=teplx;
            temply=teply;
            temprx=teprx;
            tempry=tepry;
			w = width * zoom;
			h = height * zoom;
			IplImage* resized = cvCreateImage(cvSize(w, h), 8, 1);
			cvResize(panto, resized);
			templx*=zoom;
			temply*=zoom;
			temprx*=zoom;
			tempry*=zoom;
			
			CvRect roi = cvRect(w/2-320, 0, 640, h);

			templx-=(w/2)-320;
			temprx-=(w/2)-320;
			cvSetImageROI(resized, roi);
			
			//cvShowImage("Zoom",resized);
			//cvWaitKey(0);
			
            int tempilx,tempily,tempirx,tempiry;
			
			
			int i;
			for(i=starti; i<endi; i++)
			{
				tempilx=templx;
				tempily=temply;
				tempirx=temprx;
				tempiry=tempry;
				
				int tf = 0;
				cvCopy(white, operand);
				if(i+h > 480)
				{
				    
					tf = 1;
					cvSetImageROI(operand, cvRect(0, i, 640, 480-i));
					cvSetImageROI(resized, cvRect(w/2 - 320, 0, 640, 480-i));
					
					}
				else
					{
					    cvSetImageROI(operand, cvRect(0, i, 640, h));
				        }
				cvCopy(resized, operand);
				    tempily+=i;
    			    tempiry+=i;
                    				
					
				cvResetImageROI(operand);
				
				if(tf)
					cvResetImageROI(resized);
				//cvThreshold(mask, mask, 128, 255, CV_THRESH_BINARY_INV);
				cvXor(mask, operand, andimg);
				//cvThreshold(mask, mask, 128, 255, CV_THRESH_BINARY_INV);
				int count = cvCountNonZero(andimg);
			    //cout<<" "<<count<<" ";	
				if(count < min)
				{
					min = count;
					mini = i;
					minzoom = zoom;
					cvCopy(operand, minimage);
					mplx=tempirx;
					mply=tempiry;
					mprx=tempilx;
					mpry=tempily;
				}
			
			}
            
	    	cvResetImageROI(resized);
			cvReleaseImage(&resized);
			zoom += 0.01;
			//cout<<"\n";

		}
        //cout<<min;
        IplImage* tempmin=cvCreateImage(cvSize(640,480),8,1);
        cvCopy(minimage,tempmin);
        cvCircle(tempmin,cvPoint(mplx,mply), 30, CV_RGB(0,0,0), 20, 8, 0);
        cvCircle(tempmin,cvPoint(mprx,mpry), 30, CV_RGB(0,0,0), 20, 8, 0);
        //cout<<mplx<<','<<mply<<'\n';
        //cout<<mprx<<','<<mpry;
        //cvShowImage("minimage",tempmin);
        //cvWaitKey(0);
        teplx=mplx;
        teply=mply;
        teprx=mprx;
        tepry=mpry;
        
        
        return minimage;

}
