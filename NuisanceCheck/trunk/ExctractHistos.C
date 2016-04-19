// C++
#include <iostream>
#include <fstream>
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
#include "TGraph.h"
#include "TGraphAsymmErrors.h"

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
#include <RooMsgService.h>

using namespace std;

// Global variable
double bin_vbf_lowdr_2011[9] = {0.,64.,80.,92.,104.,116.,132.,152.,256.};
double bin_vbf_highdr_tight_2011[10] = {0.,64.,80.,92.,104.,116.,132.,152.,176.,256.};
double bin_vbf_highdr_loose_2011[10] = {0.,64.,80.,92.,104.,116.,132.,152.,176.,256.};
double bin_boost_tight_2011[25] = {0.,64.,72.,80.,84.,88.,92.,96.,100.,104.,108.,112.,116.,120.,124.,128.,132.,136.,140.,144.,152.,168.,176.,200.,256.};
double bin_boost_loose_2011[23] = {0.,72.,80.,84.,88.,92.,96.,100.,104.,108.,112.,116.,120.,124.,128.,132.,136.,140.,144.,152.,176.,200.,256.};
double bin_1jet_2011[30] = {0.,48.,52.,56.,60.,64.,68.,72.,76.,80.,84.,88.,92.,96.,100.,104.,108.,112.,116.,120.,124.,128.,132.,136.,140.,144.,152.,176.,200.,256.};

double bin_vbf_lowdr_2012[9] = {0.,64.,80.,92.,104.,116.,132.,152.,256.};
double bin_vbf_highdr_tight_2012[10] = {0.,64.,80.,92.,104.,116.,132.,152.,176.,256.};
double bin_vbf_highdr_loose_2012[10] = {0.,64.,80.,92.,104.,116.,132.,152.,176.,256.};
double bin_boost_tight_2012[27] = {0.,64.,72.,80.,84.,88.,92.,96.,100.,104.,108.,112.,116.,120.,124.,128.,132.,136.,140.,144.,152.,160.,168.,176.,184.,200.,256.};
double bin_boost_loose_2012[23] = {0.,72.,80.,84.,88.,92.,96.,100.,104.,108.,112.,116.,120.,124.,128.,132.,136.,140.,144.,152.,176.,200.,256.};
double bin_1jet_2012[33] = {0.,48.,52.,56.,60.,64.,68.,72.,76.,80.,84.,88.,92.,96.,100.,104.,108.,112.,116.,120.,124.,128.,132.,136.,140.,144.,148.,152.,160.,168.,176.,184.,256.};



// Function declaration
void ExctractAllHistos(TString inputfile);
TH1D *TGraphAsymmErrorsToTH1D(TGraphAsymmErrors *g, TH1D *hmodel);
TH1D *TGraphToTH1D(TGraph *g, TH1D *hmodel);
void ExctractHistoFromCanvas(TCanvas *can, vector<TH1*> &vec_histo, TGraphAsymmErrors* &gdata);
void ReBinHistos(vector<TH1*> &vec_histo, TGraphAsymmErrors* &gdata, double BinLowEdge[]);
void SaveNormalHistoInFile(TString FileName, vector<TH1*> vec_histo,TGraphAsymmErrors *gdata);
TCanvas *MakeBeautifulCanvas(TString cname, vector<TH1*> vec_histo,TGraphAsymmErrors *gdata);


void ExctractAllHistos(TString inputfile){
  
  // *** For test ***
  //TString cname="PlotsAfterGlobalFit/conditionnal_MuIsEqualTo_0/can_DistriAfterFit_t6jetin4btagin_GlobalFit_conditionnal_mu0";
  //TString cname="PlotsAfterGlobalFit/conditionnal_MuIsEqualTo_0/can_DistriAfterFit_lh_boosted_125_2012_GlobalFit_conditionnal_mu0";
  // ****************


  gSystem->Exec("mkdir -p ExctractedHistos");
	
	vector<string> canvas_names;
	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_vbf_lowdr_2011_GlobalFit_unconditionnal_mu0");
	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_vbf_highdr_2011_GlobalFit_unconditionnal_mu0");
	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_boost_tight_2011_GlobalFit_unconditionnal_mu0");
	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_boost_loose_2011_GlobalFit_unconditionnal_mu0");
//	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_1jet_2011_GlobalFit_unconditionnal_mu0");
	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_vbf_tight_lowdr_2012_GlobalFit_unconditionnal_mu0");
	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_vbf_tight_highdr_2012_GlobalFit_unconditionnal_mu0");
	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_vbf_loose_highdr_2012_GlobalFit_unconditionnal_mu0");
	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_boost_tight_2012_GlobalFit_unconditionnal_mu0");
	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_boost_loose_2012_GlobalFit_unconditionnal_mu0");
//	canvas_names.push_back("PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_hh_1jet_2012_GlobalFit_unconditionnal_mu0");

	
	vector<string> output_file_name;
	output_file_name.push_back("ExctractedHistos/vbf_lowdr_2011.root");
	output_file_name.push_back("ExctractedHistos/vbf_highdr_2011.root");
	output_file_name.push_back("ExctractedHistos/boost_tight_2011.root");
	output_file_name.push_back("ExctractedHistos/boost_loose_2011.root");
//	output_file_name.push_back("ExctractedHistos/1jet_2011.root");
	output_file_name.push_back("ExctractedHistos/vbf_tight_lowdr_2012.root");
	output_file_name.push_back("ExctractedHistos/vbf_tight_highdr_2012.root");
	output_file_name.push_back("ExctractedHistos/vbf_loose_highdr_2012.root");
	output_file_name.push_back("ExctractedHistos/boost_tight_2012.root");
	output_file_name.push_back("ExctractedHistos/boost_loose_2012.root");
//	output_file_name.push_back("ExctractedHistos/1jet_2012.root");

	
  TFile *finput = TFile::Open(inputfile);
	
	for(int i=0;i<canvas_names.size();i++){
  TString cname = canvas_names.at(i).c_str();
  TCanvas *can = (TCanvas*) finput->Get(cname);
  vector<TH1*> vec_histo;
  TGraphAsymmErrors *gdata;
  ExctractHistoFromCanvas(can,vec_histo,gdata);
  TString fname = output_file_name.at(i).c_str();
  SaveNormalHistoInFile(fname,vec_histo,gdata);
		
	}
  
  return;

  /*
  TFile *finput = TFile::Open(inputfile);  
  TString hm = "125";
  vector<TString> ChannelName;
  vector<double*> BinSize;
  ChannelName.clear();
  BinSize.clear();
  ChannelName.push_back("hh_boost_"+hm+"_2012"); BinSize.push_back( bin_boost );
  ChannelName.push_back("hh_vbf_"+hm+"_2012"); BinSize.push_back( bin_vbf );


  // Loop over the canvas you want to extract for conditional fit (without signal histograms)
  for (unsigned i=0 ; i<ChannelName.size() ; i++ ){
    TString cname = "PlotsAfterGlobalFit/conditionnal_MuIsEqualTo_0/can_DistriAfterFit_" + ChannelName[i] + "_GlobalFit_conditionnal_mu0";
    TCanvas *can = (TCanvas*) finput->Get(cname);
    vector<TH1*> vec_histo;
    TGraphAsymmErrors *gdata;
    ExctractHistoFromCanvas(can,vec_histo,gdata);
    ReBinHistos(vec_histo,gdata,BinSize[i]);
    TString fname = "ExctractedHistos/HistoConditionalFitBonly_" + ChannelName[i] + ".root";
    SaveNormalHistoInFile(fname,vec_histo,gdata);
  }
  

  // Loop over the canvas you want to extract for unconditional fit (with signal histograms)
  for (unsigned i=0 ; i<ChannelName.size() ; i++ ){
    TString cname = "PlotsAfterGlobalFit/unconditionnal/can_DistriAfterFit_" + ChannelName[i] + "_GlobalFit_unconditionnal_mu0";
    TCanvas *can = (TCanvas*) finput->Get(cname);
    vector<TH1*> vec_histo;
    TGraphAsymmErrors *gdata;
    ExctractHistoFromCanvas(can,vec_histo,gdata);
    ReBinHistos(vec_histo,gdata,BinSize[i]);
    TString fname = "ExctractedHistos/HistoUnonditionalFit_" + ChannelName[i] + ".root";
    SaveNormalHistoInFile(fname,vec_histo,gdata);
  }

  return;
  */
}



void SaveNormalHistoInFile(TString FileName, vector<TH1*> vec_histo,TGraphAsymmErrors *gdata){

  TFile *fout = new TFile(FileName,"RECREATE");
  fout->cd();

  gdata->Write();
  for (int i=0 ; i<vec_histo.size() ; i++){
    vec_histo[i]->Write();
  }

  fout->Close();
  return;

}


TCanvas *MakeBeautifulCanvas(TString cname, vector<TH1*> vec_histo, TGraphAsymmErrors *gdata){
  TCanvas *can_output(0);
  return can_output;

}


void ReBinHistos(vector<TH1*> &vec_histo, TGraphAsymmErrors* &gdata, double BinLowEdge[]){
  
  // Data with Asym error
  int n = gdata->GetN();
  for (int ip=0 ; ip<n ; ip++){
    double xl = BinLowEdge[ip];
    double xh = BinLowEdge[ip+1];
    double xc = xl + (xh-xl)/2.;
    double x,y;
    gdata->GetPoint(ip,x,y);
      std::cout<<"data: "<<ip<<"\t"<<x<<"\t"<<y<<"\t"<<std::endl;
    gdata->SetPoint(ip,xc,y);
      std::cout<<"data: "<<ip<<"\t"<<xc<<"\t"<<y<<"\t"<<std::endl;
    gdata->SetPointEXlow (ip,xc-xl);
    gdata->SetPointEXhigh(ip,xh-xc);
  }
    
    for (int ip=0 ; ip<n ; ip++){
        double x,y;
        gdata->GetPoint(ip,x,y);
        std::cout<<"data: "<<ip<<"\t"<<x<<"\t"<<y<<"\t"<<std::endl;
    }
  
  // Other histogramms
  for (unsigned i=0 ; i<vec_histo.size() ; i++){
    TH1F *htemp = new TH1F(vec_histo[i]->GetName(), vec_histo[i]->GetTitle(), vec_histo[i]->GetNbinsX(), BinLowEdge);
  
    for (int ib=1 ; ib<vec_histo[i]->GetNbinsX()+1 ; ib++){     
      htemp->SetBinContent(ib, vec_histo[i]->GetBinContent(ib) );
      htemp->SetBinError  (ib, vec_histo[i]->GetBinError(ib) );
    }

    htemp->SetLineColor(1);
    htemp->SetLineWidth(2);
    vec_histo[i] = htemp;
  }

  return;
}



void ExctractHistoFromCanvas(TCanvas *can, vector<TH1*> &vec_histo, TGraphAsymmErrors* &gdataAsymErr){

  vec_histo.clear();

  vector<TObject*> vec_MyObjects;
  TList *ListOfObject = can->GetListOfPrimitives();
  if (ListOfObject) {
    TIter next(ListOfObject);
    TObject *ThisObject;
    vec_MyObjects.clear();
    while ( (ThisObject=(TObject*)next()) ) vec_MyObjects.push_back( ThisObject->Clone() );
  }

  TH1D *hmodel(0);
  for (unsigned i=0 ; i<vec_MyObjects.size() ; i++){
    TString ObjectName = vec_MyObjects[i]->GetName();
    TString ClassName  = vec_MyObjects[i]->ClassName();

    if (ObjectName.Contains("NotAppears")) continue;
    if (ObjectName.Contains("Stacked_") && !ObjectName.Contains("NoStacked_")  ) continue;
   
    if(ClassName=="TH1D" && !hmodel)
      hmodel = (TH1D*) can->FindObject(ObjectName);
    if (!hmodel) continue;

    TH1D *htemp(0); 
    if(ClassName=="RooHist"){
      TGraphAsymmErrors *gRooHist = (TGraphAsymmErrors*) can->FindObject(ObjectName);
      if (!gRooHist) cout << "TGraphAsymmErrors object for " << ObjectName << " (class : " << ClassName << ") was not found !" << endl;
      if ( ObjectName=="Data" ){
	gdataAsymErr = (TGraphAsymmErrors*) gRooHist->Clone("DataAsymError");
	gdataAsymErr->SetTitle("DataAsymError");
	gdataAsymErr->SetLineWidth(2);
	gdataAsymErr->SetLineColor(1);
	gdataAsymErr->SetLineStyle(1);
      }
      htemp = TGraphAsymmErrorsToTH1D(gRooHist,hmodel);
      can->cd();
      gRooHist->Draw("LP");
      
    }
    
    if(ClassName=="RooCurve"){
      TGraph *gRooCurve = (TGraph*) can->FindObject(ObjectName);
      if (!gRooCurve) cout << "TGraph object for " << ObjectName << " (class : " << ClassName << ") was not found !" << endl;
      htemp = TGraphToTH1D(gRooCurve,hmodel);
    }
    
    if (htemp) vec_histo.push_back(htemp);

  }
  
  return;
}


TH1D* TGraphAsymmErrorsToTH1D(TGraphAsymmErrors *g, TH1D *hmodel){
  TH1D* hres = (TH1D*) hmodel->Clone();
  hres->Reset();
  TString hnameOld = (TString)g->GetName();
  if (hnameOld.Contains("BeforeFit") && !hnameOld.Contains("BkgBeforeFit")) hnameOld.ReplaceAll("BeforeFit","BeforeFit_BkgTot");
  hnameOld.ReplaceAll("NoStacked_","");
  hnameOld.ReplaceAll("BkgBeforeFit_","BeforeFit_");
  hres->SetName("My_"+hnameOld);
  hres->SetTitle(hnameOld);
  hres->SetLineWidth( 2 );
  hres->SetLineColor( 1 );
  hres->SetLineStyle( 1 );


  int Npts = g->GetN();
  double xprevious = 0.0;
  for (int ip=0 ; ip<Npts ; ip++){
    double x,y,erry;
    g->GetPoint(ip,x,y);
    erry = g->GetErrorY(ip);
    if (!(xprevious==x) || ip==0){
      double xbin = (x+xprevious)/2. ;
      double ycontent = y;
      int ib = hres->FindBin(xbin);
      if (ib<=hres->GetNbinsX()) {
	hres->SetBinContent(ib,ycontent);
	hres->SetBinError(ib,erry);
      }
    }    
    xprevious = x;
  }

  TCanvas *can = new TCanvas(hres->GetName(),hres->GetName(),600,600);
  can->cd();
  hres->Draw();
  return hres;
}


TH1D* TGraphToTH1D(TGraph *g, TH1D *hmodel){
  
  TString gname = (TString)g->GetName();
  bool IsForError=false;
  if (gname=="FitError_AfterFit") IsForError=true;

  TH1D* hres = (TH1D*) hmodel->Clone();
  hres->Reset();
  TString hnameOld = (TString)g->GetName();
  if (hnameOld.Contains("BeforeFit") && !hnameOld.Contains("BkgBeforeFit")) hnameOld.ReplaceAll("BeforeFit","BeforeFit_BkgTot");
  hnameOld.ReplaceAll("NoStacked_","");
  hnameOld.ReplaceAll("BkgBeforeFit_","BeforeFit_");
  hres->SetName("My_"+hnameOld);
  hres->SetTitle(hnameOld);
  hres->SetLineWidth( 2 );
  hres->SetLineColor( 1 );
  hres->SetLineStyle( 1 );
  
  // Get TH1F of the errors
  if (IsForError){

    double xl,yl,xh,yh;
    int NN=g->GetN() / 2;

    TGraph* gUp=new TGraph(NN);
    TGraph* gLow=new TGraph(NN);

    vector<double> ratios;
    for(int i=0;i<NN;i++) {
      g->GetPoint(i,xl,yl);
      g->GetPoint(i+NN,xh,yh);
      gUp->SetPoint(NN-1-i,xh,yh);
      gLow->SetPoint(i,xl,yl);
    }

    int Nbins = hmodel->GetNbinsX();
    double xc,yc,xu,yu,xl2,yl2;
    for(int i=0;i<NN;i++) {
      gUp->GetPoint(i,xu,yu);
      gLow->GetPoint(i,xl2,yl2);
      for (int ib=0 ; ib<Nbins+1 ; ib++){
	double dx=hmodel->GetBinWidth(ib);
	double xbin=hmodel->GetBinCenter(ib);
	xc=xl2+dx/2.0;
	yc=(yu+yl2)/2.0;
	if (fabs(xc-xbin)<dx/10.){
	  hres->SetBinContent(ib,yc);
	  hres->SetBinError(ib,fabs((yu-yl2)/2.0));
	}
      }
    }
    
    return hres;
  }
 

  // Get the TH1F for central value
  int Npts = g->GetN();
  double xprevious=0.;
  for (int ip=0 ; ip<Npts ; ip++){
    double x=0.0;
    double y=0.0;
    g->GetPoint(ip,x,y);
    if ( !(xprevious==x) ){
      double xbin = (x+xprevious)/2. ;
      double ycontent = y;
      int ib = hres->FindBin(xbin);
      if (ib<=hres->GetNbinsX()) hres->SetBinContent(ib,ycontent);
    }    
    xprevious = x;
  }
  
  return hres;
}
