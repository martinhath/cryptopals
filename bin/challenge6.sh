#!/bin/sh

./challenge6 < ../data6 | 
while read line; do
    echo $line | ./challenge3
done
