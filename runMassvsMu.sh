#!/bin/sh

#  runMassvsMu.sh
#  
#
#  Created by  Daniele Zanzi Old on 07/11/2013.
#

root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_100_2011_2012_combined_AllSYS_model.root","NLLScan/100","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_105_2011_2012_combined_AllSYS_model.root","NLLScan/105","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_110_2011_2012_combined_AllSYS_model.root","NLLScan/110","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_115_2011_2012_combined_AllSYS_model.root","NLLScan/115","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_120_2011_2012_combined_AllSYS_model.root","NLLScan/120","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root","NLLScan/125","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_130_2011_2012_combined_AllSYS_model.root","NLLScan/130","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_135_2011_2012_combined_AllSYS_model.root","NLLScan/135","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_140_2011_2012_combined_AllSYS_model.root","NLLScan/140","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_145_2011_2012_combined_AllSYS_model.root","NLLScan/145","SigXsecOverSM",20, -0.500000, 5.000000)'
root -b -q 'FreiburgStat/trunk/macros/MakeNLLProfile.C+("results/hh_all_comb_MVAlike_inj125_150_2011_2012_combined_AllSYS_model.root","NLLScan/150","SigXsecOverSM",20, -0.500000, 5.000000)'

source drawMassVsMu.sh
