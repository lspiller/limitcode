#!/bin/bash
. /afs/cern.ch/atlas/project/HSG7/root/root_v5.34.09/x86_64-slc5-gcc43/bin/thisroot.sh

export LD_LIBRARY_PATH="/afs/cern.ch/user/r/ruthmann/analysis/Htt/Common/RootCore/lib:/afs/cern.ch/user/r/ruthmann/scratch0/FrFW/lib:/afs/cern.ch/user/r/ruthmann/scratch0/FrFW/libconfig/.libs:/afs/cern.ch/sw/lcg/external/xrootd/3.2.2/x86_64-slc5-gcc43-opt/lib64:/afs/cern.ch/atlas/project/HSG7/root/root_v5.34.09/x86_64-slc5-gcc43/lib:/afs/cern.ch/sw/lcg/contrib/gcc/4.3.6/x86_64-slc5-gcc43-opt/lib64:/afs/cern.ch/sw/lcg/contrib/mpfr/2.4.2/x86_64-slc5-gcc43-opt/lib:/afs/cern.ch/sw/lcg/contrib/gmp/4.3.2/x86_64-slc5-gcc43-opt/lib:/afs/cern.ch/sw/lcg/external/Python/2.7.3/x86_64-slc5-gcc43-opt/lib:"


cd /afs/cern.ch/user/r/ruthmann/analysis/Htt/TreeTools/Htt2012/PrepareWorkspace/Contours

cmd="root -b -q ' StandardMuTMuW.C+(\"../Thomas_WS/lephad/results/embchi90sths1crs_ajet_H125_combined_AllSys_model.root\",\"combined\",\"ModelConfig\",\"obsData\",__mutin__)'"
${cmd/__mutin__/${1}}
