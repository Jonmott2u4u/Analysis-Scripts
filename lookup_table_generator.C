void lookup_table_generator()
{

int entries = 315;
int binsize = 5;
int det = 1;
int angle = 0;
float yshift = -0.5;

//Certain position bins need to be manually changed after creation. The list is below:
//R1: h_pos = -85/85   -> -84.5/84.5
//R2: h_pos = -90/90   -> -89.5/89.5
//R4: h_pos = -110/110 -> -106.5/106.5
//R5: v_pos =  160     ->  157

float h_pos[entries],v_pos[entries],mean[entries],rms[entries],mp_langau[entries],gsigma_langau[entries],rms_mean[entries],res_langau[entries],weight[entries];

char run_type[] = "r1";
char weighted[] = ""; //"_w" for weighted runs, "" for no weight
char direction[] = "thetaNo";

ifstream infile;
infile.open(Form("txtfiles/r%i_%ideg_%s%s.txt",det,angle,direction,weighted));

ofstream outfile;
outfile.open(Form("csvfiles/r%i/%ideg_%s%s.csv",det,angle,direction,weighted));

//Loading simulation results
for (int i=0; i<entries; i++)
{
infile>>h_pos[i]>>v_pos[i]>>mean[i]>>rms[i]>>mp_langau[i]>>gsigma_langau[i]>>rms_mean[i]>>res_langau[i]>>weight[i];

}

//Taking a subset of the above data and moving it into a .csv file
outfile<<"Horizontal Bin Start [mm],"<<"Horizontal Bin End [mm],"<<"Vertical Bin Start [mm],"<<"Vertical Bin End [mm],"<<"Angle of Incidence [degrees],"<<"Mean PEs,"<<"Langau PEs,"<<"RMS Over Mean,"<<"Resolution,"<<"\n";
for (int i=0; i<entries; i++)
{
if ((h_pos[i] != h_pos[entries-1]) && v_pos[i] != v_pos[entries-1])
    outfile<<h_pos[i]<<","<<h_pos[i]+binsize<<","<<v_pos[i]+yshift<<","<<v_pos[i]+yshift+binsize<<","<<angle<<","<<mean[i]<<","<<mp_langau[i]<<","<<rms_mean[i]<<","<<res_langau[i]<<"\n";
}


}
