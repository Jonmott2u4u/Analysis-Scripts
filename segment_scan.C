void segment_scan()
{
float v_pos_r6[550],mean_r6[550],rms_r6[550],mp_langau_r6[550],gsigma_langau_r6[550],rms_mean_r6[550],res_langau_r6[550];

float v_pos_r5ff[550],mean_r5ff[550],rms_r5ff[550],mp_langau_r5ff[550],gsigma_langau_r5ff[550],rms_mean_r5ff[550],res_langau_r5ff[550];

float v_pos_r4[550],mean_r4[550],rms_r4[550],mp_langau_r4[550],gsigma_langau_r4[550],rms_mean_r4[550],res_langau_r4[550];

float v_pos_r3[550],mean_r3[550],rms_r3[550],mp_langau_r3[550],gsigma_langau_r3[550],rms_mean_r3[550],res_langau_r3[550];

float v_pos_r2[550],mean_r2[550],rms_r2[550],mp_langau_r2[550],gsigma_langau_r2[550],rms_mean_r2[550],res_langau_r2[550];

float v_pos_r1[550],mean_r1[550],rms_r1[550],mp_langau_r1[550],gsigma_langau_r1[550],rms_mean_r1[550],res_langau_r1[550];


ifstream infile_r6, infile_r5ff, infile_r4, infile_r3, infile_r2, infile_r1;
infile_r6.open("r6.txt");
infile_r5ff.open("r5.txt");
infile_r4.open("r4.txt");
infile_r3.open("r3.txt");
infile_r2.open("r2.txt");
infile_r1.open("r1.txt");


for (int i=0; i<550; i++)
{
infile_r6>>v_pos_r6[i]>>mean_r6[i]>>rms_r6[i]>>mp_langau_r6[i]>>gsigma_langau_r6[i]>>rms_mean_r6[i]>>res_langau_r6[i];
//cout << " ring 6 " << v_pos_r6[i] << " pe " << pe_langau_r6[i] << endl;
}
for (int i=0; i<550; i++)
{
infile_r5ff>>v_pos_r5ff[i]>>mean_r5ff[i]>>rms_r5ff[i]>>mp_langau_r5ff[i]>>gsigma_langau_r5ff[i]>>rms_mean_r5ff[i]>>res_langau_r5ff[i];
//cout << " ring 6 " << v_pos_r4[i] << " pe " << pe_langau_r4[i] << endl;
}
for (int i=0; i<550; i++)
{
infile_r4>>v_pos_r4[i]>>mean_r4[i]>>rms_r4[i]>>mp_langau_r4[i]>>gsigma_langau_r4[i]>>rms_mean_r4[i]>>res_langau_r4[i];
//cout << " ring 6 " << v_pos_r4[i] << " pe " << pe_langau_r4[i] << endl;
}
for (int i=0; i<550; i++)
{
infile_r3>>v_pos_r3[i]>>mean_r3[i]>>rms_r3[i]>>mp_langau_r3[i]>>gsigma_langau_r3[i]>>rms_mean_r3[i]>>res_langau_r3[i];
//cout << " ring 6 " << v_pos_r3[i] << " pe " << pe_langau_r3[i] << endl;
}
for (int i=0; i<550; i++)
{
infile_r2>>v_pos_r2[i]>>mean_r2[i]>>rms_r2[i]>>mp_langau_r2[i]>>gsigma_langau_r2[i]>>rms_mean_r2[i]>>res_langau_r2[i];
//cout << " ring 6 " << v_pos_r2[i] << " pe " << pe_langau_r2[i] << endl;
}
for (int i=0; i<550; i++)
{
infile_r1>>v_pos_r1[i]>>mean_r1[i]>>rms_r1[i]>>mp_langau_r1[i]>>gsigma_langau_r1[i]>>rms_mean_r1[i]>>res_langau_r1[i];
//cout << " ring 6 " << v_pos_r1[i] << " pe " << pe_langau_r1[i] << endl;
}


//..................Mean PE yield plots .................................//
TCanvas *c1 = new TCanvas();
TMultiGraph *mean_pes = new TMultiGraph();

TGraph *mean_pes_r6 = new TGraph (550,v_pos_r6,mean_r6);
mean_pes_r6->SetMarkerStyle(8);
mean_pes_r6->SetMarkerColor(kBlue);
mean_pes_r6->SetMarkerSize(1.5);

TGraph *mean_pes_r5ff = new TGraph (550,v_pos_r5ff,mean_r5ff);
mean_pes_r5ff->SetMarkerStyle(8);
mean_pes_r5ff->SetMarkerColor(kRed);
mean_pes_r5ff->SetMarkerSize(1.5);

TGraph *mean_pes_r4 = new TGraph (550,v_pos_r4,mean_r4);
mean_pes_r4->SetMarkerStyle(8);
mean_pes_r4->SetMarkerColor(kGreen+3);
mean_pes_r4->SetMarkerSize(1.5);

TGraph *mean_pes_r3 = new TGraph (550,v_pos_r3,mean_r3);
mean_pes_r3->SetMarkerStyle(8);
mean_pes_r3->SetMarkerColor(kOrange);
mean_pes_r3->SetMarkerSize(1.5);

TGraph *mean_pes_r2 = new TGraph (550,v_pos_r2,mean_r2);
mean_pes_r2->SetMarkerStyle(8);
mean_pes_r2->SetMarkerColor(kMagenta);
mean_pes_r2->SetMarkerSize(1.5);

TGraph *mean_pes_r1 = new TGraph (550,v_pos_r1,mean_r1);
mean_pes_r1->SetMarkerStyle(8);
mean_pes_r1->SetMarkerColor(kYellow);
mean_pes_r1->SetMarkerSize(1.5);

mean_pes->Add(mean_pes_r6,"p");
mean_pes->Add(mean_pes_r5ff,"p");
mean_pes->Add(mean_pes_r4,"p");
mean_pes->Add(mean_pes_r3,"p");
mean_pes->Add(mean_pes_r2,"p");
mean_pes->Add(mean_pes_r1,"p");
mean_pes->GetXaxis()->SetTitle("Vertical position [mm]");
mean_pes->GetYaxis()->SetTitle("PE yield (mean)");
mean_pes->SetTitle("Segment scan from start of R1 tile to the R6 lower lightguide");
mean_pes->GetXaxis()->SetLimits(0,550);
mean_pes->GetYaxis()->SetRangeUser(0,40);
mean_pes->Draw("A");
c1->SetGridx();
c1->SetGridy();

//..................Langau PE yield plots .................................//
TCanvas *c2 = new TCanvas();
TMultiGraph *langau_pes = new TMultiGraph();

TGraph *langau_pes_r6 = new TGraph (550,v_pos_r6,mp_langau_r6);
langau_pes_r6->SetMarkerStyle(8);
langau_pes_r6->SetMarkerColor(kBlue);
langau_pes_r6->SetMarkerSize(1.5);

TGraph *langau_pes_r5ff = new TGraph (550,v_pos_r5ff,mp_langau_r5ff);
langau_pes_r5ff->SetMarkerStyle(8);
langau_pes_r5ff->SetMarkerColor(kRed);
langau_pes_r5ff->SetMarkerSize(1.5);

TGraph *langau_pes_r4 = new TGraph (550,v_pos_r4,mp_langau_r4);
langau_pes_r4->SetMarkerStyle(8);
langau_pes_r4->SetMarkerColor(kGreen+3);
langau_pes_r4->SetMarkerSize(1.5);

TGraph *langau_pes_r3 = new TGraph (550,v_pos_r3,mp_langau_r3);
langau_pes_r3->SetMarkerStyle(8);
langau_pes_r3->SetMarkerColor(kOrange);
langau_pes_r3->SetMarkerSize(1.5);

TGraph *langau_pes_r2 = new TGraph (550,v_pos_r2,mp_langau_r2);
langau_pes_r2->SetMarkerStyle(8);
langau_pes_r2->SetMarkerColor(kMagenta);
langau_pes_r2->SetMarkerSize(1.5);

TGraph *langau_pes_r1 = new TGraph (550,v_pos_r1,mp_langau_r1);
langau_pes_r1->SetMarkerStyle(8);
langau_pes_r1->SetMarkerColor(kYellow);
langau_pes_r1->SetMarkerSize(1.5);

langau_pes->Add(langau_pes_r6,"p");
langau_pes->Add(langau_pes_r5ff,"p");
langau_pes->Add(langau_pes_r4,"p");
langau_pes->Add(langau_pes_r3,"p");
langau_pes->Add(langau_pes_r2,"p");
langau_pes->Add(langau_pes_r1,"p");
langau_pes->GetXaxis()->SetTitle("Vertical position [mm]");
langau_pes->GetYaxis()->SetTitle("PE yield (langau)");
langau_pes->SetTitle("Segment scan from start of R1 tile to the R6 lower lightguide");
langau_pes->GetXaxis()->SetLimits(0,550);
langau_pes->GetYaxis()->SetRangeUser(0,40);
langau_pes->Draw("A");
c2->SetGridx();
c2->SetGridy();

//..................RMS/Mean plots.................................//
TCanvas *c3 = new TCanvas();
TMultiGraph *RMS_mean = new TMultiGraph();

TGraph *RMS_mean_r6 = new TGraph (550,v_pos_r6,rms_mean_r6);
RMS_mean_r6->SetMarkerStyle(8);
RMS_mean_r6->SetMarkerColor(kBlue);
RMS_mean_r6->SetMarkerSize(1.5);

TGraph *RMS_mean_r5ff = new TGraph (550,v_pos_r5ff,rms_mean_r5ff);
RMS_mean_r5ff->SetMarkerStyle(8);
RMS_mean_r5ff->SetMarkerColor(kRed);
RMS_mean_r5ff->SetMarkerSize(1.5);

TGraph *RMS_mean_r4 = new TGraph (550,v_pos_r4,rms_mean_r4);
RMS_mean_r4->SetMarkerStyle(8);
RMS_mean_r4->SetMarkerColor(kGreen+3);
RMS_mean_r4->SetMarkerSize(1.5);

TGraph *RMS_mean_r3 = new TGraph (550,v_pos_r3,rms_mean_r3);
RMS_mean_r3->SetMarkerStyle(8);
RMS_mean_r3->SetMarkerColor(kOrange);
RMS_mean_r3->SetMarkerSize(1.5);

TGraph *RMS_mean_r2 = new TGraph (550,v_pos_r2,rms_mean_r2);
RMS_mean_r2->SetMarkerStyle(8);
RMS_mean_r2->SetMarkerColor(kMagenta);
RMS_mean_r2->SetMarkerSize(1.5);

TGraph *RMS_mean_r1 = new TGraph (550,v_pos_r1,rms_mean_r1);
RMS_mean_r1->SetMarkerStyle(8);
RMS_mean_r1->SetMarkerColor(kYellow);
RMS_mean_r1->SetMarkerSize(1.5);

RMS_mean->Add(RMS_mean_r6,"p");
RMS_mean->Add(RMS_mean_r5ff,"p");
RMS_mean->Add(RMS_mean_r4,"p");
RMS_mean->Add(RMS_mean_r3,"p");
RMS_mean->Add(RMS_mean_r2,"p");
RMS_mean->Add(RMS_mean_r1,"p");
RMS_mean->GetXaxis()->SetTitle("Vertical position [mm]");
RMS_mean->GetYaxis()->SetTitle("RMS/Mean");
RMS_mean->SetTitle("Segment scan from start of R1 tile to the R6 lower lightguide");
RMS_mean->GetXaxis()->SetLimits(0,550);
RMS_mean->GetYaxis()->SetRangeUser(0,50);
RMS_mean->Draw("A");
c3->SetGridx();
c3->SetGridy();

//..................Resolution plots.................................//
TCanvas *c4 = new TCanvas();
TMultiGraph *RES_langau = new TMultiGraph();

TGraph *RES_langau_r6 = new TGraph (550,v_pos_r6,res_langau_r6);
RES_langau_r6->SetMarkerStyle(8);
RES_langau_r6->SetMarkerColor(kBlue);
RES_langau_r6->SetMarkerSize(1.5);

TGraph *RES_langau_r5ff = new TGraph (550,v_pos_r5ff,res_langau_r5ff);
RES_langau_r5ff->SetMarkerStyle(8);
RES_langau_r5ff->SetMarkerColor(kRed);
RES_langau_r5ff->SetMarkerSize(1.5);

TGraph *RES_langau_r4 = new TGraph (550,v_pos_r4,res_langau_r4);
RES_langau_r4->SetMarkerStyle(8);
RES_langau_r4->SetMarkerColor(kGreen+3);
RES_langau_r4->SetMarkerSize(1.5);

TGraph *RES_langau_r3 = new TGraph (550,v_pos_r3,res_langau_r3);
RES_langau_r3->SetMarkerStyle(8);
RES_langau_r3->SetMarkerColor(kOrange);
RES_langau_r3->SetMarkerSize(1.5);

TGraph *RES_langau_r2 = new TGraph (550,v_pos_r2,res_langau_r2);
RES_langau_r2->SetMarkerStyle(8);
RES_langau_r2->SetMarkerColor(kMagenta);
RES_langau_r2->SetMarkerSize(1.5);

TGraph *RES_langau_r1 = new TGraph (550,v_pos_r1,res_langau_r1);
RES_langau_r1->SetMarkerStyle(8);
RES_langau_r1->SetMarkerColor(kYellow);
RES_langau_r1->SetMarkerSize(1.5);

RES_langau->Add(RES_langau_r6,"p");
RES_langau->Add(RES_langau_r5ff,"p");
RES_langau->Add(RES_langau_r4,"p");
RES_langau->Add(RES_langau_r3,"p");
RES_langau->Add(RES_langau_r2,"p");
RES_langau->Add(RES_langau_r1,"p");
RES_langau->GetXaxis()->SetTitle("Vertical position [mm]");
RES_langau->GetYaxis()->SetTitle("Resolution (langau)");
RES_langau->SetTitle("Segment scan from start of R1 tile to the R6 lower lightguide");
RES_langau->GetXaxis()->SetLimits(0,550);
RES_langau->GetYaxis()->SetRangeUser(0,50);
RES_langau->Draw("A");
c4->SetGridx();
c4->SetGridy();



//..................Printing the plots.................................//
c1->Print("plots/mean_PE_yield.png");
c2->Print("plots/langau_PE_yield.png");
c3->Print("plots/rms_mean.png");
c4->Print("plots/langau_res.png");

c1->Print("plots/mean_PE_yield.root");
c2->Print("plots/langau_PE_yield.root");
c3->Print("plots/rms_mean.root");
c4->Print("plots/langau_res.root");


/*
c1->Print("PE_yield_langau_vertical_54_r6_r5ff_r4.pdf");
c2->Print("PE_yield_gaus_vertical_54_r6_r5ff_r4.pdf");
c3->Print("reso_langau_vertical_54_r6_r5ff_r4.pdf");
c4->Print("reso_gaus_vertical_54_r6_r5ff_r4.pdf");
c5->Print("rms_mean_vertical_54_r6_r5ff_r4.pdf");


c1->Print("PE_yield_langau_vertical_54_r6_r5ff_r4.eps");
c2->Print("PE_yield_gaus_vertical_54_r6_r5ff_r4.eps");
c3->Print("reso_langau_vertical_54_r6_r5ff_r4.eps");
c4->Print("reso_gaus_vertical_54_r6_r5ff_r4.eps");
c5->Print("rms_mean_vertical_54_r6_r5ff_r4.eps");
*/
}
