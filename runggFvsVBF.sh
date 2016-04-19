#!/bin/sh

#  runggFvsVBF.sh
#  
#
#  Created by  Daniele Zanzi Old on 07/11/2013.
#

root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",650\)  | tee script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",750\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",850\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",950\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",1050\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",1150\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",1250\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",1350\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",1450\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",1550\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
root -b -q script_2D_ggFVBF/StandardMuTMuW.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData_inj\",1650\)  | tee -a script_2D_ggFVBF/ggVsVBF.txt;
