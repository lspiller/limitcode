import sys
import ROOT

import glob
import argparse
import os
import random
ROOT.gROOT.LoadMacro("AtlasStyle.C")
ROOT.gROOT.ProcessLine("SetAtlasStyle()")

parser = argparse.ArgumentParser()
parser.add_argument("-b", action="store_true")
parser.add_argument("--f", type=str, default="test", help="Identifier for the workspace")
parser.add_argument("--f2", type=str, default="", help="Identifier for the workspace")
parser.add_argument("--f3", type=str, default="", help="Identifier for the workspace")
parser.add_argument("--f4", type=str, default="", help="Identifier for the workspace")
parser.add_argument("--f5", type=str, default="", help="Identifier for the workspace")
parser.add_argument("--f6", type=str, default="", help="Identifier for the workspace")


parser.add_argument("--n", type=str, default="test", help="Identifier for the workspace")
parser.add_argument("--n2", type=str, default="", help="Identifier for the workspace")
parser.add_argument("--n3", type=str, default="", help="Identifier for the workspace")
parser.add_argument("--n4", type=str, default="", help="Identifier for the workspace")
parser.add_argument("--n5", type=str, default="", help="Identifier for the workspace")
parser.add_argument("--n6", type=str, default="", help="Identifier for the workspace")

parser.add_argument("--tag", type=str, default="test", help="Foldername for plots")

parser.add_argument("--muvsmass", type=str, default="", help="Give string of folder(s) replace mass with {}")

args = parser.parse_args()

rndm = random.random()
#_______________________________________
def GetLegend(n=5,x=0.63,y=0.92):

    if (x==0):
        x=0.66
    if y==0:
        y=0.92

    leghigh = y
    leglow = leghigh - (n+2)*0.045
    
    tLeg = ROOT.TLegend(x,leglow,x+0.23,leghigh)
    tLeg.SetFillStyle(0)
    tLeg.SetFillColor(0)
    tLeg.SetBorderSize(0)
    return tLeg


#___________________________________________________________________
#___________________________________________________________________
def GetListOfChains(folder):
    ''' 
    Prepare all the TChains from a given folder name
    '''

    lof = glob.glob("{}/*root".format(folder))
    mapOfChains={}
    NuisancePars_fixed=[]
    for f in lof:
        var = os.path.basename(f).split("_fixed")[0].split("ScanAndFit_")[1]
        if var == "SigXsecOverSM" : var="mu"
        NuisancePars_fixed.append(var)
        ident =  var
        if ident in mapOfChains:
            mapOfChains[ident].Add(f)
            #print "Added {} to ident={}".format(f,ident)

        else:
            mapOfChains[ident]=ROOT.TChain("FitResults")
            mapOfChains[ident].Add(f)
            #print "Added {} to ident={}".format(f,ident)
    return mapOfChains



#___________________________________________________________________
#___________________________________________________________________
def DrawDependency(var, var2, plotdir, mapOfChains, returnOnly = False ):
    '''
    Draw var2(var) where var2 is reminimised at ervy point of var2

    '''
    chain =None
    for ident in mapOfChains:
        if var == ident: chain=mapOfChains[ident]
        
    if chain is None: 
        print "Could not find chain for variable {}".format(var)
        #print mapOfChains
        return None

    #chain.Print()
    N = chain.GetEntries()


        

    pairs =[]

    for i in range(0,chain.GetEntries()): 
        chain.GetEntry(i)
        #chain.GetTree(i)
        var2_val = chain.GetLeaf(var2)
        var2_err = chain.GetLeaf(var2+"_err")
        var_val = chain.GetLeaf(var)
        isConst = chain.GetLeaf(var+"_const")
        if not var2_val or not var_val:
            print "Error could not get var1val or var2val - {}  {}".format(var,var2, "nll_var")
            return None
        if chain.MinuitStatus <=1 and (isConst.GetValue()>0.5):
            pairs.append( ( var_val.GetValue(), (var2_val.GetValue() ,var2_err.GetValue()) ) )

    pairs.sort()
    i=0

    profile = ROOT.TGraphErrors(len(pairs))

    for x,(y,y_err) in pairs:
        if "mu" in var2:
            y=rndm+y
        profile.SetPoint(i, x, y)
        profile.SetPointError(i,0,y_err)
        i+=1

    c = ROOT.TCanvas("","",500,500)
    profile.Draw("APL")
    profile.GetYaxis().SetTitle(var2)
    profile.GetXaxis().SetTitle(var)
    if returnOnly : return profile
    
    c.Print("{}/{}.eps".format(plotdir,var))
   # c.Print("{}/{}.root".format(plotdir,var))



#___________________________________________________________________
#___________________________________________________________________
def DrawProfile(var, plotdir, mapOfChains, returnOnly = False, status0=False ):
    '''
    Standard profile of variable1
    '''
    chain =None
    for ident in mapOfChains:
        if var == ident: chain=mapOfChains[ident]
        
    if chain is None: 
        print "Could not find chain for variable {}".format(var)
        #print mapOfChains
        return None,None

    #chain.Print()
    N = chain.GetEntries()
    np_nll_pairs=[]

    start =0

    status_threshold=1
    if status0: status_threshold=0

    ## This is super ugly.. but due the fact that we dont have the isConst in the current trees.. fix this 
    if var =="mu": start =1 
    minVal = 1000
    for i in range(start,chain.GetEntries()): 
        chain.GetEntry(i)
        #chain.GetTree(i)
        nll = chain.GetLeaf("nll_val")
        npval = chain.GetLeaf(var)
        isConst = chain.GetLeaf(var+"_const")
        
        
        
        if not npval or not nll:
            print "Error could not get npval or nll - {}  {}".format(var, "nll_var")

        if chain.MinuitStatus <=status_threshold and ( (isConst.GetValue()>0.5) or var=="mu"):
            np_nll_pairs.append( ( npval.GetValue(), 2*nll.GetValue() ) )

#            print "Adding point at {} - isconst={}".format(nll.GetValue(),isConst.GetValue() )
        if chain.MinuitStatus > 1:
            print "   FIT FAILED !!" 
        if (not var =="mu") and chain.MinuitStatus <=1 and (isConst.GetValue()<0.5) :
            minVal =  npval.GetValue()
            #print "found minVal at {}  . {}".format(npval.GetValue(),isConst.GetValue() )

           # print "{}".format( npval.GetValue() )
        #profile.SetPoint(i, npval.GetValue(), nll.GetValue())

    np_nll_pairs.sort()
#    print  np_nll_pairs
    profile = ROOT.TGraph(len(np_nll_pairs))

    i=0
    for np,nll in np_nll_pairs:
        profile.SetPoint(i, np, nll)
        i+=1

    c = ROOT.TCanvas("","",500,500)
    profile.Draw("APL")
    profile.GetYaxis().SetTitle("2*#Delta Log(L)")

    var_new = var
    var_new = var_new.replace("alpha_","")
    var_new = var_new.replace("ATLAS_","")
    var_new = var_new.replace("HH_","")
    var_new = var_new.replace("ANA_","")
		
    profile.GetXaxis().SetTitle(var_new)
    if returnOnly : return profile,minVal
    
    c.Print("{}/{}.eps".format(plotdir,var))
  #Print("{}/{}.root".format(plotdir,var))

#___________________________________________________________________
#___________________________________________________________________
def DrawOverlaidProfiles(var, plotdir, mapsOfChains, names):
    '''
    Overlay scans of the same parameter from different ws in one plot
    Please provide a list of chainmaps and the names to be used for the legend
    '''
    if len(mapsOfChains) != len(names):
        print "ERROR : Items in the list of maps != no items in names"

    i=0
    allprofiles=[]
    minvals = []
    for m in mapsOfChains:
        
        profile,minval = DrawProfile(var, "", m, returnOnly = True )
        #profile_status0,minval = DrawProfile(var, "", m, returnOnly = True ,status0 =True)

        if profile is None: 
            print "ERROR getting profile for {} - {}".format(var,names[i])
            i+=1
            continue

        profile.SetTitle( names[i] )
        profile.SetLineColor(i+1)
        profile.SetMarkerColor(i+1)
        profile.SetMarkerSize(0.6)
        # profile_status0.SetTitle( names[i]+"status=0" )
        # profile_status0.SetLineColor(i+1)
        # profile_status0.SetMarkerColor(i+1)
        # profile_status0.SetMarkerSize(0.3)
        # profile_status0.SetLineStyle(2)

        if i>0:
#            profile.SetLineStyle(2)
            profile.SetMarkerStyle(1)

        if (i+1 == 5) :
            profile.SetLineColor(808)
            profile.SetMarkerColor(808)

        allprofiles.append( profile )
        #allprofiles.append( profile_status0 )
        print "Got minval={}".format(minval)
        #minvals.append(minval)
        minvals.append(minval)
        i+=1
    
    if len(allprofiles) == 0:
        return
    c = ROOT.TCanvas(var,var,500,500)
    leg = GetLegend(len(mapsOfChains)+1)
    
#    allprofiles[0].Draw("APL")
    histo = ROOT.TH1D("foraxis","foraxis",1000,-100,100)
    histo.GetYaxis().SetRangeUser(-0.1,5)
    histo.GetYaxis().SetTitle("2 #Delta Log(L)")
    histo.GetXaxis().SetRangeUser(-2,5)

    var_new = var
    var_new = var_new.replace("alpha_","")
    var_new = var_new.replace("ATLAS_","")
    var_new = var_new.replace("HH_","")
    var_new = var_new.replace("ANA_","")
	
    histo.GetXaxis().SetTitle(var_new)
    histo.Draw("AXIS")

    actualline = ROOT.TLine()
    line = ROOT.TArrow()
    line.SetLineWidth=1.2
    line.SetFillColor(0)
    i=0
    for p in allprofiles:
        p.Draw("PL;SAME")
        mean,lo,hi = GetUncertaintyAndMean(p)
        leg.AddEntry(p,p.GetTitle()+" ({0}^{{+{1}}}_{{-{2}}})".format(round(mean,2),round(hi,2),round(lo,2)),"l")
        line.SetLineColor(p.GetLineColor())
        if i>0:
           line.SetLineStyle=2
           line.SetLineWidth=0.8

        line.DrawArrow(minvals[i], 1. , minvals[i],1.5,0.02,"<")
        i+=1
    actualline.DrawLine(-2,0,5,0)
    leg.Draw()
    c.Print("{}/{}.eps".format(plotdir,var))
 #   c.Print("{}/{}.root".format(plotdir,var))


#___________________________________________________________________
#___________________________________________________________________
def DrawOverlaidDependencies(var,var2, plotdir, mapsOfChains, names):
    '''
    Draw var2(var) where var2 is reminimised at ervy point of var2
    '''


    if len(mapsOfChains) != len(names):
        print "ERROR : Items in the list of maps != no items in names"

    i=0
    allprofiles=[]
    for m in mapsOfChains:
        
        profile = DrawDependency(var,var2, "", m, returnOnly = True )
        if profile is None: 
            print "ERROR getting dependency for {} vs {}-{}".format(var2,var,names[i])
            i+=1
            continue
        profile.SetTitle( names[i] )
        profile.SetLineColor(i+1)
        profile.SetMarkerColor(i+1)
        profile.SetMarkerSize(0.6)

        allprofiles.append( profile )
        i+=1
    
    if len(allprofiles) == 0:
        return
    c = ROOT.TCanvas("{}_vs_{}".format(var2,var),"{}_vs_{}".format(var2,var),500,500)
    leg = GetLegend(len(mapsOfChains))
    
#    allprofiles[0].Draw("APL")
    histo = ROOT.TH1D("foraxis","foraxis",1000,-100,100)
    
    if "mu" in var2:
        histo.GetYaxis().SetRangeUser( rndm - 0.01,rndm+0.05)
    else:
        histo.GetYaxis().SetRangeUser( -2,3)

    histo.GetYaxis().SetTitle(var2)
    histo.GetXaxis().SetRangeUser(-2,3)
    histo.GetXaxis().SetTitle(var)
    histo.Draw("AXIS")


    for p in allprofiles:
        p.Draw("PL;SAME")
        leg.AddEntry(p,p.GetTitle(),"l")

    leg.Draw()
    c.Print("{}/{}_vs_{}.eps".format(plotdir,var2,var))
 #   c.Print("{}/{}_vs_{}.root".format(plotdir,var2,var))




#___________________________________________________________________
#___________________________________________________________________
def GetUncertaintyAndMean(profile, deltaY=1):
    '''
    Based on the profile obtain the error using a interpolation between the points.
    Hack together a TF1 object and use its GetX() implementation
    The definition holds for delta Log L. 
    '''

    def function(x):
        return profile.Eval(x[0])

    profilefunction = ROOT.TF1("profile",function,-5,10,0)
    meanval = profilefunction.GetMinimumX()
    unc_lo = profilefunction.GetX( deltaY , meanval-5,meanval)
    unc_hi = profilefunction.GetX( deltaY , meanval,meanval+5)
    unc_lo= abs(meanval -unc_lo)
    unc_hi= abs(meanval -unc_hi)
    return meanval,unc_lo,unc_hi


#___________________________________________________________________
#___________________________________________________________________
def DrawMuVsMass(plotdir, mapsOfChains, masses):

    graph = ROOT.TGraphAsymmErrors(len(masses))
    i=0
    for m in mapsOfChains:
        #print m
        profile,minval = DrawProfile("mu", "", m, returnOnly = True )
        mu_hat,lo,hi = GetUncertaintyAndMean(profile)
        graph.SetPoint(i, masses[i] ,mu_hat)
        graph.SetPointError(i,1.25,1.25,lo,hi)
        i+=1
    graph.SetFillColor(868)
    graph.SetFillStyle(3001)
    graph.SetMarkerSize(0.8)
    c = ROOT.TCanvas("MuVsMh","MuVsMh",500,500)
    histo = ROOT.TH1D("foraxis","foraxis",1000,90,170)
    histo.GetXaxis().SetTitle("m_{H} [GeV]")
    histo.GetYaxis().SetTitle("#hat{#mu}")
    histo.GetYaxis().SetRangeUser(0,10)
    histo.GetXaxis().SetRangeUser(100,150)
    histo.GetXaxis().SetNdivisions(506)
    histo.Draw("AXIS")
    graph.Draw("E3")
    graph.Draw("LPX")
    histo.Draw("AXISSAME")
    actualline = ROOT.TLine()
    actualline.SetLineStyle(2)
    actualline.DrawLine(100,1,150,1)

    latex = ROOT.TLatex()
    latex.SetNDC()
    latex.SetTextSize(0.03)

    latex.DrawLatex(0.2,0.9 ,"#font[72]{ATLAS}#font[42]{  Work In Progress} ")
    latex.DrawLatex(0.2,0.85 ,"#font[42]{ #scale[0.6]{#int} L dt = 20.3 fb^{-1}}")
    latex.DrawLatex(0.2,0.80 ,"#sqrt{#it{s}} = 8 TeV ")
    latex.DrawLatex(0.2,0.75 ,"#mu#tau_{had}+e#tau_{had} ")
    latex.DrawLatex(0.2,0.7 ,"Injection ")

    legend = GetLegend(n=1,x=0.63,y=0.92)
    legend.AddEntry(graph,"Injected signal (125 GeV)","pl")
    legend.AddEntry(actualline,"Expected","l")
    legend.Draw()
    c.Print("{}/MuVsMh.eps".format(plotdir))
 #   c.Print("{}/MuVsMh.root".format(plotdir))

#___________________________________________________________________
#   MAIN
#___________________________________________________________________




#DrawProfile("alpha_ATLAS_MU_EFF")
#DrawProfile("alpha_Gen_Qmass_ggH")
print " Store plots in:  pdf-files/*/{}".format(args.tag)
os.system("mkdir -vp pdf-files/Profiles/{}/".format(args.tag))
os.system("mkdir -vp pdf-files/Dependencies/{}/".format(args.tag))
os.system("mkdir -vp pdf-files/MuHat/{}/".format(args.tag))

chains = []
names = []

## Do something else if muvsmass holds a template
if args.muvsmass != "":
    folderTemplate=args.muvsmass
    for m in range(100,155,5):
        chains.append(GetListOfChains( folderTemplate.format(m) ))
        names.append( m )
    DrawMuVsMass("pdf-files/MuHat/{}".format(args.tag) ,chains,names )

    exit()


# Get all the tchains: 


chains.append(GetListOfChains(args.f))
names.append( args.n )

if args.f2 !="":
    chains.append(GetListOfChains(args.f2))
    names.append( args.n2 )
if args.f3 !="":
    chains.append(GetListOfChains(args.f3))
    names.append( args.n3 ) 
if args.f4 !="":
    chains.append(GetListOfChains(args.f4))
    names.append( args.n4 )
if args.f5 !="":
    chains.append(GetListOfChains(args.f5))
    names.append( args.n5 )
if args.f6 !="":
    chains.append(GetListOfChains(args.f6))
    names.append( args.n6 )

for var in chains[0]:
    if "SigXsecOverSM" in var: continue
    DrawOverlaidProfiles(var, "pdf-files/Profiles/{}".format(args.tag), chains, names)
    DrawOverlaidDependencies(var,"mu", "pdf-files/Dependencies/{}".format(args.tag), chains, names)
    
    for var2 in chains[0]:
        #if "SigXsecOverSM" in var2: continue
        # var 2 is y axis, var is x axis
        DrawOverlaidDependencies(var,var2, "pdf-files/Dependencies/{}".format(args.tag), chains, names)
