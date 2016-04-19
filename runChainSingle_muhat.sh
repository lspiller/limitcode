
#!/bin/bash

channel=${1}
mass=${2}
year=${3}
doPulls=${4}

root -b -q macros/runMuhat.C+\(\"results/hh_all_${channel}_${mass}_${year}_combined_AllSYS_model.root\",${mass},\"${channel}_${year}_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\",\"nominalGlobs\"\) | tee root_files/${channel}_${year}_mu/${mass}.runMuhat.out;
