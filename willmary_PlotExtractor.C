#include <iostream>
#include <TString.h>
#include <math.h>

void willmary_pes()
{
    std::ofstream analysis;
    analysis.open ("analyzed_files.dat");
    std::ifstream rfiles("files.dat");
    std::string line, str;
    TFile *file;
    TH1D *hst, *tmp;

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        for(int det=1; det<9; det++){

            //-------The following block is for muons striking any combination of scints---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%i_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n"; 

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iAdjacent_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iOnly_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //-------The following block is for muons striking scints 1 & 3---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_Scint13_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%i_Scint13_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_Scint13_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iAdjacent_Scint13_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_Scint13_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iOnly_Scint13_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //-------The following block is for muons striking scints 1 & 4---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_Scint14_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%i_Scint14_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_Scint14_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iAdjacent_Scint14_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_Scint14_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iOnly_Scint14_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //-------The following block is for muons striking scints 2 & 3---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_Scint23_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%i_Scint23_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_Scint23_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iAdjacent_Scint23_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_Scint23_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iOnly_Scint23_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //-------The following block is for muons striking scints 2 & 4---------//

            //PE spectrum of each detector with scintillator cuts (must hit one upstream and downstream scintillator)
            tmp = (TH1D*)file->Get(Form("R%i_Scint24_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%i_Scint24_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //PE spectrum of each detector that passes scint cut and does not hit adjacent detectors
            tmp = (TH1D*)file->Get(Form("R%iAdjacent_Scint24_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iAdjacent_Scint24_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

            //PE spectrum of each detector that passes scint cut and hits only one detector
            tmp = (TH1D*)file->Get(Form("R%iOnly_Scint24_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone("pes");
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetYaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            str = Form("plots/nofit/R%iOnly_Scint24_PEs.root",det);
            hst->SaveAs(str.data());
            analysis << str << "\n";

        }
        file->Close("R");
    }
    rfiles.close();
    analysis.close();
}

//This object performs cuts over the quartz in the x-direction
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
                canvas_pes->SaveAs(Form("plots/nofit/r%i/file%i_pes_pos_%i.root",det,file_open,pos));

                /*TCanvas *canvas_pos = new TCanvas("canvas_pos","canvas_pos");
                tree->Draw(Form("MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY:MOLLEROptData.MOLLERDetectorEvent.R%iTileHitX",det,det),Form("(MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY <= %i) && (MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY > %i-2)",det,pos,det,pos),"colz");
                canvas_pos->SaveAs(Form("plots/nofit/r%i/file%i_quartz_pos_%i.root",det,file_open,pos));*/

            }
        }
        file->Close("R");
    }
}