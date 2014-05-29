#include"rhog.cpp"

int main(int argc,char *argv[])
{
    char a[10]="abc";
    VideoCapture v(argv[1]);
    VideoWriter vw;
    vw.open("ab.avi",VideoWriter::fourcc('D','I','V','X'),2,Size(128,128));
    char c=0;
    Mat frame;
    Mat gray;
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
            imshow(a,drawrhog(gray));
            a[0]++;
            waitKey(0);
        }
    }
    vw.release();
}

