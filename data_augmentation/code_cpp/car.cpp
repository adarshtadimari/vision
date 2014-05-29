#include"opencv2/opencv.hpp"
#include<iostream>
using namespace cv;
using namespace std;



Mat fn_image(Mat img)
{
    Mat projected;
    float c1,c2,c3;
    //cout<<img.cols;
    Mat reshaped=img.reshape(1,img.rows*img.cols);
    Mat finalMatrix = Mat::zeros(1216,120*120*3,CV_8U);
     
    //cout<<reshaped;
    PCA pca(reshaped,Mat(),CV_PCA_DATA_AS_ROW,3);
    projected=pca.project(reshaped);
    //cout<<projected;

    //Multiplying the projection of each patch pixel onto principal components
    Mat mCompImage;
    Mat reconImage,rIrounded;
        
    
    //Creating 12 new images
   // string filename(argv[1]);
    string subname;
    string cname;
    stringstream s; 
    //int pos=filename.find(".jpg");
    //subname=filename.substr(0,pos);
    int tr1,tr2;
    int count=0;
    Mat resized,translated,imgHSV,imgC,imgCreshaped;
    float spower,vpower;
    for(float c1=0.5;c1<=1.5;c1+=0.5)
    for(float c2=0.5;c2<=1.5;c2+=0.5)
    for(float c3=0.5;c3<=1.5;c3+=0.5)
    {
        projected.copyTo(mCompImage);
        mCompImage.col(0)=projected.col(0)*c1;
        mCompImage.col(1)=projected.col(1)*c2;
        mCompImage.col(2)=projected.col(2)*c3;
        reconImage=pca.backProject(mCompImage);
        Mat reconImageReshaped=reconImage.reshape(3,img.rows);
        reconImageReshaped.convertTo(rIrounded,CV_8U);
        //Saving it onto the file
        resize(rIrounded,resized,Size(128,128));

        //imwrite(cname,rIrounded);
            
        for(tr1=0;tr1<=8;tr1+=4)
        for(tr2=0;tr2<=8;tr2+=4)
        {
            if(tr1==4||tr2==4)
            {
                if(tr1!=4||tr2!=4)
                    continue;
            }
            translated=resized(Rect(tr1,tr2,120,120));
            cvtColor(translated,imgHSV,COLOR_BGR2HSV);
            
            Mat imgfloat; 
            imgHSV.convertTo(imgfloat,CV_32F,1.0/255);
                
            
            
            for(spower=0.5;spower<=1.5;spower+=0.5)
            for(vpower=0.5;vpower<=1.5;vpower+=0.5)
            {
        
                reshaped=imgfloat.reshape(1,imgHSV.rows*imgHSV.cols);
                reshaped.copyTo(imgC);
                cv::pow(reshaped.col(1),spower,imgC.col(1));
                cv::pow(reshaped.col(2),vpower,imgC.col(2));
                imgCreshaped=imgC.reshape(3,imgHSV.rows);
                imgCreshaped.convertTo(imgCreshaped,CV_8U,255.0);
                cvtColor(imgCreshaped,imgCreshaped,COLOR_HSV2BGR);  
              // imshow("imgRe",imgCreshaped);
              // waitKey(0);
                Mat r1=imgCreshaped.reshape(1,imgCreshaped.rows*imgCreshaped.cols);
                Mat rt1=r1.t();
                Mat rt2=rt1.reshape(1,1);
                rt2.row(0).copyTo(finalMatrix.row(count));  
                count++;
                cname=subname+s.str()+".jpg";
                imwrite(cname,imgCreshaped);
            }
 
            

        }





    }
    
    //cout<<reconImageReshaped;
    //imshow("recon",rIrounded);
    //waitKey(0);
    
    return finalMatrix;


}




