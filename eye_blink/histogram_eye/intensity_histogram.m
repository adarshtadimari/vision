function intensity_histogram
    openEye=imread('openeye.png');
    closedEye=imread('eyeclose.png');
    openg=rgb2gray(openEye);
    closeg=rgb2gray(closedEye);
    figure(1)
    subplot(2,2,1)
    imshow(openg);
    subplot(2,2,2)
    imshow(closeg);
    subplot(2,2,3)
    imhist(openg);
    subplot(2,2,4);
    imhist(closeg);
end
