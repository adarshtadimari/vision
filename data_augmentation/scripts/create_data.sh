#!/bin/bash

#compile combined_augment2.cpp 
#create a backup of lfw_funneled 
#run it from a directory such that path to the image is of the form a/b/c.jpg
obfile=tr #objectfile
dir=samples #lfw_funneled fir
list=list_all.list
list_aug=list_aug_all.list
list_wclass=list_wclass.list
find $dir -name '*.jpg' > $list

for i in `echo $list`;do
$obfile $i
done

#removing the original images and keeping only the duplicated images
for i in `echo $list`;do
rm $i
done

#there will be 432 images created from each image

find $dir -name '*.jpg' > $list_aug
prev=""
count=0
for i in `echo $list_aug`;do
    
    current=`echo $i | cut -d'/' -f 2`
    if [ $current != $prev ];
        then
        count=$((count+1))
        echo $i $count >> $list_wclass
        prev=$current
    else
        echo $i $current >> $list_wclass 


done

