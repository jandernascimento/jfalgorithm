#!/bin/bash

function generate_instances {
	for i in `seq -w 1` 
	do
		./generator $1 20 2 $i 100
		mv test.in instances/$1/instance_10_20_$i
	done
}

rm -rf analysis; mkdir analysis

for num in $(echo 1 3 4 7 10 11 |cat); do

	test -d instances/$num/ || mkdir -p instances/$num/
	
	echo "#instance;size;greedy time;brute-force time" > analysis/algorithm_time_$num.dat
	echo "#instance;size;greedy price;brute-force price" > analysis/algorithm_price_$num.dat
	generate_instances $num;
	
	for l in `ls instances/$num/*`; do
		time_greedy=$(./greedy $l | grep total | cut -d ' ' -f 3) 
		time_bf=$(./brute_force $l | grep total | cut -d ' ' -f 3) 
		echo "$l;$num;$time_greedy;$time_bf" >> analysis/algorithm_time_$num.dat
		
	
		price_greedy=$(./greedy $l | grep price: | cut -d ':' -f 3)
		price_bf=$(./brute_force $l | grep price: | cut -d ':' -f 3)
		echo "$l;$num;$price_greedy;$price_bf" >> analysis/algorithm_price_$num.dat
	done;

	cat analysis/algorithm_time_$num.dat | cut -d ';' -f 2,3 | sed 's/;/ /' | grep ^[0-9] >> analysis/time_greedy.tmp
	cat analysis/algorithm_time_$num.dat | cut -d ';' -f 2,4 | sed 's/;/ /' | grep ^[0-9] >> analysis/time_bf.tmp

	cat analysis/algorithm_price_$num.dat | cut -d ';' -f 3 | sed 's/;/ /' | grep ^[0-9] >> analysis/price_greedy.tmp
	cat analysis/algorithm_price_$num.dat | cut -d ';' -f 4 | sed 's/;/ /' | grep ^[0-9] >> analysis/price_bf.tmp

	rm -rf instances/$num
done

	gnuplot -e "set term png; set output 'analysis/time_analysis.png'; set ylabel 'Time(seconds)';set xlabel 'number of items';set title 'Algorithm benchmark - Time consuming'; set autoscale; plot 'analysis/time_greedy.tmp' title 'Greedy' with lines, 'analysis/time_bf.tmp' title 'Brute Force' with lines";	
	gnuplot -e "set term png; set output 'analysis/price_analysis.png'; set ylabel 'Value of the Bag';set xlabel 'number of items';set title 'Algorithm benchmark - Value carried'; set autoscale; plot 'analysis/price_greedy.tmp' title 'Greedy' with lines, 'analysis/price_bf.tmp' title 'Brute Force' with lines";	
	rm analysis/time_greedy.tmp ; rm analysis/time_bf.tmp;
