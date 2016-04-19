#include "th1dmorph.C"
//#include "th1fmorph.C"

TH1D* GetInterHist(TH1D*h1,TH1D*h2,std::string histname,double interfluc){
	int Nbin=h1->GetNbinsX();
	if(h2->GetNbinsX()!=Nbin) {
		std::cout << "two histograms have different binnning" << std::endl;
		return -1;
	}
	TH1D* hist= new TH1D(*(TH1D*)h1->Clone());
	hist->SetName(histname.c_str());
	hist->SetTitle(histname.c_str());
	
	for(int ibin=0;ibin<=Nbin;ibin++){
		double a1=h1->GetBinContent(ibin);
		double a2=h2->GetBinContent(ibin);
		//    std::cout << a1 << " " << a2 << " " << a1+(a2-a1)*interfluc << std::endl;
		hist->SetBinContent(ibin,a1+(a2-a1)*interfluc);
	}
	return hist;
}


void histinter(std::string inputname="mass_plots_rebinned_2012_MVAlike.root"){
	const int npoint=11;
	int masspoint[npoint]={100,105,110,115,120,125,130,135,140,145,150};
	double step=2.5;
	//  const int npoint=2;
	//  int masspoint[npoint]={100,105};
	//  double step=1;
	std::vector<std::string> HistPrefix;
	std::vector<std::string> HistPrefix_sig;
	std::vector<std::string> HistPrefix_syst;
	
	
	std::string HistSufix="All";
	int norm=1;
	
	HistPrefix.push_back("massTrkVBF_");
	HistPrefix.push_back("massTrkVBF_tight_highdr_");
	HistPrefix.push_back("massTrkVBF_loose_highdr_");
	HistPrefix.push_back("massTrkBoosted_");
	HistPrefix.push_back("massTrkBoosted_loose_");
	
	HistPrefix_sig.push_back("ggH");
	HistPrefix_sig.push_back("VBFH");
	HistPrefix_sig.push_back("WH");
	HistPrefix_sig.push_back("ZH");
	
	HistPrefix_syst.push_back("");
	//2012
	HistPrefix_syst.push_back("_SFUp");
	HistPrefix_syst.push_back("_SFDown");
	HistPrefix_syst.push_back("_TrigSystUp");
	HistPrefix_syst.push_back("_TrigSystDown");
	HistPrefix_syst.push_back("_EtaModellingUp");
	HistPrefix_syst.push_back("_EtaModellingDown");
	HistPrefix_syst.push_back("_FlavorResponseUp");
	HistPrefix_syst.push_back("_FlavorResponseDown");
	HistPrefix_syst.push_back("_Detector1Up");
	HistPrefix_syst.push_back("_Detector1Down");
	HistPrefix_syst.push_back("_Modelling1Up");
	HistPrefix_syst.push_back("_Modelling1Down");
//	HistPrefix_syst.push_back("_TESUpTrue");
//    HistPrefix_syst.push_back("_TESDownTrue");
	HistPrefix_syst.push_back("_TESUpTrueClosure");
	HistPrefix_syst.push_back("_TESDownTrueClosure");
	HistPrefix_syst.push_back("_TESUpTrueModeling");
	HistPrefix_syst.push_back("_TESDownTrueModeling");
	HistPrefix_syst.push_back("_TESUpTrueInSitu");
	HistPrefix_syst.push_back("_TESDownTrueInSitu");
	HistPrefix_syst.push_back("_TESUpTrueSingleparticle");
	HistPrefix_syst.push_back("_TESDownTrueSingleparticle");
	//2011
//	HistPrefix_syst.push_back("_TESUp");
//	HistPrefix_syst.push_back("_TESDown");
	
	
	HistSufix="";
	norm=0;
	
	TFile * file = new TFile(inputname.c_str(),"update");
	for(int imass=0;imass<npoint-1;imass++){
		for(unsigned int ihist=0;ihist<HistPrefix.size();ihist++){
			for(unsigned int ihist_sig=0;ihist_sig<HistPrefix_sig.size();ihist_sig++){
				for(unsigned int ihist_syst=0;ihist_syst<HistPrefix_syst.size();ihist_syst++){
					std::stringstream ss;  ss.str()="";
					ss << HistPrefix[ihist] << HistPrefix_sig[ihist_sig] << masspoint[imass]<< HistPrefix_syst[ihist_syst];
					std::stringstream ss2;  ss2.str()="";
					ss2 << HistPrefix[ihist] << HistPrefix_sig[ihist_sig] << masspoint[imass+1]<< HistPrefix_syst[ihist_syst];
					
					TH1D* h_ss=0;
					TH1D* h_ss_tmp =0;
					h_ss_tmp = (TH1D*)file->Get(ss.str().c_str());
					if(h_ss_tmp) h_ss = (TH1D*)h_ss_tmp->Clone();
					TH1D* h_ss2=0;
					TH1D* h_ss2_tmp=0;
					h_ss2_tmp = (TH1D*)file->Get(ss2.str().c_str());
					if(h_ss2_tmp) h_ss2 = (TH1D*)h_ss2_tmp->Clone();
					if(!h_ss || !h_ss2) {std::cout<<"histo not found: "<<ss.str().c_str() << " or "<<ss2.str().c_str()<<endl; continue;}
					double ii=masspoint[imass]+step;
					while(ii<masspoint[imass+1]){
						std::cout << "making mass=" << ii << " histogram..." << std::endl;
						double ff=(double)(ii-masspoint[imass])/(double)(masspoint[imass+1]-masspoint[imass]);
						std::stringstream ssint; ssint.str()="";
						ssint << HistPrefix[ihist] << HistPrefix_sig[ihist_sig] << ii << HistPrefix_syst[ihist_syst];
						
						if(0){
							GetInterHist(h_ss,h_ss2,ssint.str(),ff)->Write();
						}else{
							th1dmorph(ssint.str().c_str(),ssint.str().c_str(),h_ss,h_ss2,masspoint[imass],masspoint[imass+1],ii,norm,0)->Write();
							//	  std::cout << "th1dmorph(" << ssint.str().c_str() <<","<<ssint.str().c_str()<<",h_ss,h_ss2"<<","<<masspoint[imass]<<","<<masspoint[imass+1]<<","<<ii<<","<<norm<<","<<0<<")"<<std::endl;
							//	  std::cout << "integral : " << h_ss->Integral() << " " << " " << h_ss2->Integral() << std::endl;
							if(1)std::cout << h_ss->Integral() << " " << th1dmorph(ssint.str().c_str(),ssint.str().c_str(),h_ss,h_ss2,masspoint[imass],masspoint[imass+1],ii,norm,0)->Integral() << " " << h_ss2->Integral() << std::endl;
						}
						ii+=step;
					}
				}
			}
		}
	}
	
}

