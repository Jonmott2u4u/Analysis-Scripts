#include <iostream>
#include <fstream>
#include <TString.h>

void cosmic_muon_spectra()
{
//P. Shukla et al., arXiv: 1606.06907v3
int k=0, entries=1e3;
float i_not, n1, e_not, x, n2, e_c, epsilon;
float i[1000], energy[1000];

x = 0.10;
i_not=70.7;//m^-2s^-1sr^-1
e_not=4.29;//GeV
n2=3.01;
e_c=0.2;//GeV
epsilon=854.0;//GeV
n1=(n2-1.0)*pow((e_not+e_c),(n2-1.0));

while (x<=100)
{
i[k] = i_not*n1*pow((e_not+x),-n2)*1.0/(1.0 + (x/epsilon));
energy[k]=x;
x=x+0.10;
k++;
}

int int_flux[1000];
float weighted_flux[1000];
int j=0;
float y=0.10;

while (y<=100)
{
int_flux[j] = i[j]/i[k-1];
weighted_flux[j] = i[j]/i[k-1];
y=y+0.10;
j++;
}

TCanvas *c1 = new TCanvas();
TGraph *gr = new TGraph (entries,energy,weighted_flux);
gr->Draw();
c1->SetLogx();
c1->SetLogy();
gr->SetTitle("");
gr->GetXaxis()->SetTitle("E (GeV)");
gr->GetYaxis()->SetTitle("Muon flux (m^{-2}sec^{-1}sr^{-1} (GeV/c)^{-1})");

}
