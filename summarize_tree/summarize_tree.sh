#!/bin/env bash

dirCount=0
regCount=0

for dir in `find $1 -type d`
do 
	dirCount=$((dirCount+1))
done

for reg in `find $1 -type f`
do
	regCount=$((regCount+1))
done

echo $dirCount
echo $regCount



