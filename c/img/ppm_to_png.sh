#!/bin/bash 

for ppmname in `find -name '*.ppm'`
do 
echo $ppmname
name=$(basename $ppmname .ppm) 
echo "$name"
pngname="$name.png" 

if [[ ! -f $pngname ]] ; then 

    echo converting "$ppmname" to "$pngname" 
    convert "$ppmname" "$pngname" 
else 
    echo skipping $ppmname beacuse $pngname already exists 
fi 
done 
