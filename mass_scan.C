#include <stdio.h>


#include <TROOT.h>
#include <THStack.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TCanvas.h>
#include "TH1.h"
#include "TProfile.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"
#include "TF1.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "TEventList.h"
#include "TLorentzVector.h"
#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector>;
#endif
#include "TVector2.h"
#include "TLatex.h"
#include "TLegend.h"
#include <TStyle.h>
#include <TGraph.h>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include "TH1F.h"
#include "TH1D.h"
#include "TEventList.h"
#include "TObjArray.h"
#include "TLine.h"
#include "TGraphAsymmErrors.h"
#include "TArrow.h"
#include "AtlasStyle.h"
#include "RooHist.h"

void mass_scan() {
	
    gROOT->ProcessLine(".L AtlasStyle.C");
    SetAtlasStyle();
	
	std::ifstream infile("nll_hat.txt");
	std::string sline;
	double b;
	std::vector<double> vec_b;
	while (std::getline(infile, sline))
	{
		std::istringstream iss(sline);		
		std::string         a;
		double              b;
		std::getline(iss, a, '\t');
		iss >> b;
		
		std::cout<<b<<std::endl;
		vec_b.push_back(b);
	}
    
    double mH[100];
	double nll[100];
	for(int i=0;i<vec_b.size();i++){
		mH[i]=100+i*5;
		nll[i]=vec_b.at(i);
	}
	
	std::ifstream infile_inj("nll_hat_inj.txt");
	std::string sline_inj;
	double b_inj;
	std::vector<double> vec_b_inj;
	while (std::getline(infile_inj, sline_inj))
	{
		std::istringstream iss(sline_inj);
		std::string         a;
		double              b;
		std::getline(iss, a, '\t');
		iss >> b;
		
		std::cout<<b<<std::endl;
		vec_b_inj.push_back(b);
	}
    
    double mH_inj[100];
	double nll_inj[100];
	for(int i=0;i<vec_b_inj.size();i++){
		mH_inj[i]=100+i*5;
		nll_inj[i]=vec_b_inj.at(i);
	}
	
	
	double minimum = 9999999.;
	double mass_minimum = 99999;
	for(int i=0;i<vec_b.size();i++)if(nll[i]<minimum){ minimum = nll[i]; mass_minimum = mH[i];}
	for(int i=0;i<vec_b.size();i++) nll[i] = 2*(nll[i]-minimum);
	
	double minimum_inj = 9999999.;
	double mass_minimum_inj = 99999;
	for(int i=0;i<vec_b_inj.size();i++) if(nll_inj[i]<minimum_inj){ minimum_inj = nll_inj[i]; mass_minimum_inj = mH_inj[i];}
	for(int i=0;i<vec_b_inj.size();i++) nll_inj[i] = 2*(nll_inj[i]-minimum_inj);

    
    TCanvas *c1 = new TCanvas("c1","c1",0,0,800,600);
    c1->SetBorderSize(0);
    gStyle -> SetOptStat(0);
    gStyle -> SetPadBorderMode(0);
    gStyle -> SetPadBorderSize(0);
    gStyle -> SetCanvasBorderMode(0);
    
    gStyle -> SetPadLeftMargin(0.15);
    //gStyle -> SetPadRightMargin(0.05);
    //gStyle -> SetPadTopMargin(0.05);
    gStyle -> SetPadBottomMargin(0.15);
    
    gStyle->SetTitleXOffset(1.2);
    gStyle->SetTitleYOffset(1.);
    gStyle->SetTitleXSize(0.05);
    gStyle->SetTitleYSize(0.05);
    gStyle->SetLabelSize(0.05,"X");
    gStyle->SetLabelSize(0.05,"Y");
    gStyle->SetLabelOffset(0.003,"X");
    gStyle->SetLabelOffset(0.003,"Y");
    
    gStyle->SetPalette(1);
    gStyle->SetNdivisions(510);
    
    gROOT->SetStyle("ATLAS");
    gROOT->ForceStyle();
    
    gStyle -> SetPadLeftMargin(0.17);
    gStyle->SetTitleYOffset(0.8);
    
	TGraph *EXP = new TGraph(vec_b_inj.size(),mH_inj,nll_inj);
    EXP -> SetLineColor(1);
    EXP -> SetLineWidth(2);
    EXP -> SetLineStyle(2);
    EXP -> SetMarkerColor(1);
    EXP -> SetMarkerSize(1.0);
    EXP -> SetMarkerStyle(24);
    EXP -> Draw("L");
	
    TGraph *OBS = new TGraph(vec_b.size(),mH,nll);
    OBS -> SetLineColor(1);
    OBS -> SetLineWidth(2);
    OBS -> SetLineStyle(1);
    OBS -> SetMarkerColor(1);
    OBS -> SetMarkerSize(1.0);
    OBS -> SetMarkerStyle(20);
    OBS -> Draw("L");
    
	TH1F* histo = new TH1F("tmp","tmp",10,100,150);
	histo->GetXaxis()->SetTitle("m_{H} [GeV]");
	histo->GetYaxis()->SetTitle("-2#DeltalnL");
	histo->SetMaximum(8.5);
	histo->Draw();

	EXP -> Draw("LP");
	OBS -> Draw("LP");
    
    TLine* line = new TLine(100.,1.,150.,1.);
    line->SetLineColor(kRed);
    line->SetLineStyle(2);
    line->Draw();
    TLine* line1 = new TLine(100.,4.,150.,4.);
    line1->SetLineColor(kRed);
    line1->SetLineStyle(2);
    line1->Draw();

    
    TLegend* leg = new TLegend(0.55,0.7,0.9,0.85);
    leg->SetBorderSize(0.);
    leg->SetFillColor(0);
	leg->AddEntry(OBS,"#bf{Observed}","LP");
	leg->AddEntry(EXP,"#bf{Expected m_{H}=125 GeV}","LP");
    leg->Draw();
	
	TLatex l1; //l.SetTextAlign(12);
    l1.SetTextSize(0.04);
    l1.SetNDC();
    l1.SetTextColor(1);
	l1.DrawLatex(0.2,0.87,"H#rightarrow#tau_{jet}#tau_{jet}+2#nu");
	l1.DrawLatex(0.2,0.8,"#intLdt = 4.6fb^{-1}, #sqrt{s}=7 TeV");
	l1.DrawLatex(0.2,0.7,"#intLdt = 20.3fb^{-1}, #sqrt{s}=8 TeV");
	
	TF1 *func = new TF1("fit","pol5",110,150);
	func->SetLineWidth(0);
	OBS->Fit("fit","0");

	std::stringstream best;
	float err_dn = fabs(func->GetX(1,100,mass_minimum) - mass_minimum);
	float err_up = fabs(func->GetX(1,mass_minimum,150) - mass_minimum);
	
	best << "Best-fit m_{H}=" << mass_minimum <<setprecision(2)<< "^{+" << err_up << "}_{-" << err_dn << "} GeV";
	
//	float err_dn, err_up;
//	std::stringstream best;
//	
//	for(int i=0;i<OBS->GetN();i++){
//		double data_point_x=0.;
//		double data_point_y=0.;
//		OBS->GetPoint(i,data_point_x,data_point_y);
//		if(data_point_y>1. && data_point_x<mass_minimum) err_dn = data_point_x-mass_minimum;
//	}
//	for(int i=0;i<OBS->GetN();i++){
//		double data_point_x=0.;
//		double data_point_y=0.;
//		int point = OBS->GetN()-i-1;
//		OBS->GetPoint(point,data_point_x,data_point_y);
//		if(data_point_y>1. && data_point_x>mass_minimum) err_up = data_point_x-mass_minimum;
//	}
//
//	best << "Best-fit m_{H}=" << mass_minimum <<setprecision(2)<< "^{+" << err_up << "}_{" << err_dn << "} GeV";
	
	l1.DrawLatex(0.55,0.6,best.str().c_str());
	l1.DrawLatex(0.96,0.24,"#color[2]{1#sigma}");
 	l1.DrawLatex(0.96,0.52,"#color[2]{2#sigma}");
	
	c1->Print("mass_scan.eps");
 
    
}
