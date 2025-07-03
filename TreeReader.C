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

    // Setup TTreeReader
    TTreeReader reader(MOLLEROptTree);
    TTreeReaderArray<float> R5TileHitX(reader, "MOLLERGeneralEvent.R5TileHitX");
    TTreeReaderArray<float> R5TileHitY(reader, "MOLLERGeneralEvent.R5TileHitY");
    TTreeReaderArray<int> Scint1TrackHit(reader, "MOLLERGeneralEvent.Scint1TrackHit");
    TTreeReaderArray<int> Scint2TrackHit(reader, "MOLLERGeneralEvent.Scint2TrackHit");
    TTreeReaderArray<int> R5PEs(reader, "MOLLERGeneralEvent.R5PEs");

    // Prepare 2D histogram
    TH2F *h_xy = new TH2F("h_xy", "R5TileHitY vs R5TileHitX;X position;Y position",
                          10, -1.5, 1.5,  // X-axis binning
                          10, -25, 25);   // Y-axis binning

    Long64_t event_count = 0;

    // Loop over entries
    while (reader.Next()) {
        event_count++;

        for (size_t i = 0; i < R5TileHitX.GetSize(); ++i) {
            int scint1 = Scint1TrackHit[i];
            int scint2 = Scint2TrackHit[i];
            if (scint1 && scint2) {
                float x = R5TileHitX[i];
                float y = R5TileHitY[i];
                int PEweight = R5PEs[i];
                h_xy->Fill(x, y, PEweight);
                // cout << x << " " << y << " " << PEweight << endl;
            }
        }
    }

    cout << "Total processed events: " << event_count << endl;

    // Draw histogram
    TCanvas *c1 = new TCanvas("c1", "R5 Tile Hit Map", 900, 700);
    h_xy->Draw("COLZ");

    // Optionally save canvas
    c1->SaveAs("R5TileHitXY_PE_heatmap.root");
    c1->SaveAs("R5TileHitXY_PE_heatmap.png");
}
