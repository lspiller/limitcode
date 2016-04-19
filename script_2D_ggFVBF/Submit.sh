#!/bin/bash

start=150
end=3750
step=100

for i in `seq $start $step $end`;
do
    bsub -q  8nh "Run.sh $i"
#    echo $i
done
