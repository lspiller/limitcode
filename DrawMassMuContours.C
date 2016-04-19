//
//  File.c
//
//
//  Created by  Daniele Zanzi Old on 09/11/2013.
//
//

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
#include "TGraph2D.h"
#include "TArrow.h"
#include "AtlasStyle.h"
#include "RooHist.h"
#include "TRandom.h"

using namespace std;


void drawContour(TH2D* histo, TCanvas* c,TLegend* leg, float min_nll){
	
	std::vector<TGraph*> graphs;
	
	std::string name(histo->GetName());
	name += "_tmp";
	TH2D* tmp = (TH2D*)histo->Clone(name.c_str());
	
//	for(int x=0;x<histo->GetNbinsX();x++){
//		for(int y=0;y<histo->GetNbinsY();y++){
//			
//			float threshold = histo->GetBinContent(x+1,y+1);
//			float content = 0.;
//			
//			for(int x1=0;x1<histo->GetNbinsX();x1++){
//				for(int y1=0;y1<histo->GetNbinsY();y1++){
//					float bin_content = histo->GetBinContent(x1+1,y1+1);
//					if(bin_content>=threshold) content += bin_content;
//				}
//			}
//			tmp->SetBinContent(x+1,y+1,content);
//		}
//	}
	
	// set contour thresholds:
	double contours[2];
	contours[0] = 1+2*min_nll;
	contours[1] = 4+2*min_nll;
	
	TCanvas canvas_tmp("can_tmp","can_tmp",800,600);
	canvas_tmp.cd();
	gStyle->SetPalette(1);
	
	tmp->SetContour(2,contours);
	tmp->Draw("CONT LIST");
	canvas_tmp.Update();
	TObjArray *conts = (TObjArray*)gROOT->GetListOfSpecials()->FindObject("contours");
	//gDirectory->ls();
	TList* contLevel = NULL;
	TGraph* curv     = NULL;
	TGraph* gc       = NULL;
	
	Int_t nGraphs    = 0;
	Int_t TotalConts = 0;
	
	if (conts == NULL){
		printf("*** No Contours Were Extracted!\n");
		TotalConts = 0;
		return;
	} else {
		TotalConts = conts->GetSize();
	}
	
	printf("TotalConts = %d\n", TotalConts);
	
	for(int i = 0; i < TotalConts; i++){
		contLevel = (TList*)conts->At(i);
		printf("Contour %d has %d Graphs\n", i, contLevel->GetSize());
		nGraphs += contLevel->GetSize();
	}
	
	nGraphs = 0;
	Double_t x0, y0, z0;
	TLatex l;
	l.SetTextSize(0.03);
	l.SetTextColor(histo->GetLineColor());
	char val[20];
	
	c->cd();
	for(int i = 0; i < TotalConts; i++){
		contLevel = (TList*)conts->At(i);
		z0 = contours[i];
		printf("Z-Level Passed in as:  Z = %f\n", z0);
		
		// Get first graph from list on curves on this level
		curv = (TGraph*)contLevel->First();
		if(i==0)leg->AddEntry(curv,"68% CL","L");
		if(i==1)leg->AddEntry(curv,"95% CL","L");
		for(int j = 0; j < contLevel->GetSize(); j++){
			curv->GetPoint(0, x0, y0);
			curv->SetLineColor(histo->GetLineColor());
			curv->SetLineStyle(i+1);

			nGraphs ++;
			printf("\tGraph: %d  -- %d Elements\n", nGraphs,curv->GetN());
			
			// Draw clones of the graphs to avoid deletions in case the 1st
			// pad is redrawn.
			gc = (TGraph*)curv->Clone();
			gc->Draw("C");


			
			sprintf(val,"%g",z0);
			//l.DrawLatex(x0,y0,val);
			curv = (TGraph*)contLevel->After(curv); // Get Next graph
		}
	}
	
	
	
}

int main(int argc, char **argv){
	
    
    SetAtlasStyle();
	
	gStyle->SetTextSize(0.05);
	gStyle->SetTextColor(1);
	gStyle->SetLineColor(2);
	gStyle->SetFrameBorderMode(0);
	gStyle->SetFrameFillColor(0);
	gStyle->SetCanvasBorderMode(0);
	gStyle->SetCanvasColor(0);
	gStyle->SetPadBorderMode(0);
	gStyle->SetPadRightMargin(0.1);
	gStyle->SetPadLeftMargin(0.15);
	//gStyle->SetPadBottomMargin(0);
	gStyle->SetPadColor(0);
	gStyle->SetStatColor(0);
	gStyle->SetOptTitle(0);
	gStyle->SetOptStat(0);
	gStyle->SetOptFit(0);
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	//gStyle->SetOptStat(111111);
	gStyle->SetPalette(1);
	gStyle->SetPaintTextFormat("2.1E");
	gStyle->SetTitleYOffset(1.);
	
	
	vector<string> input_files;
	input_files.push_back("NLLScan/100/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/105/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/110/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/115/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/120/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/125/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/130/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/135/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/140/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/145/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	input_files.push_back("NLLScan/150/ScanAndFit_SigXsecOverSM_fixed0.5_5.root");
	
	vector<double> masses;
	masses.push_back(100);
	masses.push_back(105);
	masses.push_back(110);
	masses.push_back(115);
	masses.push_back(120);
	masses.push_back(125);
	masses.push_back(130);
	masses.push_back(135);
	masses.push_back(140);
	masses.push_back(145);
	masses.push_back(150);
	
	TGraph2D *nll_scan = new TGraph2D();
	nll_scan->SetMarkerColor(0);
	nll_scan->SetMarkerStyle(0);
	int points = 0;
	
	float min_nll = 999999.;
	float min_mu = 0;
	float min_mass = 0;
	
	for(int f=0;f<input_files.size();f++){
		TFile *finput = TFile::Open(input_files.at(f).c_str());
		TTree* tree = 0;
		finput->GetObject("FitResults",tree);
		if(tree==0) cout<< "tree not found" << endl;
		
		Double_t        nll_val;
		Double_t        Edm;
		UInt_t          MinuitStatus;
		UInt_t          HesseStatus;
		Double_t        mu;
		Double_t        mu_err;
		Int_t           mu_const;
		
		TBranch        *b_nll_val;   //!
		TBranch        *b_Edm;   //!
		TBranch        *b_MinuitStatus;   //!
		TBranch        *b_HesseStatus;   //!
		TBranch        *b_mu;   //!
		TBranch        *b_mu_err;   //!
		TBranch        *b_mu_const;   //!
		
		tree->SetMakeClass(1);
		
		tree->SetBranchAddress("nll_val", &nll_val, &b_nll_val);
		tree->SetBranchAddress("Edm", &Edm, &b_Edm);
		tree->SetBranchAddress("MinuitStatus", &MinuitStatus, &b_MinuitStatus);
		tree->SetBranchAddress("HesseStatus", &HesseStatus, &b_HesseStatus);
		tree->SetBranchAddress("mu", &mu, &b_mu);
		tree->SetBranchAddress("mu_err", &mu_err, &b_mu_err);
		tree->SetBranchAddress("mu_const", &mu_const, &b_mu_const);
		
		int total_entries = tree->GetEntries();
		for(unsigned int entry=0;entry<total_entries;entry++){
			
			tree->GetEntry(entry);
			double nll_val_my = 2*nll_val;
			cout<<masses.at(f)<<" "<<mu<<" "<<nll_val_my<<endl;
			double mass = masses.at(f);
			if(nll_val!=nll_val) continue;
			if(MinuitStatus!=0) continue;
			if(nll_val_my<min_nll){min_nll=nll_val_my;min_mu = mu;min_mass=mass;}
			nll_scan->SetPoint(points,mass,mu,nll_val_my);
			points++;
		}
		
		finput->Close();
	}
	
	cout<<"npoints "<<points<<endl;
	
	
	TCanvas *c = new TCanvas("c","Graph2D example",0,0,700,600);
	gStyle->SetPalette(1);
//	nll_scan->Draw("surf1");
	TH2D* th2_scan = nll_scan->GetHistogram();
	TH2D* th2_scan_empty = (TH2D*)nll_scan->Clone("empty");
	th2_scan_empty->Draw();
	TH2D* tmp = new TH2D("tmp","tmp",11,100,150,100,-0.5,5);
	tmp->GetXaxis()->SetNdivisions(605,kTRUE);
	tmp->GetXaxis()->SetTitle("m_{H} [GeV]");
	tmp->GetYaxis()->SetTitle("Signal Strength (#mu)");
	tmp->Draw();
	TLegend* leg = new TLegend();
    leg->SetBorderSize(0.);
    leg->SetFillColor(0);
	leg->SetX1NDC(0.4);
	leg->SetX2NDC(0.65);
	leg->SetY1NDC(0.68);
	leg->SetY2NDC(0.83);
	TGraph* min = new TGraph(1);
	min->SetMarkerStyle(20);
	min->SetMarkerColor(1);
	min->SetLineColor(1);
	min->SetPoint(1,min_mass,min_mu);
	min->Draw("P");
	leg->AddEntry(min,"Best Fit","P");
	drawContour(th2_scan,c,leg,min_nll);
	
	TLatex l1; //l.SetTextAlign(12);
    l1.SetTextSize(0.04);
    l1.SetNDC();
    l1.SetTextColor(1);
	

	std::stringstream lumi_string;
	lumi_string << "#int Ldt = 4.6-20.3 fb^{-1}, #sqrt{s} = 7+8 TeV";
	l1.DrawLatex(0.2,0.87,lumi_string.str().c_str());
	l1.DrawLatex(0.2,0.78,"H#rightarrow#tau_{had}#tau_{had}");
	leg->Draw();

	c->Print("MassVsMuCountur.eps");

//	Double_t x, y, z, P = 6.;
//	Int_t np = 200;
//	TGraph2D *dt = new TGraph2D();
//	TRandom *r = new TRandom();
//	
//	for (Int_t N=0; N<np; N++) {
//		x = 2*P*(r->Rndm(N))-P;
//		y = 2*P*(r->Rndm(N))-P;
//		z = (sin(x)/x)*(sin(y)/y)+0.2;
//		dt->SetPoint(N,x,y,z);
//	}
//	gStyle->SetPalette(1);
//	dt->Draw("surf1");
	

	
}