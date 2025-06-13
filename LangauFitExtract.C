//#include <fstream>
#include <iostream>
#include <TString.h>

Double_t langaufun(Double_t *x, Double_t *par);  
TF1 *langaufit(TH1D *his, Double_t *fitrange, Double_t *startvalues, Double_t *parlimitslo, Double_t *parlimitshi, Double_t *fitparams, Double_t *fiterrors, Double_t *ChiSqr, Int_t *NDF);
Int_t langaupro(Double_t *params, Double_t &maxx, Double_t &FWHM);
void DoFit(TH1D *hst, Double_t *fitP, Double_t *fitE);

TCanvas *C_mp = new TCanvas("C_mp","C_mp");

void LangauFitExtract()
{
  //gSystem->Load("libMOLLEROptDictionaries.so");

  std::ofstream ring_dat;       //Opens a txt file where info like mean PE's is stored. Was added to create data formatted for a specific script
  std::ofstream ring_dat_weighted;
  ring_dat.open ("r1.txt"); //Change the name to match the ring being analyzed, otherwise files will be overwritten
  ring_dat_weighted.open ("r1_w.txt");

  std::ifstream rfiles("notilt_files.dat");
  std::string line;
  TFile *file;

  Double_t paramx_start=0.0, paramy_start=0.0;     //Change based on what is being scanned
  Double_t paramx_step=5.0, paramy_step=1.0; //Increment for the horizontal axis
  Double_t limity=600.0;
  Int_t events=10000; //Total events per file
  
  TH1D *hst, *tmp, *hst2, *tmp2;
  TSpectrum *s = new TSpectrum(1);
  Double_t paramx_run, paramy_run, counterx, countery;
  Double_t y_clock;
  TString tmpStr;
  Double_t fitP[4], fitE[4];

  float mean, mp, rms, rms_mean, res;
  float w_mean, w_mp, w_rms, w_rms_mean, w_res;
  float weight, weight2, kk_scale, mean2;
  int no_run; //Flag for forcing the scaling plot to be zero.

  counterx=0, countery=0; 
  paramx_run = paramx_start;
  while(std::getline(rfiles, line)){

    file = TFile::Open(line.data()); 
    cout << line.data() << endl;
    //tmpStr = line.data();
    //tmpStr = tmpStr.ReplaceAll("MOLLEROpt_","");    
    
    paramy_run = paramy_start + countery*paramy_step;
    countery = countery + 1.0;

    tmp = (TH1D*)file->Get("R1_CathodeEventsDistrHist");  //Loads a histogram associated with a ring of the user's choice
    hst = (TH1D*)tmp->Clone("PEs");
    hst->SetTitle("Photoelectron Distribution");
    hst->GetXaxis()->SetTitle("Photoelectrons");
    hst->GetXaxis()->SetRangeUser(1,100);
    hst->SetDirectory(0);
    DoFit(hst,fitP,fitE);

        
    //Histogram parameters
    mean = hst->GetMean();
    rms = hst->GetRMS();
    mp = fitP[1];
    rms_mean = 100.*rms/mean;
    res = 100.*fitP[3]/fitP[1];
    //Conditions and misc. parameters
    //weight = (hst->GetEffectiveEntries())/(hst->GetEntries()); //Use w/ original version of MOLLEROpt
    weight = (hst->GetEntries())/(events); //Use w/ independent detector version of MOLLEROpt
    if((mean == 0) || (hst->GetRMS() == 0)) rms_mean = 0;
    if((mp < 0.5) || (fitP[3] < 0.5)) res = 0;
    //Event weighted variables
    w_mean = mean*weight;
    w_rms = rms*weight;
    w_rms_mean = rms_mean*weight;
    w_mp = mp*weight;
    w_res = res*weight;
    //Alternate scaling suggested by KK - Takes the ratio of one ring's signal to that of the ring directly US
    tmp2 = (TH1D*)file->Get("R2_CathodeEventsDistrHist");  //Loads a histogram associated with a ring of the user's choice
    hst2 = (TH1D*)tmp2->Clone("PEs_2");
    hst2->GetXaxis()->SetRangeUser(1,100);
    mean2 = hst2->GetMean();
    //weight2 = (hst2->GetEffectiveEntries())/(hst2->GetEntries());
    weight2 = (hst2->GetEntries())/(events);
    no_run = 0;
    //if(weight > 0.5) kk_scale = weight2/weight;
    //if(weight <= 0.5 || no_run == 1) kk_scale = 0.;
    if(mean2 > 1. & w_mean > 1.) kk_scale = weight2/weight;
    else kk_scale = 0;
    if(no_run == 1) kk_scale = 0.;

    //rms and gsigma are not weighted, but rms/mean and res are
    ring_dat<<paramx_run<<" "<<paramy_run<<" "<<mean<<" "<<rms<<" "<<mp<<" "<<fitP[3]<<" "<<rms_mean<<" "<<res<<" "<<1.0<<" "<<kk_scale<<"\n";
    ring_dat_weighted<<paramx_run<<" "<<paramy_run<<" "<<w_mean<<" "<<w_rms<<" "<<w_mp<<" "<<fitP[3]*weight<<" "<<w_rms_mean<<" "<<w_res<<" "<<weight<<" "<<kk_scale<<"\n";


    file->Close("R");    

    if (paramy_run == limity){
      paramx_run = paramx_start + counterx*paramx_step;
      counterx = counterx + 1.0;
      countery = 0.0;
    }

  }
  ring_dat.close();
  ring_dat_weighted.close();
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
      Double_t np = 1000.0;      // number of convolution steps
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
