//#include <fstream>
#include <iostream>
#include <TString.h>

Double_t langaufun(Double_t *x, Double_t *par);  
TF1 *langaufit(TH1D *his, Double_t *fitrange, Double_t *startvalues, Double_t *parlimitslo, Double_t *parlimitshi, Double_t *fitparams, Double_t *fiterrors, Double_t *ChiSqr, Int_t *NDF);
Int_t langaupro(Double_t *params, Double_t &maxx, Double_t &FWHM);
void DoFit(TH1D *hst, Double_t *fitP, Double_t *fitE);

TCanvas *C_mp = new TCanvas("C_mp","C_mp");

void Langau_WillMary()
{

  std::ifstream rfiles("analyzed_files.dat");
  std::string line;
  TFile *file;
  
  TH1D *hst, *tmp;
  TSpectrum *s = new TSpectrum(1);
  Int_t m;
  TString tmpStr;
  //Ssiz_t from = 0;
  Double_t fitP[4], fitE[4];

  while(std::getline(rfiles, line)){

    //from = 0;
    file = TFile::Open(line.data());
      
    cout << line.data() << endl;
    tmpStr = line.data();
    tmpStr = tmpStr.ReplaceAll("plots/nofit/","");//wherever your files happen to be

    tmp = (TH1D*)file->Get("pes");  //Loads a histogram associated with a ring of the user's choice
    
    hst = (TH1D*)tmp->Clone("Langau PEs");
    hst->SetTitle("Photoelectron Distribution");
    hst->GetXaxis()->SetTitle("Photoelectrons");
    hst->GetXaxis()->SetRangeUser(0,100);
    hst->SetDirectory(0);

    DoFit(hst,fitP,fitE);
    hst->SaveAs(Form("plots/Langau/Langau_%s",tmpStr.Data()));
    
    file->Close("R");    
  }
  rfiles.close();
}

void DoFit(TH1D *hst, Double_t *fitR, Double_t *fitE)
{

  //cout << "mean pe = " <<  s->GetPositionX()[0] << endl;
  TCanvas *cnv = new TCanvas();
  cnv->cd();
  hst->Draw();
 
  //Find peaks:
  int npeaks = 1;
  Double_t peaks_m[npeaks];
  Double_t peaks_h[npeaks];
  TSpectrum *s = new TSpectrum(2*npeaks);
  Int_t nfound2 = s->Search(hst,5,"",0.01);
  peaks_m[0] =  s->GetPositionX()[0];
  peaks_h[0] =  s->GetPositionY()[0];
  cout << "Event peak located at " << peaks_m[0] << " height = " << peaks_h[0] << endl;    
  cnv->Update();

  printf("Fitting...\n");
 
  // Setting fit range and start values
  Double_t fr[2];
  Double_t sv[4], pllo[4], plhi[4], fp[4], fpe[4];
  fr[0] = 0.6*peaks_m[0];
  fr[1] = 1.6*peaks_m[0];

  sv[0] = fr[1] - fr[0];
  sv[1] = peaks_m[0];
  sv[2] = peaks_h[0]*sv[0];
  sv[3] = peaks_m[0] - fr[0];
 
  pllo[0]=sv[0]/100;
  plhi[0]=sv[0]*4;
   
  pllo[1]=sv[1]-2*sv[3];
  plhi[1]=sv[1]+2*sv[3];
  
  pllo[2]=sv[2]/10;
  plhi[2]=sv[2]*10;
  
  pllo[3]=sv[3]/4;
  plhi[3]=sv[3]*4;
 
  Double_t chisqr;
  Int_t    ndf;
  TF1 *fitsnr = langaufit(hst,fr,sv,pllo,plhi,fp,fpe,&chisqr,&ndf);
 
  Double_t SNRPeak, SNRFWHM;
  langaupro(fp,SNRPeak,SNRFWHM);
 
  printf("Fitting done\nPlotting results...\n");

  for(int n = 0; n < 4; n++){
    fitR[n] = fp[n];
    fitE[n] = fpe[n];
    // cout << fp[n] << endl;
    // cout << fpe[n] << endl;
    
  }
 
  // Global style settings
  gStyle->SetOptStat(1111);
  gStyle->SetOptFit(111);
  gStyle->SetLabelSize(0.03,"x");
  gStyle->SetLabelSize(0.03,"y");
  
  //hst->GetXaxis()->SetRange(1,100);
  hst->Draw();
  fitsnr->Draw("lsame");
  

}


Double_t langaufun(Double_t *x, Double_t *par) {
 
   //Fit parameters:
   //par[0]=Width (scale) parameter of Landau density
   //par[1]=Most Probable (MP, location) parameter of Landau density
   //par[2]=Total area (integral -inf to inf, normalization constant)
   //par[3]=Width (sigma) of convoluted Gaussian function
   //
   //In the Landau distribution (represented by the CERNLIB approximation),
   //the maximum is located at x=-0.22278298 with the location parameter=0.
   //This shift is corrected within this function, so that the actual
   //maximum is identical to the MP parameter.
 
      // Numeric constants
      Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
      Double_t mpshift  = -0.22278298;       // Landau maximum location
 
      // Control constants
      Double_t np = 10000.0;      // number of convolution steps
      Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas
 
      // Variables
      Double_t xx;
      Double_t mpc;
      Double_t fland;
      Double_t sum = 0.0;
      Double_t xlow,xupp;
      Double_t step;
      Double_t i;
 
 
      // MP shift correction
      mpc = par[1] - mpshift * par[0];
 
      // Range of convolution integral
      xlow = x[0] - sc * par[3];
      xupp = x[0] + sc * par[3];
 
      step = (xupp-xlow) / np;
 
      // Convolution integral of Landau and Gaussian by sum
      for(i=1.0; i<=np/2; i++) {
         xx = xlow + (i-.5) * step;
         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
         sum += fland * TMath::Gaus(x[0],xx,par[3]);
 
         xx = xupp - (i-.5) * step;
         fland = TMath::Landau(xx,mpc,par[0]) / par[0];
         sum += fland * TMath::Gaus(x[0],xx,par[3]);
      }
 
      return (par[2] * step * sum * invsq2pi / par[3]);
}
 
 
 
TF1 *langaufit(TH1D *his, Double_t *fitrange, Double_t *startvalues, Double_t *parlimitslo, Double_t *parlimitshi, Double_t *fitparams, Double_t *fiterrors, Double_t *ChiSqr, Int_t *NDF)
{
   // Once again, here are the Landau * Gaussian parameters:
   //   par[0]=Width (scale) parameter of Landau density
   //   par[1]=Most Probable (MP, location) parameter of Landau density
   //   par[2]=Total area (integral -inf to inf, normalization constant)
   //   par[3]=Width (sigma) of convoluted Gaussian function
   //
   // Variables for langaufit call:
   //   his             histogram to fit
   //   fitrange[2]     lo and hi boundaries of fit range
   //   startvalues[4]  reasonable start values for the fit
   //   parlimitslo[4]  lower parameter limits
   //   parlimitshi[4]  upper parameter limits
   //   fitparams[4]    returns the final fit parameters
   //   fiterrors[4]    returns the final fit errors
   //   ChiSqr          returns the chi square
   //   NDF             returns ndf
 
   Int_t i;
   Char_t FunName[100];
 
   sprintf(FunName,"Fitfcn_%s",his->GetName());
 
   TF1 *ffitold = (TF1*)gROOT->GetListOfFunctions()->FindObject(FunName);
   if (ffitold) delete ffitold;
 
   TF1 *ffit = new TF1(FunName,langaufun,fitrange[0],fitrange[1],4);
   ffit->SetParameters(startvalues);
   ffit->SetParNames("Width","MP","Area","GSigma");
 
   for (i=0; i<4; i++) {
      ffit->SetParLimits(i, parlimitslo[i], parlimitshi[i]);
   }
 
   his->Fit(FunName,"RB0");   // fit within specified range, use ParLimits, do not plot
 
   ffit->GetParameters(fitparams);    // obtain fit parameters
   for (i=0; i<4; i++) {
      fiterrors[i] = ffit->GetParError(i);     // obtain fit parameter errors
   }
   ChiSqr[0] = ffit->GetChisquare();  // obtain chi^2
   NDF[0] = ffit->GetNDF();           // obtain ndf
 
   return (ffit);              // return fit function
 
}

Int_t langaupro(Double_t *params, Double_t &maxx, Double_t &FWHM) {
 
   // Seaches for the location (x value) at the maximum of the
   // Landau-Gaussian convolute and its full width at half-maximum.
   //
   // The search is probably not very efficient, but it's a first try.
 
   Double_t p,x,fy,fxr,fxl;
   Double_t step;
   Double_t l,lold;
   Int_t i = 0;
   Int_t MAXCALLS = 10000;
 
 
   // Search for maximum
 
   p = params[1] - 0.1 * params[0];
   step = 0.05 * params[0];
   lold = -2.0;
   l    = -1.0;
 
 
   while ( (l != lold) && (i < MAXCALLS) ) {
      i++;
 
      lold = l;
      x = p + step;
      l = langaufun(&x,params);
 
      if (l < lold)
         step = -step/10;
 
      p += step;
   }
 
   if (i == MAXCALLS)
      return (-1);
 
   maxx = x;
 
   fy = l/2;
 
 
   // Search for right x location of fy
 
   p = maxx + params[0];
   step = params[0];
   lold = -2.0;
   l    = -1e300;
   i    = 0;
 
 
   while ( (l != lold) && (i < MAXCALLS) ) {
      i++;
 
      lold = l;
      x = p + step;
      l = TMath::Abs(langaufun(&x,params) - fy);
 
      if (l > lold)
         step = -step/10;
 
      p += step;
   }
 
   if (i == MAXCALLS)
      return (-2);
 
   fxr = x;
 
 
   // Search for left x location of fy
 
   p = maxx - 0.5 * params[0];
   step = -params[0];
   lold = -2.0;
   l    = -1e300;
   i    = 0;
 
   while ( (l != lold) && (i < MAXCALLS) ) {
      i++;
 
      lold = l;
      x = p + step;
      l = TMath::Abs(langaufun(&x,params) - fy);
 
      if (l > lold)
         step = -step/10;
 
      p += step;
   }
 
   if (i == MAXCALLS)
      return (-3);
 
 
   fxl = x;
 
   FWHM = fxr - fxl;
   return (0);
}
