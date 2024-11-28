#!/bin/bash


for i in {0..10}; do
    echo $(./linked_opt1) >> "linked_opt1.txt";
done

for i in {0..10}; do
     echo $(./linked_opt2) >> "linked_opt2.txt";
done
for i in {0..10}; do
     echo $(./linked) >> "linked.txt";
done
