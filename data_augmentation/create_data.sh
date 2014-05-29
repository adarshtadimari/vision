#!/bin/bash

#compile combined_augment2.cpp 
#create a backup of lfw_funneled 
#run it from a directory such that path to the image is of the form a/b/c.jpg
dir=samples
find $dir -name '*.jpg' > list_all.list

for i in `cat list_all.list`;do
./tr2 $i
done

#removing the original images and keeping only the duplicated images
for i in `cat list_all.list`;do
rm $i
done

#there will be 432 images created from each image

find $dir -name '*.jpg' > list_aug.list
prev=""
count=0
number=0
for i in `cat list_aug.list`;do
    current=`echo $i | cut -d'/' -f 2`
    if [ "$current" != "$prev" ];
    then
        number=1
        count=$((count+1))
        echo $i $count >> list_wclass_train.list
        prev=$current
    else
        number=$((number+1))
        if [ $number -gt 360 ]; 
        then
            echo $i $count >> list_wclass_test.list
        elif [ $number -gt 300 ];
        then
            echo $i $count >> list_wclass_valid.list
        else
            echo $i $count >> list_wclass_train.list
        fi    
    fi
done

