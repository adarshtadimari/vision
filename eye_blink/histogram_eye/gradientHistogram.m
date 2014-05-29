function [Ho,Hc]= gradientHistogram(CEye,OEye)

    %CEye = imread(image1); 
    %OEye = imread(image2); 

    GOEye = double(OEye);%rgb2gray(OEye));
    GCEye = double(CEye);%rgb2gray(CEye));

    [fxo, fyo] = gradient(GOEye);
    [fxc, fyc] = gradient(GCEye);

    ho = atan2(fyo , fxo);
    hc = atan2(fyc , fxc);

    x = linspace( -pi, pi, 15);

    Ho = reshape(ho, size(ho,1)*size(ho,2),1);
    Hc = reshape(hc, size(hc,1)*size(hc,2),1);

    subplot(2,2,1)
    hist(Ho, x);
    subplot(2,2,2)
    hist(Hc, x);
    subplot(2,2,3)
    imshow(OEye);
    subplot(2,2,4)
    imshow(CEye);







end
