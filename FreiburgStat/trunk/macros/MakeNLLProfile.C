/*
Author: Romain Madar & Nils Ruthmann
Date:   2013-09-17
Email:  romain.madar@cern.ch, nils.ruthmann@cern.ch


Description : This code allows to derive Negative Log Likelihood profile by hand.
              It performs a scan in a given nuisance parameter and, for each value,
              it does a fit, store all the other NPs values, the fit status, the 
              minNLL, etc ... in a tree. For example, this is useful to study some
              kink in the NLL profile, double minima structures, ...
*/


// C++
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <map>

// Root
#include "TFile.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TList.h"
#include "TMath.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGaxis.h"
#include "TTree.h"
#include "TLeaf.h"
#include "TMarker.h"

// RooFit
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooPlot.h"
#include "RooAbsData.h"
#include "RooHist.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"
#include "RooFitResult.h"
#include "RooAbsData.h"
#include "RooRealSumPdf.h"
#include "Roo1DTable.h"
#include "RooConstVar.h"
#include "RooProduct.h"
#include "RooRandom.h"
#include "TStopwatch.h"
#include "RooNLLVar.h"
#include "RooMsgService.h"
#include "RooMinimizer.h"

// RooStat
#include "RooStats/ModelConfig.h"
#include "RooStats/ProfileInspector.h"
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/LikelihoodInterval.h"
#include "RooStats/LikelihoodIntervalPlot.h"
#include "RooStats/ProfileLikelihoodTestStat.h"
#include "RooStats/SamplingDistribution.h"
#include "RooStats/SamplingDistPlot.h"
#include "RooStats/ToyMCSampler.h"
#include "RooStats/RooStatsUtils.h"

using namespace std;
using namespace RooFit;
using namespace RooStats;

RooWorkspace *w;
ModelConfig  *mc;
RooAbsData   *data;
TTree *tree;
RooRealVar *FixedNP;
vector<double> NPval_vec;
vector<double> NPerr_vec;
vector<int> NPconst_vec;
vector<TString> NPname_vec;
double nll_val, Edm;
int MinuitStatus,HesseStatus;

void MakeNLLProfile(TString infile, TString outputdir, TString NPname, int Nstep, float min, float max);
void MakeNLLProfile();
RooFitResult* DoSingleFit(double NPval, RooAbsReal* nll );
void InitTree(TTree *t);
void FillNPs();
void MakeInitialFit(TString infile);
RooFitResult* FitPDF( ModelConfig* model, RooAbsPdf* fitpdf, RooAbsData* fitdata, 
		      int &MinuitStatus, int &HessStatus, double &Edm,
		      TString minimType = "Minuit2", bool useMinos = false );
RooFitResult* FitPDF(  RooAbsReal* nll, int &MinuitStatusloc, int &HessStatus, double &Edmloc,
		       TString minimType, bool useMinos );


void MakeNLLProfile(){
  return;
}


void MakeInitialFit(TString infile){

  // Get the model  
  TFile *file = TFile::Open(infile,"UPDATE");
  if (!file){cout << "The file " << infile << " is not found/created, will stop here." << endl; return;}
  if(!(RooWorkspace*) file->Get("combined")){cout <<"workspace not found" << endl;return;}
  w      = (RooWorkspace*) file->Get("combined");
  mc     = (ModelConfig*) w->obj("ModelConfig");
  data   = w->data("obsData");

  if (w->loadSnapshot("GlobalFit") ){
    cout<<"Initial fit was already done.. leaving"<<endl;
    file->Close();
    return;
  }
  
  // Get the pdf of the model and create the NLL
  RooAbsPdf *pdf = mc->GetPdf();

  w->saveSnapshot("init", *(pdf->getParameters(*data)) );

  int numCPU = sysconf( _SC_NPROCESSORS_ONLN );   
  RooArgSet* constrainedParams = pdf->getParameters(*data);
  RooArgSet* nuis = (RooArgSet*) mc->GetNuisanceParameters();
  RemoveConstantParameters(constrainedParams);
  const RooArgSet* glbObs = mc->GetGlobalObservables();
  RooAbsReal * nll = pdf->createNLL(*data, Constrain(*nuis), GlobalObservables(*glbObs), Offset(1),   NumCPU(numCPU, RooFit::Hybrid) );
  nll->enableOffsetting(true);
  RooRealVar * poi = (RooRealVar*) mc->GetParametersOfInterest()->first();  
  poi->setRange(0,2);
  poi->setVal(0);
  
  FitPDF( nll, MinuitStatus, HesseStatus, Edm, "Minuit2", false);
  if ( MinuitStatus !=0 && MinuitStatus !=1){
    cout<<" Initial Fit failed !"<<endl;
    cout<<"Try again!"<<endl;
    FitPDF( nll, MinuitStatus, HesseStatus, Edm, "Minuit2", false);
    if ( MinuitStatus !=0 && MinuitStatus !=1){
      cout<<" Initial Fit failed again! ..Exit"<<endl;
      return;
    }
  } 


  w->saveSnapshot("GlobalFit", *(pdf->getParameters(*data)) );

  w->loadSnapshot("init") ;

  file->cd();
  w->Write();
  file->Close();
  return;
}

void MakeNLLProfile(TString infile, TString outputdir, TString NPname, int N, float min, float max){

  ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);

  // Get the model  
  TFile *file = TFile::Open(infile);
  if (!file){cout << "The file " << infile << " is not found/created, will stop here." << endl; return;}
  if(!(RooWorkspace*) file->Get("combined")){cout <<"workspace not found" << endl;return;}
  w      = (RooWorkspace*) file->Get("combined");
  mc     = (ModelConfig*) w->obj("ModelConfig");
  data   = w->data("obsData");
  FixedNP = (RooRealVar*) w->arg(NPname);
  if (!FixedNP) {cout <<"NP " << NPname << " not found" << endl;return;}


  // Get the pdf of the model and create the NLL
  RooAbsPdf *pdf = mc->GetPdf();
  int numCPU = 1 ;  
  RooArgSet* constrainedParams = pdf->getParameters(*data);
  RooArgSet* nuis = (RooArgSet*) mc->GetNuisanceParameters();

 
  RemoveConstantParameters(constrainedParams);
  const RooArgSet* glbObs = mc->GetGlobalObservables();
  RooAbsReal * nll = pdf->createNLL(*data, Constrain(*nuis), GlobalObservables(*glbObs), Offset(1),   NumCPU(numCPU, RooFit::Hybrid) );
  nll->enableOffsetting(true);

  // See whether we have a global minimum stored
  if (w->loadSnapshot("GlobalFit") ){ 
    cout<<"Succesfully loaded global fit snapshot"<<endl;
  }


  // Initialize the tree
  tree = new TTree("FitResults","FitResults");
  InitTree(tree);
  MinuitStatus = -999;
  HesseStatus  = -999; 
  nll_val=-999;


  // Peform initial fit (all NPs floating), to get NP[post-fit] and absolute minNLL
  RooRealVar * poi = (RooRealVar*) mc->GetParametersOfInterest()->first();  
  //Stick with small mu range for randomized mu workspaces
  poi->setRange(0,2);
  //  poi->setRange(-10,10);
  poi->setVal(0);
  FixedNP->setConstant(false);
  
  FitPDF( nll, MinuitStatus, HesseStatus, Edm, "Minuit2", false);
  if ( MinuitStatus !=0 && MinuitStatus !=1){
    cout<<" Initial Fit failed !"<<endl;
    cout<<"Try again!"<<endl;
    FitPDF( nll, MinuitStatus, HesseStatus, Edm, "Minuit2", false);
    if ( MinuitStatus !=0 && MinuitStatus !=1){
      cout<<" Initial Fit failed again! ..Exit"<<endl;
      return;
    }
  } 
  (pdf->getParameters(*data))->Print("v");
  w->saveSnapshot("StartingPoint", *(pdf->getParameters(*data)));

  double nll_hat = nll->getVal() ;
  FillNPs();
  nll_val = nll->getVal() - nll_hat;
  tree->Fill();
  

  // Perform fits with Fixed NP, at different value
  FixedNP->setConstant(true);
  FixedNP->setRange(min,max);
  for (int i=0 ; i<N ; i++){
    double NPval;
    if (N==1) NPval = min;
    else      NPval = min + i *(max-min)/((float)N-1);
    cout<<" ============ Fit "<<i<<"/"<<N<<"==="<<NPval <<"====="<<endl;
    DoSingleFit(NPval, nll);
    FillNPs();
    nll_val=  nll->getVal() - nll_hat;
    tree->Fill();
  }
  

  // Save the result in a rootfile
  gSystem->Exec("mkdir -p " + outputdir);
  TString fname = outputdir+"/ScanAndFit_" + NPname + "_fixed";
  fname+=abs(min);
  fname+="_";
  fname+=max;
  fname+=".root";
  TFile *fout = new TFile(fname,"RECREATE");
  fout->cd();
  tree->Write();
  fout->Close();

 return;

}
















RooFitResult* DoSingleFit(double NPval, RooAbsReal* nll ){

  if (!  w->loadSnapshot("StartingPoint")){
    cout<<"Problem loading StartingPoint snapshot"<<endl;
  }
  else{
    cout<<"Succesfully loaded StartingPoint snapshot"<<endl;
  }

  FixedNP->setVal(NPval);
  FixedNP->setConstant(true);

  RooFitResult* r = FitPDF(nll,MinuitStatus, HesseStatus, Edm, "Minuit2", false);
  return r;
}


void InitTree(TTree *t){
  if (!w) return;
  NPval_vec.clear();
  NPerr_vec.clear();
  NPname_vec.clear();
  NPconst_vec.clear();

  RooRealVar* firstPOI = (RooRealVar*) mc->GetParametersOfInterest()->first();
  NPval_vec.push_back( firstPOI->getVal() );
  NPerr_vec.push_back( firstPOI->getError() );
  NPname_vec.push_back( "mu" );

  RooArgSet nuis = *mc->GetNuisanceParameters();
  TIterator* itr = nuis.createIterator();
  RooRealVar* arg;
  while ((arg=(RooRealVar*)itr->Next())) {
    if (!arg) continue;
    NPval_vec.push_back( arg->getVal()   );
    NPerr_vec.push_back( arg->getError() );
    NPname_vec.push_back( (TString) arg->GetName() );
    NPconst_vec.push_back( arg->isConstant() );
  }

  t->Branch("nll_val", &nll_val , "nll_val/D");
  t->Branch("Edm", &Edm , "Edm/D");
  t->Branch("MinuitStatus", &MinuitStatus , "MinuitStatus/int");
  t->Branch("HesseStatus", &HesseStatus , "HesseStatus/int");

  for (unsigned i=0; i<NPval_vec.size() ; i++){
    t->Branch( NPname_vec[i], &NPval_vec[i] , NPname_vec[i]+"/D");
    t->Branch( NPname_vec[i]+"_err", &NPerr_vec[i] , NPname_vec[i]+"_err/D");
    t->Branch( NPname_vec[i]+"_const", &NPconst_vec[i] , NPname_vec[i]+"_const/I");

  }

  return;
}

void FillNPs(){

  RooRealVar* firstPOI = (RooRealVar*) mc->GetParametersOfInterest()->first();
  NPval_vec[0] = firstPOI->getVal();
  NPerr_vec[0] = firstPOI->getError();

  RooArgSet nuis = *mc->GetNuisanceParameters();
  TIterator* itr = nuis.createIterator();
  RooRealVar* arg;
  int ic=1;
  while ((arg=(RooRealVar*)itr->Next())) {
    if (!arg) continue;
    NPval_vec[ic] = arg->getVal();
    NPerr_vec[ic] = arg->getError();
    NPconst_vec[ic] = arg->isConstant();
    ic++;
    //  cout<<arg->GetName()<<" = "<< arg->getVal()<<endl;
  }
  
  return;
}
 

RooFitResult* FitPDF( ModelConfig* model, RooAbsPdf* fitpdf, RooAbsData* fitdata, 
		      int &MinuitStatusloc, int &HessStatus, double &Edmloc,
		      TString minimType, bool useMinos ) {
  
  model->Print();
  
  RooArgSet* constrainedParams = fitpdf->getParameters(*data);
  RemoveConstantParameters(constrainedParams);
  Constrain(*constrainedParams);
  
  const RooArgSet* glbObs = mc->GetGlobalObservables();
  
  RooRealVar * poi = (RooRealVar*) model->GetParametersOfInterest()->first();
  cout << "Constatnt POI " << poi->isConstant() << endl;
  cout << "Value of POI  " << poi->getVal() << endl;
  
  RooAbsReal * nll = fitpdf->createNLL(*fitdata, Constrain(*constrainedParams), GlobalObservables(*glbObs), Offset(1) );
  double nllval = nll->getVal();
  
  std::cout << "initial parameters" << std::endl;
  constrainedParams->Print("v");
  
  std::cout << "INITIAL NLL = " << nllval << std::endl;
 


 
  static int nrItr = 0;
  int maxRetries = 5;
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer(minimType);
  int strat = ROOT::Math::MinimizerOptions::DefaultStrategy();
  int save_strat = strat;
  RooMinimizer minim(*nll);
  minim.setStrategy(strat);
  minim.setPrintLevel(-1);
  minim.setEps(1);
  
  TStopwatch sw; sw.Start(); 
  
  int status=-99;
  HessStatus=-99;
  Edmloc = -99;
  RooFitResult * r;
  while (nrItr<maxRetries && status!=0 && status!=1){
    
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Fit try n°" << nrItr+1 << endl;
    cout << "======================" << endl;
    cout << endl;
    
    
    ROOT::Math::MinimizerOptions::SetDefaultStrategy(save_strat);
    minim.minimize("Minuit2", "Scan");

    status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(),ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
    HessStatus= minim.hesse();
    r = minim.save();
    Edmloc = r->edm();
    
    //up the strategy
    bool FitIsNotGood = ((status!=0 && status!=1) || (HessStatus!=0 && HessStatus!=1) || Edmloc>1.0);

    if (FitIsNotGood && strat<2){
      
      cout << endl;
      cout << "   *******************************" << endl;
      cout << "   * Increasing Minuit strategy (was " << strat << ")" << endl;
      strat++;
      cout << "   * Fit failed with : " << endl;
      cout << "      - minuit status " << status << endl;
      cout << "      - hess status " << HessStatus << endl;
      cout << "      - Edm = " << Edmloc << endl;
      cout << "   * Retrying with strategy " << strat << endl;
      cout << "   ********************************" << endl;
      cout << endl;
      minim.setStrategy(strat);
      minim.minimize("Minuit2", "Scan");
      status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
      HessStatus= minim.hesse();
      r = minim.save();
      Edmloc = r->edm();
    }
    
    FitIsNotGood = ((status!=0 && status!=1) || (HessStatus!=0 && HessStatus!=1) || Edmloc>1.0);
    if (FitIsNotGood && strat < 2){
      cout << endl;
      cout << "   ********************************" << endl;
      cout << "   * Increasing Minuit strategy (was " << strat << ")" << endl;
      strat++;
      cout << "   * Fit failed with : " << endl;
      cout << "      - minuit status " << status << endl;
      cout << "      - hess status " << HessStatus << endl;
      cout << "      - Edm = " << Edmloc << endl;
      cout << "   * Retrying with strategy " << strat << endl;
      cout << "   ********************************" << endl;
      cout << endl;
      minim.setStrategy(strat);
      status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
      r = minim.save();
      Edmloc = r->edm();
    }
    
    FitIsNotGood = ((status!=0 && status!=1) || (HessStatus!=0 && HessStatus!=1) || Edmloc>1.0);
    if (FitIsNotGood && strat < 2){
      cout << endl;
      cout << "   *******************************" << endl;
      cout << "   * Increasing Minuit strategy (was " << strat << ")" << endl;
      strat++;
      cout << "   * Fit failed with : " << endl;
      cout << "      - minuit status " << status << endl;
      cout << "      - hess status " << HessStatus << endl;
      cout << "      - Edm = " << Edmloc << endl;
      cout << "   * Retrying with strategy " << strat << endl;
      cout << "   ********************************" << endl;
      cout << endl;
      minim.setStrategy(strat);
      status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
      HessStatus= minim.hesse();
      r = minim.save();
      Edmloc = r->edm();
    }
    
    if(useMinos) { minim.minos(); }
    
    
    FitIsNotGood = ((status!=0 && status!=1) || (HessStatus!=0 && HessStatus!=1) || Edmloc>1.0);
    if ( FitIsNotGood) nrItr++;
    if (nrItr == maxRetries) {
      cout << endl;
      cout << endl;
      cout << endl;
      cout << "***********************************************************" << endl;
      cout << "WARNING::Fit failure unresolved with status " << status << endl;
      cout << "   Please investigate your workspace" << endl;
      cout << "   Find a wall : you will need it to crash your head on it" << endl;
      cout << "***********************************************************" << endl;
      cout << endl;
      cout << endl;
      cout << endl;
      MinuitStatusloc = status;
      return r;
    }
    
  }  
  
  r = minim.save();
  cout << endl;
  cout << endl;
  cout << endl;
  cout << "***********************************************************" << endl;
  cout << "         FIT FINALIZED SUCCESSFULLY : " << endl;
  cout << "            - minuit status " << status << endl;
  cout << "            - hess status " << HessStatus << endl;
  cout << fixed;

  cout << "            - Edm = " << Edmloc << endl;
  cout << "            - nll = " << nll->getVal()  << endl;

  cout << " -- " ; sw.Print();
  cout << "***********************************************************" << endl;
  cout << endl;
  cout << endl;
  cout << endl;
  
  MinuitStatusloc = status;
  sw.Print();
  //double final_nllval = nll->getVal();
  nll_val =  nll->getVal();

  //  cout<<" getVal="<< final_nllval<<" fitres nll="<<r->minNll()<< " by hand" <<final_nllval - nllval << endl;
  return r;
} // FitPDF




RooFitResult* FitPDF(  RooAbsReal* nll,
		      int &MinuitStatusloc, int &HessStatus, double &Edmloc,
		      TString minimType, bool useMinos ) {
  
  int nrItr = 0;
  int maxRetries = 3;
  ROOT::Math::MinimizerOptions::SetDefaultMinimizer(minimType);
  ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
  ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);

  RooMsgService::instance().getStream(1).removeTopic(RooFit::Eval);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Generation);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Minimization);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Plotting);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Fitting);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Integration);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::LinkStateMgmt);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Caching);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Optimization);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::ObjectHandling);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::InputArguments);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Tracing);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::Contents);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::DataHandling);
  RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration);

  int strat = ROOT::Math::MinimizerOptions::DefaultStrategy();
  int save_strat = strat;
  int printLevel = ROOT::Math::MinimizerOptions::DefaultPrintLevel();
  if (printLevel < 0) RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);

  RooMinimizer minim(*nll);
  minim.setStrategy(strat);
  //minim.setPrintLevel(0);
  minim.setPrintLevel(printLevel);

  minim.setEps(1);
  
  TStopwatch sw; sw.Start(); 
  
  int status=-99;
  HessStatus=-99;
  Edmloc = -99;
  RooFitResult * r;
  while (nrItr<maxRetries && status!=0 && status!=1){
    
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Fit try n°" << nrItr+1 << endl;
    cout << "======================" << endl;
    cout << endl;
    
    
    ROOT::Math::MinimizerOptions::SetDefaultStrategy(save_strat);
    status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(),ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
    HessStatus= minim.hesse();
    r = minim.save();
    Edmloc = r->edm();
    
    //up the strategy
    bool FitIsNotGood = ((status!=0 && status!=1) || (HessStatus!=0 && HessStatus!=1) || Edmloc>1.0);
    if (FitIsNotGood && strat<2){
      cout << endl;
      cout << "   *******************************" << endl;
      cout << "   * Increasing Minuit strategy (was " << strat << ")" << endl;
      strat++;
      cout << "   * Fit failed with : " << endl;
      cout << "      - minuit status " << status << endl;
      cout << "      - hess status " << HessStatus << endl;
      cout << "      - Edm = " << Edmloc << endl;
      cout << "   * Retrying with strategy " << strat << endl;
      cout << "   ********************************" << endl;
      cout << endl;
      minim.setStrategy(strat);
      status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
      HessStatus= minim.hesse();
      r = minim.save();
      Edmloc = r->edm();
    }
    
    FitIsNotGood = ((status!=0 && status!=1) || (HessStatus!=0 && HessStatus!=1) || Edmloc>1.0);
    if (FitIsNotGood && strat < 2){
      cout << endl;
      cout << "   ********************************" << endl;
      cout << "   * Increasing Minuit strategy (was " << strat << ")" << endl;
      strat++;
      cout << "   * Fit failed with : " << endl;
      cout << "      - minuit status " << status << endl;
      cout << "      - hess status " << HessStatus << endl;
      cout << "      - Edm = " << Edmloc << endl;
      cout << "   * Retrying with strategy " << strat << endl;
      cout << "   ********************************" << endl;
      cout << endl;
      minim.setStrategy(strat);
      status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
      r = minim.save();
      Edmloc = r->edm();
    }
    
    FitIsNotGood = ((status!=0 && status!=1) || (HessStatus!=0 && HessStatus!=1) || Edmloc>1.0);
    if (FitIsNotGood && strat < 2){
      cout << endl;
      cout << "   *******************************" << endl;
      cout << "   * Increasing Minuit strategy (was " << strat << ")" << endl;
      strat++;
      cout << "   * Fit failed with : " << endl;
      cout << "      - minuit status " << status << endl;
      cout << "      - hess status " << HessStatus << endl;
      cout << "      - Edm = " << Edmloc << endl;
      cout << "   * Retrying with strategy " << strat << endl;
      cout << "   ********************************" << endl;
      cout << endl;
      minim.setStrategy(strat);
      status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
      HessStatus= minim.hesse();
      r = minim.save();
      Edmloc = r->edm();
    }
    
    if(useMinos) { minim.minos(); }
    
    
    FitIsNotGood = ((status!=0 && status!=1) || (HessStatus!=0 && HessStatus!=1) || Edmloc>1.0);
    if ( FitIsNotGood) nrItr++;
    if (nrItr == maxRetries) {
      cout << endl;
      cout << endl;
      cout << endl;
      cout << "***********************************************************" << endl;
      cout << "WARNING::Fit failure unresolved with status " << status << endl;
      cout << "   Please investigate your workspace" << endl;
      cout << "   Find a wall : you will need it to crash your head on it" << endl;
      cout << "***********************************************************" << endl;
      cout << endl;
      cout << endl;
      cout << endl;
      MinuitStatusloc = status;
      return r;
    }
    
  }  
  
  r = minim.save();
  cout << endl;
  cout << endl;
  cout << endl;
  cout << "***********************************************************" << endl;
  cout << "         FIT FINALIZED SUCCESSFULLY : " << endl;
  cout << "            - minuit status " << status << endl;
  cout << "            - hess status " << HessStatus << endl;
  cout << "            - Edm = " << Edmloc << endl;
  cout << fixed;
  cout << "            - nll = " << nll->getVal()  << endl;

  cout << " -- " ; sw.Print();
  cout << "***********************************************************" << endl;
  cout << endl;
  cout << endl;
  cout << endl;
  r->Print();
  MinuitStatusloc = status;
  sw.Print();
  //double final_nllval = nll->getVal();
  nll_val =  nll->getVal();

  //  cout<<" getVal="<< final_nllval<<" fitres nll="<<r->minNll()<< " by hand" <<final_nllval - nllval << endl;
  return r;
} // FitPDF
