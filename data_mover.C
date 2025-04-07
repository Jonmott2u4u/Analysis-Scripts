void data_mover()
{
float v_pos_r6[1000],mean_r6[1000],rms_r6[1000],mp_langau_r6[1000],gsigma_langau_r6[1000],rms_mean_r6[1000],res_langau_r6[1000],weight_r6[1000],scale_r6[1000];
float v_pos_r5ff[1000],mean_r5ff[1000],rms_r5ff[1000],mp_langau_r5ff[1000],gsigma_langau_r5ff[1000],rms_mean_r5ff[1000],res_langau_r5ff[1000],weight_r5ff[1000],scale_r5ff[1000];
float v_pos_r4[1000],mean_r4[1000],rms_r4[1000],mp_langau_r4[1000],gsigma_langau_r4[1000],rms_mean_r4[1000],res_langau_r4[1000],weight_r4[1000],scale_r4[1000];
float v_pos_r3[1000],mean_r3[1000],rms_r3[1000],mp_langau_r3[1000],gsigma_langau_r3[1000],rms_mean_r3[1000],res_langau_r3[1000],weight_r3[1000],scale_r3[1000];
float v_pos_r2[1000],mean_r2[1000],rms_r2[1000],mp_langau_r2[1000],gsigma_langau_r2[1000],rms_mean_r2[1000],res_langau_r2[1000],weight_r2[1000],scale_r2[1000];
float v_pos_r1[1000],mean_r1[1000],rms_r1[1000],mp_langau_r1[1000],gsigma_langau_r1[1000],rms_mean_r1[1000],res_langau_r1[1000],weight_r1[1000],scale_r1[1000];

char run_type[] = "r1_center";
char weight[] = "_w"; //"_w" for weighted runs, "" for no weight

ifstream infile_r6, infile_r5ff, infile_r4, infile_r3, infile_r2, infile_r1;
infile_r6.open(Form("txt_files/%s/r6%s.txt",run_type,weight));
infile_r5ff.open(Form("txt_files/%s/r5%s.txt",run_type,weight));
infile_r4.open(Form("txt_files/%s/r4%s.txt",run_type,weight));
infile_r3.open(Form("txt_files/%s/r3%s.txt",run_type,weight));
infile_r2.open(Form("txt_files/%s/r2%s.txt",run_type,weight));
infile_r1.open(Form("txt_files/%s/r1%s.txt",run_type,weight));

ofstream outfile;
outfile.open(Form("csv_files/%s_beam.csv",run_type));

//Loading simulation results
// i_max = quartz radial length + bevel radial length + 20mm (10 above bevel, 10 below butt of tile)
// for LG signals, set i_max = 1000
for (int i=0; i<1000; i++)
{
infile_r6>>v_pos_r6[i]>>mean_r6[i]>>rms_r6[i]>>mp_langau_r6[i]>>gsigma_langau_r6[i]>>rms_mean_r6[i]>>res_langau_r6[i]>>weight_r6[i]>>scale_r6[i];
//cout << " ring 6 " << v_pos_r6[i] << " pe " << mp_langau_r6[i] << endl;
}
for (int i=0; i<1000; i++)
{
infile_r5ff>>v_pos_r5ff[i]>>mean_r5ff[i]>>rms_r5ff[i]>>mp_langau_r5ff[i]>>gsigma_langau_r5ff[i]>>rms_mean_r5ff[i]>>res_langau_r5ff[i]>>weight_r5ff[i]>>scale_r5ff[i];
}
for (int i=0; i<1000; i++)
{
infile_r4>>v_pos_r4[i]>>mean_r4[i]>>rms_r4[i]>>mp_langau_r4[i]>>gsigma_langau_r4[i]>>rms_mean_r4[i]>>res_langau_r4[i]>>weight_r4[i]>>scale_r4[i];
}
for (int i=0; i<1000; i++)
{
infile_r3>>v_pos_r3[i]>>mean_r3[i]>>rms_r3[i]>>mp_langau_r3[i]>>gsigma_langau_r3[i]>>rms_mean_r3[i]>>res_langau_r3[i]>>weight_r3[i]>>scale_r3[i];
}
for (int i=0; i<1000; i++)
{
infile_r2>>v_pos_r2[i]>>mean_r2[i]>>rms_r2[i]>>mp_langau_r2[i]>>gsigma_langau_r2[i]>>rms_mean_r2[i]>>res_langau_r2[i]>>weight_r2[i]>>scale_r2[i];
}
for (int i=0; i<1000; i++)
{
infile_r1>>v_pos_r1[i]>>mean_r1[i]>>rms_r1[i]>>mp_langau_r1[i]>>gsigma_langau_r1[i]>>rms_mean_r1[i]>>res_langau_r1[i]>>weight_r1[i]>>scale_r1[i];
}

//Taking a subset of the above data and moving it into a .csv file.
//Currently taking the weight and weighted mean pes for each detector in each setup
outfile<<"Gamma_Energy_[MeV],"<<"R6_Response_Prob,"<<"R5_Response_Prob,"<<"R4_Response_Prob,"<<"R3_Response_Prob,"<<"R2_Response_Prob,"<<"R1_Response_Prob,"<<"R6_Mean_PEs,"<<"R5_Mean_PEs,"<<"R4_Mean_PEs,"<<"R3_Mean_PEs,"<<"R2_Mean_PEs,"<<"R1_Mean_PEs"<<"\n";
for (int i=1; i<100; i++)
{
outfile<<v_pos_r6[i*10-2]<<","<<weight_r6[i*10-2]<<","<<weight_r5ff[i*10-2]<<","<<weight_r4[i*10-2]<<","<<weight_r3[i*10-2]<<","<<weight_r2[i*10-2]<<","<<weight_r1[i*10-2]<<","<<mean_r6[i*10-2]<<","<<mean_r5ff[i*10-2]<<","<<mean_r4[i*10-2]<<","<<mean_r3[i*10-2]<<","<<mean_r2[i*10-2]<<","<<mean_r1[i*10-2]<<"\n";
}


}
