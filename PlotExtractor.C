#include <iostream>
#include <TString.h>

void PlotExtractor_pes()
{
    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        for(int det=1; det<9; det++){

            //Unedited PE spectrums
            tmp = (TH1D*)file->Get(Form("R%i_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetXaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_raw_spectrum.root",det));

            //PE spectrum for beams that hit only one quartz tile
            tmp = (TH1D*)file->Get(Form("R%iOnly_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_Solo_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetXaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            hst->SaveAs(Form("plots/R%i_quartz_cut.root",det));

            /*TTree *tree = (TTree*)file->Get("MOLLEROptTree");
            cout << tree << endl;
            TCanvas *canvas = new TCanvas("canvas","canvas");
            tree->Draw(Form("MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY:MOLLEROptData.MOLLERDetectorEvent.R%iTileHitX",det,det),Form("MOLLEROptData.MOLLERDetectorEvent.INSERT-VARIABLE-HERE CONDITION",det),"colz");
            canvas->SaveAs(Form("R%i_quartz_hit_pos.root",det));*/
        }
        file->Close("R");
    }
}

//This object performs cuts over the quartz in the x-direction in 1 cm increments. Goal is to see position dependence of PE yield, among other things
void PlotExtractor_quartzcut{

    std::ifstream rfiles("files.dat");
    std::string line;
    TFile *file;
    TH1D *hst, *tmp;
    int pos, file = 0;

    while(std::getline(rfiles, line)){
        file = TFile::Open(line.data());
        file++;
        for(int det=1; det<9; det++){
            pos = -13;
            while(pos <= 12){
                pos++;
                TTree *tree = (TTree*)file->Get("MOLLEROptTree");
                TCanvas *canvas_pes = new TCanvas("canvas_pes","canvas_pes");
                tree->Draw(Form("MOLLEROptData.MOLLERDetectorEvent.R%iSoloPEs",det),Form("(MOLLEROptData.MOLLERDetectorEvent.R%iTileHitX <= %i) && (MOLLEROptData.MOLLERDetectorEvent.R%iTileHitX > %i-1)",det,pos,det,pos),"goff");
                canvas_pes->SaveAs(Form("plots/r%i/file%i_pes_pos_%i.root",det,file,pos));

                TCanvas *canvas_pos = new TCanvas("canvas_pos","canvas_pos");
                tree->Draw(Form("MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY:MOLLEROptData.MOLLERDetectorEvent.R%iTileHitX",det,det),Form("(MOLLEROptData.MOLLERDetectorEvent.R%iTileHitX <= %i) && (MOLLEROptData.MOLLERDetectorEvent.R%iTileHitX > %i-1)",det,pos,det,pos),"goff");
                canvas_pos->SaveAs(Form("plots/r%i/file%i_quartz_pos_%i.root",det,file,pos));

            }
        }
    }
}
