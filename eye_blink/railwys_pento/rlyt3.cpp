

IplImage* fn(IplImage * pantofile, IplImage *frame, float &plx,float &ply,float &prx,float &pry) 
{
    float pwidth= 640;
    float pheight= 144;
    float stzoom= 1.00;
    float ezoom =1.5;
    float sti =0;
    float ei =450;
    
    float distan[2048];
    uint16_t t_gamma[2048];
    uint16_t inv_t_gamma[10000] = {0};
    IplImage* minimage;
    IplImage* mask;
    IplImage* panto;
    IplImage* finimg;
    IplImage* least;
    char saveend[20];

    void vertical();
    void shift();
    void colour();
    void horzoom();
    int mincount=640*480;
    int teplx=plx,teply=ply,teprx=prx,tepry=pry;
    int mn();
    mn();

    int mn()
    {
        panto = pantofile;
        mask = frame;
        //strcpy(saveend,argv[1]);
        least=cvCreateImage(cvSize(640,480),8,1);
        vertical();
        horzoom();
        //shift();
        //colour();
    }


    void vertical()
    {
            int templx=plx,temply=ply,temprx=prx,tempry=pry;
            int mplx=plx,mply=ply,mprx=prx,mpry=pry;       
            float startzoom = stzoom, endzoom = ezoom, zoom=stzoom, minzoom;
            int width = pwidth, height = pheight;
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
        cvShowImage("Minimage",minimage);
        cvWaitKey(0);
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
            cvShowImage("hzoom",hzoom);
            //cvWaitKey(0);
            t1lx=teplx*zoom;
            t1rx=teprx*zoom;
                
            
            
            for(i=0;i<640*zoom-640;i++)
            {
                
                
                cvSetImageROI(hzoom,cvRect(i,0,640,480));
                t1lx-=i;
                t1rx-=i;
                cvShowImage("h",hzoom);
                
                
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
        
        
        cvShowImage("min",least);
        cvSaveImage("least.jpg",least);
        IplImage* tempmin=cvCreateImage(cvSize(640,480),8,1);
            cvCopy(mask,tempmin);
            cvCircle(tempmin,cvPoint(mint1lx,teply), 5, CV_RGB(0,0,0), 2, 8, 0);
            cvCircle(tempmin,cvPoint(mint1rx,tepry), 5, CV_RGB(0,0,0), 2, 8, 0);
            cvShowImage("tempmin",tempmin);
        cvWaitKey(0);
        
        
    }



    void shift()
    {
        int templx=teplx,temply=teply,temprx=teprx,tempry=tepry;
        
        int i;
        IplImage* panto=cvCreateImage(cvSize(640,480),8,1);
        IplImage* img= cvCreateImage(cvSize(640,480),8,1);
        cvCopy(minimage,img);
        cvCopy(mask,panto);
        IplImage* full = cvCreateImage(cvSize(800,480),8,1);
        IplImage* andimg=cvCreateImage(cvSize(640,480),8,1);
        finimg=cvCreateImage(cvSize(640,480),8,1);
        cvSet(full,CV_RGB(255,255,255));
        cvThreshold(panto, panto, 128, 255, CV_THRESH_BINARY_INV);
        cvSetImageROI(full,cvRect(80,0,640,480));
        cvCopy(img,full);
        cvResetImageROI(full);
        
        templx+=80;
        temprx+=80;
        //cvShowImage("Panto inverse",panto);
        //cvShowImage("Full",full);
        //cvWaitKey(0);
        int ttlx,ttly,ttrx,ttry,mlx,mly,mrx,mry;
        int count,max=0;   
        for(i=0;i<=160;i++)
        {
            ttlx=templx;
            ttrx=temprx;
            cvSetImageROI(full,cvRect(i,0,640,480));
            //cvShowImage("Move",full);
            //cvWaitKey(50);
            ttlx-=i;
            ttrx-=i;
            cvXor(full,panto,andimg);
            count=cvCountNonZero(andimg);
            
            if(count>max)
            {
                max=count;
                cvCopy(full,finimg);
                mlx=ttlx;
                mrx=ttrx;
                
            }
                   cvResetImageROI(full);
            
                          
            
        
        }    
        
      //  cvShowImage("finalImage",finimg);
        //cvWaitKey(0);
        teplx=mlx;
        teprx=mrx;
       
        
    }

    void colour()
    {
        IplImage* img=cvCreateImage(cvSize(640,480),8,1);
        IplImage* panto=cvCreateImage(cvSize(640,480),8,1);
        cvCopy(mask,panto);
        cvCopy(finimg,img);
        IplImage * colour=cvCreateImage(cvSize(640,480),8,3);
        int x,y;
        
        
        for(y=0;y<img->height;y++)
        {
            uchar *ptr=(uchar*)(img->imageData + y*img->widthStep);
            uchar *ptr2=(uchar*)(panto->imageData + y*panto->widthStep);
            uchar *ptr3=(uchar*)(colour->imageData + y*colour->widthStep);
            
            for(x=0;x<img->width;x++)
            {
                /*
                if(ptr[x]==0)
                {
                    ptr3[3*x]=0;
                    ptr3[3*x+1]=255;
                    ptr3[3*x+2]=0;
                    
                }
                */
                    if(ptr2[x]==0)
                    {   
                        ptr3[3*x]=255;
                        ptr3[3*x+1]=255;
                        ptr3[3*x+2]=255;
                    
                        
                    }
                    else
                    {
                        ptr3[3*x]=0;
                        ptr3[3*x+1]=0;
                        ptr3[3*x+2]=0;
                    
                    
                    }
                
                
            }
        }   
        
        
        cvCircle(colour,cvPoint(teplx,teply), 5, CV_RGB(255,0,0), 2, 8, 0);
        cvCircle(colour,cvPoint(teprx,tepry), 5, CV_RGB(255,0,0), 2, 8, 0);
        
        char save[50]="save/";
        //strcat(save,saveend);
        //cout<<save;
        //cvSaveImage(save,colour);    
        cvSaveImage("coloured.jpg",colour);
        cvShowImage("coloured",colour);
        cvWaitKey(0);

    }
    return least;    
}

