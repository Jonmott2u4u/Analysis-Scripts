#include <iostream>
#include <TString.h>

void PlotExtractor()
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
            //hst->SaveAs(Form("plots/R%i_raw_spectrum.root",det));

            //PE spectrum for beams that hit only one quartz tile
            tmp = (TH1D*)file->Get(Form("R%iOnly_CathodeEventsDistrHist",det));
            hst = (TH1D*)tmp->Clone(Form("R%i_Solo_PEs",det));
            hst->SetTitle(Form("R%i Photoelectron Distribution",det));
            hst->GetXaxis()->SetTitle("Photoelectrons");
            hst->GetXaxis()->SetTitle("Events");
            hst->GetXaxis()->SetRangeUser(0,100);
            hst->SetDirectory(0);
            //hst->SaveAs(Form("plots/R%i_quartz_cut.root",det));

            TTree *tree = (TTree*)file->Get("MOLLEROptTree");
            cout << tree << endl;
            TCanvas *canvas = new TCanvas("canvas","canvas");
            tree->Draw(Form("MOLLEROptData.MOLLERDetectorEvent.R%iTileHitY:MOLLEROptData.MOLLERDetectorEvent.R%iTileHitX",det,det),"","colz");
            canvas->SaveAs(Form("R%i_quartz_hit_pos.root",det));
        }
        
        file->Close("R");
    }
}
