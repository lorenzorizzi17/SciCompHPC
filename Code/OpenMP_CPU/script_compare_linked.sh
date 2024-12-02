#!/bin/bash


for i in {0..40}; do
    echo "$i $(./linked_opt1)" >> "linked_opt1.txt";
done

for i in {0..40}; do
    echo "$i $(./linked_opt2)" >> "linked_opt2.txt";
done
for i in {0..40}; do
    echo "$i $(./linked))" >> "linked.txt";
done
