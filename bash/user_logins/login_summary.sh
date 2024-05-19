cd /home/ubuntu/Documents/4thSem/bash/user_logins

echo "File Name   	Size    	LOC"
for files in *.txt ; do
file_size=$(ls -l $files | awk '{print $7}')
loc=$(wc -l < $files)
	echo "$files - $file_size bytes- $loc lines"
done
