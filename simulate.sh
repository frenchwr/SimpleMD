#!/bin/bash

simtype=$1

if [[ $simtype == "bigsim" ]]; 
then
   echo "running: bin/run_md -N 5000 -ts 10000 -xyz 1000 -o 50"
   bin/run_md -N 5000 -ts 10000 -xyz 1000 -o 50
else
   echo "running: bin/run_md -N 125"
   bin/run_md -N 125
fi
