
void FitLowGain(TString filename){
  TCanvas *c1 = new TCanvas();
  gROOT->LoadMacro("./Function.C");
  TFile *rootfile = TFile::Open(filename,"R");
  drs4->Draw("ped1-ch1-(ped2-ch2)>>h_fit(550,-50,700)","","goff");
  TH1D *h_QDC = (TH1D*)gDirectory->FindObject("h_fit");
  h_QDC->Draw();
  h_QDC->SetTitle("");
  h_QDC->GetYaxis()->SetTitle("count");
  fit_pmt(h_QDC,-30,500);
  c1->Print("run#1782.pdf");
  c1->Print("run#1782.C");
  //fit_bkg(h_QDC,-20,20);
  //h_QDC->SetTitle("run 1538 @ -1.0 kV");
}


void fit_pmt(TH1D *h_QDC, double low, double high){
	///////////////////////////////
	// define fitting function
	/////////////////////////////
	TF1 *fit_func=new TF1("fit_func",the_real_deal_yx,-1000,20000,9);  // 9 parameters
	fit_func->SetLineColor(4);
	fit_func->SetNpx(2000);
	fit_func->SetLineWidth(2);
	fit_func->SetParName(0,"w");
	fit_func->SetParName(1,"Q0");
	fit_func->SetParName(2,"sigma 0");
	fit_func->SetParName(3,"alpha");
	fit_func->SetParName(4,"mean P.E");
	fit_func->SetParName(5,"Q1");
	fit_func->SetParName(6,"sigma 1");
	
	///////////////////////////////
	//get initial parameters
	//////////////////////////////
	double par[10]={0.0};
	//---w---
	par[0]=0.04;
	//---Q0--- ped mean
	par[1]=0;
	//---sigma_0---
	par[2]=5;
	//---alpha---
	par[3] =0.4;
	//pe mu, Q1, sigma1
	par[4]= mean_pe ; // mean PE
	par[5] = 30; // gain
	par[6] = 10; // gain sigma

	double bin_width = h_QDC->GetXaxis()->GetBinWidth(1);
	par[7]=0; // clock
	par[8]=bin_width*(h_QDC->GetEntries());//back[0];


	fit_func->SetParameters(par);
	// fit_func->FixParameter(0,0); // w
	fit_func->FixParameter(3,0); // alpha
	//fit_func->FixParameter(1, -0.8413); // Q0
	//fit_func->FixParameter(2,7.973); // sigma0
	//fit_func->FixParameter(4,2); // mean P.E.
	fit_func->FixParameter(7,0); // Clock
	//////////////////////////////////////////////////////////////
	// Draw and fit
	//////////////////////////////////////////////////////////////

	gStyle->SetOptFit(1);
	h_QDC->SetMarkerSize(2);
	h_QDC->SetMarkerStyle(20);
	h_QDC->GetXaxis()->SetTitle("QDC channel");
	//h_QDC->GetYaxis()->SetTitle("Normalized yield");
	h_QDC->GetYaxis()->SetTitle("count");
	h_QDC->Draw();

	///////////////////////////////
	// set minimization engine
	///////////////////////////////
	double arglist[0]=2;
	int ierflg=0;
	TMinuit minuit(9);
	minuit.mnexcm("SET STR",arglist,1,ierflg);
	
	//starter...
	double fit_low=low;
	double  fit_high=high;
	h_QDC->Fit(fit_func,"R","",fit_low,fit_high);
	/////////////////////////////////////////////////////////
	// Output parameters
	//
	// [0] = w
	// [1] = Q0, mean of PED
        // [2] = sigma_0, RMS of PED
        // [3] = alpha, decay constant of discrete background
        // [4] = mu, mean of the entire ADC distribution
        // [5] = q1, peak of SPE
        // [6] = sigma1, RMS of SPE  
        // [7] = Norm of clock contribution
        // [8] =norm of light related contribution 
	/////////////////////////////////////////////////////////
	fit_func->GetParameters(par);
	TF1 *fits_from_fit_pe[total_pe];
	for(int i=0; i<total_pe;i++){
	  par[9]=i+1;
	  fits_from_fit_pe[i] = new TF1(Form("fits_from_fit_pe%d",i),the_real_deal_yx_pe,-1000,20e3,10);
	  fits_from_fit_pe[i]->SetParameters(par);
	  fits_from_fit_pe[i]->SetLineStyle(2);
	  fits_from_fit_pe[i]->SetLineColor(2);
	  fits_from_fit_pe[i]->SetNpx(2000);
	  fits_from_fit_pe[i]->Draw("same");
	}
	
	TF1 *fis_from_fit_bg = new TF1("fis_from_fit_bg",the_real_deal_yx_bg,-1000,20e3,9);
	fis_from_fit_bg->SetParameters(par);
        fis_from_fit_bg->SetLineStyle(2);
        fis_from_fit_bg->SetLineColor(7);
        fis_from_fit_bg->SetNpx(2000);
	fis_from_fit_bg->Draw("same");
	
}


void fit_bkg(TH1D *h_QDC, double low,double high){
  TF1 *fit_func = new TF1("fit_func",the_real_deal_yx_bg,-100,100,9);
  fit_func->SetLineWidth(2);
  fit_func->SetParName(0,"w");
  fit_func->SetParName(1,"Q0");
  fit_func->SetParName(2,"sigma 0");
  fit_func->SetParName(3,"alpha");
  fit_func->SetParName(4,"mean P.E");
  fit_func->SetParName(5,"Q1");
  fit_func->SetParName(6,"sigma 1");
  fit_func->SetParName(7,"Clock Contribution");
  fit_func->SetParName(8,"Total Normalization");
  
  fit_func->SetParameter(4,0);
  fit_func->FixParameter(4,0);
  fit_func->SetParameter(5,0);
  fit_func->FixParameter(5,0);
  fit_func->SetParameter(6,0);
  fit_func->FixParameter(6,0);
  fit_func->SetParameter(7,0);
  fit_func->FixParameter(7,0);

  fit_func->SetParameter(0,0.2); // w
  fit_func->SetParameter(1,0); // Q0
  fit_func->SetParameter(2,8); // sigma0
  fit_func->SetParameter(3,0.04); // alpha
  fit_func->SetParameter(8,10e3); // Normalization

  gStyle->SetOptFit(1);
  h_QDC->SetTitle("PMT Background QDC");
  h_QDC->GetXaxis()->SetTitle("QDC Channel");
  h_QDC->GetYaxis()->SetTitle("Counts");
  h_QDC->Draw();
  
  h_QDC->Fit(fit_func,"R","",low,high);
  
}
