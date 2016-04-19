/*
Author: Aaron Armbruster
Date:   2011-2-14

Description:

Produce a set of workspaces used for signal injection studies. 
The template mu=1 asimov dataset is embedded into the nominal
set of workspaces, then written out into a new injected workspace.
This dataset can be used for injected p0 plots, but NOT injected
CLs plots, since there is some complication with the CLb treatment.

When computing the significance, be sure to load the injected snapshots
for the expected q0.

*/

#include "TFile.h"
#include "TTree.h"

#include "RooWorkspace.h"
#include "RooStats/ModelConfig.h"
#include "RooDataSet.h"
#include "RooRealVar.h"

#include <sstream>
#include <string>
#include <iostream>

#include "macros/makeAsimovData.C"
#include "macros/rebuildData.C"

using namespace std;
using namespace RooFit;
using namespace RooStats;

string fileName(double mass, string folder)
{
  stringstream name;
  name << "results/hh_all_" << folder << "_" << mass << "_2011_2012_combined_AllSYS_model.root";
  return name.str();
}

void globalInjection(double mass,
        string folder,
        string wsName = "combined",
        string mcName = "ModelConfig",
        string asimovDataName = "asimovData_1",
        string obsDataName = "obsData",
        string globSnapshot = "conditionalGlobs_1",
        string nuiSnapshot = "conditionalNuis_1",
        double target_mass = 0)
{

  vector<double> massPoints;
  massPoints.push_back(100);
	massPoints.push_back(102.5);
	massPoints.push_back(105);
	massPoints.push_back(107.5);
	massPoints.push_back(110);
	massPoints.push_back(112.5);
	massPoints.push_back(115);
	massPoints.push_back(117.5);
	massPoints.push_back(120);
	massPoints.push_back(122.5);
	massPoints.push_back(125);
	massPoints.push_back(127.5);
	massPoints.push_back(130);
	massPoints.push_back(132.5);
	massPoints.push_back(135);
	massPoints.push_back(137.5);
	massPoints.push_back(140);
	massPoints.push_back(142.5);
	massPoints.push_back(145);
	massPoints.push_back(147.5);
	massPoints.push_back(150);
	
  int nrPoints = massPoints.size();

  // make asimov data for injection point
  TFile* file = new TFile(fileName(mass, folder).c_str());
  RooWorkspace* w = (RooWorkspace*)file->Get(wsName.c_str());
  ModelConfig* mc = (ModelConfig*)w->obj(mcName.c_str());
  RooDataSet* asimovData = (RooDataSet*)w->data(asimovDataName.c_str());
  RooDataSet* obsData = (RooDataSet*)w->data(obsDataName.c_str());
  
  if (!asimovData)
  {
    cout << "Building asimov" << endl;
    bool doConditional = true;
//	  bool doConditional = false;
    makeAsimovData(mc, doConditional, w, mc->GetPdf(), obsData, 1);
    asimovData = (RooDataSet*)w->data("asimovData_1");
  }
	cout<<asimovData<<endl;
  RooDataSet* asimovData_master = asimovData;

  w->loadSnapshot(globSnapshot.c_str());
  w->loadSnapshot(nuiSnapshot.c_str());

  const RooArgSet* globs = mc->GetGlobalObservables();
  const RooArgSet* nuis = mc->GetNuisanceParameters();

  stringstream folderName;
  folderName << folder+"_inj" << mass;

  if (mass == target_mass)
  {
    asimovData = (RooDataSet*)asimovData_master->Clone("asimovData_inj");
    if (w->data(asimovData->GetName()))
    {
      w->import(*asimovData, true);
    }
    else
    {
      w->import(*asimovData);
    }

    w->saveSnapshot("conditionalGlobs_inj", *mc->GetGlobalObservables());
    w->saveSnapshot("conditionalNuis_inj", *mc->GetNuisanceParameters());

    string outFileName = fileName(mass, folderName.str());
    cout << "Writing to file: " << outFileName << endl;
    w->writeToFile(outFileName.c_str(), true);
    cout << endl;

    return;
  }

  // put asimov data in other workspaces
  for (int imass=0;imass<nrPoints;imass++)
  {
    double thisMass = massPoints[imass];
    if (target_mass != 0 && thisMass != target_mass) continue;

    //asimovData = (RooDataSet*)asimovData_master->Clone("asimovData_inj");
    asimovData = (RooDataSet*)asimovData_master->Clone("asimovData_inj_tmp");
    string outFileName = fileName(thisMass, folderName.str());

    TFile f(fileName(thisMass, folder).c_str());
    cout<<fileName(thisMass, folder).c_str()<<endl;
    cout<<wsName.c_str()<<endl;
    RooWorkspace* this_w = (RooWorkspace*)f.Get(wsName.c_str());

    if (!this_w)
    {
      cout << "Skipping point: " << thisMass << endl;
      continue;
    }
    cout << endl;

    asimovData = rebuildData(this_w, w, asimovData, "asimovData_inj");



    if (this_w->data(asimovData->GetName()))
    {
      this_w->import(*asimovData, true);
    }
    else
    {
      this_w->import(*asimovData);
    }
	  

    ModelConfig* this_mc = (ModelConfig*)this_w->obj("ModelConfig");
    RooArgSet these_globs = *this_mc->GetGlobalObservables();
    RooArgSet these_nuis = *this_mc->GetNuisanceParameters();

    these_globs = *globs;
    these_nuis = *nuis;

    this_w->saveSnapshot("conditionalGlobs_inj", these_globs);
    this_w->saveSnapshot("conditionalNuis_inj", these_nuis);
    this_w->loadSnapshot("nominalGlobs");

    cout << "Writing to file: " << outFileName << endl;
    this_w->writeToFile(outFileName.c_str(), true);
    cout << endl;
    f.Close();
    delete asimovData;
  }
}
