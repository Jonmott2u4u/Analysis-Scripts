#include <iostream>
#include <TString.h>

void scint_pes()
{
    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        for(int det=1; det<9; det++){

            //PE spectrum of each detector with scintillator cuts (must hit the upstream and at least one downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_scintcut_pes.root",det));

            //PE spectrum for beams that hit only one quartz tile (ring cut) and passes scintillator cut
            tmp = (TH1D*)file->Get(Form("R%iOnly_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_Solo_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_ringcut_pes.root",det));

            //Distribution of initial beam angles for scintillator cuts
            tmp = (TH1D*)file->Get(Form("R%i_InitialBeamAngleHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_angle",det));
            hst->SetTitle(Form("R%i Initial Beam Angle Distribution",det));
            hst->GetXaxis()->SetTitle("Angle from Z-axis [deg]");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,20);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_scintcut_angle.root",det));

            //Distribution of initial beam angles for ring+scintillator cuts
            tmp = (TH1D*)file->Get(Form("R%iOnly_InitialBeamAngleHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iOnly_angle",det));
            hst->SetTitle(Form("R%i Initial Beam Angle Distribution",det));
            hst->GetXaxis()->SetTitle("Angle from Z-axis [deg]");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,20);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_ringcut_angle.root",det));
        }
        file->Close("R");
    }
}

void gem1_pes()
{
    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        for(int det=1; det<9; det++){

            tmp = (TH1D*)file->Get(Form("R%i_GEM1_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_gem1_scintcut_pes.root",det));

            tmp = (TH1D*)file->Get(Form("R%iOnly_GEM1_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_Solo_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_gem1_ringcut_pes.root",det));

            tmp = (TH1D*)file->Get(Form("R%i_GEM1_InitialBeamAngleHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_angle",det));
            hst->SetTitle(Form("R%i Initial Beam Angle Distribution",det));
            hst->GetXaxis()->SetTitle("Angle from Z-axis [deg]");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,20);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_gem1_scintcut_angle.root",det));

            tmp = (TH1D*)file->Get(Form("R%iOnly_GEM1_InitialBeamAngleHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iOnly_angle",det));
            hst->SetTitle(Form("R%i Initial Beam Angle Distribution",det));
            hst->GetXaxis()->SetTitle("Angle from Z-axis [deg]");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,20);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_gem1_ringcut_angle.root",det));
        }
        file->Close("R");
    }
}

void gem2_pes()
{
    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        for(int det=1; det<9; det++){

            tmp = (TH1D*)file->Get(Form("R%i_GEM2_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_gem2_scintcut_pes.root",det));

            tmp = (TH1D*)file->Get(Form("R%iOnly_GEM2_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_Solo_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_gem2_ringcut_pes.root",det));

            tmp = (TH1D*)file->Get(Form("R%i_GEM2_InitialBeamAngleHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_angle",det));
            hst->SetTitle(Form("R%i Initial Beam Angle Distribution",det));
            hst->GetXaxis()->SetTitle("Angle from Z-axis [deg]");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,20);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_gem2_scintcut_angle.root",det));

            tmp = (TH1D*)file->Get(Form("R%iOnly_GEM2_InitialBeamAngleHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iOnly_angle",det));
            hst->SetTitle(Form("R%i Initial Beam Angle Distribution",det));
            hst->GetXaxis()->SetTitle("Angle from Z-axis [deg]");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,20);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_gem2_ringcut_angle.root",det));
        }
        file->Close("R");
    }
}

//This object performs cuts over the quartz in the x-direction. Goal is to see position dependence of PE yield, among other things
void quartz_pos(){

    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;
    int pos, file_open = 0;

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        file_open++;
        for(int det=4; det<5; det++){
            pos = -11;
            while(pos <= 1){
                pos++;
		        pos++;
                TTree *tree = (TTree*)file->Get("MOLLEROptTree");
                TCanvas *canvas_pes = new TCanvas("canvas_pes","canvas_pes");
                tree->Draw(Form("MOLLEROptData.MOLLERDetectorEvent.R%iSoloPEs",det),Form("(MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY <= %i) && (MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY > %i-2)",det,pos,det,pos));
                canvas_pes->SaveAs(Form("plots/r%i/file%i_pes_pos_%i.root",det,file_open,pos));

                /*TCanvas *canvas_pos = new TCanvas("canvas_pos","canvas_pos");
                tree->Draw(Form("MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY:MOLLEROptData.MOLLERDetectorEvent.R%iTileHitX",det,det),Form("(MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY <= %i) && (MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY > %i-2)",det,pos,det,pos),"colz");
                canvas_pos->SaveAs(Form("plots/r%i/file%i_quartz_pos_%i.root",det,file_open,pos));*/

            }
        }
        file->Close("R");
    }
}
