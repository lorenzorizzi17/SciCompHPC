#!/bin/bash


TEST_PER_THREAD=100

for i in {1..10}; do
	rm time_${i}.txt
	for (( j=1; j<=$TEST_PER_THREAD; j++ )); do
		result=$(./pi_multithreaded $i)
		echo "$j $result" >> "time_${i}.txt"
	done
	echo -n "$i ";
done
