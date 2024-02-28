void cosmic_muon_spectra()
{
//P. Shukla et al., arXiv: 1606.06907v3
int k=0;
float i_not, n1, e_not, x, n2, e_c, epsilon;
float i[1000000], energy[1000000];
x = 0.0;
i_not=70.7;//m^-2s^-1sr^-1
e_not=4.29;//GeV
n2=3.01;
n1=(n2-1)*pow((e_not+e_c),(n2-1));
e_c=0.5;//GeV
epsilon=854.0;//GeV

while (x<1000)
{
i[k] = i_not * n1 * pow((e_not+x),-n2) * 1.0/((1.0 + (x/epsilon)));
energy[k]=x;
x=x+0.10;
k++;
}

TCanvas *c1 = new TCanvas();
TGraph *gr = new TGraph (1e4,energy,i);
gr->Draw();
c1->SetLogx();
c1->SetLogy();
gr->SetTitle("");
gr->GetXaxis()->SetTitle("E (GeV)");
gr->GetYaxis()->SetTitle("Muon flux (m^{-2}sec^{-1}sr^{-1} (GeV/c)^{-1})");
}
