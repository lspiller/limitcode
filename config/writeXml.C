//
//  writeXml.C
//  
//
//  Created by Daniele Zanzi on 06/07/2012.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
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
#include "TNtuple.h"
#include "TMatrixD.h"
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include "TEventList.h"
#include "TLorentzVector.h"
#include <vector>
#ifdef __MAKECINT__
#pragma link C++ class vector<TLorentzVector>;
#endif
#include "TVector2.h"
#include "TVector3.h"
#include "TLatex.h"
#include "TLegend.h"
#include <TStyle.h>
#include <stdlib.h>
#include "TGraph.h"
#include <fstream>
#include "TH1F.h"
#include "TF1.h"
#include "TEventList.h"
#include "TObjArray.h"
#include "TLine.h"
#include <iomanip>
#include "TSystem.h"

int main(int argc, char **argv){
	
	//gROOT->ProcessLine(".L ggFReweighting.cxx++");
	
	gROOT->ProcessLine("#include <vector>");
	gSystem->Load( "libCintex.so" );
 	gROOT->ProcessLine("Cintex::Cintex::Enable();");
  	//SetAtlasStyle();
	
	int signal_flag = 0;
	if(argc>1) signal_flag = atoi(argv[1]);
    
    std::vector<std::string>mass;
    mass.push_back("100");
	mass.push_back("102.5");
    mass.push_back("105");
	mass.push_back("107.5");
    mass.push_back("110");
	mass.push_back("112.5");
    mass.push_back("115");
	mass.push_back("117.5");
    mass.push_back("120");
	mass.push_back("122.5");
    mass.push_back("125");
	mass.push_back("127.5");
    mass.push_back("130");
	mass.push_back("132.5");
    mass.push_back("135");
	mass.push_back("137.5");
    mass.push_back("140");
	mass.push_back("142.5");
    mass.push_back("145");
	mass.push_back("147.5");
    mass.push_back("150");
	
	float LumiRelErr = 0.018;
	
	std::string input_flag("_2012.xml</Input>\n");
	std::string file_flag("");
	if(signal_flag==1) {input_flag = "_TESClosureUp_2012.xml</Input>\n"; file_flag = "_TESClosureUp_";}
	if(signal_flag==2) {input_flag = "_TESClosureDown_2012.xml</Input>\n"; file_flag = "_TESClosureDown_";}
	
    for(int m=0;m<mass.size();m++){
		
        //++++++++++++++++++++++++++++++++++++++++
        // CONFIG XML
        //++++++++++++++++++++++++++++++++++++++++
		
		std::fstream latex_file_VBF_MVAlike_xml;
        std::string file_name_VBF_MVAlike_xml("hh_all_vbf_MVAlike_");
        file_name_VBF_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_VBF_MVAlike_xml.open(file_name_VBF_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_VBF_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_VBF_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_vbf_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_VBF_MVAlike_xml << "\t\t<Input>./config/hh_vbf_lowdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_VBF_MVAlike_xml << "\t\t<Input>./config/hh_vbf_highdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_VBF_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_lowdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_VBF_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_highdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_VBF_MVAlike_xml << "\t\t<Input>./config/hh_vbf_loose_highdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_VBF_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\"0.039\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_VBF_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_VBF_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_VBF_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_VBF_MVAlike_xml << "\t</Combination>\n";
        latex_file_VBF_MVAlike_xml.close();
		
		std::fstream latex_file_VBF_2011_MVAlike_xml;
        std::string file_name_VBF_2011_MVAlike_xml("hh_all_VBF_2011_MVAlike_");
        file_name_VBF_2011_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_VBF_2011_MVAlike_xml.open(file_name_VBF_2011_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_VBF_2011_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_VBF_2011_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_VBF_2011_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_VBF_2011_MVAlike_xml << "\t\t<Input>./config/hh_vbf_lowdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_VBF_2011_MVAlike_xml << "\t\t<Input>./config/hh_vbf_highdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
        latex_file_VBF_2011_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\"0.039\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_VBF_2011_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_VBF_2011_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_VBF_2011_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_VBF_2011_MVAlike_xml << "\t</Combination>\n";
        latex_file_VBF_2011_MVAlike_xml.close();
		
		std::fstream latex_file_VBF_lowdr_2011_MVAlike_xml;
        std::string file_name_VBF_lowdr_2011_MVAlike_xml("hh_all_VBF_lowdr_2011_MVAlike_");
        file_name_VBF_lowdr_2011_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_VBF_lowdr_2011_MVAlike_xml.open(file_name_VBF_lowdr_2011_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_VBF_lowdr_2011_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_VBF_lowdr_2011_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_VBF_lowdr_2011_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_VBF_lowdr_2011_MVAlike_xml << "\t\t<Input>./config/hh_vbf_lowdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
        latex_file_VBF_lowdr_2011_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\"0.039\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_VBF_lowdr_2011_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_VBF_lowdr_2011_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_VBF_lowdr_2011_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_VBF_lowdr_2011_MVAlike_xml << "\t</Combination>\n";
        latex_file_VBF_lowdr_2011_MVAlike_xml.close();
		
		std::fstream latex_file_VBF_highdr_tight_2011_MVAlike_xml;
        std::string file_name_VBF_highdr_tight_2011_MVAlike_xml("hh_all_VBF_highdr_tight_2011_MVAlike_");
        file_name_VBF_highdr_tight_2011_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_VBF_highdr_tight_2011_MVAlike_xml.open(file_name_VBF_highdr_tight_2011_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_VBF_highdr_tight_2011_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_VBF_highdr_tight_2011_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_VBF_highdr_tight_2011_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_VBF_highdr_tight_2011_MVAlike_xml << "\t\t<Input>./config/hh_vbf_highdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
        latex_file_VBF_highdr_tight_2011_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\"0.039\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_VBF_highdr_tight_2011_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_VBF_highdr_tight_2011_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_VBF_highdr_tight_2011_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_VBF_highdr_tight_2011_MVAlike_xml << "\t</Combination>\n";
        latex_file_VBF_highdr_tight_2011_MVAlike_xml.close();
		
		
		std::fstream latex_file_VBF_2012_MVAlike_xml;
        std::string file_name_VBF_2012_MVAlike_xml("hh_all_VBF_2012_MVAlike_");
        file_name_VBF_2012_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_VBF_2012_MVAlike_xml.open(file_name_VBF_2012_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_VBF_2012_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_VBF_2012_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_VBF_2012_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_VBF_2012_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_lowdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_VBF_2012_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_highdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_VBF_2012_MVAlike_xml << "\t\t<Input>./config/hh_vbf_loose_highdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_VBF_2012_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\"0.039\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_VBF_2012_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_VBF_2012_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_VBF_2012_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_VBF_2012_MVAlike_xml << "\t</Combination>\n";
        latex_file_VBF_2012_MVAlike_xml.close();
		
		std::fstream latex_file_VBF_lowdr_2012_MVAlike_xml;
        std::string file_name_VBF_lowdr_2012_MVAlike_xml("hh_all_VBF_lowdr_2012_MVAlike_");
        file_name_VBF_lowdr_2012_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_VBF_lowdr_2012_MVAlike_xml.open(file_name_VBF_lowdr_2012_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_VBF_lowdr_2012_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_VBF_lowdr_2012_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_VBF_lowdr_2012_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_VBF_lowdr_2012_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_lowdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_VBF_lowdr_2012_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\"0.039\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_VBF_lowdr_2012_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_VBF_lowdr_2012_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_VBF_lowdr_2012_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_VBF_lowdr_2012_MVAlike_xml << "\t</Combination>\n";
        latex_file_VBF_lowdr_2012_MVAlike_xml.close();
		
		std::fstream latex_file_VBF_highdr_tight_2012_MVAlike_xml;
        std::string file_name_VBF_highdr_tight_2012_MVAlike_xml("hh_all_VBF_highdr_tight_2012_MVAlike_");
        file_name_VBF_highdr_tight_2012_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_VBF_highdr_tight_2012_MVAlike_xml.open(file_name_VBF_highdr_tight_2012_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_VBF_highdr_tight_2012_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_VBF_highdr_tight_2012_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_VBF_highdr_tight_2012_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_VBF_highdr_tight_2012_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_highdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_VBF_highdr_tight_2012_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\"0.039\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_VBF_highdr_tight_2012_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_VBF_highdr_tight_2012_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_VBF_highdr_tight_2012_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_VBF_highdr_tight_2012_MVAlike_xml << "\t</Combination>\n";
        latex_file_VBF_highdr_tight_2012_MVAlike_xml.close();
		
		std::fstream latex_file_VBF_highdr_loose_2012_MVAlike_xml;
        std::string file_name_VBF_highdr_loose_2012_MVAlike_xml("hh_all_VBF_highdr_loose_2012_MVAlike_");
        file_name_VBF_highdr_loose_2012_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_VBF_highdr_loose_2012_MVAlike_xml.open(file_name_VBF_highdr_loose_2012_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_VBF_highdr_loose_2012_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_VBF_highdr_loose_2012_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_VBF_highdr_loose_2012_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_VBF_highdr_loose_2012_MVAlike_xml << "\t\t<Input>./config/hh_vbf_loose_highdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_VBF_highdr_loose_2012_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\"0.039\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_VBF_highdr_loose_2012_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_VBF_highdr_loose_2012_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_VBF_highdr_loose_2012_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_VBF_highdr_loose_2012_MVAlike_xml << "\t</Combination>\n";
        latex_file_VBF_highdr_loose_2012_MVAlike_xml.close();
		
		std::fstream latex_file_boost_MVAlike_xml;
        std::string file_name_boost_MVAlike_xml("hh_all_boost_MVAlike_");
        file_name_boost_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_boost_MVAlike_xml.open(file_name_boost_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_boost_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_boost_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_boost_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_boost_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_boost_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_boost_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_boost_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_boost_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_boost_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_boost_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_boost_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_boost_MVAlike_xml << "\t</Combination>\n";
        latex_file_boost_MVAlike_xml.close();
		
		std::fstream latex_file_boost_2011_MVAlike_xml;
        std::string file_name_boost_2011_MVAlike_xml("hh_all_boost_2011_MVAlike_");
        file_name_boost_2011_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_boost_2011_MVAlike_xml.open(file_name_boost_2011_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_boost_2011_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_boost_2011_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_boost_2011_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_boost_2011_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_boost_2011_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<"_2011.xml</Input>\n";
        latex_file_boost_2011_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_boost_2011_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_boost_2011_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_boost_2011_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_boost_2011_MVAlike_xml << "\t</Combination>\n";
        latex_file_boost_2011_MVAlike_xml.close();
		
		
		std::fstream latex_file_boost_tight_2011_MVAlike_xml;
        std::string file_name_boost_tight_2011_MVAlike_xml("hh_all_boost_tight_2011_MVAlike_");
        file_name_boost_tight_2011_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_boost_tight_2011_MVAlike_xml.open(file_name_boost_tight_2011_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_boost_tight_2011_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_boost_tight_2011_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_boost_tight_2011_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_boost_tight_2011_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<"_2011.xml</Input>\n";
        latex_file_boost_tight_2011_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_boost_tight_2011_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_boost_tight_2011_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_boost_tight_2011_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_boost_tight_2011_MVAlike_xml << "\t</Combination>\n";
        latex_file_boost_tight_2011_MVAlike_xml.close();
		
		std::fstream latex_file_boost_loose_2011_MVAlike_xml;
        std::string file_name_boost_loose_2011_MVAlike_xml("hh_all_boost_loose_2011_MVAlike_");
        file_name_boost_loose_2011_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_boost_loose_2011_MVAlike_xml.open(file_name_boost_loose_2011_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_boost_loose_2011_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_boost_loose_2011_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_boost_loose_2011_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_boost_loose_2011_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<"_2011.xml</Input>\n";
        latex_file_boost_loose_2011_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_boost_loose_2011_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_boost_loose_2011_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_boost_loose_2011_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_boost_loose_2011_MVAlike_xml << "\t</Combination>\n";
        latex_file_boost_loose_2011_MVAlike_xml.close();
		
		std::fstream latex_file_boost_2012_MVAlike_xml;
        std::string file_name_boost_2012_MVAlike_xml("hh_all_boost_2012_MVAlike_");
        file_name_boost_2012_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_boost_2012_MVAlike_xml.open(file_name_boost_2012_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_boost_2012_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_boost_2012_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_boost_2012_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_boost_2012_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_boost_2012_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_boost_2012_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_boost_2012_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_boost_2012_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_boost_2012_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_boost_2012_MVAlike_xml << "\t</Combination>\n";
        latex_file_boost_2012_MVAlike_xml.close();
		
		std::fstream latex_file_boost_tight_2012_MVAlike_xml;
        std::string file_name_boost_tight_2012_MVAlike_xml("hh_all_boost_tight_2012_MVAlike_");
        file_name_boost_tight_2012_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_boost_tight_2012_MVAlike_xml.open(file_name_boost_tight_2012_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_boost_tight_2012_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_boost_tight_2012_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_boost_tight_2012_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_boost_tight_2012_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_boost_tight_2012_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_boost_tight_2012_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_boost_tight_2012_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_boost_tight_2012_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_boost_tight_2012_MVAlike_xml << "\t</Combination>\n";
        latex_file_boost_tight_2012_MVAlike_xml.close();
		
		std::fstream latex_file_boost_loose_2012_MVAlike_xml;
        std::string file_name_boost_loose_2012_MVAlike_xml("hh_all_boost_loose_2012_MVAlike_");
        file_name_boost_loose_2012_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_boost_loose_2012_MVAlike_xml.open(file_name_boost_loose_2012_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_boost_loose_2012_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_boost_loose_2012_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_boost_loose_2012_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_boost_loose_2012_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_boost_loose_2012_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_boost_loose_2012_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_boost_loose_2012_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_boost_loose_2012_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_boost_loose_2012_MVAlike_xml << "\t</Combination>\n";
        latex_file_boost_loose_2012_MVAlike_xml.close();
		
		std::fstream latex_file_comb_MVAlike_xml;
        std::string file_name_comb_MVAlike_xml("hh_all_comb_MVAlike_");
        file_name_comb_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_comb_MVAlike_xml.open(file_name_comb_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_comb_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_comb_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_comb_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_comb_MVAlike_xml << "\t\t<Input>./config/hh_vbf_lowdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_comb_MVAlike_xml << "\t\t<Input>./config/hh_vbf_highdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_comb_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_comb_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_comb_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_lowdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_comb_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_highdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_comb_MVAlike_xml << "\t\t<Input>./config/hh_vbf_loose_highdr_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_comb_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<"_2012.xml</Input>\n";
		latex_file_comb_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<"_2012.xml</Input>\n";
        latex_file_comb_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_comb_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_comb_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_comb_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_comb_MVAlike_xml << "\t</Combination>\n";
        latex_file_comb_MVAlike_xml.close();
		
		std::fstream latex_file_comb_2011_MVAlike_xml;
        std::string file_name_comb_2011_MVAlike_xml("hh_all_comb_2011_MVAlike_");
        file_name_comb_2011_MVAlike_xml+= mass.at(m) + "_2011_2012.xml";
        latex_file_comb_2011_MVAlike_xml.open(file_name_comb_2011_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_comb_2011_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_comb_2011_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_comb_2011_MVAlike_"<<mass.at(m)<<"_2011_2012\">\n";
		latex_file_comb_2011_MVAlike_xml << "\t\t<Input>./config/hh_vbf_lowdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_comb_2011_MVAlike_xml << "\t\t<Input>./config/hh_vbf_highdr_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_comb_2011_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<"_2011.xml</Input>\n";
		latex_file_comb_2011_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<"_2011.xml</Input>\n";
        latex_file_comb_2011_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_comb_2011_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_comb_2011_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_comb_2011_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_comb_2011_MVAlike_xml << "\t</Combination>\n";
        latex_file_comb_2011_MVAlike_xml.close();
		
		std::fstream latex_file_comb_2012_MVAlike_xml;
        std::string file_name_comb_2012_MVAlike_xml("hh_all_comb_2012_MVAlike_");
        file_name_comb_2012_MVAlike_xml+= file_flag + mass.at(m) + "_2011_2012.xml";
        latex_file_comb_2012_MVAlike_xml.open(file_name_comb_2012_MVAlike_xml.c_str(), fstream::in|fstream::out|fstream::trunc);
        latex_file_comb_2012_MVAlike_xml << "<!DOCTYPE Combination  SYSTEM 'HistFactorySchema.dtd'>\n";
        latex_file_comb_2012_MVAlike_xml << "\t<Combination OutputFilePrefix=\"./results/hh_all_comb_2012_MVAlike_"<< file_flag <<mass.at(m)<<"_2011_2012\">\n";
        latex_file_comb_2012_MVAlike_xml << "\t\t<Input>./config/hh_boost_tight_"<<mass.at(m)<<input_flag;
		latex_file_comb_2012_MVAlike_xml << "\t\t<Input>./config/hh_boost_loose_"<<mass.at(m)<<input_flag;
		latex_file_comb_2012_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_lowdr_"<<mass.at(m)<<input_flag;
		latex_file_comb_2012_MVAlike_xml << "\t\t<Input>./config/hh_vbf_tight_highdr_"<<mass.at(m)<<input_flag;
		latex_file_comb_2012_MVAlike_xml << "\t\t<Input>./config/hh_vbf_loose_highdr_"<<mass.at(m)<<input_flag;
        latex_file_comb_2012_MVAlike_xml << "\t\t<Measurement Name=\"AllSYS\" Lumi=\"1.\" LumiRelErr=\""<<LumiRelErr<<"\" Mode=\"comb\"   ExportOnly=\"True\" >\n";
        latex_file_comb_2012_MVAlike_xml << "\t\t\t<POI>SigXsecOverSM</POI>\n";
        latex_file_comb_2012_MVAlike_xml << "\t\t<ParamSetting Const=\"True\">Lumi mu_XS8_ggH mu_XS8_VBF mu_XS8_WH mu_XS8_ZH mu_XS7_ggH mu_XS7_VBF mu_XS7_WH mu_XS7_ZH mu_BR_tautau</ParamSetting>\n";
        latex_file_comb_2012_MVAlike_xml << "\t\t</Measurement>\n";
        latex_file_comb_2012_MVAlike_xml << "\t</Combination>\n";
        latex_file_comb_2012_MVAlike_xml.close();
		

    }
    
    return 0;

}