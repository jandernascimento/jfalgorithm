#!/bin/bash

for i in `seq 1 100`
do
./generator 10 20 2 $i 100
mv test.in instance_10_20_$i
done

