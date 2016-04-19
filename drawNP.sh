#!/bin/sh

#  drawNP.sh
#  
#
#  Created by  Daniele Zanzi Old on 17/11/2013.
#




root -b -q macros/drawPlot_pulls.C+\(\"125\",\"vbf_MVAlike_2011_2012_pulls\"\);

root -b -q macros/drawPlot_pulls.C+\(\"125\",\"boost_MVAlike_2011_2012_pulls\"\);

#root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_vb_MVAlike_2011_2012_pulls\"\);
#root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_deCorrQCDmass_MVAlike_2011_2012_pulls\"\);
#root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_deCorrQCD_MVAlike_2011_2012_pulls\"\);


#root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_MVAlike_2011_2012_pulls\",1,\"comb_vb_MVAlike_2011_2012_pulls\"\);
#root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_MVAlike_2011_2012_pulls\",1,\"comb_deCorrQCDmass_MVAlike_2011_2012_pulls\"\);

#root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_MVAlike_2011_2012_pulls\",1,\"comb_MVAlike_2011_2012_pulls_symm\"\);

#root -b -q macros/drawPlot_pulls.C+\(\"125\",\"boost_MVAlike_2011_2012_pulls\",1,\"boost_MVAlike_2011_2012_pulls_symm\"\);


#root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_MVAlike_2011_2012_pulls_symm\"\);

#root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_MVAlike_2011_2012_pulls_symm\"\);

root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_asimov_MVAlike_2011_2012_pulls\"\);

root -b -q macros/drawPlot_pulls.C+\(\"125\",\"comb_MVAlike_2011_2012_pulls\"\);

