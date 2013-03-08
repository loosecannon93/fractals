#!/bin/bash 

for file in `find -name '*.ppm'`
do 
name=`basename $file  .ppm` 
convert $name.ppm $name.png
done 
