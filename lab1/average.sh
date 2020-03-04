#!/bin/bash
cat /dev/null > numbers.txt
count=$(shuf -i 0-1000 -n 1)
shuf -i 0-1000 -n $count -o numbers.txt
sum=0
for lines in $(cat numbers.txt)
do
((sum+= lines))
done
average=$(( $sum / $count))
echo "count: $count"
echo "average: $average" 
