#include"rhog.cpp"
int main(int argc,char* argv[])
{
    Mat img=imread(argv[1],0);
    imshow("R-HOG",drawrhog(img));
    waitKey(0);
}


