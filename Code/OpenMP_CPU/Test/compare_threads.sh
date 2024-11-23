#!/bin/bash


TEST_PER_THREAD=100

for i in {1..20}; do
	mean=0
	for (( j=1; j<=$TEST_PER_THREAD; j++ )); do
		result=$(./pi_multithreaded $i)
		mean=$( echo "scale=5; $mean+$result" | bc);
	done
	echo -n "$i ";
	echo $( echo "scale=5; $mean / $TEST_PER_THREAD" | bc);
done
