#!/bin/bash

channel=${1}
mass=${2}
year=${3}
doPulls=${4}

root -b -q macros/runSig.C+\(\"results/hh_all_${channel}_${mass}_${year}_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"asimovData_1\",\"conditionalGlobs_1\",\"nominalGlobs\",\"${mass}\",\"${channel}_${year}_sig\"\) | tee root_files/${channel}_${year}_sig/${mass}.runSig.out;
root -b -q macros/runAsymptoticsCLs.C+\(\"results/hh_all_${channel}_${mass}_${year}_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"asimovData_0\",\"${channel}_${year}_cls\",\"${mass}\",0.95\) | tee root_files/${channel}_${year}_cls/${mass}.runAsymptoticsCLs.out;
