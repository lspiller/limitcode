#!/bin/sh

#  drawPlots.sh
#  
#
#  Created by  Daniele Zanzi Old on 07/11/2013.
#

root -b -q macros/drawPlot_limit.C\(\"comb_MVAlike_2011_2012\",1,0,\"vbf_MVAlike_2011_2012:VBF\",\"boost_MVAlike_2011_2012:Boost\"\)

root -b -q macros/drawPlot_p0.C\(\"comb_MVAlike_2011_2012\",1,0,\"vbf_MVAlike_2011_2012\",\"boost_MVAlike_2011_2012\"\)
mv eps_files/comb_MVAlike_2011_2012_sig_p0_comp.eps eps_files/comb_MVAlike_2011_2012_sig_p0_comp_cat.eps
mv pdf_files/comb_MVAlike_2011_2012_sig_p0_comp.pdf pdf_files/comb_MVAlike_2011_2012_sig_p0_comp_cat.pdf
root -b -q macros/drawPlot_p0.C\(\"comb_MVAlike_2011_2012\",1,0,\"comb_MVAlike_2011_2012_inj105:m_{H}=105\ GeV\",\"comb_MVAlike_2011_2012_inj125:m_{H}=125\ GeV\",\"comb_MVAlike_2011_2012_inj145:m_{H}=145\ GeV\"\)


root -b -q macros/drawPlot_muhat.C\(\"comb_MVAlike_2011_2012\",1,0\)
root -b -q macros/drawPlot_muhat.C\(\"comb_MVAlike_2011_2012\",1,1,\"comb_MVAlike_2011_2012_inj125:m_{H}=125\ GeV\"\)
mv eps_files/comb_MVAlike_2011_2012_mu_comp_zoom.eps eps_files/comb_MVAlike_2011_2012_mu_comp_zoom_125.eps
mv pdf_files/comb_MVAlike_2011_2012_mu_comp_zoom.pdf pdf_files/comb_MVAlike_2011_2012_mu_comp_zoom_125.pdf

root -b -q macros/drawPlot_muhat.C\(\"comb_MVAlike_2011_2012\",1,1,\"comb_MVAlike_2011_2012_inj105:m_{H}=105\ GeV\"\)
mv eps_files/comb_MVAlike_2011_2012_mu_comp_zoom.eps eps_files/comb_MVAlike_2011_2012_mu_comp_zoom_105.eps
mv pdf_files/comb_MVAlike_2011_2012_mu_comp_zoom.pdf pdf_files/comb_MVAlike_2011_2012_mu_comp_zoom_105.pdf

root -b -q macros/drawPlot_muhat.C\(\"comb_MVAlike_2011_2012\",1,1,\"comb_MVAlike_2011_2012_inj145:m_{H}=145\ GeV\"\)
mv eps_files/comb_MVAlike_2011_2012_mu_comp_zoom.eps eps_files/comb_MVAlike_2011_2012_mu_comp_zoom_145.eps
mv pdf_files/comb_MVAlike_2011_2012_mu_comp_zoom.pdf pdf_files/comb_MVAlike_2011_2012_mu_comp_zoom_145.pdf

