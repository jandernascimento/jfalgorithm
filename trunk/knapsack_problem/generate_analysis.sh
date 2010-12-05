#!/bin/bash
#Author: Jander Nascimento
#License: LGPL
#Date: 25 Oct 2010
#Note: make sure you runned make before run this script
function generate_instances {
	for i in `seq -w 1` 
	do
		./generator $1 20 2 $i 100
		mv test.in instances/$1/instance_10_20_$i
	done
}

rm -rf analysis; mkdir analysis

for num in $(echo 1 2 3 4 5 6 7 |cat); do

	test -d instances/$num/ || mkdir -p instances/$num/
	
	echo "#instance;size;greedy time;brute-force time;seqdp time;recdp time" > analysis/algorithm_time_$num.dat
	echo "#instance;size;greedy price;brute-force price; seqdp price; reqdp price" > analysis/algorithm_price_$num.dat
	generate_instances $num;
	
	for l in `ls instances/$num/*`; do
		time_greedy=$(./greedy $l | grep total | cut -d ' ' -f 3) 
		time_bf=$(./brute_force $l | grep total | cut -d ' ' -f 3) 
		time_seqdp=$(./seqdp $l | grep total | cut -d ' ' -f 3) 
		time_recdp=$(./recdp $l | grep total | cut -d ' ' -f 3) 
 		echo "$l;$num;$time_greedy;$time_bf;$time_seqdp;$time_recdp" >> analysis/algorithm_time_$num.dat
		
	
		price_greedy=$(./greedy $l | grep price: | cut -d ':' -f 3)
		price_bf=$(./brute_force $l | grep price: | cut -d ':' -f 3)
		price_seqdp=$(./seqdp $l | grep price: | cut -d ':' -f 3)
		price_recdp=$(./recdp $l | grep price: | cut -d ':' -f 3)
		echo "$l;$num;$price_greedy;$price_bf;$price_seqdp;$price_recdp" >> analysis/algorithm_price_$num.dat
	done;

	cat analysis/algorithm_time_$num.dat | cut -d ';' -f 2,3 | sed 's/;/ /' | grep ^[0-9] >> analysis/time_greedy.tmp
	cat analysis/algorithm_time_$num.dat | cut -d ';' -f 2,4 | sed 's/;/ /' | grep ^[0-9] >> analysis/time_bf.tmp
	cat analysis/algorithm_time_$num.dat | cut -d ';' -f 2,5 | sed 's/;/ /' | grep ^[0-9] >> analysis/time_seqdp.tmp
	cat analysis/algorithm_time_$num.dat | cut -d ';' -f 2,6 | sed 's/;/ /' | grep ^[0-9] >> analysis/time_recdp.tmp

	cat analysis/algorithm_price_$num.dat | cut -d ';' -f 3 | sed 's/;/ /' | grep ^[0-9] >> analysis/price_greedy.tmp
	cat analysis/algorithm_price_$num.dat | cut -d ';' -f 4 | sed 's/;/ /' | grep ^[0-9] >> analysis/price_bf.tmp
	cat analysis/algorithm_price_$num.dat | cut -d ';' -f 5 | sed 's/;/ /' | grep ^[0-9] >> analysis/price_seqdp.tmp
	cat analysis/algorithm_price_$num.dat | cut -d ';' -f 6 | sed 's/;/ /' | grep ^[0-9] >> analysis/price_recdp.tmp

	rm -rf instances/$num
done

	if [ -e "$(which gnuplot)" ]; then
		gnuplot -e "set term png; set output 'analysis/time_analysis.png'; set ylabel 'Time(ms)';set xlabel 'number of items';set title 'Algorithm benchmark - Time consuming'; set autoscale; plot 'analysis/time_greedy.tmp' title 'Greedy' with lines, 'analysis/time_bf.tmp' title 'Brute Force' with lines, 'analysis/time_seqdp.tmp' title 'SeqDP' with lines, 'analysis/time_recdp.tmp' title 'RecDP' with lines";
		gnuplot -e "set term png; set output 'analysis/price_analysis.png'; set ylabel 'Value of the Bag';set xlabel 'number of items';set title 'Algorithm benchmark - Value carried'; set autoscale; plot 'analysis/price_greedy.tmp' title 'Greedy' with lines, 'analysis/price_bf.tmp' title 'Brute Force' with lines, 'analysis/price_seqdp.tmp' title 'SeqDP' with lines, 'analysis/price_recdp.tmp' title 'ReqDP' with lines";
		
		#gnuplot -e "set term png; set output 'analysis/time_analysis.png'; set ylabel 'Time(ms)';set xlabel 'number of items';set title 'Algorithm benchmark - Time consuming'; set autoscale; plot 'analysis/time_greedy.tmp' title 'Greedy' with lines, 'analysis/time_bf.tmp' title 'Brute Force' with lines";
		#gnuplot -e "set term png; set output 'analysis/price_analysis.png'; set ylabel 'Value of the Bag';set xlabel 'number of items';set title 'Algorithm benchmark - Value carried'; set autoscale; plot 'analysis/price_greedy.tmp' title 'Greedy' with lines, 'analysis/price_bf.tmp' title 'Brute Force' with lines";
	fi
	rm analysis/time_greedy.tmp ; rm analysis/time_bf.tmp;
