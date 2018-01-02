#!/bin/bash

simtype=$1

if [[ $simtype == "bigsim" ]]; 
then
   echo "running: bin/run_md -N 5000 -ts 10000 -xyz 1000 -o 50"
   bin/run_md -N 5000 -ts 10000 -xyz 1000 -o 50 | tee stdout.log
elif [[ $simtype == "500" ]];
then
   echo "running: bin/run_md -N 500"
   bin/run_md -N 500 | tee stdout.log
elif [[ $simtype == "1000" ]];
then
   echo "running: bin/run_md -N 1000"
   bin/run_md -N 1000 | tee stdout.log
elif [[ $simtype == "2000" ]];
then
   echo "running: bin/run_md -N 2000"
   bin/run_md -N 2000 | tee stdout.log
elif [[ $simtype == "4000" ]];
then
   echo "running: bin/run_md -N 4000"
   bin/run_md -N 4000 | tee stdout.log
else
   echo "running: bin/run_md -N 125"
   bin/run_md -N 125 | tee stdout.log
fi

grep -A 10000000 Timestep stdout.log | grep -v -i time | grep -v -i complete > nums.txt
echo "********Thermo stats (mean/std)********"
awk '{mean += $2; sumsq+=$2*$2} END {print "KE: " mean/NR,"/",sqrt(sumsq/NR - (mean/NR)**2)}' nums.txt
awk '{mean += $3; sumsq+=$3*$3} END {print "PE: " mean/NR,"/",sqrt(sumsq/NR - (mean/NR)**2)}' nums.txt
awk '{mean += $4; sumsq+=$4*$4} END {print "TotE: " mean/NR,"/",sqrt(sumsq/NR - (mean/NR)**2)}' nums.txt
awk '{mean += $5; sumsq+=$5*$5} END {print "Temp: " mean/NR,"/",sqrt(sumsq/NR - (mean/NR)**2)}' nums.txt
awk '{mean += $6; sumsq+=$6*$6} END {print "Pres: " mean/NR,"/",sqrt(sumsq/NR - (mean/NR)**2)}' nums.txt
rm nums.txt
