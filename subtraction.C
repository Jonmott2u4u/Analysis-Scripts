#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TString.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;


void subtraction()
{
	//ifstream rfiles("R5_horizontal_scans.dat"); //Reads a .dat file listing all the .dat files to be analyzed
	ifstream rfiles_ped("pedestal.dat");
	ifstream rfiles_lg("lg.dat");
	ofstream Mainz_dat;
	Mainz_dat.open ("analyzed_data/subtraction.txt"); //Opens a text file that stores the mean and sigma of the data (with and without a fit)
	string line_ped;
	string line_lg;
	while(getline(rfiles_ped, line_ped)){
	while(getline(rfiles_lg, line_lg)){

	gDirectory->DeleteAll();
	
	ifstream inFile_ped(line_ped);
	ifstream inFile_lg(line_lg);
	string line2_ped;
	string line2_lg;
	getline(inFile_ped,line2_ped);
	getline(inFile_lg,line2_lg);

	int k=0;
	double charge;
	double mean,mpv,gsigma,mpv2,gsigma2;
	double sigma=-10;
	double ampli=-10.;
	double area = -100;
	double fr[2]={-10};
	
	//The following settings are the default used
        /*double gainADC = 200.; //Will depend. Probably 200, if not then 25
	double gainPMT = 14.96e6, double pedestal = 38.06; // @ 1100 V for R6 in count mode using Michael's PMT (Get gain info from Brynne, current value is default)
        double gainAmp = 1.;*/

	//The following alternative settings use Michael's ET 9305QKB #539 PMT + base. Consider them more accurate until further notice
	double gainADC = 200.;
	//double gainPMT = 1e6; double pedestal = 90.5;  //1000V
	double gainPMT = 2.6e6; double pedestal = 27.4; //1100V
	//double gainPMT = 6e6; double pedestal = 11.9;   //1200V
	//double gainPMT = 9.3e6; double pedestal = 7.5; //1300V
	//double gainPMT = 1.15e7; double pedestal = 0;//1400V
	//The following settings use P2's ET 518 PMT. It was used for R5 in November 2022 @ Mainz
	//double gainPMT = 2.4e6; double pedestal = 37;//1000V For ET PMT 518 used for R1, R5. Provided by P2. Gain info is currently inaccurate
	//The following settings are for R5 in May 2022 at -1500V
	//double gainPMT = 10.5e6; double pedestal = 5.2;
	double gainAmp = 8.;


        double Q = 0.000160218; 

        double minChannel = 0;
        double maxChannel = 4095;

        double gainFactor = gainADC / (gainPMT * gainAmp * Q);
	double counts1; double counts2;
	double cut = 0 + pedestal; //Cuts a section of the final plot out


	TH1F* hst1 = new TH1F("hst1","",4096, minChannel*gainFactor, maxChannel*gainFactor);
	TH1F* hst2 = new TH1F("hst2","",4096, minChannel*gainFactor, maxChannel*gainFactor);

        for(int i = 1; i <= 4096; i++) {
		
		inFile_ped >> counts1;
		inFile_lg >> counts2;
		//cout<<counts<<'\n'; 
		if (i*gainFactor >= pedestal) {
			if ((i-k)*gainFactor >= (cut-pedestal)) {
                		hst1->SetBinContent(i-k, counts1);
				hst2->SetBinContent(i-k, counts2);
			}
		}
		else {
			k++;
		}	
	}
	//pulseHist->Scale(1./(pulseHist->Integral()));
	//pulseHist->Scale(1./225000);
	hst1->Scale(1./114000.);
	hst2->Scale(1./105000.);

	TString run_number;

        run_number = line2_lg;
	run_number = run_number.Append("-" + line2_ped);
        run_number = run_number.ReplaceAll("data/ch00/run_",""); //Pulls the run number from the list of files
        run_number = run_number.ReplaceAll("_ch00.dat",""); 	       //
	//run_number = run_number.ReplaceAll("_ch02.dat","");            //


	//TCanvas *og_plot = new TCanvas("og_plot","og_plot",800,600);
	//og_plot->cd();
        //hst->Draw();
	//hst->GetXaxis()->SetRangeUser(0,20); //Range for the pedestal
	//og_plot->SaveAs("R5_horizontal_plots/" + og_number + "_nofit.png"); //Saves a plot with no fit
	
	hst2->Add(hst1,-1);

	gStyle->SetOptStat(1111);
    	gStyle->SetOptFit(111);
	TCanvas *sub_plot = new TCanvas("sub_plot","multi-plot",800,600);
	sub_plot->cd();
	hst2->Draw();
	hst2->SetTitle("Runs " + run_number + ""); //pulseHist->GetXaxis()->SetTitle("PEs");
	hst2->GetXaxis()->SetRangeUser(0,20);
	sub_plot->SaveAs("test_plots/" + run_number + ".png");
	//sub_plot->Close();

	Mainz_dat << "Run: " << run_number << "		";
	Mainz_dat << "Mean: " << mean << " " << "RMS: " << sigma << "      " << "mpv: " << mpv2 << "     " << "gsigma: " << gsigma2 << "\n\n";
	
	}
	} //Ends the while loop that reads files.dat
	Mainz_dat.close();
        
	rfiles_ped.close();	
	rfiles_lg.close();

}

