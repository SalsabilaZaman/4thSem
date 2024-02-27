#!/usr/bin/bash

#echo "Kire tor nam ki"
#read name
#echo 'HI'
#echo
#echo "kire"

#echo "Hi,$1"
#file_name=$(ls -l $filepath | awk '{print $9,$5}')
#echo "$file_name"
echo "Enter directory name:"
read filepath

echo
echo "Finding Files and their Sizes"

cd $filepath
echo "File Name   	Size    	LOC"
for files in *.cpp ; do
file_size=$(ls -l $files | awk '{print $5}')
loc=$(wc -l < "$files")
	echo "$files - $file_size bytes- $loc lines"
done
