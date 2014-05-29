from cv2 import *
import sys
def fn(img):
    
    #resizing it to 128*128
    resized=resize(img,((128,128)))
    namedWindow("translated") 
    #getting translated images
    for i in [0,4,8]:
        for j in [0,4,8]:
            if(i==4 or  j==4):
                if(i!=4 or j!=4):
                    continue
            translated=resized[i:i+120,j:j+120]
            imshow("translated",translated)
            waitKey(0)
    
        
  

if __name__=='__main__':
    print sys.argv[1]
    img=imread(sys.argv[1])
    
    fn(img)
