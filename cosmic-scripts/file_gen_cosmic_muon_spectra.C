#include <iostream>
#include <fstream>

void file_gen_cosmic_muon_spectra()
{
//P. Shukla et al., arXiv: 1606.06907v3
int k=0, entries=1e3;
float i_not, n1, e_not, x, n2, e_c, epsilon, old_energy = 0;
float i[1000], energy[1000];

ofstream data1, data2;
//data1.open ("cosmics_long.dat"); //.dat file containing energy values according to weight (more appearances = higher flux)
data2.open ("cosmics.txt");

x = 0.10;
//The below settings are for Tsukuba, Japan (36.2 N, 140.1 W)
//Used for Amherst Massachusetts (32.9 N, 11.5 W)
//Williamsburg, Virginia (32.0 N, 32.5 W) also seems fine
i_not=70.7;//m^-2s^-1sr^-1
e_not=4.29;//GeV
n2=3.01;
e_c=0.2;//GeV
epsilon=854.0;//GeV
n1=(n2-1.0)*pow((e_not+e_c),(n2-1.0));
//For different latitudes, see https://arxiv.org/pdf/1606.06907, page 11 table 1

while (x<=100)
{
    i[k] = i_not*n1*pow((e_not+x),-n2)*1.0/(1.0 + (x/epsilon));
    energy[k]=x;
    x=x+0.10;
    k++;
}

int int_flux[1000];
float weighted_flux[1000];
int j=0, n=0;
float y=0.10;


while (y<=10.1)
{
    int_flux[j] = i[j]/i[k-1];
    weighted_flux[j] = i[j]/i[k-1];
    int z=0;
    while (z<int_flux[j])
    {
        //data1 << energy[j]*1000 << "\n";//Stores energy in MeV
        z++;
        n++;
        if(z == int_flux[j]){
            data2 << energy[j]*1000 << " " << n << "\n";
        }
    }
    y=y+0.10;
    j++;
}
//data1.close();
data2.close();


TCanvas *c1 = new TCanvas();
//TGraph *gr = new TGraph (entries,energy,i);
TGraph *gr = new TGraph (entries,energy,weighted_flux);
gr->Draw();
c1->SetLogx();
c1->SetLogy();
gr->SetTitle("");
gr->GetXaxis()->SetTitle("E (GeV)");
gr->GetYaxis()->SetTitle("Muon flux (m^{-2}sec^{-1}sr^{-1} (GeV/c)^{-1})");
}
