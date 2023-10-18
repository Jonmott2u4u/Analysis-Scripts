#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TString.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
Double_t langaufun(Double_t *x, Double_t *par);


void FitLanGaus()
{
	//ifstream rfiles("R5_horizontal_scans.dat"); //Reads a .dat file listing all the .dat files to be analyzed
	ifstream rfiles("runs/ch02_21969_22084.dat");
	ofstream Mainz_dat;
	Mainz_dat.open ("analyzed_data/ch02_21969_22084.txt"); //Opens a text file that stores the mean and sigma of the data (with and without a fit)
	string line;
	while(getline(rfiles, line)){

	gDirectory->DeleteAll();
	
	ifstream inFile(line);
	string line2;
	getline(inFile,line2);

	int k=0;
	double charge;
	double mean,mpv,gsigma,mpv2,gsigma2;
	double pe_langau,pe_gaus;
	double sigma=-10;
	double ampli=-10.;
	double area = -100;
	double fr[2]={-10};
	
	double gainADC = 200.;
	double gainAmp = 10.;
	double Q = 0.000160218; 
    double minChannel = 0;
    double maxChannel = 4095;

	//***The following alternative settings use Michael's ET 9305QKB #539 PMT + base. Consider them more accurate until further notice***
	//double gainPMT = 1e6; double pedestal = 90.5;  //1000V
	//double gainPMT = 2.6e6; double pedestal = 27.4; //1100V
	//double gainPMT = 6e6; double pedestal = 11.9;   //1200V
	//double gainPMT = 9.3e6; double pedestal = 7.5; //1300V
	//double gainPMT = 1.15e7; double pedestal = 0;//1400V
	//***The following settings use P2's ET 518 PMT. It was used for R5 in November 2022 @ Mainz***
	//double gainPMT = 2.4e6; double pedestal = 37;//1000V For ET PMT 518 used for R1, R5. Provided by P2. Gain info is currently inaccurate
	//The following settings are for R5 in May 2022 at -1500V
	//double gainPMT = 10.5e6; double pedestal = 5.2;
	//***Following settings are for PMT ET 9305QKB #615 + custom base (values will be updated when known)***
	//double gainPMT = 2.69e6; double pedestal = 0;  //950V
	//double gainPMT = 0.27e6; double pedestal = 239;  //950V, dividing by 8.2 rather than 0.82
	//***Following settings are for PMT ET 9305QKB #616 + custom base (values will be updated when known)***
	//double gainPMT = 5.59e6; double pedestal = 0;  //900V
	//double gainPMT = 0.57e6; double pedestal = 96.5;  //900V, dividing by 8.2 rather than 0.82

	//***Use the below values if not using PMT gain in your analysis***
	//double pedestal = peak of pedestal; //Name of PMT + base combination, voltage used, channel number
	//double pedestal = 517.;			//ET 9305QKB #615 + BT-01, 950 V, ch03, Ring 5 BF
	double pedestal = 540.;				//JLab ET (likely 9305QKB) + JLab base (Jie custom), 900 V, ch02, Ring 1 FF


	//double gainFactor = gainADC / (gainPMT * gainAmp * Q); //***Use if doing analysis with gain***
	double gainFactor = 1.; 								 //***Use if doing analysis without gain***


    TH1F* pulseHist = new TH1F("pulseHeight","",4096, minChannel*gainFactor, maxChannel*gainFactor);

    double counts;
	double cut = 6 + pedestal; 								 //Cuts a section of the final plot out
    for(int i = 1; i <= 4096; i++) {
		inFile >> counts;
		if (i*gainFactor >= pedestal) {
			if ((i-k)*gainFactor >= (cut-pedestal)) {
                		pulseHist->SetBinContent(i-k, counts);
			}
		}
		else {
			k++;
		}
	}
	//pulseHist->Scale(1./(pulseHist->Integral()));
	//pulseHist->Scale(1./114000.);

	TString run_number;
    run_number = line;
    run_number = run_number.ReplaceAll("data/ch02/run_",""); //Pulls the run number from the list of files
    run_number = run_number.ReplaceAll("_ch02.dat",""); 	       
	

	//TString langau_number; TString gaus_number; TString og_number;
	//langau_number = run_number; gaus_number = run_number; og_number = run_number;
	//langau_number.Append("_langau.png");gaus_number.Append("_gaus.png"); og_number.Append("_noFit.png");
	

	//TCanvas *og_plot = new TCanvas("og_plot","og_plot",800,600);
	//og_plot->cd();
	TH1F *hst;
	hst = (TH1F*)pulseHist->Clone();
    //hst->Draw();
	//hst->GetXaxis()->SetRangeUser(0,20); //Range for the pedestal
	//og_plot->SaveAs("R5_horizontal_plots/" + og_number + "_nofit.png"); //Saves a plot with no fit

	mean=hst->GetMean();
    sigma=hst->GetRMS();

	fr[0]=0.6*mean;
    fr[1]=1.4*mean;
	area=pulseHist->Integral(fr[0],fr[1]);
	TF1 *langaus = new TF1("langaus",langaufun,fr[0],fr[1],4);
    langaus->SetParNames("lwidth","mpv","integral","gsigma");
	
	cout<<"mean "<<mean<<"  area  "<<area<<"  sigma  "<<sigma<<endl;
	
	langaus->SetParameters(5.,mean,area,sigma);
	pulseHist->Fit("langaus","R0","",fr[0],fr[1]);
	

	mpv = langaus->GetParameter(1);
	gsigma = langaus->GetParameter(3);

	fr[0]= 0.6*mean;
	fr[1]= 1.1*mean;
	TF1 *gaus = new TF1("gaus","gaus",fr[0],fr[1]);
	TH1F *pulseHist2;
	pulseHist2 = (TH1F*)pulseHist->Clone();
	pulseHist2->Fit(gaus,"R");
	mpv2 = gaus->GetParameter(1);
	gsigma2 = gaus->GetParameter(2);

	pe_langau = mpv*mpv/(gsigma*gsigma);
	pe_gaus = mpv2*mpv2/(gsigma2*gsigma2);


	gStyle->SetOptStat(1111);
    gStyle->SetOptFit(111);
	TCanvas *multi_plot = new TCanvas("multi-plot","multi-plot",800,600);
	multi_plot->Divide(2,1);
	multi_plot->cd(1);
	pulseHist->Draw();
	pulseHist->SetTitle("Langau fit [run " + run_number + "]"); //pulseHist->GetXaxis()->SetTitle("PEs");
	pulseHist->GetXaxis()->SetRangeUser(0,1000);
	langaus->Draw("same");
	multi_plot->cd(2);
	pulseHist2->Draw();
	pulseHist2->SetTitle("Gaussian fit [run " + run_number + "]");
	pulseHist2->GetXaxis()->SetRangeUser(0,1000);
	multi_plot->SaveAs("plots/ch02_21969_22084/" + run_number + ".png");
	multi_plot->Close();

	Mainz_dat << "Run: " << run_number << "		";
	//Mainz_dat << "Mean: " << mean << " " << "RMS: " << sigma << "      " << "mpv: " << mpv2 << "     " << "gsigma: " << gsigma2 << "\n\n";
	Mainz_dat << "Langau MP: " << mpv << " " << "Langau gsigma: " << gsigma << "Langau PEs: " << pe_langau << "		" << "Gaussian MP: " << mpv2 << " " << "Gaussian gsigma: " << gsigma2 << "Gaussian PEs: " << pe_gaus << "\n\n";
	
	} //Ends the while loop that reads files.dat
	Mainz_dat.close();
        
	//This next section is used to plot MP as a function of position (or whatever you want, the values are inputted by hand)
	
	//Plotting 20 mm R6 vertical data R5 data. Assumed beam starts 3 cm below center and moved towards the edge
	//Uses gaussian MPs
	/*double mean_vector[11] = {16.77, 16.8, 16.25, 15.8, 16.12, 16.4, 17.07, 17.54, 17.51, 17.52, 19.45};
	double position_vector[13] = {.225,1.225,2.225,3.225,4.225,5.225,6.225,7.225,8.225,9.225,10.225};
	TGraph* mean_plot = new TGraph(11,position_vector,mean_vector);
	mean_plot->SetTitle("PE variation with beam position;Beam position [cm];PE yield");
	mean_plot->SetMarkerStyle(kFullSquare);
	TCanvas *plot3 = new TCanvas("plot3","plot3",800,600);
	plot3->cd();
	mean_plot->Draw();*/

	rfiles.close();	
}

Double_t langaufun(Double_t *x, Double_t *par) {

  //Fit parameters:
  //par[0]=Width (scale) parameter of Landau density
  //par[1]=Most Probable (MP, location) parameter of Landau density
  //par[2]=Total area (integral -inf to inf, normalization constant)
  //par[3]=Width (sigma) of convoluted Gaussian function
  //
  //In the Landau distribution (represented by the CERNLIB approximation),
  //the maximum is located at x=-0.22278298 with the location parameter=0.
  //This shift is corrected within this function, so that the actual
  //maximum is identical to the MP parameter.

  // Numeric constants
  Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
  Double_t mpshift  = -0.22278298;       // Landau maximum location

  // Control constants
  Double_t np = 100.0;      // number of convolution steps
  Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

  // Variables
  Double_t xx;
  Double_t mpc;
  Double_t fland;
  Double_t sum = 0.0;
  Double_t xlow,xupp;
  Double_t step;
  Double_t i;


  // MP shift correction
  mpc = par[1] - mpshift * par[0];

  // Range of convolution integral
  xlow = x[0] - sc * par[3];
  xupp = x[0] + sc * par[3];

  step = (xupp-xlow) / np;

  // Convolution integral of Landau and Gaussian by sum
  for(i=1.0; i<=np/2; i++) {
    xx = xlow + (i-.5) * step;
    fland = TMath::Landau(xx,mpc,par[0]) / par[0];
    sum += fland * TMath::Gaus(x[0],xx,par[3]);

    xx = xupp - (i-.5) * step;
    fland = TMath::Landau(xx,mpc,par[0]) / par[0];
    sum += fland * TMath::Gaus(x[0],xx,par[3]);
  }

  return (par[2] * step * sum * invsq2pi / par[3]);
}
