void rootfilecheck(std::string file="mass_plots_rebinned_2012_MVAlike.root", std::string HistName="massTrkVBF_VBFH",std::string HistSufix=""){

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
	
	
  TFile *f = new TFile(file.c_str());
	
	TLatex l1; //l.SetTextAlign(12);
    l1.SetTextSize(0.05);
    //l1.SetNDC();
    l1.SetTextColor(1);

  TCanvas *c1 = new TCanvas("c1","c1");
  TH1D* hist =(TH1D*)f->Get((""+HistName+"100"+HistSufix).c_str());
//  hist->SetMaximum(hist->GetMaximum()*1.5);
	hist->GetXaxis()->SetTitle("Discriminating Variable");
	hist->GetYaxis()->SetTitle("A.U.");
  hist->Draw("HIST C");
	float max_bin= hist->GetMaximumBin()-0.5*hist->GetXaxis()->GetBinWidth(1);
	float x_range = hist->GetNbinsX();
	float y_range = hist->GetMaximum();
	float max = hist->GetMaximum();
	max*=1.1;
	std::stringstream mass_label;
	mass_label<<"#bf{"<<100<<"}";
	std::cout<<max_bin<<"\t"<<max<<"\t"<<mass_label.str().c_str()<<endl;
	l1.DrawLatex(max_bin,max,mass_label.str().c_str());

  int start=100;
  int end=150;
  double step=2.5;
  double mass=start;
  while(mass<=end){
    //  for(int mass=start; mass<=end;mass++){
    std::stringstream ss; ss.str()="";
    ss << HistName << mass << HistSufix ;
    std::cout  << ss.str() << std::endl;
    TH1D* hist=(TH1D*)f->Get(ss.str().c_str());
    hist->SetLineColor(mass-50);
	  if(mass==100 || mass==105 || mass==110 || mass==115 || mass==120 || mass==125 || mass==130 || mass==135 || mass==140 || mass==145 || mass==150 ){
		  hist->SetLineColor(1);
		  max_bin= hist->GetMaximumBin()-0.5*hist->GetXaxis()->GetBinWidth(1);
		  max = hist->GetMaximum();
		  max*=1.1;
		  std::stringstream mass_label1;
		  mass_label1<<"#bf{"<<mass<<"}";
		  std::cout<<max_bin<<"\t"<<max<<"\t"<<mass_label1.str().c_str()<<endl;
		  l1.DrawLatex(max_bin,max,mass_label1.str().c_str());
	  }
    //    hist->SetLineColor(51+(mass-start)*8);
    hist->Draw("Same HIST C");
    mass+=step;
  }
  c1->Update();
  c1->Print((""+HistName+"shape.eps").c_str());

}
