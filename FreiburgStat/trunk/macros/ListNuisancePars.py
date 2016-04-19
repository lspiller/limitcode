import math
import subprocess
import functools
from optparse import OptionParser

@functools.total_ordering
#_____________________________________________________________________________
#_____________________________________________________________________________
class Systematic(object):
    def __init__(self,name,high=1.0,low=1.0,shaped=False):
        self._name=name
        self._shaped=shaped
        self._high=high
        self._low=low

        self._total= (abs(1.-self._high) +  abs(1.-self._low)) /2.

        self._class=name
        if "JES" in name or  "JER" in name or "JVF" in name :self._class="JES"
        elif "TES" in name :self._class="TES"
        elif "MET" in name :self._class="MET"
        elif "_EL_" in name :self._class="EL"
        elif "_MU_" in name :self._class="MU"
#        elif "pdf" in name :self._class="PDF"
        elif "BTag" in name :self._class="BTAG"
        elif "QCDscale" in name or "Qmass" in name or "BR_tautau" in name or "UE_" in name or "pdf" in name:self._class="THEO"
        elif "MFS" in name or "ISOL" in name :self._class="EMB"
        elif "TRIG" in name :self._class="Trig"
        elif "TAU" in name: self._class="Tau"
        elif "ANA_LH" in name: self._class="KFac"

    def MakeTotal(self):
        self._total= (abs(1.-self._high) +  abs(1.-self._low)) /2.
    def __lt__(self,other):
        totalErr=( abs(1.-self._high) + abs(1.-self._low)) / 2.
        OthertotalErr=( abs(1.-other._high) + abs(1.-other._low))/2.
        return totalErr<OthertotalErr
    def __eq__(self,other):
        totalErr=( abs(1.-self._high) + abs(1.-self._low)) / 2.
        OthertotalErr=( abs(1.-other._high) + abs(1.-other._low))/2.
        return totalErr == OthertotalErr

    def Add(self,otherSyst):
        ## not clear how to properly combine two systs with different up/down variation.. just combine the average
        self._high =1
        self._low =1
        #print "Adding: old total={}, add total={} new total={}".format(self._total, otherSyst._total, math.sqrt(self._total **2 + otherSyst._total**2)  )
        self._total =  math.sqrt(self._total **2 + otherSyst._total**2)
                

#_____________________________________________________________________________
#_____________________________________________________________________________
class Sample(object):
    '''
    A sample is named and holds a list of systematics
    '''
    def __init__(self,name):
        self._name=name
        self._systematics=[]

    def GetReducedListofSystematics(self):
        '''
        Returns a list of systematics, which was reduced down to the syst classes
        '''
        reducedList=[]
        reducedListNames=[]

        for syst in self._systematics:
            if syst._class not in reducedListNames:
                #print "{} Creating new reduced syst class {} : {} - {}".format(self._name,syst._class,syst._high,syst._low )
                newSyst = Systematic(syst._class,syst._high,syst._low)
                reducedList.append(newSyst)
                reducedListNames.append(syst._class)
            else:
                for Reducedsyst in reducedList: 
                    if syst._class == Reducedsyst._name: 
                        #print "{} Adding to reduced syst class {} : {} - {}".format(self._name,syst._class,syst._high,syst._low )
                
                        Reducedsyst.Add(syst)
        return reducedList

#_____________________________________________________________________________
#_____________________________________________________________________________
class Category(object):
    def __init__(self,name):
        self._name=name
        self._samples=[]

    def printit(self):
        print " ============================ "
        print "   {} " .format(self._name)
        print " ============================ "
        for sample in self._samples:
            print " ******************************"
            print "   {} ".format(sample._name)
            print " ******************************"
            sample._systematics.sort(reverse=True)
            for syst in sample._systematics:
                color=""
                if syst._shaped: color="\033[94m"
                print color+"{} - {}  {}%   {} : High={} Low={}  Shaped:{}".format(self._name,sample._name, (abs(1.-syst._high) + abs(1.-syst._low))/2.*100  , syst._name,syst._high,syst._low,syst._shaped) + '\033[0m'
        print ""
        print ""

    #_____________________________________________________________________________
    #_____________________________________________________________________________
    def printShapes(self,systList=None,AddNewSysts=True):
        '''
        Make a table
        Rows: Samples
        Columns: Systs
        tick the systs which are shapes
        
        if systList=None will print all systs which are shape in one sample
        if a list is provided make the table for these systs
        '''
        
        if systList is None: 
            # Make a list of all shape systs
            systList=[]
            for sample in self._samples:
                for syst in sample._systematics:
                    if syst._shaped and syst._name not in systList: systList.append( syst._name )
        else:
            for sample in self._samples:
                for syst in sample._systematics:
                    if syst._shaped and syst._name not in systList: 
                        print "The systlist you provided is not complete "
                        if AddNewSysts:
                            systList.append( syst._name )

        print " ======================================================== "
        print "  ShapeSyst Table  {} " .format(self._name)
        print " ======================================================== "

        columnWidth="12"
        # Build the headline
        firstline =("{:"+columnWidth+"s}|").format( "" )
        for syst in systList:firstline+= ("{:"+columnWidth+"s}|").format(syst.replace("ATLAS_","").replace("2012","").replace("_","").replace("ANALH12Wlnu01jetDETAOS","wrewDeta").replace("ANALH12Wlnu01jetPTRATOS","wrewPt").replace("JES","J").replace("FAKE","_f").replace("Fake","_f").replace("FlavComp","FlCo").replace("Modelling","Model") )
        print firstline

        # loop through samples
        for sample in self._samples:
            sampleName = sample._name.replace("ATLAS_","")
            line = ("{:"+columnWidth+"s}|").format( sampleName )
            for syst in systList:
                exists = ""
                for sampleSyst in  sample._systematics:
                    if syst in sampleSyst._name and sampleSyst._shaped : exists=" X "
                line+=("{:"+columnWidth+"s}|").format( exists )
            print line

        return systList

    #_____________________________________________________________________________
    #_____________________________________________________________________________
    def printReducedSystTable(self,systList=None,AddNewSysts=True):
        '''
        Make a table
        Rows: Samples
        Columns: Systs
        Give the combined syst lo/hi
        
        if systList=None will print all systs which are shape in one sample
        if a list is provided make the table for these systs
        '''
        
        if systList is None: 
            # Make a list of all systs
            systList=[]
            for sample in self._samples:
                for syst in sample._systematics:
                    if syst._class not in systList: systList.append( syst._class )
        else:
            for sample in self._samples:
                for syst in sample._systematics:
                    if syst._class not in systList: 
                        print "The systlist you provided is not complete "
                        if AddNewSysts:
                            systList.append( syst._class )

        print " ======================================================== "
        print "  Syst Table  {} " .format(self._name)
        print " ======================================================== "

        columnWidth="12"
        # Build the headline
        firstline =("{:"+columnWidth+"s}|").format( "" )
        for syst in systList:firstline+= ("{:"+columnWidth+"s}|").format(syst.replace("ATLAS_","").replace("2012",""))
        print firstline

        # loop through samples
        for sample in self._samples:
            sampleName = sample._name
            listOfSysts =  sample.GetReducedListofSystematics()

            line = ("{:"+columnWidth+"s}|").format( sampleName )
            answer=""
            for syst in systList:
                answer=0
                for sampleSyst in listOfSysts:
                    if syst == sampleSyst._name:
                        answer = round( sampleSyst._total*100 ,1)

                line+=("{:"+columnWidth+"s}|").format( str(answer)+"%" )
            print line

        return systList
                
#_____________________________________________________________________________
#_____________________________________________________________________________

def cb(option, opt_str, value, parser):
#    print opt_str
#    print parser.rargs
    args=[]
    for arg in parser.rargs:
        if arg[0] != "-":
            args.append(arg)
        else:
            del parser.rargs[:len(args)]
            break
    if getattr(parser.values, option.dest):
        args.extend(getattr(parser.values, option.dest))
    setattr(parser.values, option.dest, args)


#_____________________________________________________________________________
#_____________________________________________________________________________
parser = OptionParser()
parser.add_option('-f', '--files',
                  action='callback',
                  callback=cb,
                  dest="files")
parser.add_option('-s', '--shape',
                  dest="shape",
                  action="store_true"
              )
parser.add_option( '--full',
                  dest="full",
                  action="store_true"
              )
parser.add_option( '--reduced',
                  dest="reduced",
                  action="store_true"
              )
(options, args) = parser.parse_args()
#_____________________________________________________________________________
#_____________________________________________________________________________




Categories=[]
for f in options.files: 
    #print "================================================"
    #print "  {}    ".format(f)
    #print "================================================"
    cat = Category(f)

    with open(f) as inFile:
        content = inFile.readlines()


    # Go through this category line by line - Each sample on its own
    tmpSample=None
    for line in content:
        
        # A new sample starts
        if "Sample" in line and not "</Sample>" in line: 
            if tmpSample is not None: 
                cat._samples.append(tmpSample)

            tmpSample = Sample(line.split('"')[1])
#            print line.split('"')[1]

        if "HistoSys" in line and not "<!--" in line: 
            systs = tmpSample._systematics
            name = line.split('"')[1]
#            print line.split('"')[1]
            
            done = False
            for syst in systs:
                if syst._name == name:
                    syst._shaped=True
                    done = True
            if not done: 
                tmpSyst = Systematic(name,shaped=True)
                tmpSample._systematics.append(tmpSyst)


        if "OverallSys" in line: 
            name = line.split('"')[1]
#            print line.split('"')[1]
            
            done = False
            systs = tmpSample._systematics
            i=0
            for item in line.split('"'):
                if "High" in item:
                    high=float( line.split('"')[i+1] )
                if "Low" in item:
                    low=float( line.split('"')[i+1] )
                i+=1
#            print "low={} high={}".format(low,high)

            for syst in systs:
                if syst._name == name:
                    syst._high=high
                    syst._low=low
                    syst.MakeTotal()
                    done = True
            if not done: 
                tmpSyst = Systematic(name,high=high,low=low)
                tmpSample._systematics.append(tmpSyst)

    if tmpSample is not None: 
        cat._samples.append(tmpSample)
    

    Categories.append(cat)



#_____________________________________________________________________________
#     MAIN
#_____________________________________________________________________________

#systList=[]
systList = ['ATLAS_TAU_TRIG_2012_Fake', 'ATLAS_ANA_LH12_Wlnu_01jet_DETA_OS', 'ATLAS_TES_FAKE_2012', 'ATLAS_JES_FlavComp_TAU_G', 'ATLAS_JVF_2012', 'ATLAS_JES_2012_Modelling1', 'ATLAS_JES_FlavComp_TAU_Q', 'ATLAS_MET_RESOSOFT', 'ATLAS_MET_SCALESOFT', 'ATLAS_TAU_TRIG_2012_Emb',  'ATLAS_TES_2012',  'ATLAS_JES_Eta_Modelling', 'ATLAS_JES_FlavResp', 'ATLAS_TES_SS_2012']


for cat in Categories:
    if   options.full:    cat.printit()
    if options.reduced:   cat.printReducedSystTable()
    if options.shape: 

        tmplist = cat.printShapes(systList,False)
        for sys in tmplist: 
            if sys not in systList: systList.append(sys)

    print "===================="

#print systList
