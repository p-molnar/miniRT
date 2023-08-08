#!/usr/bin/env bash

declare -i count
count=1
for scene in scenes/*; do
	echo "#${count}	${scene}"
	./miniRT $scene
	count+=1
done