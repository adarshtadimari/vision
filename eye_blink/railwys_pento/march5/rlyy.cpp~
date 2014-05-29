


float pwidth1= 640;
float pheight1= 144;
float stzoom1= 1.00;
float ezoom1 =1.5;
float plx= 99.0;
float ply= 26.0;
float prx= 500.0;
float pry= 22.0;

IplImage* minimage;
IplImage* mask;
IplImage* panto;
IplImage* finimg;
IplImage* least;


void vertical();
void shift();
void colour();
void horzoom();
int mincount=640*480;
int teplx=plx,teply=ply,teprx=prx,tepry=pry;


void templatefind(const char a[100])
{
    panto = cvLoadImage("t2.jpg", 0);
    mask = cvLoadImage(a,0);
    //strcpy(saveend,argv[1]);
    least=cvCreateImage(cvSize(640,480),8,1);
    vertical();
    horzoom();
}


void vertical()
{
        int templx=plx,temply=ply,temprx=prx,tempry=pry;
        int mplx=plx,mply=ply,mprx=prx,mpry=pry;       
        float startzoom = stzoom1, endzoom = ezoom1, zoom=stzoom1, minzoom;
        int width = pwidth1, height = pheight1;
        int w,h;
        int starti = 0, endi = 450;
        IplImage* white = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage* operand = cvCreateImage(cvSize(640, 480), 8, 1);
        IplImage*  andimg = cvCreateImage(cvSize(640, 480), 8, 1);
        minimage = cvCreateImage(cvSize(640, 480), 8, 1);
        cvSet(white, CV_RGB(255, 255, 255));
        int min = 640*480, mini = 0;
        
        while(zoom <= endzoom)
        {
            templx=plx;
            temply=ply;
            temprx=prx;
            tempry=pry;
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
					mplx=tempilx;
					mply=tempily;
					mprx=tempirx;
					mpry=tempiry;
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
        cvCircle(tempmin,cvPoint(mplx,mply), 5, CV_RGB(0,0,0), 2, 8, 0);
        cvCircle(tempmin,cvPoint(mprx,mpry), 5, CV_RGB(0,0,0), 2, 8, 0);
        //cout<<mplx<<','<<mply<<'\n';
        //cout<<mprx<<','<<mpry;
        //cvShowImage("minimage",tempmin);
        //cvWaitKey(0);
        teplx=mplx;
        teply=mply;
        teprx=mprx;
        tepry=mpry;

}
int findmin(int count,IplImage* img)
{   
    int flag=0;
    if(count< mincount)
    {
        mincount=count;
        cvCopy(img,least);
        flag++;
        
    }
    
    return flag;


}

void horzoom()
{   
    int t1lx=teplx,t1rx=teprx;
    int mint1lx=teplx,mint1rx=teprx;
    //cvShowImage("Minimage",minimage);
    //cvWaitKey(0);
    float startzoom=0.8,endzoom=1.2,zoom;
    zoom=startzoom;
    IplImage* zoomcrop=cvCreateImage(cvSize(640,480),8,1);
    int i,j;
    IplImage* xorimage=cvCreateImage(cvSize(640,480),8,1);
    IplImage* hmask=cvCreateImage(cvSize(640,480),8,1);
    cvCopy(minimage,hmask);
    int count;
    while(zoom<=1)
    {
        t1lx=teplx;
        t1rx=teprx;
        IplImage* hzoom=cvCreateImage(cvSize(640*zoom,480),8,1);
        cvResize(minimage,hzoom);
        //cvShowImage("hzoom",hzoom);
        //cvWaitKey(0);
        
        for(i=0;i<640*(1-zoom);i++)
        {   
            t1lx=teplx*zoom;
            t1rx=teprx*zoom;
            
            cvSet(zoomcrop,CV_RGB(255,255,255));
            cvSetImageROI(zoomcrop,cvRect( i ,0,640*zoom,480));
            cvCopy(hzoom,zoomcrop);
            cvResetImageROI(zoomcrop);
            cvShowImage("zoomcrop",zoomcrop);
            t1lx+=i;
            t1rx+=i;
          //  cvWaitKey(0);
            
            //cvThreshold(zoomcrop, zoomcrop, 128, 255, CV_THRESH_BINARY_INV);
            cvXor(zoomcrop,mask,xorimage);
            count=cvCountNonZero(xorimage);
            if(findmin(count,zoomcrop))
            {
                mint1lx=t1lx;
                mint1rx=t1rx;
            }
            //cvThreshold(zoomcrop, zoomcrop, 128, 255, CV_THRESH_BINARY_INV);
            //cvShowImage("zoominv",zoomcrop);
            
        }
        
        
        cvReleaseImage(&hzoom);
        zoom+=0.05; 
    }
    
    
    
    
    while(zoom<=endzoom)
    {
        IplImage* hzoom=cvCreateImage(cvSize(640*zoom,480),8,1);
        
        cvResize(minimage,hzoom);
        //cvShowImage("hzoom",hzoom);
        //cvWaitKey(0);
        t1lx=teplx*zoom;
        t1rx=teprx*zoom;
            
        
        
        for(i=0;i<640*zoom-640;i++)
        {
            
            
            cvSetImageROI(hzoom,cvRect(i,0,640,480));
            t1lx-=i;
            t1rx-=i;
           // cvShowImage("h",hzoom);
            
            
            cvCopy(hzoom,zoomcrop);
            //cvThreshold(zoomcrop, zoomcrop, 128, 255, CV_THRESH_BINARY_INV);
            cvXor(zoomcrop,mask,xorimage);
            count=cvCountNonZero(xorimage);
            //cvThreshold(zoomcrop, zoomcrop, 128, 255, CV_THRESH_BINARY_INV);
            if(findmin(count,zoomcrop))
            {
                mint1lx=t1lx;
                mint1rx=t1rx;
            }
        
            //cvWaitKey(0);
            cvResetImageROI(hzoom);
        }
        cvReleaseImage(&hzoom);
        zoom+=0.05;
    }
    
    
    //cvShowImage("min",least);
    cvSaveImage("least.jpg",least);
    IplImage* tempmin=cvCreateImage(cvSize(640,480),8,1);
     
    cvCopy(mask,tempmin);
    
    cvCircle(tempmin,cvPoint(mint1lx,teply), 5, CV_RGB(0,0,0), 2, 8, 0);
    cvCircle(tempmin,cvPoint(mint1rx,tepry), 5, CV_RGB(0,0,0), 2, 8, 0);
    
    //cvShowImage("tempmin",tempmin);
    /*
    cout<<"left"<<mint1lx<<" ," <<teply <<'\n';
    cout<<"right"<<mint1rx<<','<<tepry;
    cout<<"   " <<teplx<<" , " <<teprx;
    */
    //cvWaitKey(0);
    plx=mint1lx;
    prx=mint1rx;
    ply=teply;
    pry=tepry;
    
    
}




