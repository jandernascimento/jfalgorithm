#!/bin/bash

echo "#instance;greedy;brute_force" >> algorithm_acurracy.dat

for l in $(ls trial/*); do

price_greedy=$(./greedy $l | grep price: | cut -d ':' -f 3)
price_bf=$(./brute_force $l | grep price: | cut -d ':' -f 3)

echo "$l;$price_greedy;$price_bf" >> ./algorithm_acurracy.dat


done;
