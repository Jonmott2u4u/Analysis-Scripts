#include <string>  
using namespace std;

void MainDet_Performance_LookupTable()
{

float yshift = -0.5;
int binsize = 5;
int entries = 0;
int det = 4;

if (det == 1){
    entries = 315;
}
else if (det == 2){
    entries = 629;
}
else if (det == 3){
    entries = 663;
}
else if (det == 4){
    entries = 1305;
}
else if (det == 5){
    entries = 561;
}
else if (det == 6){
    entries = 1325;
}
int total_entries = entries*3;

float h_pos[total_entries],v_pos[total_entries],mean[total_entries],rms[total_entries],mp_langau[total_entries],gsigma_langau[total_entries],rms_mean[total_entries],res_langau[total_entries],weight[total_entries];

char run_type[] = "";
char direction[] = "thetaY";

//Loading simulation data from MOLLEROptical txtfiles
//ifstream infileX;
ifstream infileY;
//infileX.open(Form("txtfiles/r%i_composite_%s.txt",det,direction));
infileY.open(Form("txtfiles/r%i_composite_%s.txt",det,direction));

//Creating the lookup table
//Certain position bins need to be manually changed after creation. The list is below:
//R1: h_pos = -85/85   -> -84.5/84.5
//R2: h_pos = -90/90   -> -89.5/89.5
//R4: h_pos = -110/110 -> -106.5/106.5
//R5: v_pos =  160     ->  157
ofstream LookupTable;
LookupTable.open(Form("csvfiles/r%i_LookupTable.csv",det));
LookupTable<<"Horizontal Bin Start [mm],"<<"Horizontal Bin End [mm],"<<"Vertical Bin Start [mm],"<<"Vertical Bin End [mm],"<<"Mean PEs,"<<"Langau PEs,"<<"RMS Over Mean,"<<"Resolution,"<<" Theta Fit Param p0,"<<"Theta Fit Param p1,"<<"Theta Fit param p2,"<<"\n";

//Loading simulation results
for (int i=0; i<total_entries; i++)
{
infileY>>h_pos[i]>>v_pos[i]>>mean[i]>>rms[i]>>mp_langau[i]>>gsigma_langau[i]>>rms_mean[i]>>res_langau[i]>>weight[i];
//cout << h_pos[i] << endl;
}

for (int entry=0; entry<entries; entry++){

    //..................Langau PE yield plot.................................//
    TGraph *langau_pes = new TGraph();
    langau_pes->GetXaxis()->SetTitle("Angle of Incidence [deg]");
    langau_pes->GetYaxis()->SetTitle("PE Yield");
    langau_pes->SetTitle(Form("PE Yield vs. Angle of Incidence for R%i at Xbin=%.1f & Ybin=%.1f",det,h_pos[entry],v_pos[entry]));
    for(int i=0; i<3; i++){
        langau_pes->SetPoint(i,i,mp_langau[entry + entries*i]);
    }
    langau_pes->GetXaxis()->SetTitle("Angle of Incidence [deg]");
    langau_pes->GetYaxis()->SetTitle("PE Yield");
    langau_pes->GetXaxis()->SetRangeUser(-1,3);
    langau_pes->GetYaxis()->SetRangeUser(0,40);
    langau_pes->SetMarkerStyle(21);

    TF1 *fit = new TF1("fit", "[0] + [1]*x + [2]*x*x", 0, 2);
    fit->SetParameter(0,mp_langau[entry]);
    fit->SetParameter(1,-.1);
    fit->SetParameter(2,0);
    langau_pes->Fit("fit","Q");
    langau_pes->SaveAs(Form("theta_dependence/r%i/%s_Xpos%.1f_Ypos%.1f.root",det,direction,h_pos[entry],v_pos[entry]));

    if (mp_langau[entry] == 0){
        fit->SetParameter(0,mp_langau[entry]);
        fit->SetParameter(1,0);
        fit->SetParameter(2,0);
    }
    if ((h_pos[entry] != h_pos[entries-1]) && v_pos[entry] != v_pos[entries-1]){
        LookupTable<<h_pos[entry]<<","<<h_pos[entry]+binsize<<","<<v_pos[entry]+yshift<<","<<v_pos[entry]+yshift+binsize<<","<<mean[entry]<<","<<mp_langau[entry]<<","<<rms_mean[entry]<<","<<res_langau[entry]<<","<<fit->GetParameter(0)<<","<<fit->GetParameter(1)<<","<<fit->GetParameter(2)<<"\n";
    }


    langau_pes->Delete();
    fit->Delete();
}

}