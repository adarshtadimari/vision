from cv2 import *
import sys
from numpy import *
def pca(img):
   
    #reshaping it to img.rows*img.cols,i
    reshaped=img.reshape((size(img,0)*size(img,1),3))
    #finding the principal components
    mean1,eigenvectors = PCACompute(reshaped,mean(reshaped,axis=0).reshape(1,-1))
 
    #project data onto the principal components
    projection = PCAProject(reshaped,mean1,eigenvectors)
    #print projection
    #print mean,eigenvectors
    l=zeros(projection.shape)
    for c1 in [0.5,1,1.5]:
        for c2 in [0.5,1,1.5]:
            for c3 in [0.5,1,1.5]:
                                
                #multiply prin components with different values
                l[:,0]=projection[:,0]*c1;
                l[:,1]=projection[:,1]*c2;
                l[:,2]=projection[:,2]*c3;

                #backproject
                backProjection = PCABackProject(l,mean1,eigenvectors)
		print backProjection.max(),backProjection.min()	                
		#convert to int
                backProjection1 = backProjection.astype(uint8)
                reshapedBack = backProjection1.reshape((size(img,0),size(img,0),3))
                
                print 'reshaped',reshapedBack
                print 'img',img
                print shape(reshapedBack)
                print shape(img)
                print c1,c2,c3
                imshow("reshaped",reshapedBack)
                waitKey(0)
                

                






if __name__=='__main__':
    #print sys.argv[1]
    img=imread(sys.argv[1])
    pca(img)
