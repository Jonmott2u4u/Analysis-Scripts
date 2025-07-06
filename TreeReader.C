// This script uses a TTreeReader to access data within MOLLEROptical's tree
// Thanks to Sudip Bhattarai for showing me how to use TTreeReaders. So easy

#include "TFile.h"
#include "TH2.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"
#include <iostream>

using namespace std;

void plot_r5_pes_vs_pos() {
    // Open ROOT file
    TFile *f = TFile::Open("MOLLEROpt_0002.root");
    if (!f || f->IsZombie()) {
        cerr << "Error: Cannot open ROOT file!" << endl;
        return;
    }

    TTree *MOLLEROptTree = nullptr;
    f->GetObject("MOLLEROptTree", MOLLEROptTree);
    if (!MOLLEROptTree) {
        cerr << "Error: Cannot load MOLLEROptTree" << endl;
        return;
    }

    // Setup TTreeReader //
    //These readers are used to store the number of entries per position bin (w/ cuts included)
    TTreeReader reader_entries(MOLLEROptTree);
    TTreeReaderArray<float> R5TileHitX_ent(reader_entries, "MOLLERGeneralEvent.R5TileHitX");
    TTreeReaderArray<float> R5TileHitY_ent(reader_entries, "MOLLERGeneralEvent.R5TileHitY");
    TTreeReaderArray<int> Scint1TrackHit_ent(reader_entries, "MOLLERGeneralEvent.Scint1TrackHit");
    TTreeReaderArray<int> Scint2TrackHit_ent(reader_entries, "MOLLERGeneralEvent.Scint2TrackHit");
    TTreeReaderArray<int> R5AdjacentCutQuartzTrackHit_ent(reader_entries, "MOLLERGeneralEvent.R5AdjacentCutQuartzTrackHit");
    TTreeReaderArray<int> R5SoloCutQuartzTrackHit_ent(reader_entries, "MOLLERGeneralEvent.R5SoloCutQuartzTrackHit");
    //These readers are used for the "xy" histograms.
    TTreeReader reader_main(MOLLEROptTree);
    TTreeReaderArray<float> R5TileHitX(reader_main, "MOLLERGeneralEvent.R5TileHitX");
    TTreeReaderArray<float> R5TileHitY(reader_main, "MOLLERGeneralEvent.R5TileHitY");
    TTreeReaderArray<int> Scint1TrackHit(reader_main, "MOLLERGeneralEvent.Scint1TrackHit");
    TTreeReaderArray<int> Scint2TrackHit(reader_main, "MOLLERGeneralEvent.Scint2TrackHit");
    TTreeReaderArray<int> R5AdjacentCutQuartzTrackHit(reader_main, "MOLLERGeneralEvent.R5AdjacentCutQuartzTrackHit");
    TTreeReaderArray<int> R5SoloCutQuartzTrackHit(reader_main, "MOLLERGeneralEvent.R5SoloCutQuartzTrackHit");
    TTreeReaderArray<int> R5PEs(reader_main, "MOLLERGeneralEvent.R5PEs");

    // Prepare 2D histograms //
    //The "entry" plots store the number of hits per bin
    TH2F *h_entries = new TH2F("h_entries", "Entries per tile hit position",
                        8, -4, 4,  // X-axis binning
                        16, 18, 34);   // Y-axis binning
    TH2F *h_entries_adj = new TH2F("h_entries", "Entries per tile hit position",
                        8, -4, 4,  // X-axis binning
                        16, 18, 34);   // Y-axis binning
    TH2F *h_entries_solo = new TH2F("h_entries", "Entries per tile hit position",
                        8, -4, 4,  // X-axis binning
                        16, 18, 34);   // Y-axis binning
    //The "xy" plots store the average pe yield per bin
    TH2F *h_xy = new TH2F("h_xy", "R5TileHitY vs R5TileHitX w/ scint cut;X position;Y position",
                        8, -4, 4,  // X-axis binning
                        16, 18, 34);   // Y-axis binning
    TH2F *h_xy_adj = new TH2F("h_xy_adj", "R5TileHitY vs R5TileHitX w/ adjacency cut;X position;Y position",
                        8, -4, 4,  // X-axis binning
                        16, 18, 34);   // Y-axis binning
    TH2F *h_xy_solo = new TH2F("h_xy_solo", "R5TileHitY vs R5TileHitX w/ solocut;X position;Y position",
                        8, -4, 4,  // X-axis binning
                        16, 18, 34);   // Y-axis binning

    Long64_t event_count = 0;

    //Set the shift so that (shift + the x/y start bin above) = 1
    float x_shift = 5, y_shift = -17;


    // Loop over entries
    while (reader_entries.Next()) {
        event_count++;

        //Loops over the events once to create the weight factor per bin. Weight factor is = events per bin
        for (size_t i = 0; i < R5TileHitX_ent.GetSize(); ++i) {
            int scint1 = Scint1TrackHit_ent[i];
            int scint2 = Scint2TrackHit_ent[i];
            int adj = R5AdjacentCutQuartzTrackHit_ent[i];
            int solo = R5SoloCutQuartzTrackHit_ent[i];
            if (scint1 && scint2) {
                float x = R5TileHitX_ent[i];
                float y = R5TileHitY_ent[i];
                h_entries->Fill(x, y, 1);
                if (adj) h_entries_adj->Fill(x, y, 1);
                if (solo) h_entries_solo->Fill(x, y, 1);
                // cout << x << " " << y << " " << PEweight << endl;
            }
        }
    }

    while (reader_main.Next()) {
        //Loops over the events again to find the average pe yield per bin. Uses the weight factor defined above (h_entries*)
        for (size_t i = 0; i < R5TileHitX.GetSize(); ++i) {
            int scint1 = Scint1TrackHit[i];
            int scint2 = Scint2TrackHit[i];
            int adj = R5AdjacentCutQuartzTrackHit[i];
            int solo = R5SoloCutQuartzTrackHit[i];
            if (scint1 && scint2) {
                float x = R5TileHitX[i];
                float y = R5TileHitY[i];
                int PE = R5PEs[i];
                float weight = 1./h_entries->GetBinContent(x+x_shift,y+y_shift);
                h_xy->Fill(x, y, PE*weight);
                //cout << "x: " << x << "      y: " << y << endl;
                //cout << "PEs: " << PE << "      weight: " << weight << "        BinContent: " << h_xy->GetBinContent(x+x_shift,y+y_shift) << endl;
                if (adj) h_xy_adj->Fill(x, y, PE/h_entries_adj->GetBinContent(x+x_shift,y+y_shift));
                if (solo) h_xy_solo->Fill(x, y, PE/h_entries_solo->GetBinContent(x+x_shift,y+y_shift));
                // cout << x << " " << y << " " << PEweight << endl;
            }
        }
    }

    cout << "Total processed events: " << event_count << endl;

    // Draw and save histograms
    TCanvas *c1 = new TCanvas("c1", "R5 Tile Hit Map w/ scint cut", 900, 700);
    h_xy->Draw("COLZ");
    h_xy->GetZaxis()->SetRangeUser(0,45);
    c1->SaveAs("plots/ScintCut_R5TileHitXY_PE_heatmap.root");
    c1->SaveAs("plots/ScintCut_R5TileHitXY_PE_heatmap.png");
    c1->Close();

    TCanvas *c2 = new TCanvas("c2", "R5 Tile Hit Map w/ adjacency cut", 900, 700);
    h_xy_adj->Draw("COLZ");
    h_xy_adj->GetZaxis()->SetRangeUser(0,45);
    c2->SaveAs("plots/AdjCut_R5TileHitXY_PE_heatmap.root");
    c2->SaveAs("plots/AdjCut_R5TileHitXY_PE_heatmap.png");
    c2->Close();

    TCanvas *c3 = new TCanvas("c3", "R5 Tile Hit Map w/ solo cut", 900, 700);
    h_xy_solo->Draw("COLZ");
    h_xy_solo->GetZaxis()->SetRangeUser(0,45);
    c3->SaveAs("plots/SoloCut_R5TileHitXY_PE_heatmap.root");
    c3->SaveAs("plots/SoloCut_R5TileHitXY_PE_heatmap.png");
    c3->Close();
}