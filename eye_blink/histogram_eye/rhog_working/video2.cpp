#include"rhog.cpp"

int main(int argc,char *argv[])
{
    char a[10]="abc";
    char open[15]="aopen.jpg";
    char close[15]="aclose.jpg";

    VideoCapture v(argv[1]);
    VideoWriter vw;
    vw.open("ab.avi",VideoWriter::fourcc('D','I','V','X'),2,Size(128,128));
    char c=0;
    Mat frame;
    Mat gray;
    int count=0;
    while(c!='q')
    {
        v>>frame;
        cvtColor(frame,gray,COLOR_BGR2GRAY);
        equalizeHist(gray,gray);
        imshow("frame",gray);
        c=waitKey(150);
        imshow("rhog",drawrhog(gray));
        
        if(c=='p')
        {
            //imshow(a,drawrhog(gray));
            imwrite(open,drawrhog(gray));
            //a[0]++;
            open[0]++;
            waitKey(0);
        }
        if(c=='r')
        {
            //imshow(a,drawrhog(gray));
            imwrite(close,drawrhog(gray));
            //a[0]++;
            close[0]++;
            waitKey(0);
        }

    }
    vw.release();
}

