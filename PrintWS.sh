#!/bin/sh

#  PrintWS.sh
#
#
#  Created by  Daniele Zanzi Old on 05/11/2013.
#


root -b -q PrintWS.C+\(\"/home/lspiller/hh/hhana/workspaces/hh_nos_nonisol_mcz_cuts_fixed/hh_15_combination_125/measurement_hh_15_combination_125.root\"\);
#root -b -q PrintWS.C+\(\"results/hh_all_vbf_MVAlike_125_2011_2012_combined_AllSYS_model.root\"\);
#root -b -q PrintWS.C+\(\"results/hh_all_boost_MVAlike_125_2011_2012_combined_AllSYS_model.root\"\);
latex PrintWS_.tex
dvips -t landscape  PrintWS_.dvi
ps2pdf PrintWS_.ps
#latex PrintWS_VBF.tex
#dvips -t landscape  PrintWS_VBF.dvi
#ps2pdf PrintWS_VBF.ps
#
#latex PrintWS_boost.tex
#dvips -t landscape  PrintWS_boost.dvi
#ps2pdf PrintWS_boost.ps
