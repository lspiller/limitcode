#!/bin/bash

#root -b -q macros/runPulls.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"SigXsecOverSM\",\"combined\",\"ModelConfig\",\"obsData\",\"comb_MVAlike_2011_2012_pulls\"\);


root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"comb_MVAlike_2011_2012_pulls\",\"macros/muhat_breakdown.xml\",\"add\",\"tes\"\);
root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"comb_MVAlike_2011_2012_pulls\",\"macros/muhat_breakdown.xml\",\"add\",\"jes\"\);
root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"comb_MVAlike_2011_2012_pulls\",\"macros/muhat_breakdown.xml\",\"add\",\"taueff\"\);
root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"comb_MVAlike_2011_2012_pulls\",\"macros/muhat_breakdown.xml\",\"add\",\"datadriven\"\);
root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"comb_MVAlike_2011_2012_pulls\",\"macros/muhat_breakdown.xml\",\"add\",\"theory\"\);
root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"comb_MVAlike_2011_2012_pulls\",\"macros/muhat_breakdown.xml\",\"add\",\"experimental\"\);
root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"comb_MVAlike_2011_2012_pulls\",\"macros/muhat_breakdown.xml\",\"add\",\"srstat\"\);
root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"comb_MVAlike_2011_2012_pulls\",\"macros/muhat_breakdown.xml\",\"add\",\"mcstat\"\);
root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"comb_MVAlike_2011_2012_pulls\",\"macros/muhat_breakdown.xml\",\"add\",\"total\"\);
#root -b -q macros/runPulls.C+\(\"results/hh_all_vbf_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"SigXsecOverSM\",\"combined\",\"ModelConfig\",\"obsData\",\"vbf_MVAlike_2011_2012_pulls\"\);

#root -b -q macros/runBreakdown.C+\(\"results/hh_all_vbf_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"vbf_MVAlike_2011_2012_pulls\"\);



#root -b -q macros/runPulls.C+\(\"results/hh_all_boost_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"SigXsecOverSM\",\"combined\",\"ModelConfig\",\"obsData\",\"boost_MVAlike_2011_2012_pulls\"\);

#root -b -q macros/runBreakdown.C+\(\"results/hh_all_boost_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"obsData\",\"SigXsecOverSM\",\"boost_MVAlike_2011_2012_pulls\"\);


#root -b -q macros/runPulls.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"SigXsecOverSM\",\"combined\",\"ModelConfig\",\"asimovData\",\"comb_asimov_MVAlike_2011_2012_pulls\"\);

#root -b -q macros/runBreakdown.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",\"combined\",\"ModelConfig\",\"asimovData\",\"SigXsecOverSM\",\"comb_asimov_MVAlike_2011_2012_pulls\"\);






