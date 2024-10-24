#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TString.h"
#include "TCanvas.h"
#include "TGraph.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
Double_t langaufun(Double_t *x, Double_t *par);


void mainz_analysis()
{
	//Reads a .dat file listing all the .dat files to be analyzed
	ifstream rfiles("runs/r4_r5_edge_transition_r5.dat");
	//Opens a text file that stores misc. information
	ofstream Mainz_dat;
	Mainz_dat.open ("analyzed_data/r4_r5_edge_transition_r5.txt");
	string line;
	//Generating plots for future use
	TGraph* counts_plot_whole = new TGraph();
	TGraph* counts_plot_pulse = new TGraph();

	//Looping over the data files
	int file_counter = 0;
	int starting_pos = 282;; // 426 - 144;
	int pos = 0;
	int det = 5;
	while(getline(rfiles, line)){
	pos = starting_pos - 1*file_counter; //Use + if starting with 144, - for 426. Done to account for different position conventions
	file_counter++;
	gDirectory->DeleteAll();
	
	//Removes the line #HistoMode from the top of the data files
	ifstream inFile(line);
	string line2;
	getline(inFile,line2);

	//Defining parameters & constants
	int k=0;
	double binmax, binmaxpos;
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

	//***Use the below values if not using PMT gain in your analysis***
	//int det = 5;
	double pedestal = 0., cut = 0 + pedestal; //Use to see unedited spectrum
	//double pedestal = peak of pedestal; //Name of PMT + base combination, voltage used, channel number
	if (det == 1) pedestal = 540., cut = 10 + pedestal; //JLab ET (likely 9305QKB) + JLab base (Jie custom), 900 V, ch02, Ring 1 FF
	if (det == 2) pedestal = 442., cut = 10 + pedestal; //ET 9305QKB #616 + BT-06, 900 V, ch00, Ring 2 FF
	if (det == 3) pedestal = 445., cut = 30 + pedestal; //ET 9305QKB #542 + BT-04, 850 V, ch01, Ring 3 FF
	if (det == 4) pedestal = 521., cut = 10 + pedestal; //ET 9305QKB #539 + BT-02, 975 V, ch04, Ring 4 FF - Runs 21959->22084 have double pedestal. Current value given by Sayak Chatterjee
	if (det == 5) pedestal = 516., cut = 10 + pedestal; //ET 9305QKB #615 + BT-01, 950 V, ch03, Ring 5 BF, cut may be higher
	cout << pedestal << endl;

	//double gainFactor = gainADC / (gainPMT * gainAmp * Q); //***Use if doing analysis with gain***
	double gainFactor = 1.; 								 //***Use if doing analysis without gain***


    TH1F* pulseHist = new TH1F("pulseHeight","",4096, minChannel*gainFactor, maxChannel*gainFactor);

    double counts = 0;
	double total_counts_whole = 0, total_counts_pulse = 0;
    for(int i = 1; i <= 4096; i++) {
		inFile >> counts;
		total_counts_whole = total_counts_whole + counts; //Considers all events (including the pedestal)
		if (i*gainFactor >= pedestal) {
			if ((i-k)*gainFactor >= (cut-pedestal)) {
                		pulseHist->SetBinContent(i-k, counts);
						total_counts_pulse = total_counts_pulse + counts; //Only considers events outside the pedestal
			}
		}
		else {
			k++;
		}
	}
	counts_plot_whole->AddPoint(pos,total_counts_whole);
	counts_plot_pulse->AddPoint(pos,total_counts_pulse);
	
	//Gets the height of the maximum point (the pedestal, pulse, etc) of the histogram
	binmaxpos = pulseHist->GetMaximumBin();
	binmax = pulseHist->GetBinContent(binmaxpos);
	cout<<"MaxHeight: "<<binmax<<"  MaxHeightPos: "<<binmaxpos<<endl;


	TString run_number;
    run_number = line;
	if (det == 1){
    run_number = run_number.ReplaceAll("Mainz_Data/data/ch02/run_",""); //Pulls the run number from the list of files
    run_number = run_number.ReplaceAll("_ch02.dat",""); 	       
	}
	if (det == 2){
    run_number = run_number.ReplaceAll("Mainz_Data/data/ch00/run_",""); //Pulls the run number from the list of files
    run_number = run_number.ReplaceAll("_ch00.dat",""); 	       
	}
	if (det == 3){
    run_number = run_number.ReplaceAll("Mainz_Data/data/ch01/run_",""); //Pulls the run number from the list of files
    run_number = run_number.ReplaceAll("_ch01.dat",""); 	       
	}
	if (det == 4){
    run_number = run_number.ReplaceAll("Mainz_Data/data/ch04/run_",""); //Pulls the run number from the list of files
    run_number = run_number.ReplaceAll("_ch04.dat",""); 	       
	}
	if (det == 5){
    run_number = run_number.ReplaceAll("Mainz_Data/data/ch03/run_",""); //Pulls the run number from the list of files
    run_number = run_number.ReplaceAll("_ch03.dat",""); 	       
	}
	

	//TString langau_number; TString gaus_number; TString og_number;
	//langau_number = run_number; gaus_number = run_number; og_number = run_number;
	//langau_number.Append("_langau.root");gaus_number.Append("_gaus.root"); og_number.Append("_noFit.root");
	
	TCanvas *og_plot = new TCanvas("og_plot","og_plot",800,600);
	og_plot->cd();
	TH1F *hst;
	hst = (TH1F*)pulseHist->Clone();
    hst->Draw();
	hst->GetXaxis()->SetRangeUser(0,1000); //Range for the pedestal
	//og_plot->SaveAs("plots/raw/" + run_number + "_nofit.root"); //Saves a plot with no fit
	og_plot->SaveAs(Form("plots/%i/raw/"+ run_number +".root",det));

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
	//Langau portion of multiplot
	multi_plot->cd(1);
	pulseHist->Draw();
	pulseHist->SetTitle("Langau fit [run " + run_number + "]"); //pulseHist->GetXaxis()->SetTitle("PEs");
	pulseHist->GetXaxis()->SetRangeUser(0,1000);
	langaus->Draw("same");
	auto legend1 = new TLegend(0.6,0.7,0.9,0.9);
	legend1->SetHeader("PE yields","C"); // option "C" allows to center the header
	legend1->AddEntry(((TObject*)0), TString::Format("Langau PEs = %g", pe_langau), "");
	legend1->Draw();
	//Gaussian portion of the multiplot
	multi_plot->cd(2);
	pulseHist2->Draw();
	pulseHist2->SetTitle("Gaussian fit [run " + run_number + "]");
	pulseHist2->GetXaxis()->SetRangeUser(0,1000);
	auto legend2 = new TLegend(0.6,0.7,0.9,0.9);
	legend2->SetHeader("PE yields","C"); // option "C" allows to center the header
	legend2->AddEntry(((TObject*)0), TString::Format("Gaussian PEs = %g", pe_gaus), "");
	legend2->Draw();
	//multi_plot->SaveAs("plots/" + det + "/fitted/" + run_number +".root");
	//og_plot->SaveAs(Form("plots/%i/fitted/"+ run_number +".root",det));
	multi_plot->Draw();
	multi_plot->SaveAs(Form("plots/%i/fitted/"+ run_number +".root",det));
	multi_plot->Close();

	Mainz_dat << "Run: " << run_number << "		";
	//Mainz_dat << "Mean: " << mean << " " << "RMS: " << sigma << "      " << "mpv: " << mpv2 << "     " << "gsigma: " << gsigma2 << "\n\n";
	Mainz_dat << "Langau MP: " << mpv << " " << "Langau gsigma: " << gsigma << " " << "Langau PEs: " << pe_langau << "		" << "Gaussian MP: " << mpv2 << " " << "Gaussian gsigma: " << gsigma2 << " " << "Gaussian PEs: " << pe_gaus << "\n\n";
	
	} //Ends the while loop that reads files.dat
	Mainz_dat.close();
        
	//Creating misc. plots after the file loop has finished.

	counts_plot_whole->SetTitle(Form("Pulse + pedestal count variation with beam position in R%i;Beam position [mm];Counts",det));
	counts_plot_whole->SetMarkerStyle(kFullSquare);
	counts_plot_pulse->SetTitle(Form("Pulse count variation with beam position in R%i;Beam position [mm];Counts",det));
	counts_plot_pulse->SetMarkerStyle(kFullSquare);
	TCanvas *plot3 = new TCanvas("plot3","plot3",800,600);
	TCanvas *plot4 = new TCanvas("plot4","plot4",800,600);
	plot3->cd();
	counts_plot_whole->Draw();
	plot3->SaveAs(Form("plots/misc/all_counts_R%i.root",det));
	plot4->cd();
	counts_plot_pulse->Draw();
	plot4->SaveAs(Form("plots/misc/pulse_counts_R%i.root",det));

	//Unrelated plot
	double position_vector[12] = {282,281,280,279,278,277,276,275,274,273,272,271};
	double count_ratios[12] = {1.032,1.020,1.011,1.004,0.971,0.684,0.157,0.072,0.074,0.041,0.033,0.029};
	TGraph* count_ratio_plot = new TGraph(12,position_vector,count_ratios);
	count_ratio_plot->SetTitle("Ratio of counts for R5/R4;Beam position [mm];Count ratio (R5/R4)");
	count_ratio_plot->SetMarkerStyle(kFullSquare);
	TCanvas *plot5 = new TCanvas("plot5","plot5",800,600);
	TF1 *f1 = new TF1("f1","1/(1+TMath::Exp([1]*([0]-x)))",274,283);
	f1->SetParameter(0,276);
	f1->SetParameter(1,2);
	count_ratio_plot->Fit("f1");
	plot5->cd();
	count_ratio_plot->Draw();
	f1->Draw("lsame");
	plot5->SaveAs("plots/misc/counts_ratio_R5_R4.root");

	//TGraph* mean_plot = new TGraph(11,position_vector,mean_vector);
	//mean_plot->SetTitle("PE variation with beam position;Beam position [cm];PE yield");
	//mean_plot->SetMarkerStyle(kFullSquare);
	//TCanvas *plot3 = new TCanvas("plot3","plot3",800,600);
	//plot3->cd();
	//mean_plot->Draw();

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
