#!/bin/bash

make

while :
do
    echo Test:
    python3 case_generator.py -t 1
    ./main IDS
    ./check
    result=$(cat ./data/result.txt)
    if [ ${result} -eq AC ];
    then
        echo PASS
    fi 
        echo WRONG
    sleep 1
done    
