//
//  PrintWS.C
//
//
//  Created by  Daniele Zanzi Old on 03/11/2013.
//
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
//
#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"
#include "TExec.h"
#include "TMath.h"
#include "TFile.h"
#include "TObjArray.h"
#include "TString.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TLegend.h"
#include "TLine.h"

#include "RooAbsData.h"
#include "RooDataHist.h"
#include "RooCategory.h"
#include "RooDataSet.h"
#include "RooAbsPdf.h"
#include "RooSimultaneous.h"
#include "RooWorkspace.h"
#include "RooStats/RooStatsUtils.h"
#include "RooStats/ModelConfig.h"

//
#include "RooStats/HistFactory/Channel.h"
#include "RooStats/HistFactory/Data.h"
#include "RooStats/HistFactory/Sample.h"
#include "RooStats/HistFactory/Systematics.h"
#include "RooStats/HistFactory/Measurement.h"
//
//#include "parseString.h"
//
using namespace std;
//using namespace RooFit;
using namespace RooStats;
using namespace HistFactory;

string removeAlpha(string input){
	size_t pos;
	while(input.find("alpha_")!=std::string::npos){
		pos = input.find("alpha_");
		input.erase(pos,6);
	}
	while(input.find("stat_hh_")!=std::string::npos){
		pos = input.find("stat_hh_");
		input.erase(pos,8);
	}
	while(input.find("ATLAS_")!=std::string::npos){
		pos = input.find("ATLAS_");
		input.erase(pos,6);
	}
	while(input.find("gamma_")!=std::string::npos){
		pos = input.find("gamma_");
		input.erase(pos,6);
	}
	while(input.find("ANA_")!=std::string::npos){
		pos = input.find("ANA_");
		input.erase(pos,4);
	}
	while(input.find("HH_")!=std::string::npos){
		pos = input.find("HH_");
		input.erase(pos,3);
	}
	while(input.find("norm_SF_HH_")!=std::string::npos){
		pos = input.find("norm_SF_HH_");
		input.erase(pos,11);
	}
	return input;
}


std::string removeUnderscore(std::string str){
	size_t pos;
		while(str.find("_")!=std::string::npos){
			pos = str.find("_");
			str.erase(pos,1);
			str.insert(pos," ");
		}
	return str;
}




void PrintWS(const char* input_file){
	//
	// Input file
	//
	TString ifname(input_file);
	TString wsname="combined";
	TString modname="ModelConfig";
	TString datname="obsData";
//      TString measname="AllSYS";
        TString measname="measurement_hh_15_combination_125";
	//


	vector<TString> vec_cname;
	//
	map<TString , vector<TString> > sample_per_channel;
	vector < map < TString, TString > > vec_map_hname_per_channel;
	//
	map<TString , vector<TString> > nfac_nam_per_channelsample;
	map<TString , vector<double> >  nfac_val_per_channelsample;
	map<TString , vector<double> >  nfac_low_per_channelsample;
	map<TString , vector<double> >  nfac_hig_per_channelsample;
	//
	map<TString , vector<TString> > osys_nam_per_channelsample;
	map<TString , vector<double> >  osys_low_per_channelsample;
	map<TString , vector<double> >  osys_hig_per_channelsample;
	//
	map<TString , vector<TString> > hsys_nam_per_channelsample;
	map<TString , vector<TString> > hsys_hnm_per_channelsample;
	map<TString , vector<TString> > hsys_hlo_per_channelsample;
	map<TString , vector<TString> > hsys_hhi_per_channelsample;
	//
	map<TString , vector<TString> > ohsys_nam_per_channelsample;
	map<TString , vector<double> >  ohsys_low_per_channelsample;
	map<TString , vector<double> >  ohsys_hig_per_channelsample;
	map<TString , vector<TString> > ohsys_hnm_per_channelsample;
	map<TString , vector<TString> > ohsys_hlo_per_channelsample;
	map<TString , vector<TString> > ohsys_hhi_per_channelsample;
	//
	TFile *ifile=TFile::Open(ifname);
        cout << "ONE\n";
	cout<<ifile->IsOpen()<<endl;
	Measurement*	meas=(Measurement*)ifile->Get(measname);
        cout << "TWO\n";
        cout << measname << "\n";
	//

	vector<Channel> vec_channel = meas->GetChannels();
        cout << "THREE\n";
	for (int ichannel=0;ichannel < vec_channel.size(); ++ichannel) {
		Channel& channel = vec_channel.at(ichannel);
		TString cname = channel.GetName();
		cout << ichannel << " " << cname << endl;
		vec_cname.push_back(cname);
		//
		Data&    data = channel.GetData();
		TString hdname ;
		if (data.GetHistoPath() != "") {
			hdname = Form("%s%s",data.GetHistoPath().c_str(),data.GetHistoName().c_str());
		} else {
			hdname = Form("%s",data.GetHistoName().c_str());
		}
		//
		map <TString, TString> map_hname;
		map_hname["Data"] = hdname;
		//
		vector<Sample > vec_sample = channel.GetSamples() ;
		vector<TString> vec_sname;
		vector<TString> vec_hsname;
		vector<TString> vec_hbname;
		for (int isample=0;isample < vec_sample.size(); ++isample) {
			Sample& sample=vec_sample.at(isample);
			//      sample.Print(cout);
			TString hname=sample.GetHistoName();
			TString sname=sample.GetName();
			cout << isample << " " << Form("%-6s",sname.Data()) << " hname = " << hname << endl;
			vec_sname.push_back(sname);
			//
			TString histfullname;
			if (sample.GetHistoPath() != "") {
				histfullname = Form("%s%s",sample.GetHistoPath().c_str(),sample.GetHistoName().c_str());
			} else {
				histfullname = Form("%s",sample.GetHistoName().c_str());
			}
			if (sname == "ggH" || sname == "VBF" || sname == "WH" || sname == "ZH") {
				vec_hsname.push_back(histfullname);
			} else {
				vec_hbname.push_back(histfullname);
			}
			//
			map_hname[sname] = histfullname;
			//
			vector<TString> vec_nfac_nam;
			vector<double> vec_nfac_val;
			vector<double> vec_nfac_low;
			vector<double> vec_nfac_hig;
			for ( unsigned int i = 0; i < sample.GetNormFactorList().size(); ++i ) {
				NormFactor nfac=sample.GetNormFactorList().at(i);
				cout << "Channel " << cname << " Sample " << sname << " NFactor " << nfac.GetName() << " "<< endl;
				vec_nfac_nam.push_back(nfac.GetName());
				vec_nfac_val.push_back(nfac.GetVal());
				vec_nfac_low.push_back(nfac.GetLow());
				vec_nfac_hig.push_back(nfac.GetHigh());
			}
			vector<TString> vec_osys_nam;
			vector<double>  vec_osys_low;
			vector<double>  vec_osys_hig;
			//
			vector<TString> vec_hsys_nam;
			vector<TString> vec_hsys_hnm;
			vector<TString> vec_hsys_hlo;
			vector<TString> vec_hsys_hhi;
			//
			vector<TString> vec_ohsys_nam;
			vector<double>  vec_ohsys_low;
			vector<double>  vec_ohsys_hig;
			vector<TString> vec_ohsys_hnm;
			vector<TString> vec_ohsys_hlo;
			vector<TString> vec_ohsys_hhi;
			//
			for ( unsigned int i = 0; i < sample.GetOverallSysList().size(); ++i ) {
				OverallSys osys = sample.GetOverallSysList().at(i);
				TString osys_name = osys.GetName() ;
				//	cout << "osys_name = " << osys_name << endl;
				bool is_both = false;
				TString hlo;
				TString hhi;
				for ( unsigned int j = 0; j < sample.GetHistoSysList().size(); ++j ) {
					HistoSys hsys=sample.GetHistoSysList().at(j);
					TString hsys_name = hsys.GetName()  ;
					if (osys_name == hsys_name)  {
						is_both = true;
						hlo = hsys.GetHistoNameLow();
						hhi = hsys.GetHistoNameHigh();
						break;
					}
				}
				if (is_both) {
					vec_ohsys_nam.push_back(osys_name);
					vec_ohsys_low.push_back(osys.GetLow());
					vec_ohsys_hig.push_back(osys.GetHigh());
					vec_ohsys_hnm.push_back(sample.GetHistoName());
					vec_ohsys_hlo.push_back(hlo);
					vec_ohsys_hhi.push_back(hhi);
				} else {
					//	  cout << "before vec_osys_nam.size() = " << vec_osys_nam.size() << endl;
					vec_osys_nam.push_back(osys_name);
					//	  cout << "after vec_osys_nam.size() = "  << vec_osys_nam.size() << endl;
					vec_osys_low.push_back(osys.GetLow());
					vec_osys_hig.push_back(osys.GetHigh());
				}
			}
			for ( unsigned int j = 0; j < sample.GetHistoSysList().size(); ++j ) {
				HistoSys hsys=sample.GetHistoSysList().at(j);
				TString hsys_name = hsys.GetName()  ;
				if (find(vec_ohsys_nam.begin(),vec_ohsys_nam.end(),hsys_name) == vec_ohsys_nam.end()) {
					vec_hsys_nam.push_back(hsys_name);
					vec_hsys_hnm.push_back(sample.GetHistoName());
					vec_hsys_hlo.push_back(hsys.GetHistoNameLow());
					vec_hsys_hhi.push_back(hsys.GetHistoNameHigh());
				}
			}
			//
			//      cout << "sample.GetOverallSysList().size() = " << sample.GetOverallSysList().size() << endl;
			//      cout << "vec_osys_nam.size() = " << vec_osys_nam.size() << " vec_osys_nam.front() = " << vec_osys_nam.front() << " " << " vec_osys_nam.back() = " << vec_osys_nam.back() << endl;
			//      cout << "vec_osys_nam[0] = " << vec_osys_nam[0] << endl;
			int check_vec_osys=0;
			for ( unsigned int i = 0; i < sample.GetOverallSysList().size(); ++i ) {
				TString osys_name = sample.GetOverallSysList().at(i).GetName() ;
				//	cout << "osys_name = " << osys_name << endl;
				if (find(vec_osys_nam.begin(),vec_osys_nam.end(),osys_name) != vec_osys_nam.end()) {
					//	  cout << "check_vec_osys = " << check_vec_osys << endl;
					++check_vec_osys;
					//	  cout << "check_vec_osys = " << check_vec_osys << endl;
					cout << "Channel " << cname << " Sample " << sname << " OSys    " << sample.GetOverallSysList().at(i).GetName() << " "<< endl;
				}
			}
			if (check_vec_osys != vec_osys_nam.size()) { cout << "check_vec_osys = " << check_vec_osys << " vec_osys_nam.size() = " << vec_osys_nam.size()  << endl; abort();}
			//
			int check_vec_hsys=0;
			for ( unsigned int i = 0; i < sample.GetHistoSysList().size(); ++i ) {
				TString hsys_name = sample.GetHistoSysList().at(i).GetName()  ;
				if (find(vec_hsys_nam.begin(),vec_hsys_nam.end(),hsys_name) != vec_hsys_nam.end()) {
					++check_vec_hsys;
					cout << "Channel " << cname << " Sample " << sname << " HSys    " << sample.GetHistoSysList().at(i).GetName()   << " "<< endl;
				}
			}
			if (check_vec_hsys != vec_hsys_nam.size()) { cout << "check_vec_hsys = " << check_vec_hsys << " vec_hsys_nam.size() = " << vec_hsys_nam.size()  << endl; abort();}
			//
			int check_vec_ohsys=0;
			for ( unsigned int i = 0; i < sample.GetHistoSysList().size(); ++i ) {
				TString hsys_name = sample.GetHistoSysList().at(i).GetName()  ;
				if (find(vec_hsys_nam.begin(),vec_hsys_nam.end(),hsys_name) == vec_hsys_nam.end()) {
					++check_vec_ohsys;
					cout << "Channel " << cname << " Sample " << sname << " OHSys   " << sample.GetHistoSysList().at(i).GetName()   << " "<< endl;
				}
			}
			if (check_vec_ohsys != vec_ohsys_nam.size()) { cout << "check_vec_ohsys = " << check_vec_ohsys << " vec_ohsys_nam.size() = " << vec_ohsys_nam.size()  << endl; abort();}
			if ((vec_osys_nam.size() + vec_hsys_nam.size() + 2 * vec_ohsys_nam.size() - sample.GetHistoSysList().size() - sample.GetOverallSysList().size()) != 0 ) {
				cout << "vec_osys_nam.size() = " << vec_osys_nam.size() << " "
				<< "vec_hsys_nam.size() = " << vec_hsys_nam.size() << " "
				<< "2 * vec_ohsys_nam.size() = " << 2 * vec_ohsys_nam.size() << " "
				<< "sample.GetOverallSysList().size() = " << sample.GetOverallSysList().size() << " "
				<< "sample.GetHistoSysList().size() = " << sample.GetHistoSysList().size() << " "
				<< "vec_osys_nam.size() + vec_hsys_nam.size() + 2 * vec_ohsys_nam.size() - sample.GetHistoSysList().size() - sample.GetOverallSysList().size() = "
				<< vec_osys_nam.size() + vec_hsys_nam.size() + 2 * vec_ohsys_nam.size() - sample.GetHistoSysList().size() - sample.GetOverallSysList().size()
				<< endl;
			}
			//
			nfac_nam_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_nfac_nam;
			nfac_val_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_nfac_val;
			nfac_low_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_nfac_low;
			nfac_hig_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_nfac_hig;
			//
			osys_nam_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_osys_nam;
			osys_low_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_osys_low;
			osys_hig_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_osys_hig;
			//
			hsys_nam_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_hsys_nam;
			hsys_hnm_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_hsys_hnm;
			hsys_hlo_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_hsys_hlo;
			hsys_hhi_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_hsys_hhi;
			//
			ohsys_nam_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_ohsys_nam;
			ohsys_low_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_ohsys_low;
			ohsys_hig_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_ohsys_hig;
			ohsys_hnm_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_ohsys_hnm;
			ohsys_hlo_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_ohsys_hlo;
			ohsys_hhi_per_channelsample[ Form("%s:%s",cname.Data(),sname.Data()) ] = vec_ohsys_hhi;
			//
		}
		sample_per_channel[cname] = vec_sname;
		//
		vec_map_hname_per_channel.push_back(map_hname);
		//
	}



	std::fstream latex_file;
	string output_name("PrintWS_");
	string input_file_string(input_file);
	if(input_file_string.find("vbf")!=string::npos) output_name +="VBF";
	if(input_file_string.find("boost")!=string::npos) output_name +="boost";
	if(input_file_string.find("1jet")!=string::npos) output_name +="1jet";
        output_name += ".tex";
        cout << output_name << endl;
	std:: string latex_file_name(output_name.c_str());
	latex_file.open (latex_file_name.c_str(), std::fstream::in | std::fstream::out | std::fstream::trunc);

	latex_file << "\\documentclass[11pt,a4paper]{article} \n";
	latex_file << "\\usepackage[a4paper,hmargin={0.01cm,0.01cm},vmargin={0.01cm,0.01cm}]{geometry}\n \\usepackage[applemac]{inputenc} \n \\usepackage{indentfirst}\n \\usepackage{graphicx}\n \\usepackage[english]{babel}\n \\usepackage{pdfpages}\n \\usepackage{subfigure}\n \\usepackage{mathrsfs}\n \\usepackage{lscape}\n";
	latex_file << "\\begin{document} \n";
//	latex_file << "\\begin{landscape}\n";
	latex_file << "\\begin{table}[width=0.8\\textwidth]\n";
	latex_file << "\\begin{center}\n";
	latex_file << "\\scalebox{0.48}{\n";// HACK WELP
	latex_file << "\\begin{tabular}{r|";

	typedef map<TString,TString>::iterator it_type;
	typedef map<TString,vector<TString> >::iterator it_type_vec;

	vector<int> samples_channels;

	for(int i =0;i<vec_cname.size();i++){
		TString channel = vec_cname.at(i);
		map < TString, TString > map_hname_per_channel = vec_map_hname_per_channel.at(i);
		int count_sample = 0;
		for(it_type it_sample = map_hname_per_channel.begin(); it_sample != map_hname_per_channel.end(); it_sample++) {
			// iterator->first = key
			// iterator->second = value
			if(it_sample->second.Contains("data")) continue;
			latex_file << "c";
			count_sample++;
		}
		if(i<(vec_cname.size()-1))latex_file << "|";
		samples_channels.push_back(count_sample);
	}
	latex_file << "}\n";
	latex_file << "\\hline\\hline\n";
	latex_file << " & ";
	for(int i =0;i<(samples_channels.size()-1);i++){
		string sample_name(vec_cname.at(i).Data());
		string sample_name_new = removeUnderscore(sample_name);
		latex_file << " \\multicolumn{"<<samples_channels.at(i)<<"}{c|}{"<<sample_name_new.c_str()<<"} &";
	}
	string sample_name(vec_cname.back().Data());
	string sample_name_new = removeUnderscore(sample_name);
	latex_file << " \\multicolumn{"<<samples_channels.back()<<"}{c}{"<<sample_name_new.c_str()<<"} \\\\ \n";

	latex_file << "NP ";
	for(int i =0;i<vec_cname.size();i++){
		TString channel = vec_cname.at(i);
		map < TString, TString > map_hname_per_channel = vec_map_hname_per_channel.at(i);
		for(it_type it_sample = map_hname_per_channel.begin(); it_sample != map_hname_per_channel.end(); it_sample++) {
			// iterator->first = key
			// iterator->second = value
			if(it_sample->second.Contains("data")) continue;
			string sample_name(it_sample->first.Data());
			string sample_name_new = removeUnderscore(sample_name);
			latex_file << " & "<<sample_name_new.c_str();
		}
	}
	latex_file << " \\\\ \n ";

	vector<TString> vec_NP;
	for(it_type_vec it_param = osys_nam_per_channelsample.begin(); it_param != osys_nam_per_channelsample.end(); it_param++) {
		vector<TString> vec_name = it_param->second;
		for(int i=0;i<vec_name.size();i++){
			TString name_par = vec_name.at(i);
			bool insert = true;
			for(int j=0;j<vec_NP.size();j++){
				if(name_par.EqualTo(vec_NP.at(j))) insert = false;
			}
			if(insert) vec_NP.push_back(name_par);
		}
	}
	for(it_type_vec it_param = hsys_nam_per_channelsample.begin(); it_param != hsys_nam_per_channelsample.end(); it_param++) {
		vector<TString> vec_name = it_param->second;
		for(int i=0;i<vec_name.size();i++){
			TString name_par = vec_name.at(i);
			bool insert = true;
			for(int j=0;j<vec_NP.size();j++){
				if(name_par.EqualTo(vec_NP.at(j))) insert = false;
			}
			if(insert) vec_NP.push_back(name_par);
		}
	}
	for(it_type_vec it_param = nfac_nam_per_channelsample.begin(); it_param != nfac_nam_per_channelsample.end(); it_param++) {
		vector<TString> vec_name = it_param->second;
		for(int i=0;i<vec_name.size();i++){
			TString name_par = vec_name.at(i);
			bool insert = true;
			for(int j=0;j<vec_NP.size();j++){
				if(name_par.EqualTo(vec_NP.at(j))) insert = false;
			}
			if(insert) vec_NP.push_back(name_par);
		}
	}
	for(it_type_vec it_param = ohsys_nam_per_channelsample.begin(); it_param != ohsys_nam_per_channelsample.end(); it_param++) {
		vector<TString> vec_name = it_param->second;
		for(int i=0;i<vec_name.size();i++){
			TString name_par = vec_name.at(i);
			bool insert = true;
			for(int j=0;j<vec_NP.size();j++){
				if(name_par.EqualTo(vec_NP.at(j))) insert = false;
			}
			if(insert) vec_NP.push_back(name_par);
		}
	}

	for(int i=0;i<vec_NP.size();i++){
		string sample_name(vec_NP.at(i).Data());
		sample_name = removeAlpha(sample_name);
		string sample_name_new = removeUnderscore(sample_name);
		latex_file << sample_name_new.c_str()<<" ";

		for(int j =0;j<vec_cname.size();j++){
			TString channel = vec_cname.at(j);
			map < TString, TString > map_hname_per_channel = vec_map_hname_per_channel.at(j);
			for(it_type it_sample = map_hname_per_channel.begin(); it_sample != map_hname_per_channel.end(); it_sample++) {
				// iterator->first = key
				// iterator->second = value
				if(it_sample->second.Contains("data")) continue;
				TString sample = it_sample->first;

				vector<TString> vec_name_n = nfac_nam_per_channelsample[ Form("%s:%s",channel.Data(),sample.Data()) ];
				vector<TString> vec_name_o = osys_nam_per_channelsample[ Form("%s:%s",channel.Data(),sample.Data()) ];
				vector<TString> vec_name_h = hsys_nam_per_channelsample[ Form("%s:%s",channel.Data(),sample.Data()) ];
				vector<TString> vec_name_oh = ohsys_nam_per_channelsample[ Form("%s:%s",channel.Data(),sample.Data()) ];

				string text(" ");
				for(int k=0;k<vec_name_o.size();k++){
					if(vec_name_o.at(k).EqualTo(vec_NP.at(i))) text = "Y";
				}
				for(int k=0;k<vec_name_h.size();k++){
					if(vec_name_h.at(k).EqualTo(vec_NP.at(i))) text = "S";
				}
				for(int k=0;k<vec_name_oh.size();k++){
					if(vec_name_oh.at(k).EqualTo(vec_NP.at(i))) text = "YS";
				}
				for(int k=0;k<vec_name_n.size();k++){
					if(vec_name_n.at(k).EqualTo(vec_NP.at(i))) text = "NF";
				}

				latex_file << "& " << text.c_str() << " ";

			}
		}

		latex_file << "\\\\ \n";
	}




	//	typedef std::map<std::string, std::map<std::string, std::string>>::iterator it_type;
	//	for(it_type iterator = m.begin(); iterator != m.end(); iterator++) {
	//		// iterator->first = key
	//		// iterator->second = value
	//		// Repeat if you also want to iterate through the second map.
	//	}
	//
	//	vector<TString> vec_cname;
	//	//
	//	map<TString , vector<TString> > sample_per_channel;
	//	vector < map < TString, TString > > vec_map_hname_per_channel;
	//	//
	//	map<TString , vector<TString> > nfac_nam_per_channelsample;
	//	map<TString , vector<double> >  nfac_val_per_channelsample;
	//	map<TString , vector<double> >  nfac_low_per_channelsample;
	//	map<TString , vector<double> >  nfac_hig_per_channelsample;
	//	//
	//	map<TString , vector<TString> > osys_nam_per_channelsample;
	//	map<TString , vector<double> >  osys_low_per_channelsample;
	//	map<TString , vector<double> >  osys_hig_per_channelsample;
	//	//
	//	map<TString , vector<TString> > hsys_nam_per_channelsample;
	//	map<TString , vector<TString> > hsys_hnm_per_channelsample;
	//	map<TString , vector<TString> > hsys_hlo_per_channelsample;
	//	map<TString , vector<TString> > hsys_hhi_per_channelsample;
	//	//
	//	map<TString , vector<TString> > ohsys_nam_per_channelsample;
	//	map<TString , vector<double> >  ohsys_low_per_channelsample;
	//	map<TString , vector<double> >  ohsys_hig_per_channelsample;
	//	map<TString , vector<TString> > ohsys_hnm_per_channelsample;
	//	map<TString , vector<TString> > ohsys_hlo_per_channelsample;
	//	map<TString , vector<TString> > ohsys_hhi_per_channelsample;

	latex_file << "\\hline\\hline\n";
	latex_file << "\\end{tabular}} \n";
	latex_file << "\\end{center} \n";
	latex_file << "\\end{table}\n";
//	latex_file << "\\end{landscape}\n";
	latex_file << "\\end{document} \n";
	latex_file.close();

}
