#include"cv.h"
#include"highgui.h"
#include<stdio.h>
int main()
{
    IplImage* least=cvLoadImage("least.jpg");
    printf("%d",least->height);
    

}
