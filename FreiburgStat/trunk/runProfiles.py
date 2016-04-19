# Author      : Stefan Gadatsch
# Email       : gadatsch@nikhef.nl
# Date        : 2013-04-24
# Description : Submit jobs to LSF for computing pulls

import os
import ROOT
from ROOT import *
from sys import exit

import argparse
parser = argparse.ArgumentParser()
parser.add_argument("workspace", type=str, help="Path to workspace to run on.")
parser.add_argument("--folder", type=str, default="test", help="Identifier for the workspace")
parser.add_argument("--compileRunPulls", help="Compile runPulls.C", action="store_true")
parser.add_argument("--queue", type=str, default="8nh", help="Queue to submit to.")
parser.add_argument("--workspaceName", type=str, default="combined", help="Name of the workspace.")
parser.add_argument("--NPName", type=str, default="", help="Name of the nuisance parameter you want to submit on")
parser.add_argument("--ModelConfigName", type=str, default="ModelConfig", help="Name of the ModelConfig.")
parser.add_argument("--dataName", type=str, default="obsData", help="Name of the dataset.")
parser.add_argument("--poiName", type=str, default="SigXsecOverSM", help="Name of the POI.")
parser.add_argument("--doInitialFit", action="store_true", help= "perform an initial fit and store it in the ws under the name 'globalFit'" )

parser.add_argument("--precision", type=str, default="0.005", help="Precision of uncertainty evaluation.")
parser.add_argument("--useMinos", type=str, default="1", help="Use Minos to compute uncertainties, default is findSigma.")
parser.add_argument("--loglevel", type=str, default="INFO", help="Control the printout.")
parser.add_argument("--NPoints",type=int,default=10)
parser.add_argument("--Min",type=float,default=-2)
parser.add_argument("--Max",type=float,default=2)
parser.add_argument("--Split",type=int,default=1)
parser.add_argument("--dry",default=False,action="store_true")

args = parser.parse_args()

workspace = args.workspace
folder = args.folder
compileRunPulls = args.compileRunPulls
queue = args.queue
workspaceName = args.workspaceName
ModelConfigName = args.ModelConfigName
dataName = args.dataName
poiName = args.poiName
precision = args.precision
useMinos = args.useMinos
loglevel = args.loglevel
npoints = args.NPoints
low = args.Min
high= args.Max
split = args.Split

def submitJob(variable):
    bsubFile = open("bsub/"+folder+"/"+variable+"{}_{}.sh".format(low,high), "w")
    text = getJobDef(variable)
    bsubFile.write(text)
    bsubFile.close()
    os.system("chmod -R 775 bsub/"+folder)
    command = "bsub < bsub/"+folder+"/"+variable+"{}_{}.sh".format(low,high)
    print
    print command
    os.system(command)


def getJobDef(variable):

    text = """
#!/bin/bash

#BSUB -J %s
#BSUB -o bsub/%s/stdout_%s_%i_%i.out
#BSUB -q %s
#BSUB -u $USER@cern.ch

WORKDIR=$TMPDIR/LSF_$LSB_JOBID
HOMEDIR=%s
OUTDIR=$HOMEDIR
FOLDER=%s

stagein()
{
  uname -a

  mkdir -vp ${WORKDIR}
  cd ${HOMEDIR} 2> /dev/null || { echo "The directory does not exist."; exit -1; }
  echo Current folder is
  pwd
  ls -l

  export LD_LIBRARY_PATH="/afs/cern.ch/sw/lcg/external/xrootd/3.2.2/x86_64-slc5-gcc43-opt/lib64:/afs/cern.ch/atlas/project/HSG7/root/root_v5-34-00-patches_130919/x86_64-slc5-gcc43/lib:/afs/cern.ch/sw/lcg/contrib/gcc/4.3.6/x86_64-slc5-gcc43-opt/lib64:/afs/cern.ch/sw/lcg/contrib/mpfr/2.4.2/x86_64-slc5-gcc43-opt/lib:/afs/cern.ch/sw/lcg/contrib/gmp/4.3.2/x86_64-slc5-gcc43-opt/lib:/afs/cern.ch/sw/lcg/external/Python/2.7.3/x86_64-slc5-gcc43-opt/lib:"
  . /afs/cern.ch/atlas/project/HSG7/root/root_v5-34-00-patches_130919/x86_64-slc5-gcc43/bin/thisroot.sh
}

runcode()
{
  ulimit -S -s 20000
""" % (variable, folder, variable, low,high,queue, home_folder, folder)

    text += """
  root -b -q 'macros/MakeNLLProfile.C+(\"%s\",\"%s\",\"%s\",%i, %f, %f)'
    """ % (workspace, folder, variable, npoints,low,high)

    text += """
}

stageout()
{
  cd ${WORKDIR}

  cd ${OUTDIR}; ls -l
}

stagein
runcode
stageout

exit
"""
    return text

os.system("mkdir -vp bsub/%s" % folder)
os.system("mkdir -vp root-files/%s" % folder)
os.system("mkdir -vp %s" % folder)

home_folder = os.getcwd()

ret = 0


if compileRunPulls:
    # os.system("cp macros/runPulls.C bsub/%s/." % folder)
    ret += os.system("root -b -q macros/MakeNLLProfile.C+")

if ret != 0:
    print "Error in compilation"
else:

    openMode="READ"
    if args.doInitialFit:
        openMode="UPDATE"
        print "Will create an initial fit on the workspace.. this might take quite a while"
        gROOT.ProcessLine(".L macros/MakeNLLProfile.C+")
        ROOT.MakeInitialFit(workspace)
        exit()

    file = TFile(workspace,openMode)

    ws = file.Get(workspaceName)
    mc = ws.obj(ModelConfigName)
    mc.GetNuisanceParameters().Print()
    
    if args.NPName is not "": 
        params = mc.GetNuisanceParameters()
        params.add( mc.GetParametersOfInterest() )
        nitr = params.createIterator()
    else: nitr = mc.GetNuisanceParameters().createIterator()

        
#    nitr = mc.GetNuisanceParameters().createIterator()
    v=nitr.Next()
    n=0
    allNPs=[]
    while (v):
        
        varName = str(v.GetName())
        allNPs.append(varName)
        #print varName
        if args.NPName is not "" and varName != args.NPName: 
            v=nitr.Next() 
            continue
        
        if  "gamma_stat" in varName or "_shape_LH" in varName or "_norm_" in varName:
            v=nitr.Next()
            continue
        
        if split>1:
            npoints = args.NPoints / split
            step = float(args.Max-args.Min) / float(split)
            print "Step={}".format(step)
            high=low
            # exit()
            while high < args.Max:
                high += step
                print "Submitt on {} low={} max={} npoints={}".format(varName,low,high,npoints)
                if not args.dry:
                    #pass
                    submitJob(varName)
                n+=1
                low += step
                
        else:
            if not args.dry:
                print "Submitt on {} low={} max={} npoints={}".format(varName,low,high,npoints)

                #pass
                submitJob(varName)
            n+=1
        v=nitr.Next()
        
        npoints = args.NPoints
        low = args.Min
        high= args.Max





print "Submitted {} jobs".format(n)
if n==0: 
    print "Could not find any mathcin NP. Here is a list of all"
    for np in   allNPs:
        print np
