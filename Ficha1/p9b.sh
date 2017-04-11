#!/bin/sh

for i in $(seq -f "%02g" 1 10)
do
	if [ ! -d "proj$i" ]; then
		mkdir ./proj$i
	fi
	
chmod +x $p9b

