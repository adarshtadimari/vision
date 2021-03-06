#include"a10v1.cpp"

int main(int argc,char* argv[])
{
	Mat img=imread(argv[1]);
	//fn(img);
	imshow("Image",img);
	VideoCapture cap(0); // open the default camera
	if(!cap.isOpened()) // check if we succeeded
		return -1;
	namedWindow("edges",WINDOW_NORMAL);
	Mat frame,frame2;
	for(;;)
	{
		cap >> frame; // get a new frame from camera
		Mat temp;
		frame.copyTo(temp);
		rectangle(temp,Rect((frame.cols/2)-125,(frame.rows/2)-50,250,100),Scalar(255,0,0),3);
		frame2=frame(Rect((frame.cols/2)-125,(frame.rows/2)-50,250,100));
		imshow("edges", frame);
		imshow("frame2",frame2);
		char c=waitKey(30);
		if(c=='e')
			break;
		else if(c=='y')
		{
			//fn(frame2);
			imshow("out",frame2);
			imwrite("out.jpg",frame2);
			waitKey(0);
		}
		
	}
	// the camera will be deinitialized automatically in VideoCapture destructor
	return 0;

	
}
