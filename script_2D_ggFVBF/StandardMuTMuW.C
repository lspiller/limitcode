
// Sven Kreiss, Kyle Cranmer
// July 18, 2012

#include "TFile.h"

#include "RooWorkspace.h"
#include "RooStats/ModelConfig.h"
#include "RooNLLVar.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooNumIntConfig.h"

#include "RooMinimizer.h"
#include "Math/MinimizerOptions.h"
#include "RooStats/RooStatsUtils.h"

#include <iostream>
#include <sstream>
#include <iomanip>

#include <TMath.h>


using namespace std;
using namespace RooFit;
using namespace RooStats;




int minimize_fancy(RooNLLVar* nll)
{
	bool const_test = 0;
	
	vector<string> const_vars;
	//  const_vars.push_back("alpha_ATLAS_JES_NoWC_llqq");
	//   const_vars.push_back("alpha_ATLAS_ZBB_PTW_NoWC_llqq");
	//   const_vars.push_back("alpha_ATLAS_ZCR_llqqNoWC_llqq");
	
	int nrConst = const_vars.size();
	
	
	
	int printLevel = ROOT::Math::MinimizerOptions::DefaultPrintLevel();
	RooFit::MsgLevel msglevel = RooMsgService::instance().globalKillBelow();
	if (printLevel < 0) RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
	
	int strat = ROOT::Math::MinimizerOptions::DefaultStrategy();
	RooMinimizer minim(*nll);
	minim.setStrategy(strat);
	minim.setPrintLevel(printLevel);
	
	
	int status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
	
	
	if (status != 0 && status != 1 && strat < 2)
	{
		strat++;
		cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
		minim.setStrategy(strat);
		status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
	}
	
	if (status != 0 && status != 1 && strat < 2)
	{
		strat++;
		cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
		minim.setStrategy(strat);
		status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
	}
	
	if (status != 0 && status != 1)
	{
		cout << "Fit failed with status " << status << endl;
		string minType = ROOT::Math::MinimizerOptions::DefaultMinimizerType();
		string newMinType;
		if (minType == "Minuit2") newMinType = "Minuit";
		else newMinType = "Minuit2";
		
		cout << "Switching minuit type from " << minType << " to " << newMinType << endl;
		
		ROOT::Math::MinimizerOptions::SetDefaultMinimizer(newMinType.c_str());
		strat = 1; //ROOT::Math::MinimizerOptions::DefaultStrategy();
		minim.setStrategy(strat);
		
		status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
		
		
		if (status != 0 && status != 1 && strat < 2)
		{
			strat++;
			cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
			minim.setStrategy(strat);
			status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
		}
		
		if (status != 0 && status != 1 && strat < 2)
		{
			strat++;
			cout << "Fit failed with status " << status << ". Retrying with strategy " << strat << endl;
			minim.setStrategy(strat);
			status = minim.minimize(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
		}
		strat=2;
		ROOT::Math::MinimizerOptions::SetDefaultMinimizer(minType.c_str());
	}
	
	
	if (status == 0)
		cout<<"Successful fit! "<<endl;
	cout<<"Fit exists with status:"<<status<<endl;
	
	//   if (status != 0 && status != 1)
	//   {
	//     cout << "Fit failed for mu = " << mu->getVal() << " with status " << status << ". Retrying with pdf->fitTo()" << endl;
	//     combPdf->fitTo(*combData,Hesse(false),Minos(false),PrintLevel(0),Extended(), Constrain(nuiSet_tmp));
	//   }
	if (printLevel < 0) RooMsgService::instance().setGlobalKillBelow(msglevel);
	
	
	
	return status;
}


double minimize(RooAbsReal* nll) {
	
	RooMinimizer minim(*nll);
	minim.setStrategy(0);
	minim.setPrintLevel(-1);
	//minim.setEps(0.001);
	// this cayses a memory leak
	minim.optimizeConst(2);
	int status=12345;
	for (int tries = 0, maxtries = 4; tries <= maxtries; ++tries) {
		//	 status = minim.minimize(fMinimizer, ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
		status = minim.minimize("Minuit2", "MIGRAD");
		if (status == 0) {
			break;
		} else {
			if (tries > 1) {
				printf("    ----> Doing a re-scan first\n");
				minim.minimize("Minuit2", "Scan");
			}
			if (tries > 2) {
				printf("    ----> trying with strategy = 1\n");
				minim.setStrategy(1);
			}
			if (tries > 3) {
				printf("    ----> trying with strategy = 2\n");
				minim.setStrategy(2);
			}
			
		}
	}
	if(status<0){
		cout<<"FAILED!"<<endl;
	}
	return nll->getVal();
}




/*
 muT : ggF
 muW : VBF
 
 Runs a nStep fits between muWmin and muWmax for fixed muT
 muTin = 90 = -10
 muTIn = 1090 = 0.90
 muTIn = 1100 = 1.000
 muTIn = 1200 = 2.000
 
 muWMin = -35 = -0.035
 muWMax = 100
 */
void StandardMuTMuW(
					string inFileName,
					string wsName = "combined",
					string mcName = "ModelConfig",
					string dataName = "obsData",
					double muTIn = 1100,
					double muWMin = -3.5,
					double muWMax = 3.5,
					int nSteps = 20
					) {
	double muT = (muTIn-1000.)/100.0;
	
	//check inputs
	TFile f(inFileName.c_str());
	RooWorkspace* w = (RooWorkspace*)f.Get(wsName.c_str());
	if (!w)
	{
		cout << "ERROR::Workspace: " << wsName << " doesn't exist!" << endl;
		return;
	}
	ModelConfig* mc = (ModelConfig*)w->obj(mcName.c_str());
	if (!mc)
	{
		cout << "ERROR::ModelConfig: " << mcName << " doesn't exist!" << endl;
		return;
	}
	RooDataSet* origData = (RooDataSet*)w->data(dataName.c_str());
	if (!origData)
	{
		cout << "ERROR::Dataset: " << dataName << " doesn't exist!" << endl;
		return;
	}
	
	
	
	RooDataSet* data = origData;
	//   addPhantomData( inFileName, w, mc, data );
	
	//RooAbsReal::defaultIntegratorConfig()->method1D().setLabel("RooAdaptiveGaussKronrodIntegrator1D") ;
	
	ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit");
	ROOT::Math::MinimizerOptions::SetDefaultStrategy(1);
	//ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(1);
	ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(-1);
	//ROOT::Math::MinimizerOptions::SetDefaultTolerance(0.0001);
	
	RooArgSet* params = mc->GetPdf()->getParameters(*data);
	RemoveConstantParameters(params);
	RooAbsReal* nll =   mc->GetPdf()->createNLL(*data, CloneData(kFALSE), Constrain(*params));
	nll->setEvalErrorLoggingMode(RooAbsReal::CountErrors);
	nll->enableOffsetting(true);
	RooRealVar* firstPOI = (RooRealVar*)mc->GetParametersOfInterest()->first();
	
	
	// w->loadSnapshot("ucmles");
	// mc->GetParametersOfInterest()->Print("V");
	// mc->GetNuisanceParameters()->Print("V");
	// cout << "ucmles (mu="<<firstPOI->getVal()<<"): NLL = "<<setprecision(6)<<setiosflags(ios::fixed)<<nll->getVal()<<endl;
	// cout << endl << endl;
	if(! w->loadSnapshot("globalFitGlobs"))
		cout<<"Could not load globalFitGlobs"<<endl;
	if(!w->loadSnapshot("globalFitNuis"))
		cout<<"Could not load globalFitNuis"<<endl;
	
	cout << "GlobalFit (mu="<<firstPOI->getVal()<<"): NLL = "<<setprecision(6)<<setiosflags(ios::fixed)<<nll->getVal()<<endl;
	cout << endl << endl;
	
	mc->GetParametersOfInterest()->Print("V");
	mc->GetNuisanceParameters()->Print("V");
	
	// set global mu fixed to one:
	firstPOI->setConstant();
	firstPOI->setVal( 1.0 );
	
	// Find uncertainty due to tautau branching ratio and set it constant
	// since the axes will be labeled mu * B / B_SM
	RooRealVar* tautaubr = w->var( "alpha_ATLAS_BR_tautau" );
	tautaubr->setConstant();
	tautaubr->setVal(1);
	
	// check variables and change ranges
	RooRealVar* mu_XS_ggF = w->var( "mu_XS8_ggH" );
	RooRealVar* mu_XS_VBF = w->var( "mu_XS8_VBF" );
	RooRealVar* mu_XS_ttH = w->var( "mu_XS8_ttH" );
	RooRealVar* mu_XS_WH = w->var( "mu_XS8_WH" );
	RooRealVar* mu_XS_ZH = w->var( "mu_XS8_ZH" );
	
	RooRealVar* mu_XS7_ggF = w->var( "mu_XS7_ggH" );
	RooRealVar* mu_XS7_VBF = w->var( "mu_XS7_VBF" );
	RooRealVar* mu_XS7_ttH = w->var( "mu_XS7_ttH" );
	RooRealVar* mu_XS7_WH = w->var( "mu_XS7_WH" );
	RooRealVar* mu_XS7_ZH = w->var( "mu_XS7_ZH" );
	
	if( !mu_XS_ggF ) cout << "no mu_XS_ggF in workspace" << endl;
	if( !mu_XS_ttH ) cout << "no mu_XS_ttH in workspace" << endl;
	if( !mu_XS_VBF ) cout << "no mu_XS_VBF in workspace" << endl;
	if( !mu_XS_WH ) cout << "no mu_XS_WH in workspace" << endl;
	if( !mu_XS_ZH ) cout << "no mu_XS_ZH in workspace" << endl;
	
	mu_XS_ggF->setRange( -50,50 );
	mu_XS_VBF->setRange( -50,50 );
	if( mu_XS_WH ) mu_XS_WH->setRange( -50,50 );
	mu_XS_ZH->setRange( -50,50 );
	if( mu_XS_ttH ) mu_XS_ttH->setRange( -50,50 );
	mu_XS7_ggF->setRange( -50,50 );
	mu_XS7_VBF->setRange( -50,50 );
	if( mu_XS7_WH ) mu_XS7_WH->setRange( -50,50 );
	mu_XS7_ZH->setRange( -50,50 );
	if( mu_XS7_ttH ) mu_XS7_ttH->setRange( -50,50 );
	
	// muT is fixed in this run
	cout << endl;
	cout << "muT = "<<muT<<endl;
	mu_XS_ggF->setVal( muT );
	mu_XS7_ggF->setVal( muT );
	if( mu_XS_ttH ) mu_XS_ttH->setVal( muT );
	if( mu_XS7_ttH ) mu_XS7_ttH->setVal( muT );
	cout << endl;
	
	
	RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL);
	int status=-1234;
	for( int i=nSteps; i >= 0; i-- ) {
		double muW = muWMin + i*(muWMax-muWMin)/nSteps;
		mu_XS_VBF->setVal( muW );
		mu_XS7_VBF->setVal( muW );
		if( mu_XS_WH ) mu_XS_WH->setVal( muW );
		if( mu_XS7_WH ) mu_XS7_WH->setVal( muW );
		mu_XS_ZH->setVal( muW );
		mu_XS7_ZH->setVal( muW );
		status = minimize_fancy( (RooNLLVar*) nll );
		if(status>=0)
			cout << "muW = "<<muW<<", NLL = "<< setprecision(6)<<setiosflags(ios::fixed)<<nll->getVal() <<endl;
		else
			cout<<"Sadly the fit failed"<<endl;
	}
	
	cout << "nll errors = " << nll->numEvalErrors() << endl;
}
