#!/bin/sh

#  drawNLL.sh
#  
#
#  Created by  Daniele Zanzi Old on 21/11/2013.
#


python FreiburgStat/trunk/macros/drawPlot_Profile.py -b --f NLLScan/comb --n 'comb' --f2 NLLScan/vbf --n2 'vbf' --f3 NLLScan/boost --n3 'boost'


#python FreiburgStat/trunk/macros/drawPlot_Profile.py -b --f NLLScan/comb_symm --n 'comb' --f2 NLLScan/vbf_symm --n2 'vbf' --f3 NLLScan/boost_symm --n3 'boost'
