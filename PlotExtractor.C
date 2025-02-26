#include <iostream>
#include <TString.h>
#include <math.h>

void umass_scint_pes()
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

void willmary_pes()
{
    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        for(int det=1; det<9; det++){

            //-------The following block is for muons striking any combination of scints---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iAdjacent_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iAdjacent_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iOnly_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iOnly_PEs.root",det));

            //-------The following block is for muons striking scints 1 & 3---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_Scint13_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_Scint13_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_Scint13_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_Scint13_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iAdjacent_Scint13_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iAdjacent_Scint13_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_Scint13_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iOnly_Scint13_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iOnly_Scint13_PEs.root",det));

            //-------The following block is for muons striking scints 1 & 4---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_Scint14_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_Scint14_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_Scint14_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_Scint14_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iAdjacent_Scint14_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iAdjacent_Scint14_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_Scint14_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iOnly_Scint14_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iOnly_Scint14_PEs.root",det));

            //-------The following block is for muons striking scints 2 & 3---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_Scint23_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_Scint23_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_Scint23_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_Scint23_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iAdjacent_Scint23_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iAdjacent_Scint23_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_Scint23_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iOnly_Scint23_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iOnly_Scint23_PEs.root",det));

            //-------The following block is for muons striking scints 2 & 4---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_Scint24_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_Scint24_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_Scint24_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_Scint24_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iAdjacent_Scint24_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iAdjacent_Scint24_PEs.root",det));

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_Scint24_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%iOnly_Scint24_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%iOnly_Scint24_PEs.root",det));

        }
        file->Close("R");
    }
}

void old_gem1_pes()
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

void old_gem2_pes()
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

void old_scint_hit_tracker(){

    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;
    int pos, file_open = 0;
    char ext[] = "MOLLEROptData.MOLLERDetectorEvent.";

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        file_open++;
        TTree *tree = (TTree*)file->Get("MOLLEROptTree");

        TCanvas *canvas_scint12 = new TCanvas("canvas_scint12","canvas_scint12");
        tree->Draw(Form("%sScint1TrackHit",ext),Form("%sScint2TrackHit == 1",ext));
        canvas_scint12->SaveAs("plots/scint12_gems.root");

        TCanvas *canvas_scint123 = new TCanvas("canvas_scint123","canvas_scint123");
        tree->Draw(Form("%sScint1TrackHit",ext),Form("(%sScint2TrackHit == 1) && (%sScint3TrackHit == 1)",ext,ext));
        canvas_scint123->SaveAs("plots/scint123_gems.root");

        TCanvas *canvas_scint124 = new TCanvas("canvas_scint124","canvas_scint124");
        tree->Draw(Form("%sScint1TrackHit",ext),Form("(%sScint2TrackHit == 1) && (%sScint4TrackHit == 1)",ext,ext));
        canvas_scint124->SaveAs("plots/scint124_gems.root");

        TCanvas *canvas_scint1234 = new TCanvas("canvas_scint1234","canvas_scint1234");
        tree->Draw(Form("%sScint1TrackHit",ext),Form("(%sScint2TrackHit == 1) && (%sScint3TrackHit == 1) && (%sScint4TrackHit == 1)",ext,ext,ext));
        canvas_scint1234->SaveAs("plots/scint1234_gems.root");

        file->Close("R");
    }
}

void scint_angle_tracker(){

    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;
    int pos, file_open = 0;
    char ext[] = "MOLLEROptData.MOLLERDetectorEvent.";

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        file_open++;
        TTree *tree = (TTree*)file->Get("MOLLEROptTree");

        TCanvas *canvas_scint12_angles = new TCanvas("canvas_scint12_angles","canvas_scint12_angles");
        tree->Draw(Form("%sInitialBeamAngle",ext),Form("(%sScint1TrackHit == 1) & (%sScint2TrackHit == 1)",ext,ext));
        canvas_scint12_angles->SaveAs("plots/scint12_angles.root");

        TCanvas *canvas_scint123_angles = new TCanvas("canvas_scint123_angles","canvas_scint123_angles");
        tree->Draw(Form("%sInitialBeamAngle",ext),Form("(%sScint1TrackHit == 1) & (%sScint2TrackHit == 1) & (%sScint3TrackHit == 1)",ext,ext,ext));
        canvas_scint123_angles->SaveAs("plots/scint123_angles.root");

        TCanvas *canvas_scint124_angles = new TCanvas("canvas_scint124_angles","canvas_scint124_angles");
        tree->Draw(Form("%sInitialBeamAngle",ext),Form("(%sScint1TrackHit == 1) & (%sScint2TrackHit == 1) & (%sScint4TrackHit == 1)",ext,ext,ext));
        canvas_scint124_angles->SaveAs("plots/scint124_angles.root");

        TCanvas *canvas_scint1234_angles = new TCanvas("canvas_scint1234_angles","canvas_scint1234_angles");
        tree->Draw(Form("%sInitialBeamAngle",ext),Form("(%sScint1TrackHit == 1) & (%sScint2TrackHit == 1) & (%sScint3TrackHit == 1) & (%sScint4TrackHit == 1) ",ext,ext,ext,ext));
        canvas_scint1234_angles->SaveAs("plots/scint1234_angles.root");

        file->Close("R");
    }
}

void scint_hitpos_tracker(){

    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;
    int pos, file_open = 0;
    char ext[] = "MOLLEROptData.MOLLERDetectorEvent.";

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        file_open++;
        TTree *tree = (TTree*)file->Get("MOLLEROptTree");

        TCanvas *canvas_scint123 = new TCanvas("canvas_scint123","canvas_scint123");
        tree->Draw(Form("%sScint3HitY:%sScint3HitX",ext,ext),Form("(%sScint1TrackHit == 1) & (%sScint2TrackHit == 1)",ext,ext),"colz");
        canvas_scint123->SaveAs("plots/scint12_gem1_hitpos.root");

        TCanvas *canvas_scint124 = new TCanvas("canvas_scint124","canvas_scint124");
        tree->Draw(Form("%sScint4HitY:%sScint4HitX",ext,ext),Form("(%sScint1TrackHit == 1) & (%sScint2TrackHit == 1)",ext,ext),"colz");
        canvas_scint124->SaveAs("plots/scint12_gem2_hitpos.root");

        TCanvas *canvas_scint1234_gem1 = new TCanvas("canvas_scint1234_gem1","canvas_scint1234_gem1");
        tree->Draw(Form("%sScint3HitY:%sScint3HitX",ext,ext),Form("(%sScint1TrackHit == 1) & (%sScint2TrackHit == 1) & (%sScint4TrackHit == 1)",ext,ext,ext),"colz");
        canvas_scint1234_gem1->SaveAs("plots/scint1234_gem1_hitpos.root");

        TCanvas *canvas_scint1234_gem2 = new TCanvas("canvas_scint1234_gem2","canvas_scint1234_gem2");
        tree->Draw(Form("%sScint4HitY:%sScint4HitX",ext,ext),Form("(%sScint1TrackHit == 1) & (%sScint2TrackHit == 1) & (%sScint3TrackHit == 1)",ext,ext,ext),"colz");
        canvas_scint1234_gem2->SaveAs("plots/scint1234_gem2_hitpos.root");

        file->Close("R");
    }
}

void scint_slope_calc(){

    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;
    int pos, file_open = 0;
    float pi = TMath::Pi();
    char ext[] = "MOLLEROptData.MOLLERDetectorEvent.";

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        file_open++;
        TTree *tree = (TTree*)file->Get("MOLLEROptTree");
        // No conditions are used since slopex/y require hits on all scints+gems to store data
        TCanvas *canvas_scint1234_slope = new TCanvas("canvas_scint1234_slope","canvas_scint1234_slope");
        tree->Draw(Form("%sslopey:%sslopex",ext,ext),"","colz");
        canvas_scint1234_slope->SaveAs("plots/scint1234_slope_hitpos.root");

        TCanvas *canvas_scint1234_slopex = new TCanvas("canvas_scint1234_slopex","canvas_scint1234_slopex");
        tree->Draw(Form("%sslopex",ext),"");
        canvas_scint1234_slopex->SaveAs("plots/scint1234_slopex.root");

        TCanvas *canvas_scint1234_slopey = new TCanvas("canvas_scint1234_slopey","canvas_scint1234_slopey");
        tree->Draw(Form("%sslopey",ext),"");
        canvas_scint1234_slopey->SaveAs("plots/scint1234_slopey.root");

        file->Close("R");
    }
}