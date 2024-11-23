#!/bin/bash


TEST_PER_THREAD=200

for i in {10..1}; do
	rm time_${i}.txt
	for (( j=1; j<=$TEST_PER_THREAD; j++ )); do
		result=$(./pi_multithreaded $i)
		echo "$j $result" >> "time_${i}.txt" 
	done
	echo -n "$i ";
done