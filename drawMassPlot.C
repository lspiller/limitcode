//
//  drawMassPlot.C
//
//
//  Created by  Daniele Zanzi Old on 07/11/2013.
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
#include "TArrow.h"
#include "AtlasStyle.h"
#include "RooHist.h"

using namespace std;


void applyRew(TGraphAsymmErrors* histo_data,
			  TH1D* histo_fitErr,
			  TH1D* histo_QCD,
			  TH1D* histo_Zemb,
			  TH1D* histo_EW,
			  TH1D* histo_gg,
			  TH1D* histo_VBF,
			  TH1D* histo_wh,
			  TH1D* histo_zh,
			  TH1D* histo_gg_115,
			  TH1D* histo_VBF_115,
			  TH1D* histo_wh_115,
			  TH1D* histo_zh_115,
			  TH1D* histo_gg_135,
			  TH1D* histo_VBF_135,
			  TH1D* histo_wh_135,
			  TH1D* histo_zh_135
			  ){
	
	float tot_bkg = 0.;
	float tot_sig = 0.;
	
	for(int i=4;i<7;i++){
		
		tot_bkg += histo_QCD->GetBinContent(i+1);
		tot_bkg += histo_Zemb->GetBinContent(i+1);
		tot_bkg += histo_EW->GetBinContent(i+1);
		
		tot_sig += histo_gg->GetBinContent(i+1);
		tot_sig += histo_VBF->GetBinContent(i+1);
		if(histo_wh) tot_sig += histo_wh->GetBinContent(i+1);
		if(histo_zh) tot_sig += histo_zh->GetBinContent(i+1);
		
	}
	
	float weight = 1.;
	//	cout<<"tot_sig: "<<tot_sig<<endl;
	if(tot_sig>0.0001) weight = tot_sig/sqrt(tot_bkg);
	//	if(tot_sig>0.0001) weight = TMath::Log(1+tot_sig/tot_bkg);
	
	
	for(int i=0;i<histo_data->GetN();i++){
		
		float content = histo_fitErr->GetBinContent(i+1);
		float error = histo_fitErr->GetBinError(i+1);
		content *= weight;
		error *= weight;
		histo_fitErr->SetBinContent(i+1,content);
		histo_fitErr->SetBinError(i+1,error);
		
		content = histo_QCD->GetBinContent(i+1);
		error = histo_QCD->GetBinError(i+1);
		content *= weight;
		error *= weight;
		histo_QCD->SetBinContent(i+1,content);
		histo_QCD->SetBinError(i+1,error);
		
		content = histo_Zemb->GetBinContent(i+1);
		error = histo_Zemb->GetBinError(i+1);
		content *= weight;
		error *= weight;
		histo_Zemb->SetBinContent(i+1,content);
		histo_Zemb->SetBinError(i+1,error);
		
		content = histo_EW->GetBinContent(i+1);
		error = histo_EW->GetBinError(i+1);
		content *= weight;
		error *= weight;
		histo_EW->SetBinContent(i+1,content);
		histo_EW->SetBinError(i+1,error);
		
		content = histo_gg->GetBinContent(i+1);
		error = histo_gg->GetBinError(i+1);
		content *= weight;
		error *= weight;
		histo_gg->SetBinContent(i+1,content);
		histo_gg->SetBinError(i+1,error);
		
		content = histo_VBF->GetBinContent(i+1);
		error = histo_VBF->GetBinError(i+1);
		content *= weight;
		error *= weight;
		histo_VBF->SetBinContent(i+1,content);
		histo_VBF->SetBinError(i+1,error);
		
		if(histo_wh){content = histo_wh->GetBinContent(i+1);
			error = histo_wh->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_wh->SetBinContent(i+1,content);
			histo_wh->SetBinError(i+1,error);}
		
		if(histo_zh){content = histo_zh->GetBinContent(i+1);
			error = histo_zh->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_zh->SetBinContent(i+1,content);
			histo_zh->SetBinError(i+1,error);}
		
		
		if(histo_gg_115){content = histo_gg_115->GetBinContent(i+1);
			error = histo_gg_115->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_gg_115->SetBinContent(i+1,content);
			histo_gg_115->SetBinError(i+1,error);}
		
		if(histo_VBF_115){content = histo_VBF_115->GetBinContent(i+1);
			error = histo_VBF_115->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_VBF_115->SetBinContent(i+1,content);
			histo_VBF_115->SetBinError(i+1,error);}
		
		if(histo_wh_115){content = histo_wh_115->GetBinContent(i+1);
			error = histo_wh_115->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_wh_115->SetBinContent(i+1,content);
			histo_wh_115->SetBinError(i+1,error);}
		
		if(histo_zh_115){content = histo_zh_115->GetBinContent(i+1);
			error = histo_zh_115->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_zh_115->SetBinContent(i+1,content);
			histo_zh_115->SetBinError(i+1,error);}
		
		if(histo_gg_135){content = histo_gg_135->GetBinContent(i+1);
			error = histo_gg_135->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_gg_135->SetBinContent(i+1,content);
			histo_gg_135->SetBinError(i+1,error);}
		
		if(histo_VBF_135){content = histo_VBF_135->GetBinContent(i+1);
			error = histo_VBF_135->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_VBF_135->SetBinContent(i+1,content);
			histo_VBF_135->SetBinError(i+1,error);}
		
		if(histo_wh_135){content = histo_wh_135->GetBinContent(i+1);
			error = histo_wh_135->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_wh_135->SetBinContent(i+1,content);
			histo_wh_135->SetBinError(i+1,error);}
		
		if(histo_zh_135){content = histo_zh_135->GetBinContent(i+1);
			error = histo_zh_135->GetBinError(i+1);
			content *= weight;
			error *= weight;
			histo_zh_135->SetBinContent(i+1,content);
			histo_zh_135->SetBinError(i+1,error);}
		
		
		
		
		double eyl = histo_data->GetErrorYlow(i);
		double eyh = histo_data->GetErrorYhigh(i);
		double data_point_x=0.;
		double data_point_y=0.;
		histo_data->GetPoint(i,data_point_x,data_point_y);
		data_point_y *= weight;
		eyl *= weight;
		eyh *= weight;
		histo_data->SetPoint(i,data_point_x,data_point_y);
		histo_data->SetPointEYhigh(i,eyh);
		histo_data->SetPointEYlow(i,eyl);
	}
	
}

void AddTGraphAsymmErrors(TGraphAsymmErrors* histo, TGraphAsymmErrors* histo_add){
	
	for(int i =0;i<histo->GetN();i++){
		
		double eyl = histo->GetErrorYlow(i);
		double eyh = histo->GetErrorYhigh(i);
		double data_point_x=0.;
		double data_point_y=0.;
		histo->GetPoint(i,data_point_x,data_point_y);
		
		double eyl_add = histo_add->GetErrorYlow(i);
		double eyh_add = histo_add->GetErrorYhigh(i);
		double data_point_x_add=0.;
		double data_point_y_add=0.;
		histo_add->GetPoint(i,data_point_x_add,data_point_y_add);
		
		data_point_y +=data_point_y_add;
		eyl = sqrt(eyl*eyl+eyl_add*eyl_add);
		eyh = sqrt(eyh*eyh+eyh_add*eyh_add);
		
		histo->SetPoint(i,data_point_x,data_point_y);
		histo->SetPointEYhigh(i,eyh);
		histo->SetPointEYlow(i,eyl);
	}
	
}


void rebinVariableBins(TH1D* histo,vector<float> bins){
	
	int nbins = histo->GetNbinsX();
	int nbins_var = bins.size();
	if(nbins!=(nbins_var-1)) cout<<"different binning!!!"<<endl;
	
	double binning[nbins_var];
	for(int i=0;i<nbins_var;i++) binning[i]=bins.at(i);
	histo->SetBins(nbins,binning);
	for(int i=0;i<histo->GetNbinsX();i++){
		float width = histo->GetBinWidth(i+1);
		float content = histo->GetBinContent(i+1);
		float error = histo->GetBinError(i+1);
		content *=1./width;
		error *=1./width;
		histo->SetBinContent(i+1,content);
		histo->SetBinError(i+1,error);
	}
	
}

void rebinVariableBins(TGraphAsymmErrors* histo,vector<float> bins){
	
	int nbins = histo->GetN();
	int nbins_var = bins.size();
	if(nbins!=(nbins_var-1)) cout<<"different binning!!!"<<endl;
	
	for(int i=0;i<nbins;i++){
		double eyl = histo->GetErrorYlow(i);
		double eyh = histo->GetErrorYhigh(i);
		double exl = histo->GetErrorXlow(i);
		double exh = histo->GetErrorXhigh(i);
		double data_point_x=0.;
		double data_point_y=0.;
		histo->GetPoint(i,data_point_x,data_point_y);
		
		float bin_low = bins.at(i);
		float bin_high = bins.at(i+1);
		float bin_center = 0.5*(bin_high+bin_low);
		float bin_width = bin_high - bin_low;
		
		data_point_y *=1./bin_width;
		eyl *=1./bin_width;
		eyh *=1./bin_width;
		
		histo->SetPoint(i,bin_center,data_point_y);
		histo->SetPointEXlow(i,0.);
		histo->SetPointEXhigh(i,0.);
		histo->SetPointEYlow(i,eyl);
		histo->SetPointEYhigh(i,eyh);
    }
	
	//	double binning[nbins_var];
	//	for(int i=0;i<nbins_var;i++) binning[i]=bins.at(i);
	//	histo->SetBins(nbins,binning);
	
}

float yieldInMassWindow(TH1D* histo,vector<float> bins, float min, float max){
	
	float yield = 0.;
	
	int nbins = histo->GetNbinsX();
	int nbins_var = bins.size();
	if(nbins!=(nbins_var-1)) cout<<"different binning!!!"<<endl;
	
	int bin_min = -1;
	int bin_max = -1;
	for(int i = 0; i<bins.size(); i++){
		if(bins.at(i)<min) bin_min = i+1;
		if(bins.at(i)<max) bin_max = i+1;
	}
	
	yield = histo->Integral(bin_min,bin_max);
	
	return yield;
	
}

float yieldInMassWindowErr(TH1D* histo,vector<float> bins, float min, float max){
	
	float yield = 0.;
	
	int nbins = histo->GetNbinsX();
	int nbins_var = bins.size();
	if(nbins!=(nbins_var-1)) cout<<"different binning!!!"<<endl;
	
	int bin_min = -1;
	int bin_max = -1;
	for(int i = 0; i<bins.size(); i++){
		if(bins.at(i)<min) bin_min = i+1;
		if(bins.at(i)<max) bin_max = i+1;
	}
	
	for(int i=bin_min;i<(bin_max+1);i++){
		float error = histo->GetBinError(i);
		yield += error;
	}

	return yield;
	
}

float yieldInMassWindow(TGraphAsymmErrors* histo,vector<float> bins, float min, float max){
	
	float yield = 0.;
	
	int nbins = histo->GetN();
	int nbins_var = bins.size();
	if(nbins!=(nbins_var-1)) cout<<"different binning!!!"<<endl;
	
	int bin_min = -1;
	int bin_max = -1;
	for(int i = 0; i<bins.size(); i++){
		if(bins.at(i)<min) bin_min = i;
		if(bins.at(i)<max) bin_max = i;
	}
	
	for(int i=bin_min;i<(bin_max+1);i++){
		double data_point_x=0.;
		double data_point_y=0.;
		histo->GetPoint(i,data_point_x,data_point_y);
		yield +=data_point_y;
    }
	
	return yield;
	
}

TH1D* AddBin(TH1D* histo,vector<float>bins){
	
	string histo_name(histo->GetName());
	histo_name += "_newBins";
	double binning[bins.size()];
	for(int i=0;i<bins.size();i++) binning[i]=bins.at(i);
	int nbins = bins.size()-1;
	TH1D* new_histo = new TH1D(histo_name.c_str(),histo_name.c_str(),nbins,0.,256.);
	new_histo->SetBins(nbins,binning);
	for(int i=0;i<histo->GetNbinsX();i++){
		float width = histo->GetBinWidth(i+1);
		float content = histo->GetBinContent(i+1);
		float error = histo->GetBinError(i+1);
		new_histo->SetBinContent(i+1,content);
		new_histo->SetBinError(i+1,error);
	}
	
	return new_histo;
	
}

TGraphAsymmErrors* AddBin(TGraphAsymmErrors* histo,vector<float> bins){
	
	int nbins = bins.size()-1;
	TGraphAsymmErrors* new_histo = new TGraphAsymmErrors(nbins);
	
	
	for(int i=0;i<histo->GetN();i++){
		double eyl = histo->GetErrorYlow(i);
		double eyh = histo->GetErrorYhigh(i);
		double exl = histo->GetErrorXlow(i);
		double exh = histo->GetErrorXhigh(i);
		double data_point_x=0.;
		double data_point_y=0.;
		histo->GetPoint(i,data_point_x,data_point_y);
		
		float bin_low = bins.at(i);
		float bin_high = bins.at(i+1);
		float bin_center = 0.5*(bin_high+bin_low);
		
		new_histo->SetPoint(i,bin_center,data_point_y);
		new_histo->SetPointEXlow(i,0.);
		new_histo->SetPointEXhigh(i,0.);
		new_histo->SetPointEYlow(i,eyl);
		new_histo->SetPointEYhigh(i,eyh);
    }
	for(int i=histo->GetN();i<new_histo->GetN();i++){
		
		float bin_low = bins.at(i);
		float bin_high = bins.at(i+1);
		float bin_center = 0.5*(bin_high+bin_low);
		
		new_histo->SetPoint(i,bin_center,0);
		new_histo->SetPointEXlow(i,0.);
		new_histo->SetPointEXhigh(i,0.);
		new_histo->SetPointEYlow(i,0);
		new_histo->SetPointEYhigh(i,0);
    }
	
	return new_histo;
	
}

TH1D* newBinning(TH1D* histo,vector<float>bins){
	
	string histo_name(histo->GetName());
	histo_name += "_VBFBins";
	double binning[bins.size()];
	for(int i=0;i<bins.size();i++) binning[i]=bins.at(i);
	int nbins = bins.size()-1;
	TH1D* new_histo = (TH1D*)histo->Rebin(nbins,histo_name.c_str(),binning);
	return new_histo;
	
}

TGraphAsymmErrors*  newBinning(TGraphAsymmErrors*  histo,vector<float>bins, vector<float> old_bins){
	
	int nbins = bins.size()-1;
	TGraphAsymmErrors* new_histo = new TGraphAsymmErrors(nbins);
	
	int new_bin = 0;
	int old_j=1;
	for(int i=1;i<bins.size();i++){
		
		float data_y = 0;
		float erry_up = 0;
		float erry_dn = 0;
		float data_x = 0.5*(bins.at(i-1)+bins.at(i));
		
		//		cout<< "Bin "<< i << endl;
		
		for(int j=old_j;(old_bins[j]<=bins[i] && j<(old_bins.size()));j++){
			
			double eyl = histo->GetErrorYlow(j-1);
			double eyh = histo->GetErrorYhigh(j-1);
			double x=0.;
			double y=0.;
			histo->GetPoint(j-1,x,y);
			
			data_y+=y;
			erry_up = sqrt(erry_up*erry_up+eyh*eyh);
			erry_dn = sqrt(erry_dn*erry_dn+eyl*eyl);
			
			//			cout<< i << "\t" << j << "\t[" << bins[i] << "]\t[" << old_bins[j] << "]\t"<< data_y << "\t" << eyl << "\t" << eyh << endl;
			
			old_j=j+1;
		}
		
		new_histo->SetPoint(new_bin,data_x,data_y);
		new_histo->SetPointEYhigh(new_bin,erry_up);
		new_histo->SetPointEYlow(new_bin,erry_dn);
		new_bin++;
		
	}
	
	return new_histo;
	
}

//TH1D* splitInUniformBins(TH1D* histo){
//
//	string histo_name(histo->GetName());
//	histo_name += "_uniform";
//	TH1D* new_histo = new TH1D(histo_name.c_str(),histo_name.c_str(),64,0.,256.);
//
//	int new_bin = 0;
//	for(int i =0;i<histo->GetNbinsX();i++){
//		float content = histo->GetBinContent(i+1);
//		float error = histo->GetBinError(i+1);
//		float low_edge = histo->GetBinLowEdge(i+1);
//		float width = histo->GetBinWidth(i+1);
//		int n_new_bins = width/4.;
//		for(int j=0;j<n_new_bins;j++){
//			new_bin++;
//			new_histo->SetBinContent(new_bin,content);
//			new_histo->SetBinError(new_bin,error);
//		}
//	}
//
//	return new_histo;
//
//}
//
//TGraphAsymmErrors* splitInUniformBins(TGraphAsymmErrors* histo, vector<float> bins){
//
//	string histo_name(histo->GetName());
//	histo_name += "_uniform";
//	TGraphAsymmErrors* new_histo = new TGraphAsymmErrors(64);
//
//	int new_bin = 0;
//	for(int i =0;i<histo->GetN();i++){
//
//		double eyl = histo->GetErrorYlow(i);
//		double eyh = histo->GetErrorYhigh(i);
//		double data_point_x=0.;
//		double data_point_y=0.;
//		histo->GetPoint(i,data_point_x,data_point_y);
//
//		float low_bin = bins.at(i);
//		float high_bin = bins.at(i+1);
//		float width = high_bin - low_bin;
//		int npoint = width/4.;
//
//		eyl *=1./sqrt(npoint);
//		eyh *=1./sqrt(npoint);
//
//		for(int j=0;j<npoint;j++){
//			data_point_x = low_bin + 2. + j*4.;
//			new_histo->SetPoint(new_bin,data_point_x,data_point_y);
//			new_histo->SetPointEYhigh(new_bin,eyh);
//			new_histo->SetPointEYlow(new_bin,eyl);
//			new_bin++;
//		}
//	}
//
//	return new_histo;
//
//}


int draw_massplot(TGraphAsymmErrors* histo_data,
				  TH1D* histo_Zemb,
				  TH1D* histo_QCD,
				  TH1D* histo_EW,
				  TH1D* histo_gg,
				  TH1D* histo_VBF,
				  TH1D* histo_wh,
				  TH1D* histo_zh,
				  TH1D* fit_err,
				  std::string category,
				  vector<float> bins,
				  bool rebin = true,
				  TH1D* histo_gg_115=0,
				  TH1D* histo_VBF_115=0,
				  TH1D* histo_wh_115=0,
				  TH1D* histo_zh_115=0,
				  TH1D* histo_gg_135=0,
				  TH1D* histo_VBF_135=0,
				  TH1D* histo_wh_135=0,
				  TH1D* histo_zh_135=0
				  ){
	
    if(histo_QCD){
		if(rebin)rebinVariableBins(histo_QCD,bins);
		histo_QCD->SetMarkerColor(0);
		histo_QCD->SetMarkerStyle(0);
		histo_QCD->SetLineColor(kGray+2);
		histo_QCD->SetFillColor(kGray+1);
	}
    if(histo_EW){
		if(rebin)rebinVariableBins(histo_EW,bins);
		histo_EW->SetMarkerColor(0);
		histo_EW->SetMarkerStyle(0);
		histo_EW->SetLineColor(kBlue+1);
		histo_EW->SetFillColor(kBlue);
	}
    if(histo_Zemb){
		if(rebin)rebinVariableBins(histo_Zemb,bins);
		histo_Zemb->SetMarkerColor(0);
		histo_Zemb->SetMarkerStyle(0);
		histo_Zemb->SetLineColor(kAzure+9);
		histo_Zemb->SetFillColor(kAzure+10);
	}
    if(histo_gg){
		if(rebin)rebinVariableBins(histo_gg,bins);
		histo_gg->SetLineStyle(1);
		histo_gg->SetLineWidth(1);
		histo_gg->SetLineColor(kRed);
		histo_gg->SetFillColor(kRed);
	}
    if(histo_VBF){
		if(rebin)rebinVariableBins(histo_VBF,bins);
		histo_VBF->SetLineStyle(1);
		histo_VBF->SetLineWidth(1);
		histo_VBF->SetLineColor(kRed+1);
		histo_VBF->SetFillColor(kRed+1);
	}
    if(histo_wh){
		if(rebin)rebinVariableBins(histo_wh,bins);
		histo_wh->SetLineStyle(1);
		histo_wh->SetLineWidth(1);
		histo_wh->SetLineColor(kRed+2);
		histo_wh->SetFillColor(kRed+2);
	}
	if(histo_zh){
		if(rebin)rebinVariableBins(histo_zh,bins);
		histo_zh->SetLineStyle(1);
		histo_zh->SetLineWidth(1);
		histo_zh->SetLineColor(kRed+2);
		histo_zh->SetFillColor(kRed+2);
	}
	
	if(histo_gg_115){
		if(rebin)rebinVariableBins(histo_gg_115,bins);
		histo_gg_115->SetLineStyle(1);
		histo_gg_115->SetLineWidth(1);
		histo_gg_115->SetLineColor(kBlue);
		histo_gg_115->SetFillColor(kBlue);
	}
    if(histo_VBF_115){
		if(rebin)rebinVariableBins(histo_VBF_115,bins);
		histo_VBF_115->SetLineStyle(1);
		histo_VBF_115->SetLineWidth(1);
		histo_VBF_115->SetLineColor(kBlue);
		histo_VBF_115->SetFillColor(kBlue);
	}
    if(histo_wh_115){
		if(rebin)rebinVariableBins(histo_wh_115,bins);
		histo_wh_115->SetLineStyle(1);
		histo_wh_115->SetLineWidth(1);
		histo_wh_115->SetLineColor(kBlue);
		histo_wh_115->SetFillColor(kBlue);
	}
	if(histo_zh_115){
		if(rebin)rebinVariableBins(histo_zh_115,bins);
		histo_zh_115->SetLineStyle(1);
		histo_zh_115->SetLineWidth(1);
		histo_zh_115->SetLineColor(kBlue);
		histo_zh_115->SetFillColor(kBlue);
	}
	if(histo_gg_135){
		if(rebin)rebinVariableBins(histo_gg_135,bins);
		histo_gg_135->SetLineStyle(1);
		histo_gg_135->SetLineWidth(1);
		histo_gg_135->SetLineColor(kMagenta);
		histo_gg_135->SetFillColor(kMagenta);
	}
    if(histo_VBF_135){
		if(rebin)rebinVariableBins(histo_VBF_135,bins);
		histo_VBF_135->SetLineStyle(1);
		histo_VBF_135->SetLineWidth(1);
		histo_VBF_135->SetLineColor(kMagenta);
		histo_VBF_135->SetFillColor(kMagenta);
	}
    if(histo_wh_135){
		if(rebin)rebinVariableBins(histo_wh_135,bins);
		histo_wh_135->SetLineStyle(1);
		histo_wh_135->SetLineWidth(1);
		histo_wh_135->SetLineColor(kMagenta);
		histo_wh_135->SetFillColor(kMagenta);
	}
	if(histo_zh_135){
		if(rebin)rebinVariableBins(histo_zh_135,bins);
		histo_zh_135->SetLineStyle(1);
		histo_zh_135->SetLineWidth(1);
		histo_zh_135->SetLineColor(kMagenta);
		histo_zh_135->SetFillColor(kMagenta);
	}
	
	
	
	if(fit_err){
		if(rebin)rebinVariableBins(fit_err,bins);
	}
    
    if(histo_data){
		if(rebin)rebinVariableBins(histo_data,bins);
		histo_data->SetMarkerColor(1);
		histo_data->SetMarkerStyle(20);
		histo_data->SetLineColor(1);
		histo_data->SetLineWidth(1);
	}
    
    // stack and tot histo:
    string histo_name(histo_QCD->GetName());
    histo_name += category;
    histo_name += "_stack";
    THStack *tmp_stack = new THStack(histo_name.c_str(),histo_name.c_str());
	tmp_stack->Add(histo_EW);
    tmp_stack->Add(histo_QCD);
    tmp_stack->Add(histo_Zemb);
	if(histo_wh) tmp_stack->Add(histo_wh);
	if(histo_zh) tmp_stack->Add(histo_zh);
	tmp_stack->Add(histo_VBF);
	tmp_stack->Add(histo_gg);
	
	histo_name = histo_QCD->GetName();
	histo_name += "_tot";
	TH1D* tot_histo = (TH1D*)histo_QCD->Clone(histo_name.c_str());
	tot_histo->Add(histo_EW);
	tot_histo->Add(histo_Zemb);
	tot_histo->Add(histo_gg);
	tot_histo->Add(histo_VBF);
	if(histo_wh) tot_histo->Add(histo_wh);
	if(histo_zh) tot_histo->Add(histo_zh);
	
	histo_name += "_bkg";
	TH1D* tot_histo_bkg = (TH1D*)histo_QCD->Clone(histo_name.c_str());
	tot_histo_bkg->Add(histo_EW);
	tot_histo_bkg->Add(histo_Zemb);
	
	histo_name += "_signal";
	TH1D* tot_histo_signal = (TH1D*)histo_gg->Clone(histo_name.c_str());
	tot_histo_signal->Add(histo_VBF);
	if(histo_wh) tot_histo_signal->Add(histo_wh);
	if(histo_zh) tot_histo_signal->Add(histo_zh);
	
	histo_name += "_signal_115";
	TH1D* tot_histo_signal_115 = (TH1D*)histo_gg->Clone(histo_name.c_str());
	tot_histo_signal_115->Reset();
	if(histo_gg_115) tot_histo_signal_115->Add(histo_gg_115);
	if(histo_VBF_115) tot_histo_signal_115->Add(histo_VBF_115);
	if(histo_wh_115) tot_histo_signal_115->Add(histo_wh_115);
	if(histo_zh_115) tot_histo_signal_115->Add(histo_zh_115);
	
	histo_name += "_signal_135";
	TH1D* tot_histo_signal_135 = (TH1D*)histo_gg->Clone(histo_name.c_str());
	tot_histo_signal_135->Reset();
	if(histo_gg_135) tot_histo_signal_135->Add(histo_gg_135);
	if(histo_VBF_135) tot_histo_signal_135->Add(histo_VBF_135);
	if(histo_wh_135) tot_histo_signal_135->Add(histo_wh_135);
	if(histo_zh_135) tot_histo_signal_135->Add(histo_zh_135);
	
	tot_histo_signal->SetLineStyle(2);
    tot_histo_signal->SetLineColor(kRed);
    tot_histo_signal->SetLineWidth(2);
    tot_histo_signal->SetFillColor(0);
	
	tot_histo_signal_115->SetLineStyle(2);
    tot_histo_signal_115->SetLineColor(kBlue);
    tot_histo_signal_115->SetLineWidth(2);
    tot_histo_signal_115->SetFillColor(0);
	
	tot_histo_signal_135->SetLineStyle(2);
    tot_histo_signal_135->SetLineColor(kMagenta);
    tot_histo_signal_135->SetLineWidth(2);
    tot_histo_signal_135->SetFillColor(0);
    
	float max=0.;
    int tot_bins = tot_histo->GetNbinsX();
    for(int i=0;i<tot_bins;i++){
        if(tot_histo->GetBinContent(i+1)>max) max = tot_histo->GetBinContent(i+1);
		double data_point_x=0.;
		double data_point_y=0.;
		histo_data->GetPoint(i,data_point_x,data_point_y);
		if(data_point_y>max) max = data_point_y;
    }
	tot_histo->SetMinimum(0.);
	tot_histo->SetMaximum(max*1.6);
	
    std::stringstream name_yaxis;
    float bin_size = (tot_histo->GetXaxis()->GetXmax() - tot_histo->GetXaxis()->GetXmin())/tot_histo->GetNbinsX();
    name_yaxis << "dN/dm_{#tau#tau}^{MMC} [1/GeV]";
    std::string xaxis_name("m_{#tau#tau}^{MMC} [GeV]");
	tot_histo->GetXaxis()->SetTitle(xaxis_name.c_str());
    tot_histo->GetYaxis()->SetTitle(name_yaxis.str().c_str());
	
    tot_histo->GetYaxis()->SetTitleSize(0.06);
    tot_histo->GetYaxis()->SetLabelSize(0.06);
	
    tot_histo->SetMarkerColor(0);
    tot_histo->SetMarkerStyle(0);
    tot_histo->SetLineColor(0);
    tot_histo->SetFillColor(0);
    
    
    float x1[500],syst1[500];
    int nbins1 = fit_err->GetNbinsX();
    for(int b=0;b<nbins1;b++){
        
        x1[2*b]=fit_err->GetBinLowEdge(b+1);
        x1[2*b+1]=fit_err->GetBinLowEdge(b+2);
        
        x1[4*nbins1-2*b-2]=fit_err->GetBinLowEdge(b+2);
        x1[4*nbins1-2*b-1]=fit_err->GetBinLowEdge(b+1);
        
        float tot_content = tot_histo->GetBinContent(b+1);
        float error = fit_err->GetBinError(b+1);
		
        
        syst1[2*b]= tot_content+error;
        syst1[2*b+1]= tot_content+error;
        
        syst1[4*nbins1-2*b-2]= tot_content-error;
        syst1[4*nbins1-2*b-1]= tot_content-error;
        
        
    }
    
    TGraph bands1(4*nbins1,x1,syst1);
    bands1.SetFillStyle(3004);
    bands1.SetFillColor(1);
    bands1.SetLineWidth(2);
    bands1.SetLineColor(0);
    
	std::stringstream lumi_string;
	lumi_string << "#int Ldt = 4.6-20.3 fb^{-1}, #sqrt{s} = 7+8 TeV";
	
    TCanvas canvas("can","can",800,600);
    
    canvas.Divide(1,2);
    
    double t_size = 0.06;
    double t_off = 1.;
    canvas.cd(1);
    gPad->SetPad( .005, .3525,.995,.995);
    gPad->SetBottomMargin(0.001);
    gPad->SetRightMargin(0.10);
    double height_1 = gPad->YtoPixel(gPad->GetY1());
    
    canvas.cd(2);
    gPad->SetPad( .005, .005,.995,.3525);
    gPad->SetTopMargin(0.001);
    gPad->SetBottomMargin(0.30);
    double height_2 = gPad->YtoPixel(gPad->GetY1());
    
    canvas.cd(1);
    //gPad->SetLogy();
	
    tot_histo->Draw("HIST");
    tmp_stack->Draw("SAME HIST");
    bands1.Draw("same LF");
	histo_data->Draw("P");
	
    TLegend leg;
    leg.SetBorderSize(0.);
    leg.SetFillColor(0);
	leg.SetX1NDC(0.58);
	leg.SetX2NDC(0.88);
	leg.SetY1NDC(0.45);
	leg.SetY2NDC(0.9);
    
    TLatex l1; //l.SetTextAlign(12);
    l1.SetTextSize(0.05);
    l1.SetNDC();
    l1.SetTextColor(1);
	
	float bestfit_mu = 1.18;
	
	// normalizize to same integral:
	double integral = tot_histo_signal->Integral(0,tot_histo_signal->GetNbinsX()+2);
	double integral_115 = tot_histo_signal_115->Integral(0,tot_histo_signal_115->GetNbinsX()+2);
	double integral_135 = tot_histo_signal_135->Integral(0,tot_histo_signal_135->GetNbinsX()+2);
	if(integral_115) integral_115 = integral/integral_115;
	if(integral_135) integral_135 = integral/integral_135;
	if(histo_gg_115) tot_histo_signal_115->Scale(integral_115);
	if(histo_gg_135) tot_histo_signal_135->Scale(integral_135);
	
	integral_115 *=bestfit_mu;
	integral_135 *=bestfit_mu;
	
	std::stringstream leg_115;
	leg_115 << "H(m_{H}=115 GeV, #mu="<<setprecision(2)<<integral_115 <<")";
	std::stringstream leg_125;
	leg_125 << "H(m_{H}=125 GeV, #mu="<<setprecision(2)<<bestfit_mu <<")";
	std::stringstream leg_135;
	leg_135 << "H(m_{H}=135 GeV, #mu="<<setprecision(2)<<integral_135 <<")";
    
    leg.AddEntry(histo_data,"data","LP");
    leg.AddEntry(histo_QCD,"Multi-jets","F");
    leg.AddEntry(histo_Zemb,"Z#rightarrow#tau#tau","F");
    leg.AddEntry(histo_EW,"Others","F");
	leg.AddEntry(histo_gg,"ggF(m_{H}=125 GeV)","F");
    leg.AddEntry(histo_VBF,"VBF(m_{H}=125 GeV)","F");
	if(histo_wh)leg.AddEntry(histo_wh,"VH(m_{H}=125 GeV)","F");
	if(histo_gg_115)leg.AddEntry(tot_histo_signal_115,leg_115.str().c_str(),"L");
	if(histo_gg)leg.AddEntry(tot_histo_signal,leg_125.str().c_str(),"L");
	if(histo_gg_135)leg.AddEntry(tot_histo_signal_135,leg_135.str().c_str(),"L");
	
	
	l1.DrawLatex(0.2,0.87,lumi_string.str().c_str());
    l1.DrawLatex(0.2,0.78,category.c_str());
	leg.Draw();
	
	
	
    canvas.cd(2);
    
    float x[500],syst[500],stat[500];
    int nbins = fit_err->GetNbinsX();
    for(int b=0;b<nbins;b++){
        
        x[2*b]=fit_err->GetBinLowEdge(b+1);
        x[2*b+1]=fit_err->GetBinLowEdge(b+2);
        
        x[4*nbins-2*b-2]=fit_err->GetBinLowEdge(b+2);
        x[4*nbins-2*b-1]=fit_err->GetBinLowEdge(b+1);
        
        float error = fit_err->GetBinError(b+1);
		
        syst[2*b]= +error;
        syst[2*b+1]= +error;
        
        syst[4*nbins-2*b-2]= -error;
        syst[4*nbins-2*b-1]= -error;
		
    }
    
    TGraph bands(4*nbins,x,syst);
    bands.SetFillStyle(3004);
    bands.SetFillColor(1);
    bands.SetLineWidth(2);
    bands.SetLineColor(0);
	
	//
	//    histo_name = tot_histo->GetName();
	//    histo_name += "_ratio";
	//    TH1F* tmp_tot_histo = (TH1F*)tot_histo->Clone(histo_name.c_str());
	//    tmp_tot_histo->Sumw2();
	//    tmp_tot_histo->SetMarkerColor(1);
	//    tmp_tot_histo->SetMarkerStyle(20);
	//    tmp_tot_histo->SetLineColor(1);
	//    tmp_tot_histo->SetLineStyle(1);
	//	  tmp_tot_histo->Divide(total_bgk);
	
    int npoint = 0;
    for(int i=0;i<tot_histo_bkg->GetNbinsX();i++) if(tot_histo_bkg->GetBinContent(i+1)>0) npoint++;
    TGraphAsymmErrors graph_diff(npoint);
    
    graph_diff.SetLineWidth(1);
    graph_diff.SetLineColor(1);
    graph_diff.SetLineStyle(1);
	
    int ipoint = 0;
	max = 0;
    float min = 999.;
	
    for(int i=0;i<tot_histo_bkg->GetNbinsX();i++){
		double eyl = histo_data->GetErrorYlow(ipoint);
		double eyh = histo_data->GetErrorYhigh(ipoint);
		double exl = histo_data->GetErrorXlow(ipoint);
		double exh = histo_data->GetErrorXhigh(ipoint);
		double data_point_x=0.;
		double data_point_y=0.;
		histo_data->GetPoint(ipoint,data_point_x,data_point_y);
		double content = tot_histo_bkg->GetBinContent(i+1);
		data_point_y -=content;
		
		graph_diff.SetPoint(ipoint,data_point_x,data_point_y);
		graph_diff.SetPointEXlow(ipoint,exl);
		graph_diff.SetPointEXhigh(ipoint,exh);
		graph_diff.SetPointEYlow(ipoint,eyl);
		graph_diff.SetPointEYhigh(ipoint,eyh);
		ipoint += 1;
		if(data_point_y>max) max = data_point_y;
		if(data_point_y<min) min = data_point_y;
		
    }
	
    for(int x=0;x<tot_histo_signal->GetNbinsX();x++){
        if(tot_histo_signal->GetBinContent(x+1)>max) max = tot_histo_signal->GetBinContent(x+1);
        if(tot_histo_signal->GetBinContent(x+1)<min) min = tot_histo_signal->GetBinContent(x+1);
    }
	
    max *=1.9;
	min *=1.9;
    if(min>=0 || fabs(min)<0.05*fabs(max))min = -1.*max;
    tot_histo_signal->SetMaximum(max);
    tot_histo_signal->SetMinimum(min);
    
    tot_histo_signal->GetYaxis()->CenterTitle(true);
    tot_histo_signal->GetYaxis()->SetNdivisions(605,kTRUE);
    tot_histo_signal->GetYaxis()->SetLabelSize(t_size*height_1/height_2);
    tot_histo_signal->GetYaxis()->SetTitleSize(t_size*height_1/height_2);
    tot_histo_signal->GetYaxis()->SetTitleOffset(t_off*height_2/height_1);
    
    tot_histo_signal->GetXaxis()->SetLabelSize(t_size*height_1/height_2);
    tot_histo_signal->GetXaxis()->SetTitleSize(t_size*height_1/height_2);
    tot_histo_signal->GetXaxis()->SetLabelOffset(t_off*0.05*height_2/height_1);
	tot_histo_signal->GetYaxis()->SetTitle("Data-Bkg");
	tot_histo_signal->GetXaxis()->SetTitle(xaxis_name.c_str());
	
	
    tot_histo_signal->Draw("HIST");
	if(histo_gg_115) tot_histo_signal_115->Draw("HIST SAME");
	if(histo_gg_135) tot_histo_signal_135->Draw("HIST SAME");
    tot_histo_signal->Draw("HIST SAME");
    bands.Draw("same LF");
    //Statbands.Draw("same LF");
    
    TLine line(tot_histo_signal->GetXaxis()->GetXmin(),0.,tot_histo_signal->GetXaxis()->GetXmax(),0.);
    line.SetLineColor(kGray+2);
    line.SetLineStyle(2);
    line.SetLineWidth(2);
    line.Draw();
	graph_diff.Draw("P");
	
	
    canvas.cd();
    
    std::string canvas_name("ExctractedHistos/");
    canvas_name = canvas_name + histo_data->GetName()+".eps";
    canvas.Print(canvas_name.c_str());
    
    return 0;
	
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
	
	int index_VBF_2012 = 4;
	
	vector<string> category_names;
	category_names.push_back("VBF High-p_{T}^{H} 2011");
	category_names.push_back("VBF Low-p_{T}^{H} 2011");
	category_names.push_back("Boost High-p_{T}^{H} 2011");
	category_names.push_back("Boost Low-p_{T}^{H} 2011");
	category_names.push_back("VBF High-p_{T}^{H} 2012");
	category_names.push_back("VBF Low-p_{T}^{H} Tight 2012");
	category_names.push_back("VBF Low-p_{T}^{H} Loose 2012");
	category_names.push_back("Boost High-p_{T}^{H} 2012");
	category_names.push_back("Boost Low-p_{T}^{H} 2012");
	
	vector<string> input_files;
	input_files.push_back("ExctractedHistos/vbf_lowdr_2011.root");
	input_files.push_back("ExctractedHistos/vbf_highdr_2011.root");
	input_files.push_back("ExctractedHistos/boost_tight_2011.root");
	input_files.push_back("ExctractedHistos/boost_loose_2011.root");
	input_files.push_back("ExctractedHistos/vbf_tight_lowdr_2012.root");
	input_files.push_back("ExctractedHistos/vbf_tight_highdr_2012.root");
	input_files.push_back("ExctractedHistos/vbf_loose_highdr_2012.root");
	input_files.push_back("ExctractedHistos/boost_tight_2012.root");
	input_files.push_back("ExctractedHistos/boost_loose_2012.root");
	
	vector<string> input_files_115;
	input_files_115.push_back("ExctractedHistos/vbf_lowdr_2011_115.root");
	input_files_115.push_back("ExctractedHistos/vbf_highdr_2011_115.root");
	input_files_115.push_back("ExctractedHistos/boost_tight_2011_115.root");
	input_files_115.push_back("ExctractedHistos/boost_loose_2011_115.root");
	input_files_115.push_back("ExctractedHistos/vbf_tight_lowdr_2012_115.root");
	input_files_115.push_back("ExctractedHistos/vbf_tight_highdr_2012_115.root");
	input_files_115.push_back("ExctractedHistos/vbf_loose_highdr_2012_115.root");
	input_files_115.push_back("ExctractedHistos/boost_tight_2012_115.root");
	input_files_115.push_back("ExctractedHistos/boost_loose_2012_115.root");
	
	vector<string> input_files_135;
	input_files_135.push_back("ExctractedHistos/vbf_lowdr_2011_135.root");
	input_files_135.push_back("ExctractedHistos/vbf_highdr_2011_135.root");
	input_files_135.push_back("ExctractedHistos/boost_tight_2011_135.root");
	input_files_135.push_back("ExctractedHistos/boost_loose_2011_135.root");
	input_files_135.push_back("ExctractedHistos/vbf_tight_lowdr_2012_135.root");
	input_files_135.push_back("ExctractedHistos/vbf_tight_highdr_2012_135.root");
	input_files_135.push_back("ExctractedHistos/vbf_loose_highdr_2012_135.root");
	input_files_135.push_back("ExctractedHistos/boost_tight_2012_135.root");
	input_files_135.push_back("ExctractedHistos/boost_loose_2012_135.root");
	
	vector<vector<float> > binning;
	binning.push_back(std::vector<float>());
	binning.back().push_back(0); //0
	binning.back().push_back(64); //1
	binning.back().push_back(80); //2
	binning.back().push_back(92); //3
	binning.back().push_back(104); //4
	binning.back().push_back(116); //5
	binning.back().push_back(132); //6
	binning.back().push_back(256); //7
	
	binning.push_back(std::vector<float>());
	binning.back().push_back(0); //0
	binning.back().push_back(64); //0
	binning.back().push_back(80); //0
	binning.back().push_back(92); //0
  	binning.back().push_back(104); //1
	binning.back().push_back(116); //2
	binning.back().push_back(132); //3
	binning.back().push_back(152); //5
//	binning.back().push_back(176); //6
	binning.back().push_back(256); //0
	
	
	binning.push_back(std::vector<float>());
	binning.back().push_back(0); //0
	binning.back().push_back(64); //0
	binning.back().push_back(72); //1
	binning.back().push_back(80); //2
	binning.back().push_back(84); //3
	binning.back().push_back(88); //4
	binning.back().push_back(92); //5
	binning.back().push_back(96); //6
	binning.back().push_back(100); //7
	binning.back().push_back(104); //8
	binning.back().push_back(108); //9
	binning.back().push_back(112); //10
	binning.back().push_back(116); //11
	binning.back().push_back(120); //12
	binning.back().push_back(124); //13
	binning.back().push_back(128); //14
	binning.back().push_back(132); //15
//	binning.back().push_back(136); //16
	binning.back().push_back(140); //17
//	binning.back().push_back(144); //18
	binning.back().push_back(160); //19
//	binning.back().push_back(168); //20
//	binning.back().push_back(176); //20
//	binning.back().push_back(200); //21
	binning.back().push_back(256); //0
	
	
	binning.push_back(std::vector<float>());
	binning.back().push_back(0); //0
	binning.back().push_back(64); //0
	binning.back().push_back(80); //1
	binning.back().push_back(84); //2
	binning.back().push_back(88); //3
	binning.back().push_back(92); //4
	binning.back().push_back(96); //5
	binning.back().push_back(100); //6
	binning.back().push_back(104); //7
	binning.back().push_back(108); //8
	binning.back().push_back(112); //9
	binning.back().push_back(116); //10
	binning.back().push_back(120); //11
	binning.back().push_back(124); //12
	binning.back().push_back(128); //13
	binning.back().push_back(132); //14
	binning.back().push_back(136); //15
	binning.back().push_back(140); //16
//	binning.back().push_back(144); //17
	binning.back().push_back(156); //19
//	binning.back().push_back(176); //21
	binning.back().push_back(200); //23
	binning.back().push_back(256); //0

	//2012
	
	binning.push_back(std::vector<float>());
	binning.back().push_back(0); //0
	binning.back().push_back(64); //1
	binning.back().push_back(80); //2
	binning.back().push_back(92); //3
	binning.back().push_back(104); //4
	binning.back().push_back(116); //5
	binning.back().push_back(132); //6
	binning.back().push_back(176); //7
	binning.back().push_back(256); //8
	
	binning.push_back(std::vector<float>());
	binning.back().push_back(0); //0
	binning.back().push_back(64); //0
	binning.back().push_back(80); //0
	binning.back().push_back(92); //0
  	binning.back().push_back(104); //1
	binning.back().push_back(116); //2
	binning.back().push_back(132); //3
	binning.back().push_back(152); //5
	binning.back().push_back(176); //6
	binning.back().push_back(256); //0
	
	binning.push_back(std::vector<float>());
	binning.back().push_back(0); //0
	binning.back().push_back(64); //0
	binning.back().push_back(80); //0
	binning.back().push_back(92); //0
  	binning.back().push_back(104); //1
	binning.back().push_back(116); //2
	binning.back().push_back(132); //3
	binning.back().push_back(152); //5
	binning.back().push_back(176); //6
	binning.back().push_back(256); //0
	
	binning.push_back(std::vector<float>());
	binning.back().push_back(0); //0
	binning.back().push_back(64); //1
	binning.back().push_back(72); //2
	binning.back().push_back(80); //3
	binning.back().push_back(84); //4
	binning.back().push_back(88); //5
	binning.back().push_back(92); //6
	binning.back().push_back(96); //7
	binning.back().push_back(100); //8
	binning.back().push_back(104); //9
	binning.back().push_back(108); //10
	binning.back().push_back(112); //11
	binning.back().push_back(116); //12
	binning.back().push_back(120); //13
	binning.back().push_back(124); //14
	binning.back().push_back(128); //15
	binning.back().push_back(132); //16
//	binning.back().push_back(136); //17
	binning.back().push_back(140); //18
//	binning.back().push_back(144); //19
	binning.back().push_back(156); //20
//	binning.back().push_back(160); //21
//	binning.back().push_back(168); //22
	binning.back().push_back(176); //23
//	binning.back().push_back(184); //24
//	binning.back().push_back(200); //25
	binning.back().push_back(256); //26
	
	binning.push_back(std::vector<float>());
	binning.back().push_back(0); //0
	binning.back().push_back(64); //1
	binning.back().push_back(80); //2
	binning.back().push_back(84); //3
	binning.back().push_back(88); //4
	binning.back().push_back(92); //5
	binning.back().push_back(96); //6
	binning.back().push_back(100); //7
	binning.back().push_back(104); //8
	binning.back().push_back(108); //9
	binning.back().push_back(112); //10
	binning.back().push_back(116); //11
	binning.back().push_back(120); //12
	binning.back().push_back(124); //13
	binning.back().push_back(128); //14
	binning.back().push_back(132); //15
	binning.back().push_back(136); //16
	binning.back().push_back(140); //17
	binning.back().push_back(148); //18
	binning.back().push_back(156); //19
	binning.back().push_back(176); //20
//	binning.back().push_back(200); //21
	binning.back().push_back(256); //22
	
	
	vector<TGraphAsymmErrors*> data_histos;
	vector<TH1D*> Ztt_histos;
	vector<TH1D*> QCD_histos;
	vector<TH1D*> EWK_histos;
	vector<TH1D*> ggH_histos;
	vector<TH1D*> VBFH_histos;
	vector<TH1D*> WH_histos;
	vector<TH1D*> ZH_histos;
	vector<TH1D*> fitErr_histos;
	
	vector<TH1D*> ggH_histos_115;
	vector<TH1D*> VBFH_histos_115;
	vector<TH1D*> WH_histos_115;
	vector<TH1D*> ZH_histos_115;
	
	vector<TH1D*> ggH_histos_135;
	vector<TH1D*> VBFH_histos_135;
	vector<TH1D*> WH_histos_135;
	vector<TH1D*> ZH_histos_135;
	
	vector<TGraphAsymmErrors*> data_histos_unif;
	vector<TH1D*> Ztt_histos_unif;
	vector<TH1D*> QCD_histos_unif;
	vector<TH1D*> EWK_histos_unif;
	vector<TH1D*> ggH_histos_unif;
	vector<TH1D*> VBFH_histos_unif;
	vector<TH1D*> WH_histos_unif;
	vector<TH1D*> ZH_histos_unif;
	vector<TH1D*> fitErr_histos_unif;
	
	vector<TH1D*> ggH_histos_unif_115;
	vector<TH1D*> VBFH_histos_unif_115;
	vector<TH1D*> WH_histos_unif_115;
	vector<TH1D*> ZH_histos_unif_115;
	
	vector<TH1D*> ggH_histos_unif_135;
	vector<TH1D*> VBFH_histos_unif_135;
	vector<TH1D*> WH_histos_unif_135;
	vector<TH1D*> ZH_histos_unif_135;
	
	std::fstream text_file;
	std:: string latex_file_name("yields.txt");
	text_file.open (latex_file_name.c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);
	
	for(int i =0;i<input_files.size();i++){
		TFile *finput = TFile::Open(input_files.at(i).c_str());
		TFile *finput_115 = TFile::Open(input_files_115.at(i).c_str());
		TFile *finput_135 = TFile::Open(input_files_135.at(i).c_str());
		
		data_histos.push_back(0);
		Ztt_histos.push_back(0);
		QCD_histos.push_back(0);
		EWK_histos.push_back(0);
		ggH_histos.push_back(0);
		VBFH_histos.push_back(0);
		WH_histos.push_back(0);
		ZH_histos.push_back(0);
		fitErr_histos.push_back(0);
		
		ggH_histos_115.push_back(0);
		VBFH_histos_115.push_back(0);
		WH_histos_115.push_back(0);
		ZH_histos_115.push_back(0);
		
		ggH_histos_135.push_back(0);
		VBFH_histos_135.push_back(0);
		WH_histos_135.push_back(0);
		ZH_histos_135.push_back(0);
		
		cout<<input_files.at(i).c_str()<<endl;
		text_file<<input_files.at(i).c_str()<<"\n";

		
		finput->GetObject("DataAsymError",data_histos.back());
		finput->GetObject("My_Ztt",Ztt_histos.back());
		finput->GetObject("My_QCD",QCD_histos.back());
		finput->GetObject("My_EWK",EWK_histos.back());
		finput->GetObject("My_ggH",ggH_histos.back());
		finput->GetObject("My_VBFH",VBFH_histos.back());
		finput->GetObject("My_WH",WH_histos.back());
		finput->GetObject("My_ZH",ZH_histos.back());
		finput->GetObject("My_FitError_AfterFit",fitErr_histos.back());
		
		float yield_data = yieldInMassWindow(data_histos.back(),binning.at(i),111,139);
		float yield_Ztt = yieldInMassWindow(Ztt_histos.back(),binning.at(i),111,139);
		float yield_QCD = yieldInMassWindow(QCD_histos.back(),binning.at(i),111,139);
		float yield_EW = yieldInMassWindow(EWK_histos.back(),binning.at(i),111,139);
		float yield_ggH = yieldInMassWindow(ggH_histos.back(),binning.at(i),111,139);
		float yield_VBFH = yieldInMassWindow(VBFH_histos.back(),binning.at(i),111,139);
		float yield_WH = 0;
		if(WH_histos.back()) yield_WH = yieldInMassWindow(WH_histos.back(),binning.at(i),111,139);
		float yield_ZH = 0;
		if(ZH_histos.back()) yield_ZH = yieldInMassWindow(ZH_histos.back(),binning.at(i),111,139);
		float yield_err = yieldInMassWindowErr(fitErr_histos.back(),binning.at(i),111,139);

		float yield_bkg = yield_Ztt + yield_QCD + yield_EW;
		float yield_signal = yield_ggH + yield_VBFH + yield_WH + yield_ZH;

		text_file<<"data:\t"<<yield_data<<"\n";
		text_file<<"Ztt:\t"<<yield_Ztt<<"\n";
		text_file<<"QCD:\t"<<yield_QCD<<"\n";
		text_file<<"EW:\t"<<yield_EW<<"\n";
		text_file<<"ggH:\t"<<yield_ggH<<"\n";
		text_file<<"VBFH:\t"<<yield_VBFH<<"\n";
		text_file<<"WH:\t"<<yield_ggH<<"\n";
		text_file<<"ZF:\t"<<yield_VBFH<<"\n";
		text_file<<"tot bkg:\t"<<yield_bkg<<"\n";
		text_file<<"err bkg+signal:\t"<<yield_err<<"\n";
		text_file<<"tot H:\t"<<yield_signal<<"\n";

		if(finput_115){
			finput_115->GetObject("My_ggH",ggH_histos_115.back());
			finput_115->GetObject("My_VBFH",VBFH_histos_115.back());
			finput_115->GetObject("My_WH",WH_histos_115.back());
			finput_115->GetObject("My_ZH",ZH_histos_115.back());
		}
		if(finput_135){
			finput_135->GetObject("My_ggH",ggH_histos_135.back());
			finput_135->GetObject("My_VBFH",VBFH_histos_135.back());
			finput_135->GetObject("My_WH",WH_histos_135.back());
			finput_135->GetObject("My_ZH",ZH_histos_135.back());
		}
		
		stringstream name_data;
		if(data_histos.back()){name_data << data_histos.back()->GetName() << "_" << i;
			data_histos.back()->SetName(name_data.str().c_str());}
		
		stringstream name_Z;
		if(Ztt_histos.back()){name_Z << Ztt_histos.back()->GetName() << "_" << i;
			Ztt_histos.back()->SetName(name_Z.str().c_str());}
		
		stringstream name_QCD;
		if(QCD_histos.back()){name_QCD << QCD_histos.back()->GetName() << "_" << i;
			QCD_histos.back()->SetName(name_QCD.str().c_str());}
		
		stringstream name_EWK;
		if(EWK_histos.back()){name_EWK << EWK_histos.back()->GetName() << "_" << i;
			EWK_histos.back()->SetName(name_EWK.str().c_str());}
		
		stringstream name_ggH;
		if(ggH_histos.back()){name_ggH << ggH_histos.back()->GetName() << "_" << i;
			ggH_histos.back()->SetName(name_ggH.str().c_str());}
		
		stringstream name_VBFH;
		if(VBFH_histos.back()){name_VBFH << VBFH_histos.back()->GetName() << "_" << i;
			VBFH_histos.back()->SetName(name_VBFH.str().c_str());}
		
		stringstream name_WH;
		if(WH_histos.back()){name_WH << WH_histos.back()->GetName() << "_" << i;
			WH_histos.back()->SetName(name_WH.str().c_str());}
		
		stringstream name_ZH;
		if(ZH_histos.back()){name_ZH << ZH_histos.back()->GetName() << "_" << i;
			ZH_histos.back()->SetName(name_ZH.str().c_str());}
		
		stringstream name_fit;
		if(fitErr_histos.back()){name_fit << fitErr_histos.back()->GetName() << "_" << i;
			fitErr_histos.back()->SetName(name_fit.str().c_str());}
		
		
		stringstream name_ggH_115;
		if(ggH_histos_115.back()){name_ggH_115 << ggH_histos_115.back()->GetName() << "_115_" << i;
			ggH_histos_115.back()->SetName(name_ggH_115.str().c_str());}
		stringstream name_ggH_135;
		if(ggH_histos_135.back()){name_ggH_135 << ggH_histos_135.back()->GetName() << "_135_" << i;
			ggH_histos_135.back()->SetName(name_ggH_135.str().c_str());}
		
		stringstream name_VBFH_115;
		if(VBFH_histos_115.back()){name_VBFH_115 << VBFH_histos_115.back()->GetName() << "_115_" << i;
			VBFH_histos_115.back()->SetName(name_VBFH_115.str().c_str());}
		stringstream name_VBFH_135;
		if(VBFH_histos_135.back()){name_VBFH_135 << VBFH_histos_135.back()->GetName() << "_135_" << i;
			VBFH_histos_135.back()->SetName(name_VBFH_135.str().c_str());}
		
		stringstream name_WH_115;
		if(WH_histos_115.back()){name_WH_115 << WH_histos_115.back()->GetName() << "_115_" << i;
			WH_histos_115.back()->SetName(name_WH_115.str().c_str());}
		stringstream name_WH_135;
		if(WH_histos_135.back()){name_WH_135 << WH_histos_135.back()->GetName() << "_135_" << i;
			WH_histos_135.back()->SetName(name_WH_135.str().c_str());}
		
		stringstream name_ZH_115;
		if(ZH_histos_115.back()){name_ZH_115 << ZH_histos_115.back()->GetName() << "_115_" << i;
			ZH_histos_115.back()->SetName(name_ZH_115.str().c_str());}
		stringstream name_ZH_135;
		if(ZH_histos_135.back()){name_ZH_135 << ZH_histos_135.back()->GetName() << "_135_" << i;
			ZH_histos_135.back()->SetName(name_ZH_135.str().c_str());}
		
		draw_massplot(data_histos.back(),
					  Ztt_histos.back(),
					  QCD_histos.back(),
					  EWK_histos.back(),
					  ggH_histos.back(),
					  VBFH_histos.back(),
					  WH_histos.back(),
					  ZH_histos.back(),
					  fitErr_histos.back(),
					  category_names.at(i),
					  binning.at(i),
					  true,
					  ggH_histos_115.back(),
					  VBFH_histos_115.back(),
					  WH_histos_115.back(),
					  ZH_histos_115.back(),
					  ggH_histos_135.back(),
					  VBFH_histos_135.back(),
					  WH_histos_135.back(),
					  ZH_histos_135.back()
					  );
		
		if(i==0){
			
			data_histos_unif.push_back(AddBin(data_histos.back(),binning.at(index_VBF_2012)));
			Ztt_histos_unif.push_back(AddBin(Ztt_histos.back(),binning.at(index_VBF_2012)));
			QCD_histos_unif.push_back(AddBin(QCD_histos.back(),binning.at(index_VBF_2012)));
			EWK_histos_unif.push_back(AddBin(EWK_histos.back(),binning.at(index_VBF_2012)));
			ggH_histos_unif.push_back(AddBin(ggH_histos.back(),binning.at(index_VBF_2012)));
			VBFH_histos_unif.push_back(AddBin(VBFH_histos.back(),binning.at(index_VBF_2012)));
			WH_histos_unif.push_back(0);
			ZH_histos_unif.push_back(0);
			if(WH_histos.back())WH_histos_unif.back()=AddBin(WH_histos.back(),binning.at(index_VBF_2012));
			if(ZH_histos.back())ZH_histos_unif.back()=AddBin(ZH_histos.back(),binning.at(index_VBF_2012));
			fitErr_histos_unif.push_back(AddBin(fitErr_histos.back(),binning.at(index_VBF_2012)));
			
			ggH_histos_unif_115.push_back(0);
			VBFH_histos_unif_115.push_back(0);
			WH_histos_unif_115.push_back(0);
			ZH_histos_unif_115.push_back(0);
			if(ggH_histos_115.back())ggH_histos_unif_115.back()=AddBin(ggH_histos_115.back(),binning.at(index_VBF_2012));
			if(VBFH_histos_115.back())VBFH_histos_unif_115.back()=AddBin(VBFH_histos_115.back(),binning.at(index_VBF_2012));
			if(WH_histos_115.back())WH_histos_unif_115.back()=AddBin(WH_histos_115.back(),binning.at(index_VBF_2012));
			if(ZH_histos_115.back())ZH_histos_unif_115.back()=AddBin(ZH_histos_115.back(),binning.at(index_VBF_2012));
			
			ggH_histos_unif_135.push_back(0);
			VBFH_histos_unif_135.push_back(0);
			WH_histos_unif_135.push_back(0);
			ZH_histos_unif_135.push_back(0);
			if(ggH_histos_135.back())ggH_histos_unif_135.back()=AddBin(ggH_histos_135.back(),binning.at(index_VBF_2012));
			if(VBFH_histos_135.back())VBFH_histos_unif_135.back()=AddBin(VBFH_histos_135.back(),binning.at(index_VBF_2012));
			if(WH_histos_135.back())WH_histos_unif_135.back()=AddBin(WH_histos_135.back(),binning.at(index_VBF_2012));
			if(ZH_histos_135.back())ZH_histos_unif_135.back()=AddBin(ZH_histos_135.back(),binning.at(index_VBF_2012));
			
		}
		if(i!=0 && i!=index_VBF_2012){
			
			data_histos_unif.push_back(newBinning(data_histos.back(),binning.at(index_VBF_2012),binning.at(i)));
			Ztt_histos_unif.push_back(newBinning(Ztt_histos.back(),binning.at(index_VBF_2012)));
			QCD_histos_unif.push_back(newBinning(QCD_histos.back(),binning.at(index_VBF_2012)));
			EWK_histos_unif.push_back(newBinning(EWK_histos.back(),binning.at(index_VBF_2012)));
			ggH_histos_unif.push_back(newBinning(ggH_histos.back(),binning.at(index_VBF_2012)));
			VBFH_histos_unif.push_back(newBinning(VBFH_histos.back(),binning.at(index_VBF_2012)));
			WH_histos_unif.push_back(0);
			ZH_histos_unif.push_back(0);
			if(WH_histos.back())WH_histos_unif.back()=newBinning(WH_histos.back(),binning.at(index_VBF_2012));
			if(ZH_histos.back())ZH_histos_unif.back()=newBinning(ZH_histos.back(),binning.at(index_VBF_2012));
			fitErr_histos_unif.push_back(newBinning(fitErr_histos.back(),binning.at(index_VBF_2012)));
			
			ggH_histos_unif_115.push_back(0);
			VBFH_histos_unif_115.push_back(0);
			WH_histos_unif_115.push_back(0);
			ZH_histos_unif_115.push_back(0);
			if(ggH_histos_115.back())ggH_histos_unif_115.back()=newBinning(ggH_histos_115.back(),binning.at(index_VBF_2012));
			if(VBFH_histos_115.back())VBFH_histos_unif_115.back()=newBinning(VBFH_histos_115.back(),binning.at(index_VBF_2012));
			if(WH_histos_115.back())WH_histos_unif_115.back()=newBinning(WH_histos_115.back(),binning.at(index_VBF_2012));
			if(ZH_histos_115.back())ZH_histos_unif_115.back()=newBinning(ZH_histos_115.back(),binning.at(index_VBF_2012));
			
			ggH_histos_unif_135.push_back(0);
			VBFH_histos_unif_135.push_back(0);
			WH_histos_unif_135.push_back(0);
			ZH_histos_unif_135.push_back(0);
			if(ggH_histos_135.back())ggH_histos_unif_135.back()=newBinning(ggH_histos_135.back(),binning.at(index_VBF_2012));
			if(VBFH_histos_135.back())VBFH_histos_unif_135.back()=newBinning(VBFH_histos_135.back(),binning.at(index_VBF_2012));
			if(WH_histos_135.back())WH_histos_unif_135.back()=newBinning(WH_histos_135.back(),binning.at(index_VBF_2012));
			if(ZH_histos_135.back())ZH_histos_unif_135.back()=newBinning(ZH_histos_135.back(),binning.at(index_VBF_2012));
			
		}
		
		// apply reweighting:
		applyRew(data_histos_unif.back(),
				 fitErr_histos_unif.back(),
				 QCD_histos_unif.back(),
				 Ztt_histos_unif.back(),
				 EWK_histos_unif.back(),
				 ggH_histos_unif.back(),
				 VBFH_histos_unif.back(),
				 WH_histos_unif.back(),
				 ZH_histos_unif.back(),
				 ggH_histos_unif_115.back(),
				 VBFH_histos_unif_115.back(),
				 WH_histos_unif_115.back(),
				 ZH_histos_unif_115.back(),
				 ggH_histos_unif_135.back(),
				 VBFH_histos_unif_135.back(),
				 WH_histos_unif_135.back(),
				 ZH_histos_unif_135.back()
				 );
		
	}
	
	for(int i =0;i<data_histos_unif.size()-1;i++){
		Ztt_histos_unif.back()->Add(Ztt_histos_unif.at(i));
		QCD_histos_unif.back()->Add(QCD_histos_unif.at(i));
		EWK_histos_unif.back()->Add(EWK_histos_unif.at(i));
		ggH_histos_unif.back()->Add(ggH_histos_unif.at(i));
		VBFH_histos_unif.back()->Add(VBFH_histos_unif.at(i));
		if(WH_histos_unif.at(i)) WH_histos_unif.back()->Add(WH_histos_unif.at(i));
		if(ZH_histos_unif.at(i)) ZH_histos_unif.back()->Add(ZH_histos_unif.at(i));
		AddTGraphAsymmErrors(data_histos_unif.back(),data_histos_unif.at(i));
		
		if(ggH_histos_unif_115.at(i)) ggH_histos_unif_115.back()->Add(ggH_histos_unif_115.at(i));
		if(VBFH_histos_unif_115.at(i)) VBFH_histos_unif_115.back()->Add(VBFH_histos_unif_115.at(i));
		if(WH_histos_unif_115.at(i)) WH_histos_unif_115.back()->Add(WH_histos_unif_115.at(i));
		if(ZH_histos_unif_115.at(i)) ZH_histos_unif_115.back()->Add(ZH_histos_unif_115.at(i));
		
		if(ggH_histos_unif_135.at(i)) ggH_histos_unif_135.back()->Add(ggH_histos_unif_135.at(i));
		if(VBFH_histos_unif_135.at(i)) VBFH_histos_unif_135.back()->Add(VBFH_histos_unif_135.at(i));
		if(WH_histos_unif_135.at(i)) WH_histos_unif_135.back()->Add(WH_histos_unif_135.at(i));
		if(ZH_histos_unif_135.at(i)) ZH_histos_unif_135.back()->Add(ZH_histos_unif_135.at(i));
		
	}
	
	
	draw_massplot(data_histos_unif.back(),
				  Ztt_histos_unif.back(),
				  QCD_histos_unif.back(),
				  EWK_histos_unif.back(),
				  ggH_histos_unif.back(),
				  VBFH_histos_unif.back(),
				  WH_histos_unif.back(),
				  ZH_histos_unif.back(),
				  fitErr_histos_unif.back(),
				  "S/#sqrt{B} weighted",
				  binning.back(),
				  false ,
				  ggH_histos_unif_115.back(),
				  VBFH_histos_unif_115.back(),
				  WH_histos_unif_115.back(),
				  ZH_histos_unif_115.back(),
				  ggH_histos_unif_135.back(),
				  VBFH_histos_unif_135.back(),
				  WH_histos_unif_135.back(),
				  ZH_histos_unif_135.back()
				  );
	
	
	text_file.close();
	
}




