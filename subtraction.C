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
	ifstream rfiles_ped("runs/subtraction/ch04_PMT539_B02_975V/pedestal.dat");
	ifstream rfiles("runs/ch04_21869_21882.dat");
	ofstream Mainz_dat;
	Mainz_dat.open ("analyzed_data/subtraction.txt"); //Opens a text file that stores the mean and sigma of the data (with and without a fit)
	string line_ped;
	string line;
	while(getline(rfiles_ped, line_ped)){
		//ifstream inFile_ped(line_ped);
		//string line2_ped;
		//getline(inFile_ped,line2_ped);
	while(getline(rfiles, line)){
	gDirectory->DeleteAll();
	
	ifstream inFile_ped(line_ped);
	ifstream inFile(line);
	string line2_ped;
	string line2;
	getline(inFile_ped,line2_ped);
	getline(inFile,line2);

	int k=0;
	double binmax, binmaxpos, binmax_ped, binmaxpos_ped;
	double charge;
	double mean,mpv,gsigma,mpv2,gsigma2;
	double sigma=-10;
	double ampli=-10.;
	double area = -100;
	double fr[2]={-10};

	double gainADC = 200.;
	double gainAmp = 10.;
	double Q = 0.000160218; 
    double minChannel = 0;
    double maxChannel = 4095;

	//The following alternative settings use Michael's ET 9305QKB #539 PMT + base. Consider them more accurate until further notice
	//double gainPMT = 1e6; double pedestal = 90.5;  //1000V
	//double gainPMT = 2.6e6; double pedestal = 27.4; //1100V
	//double gainPMT = 6e6; double pedestal = 11.9;   //1200V
	//double gainPMT = 9.3e6; double pedestal = 7.5; //1300V
	//double gainPMT = 1.15e7; double pedestal = 0;//1400V
	//The following settings use P2's ET 518 PMT. It was used for R5 in November 2022 @ Mainz
	//double gainPMT = 2.4e6; double pedestal = 37;//1000V For ET PMT 518 used for R1, R5. Provided by P2. Gain info is currently inaccurate
	//The following settings are for R5 in May 2022 at -1500V
	//double gainPMT = 10.5e6; double pedestal = 5.2;

	//***Use the below values if not using PMT gain in your analysis***
	//double pedestal = peak of pedestal; //Name of PMT + base combination, voltage used, channel number
	//double pedestal = 442., cut = 0 + pedestal;		//ET 9305QKB #616 + BT-06, 900 V, ch00, Ring 2 FF
	//double pedestal = 444., cut = 0 + pedestal;		//ET 9305QKB #542 + BT-04, 850 V, ch01, Ring 3 FF
	//double pedestal = 540., cut = 0 + pedestal;		//JLab ET (likely 9305QKB) + JLab base (Jie custom), 900 V, ch02, Ring 1 FF
	//double pedestal = 516., cut = 0 + pedestal;		//ET 9305QKB #615 + BT-01, 950 V, ch03, Ring 5 BF, cut may be higher
	double pedestal = 500., cut = 0 + pedestal;		//ET 9305QKB #539 + BT-02, 975 V, ch04, Ring 4 FF - Runs 21959->22084 have double pedestal. 500 is between both ped peaks
	//double pedestal = 0., cut = 0 + pedestal;			//Use to see unedited spectrum

    //double gainFactor = gainADC / (gainPMT * gainAmp * Q); //***Use if doing analysis with gain***
	double gainFactor = 1.; 								 //***Use if doing analysis without gain***

	TH1F* hst1 = new TH1F("hst1","",4096, minChannel*gainFactor, maxChannel*gainFactor);
	TH1F* hst2 = new TH1F("hst2","",4096, minChannel*gainFactor, maxChannel*gainFactor);

	double counts1; double counts2;
    for(int i = 1; i <= 4096; i++) {
		inFile_ped >> counts1;
		inFile >> counts2;
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

	//Gets the height of the maximum point (the pedestal, pulse, etc) of the histograms
	binmaxpos_ped = hst1->GetMaximumBin();
	binmax_ped = hst1->GetBinContent(binmaxpos_ped);
	cout<<"Pure pedestal MaxHeight: "<<binmax_ped<<"  Pure pedestal MaxHeightPos: "<<binmaxpos_ped<<"\n"<<endl;
	binmaxpos = hst2->GetMaximumBin();
	binmax = hst2->GetBinContent(binmaxpos);
	cout<<"MaxHeight: "<<binmax<<"  MaxHeightPos: "<<binmaxpos<<"\n"<<endl;


	//***Normalizing histograms*** The scaling values are the heights of the pedestal in each file
	hst1->Scale(1./binmax_ped);
	hst2->Scale(1./binmax);


	TString run_number;

    run_number = line;
	run_number = run_number.Append("-" + line_ped);
    run_number = run_number.ReplaceAll("data/ch04/run_",""); //Pulls the run number from the list of files
    run_number = run_number.ReplaceAll("_ch04.dat",""); 	 //


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
	hst2->GetXaxis()->SetRangeUser(0,600);
	sub_plot->SaveAs("plots/subtraction/ch04_21869_21882/" + run_number + ".png");
	//sub_plot->Close();

	Mainz_dat << "Run: " << run_number << "		";
	Mainz_dat << "Mean: " << mean << " " << "RMS: " << sigma << "      " << "mpv: " << mpv2 << "     " << "gsigma: " << gsigma2 << "\n\n";
	
	}
	} //Ends the while loop that reads files.dat
	Mainz_dat.close();
        
	rfiles_ped.close();	
	rfiles.close();

}

