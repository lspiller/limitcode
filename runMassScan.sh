#!/bin/sh

#  runMassScan.sh
#  
#
#  Created by  Daniele Zanzi Old on 26/11/2013.
#


### mu_inj = 1
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",100\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",102.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",105\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",107.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",110\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",112.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",115\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",117.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",120\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",122.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",125\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",127.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",130\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",132.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",135\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",137.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",140\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",142.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",145\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",147.5\);
#root -b -q macros/globalInjection.C+\(125,\"comb_MVAlike\",\"combined\",\"ModelConfig\",\"asimovData_1\",\"obsData\",\"conditionalGlobs_1\",\"conditionalNuis_1\",150\);

#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_100_2011_2012_combined_AllSYS_model.root\",100,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_102.5_2011_2012_combined_AllSYS_model.root\",102.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_105_2011_2012_combined_AllSYS_model.root\",105,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_107.5_2011_2012_combined_AllSYS_model.root\",107.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_110_2011_2012_combined_AllSYS_model.root\",110,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_112.5_2011_2012_combined_AllSYS_model.root\",112.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_115_2011_2012_combined_AllSYS_model.root\",115,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_117.5_2011_2012_combined_AllSYS_model.root\",117.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_120_2011_2012_combined_AllSYS_model.root\",120,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_122.5_2011_2012_combined_AllSYS_model.root\",122.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_125_2011_2012_combined_AllSYS_model.root\",125,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_127.5_2011_2012_combined_AllSYS_model.root\",127.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_130_2011_2012_combined_AllSYS_model.root\",130,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_132.5_2011_2012_combined_AllSYS_model.root\",132.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_135_2011_2012_combined_AllSYS_model.root\",135,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_137.5_2011_2012_combined_AllSYS_model.root\",137.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_140_2011_2012_combined_AllSYS_model.root\",140,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_142.5_2011_2012_combined_AllSYS_model.root\",142.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_145_2011_2012_combined_AllSYS_model.root\",145,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_147.5_2011_2012_combined_AllSYS_model.root\",147.5,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);
#root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_inj125_150_2011_2012_combined_AllSYS_model.root\",150,\"comb_MVAlike_2011_2012_inj125_mu\",\"combined\",\"ModelConfig\",\"asimovData_inj\",\"conditionalGlobs_inj\"\);

root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_100_2011_2012_combined_AllSYS_model.root\",100,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_102.5_2011_2012_combined_AllSYS_model.root\",102.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_105_2011_2012_combined_AllSYS_model.root\",105,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_107.5_2011_2012_combined_AllSYS_model.root\",107.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_110_2011_2012_combined_AllSYS_model.root\",110,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_112.5_2011_2012_combined_AllSYS_model.root\",112.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_115_2011_2012_combined_AllSYS_model.root\",115,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_117.5_2011_2012_combined_AllSYS_model.root\",117.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_120_2011_2012_combined_AllSYS_model.root\",120,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_122.5_2011_2012_combined_AllSYS_model.root\",122.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_125_2011_2012_combined_AllSYS_model.root\",125,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_127.5_2011_2012_combined_AllSYS_model.root\",127.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_130_2011_2012_combined_AllSYS_model.root\",130,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_132.5_2011_2012_combined_AllSYS_model.root\",132.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_135_2011_2012_combined_AllSYS_model.root\",135,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_137.5_2011_2012_combined_AllSYS_model.root\",137.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_140_2011_2012_combined_AllSYS_model.root\",140,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_142.5_2011_2012_combined_AllSYS_model.root\",142.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_145_2011_2012_combined_AllSYS_model.root\",145,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_147.5_2011_2012_combined_AllSYS_model.root\",147.5,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
root -b -q macros/runMuhat.C+\(\"results/hh_all_comb_MVAlike_150_2011_2012_combined_AllSYS_model.root\",150,\"comb_MVAlike_2011_2012_mu\",\"combined\",\"ModelConfig\",\"obsData\",\"conditionalGlobs_1\"\);
