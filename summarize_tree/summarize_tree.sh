#!/bin/env bash

# Assume no directories or files
dirCount=0
regCount=0

# for every directory returned by find, increment the count
for dir in `find $1 -type d`
do 
	dirCount=$((dirCount+1))
done

# for every regular file returned by find, increment the count
for reg in `find $1 -type f`
do
	regCount=$((regCount+1))
done


echo "There were $dirCount directories."
echo "There were $regCount regular files."



