#!/bin/sh

export PATH=$PATH:$(pwd)"/bin"

exec 3<challenge4_input
while read -u 3 line; do
    echo $line | challenge3 
done

