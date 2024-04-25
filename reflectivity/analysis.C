#include <TROOT.h>
#include <TTree.h>
#include <TH1.h>
#include <TH2.h>
#include <TFile.h>
#include <TF1.h>
#include <TStyle.h>
#include <TColor.h>
#include <TGaxis.h>
#include <TCanvas.h>
#include <TPaveLabel.h>
#include <TPaveText.h>
#include <TGraphErrors.h>
#include <iostream>
using namespace std;

const float pi = 3.1415926;

int analysis(int angle)  
{

  //Define parameters common to all analysis configurations

  const Int_t points = 2048;
  const Int_t files = 79;
  const int std = 54; //file index (starts with 0) for NIST standard run

  char printname[256];
  char graphname1[256];
  char xTitle[256];
  char yTitle[256];
  char GraphText1[256];
  char histTitle[256];

  char output_line[256];

  gStyle->SetStatColor(0);//All this stuff makes backgrounds, etc.
  gStyle->SetTitleColor(0);//transparent for printing purposes...
  gStyle->SetCanvasColor(0);
  gStyle->SetPadColor(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetCanvasBorderMode(0);
  gStyle->SetFrameBorderMode(0);
  gStyle->SetPalette(1);
  //gStyle->SetOptDate(1);
  //gStyle->SetOptStat(kFALSE);
  gStyle->SetOptStat(11);
  gStyle->SetOptFit(1111);
  gStyle->SetPadGridX(kTRUE);
  gStyle->SetPadGridY(kTRUE);
  
  TGaxis::SetMaxDigits(3);

  //Open Input file which stores reflectivity data

  char INPUT_FILENAME[files][256];
  sprintf(INPUT_FILENAME[0],"data/2000_1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[0]);
  ifstream myInFile0(INPUT_FILENAME[0]);

  sprintf(INPUT_FILENAME[1],"data/2000_2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[1]);
  ifstream myInFile1(INPUT_FILENAME[1]);

  sprintf(INPUT_FILENAME[2],"data/2000_3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[2]);
  ifstream myInFile2(INPUT_FILENAME[2]);

  sprintf(INPUT_FILENAME[3],"data/2000_4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[3]);
  ifstream myInFile3(INPUT_FILENAME[3]);

  sprintf(INPUT_FILENAME[4],"data/2000_30.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[4]);
  ifstream myInFile4(INPUT_FILENAME[4]);

  sprintf(INPUT_FILENAME[5],"data/2000_45.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[5]);
  ifstream myInFile5(INPUT_FILENAME[5]);

  sprintf(INPUT_FILENAME[6],"data/2000_60.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[6]);
  ifstream myInFile6(INPUT_FILENAME[6]);

  sprintf(INPUT_FILENAME[7],"data/2000_45diffuse.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[7]);
  ifstream myInFile7(INPUT_FILENAME[7]);

  sprintf(INPUT_FILENAME[8],"data/4270_1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[8]);
  ifstream myInFile8(INPUT_FILENAME[8]);

  sprintf(INPUT_FILENAME[9],"data/4270_2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[9]);
  ifstream myInFile9(INPUT_FILENAME[9]);

  sprintf(INPUT_FILENAME[10],"data/4270_3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[10]);
  ifstream myInFile10(INPUT_FILENAME[10]);

  sprintf(INPUT_FILENAME[11],"data/4270_4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[11]);
  ifstream myInFile11(INPUT_FILENAME[11]);

  sprintf(INPUT_FILENAME[12],"data/4270_30.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[12]);
  ifstream myInFile12(INPUT_FILENAME[12]);

  sprintf(INPUT_FILENAME[13],"data/4270_45.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[13]);
  ifstream myInFile13(INPUT_FILENAME[13]);

  sprintf(INPUT_FILENAME[14],"data/4270_60.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[14]);
  ifstream myInFile14(INPUT_FILENAME[14]);

  sprintf(INPUT_FILENAME[15],"data/alzakAg1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[15]);
  ifstream myInFile15(INPUT_FILENAME[15]);

  sprintf(INPUT_FILENAME[16],"data/alzakAg2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[16]);
  ifstream myInFile16(INPUT_FILENAME[16]);

  sprintf(INPUT_FILENAME[17],"data/alzakAg30.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[17]);
  ifstream myInFile17(INPUT_FILENAME[17]);

  sprintf(INPUT_FILENAME[18],"data/alzakAg45.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[18]);
  ifstream myInFile18(INPUT_FILENAME[18]);

  sprintf(INPUT_FILENAME[19],"data/alzakAg60.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[19]);
  ifstream myInFile19(INPUT_FILENAME[19]);

  sprintf(INPUT_FILENAME[20],"data/alzakAl1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[20]);
  ifstream myInFile20(INPUT_FILENAME[20]);

  sprintf(INPUT_FILENAME[21],"data/alzakAl2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[21]);
  ifstream myInFile21(INPUT_FILENAME[21]);

  sprintf(INPUT_FILENAME[22],"data/alzakAl30.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[22]);
  ifstream myInFile22(INPUT_FILENAME[22]);

  sprintf(INPUT_FILENAME[23],"data/alzakAl45.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[23]);
  ifstream myInFile23(INPUT_FILENAME[23]);

  sprintf(INPUT_FILENAME[24],"data/alzakAl60.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[24]);
  ifstream myInFile24(INPUT_FILENAME[24]);

  sprintf(INPUT_FILENAME[25],"data/anoluxI1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[25]);
  ifstream myInFile25(INPUT_FILENAME[25]);

  sprintf(INPUT_FILENAME[26],"data/anoluxI2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[26]);
  ifstream myInFile26(INPUT_FILENAME[26]);

  sprintf(INPUT_FILENAME[27],"data/anoluxI3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[27]);
  ifstream myInFile27(INPUT_FILENAME[27]);

  sprintf(INPUT_FILENAME[28],"data/anoluxI4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[28]);
  ifstream myInFile28(INPUT_FILENAME[28]);

  sprintf(INPUT_FILENAME[29],"data/anoluxI45diffuse.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[29]);
  ifstream myInFile29(INPUT_FILENAME[29]);

  sprintf(INPUT_FILENAME[30],"data/bogdanMylar_brightest.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[30]);
  ifstream myInFile30(INPUT_FILENAME[30]);

  sprintf(INPUT_FILENAME[31],"data/bogdanMylar1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[31]);
  ifstream myInFile31(INPUT_FILENAME[31]);

  sprintf(INPUT_FILENAME[32],"data/bogdanMylar2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[32]);
  ifstream myInFile32(INPUT_FILENAME[32]);

  sprintf(INPUT_FILENAME[33],"data/bogdanMylar3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[33]);
  ifstream myInFile33(INPUT_FILENAME[33]);

  sprintf(INPUT_FILENAME[34],"data/bogdanMylar4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[34]);
  ifstream myInFile34(INPUT_FILENAME[34]);

  sprintf(INPUT_FILENAME[35],"data/lightoffcalibration.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[35]);
  ifstream myInFile35(INPUT_FILENAME[35]);

  sprintf(INPUT_FILENAME[36],"data/miro27_1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[36]);
  ifstream myInFile36(INPUT_FILENAME[36]);

  sprintf(INPUT_FILENAME[37],"data/miro27_2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[37]);
  ifstream myInFile37(INPUT_FILENAME[37]);

  sprintf(INPUT_FILENAME[38],"data/miro27_3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[38]);
  ifstream myInFile38(INPUT_FILENAME[38]);

  sprintf(INPUT_FILENAME[39],"data/miro27_4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[39]);
  ifstream myInFile39(INPUT_FILENAME[39]);

  sprintf(INPUT_FILENAME[40],"data/miro27_30.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[40]);
  ifstream myInFile40(INPUT_FILENAME[40]);

  sprintf(INPUT_FILENAME[41],"data/miro27_45.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[41]);
  ifstream myInFile41(INPUT_FILENAME[41]);

  sprintf(INPUT_FILENAME[42],"data/miro27_60.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[42]);
  ifstream myInFile42(INPUT_FILENAME[42]);

  sprintf(INPUT_FILENAME[43],"data/miroIV1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[43]);
  ifstream myInFile43(INPUT_FILENAME[43]);

  sprintf(INPUT_FILENAME[44],"data/miroIV2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[44]);
  ifstream myInFile44(INPUT_FILENAME[44]);

  sprintf(INPUT_FILENAME[45],"data/miroIV3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[45]);
  ifstream myInFile45(INPUT_FILENAME[45]);

  sprintf(INPUT_FILENAME[46],"data/miroIV4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[46]);
  ifstream myInFile46(INPUT_FILENAME[46]);

  sprintf(INPUT_FILENAME[47],"data/miroSun1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[47]);
  ifstream myInFile47(INPUT_FILENAME[47]);

  sprintf(INPUT_FILENAME[48],"data/miroSun2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[48]);
  ifstream myInFile48(INPUT_FILENAME[48]);

  sprintf(INPUT_FILENAME[49],"data/miroSun3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[49]);
  ifstream myInFile49(INPUT_FILENAME[49]);

  sprintf(INPUT_FILENAME[50],"data/miroSun4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[50]);
  ifstream myInFile50(INPUT_FILENAME[50]);

  sprintf(INPUT_FILENAME[51],"data/nist1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[51]);
  ifstream myInFile51(INPUT_FILENAME[51]);

  sprintf(INPUT_FILENAME[52],"data/nist2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[52]);
  ifstream myInFile52(INPUT_FILENAME[52]);

  sprintf(INPUT_FILENAME[53],"data/nist3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[53]);
  ifstream myInFile53(INPUT_FILENAME[53]);

  sprintf(INPUT_FILENAME[54],"data/nist4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[54]);
  ifstream myInFile54(INPUT_FILENAME[54]);

  sprintf(INPUT_FILENAME[55],"data/nist30_1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[55]);
  ifstream myInFile55(INPUT_FILENAME[55]);

  sprintf(INPUT_FILENAME[56],"data/nist30_2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[56]);
  ifstream myInFile56(INPUT_FILENAME[56]);

  sprintf(INPUT_FILENAME[57],"data/nist45_1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[57]);
  ifstream myInFile57(INPUT_FILENAME[57]);

  sprintf(INPUT_FILENAME[58],"data/nist45_2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[58]);
  ifstream myInFile58(INPUT_FILENAME[58]);

  sprintf(INPUT_FILENAME[59],"data/nist45_3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[59]);
  ifstream myInFile59(INPUT_FILENAME[59]);

  sprintf(INPUT_FILENAME[60],"data/nist45_4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[60]);
  ifstream myInFile60(INPUT_FILENAME[60]);

  sprintf(INPUT_FILENAME[61],"data/nist45diffuse.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[61]);
  ifstream myInFile61(INPUT_FILENAME[61]);

  sprintf(INPUT_FILENAME[62],"data/nist60_1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[62]);
  ifstream myInFile62(INPUT_FILENAME[62]);

  sprintf(INPUT_FILENAME[63],"data/nist60_2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[63]);
  ifstream myInFile63(INPUT_FILENAME[63]);

  sprintf(INPUT_FILENAME[64],"data/nist60_3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[64]);
  ifstream myInFile64(INPUT_FILENAME[64]);

  sprintf(INPUT_FILENAME[65],"data/tyvek1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[65]);
  ifstream myInFile65(INPUT_FILENAME[65]);

  sprintf(INPUT_FILENAME[66],"data/tyvek2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[66]);
  ifstream myInFile66(INPUT_FILENAME[66]);

  sprintf(INPUT_FILENAME[67],"data/tyvek30.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[67]);
  ifstream myInFile67(INPUT_FILENAME[67]);

  sprintf(INPUT_FILENAME[68],"data/tyvek45.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[68]);
  ifstream myInFile68(INPUT_FILENAME[68]);

  sprintf(INPUT_FILENAME[69],"data/tyvek60.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[69]);
  ifstream myInFile69(INPUT_FILENAME[69]);

  sprintf(INPUT_FILENAME[70],"data/uvs1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[70]);
  ifstream myInFile70(INPUT_FILENAME[70]);

  sprintf(INPUT_FILENAME[71],"data/uvs1.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[71]);
  ifstream myInFile71(INPUT_FILENAME[71]);

  sprintf(INPUT_FILENAME[72],"data/uvs2.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[72]);
  ifstream myInFile72(INPUT_FILENAME[72]);

  sprintf(INPUT_FILENAME[73],"data/uvs3.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[73]);
  ifstream myInFile73(INPUT_FILENAME[73]);

  sprintf(INPUT_FILENAME[74],"data/uvs4.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[74]);
  ifstream myInFile74(INPUT_FILENAME[74]);

  sprintf(INPUT_FILENAME[75],"data/uvs30.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[75]);
  ifstream myInFile75(INPUT_FILENAME[75]);

  sprintf(INPUT_FILENAME[76],"data/uvs45.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[76]);
  ifstream myInFile76(INPUT_FILENAME[76]);

  sprintf(INPUT_FILENAME[77],"data/uvs60.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[77]);
  ifstream myInFile77(INPUT_FILENAME[77]);

  sprintf(INPUT_FILENAME[78],"data/uvs45diffuse.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAME[78]);
  ifstream myInFile78(INPUT_FILENAME[78]);

  float lambda[files][points], counts[files][points];
  float dummyError[points];
  float statError[files][points];
  char header[256];
  for(int h = 0; h<57; h++) { //read the header info
    myInFile0 >> header;
    myInFile1 >> header;
    myInFile2 >> header;
    myInFile3 >> header;
    myInFile4 >> header;
    myInFile5 >> header;
    myInFile6 >> header;
    myInFile7 >> header;
    myInFile8 >> header;
    myInFile9 >> header;
    myInFile10 >> header;
    myInFile11 >> header;
    myInFile12 >> header;
    myInFile13 >> header;
    myInFile14 >> header;
    myInFile15 >> header;
    myInFile16 >> header;
    myInFile17 >> header;
    myInFile18 >> header;
    myInFile19 >> header;
    myInFile20 >> header;
    myInFile21 >> header;
    myInFile22 >> header;
    myInFile23 >> header;
    myInFile24 >> header;
    myInFile25 >> header;
    myInFile26 >> header;
    myInFile27 >> header;
    myInFile28 >> header;
    myInFile29 >> header;
    myInFile30 >> header;
    myInFile31 >> header;
    myInFile32 >> header;
    myInFile33 >> header;
    myInFile34 >> header;
    myInFile35 >> header;
    myInFile36 >> header;
    myInFile37 >> header;
    myInFile38 >> header;
    myInFile39 >> header;
    myInFile40 >> header;
    myInFile41 >> header;
    myInFile42 >> header;
    myInFile43 >> header;
    myInFile44 >> header;
    myInFile45 >> header;
    myInFile46 >> header;
    myInFile47 >> header;
    myInFile48 >> header;
    myInFile49 >> header;
    myInFile50 >> header;
    myInFile51 >> header;
    myInFile52 >> header;
    myInFile53 >> header;
    myInFile54 >> header;
    myInFile55 >> header;
    myInFile56 >> header;
    myInFile57 >> header;
    myInFile58 >> header;
    myInFile59 >> header;
    myInFile60 >> header;
    myInFile61 >> header;
    myInFile62 >> header;
    myInFile63 >> header;
    myInFile64 >> header;
    myInFile65 >> header;
    myInFile66 >> header;
    myInFile67 >> header;
    myInFile68 >> header;
    myInFile69 >> header;
    myInFile70 >> header;
    myInFile71 >> header;
    myInFile72 >> header;
    myInFile73 >> header;
    myInFile74 >> header;
    myInFile75 >> header;
    myInFile76 >> header;
    myInFile77 >> header;
    myInFile78 >> header;

    //cout << header[h] << endl;
  }
  //cout << "Wavelength (nm) 	Counts" << endl;
  for(int i=0;i<points;i++) {
    myInFile0 >> lambda[0][i] >> counts[0][i];
    myInFile1 >> lambda[1][i] >> counts[1][i];
    myInFile2 >> lambda[2][i] >> counts[2][i];
    myInFile3 >> lambda[3][i] >> counts[3][i];
    myInFile4 >> lambda[4][i] >> counts[4][i];
    myInFile5 >> lambda[5][i] >> counts[5][i];
    myInFile6 >> lambda[6][i] >> counts[6][i];
    myInFile7 >> lambda[7][i] >> counts[7][i];
    myInFile8 >> lambda[8][i] >> counts[8][i];
    myInFile9 >> lambda[9][i] >> counts[9][i];
    myInFile10 >> lambda[10][i] >> counts[10][i];
    myInFile11 >> lambda[11][i] >> counts[11][i];
    myInFile12 >> lambda[12][i] >> counts[12][i];
    myInFile13 >> lambda[13][i] >> counts[13][i];
    myInFile14 >> lambda[14][i] >> counts[14][i];
    myInFile15 >> lambda[15][i] >> counts[15][i];
    myInFile16 >> lambda[16][i] >> counts[16][i];
    myInFile17 >> lambda[17][i] >> counts[17][i];
    myInFile18 >> lambda[18][i] >> counts[18][i];
    myInFile19 >> lambda[19][i] >> counts[19][i];
    myInFile20 >> lambda[20][i] >> counts[20][i];
    myInFile21 >> lambda[21][i] >> counts[21][i];
    myInFile22 >> lambda[22][i] >> counts[22][i];
    myInFile23 >> lambda[23][i] >> counts[23][i];
    myInFile24 >> lambda[24][i] >> counts[24][i];
    myInFile25 >> lambda[25][i] >> counts[25][i];
    myInFile26 >> lambda[26][i] >> counts[26][i];
    myInFile27 >> lambda[27][i] >> counts[27][i];
    myInFile28 >> lambda[28][i] >> counts[28][i];
    myInFile29 >> lambda[29][i] >> counts[29][i];
    myInFile30 >> lambda[30][i] >> counts[30][i];
    myInFile31 >> lambda[31][i] >> counts[31][i];
    myInFile32 >> lambda[32][i] >> counts[32][i];
    myInFile33 >> lambda[33][i] >> counts[33][i];
    myInFile34 >> lambda[34][i] >> counts[34][i];
    myInFile35 >> lambda[35][i] >> counts[35][i];
    myInFile36 >> lambda[36][i] >> counts[36][i];
    myInFile37 >> lambda[37][i] >> counts[37][i];
    myInFile38 >> lambda[38][i] >> counts[38][i];
    myInFile39 >> lambda[39][i] >> counts[39][i];
    myInFile40 >> lambda[40][i] >> counts[40][i];
    myInFile41 >> lambda[41][i] >> counts[41][i];
    myInFile42 >> lambda[42][i] >> counts[42][i];
    myInFile43 >> lambda[43][i] >> counts[43][i];
    myInFile44 >> lambda[44][i] >> counts[44][i];
    myInFile45 >> lambda[45][i] >> counts[45][i];
    myInFile46 >> lambda[46][i] >> counts[46][i];
    myInFile47 >> lambda[47][i] >> counts[47][i];
    myInFile48 >> lambda[48][i] >> counts[48][i];
    myInFile49 >> lambda[49][i] >> counts[49][i];
    myInFile50 >> lambda[50][i] >> counts[50][i];
    myInFile51 >> lambda[51][i] >> counts[51][i];
    myInFile52 >> lambda[52][i] >> counts[52][i];
    myInFile53 >> lambda[53][i] >> counts[53][i];
    myInFile54 >> lambda[54][i] >> counts[54][i];
    myInFile55 >> lambda[55][i] >> counts[55][i];
    myInFile56 >> lambda[56][i] >> counts[56][i];
    myInFile57 >> lambda[57][i] >> counts[57][i];
    myInFile58 >> lambda[58][i] >> counts[58][i];
    myInFile59 >> lambda[59][i] >> counts[59][i];
    myInFile60 >> lambda[60][i] >> counts[60][i];
    myInFile61 >> lambda[61][i] >> counts[61][i];
    myInFile62 >> lambda[62][i] >> counts[62][i];
    myInFile63 >> lambda[63][i] >> counts[63][i];
    myInFile64 >> lambda[64][i] >> counts[64][i];
    myInFile65 >> lambda[65][i] >> counts[65][i];
    myInFile66 >> lambda[66][i] >> counts[66][i];
    myInFile67 >> lambda[67][i] >> counts[67][i];
    myInFile68 >> lambda[68][i] >> counts[68][i];
    myInFile69 >> lambda[69][i] >> counts[69][i];
    myInFile70 >> lambda[70][i] >> counts[70][i];
    myInFile71 >> lambda[71][i] >> counts[71][i];
    myInFile72 >> lambda[72][i] >> counts[72][i];
    myInFile73 >> lambda[73][i] >> counts[73][i];
    myInFile74 >> lambda[74][i] >> counts[74][i];
    myInFile75 >> lambda[75][i] >> counts[75][i];
    myInFile76 >> lambda[76][i] >> counts[76][i];
    myInFile77 >> lambda[77][i] >> counts[77][i];
    myInFile78 >> lambda[78][i] >> counts[78][i];

    //cout << i << " : " << lambda[73][i] << "             " <<  counts[73][i] << endl;

    dummyError[i] = 0.0;
    statError[0][i] = sqrt(counts[0][i]);
    statError[1][i] = sqrt(counts[1][i]);
    statError[2][i] = sqrt(counts[2][i]);
    statError[3][i] = sqrt(counts[3][i]);
    statError[4][i] = sqrt(counts[4][i]);
    statError[5][i] = sqrt(counts[5][i]);
    statError[6][i] = sqrt(counts[6][i]);
    statError[7][i] = sqrt(counts[7][i]);
    statError[6][i] = sqrt(counts[8][i]);
    statError[9][i] = sqrt(counts[9][i]);
    statError[10][i] = sqrt(counts[10][i]);
    statError[11][i] = sqrt(counts[11][i]);
    statError[12][i] = sqrt(counts[12][i]);
    statError[13][i] = sqrt(counts[13][i]);
    statError[14][i] = sqrt(counts[14][i]);
    statError[15][i] = sqrt(counts[15][i]);
    statError[16][i] = sqrt(counts[16][i]);
    statError[17][i] = sqrt(counts[17][i]);
    statError[18][i] = sqrt(counts[18][i]);
    statError[19][i] = sqrt(counts[19][i]);
    statError[20][i] = sqrt(counts[20][i]);
    statError[21][i] = sqrt(counts[21][i]);
    statError[22][i] = sqrt(counts[22][i]);
    statError[23][i] = sqrt(counts[23][i]);
    statError[24][i] = sqrt(counts[24][i]);
    statError[25][i] = sqrt(counts[25][i]);
    statError[26][i] = sqrt(counts[26][i]);
    statError[27][i] = sqrt(counts[27][i]);
    statError[28][i] = sqrt(counts[28][i]);
    statError[29][i] = sqrt(counts[29][i]);
    statError[30][i] = sqrt(counts[30][i]);
    statError[31][i] = sqrt(counts[31][i]);
    statError[32][i] = sqrt(counts[32][i]);
    statError[33][i] = sqrt(counts[33][i]);
    statError[34][i] = sqrt(counts[34][i]);
    statError[35][i] = sqrt(counts[35][i]);
    statError[36][i] = sqrt(counts[36][i]);
    statError[37][i] = sqrt(counts[37][i]);
    statError[38][i] = sqrt(counts[38][i]);
    statError[39][i] = sqrt(counts[39][i]);
    statError[40][i] = sqrt(counts[40][i]);
    statError[41][i] = sqrt(counts[41][i]);
    statError[42][i] = sqrt(counts[42][i]);
    statError[43][i] = sqrt(counts[43][i]);
    statError[44][i] = sqrt(counts[44][i]);
    statError[45][i] = sqrt(counts[45][i]);
    statError[46][i] = sqrt(counts[46][i]);
    statError[47][i] = sqrt(counts[47][i]);
    statError[48][i] = sqrt(counts[48][i]);
    statError[49][i] = sqrt(counts[49][i]);
    statError[50][i] = sqrt(counts[50][i]);
    statError[51][i] = sqrt(counts[51][i]);
    statError[52][i] = sqrt(counts[52][i]);
    statError[53][i] = sqrt(counts[53][i]);
    statError[54][i] = sqrt(counts[54][i]);
    statError[55][i] = sqrt(counts[55][i]);
    statError[56][i] = sqrt(counts[56][i]);
    statError[57][i] = sqrt(counts[57][i]);
    statError[58][i] = sqrt(counts[58][i]);
    statError[59][i] = sqrt(counts[59][i]);
    statError[60][i] = sqrt(counts[60][i]);
    statError[61][i] = sqrt(counts[61][i]);
    statError[62][i] = sqrt(counts[62][i]);
    statError[63][i] = sqrt(counts[63][i]);
    statError[64][i] = sqrt(counts[64][i]);
    statError[65][i] = sqrt(counts[65][i]);
    statError[66][i] = sqrt(counts[66][i]);
    statError[67][i] = sqrt(counts[67][i]);
    statError[68][i] = sqrt(counts[68][i]);
    statError[69][i] = sqrt(counts[69][i]);
    statError[70][i] = sqrt(counts[70][i]);
    statError[71][i] = sqrt(counts[71][i]);
    statError[72][i] = sqrt(counts[72][i]);
    statError[73][i] = sqrt(counts[73][i]);
    statError[74][i] = sqrt(counts[74][i]);
    statError[75][i] = sqrt(counts[75][i]);
    statError[76][i] = sqrt(counts[76][i]);
    statError[77][i] = sqrt(counts[77][i]);
    statError[78][i] = sqrt(counts[78][i]);



  }

  myInFile0.close();
  myInFile1.close();
  myInFile2.close();
  myInFile3.close();  
  myInFile4.close();
  myInFile5.close();
  myInFile6.close();
  myInFile7.close();
  myInFile8.close();
  myInFile9.close();
  myInFile10.close();
  myInFile11.close();
  myInFile12.close();
  myInFile13.close();
  myInFile14.close();
  myInFile15.close();
  myInFile16.close();
  myInFile17.close();
  myInFile18.close();
  myInFile19.close();
  myInFile20.close();
  myInFile21.close();
  myInFile22.close();
  myInFile23.close();
  myInFile24.close();
  myInFile25.close();
  myInFile26.close();
  myInFile27.close();
  myInFile28.close();
  myInFile29.close();
  myInFile30.close();
  myInFile31.close();
  myInFile32.close();
  myInFile33.close();
  myInFile34.close();
  myInFile35.close();
  myInFile36.close();
  myInFile37.close();
  myInFile38.close();
  myInFile39.close();
  myInFile40.close();
  myInFile41.close();
  myInFile42.close();
  myInFile43.close();
  myInFile44.close();
  myInFile45.close();
  myInFile46.close();
  myInFile47.close();
  myInFile48.close();
  myInFile49.close();
  myInFile50.close();
  myInFile51.close();
  myInFile52.close();
  myInFile53.close();
  myInFile54.close();
  myInFile55.close();
  myInFile56.close();
  myInFile57.close();
  myInFile58.close();
  myInFile59.close();
  myInFile60.close();
  myInFile61.close();
  myInFile62.close();
  myInFile63.close();
  myInFile64.close();
  myInFile65.close();
  myInFile66.close();
  myInFile67.close();
  myInFile68.close();
  myInFile69.close();
  myInFile70.close();
  myInFile71.close();
  myInFile72.close();
  myInFile73.close();
  myInFile74.close();
  myInFile75.close();
  myInFile76.close();
  myInFile77.close();
  myInFile78.close();


  const Int_t points_cal = 65;
  const Int_t points_cal_my = 1;
  float lambda_my[points_cal_my];
  float ref_nist_my[points_cal_my];
  lambda_my[0] = 175;
  ref_nist_my[0] = 0.50;
  float correction = 0.0/600; //0.04
 
  char INPUT_FILENAMEref[256];
  sprintf(INPUT_FILENAMEref,"data/STAN-SSH-NIST_SN00400CERT00439.txt");
  fprintf(stderr, "My Input file name is: %s\n", INPUT_FILENAMEref);
  ifstream myInFileRef(INPUT_FILENAMEref);
  float lambda_cal[points_cal], reflectivity[points_cal], ref_my[points_cal];
  float dummyError_cal[points_cal];
  float dummyError_cal_my[points_cal_my];
  dummyError_cal_my[0] = 0.0;
  char header2[256];
  float temp[points_cal];
  for(int h = 0; h<1; h++) { //read the header info
    myInFileRef >> header2;
    //cout << header[h] << endl;
  }
  //cout << "Wavelength (nm) 	Counts" << endl;
  lambda_cal[0] = lambda_my[0]; 
  reflectivity[0] = ref_nist_my[0];
  ref_my[0] = reflectivity[0] - correction*600;//lambda_cal[0];
  for(int i=1;i<points_cal;i++) {
    myInFileRef >> lambda_cal[i] >> reflectivity[i] >> temp[i];
    //cout << i << " : " << lambda_cal[i] << "             " <<  reflectivity[i] << endl;
    dummyError_cal[i] = 0.0;
    ref_my[i] = reflectivity[i] - correction*600;//lambda_cal[i];
  }

  myInFileRef.close();


  //********************************************************************************************************************
  //Now produce raw data graph for unradiated varieties

  TCanvas *final_canvas1 = new TCanvas("final_canvas1","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr1;
  hr1 = new TH2F("hr1",graphname1,1000,170.0,890.0,100,-200,70000);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Counts");  
  hr1->GetYaxis()->SetLabelColor(1);
  hr1->GetYaxis()->SetTitleColor(1);
  hr1->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr1->GetYaxis()->SetTitleOffset(1.3);
  hr1->GetXaxis()->SetLabelColor(1);
  hr1->GetXaxis()->SetTitleColor(1);
  hr1->SetXTitle(xTitle);
  hr1->Draw();

  //  gr1 = new TGraphErrors(dndt_bins,theta_f, dn_f,dummyError,dn_f_err);
  //  gr1->SetMarkerColor(51);
  //  gr1->SetMarkerStyle(20);   
  //  gr1->SetMarkerSize(0.75);
  //  gr1->SetFillColor(0);
  //  gr1->Draw("P");

  //  gr2_ee = new TGraph(dndt_bins,theta_f, dn_f);

  TGraphErrors *gr1_nist = new TGraphErrors(points,lambda[std], counts[std], dummyError, statError[std]);
  gr1_nist->SetMarkerColor(kBlue);
  gr1_nist->SetMarkerStyle(20);   
  gr1_nist->SetMarkerSize(0.35);
  //  gr1_nist->SetFillColor(0);
  gr1_nist->Draw("P");

  //  TGraphErrors *gr2 = new TGraphErrors(points,lambda[31], counts[31], dummyError, statError[31]);
  TGraphErrors *gr2 = new TGraphErrors(points,lambda[30], counts[30], dummyError, statError[30]);
  gr2->SetMarkerColor(kRed);
  gr2->SetMarkerStyle(20);   
  gr2->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2->Draw("P");

  TGraphErrors *gr3 = new TGraphErrors(points,lambda[8], counts[8], dummyError, statError[8]);
  gr3->SetMarkerColor(kMagenta+2);
  gr3->SetMarkerStyle(20);   
  gr3->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3->Draw("P");

  TGraphErrors *gr4 = new TGraphErrors(points,lambda[47], counts[47], dummyError, statError[47]);
  gr4->SetMarkerColor(kOrange+5);
  gr4->SetMarkerStyle(20);   
  gr4->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4->Draw("P");

  TGraphErrors *gr5 = new TGraphErrors(points,lambda[15], counts[15], dummyError, statError[15]);
  gr5->SetMarkerColor(kTeal-1);
  gr5->SetMarkerStyle(20);
  gr5->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5->Draw("P");

  TGraphErrors *gr6 = new TGraphErrors(points,lambda[20], counts[20], dummyError, statError[20]);
  gr6->SetMarkerColor(kGreen+2);
  gr6->SetMarkerStyle(20);
  gr6->SetMarkerSize(0.35);
  //  gr6->SetFillColor(0);
  gr6->Draw("P");

  TGraphErrors *gr7 = new TGraphErrors(points,lambda[25], counts[25], dummyError, statError[25]);
  gr7->SetMarkerColor(kOrange);
  gr7->SetMarkerStyle(20);   
  gr7->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr7->Draw("P");

  TGraphErrors *gr8 = new TGraphErrors(points,lambda[71], counts[71], dummyError, statError[71]);
  gr8->SetMarkerColor(kGreen);
  gr8->SetMarkerStyle(20);   
  gr8->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr8->Draw("P");

  TGraphErrors *gr9 = new TGraphErrors(points,lambda[36], counts[36], dummyError, statError[36]);
  gr9->SetMarkerColor(kMagenta);
  gr9->SetMarkerStyle(20);   
  gr9->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr9->Draw("P");

  TGraphErrors *gr10 = new TGraphErrors(points,lambda[0], counts[0], dummyError, statError[0]);
  gr10->SetMarkerColor(kCyan);
  gr10->SetMarkerStyle(20);   
  gr10->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr10->Draw("P");

  //gr2->Draw("P");

  sprintf(GraphText1,"       Reflectivity Study: Raw data (~90 degree)");
  TPaveLabel *raw_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  raw_pt->SetBorderSize(0);
  raw_pt->SetTextColor(1);
  raw_pt->SetTextSize(0.85);
  raw_pt->SetFillColor(0);
  raw_pt->Draw();

  TPaveLabel *ocean_pt = new TPaveLabel(0.75,0.84, 0.89,0.89, "Ocean Optics","NDC");
  ocean_pt->SetBorderSize(0);
  ocean_pt->SetTextColor(1);
  ocean_pt->SetTextSize(0.6);
  ocean_pt->SetFillColor(0);
  ocean_pt->SetFillStyle(0);
  ocean_pt->Draw();
  TPaveLabel *DH2000_pt = new TPaveLabel(0.75,0.80, 0.89,0.86, "DH-2000","NDC");
  DH2000_pt->SetBorderSize(0);
  DH2000_pt->SetTextColor(1);
  DH2000_pt->SetTextSize(0.5);
  DH2000_pt->SetFillColor(0);
  DH2000_pt->SetFillStyle(0);
  DH2000_pt->Draw();
  TPaveLabel *light_source_pt = new TPaveLabel(0.75,0.765, 0.89,0.825, "light source","NDC");
  light_source_pt->SetBorderSize(0);
  light_source_pt->SetTextColor(1);
  light_source_pt->SetTextSize(0.58);
  light_source_pt->SetFillColor(0);
  light_source_pt->SetFillStyle(0);
  light_source_pt->Draw();

  //TDatime d;
  //  sprintf(GraphText1,"%s",d.AsString());
  //  TPaveText *pt_0 = new TPaveText(0.61,0.71, 0.895,0.77,"NDC");
  //  pt_0->AddText(GraphText1);
  //  pt_0->SetBorderSize(0);
  //  pt_0->SetTextColor(49);
  //  pt_0->SetFillColor(0);
  //  pt_0->Draw();

  TPaveLabel *unradiated_pt = new TPaveLabel(0.15,0.84, 0.33,0.89, "Un-radiated","NDC");
  unradiated_pt->SetBorderSize(0);
  unradiated_pt->SetTextColor(1);
  unradiated_pt->SetTextSize(0.7);
  unradiated_pt->SetFillColor(0);
  unradiated_pt->SetFillStyle(0);
  //unradiated_pt->Draw();

  TLegend *leg1 = new TLegend(0.15,0.50,0.40,0.85);
  leg1->SetBorderSize(0);
  leg1->SetFillColor(0);
  leg1->SetFillStyle(0);
  leg1->AddEntry(gr1_nist,"NIST standard","pl");
  leg1->AddEntry(gr2,"1 mil Al. mylar","pl");
  //leg1->AddEntry(gr3,"Tyvek 1073B","pl");
  leg1->AddEntry(gr3,"Miro-silver 4270","pl");
  leg1->AddEntry(gr4,"Miro-silver SUN","pl");
  leg1->AddEntry(gr5,"Alzak Ag.","pl");
  leg1->AddEntry(gr6,"Alzak Al.","pl");
  leg1->AddEntry(gr7,"Anolux I","pl");
  leg1->AddEntry(gr8,"Anolux UVS","pl");
  leg1->AddEntry(gr9,"Miro-silver 27","pl");
  leg1->AddEntry(gr10,"Miro 2000Ag (diffuse)","pl");

  leg1->Draw();

  sprintf(printname,"rawData1_%ddeg.pdf", angle);
  final_canvas1->Print(printname);

  //*************************************************************************************

  TCanvas *final_canvas2 = new TCanvas("final_canvas2","Reflectivity",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr2;
  hr2 = new TH2F("hr2",graphname1,1000,170.0,890.0,100,0,1);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr2->GetYaxis()->SetLabelColor(1);
  hr2->GetYaxis()->SetTitleColor(1);
  hr2->SetYTitle(yTitle);
  //    hr2->GetXaxis()->CenterTitle();
  //    hr2->GetYaxis()->CenterTitle();
  //hr2->GetYaxis()->SetTitleOffset(1.3);
  hr2->GetXaxis()->SetLabelColor(1);
  hr2->GetXaxis()->SetTitleColor(1);
  hr2->SetXTitle(xTitle);
  hr2->Draw();

  TBox *b1 = new TBox(170,0,250,1.0);
  b1->SetFillStyle(3001);
  b1->SetLineColor(0);
  b1->SetFillColor(19);
  b1->Draw();

  TGraphErrors *gr1_cal = new TGraphErrors(points_cal,lambda_cal,reflectivity,dummyError_cal,dummyError_cal);
  gr1_cal->SetMarkerColor(kBlue);
  gr1_cal->SetMarkerStyle(22);   
  gr1_cal->SetMarkerSize(0.75);
  //  gr1_cal->SetFillColor(0);
  gr1_cal->Draw("P");

  TGraphErrors *gr2_cal = new TGraphErrors(points_cal_my,lambda_my,ref_nist_my,dummyError_cal_my,dummyError_cal_my);
  gr2_cal->SetMarkerColor(kSpring+4);
  gr2_cal->SetMarkerStyle(21);   
  gr2_cal->SetMarkerSize(0.85);
  //  gr1_cal->SetFillColor(0);
  gr2_cal->Draw("P");

  //Make a spline of this data
  // use a cubic spline to smooth the graph
  TSpline3 *s = new TSpline3("grs",gr1_cal);
  s->SetLineColor(kRed);
  s->SetLineWidth(1);
  s->Draw("same");

  TLegend *leg2 = new TLegend(0.55,0.55,0.89,0.75);
  leg2->SetBorderSize(0);
  leg2->SetFillColor(0);
  leg2->SetFillStyle(0);
  leg2->AddEntry(gr1_cal,"data from NIST","p");
  leg2->AddEntry(gr2_cal,"my added point","p");
  leg2->AddEntry(s,"Spline Interpolation","l");
  leg2->Draw();

  //cout << "I am here" << endl;

  sprintf(GraphText1,"   Reflectivity: NIST Standard (84 degree)");
  TPaveLabel *pt2 = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  pt2->SetBorderSize(0);
  pt2->SetTextColor(1);
  pt2->SetTextSize(0.85);
  pt2->SetFillColor(0);
  pt2->Draw();

  sprintf(printname,"plotNIST_%ddeg.pdf", angle);
  final_canvas2->Print(printname);

    TGraphErrors *gr1_cal_my = new TGraphErrors(points_cal,lambda_cal,ref_my,dummyError_cal,dummyError_cal);
  //Make a spline of this data
  // use a cubic spline to smooth the graph
  TSpline3 *s_my = new TSpline3("grs_my",gr1_cal_my);

  //********************************************************************************************************************

  float ref[files][points];
  float refError[files][points];

  char OUTPUT_FILENAME[files][256];
  for(int inc=0;inc<files;inc++) {
	  sprintf(OUTPUT_FILENAME[inc],"%s%s","analyzed-",INPUT_FILENAME[inc]);
    //ofstream Form("myOutFile%i(OUTPUT_FILENAME[%i])",inc,inc);
    cout << OUTPUT_FILENAME[inc] << "\n" << endl;
  }

  ofstream myOutFile0(OUTPUT_FILENAME[0]);
  ofstream myOutFile1(OUTPUT_FILENAME[1]);
  ofstream myOutFile2(OUTPUT_FILENAME[2]);
  ofstream myOutFile3(OUTPUT_FILENAME[3]);
  ofstream myOutFile4(OUTPUT_FILENAME[4]);
  ofstream myOutFile5(OUTPUT_FILENAME[5]);
  ofstream myOutFile6(OUTPUT_FILENAME[6]);
  ofstream myOutFile7(OUTPUT_FILENAME[7]);
  ofstream myOutFile8(OUTPUT_FILENAME[8]);
  ofstream myOutFile9(OUTPUT_FILENAME[9]);
  ofstream myOutFile10(OUTPUT_FILENAME[10]);
  ofstream myOutFile11(OUTPUT_FILENAME[11]);
  ofstream myOutFile12(OUTPUT_FILENAME[12]);
  ofstream myOutFile13(OUTPUT_FILENAME[13]);
  ofstream myOutFile14(OUTPUT_FILENAME[14]);
  ofstream myOutFile15(OUTPUT_FILENAME[15]);
  ofstream myOutFile16(OUTPUT_FILENAME[16]);
  ofstream myOutFile17(OUTPUT_FILENAME[17]);
  ofstream myOutFile18(OUTPUT_FILENAME[18]);
  ofstream myOutFile19(OUTPUT_FILENAME[19]);
  ofstream myOutFile20(OUTPUT_FILENAME[20]);
  ofstream myOutFile21(OUTPUT_FILENAME[21]);
  ofstream myOutFile22(OUTPUT_FILENAME[22]);
  ofstream myOutFile23(OUTPUT_FILENAME[23]);
  ofstream myOutFile24(OUTPUT_FILENAME[24]);
  ofstream myOutFile25(OUTPUT_FILENAME[25]);
  ofstream myOutFile26(OUTPUT_FILENAME[26]);
  ofstream myOutFile27(OUTPUT_FILENAME[27]);
  ofstream myOutFile28(OUTPUT_FILENAME[28]);
  ofstream myOutFile29(OUTPUT_FILENAME[29]);
  ofstream myOutFile30(OUTPUT_FILENAME[30]);
  ofstream myOutFile31(OUTPUT_FILENAME[31]);
  ofstream myOutFile32(OUTPUT_FILENAME[32]);
  ofstream myOutFile33(OUTPUT_FILENAME[33]);
  ofstream myOutFile34(OUTPUT_FILENAME[34]);
  ofstream myOutFile35(OUTPUT_FILENAME[35]);
  ofstream myOutFile36(OUTPUT_FILENAME[36]);
  ofstream myOutFile37(OUTPUT_FILENAME[37]);
  ofstream myOutFile38(OUTPUT_FILENAME[38]);
  ofstream myOutFile39(OUTPUT_FILENAME[39]);
  ofstream myOutFile40(OUTPUT_FILENAME[40]);
  ofstream myOutFile41(OUTPUT_FILENAME[41]);
  ofstream myOutFile42(OUTPUT_FILENAME[42]);
  ofstream myOutFile43(OUTPUT_FILENAME[43]);
  ofstream myOutFile44(OUTPUT_FILENAME[44]);
  ofstream myOutFile45(OUTPUT_FILENAME[45]);
  ofstream myOutFile46(OUTPUT_FILENAME[46]);
  ofstream myOutFile47(OUTPUT_FILENAME[47]);
  ofstream myOutFile48(OUTPUT_FILENAME[48]);
  ofstream myOutFile49(OUTPUT_FILENAME[49]);
  ofstream myOutFile50(OUTPUT_FILENAME[50]);
  ofstream myOutFile51(OUTPUT_FILENAME[51]);
  ofstream myOutFile52(OUTPUT_FILENAME[52]);
  ofstream myOutFile53(OUTPUT_FILENAME[53]);
  ofstream myOutFile54(OUTPUT_FILENAME[54]);
  ofstream myOutFile55(OUTPUT_FILENAME[55]);
  ofstream myOutFile56(OUTPUT_FILENAME[56]);
  ofstream myOutFile57(OUTPUT_FILENAME[57]);
  ofstream myOutFile58(OUTPUT_FILENAME[58]);
  ofstream myOutFile59(OUTPUT_FILENAME[59]);
  ofstream myOutFile60(OUTPUT_FILENAME[60]);
  ofstream myOutFile61(OUTPUT_FILENAME[61]);
  ofstream myOutFile62(OUTPUT_FILENAME[62]);
  ofstream myOutFile63(OUTPUT_FILENAME[63]);
  ofstream myOutFile64(OUTPUT_FILENAME[64]);
  ofstream myOutFile65(OUTPUT_FILENAME[65]);
  ofstream myOutFile66(OUTPUT_FILENAME[66]);
  ofstream myOutFile67(OUTPUT_FILENAME[67]);
  ofstream myOutFile68(OUTPUT_FILENAME[68]);
  ofstream myOutFile69(OUTPUT_FILENAME[69]);
  ofstream myOutFile70(OUTPUT_FILENAME[70]);
  ofstream myOutFile71(OUTPUT_FILENAME[71]);
  ofstream myOutFile72(OUTPUT_FILENAME[72]);
  ofstream myOutFile73(OUTPUT_FILENAME[73]);
  ofstream myOutFile74(OUTPUT_FILENAME[74]);
  ofstream myOutFile75(OUTPUT_FILENAME[75]);
  ofstream myOutFile76(OUTPUT_FILENAME[76]);
  ofstream myOutFile77(OUTPUT_FILENAME[77]);
  ofstream myOutFile78(OUTPUT_FILENAME[78]);

  /*ofstream myOutFile0;
  ofstream myOutFile1;
  ofstream myOutFile2;
  ofstream myOutFile3;
  ofstream myOutFile4;
  ofstream myOutFile5;
  ofstream myOutFile6;
  ofstream myOutFile7;
  ofstream myOutFile8;
  ofstream myOutFile9;
  ofstream myOutFile10;
  ofstream myOutFile11;
  ofstream myOutFile12;
  ofstream myOutFile13;
  ofstream myOutFile14;
  ofstream myOutFile15;
  ofstream myOutFile16;
  ofstream myOutFile17;
  ofstream myOutFile18;
  ofstream myOutFile19;
  ofstream myOutFile20;
  ofstream myOutFile21;
  ofstream myOutFile22;
  ofstream myOutFile23;
  ofstream myOutFile24;
  ofstream myOutFile25;
  ofstream myOutFile26;
  ofstream myOutFile27;
  ofstream myOutFile28;
  ofstream myOutFile29;
  ofstream myOutFile30;
  ofstream myOutFile31;
  ofstream myOutFile32;
  ofstream myOutFile33;
  ofstream myOutFile34;
  ofstream myOutFile35;
  ofstream myOutFile36;
  ofstream myOutFile37;
  ofstream myOutFile38;
  ofstream myOutFile39;
  ofstream myOutFile40;
  ofstream myOutFile41;
  ofstream myOutFile42;
  ofstream myOutFile43;
  ofstream myOutFile44;
  ofstream myOutFile45;
  ofstream myOutFile46;
  ofstream myOutFile47;
  ofstream myOutFile48;
  ofstream myOutFile49;
  ofstream myOutFile50;
  ofstream myOutFile51;
  ofstream myOutFile52;
  ofstream myOutFile53;
  ofstream myOutFile54;
  ofstream myOutFile55;
  ofstream myOutFile56;
  ofstream myOutFile57;
  ofstream myOutFile58;
  ofstream myOutFile59;
  ofstream myOutFile60;
  ofstream myOutFile61;
  ofstream myOutFile62;
  ofstream myOutFile63;
  ofstream myOutFile64;
  ofstream myOutFile65;
  ofstream myOutFile66;
  ofstream myOutFile67;
  ofstream myOutFile68;
  ofstream myOutFile69;
  ofstream myOutFile70;
  ofstream myOutFile71;
  ofstream myOutFile72;
  ofstream myOutFile73;
  ofstream myOutFile74;
  ofstream myOutFile75;
  ofstream myOutFile76;
  ofstream myOutFile77;
  ofstream myOutFile78;

  for(int inc=0;inc<files;inc++) {
	  Form("myOutFile%i.open (\"analyzed-data/%s\")",inc,OUTPUT_FILENAME[inc]);
  }*/

  for(int i=0;i<points;i++) {

    ref[0][i] = counts[0][i]/counts[std][i]*s_my->Eval(lambda[0][i]);    
    ref[1][i] = counts[1][i]/counts[std][i]*s_my->Eval(lambda[1][i]);    
    ref[2][i] = counts[2][i]/counts[std][i]*s_my->Eval(lambda[2][i]);    
    ref[3][i] = counts[3][i]/counts[std][i]*s_my->Eval(lambda[3][i]);
    ref[4][i] = counts[4][i]/counts[std][i]*s_my->Eval(lambda[4][i]);
    ref[5][i] = counts[5][i]/counts[std][i]*s_my->Eval(lambda[5][i]);
    ref[6][i] = counts[6][i]/counts[std][i]*s_my->Eval(lambda[6][i]);
    ref[7][i] = counts[7][i]/counts[std][i]*s_my->Eval(lambda[7][i]);
    ref[8][i] = counts[8][i]/counts[std][i]*s_my->Eval(lambda[8][i]);
    ref[9][i] = counts[9][i]/counts[std][i]*s_my->Eval(lambda[9][i]);
    ref[10][i] = counts[10][i]/counts[std][i]*s_my->Eval(lambda[10][i]);
    ref[11][i] = counts[11][i]/counts[std][i]*s_my->Eval(lambda[11][i]);
    ref[12][i] = counts[12][i]/counts[std][i]*s_my->Eval(lambda[12][i]);
    ref[13][i] = counts[13][i]/counts[std][i]*s_my->Eval(lambda[13][i]);
    ref[14][i] = counts[14][i]/counts[std][i]*s_my->Eval(lambda[14][i]);
    ref[15][i] = counts[15][i]/counts[std][i]*s_my->Eval(lambda[15][i]);
    ref[16][i] = counts[16][i]/counts[std][i]*s_my->Eval(lambda[16][i]);
    ref[17][i] = counts[17][i]/counts[std][i]*s_my->Eval(lambda[17][i]);
    ref[18][i] = counts[18][i]/counts[std][i]*s_my->Eval(lambda[18][i]);
    ref[19][i] = counts[19][i]/counts[std][i]*s_my->Eval(lambda[19][i]);
    ref[20][i] = counts[20][i]/counts[std][i]*s_my->Eval(lambda[20][i]);
    ref[21][i] = counts[21][i]/counts[std][i]*s_my->Eval(lambda[21][i]);
    ref[22][i] = counts[22][i]/counts[std][i]*s_my->Eval(lambda[22][i]);
    ref[23][i] = counts[23][i]/counts[std][i]*s_my->Eval(lambda[23][i]);
    ref[24][i] = counts[24][i]/counts[std][i]*s_my->Eval(lambda[24][i]);
    ref[25][i] = counts[25][i]/counts[std][i]*s_my->Eval(lambda[25][i]);
    ref[26][i] = counts[26][i]/counts[std][i]*s_my->Eval(lambda[26][i]);
    ref[27][i] = counts[27][i]/counts[std][i]*s_my->Eval(lambda[27][i]);
    ref[28][i] = counts[28][i]/counts[std][i]*s_my->Eval(lambda[28][i]);
    ref[29][i] = counts[29][i]/counts[std][i]*s_my->Eval(lambda[29][i]);
    ref[30][i] = counts[30][i]/counts[std][i]*s_my->Eval(lambda[30][i]);
    ref[31][i] = counts[31][i]/counts[std][i]*s_my->Eval(lambda[31][i]);
    ref[32][i] = counts[32][i]/counts[std][i]*s_my->Eval(lambda[32][i]);
    ref[33][i] = counts[33][i]/counts[std][i]*s_my->Eval(lambda[33][i]);
    ref[34][i] = counts[34][i]/counts[std][i]*s_my->Eval(lambda[34][i]);
    ref[35][i] = counts[35][i]/counts[std][i]*s_my->Eval(lambda[35][i]);
    ref[36][i] = counts[36][i]/counts[std][i]*s_my->Eval(lambda[36][i]);
    ref[37][i] = counts[37][i]/counts[std][i]*s_my->Eval(lambda[37][i]);
    ref[38][i] = counts[38][i]/counts[std][i]*s_my->Eval(lambda[38][i]);
    ref[39][i] = counts[39][i]/counts[std][i]*s_my->Eval(lambda[39][i]);
    ref[40][i] = counts[40][i]/counts[std][i]*s_my->Eval(lambda[40][i]);
    ref[41][i] = counts[41][i]/counts[std][i]*s_my->Eval(lambda[41][i]);
    ref[42][i] = counts[42][i]/counts[std][i]*s_my->Eval(lambda[42][i]);
    ref[43][i] = counts[43][i]/counts[std][i]*s_my->Eval(lambda[43][i]);
    ref[44][i] = counts[44][i]/counts[std][i]*s_my->Eval(lambda[44][i]);
    ref[45][i] = counts[45][i]/counts[std][i]*s_my->Eval(lambda[45][i]);
    ref[46][i] = counts[46][i]/counts[std][i]*s_my->Eval(lambda[46][i]);
    ref[47][i] = counts[47][i]/counts[std][i]*s_my->Eval(lambda[47][i]);
    ref[48][i] = counts[48][i]/counts[std][i]*s_my->Eval(lambda[48][i]);
    ref[49][i] = counts[49][i]/counts[std][i]*s_my->Eval(lambda[49][i]);
    ref[50][i] = counts[50][i]/counts[std][i]*s_my->Eval(lambda[50][i]);
    ref[51][i] = counts[51][i]/counts[std][i]*s_my->Eval(lambda[51][i]);
    ref[52][i] = counts[52][i]/counts[std][i]*s_my->Eval(lambda[52][i]);
    ref[53][i] = counts[53][i]/counts[std][i]*s_my->Eval(lambda[53][i]);
    ref[54][i] = counts[54][i]/counts[std][i]*s_my->Eval(lambda[54][i]);
    ref[55][i] = counts[55][i]/counts[std][i]*s_my->Eval(lambda[55][i]);
    ref[56][i] = counts[56][i]/counts[std][i]*s_my->Eval(lambda[56][i]);
    ref[57][i] = counts[57][i]/counts[std][i]*s_my->Eval(lambda[57][i]);
    ref[58][i] = counts[58][i]/counts[std][i]*s_my->Eval(lambda[58][i]);
    ref[59][i] = counts[59][i]/counts[std][i]*s_my->Eval(lambda[59][i]);
    ref[60][i] = counts[60][i]/counts[std][i]*s_my->Eval(lambda[60][i]);
    ref[61][i] = counts[61][i]/counts[std][i]*s_my->Eval(lambda[61][i]);
    ref[62][i] = counts[62][i]/counts[std][i]*s_my->Eval(lambda[62][i]);
    ref[63][i] = counts[63][i]/counts[std][i]*s_my->Eval(lambda[63][i]);
    ref[64][i] = counts[64][i]/counts[std][i]*s_my->Eval(lambda[64][i]);
    ref[65][i] = counts[65][i]/counts[std][i]*s_my->Eval(lambda[65][i]);
    ref[66][i] = counts[66][i]/counts[std][i]*s_my->Eval(lambda[66][i]);
    ref[67][i] = counts[67][i]/counts[std][i]*s_my->Eval(lambda[67][i]);
    ref[68][i] = counts[68][i]/counts[std][i]*s_my->Eval(lambda[68][i]);
    ref[69][i] = counts[69][i]/counts[std][i]*s_my->Eval(lambda[69][i]);
    ref[70][i] = counts[70][i]/counts[std][i]*s_my->Eval(lambda[70][i]);
    ref[71][i] = counts[71][i]/counts[std][i]*s_my->Eval(lambda[71][i]);
    ref[72][i] = counts[72][i]/counts[std][i]*s_my->Eval(lambda[72][i]);
    ref[73][i] = counts[73][i]/counts[std][i]*s_my->Eval(lambda[73][i]);
    ref[74][i] = counts[74][i]/counts[std][i]*s_my->Eval(lambda[74][i]);
    ref[75][i] = counts[75][i]/counts[std][i]*s_my->Eval(lambda[75][i]);
    ref[76][i] = counts[76][i]/counts[std][i]*s_my->Eval(lambda[76][i]);
    ref[77][i] = counts[77][i]/counts[std][i]*s_my->Eval(lambda[77][i]);
    ref[78][i] = counts[78][i]/counts[std][i]*s_my->Eval(lambda[78][i]);

    ref[std][i] = s->Eval(lambda[std][i]);

    if(counts[0][i] > 0) {refError[0][i] = ref[0][i]/sqrt(counts[0][i]);}
    else {refError[0][i] = ref[0][i];}
    if(counts[1][i] > 0) {refError[1][i] = ref[1][i]/sqrt(counts[1][i]);}
    else {refError[1][i] = ref[1][i];}
    if(counts[2][i] > 0) {refError[2][i] = ref[2][i]/sqrt(counts[2][i]);}
    else {refError[2][i] = ref[2][i];}
    if(counts[3][i] > 0) {refError[3][i] = ref[3][i]/sqrt(counts[3][i]);}
    else {refError[3][i] = ref[3][i];}
    if(counts[4][i] > 0) {refError[4][i] = ref[4][i]/sqrt(counts[4][i]);}
    else {refError[4][i] = ref[4][i];}
    if(counts[5][i] > 0) {refError[5][i] = ref[5][i]/sqrt(counts[5][i]);}
    else {refError[5][i] = ref[5][i];}
    if(counts[6][i] > 0) {refError[6][i] = ref[6][i]/sqrt(counts[6][i]);}
    else {refError[6][i] = ref[6][i];}
    if(counts[7][i] > 0) {refError[7][i] = ref[7][i]/sqrt(counts[7][i]);}
    else {refError[7][i] = ref[7][i];}
    if(counts[8][i] > 0) {refError[8][i] = ref[8][i]/sqrt(counts[8][i]);}
    else {refError[8][i] = ref[8][i];}
    if(counts[9][i] > 0) {refError[9][i] = ref[9][i]/sqrt(counts[9][i]);}
    else {refError[9][i] = ref[9][i];}
    if(counts[10][i] > 0) {refError[10][i] = ref[10][i]/sqrt(counts[10][i]);}
    else {refError[10][i] = ref[10][i];}
    if(counts[11][i] > 0) {refError[11][i] = ref[11][i]/sqrt(counts[11][i]);}
    else {refError[11][i] = ref[11][i];}
    if(counts[12][i] > 0) {refError[12][i] = ref[12][i]/sqrt(counts[12][i]);}
    else {refError[12][i] = ref[12][i];}
    if(counts[13][i] > 0) {refError[13][i] = ref[13][i]/sqrt(counts[13][i]);}
    else {refError[13][i] = ref[13][i];}
    if(counts[14][i] > 0) {refError[14][i] = ref[14][i]/sqrt(counts[14][i]);}
    else {refError[14][i] = ref[14][i];}
    if(counts[15][i] > 0) {refError[15][i] = ref[15][i]/sqrt(counts[15][i]);}
    else {refError[15][i] = ref[15][i];}
    if(counts[16][i] > 0) {refError[16][i] = ref[16][i]/sqrt(counts[16][i]);}
    else {refError[16][i] = ref[16][i];}
    if(counts[17][i] > 0) {refError[17][i] = ref[17][i]/sqrt(counts[17][i]);}
    else {refError[17][i] = ref[17][i];}
    if(counts[18][i] > 0) {refError[18][i] = ref[18][i]/sqrt(counts[18][i]);}
    else {refError[18][i] = ref[18][i];}
    if(counts[19][i] > 0) {refError[19][i] = ref[19][i]/sqrt(counts[19][i]);}
    else {refError[19][i] = ref[19][i];}
    if(counts[20][i] > 0) {refError[20][i] = ref[20][i]/sqrt(counts[20][i]);}
    else {refError[20][i] = ref[20][i];}
    if(counts[21][i] > 0) {refError[21][i] = ref[21][i]/sqrt(counts[21][i]);}
    else {refError[21][i] = ref[21][i];}
    if(counts[22][i] > 0) {refError[22][i] = ref[22][i]/sqrt(counts[22][i]);}
    else {refError[22][i] = ref[22][i];}
    if(counts[23][i] > 0) {refError[23][i] = ref[23][i]/sqrt(counts[23][i]);}
    else {refError[23][i] = ref[23][i];}
    if(counts[24][i] > 0) {refError[24][i] = ref[24][i]/sqrt(counts[24][i]);}
    else {refError[24][i] = ref[24][i];}
    if(counts[25][i] > 0) {refError[25][i] = ref[25][i]/sqrt(counts[25][i]);}
    else {refError[25][i] = ref[25][i];}
    if(counts[26][i] > 0) {refError[26][i] = ref[26][i]/sqrt(counts[26][i]);}
    else {refError[26][i] = ref[26][i];}
    if(counts[27][i] > 0) {refError[27][i] = ref[27][i]/sqrt(counts[27][i]);}
    else {refError[27][i] = ref[27][i];}
    if(counts[28][i] > 0) {refError[28][i] = ref[28][i]/sqrt(counts[28][i]);}
    else {refError[28][i] = ref[28][i];}
    if(counts[29][i] > 0) {refError[29][i] = ref[29][i]/sqrt(counts[29][i]);}
    else {refError[29][i] = ref[29][i];}
    if(counts[30][i] > 0) {refError[30][i] = ref[30][i]/sqrt(counts[30][i]);}
    else {refError[30][i] = ref[30][i];}
    if(counts[31][i] > 0) {refError[31][i] = ref[31][i]/sqrt(counts[31][i]);}
    else {refError[31][i] = ref[31][i];}
    if(counts[32][i] > 0) {refError[32][i] = ref[32][i]/sqrt(counts[32][i]);}
    else {refError[32][i] = ref[32][i];}
    if(counts[33][i] > 0) {refError[33][i] = ref[33][i]/sqrt(counts[33][i]);}
    else {refError[33][i] = ref[33][i];}
    if(counts[34][i] > 0) {refError[34][i] = ref[34][i]/sqrt(counts[34][i]);}
    else {refError[34][i] = ref[34][i];}
    if(counts[35][i] > 0) {refError[35][i] = ref[35][i]/sqrt(counts[35][i]);}
    else {refError[35][i] = ref[35][i];}
    if(counts[36][i] > 0) {refError[36][i] = ref[36][i]/sqrt(counts[36][i]);}
    else {refError[36][i] = ref[36][i];}
    if(counts[37][i] > 0) {refError[37][i] = ref[37][i]/sqrt(counts[37][i]);}
    else {refError[37][i] = ref[37][i];}
    if(counts[38][i] > 0) {refError[38][i] = ref[38][i]/sqrt(counts[38][i]);}
    else {refError[38][i] = ref[38][i];}
    if(counts[39][i] > 0) {refError[39][i] = ref[39][i]/sqrt(counts[39][i]);}
    else {refError[39][i] = ref[39][i];}
    if(counts[40][i] > 0) {refError[40][i] = ref[40][i]/sqrt(counts[40][i]);}
    else {refError[40][i] = ref[40][i];}
    if(counts[41][i] > 0) {refError[41][i] = ref[41][i]/sqrt(counts[41][i]);}
    else {refError[41][i] = ref[41][i];}
    if(counts[42][i] > 0) {refError[42][i] = ref[42][i]/sqrt(counts[42][i]);}
    else {refError[42][i] = ref[42][i];}
    if(counts[43][i] > 0) {refError[43][i] = ref[43][i]/sqrt(counts[43][i]);}
    else {refError[43][i] = ref[43][i];}
    if(counts[44][i] > 0) {refError[44][i] = ref[44][i]/sqrt(counts[44][i]);}
    else {refError[44][i] = ref[44][i];}
    if(counts[45][i] > 0) {refError[45][i] = ref[45][i]/sqrt(counts[45][i]);}
    else {refError[45][i] = ref[45][i];}
    if(counts[46][i] > 0) {refError[46][i] = ref[46][i]/sqrt(counts[46][i]);}
    else {refError[46][i] = ref[46][i];}
    if(counts[47][i] > 0) {refError[47][i] = ref[47][i]/sqrt(counts[47][i]);}
    else {refError[47][i] = ref[47][i];}
    if(counts[48][i] > 0) {refError[48][i] = ref[48][i]/sqrt(counts[48][i]);}
    else {refError[48][i] = ref[48][i];}
    if(counts[49][i] > 0) {refError[49][i] = ref[49][i]/sqrt(counts[49][i]);}
    else {refError[49][i] = ref[49][i];}
    if(counts[50][i] > 0) {refError[50][i] = ref[50][i]/sqrt(counts[50][i]);}
    else {refError[50][i] = ref[50][i];}
    if(counts[51][i] > 0) {refError[51][i] = ref[51][i]/sqrt(counts[51][i]);}
    else {refError[51][i] = ref[51][i];}
    if(counts[52][i] > 0) {refError[52][i] = ref[52][i]/sqrt(counts[52][i]);}
    else {refError[52][i] = ref[52][i];}
    if(counts[53][i] > 0) {refError[53][i] = ref[53][i]/sqrt(counts[53][i]);}
    else {refError[53][i] = ref[53][i];}
    if(counts[54][i] > 0) {refError[54][i] = ref[54][i]/sqrt(counts[54][i]);}
    else {refError[54][i] = ref[54][i];}
    if(counts[55][i] > 0) {refError[55][i] = ref[55][i]/sqrt(counts[55][i]);}
    else {refError[55][i] = ref[55][i];}
    if(counts[56][i] > 0) {refError[56][i] = ref[56][i]/sqrt(counts[56][i]);}
    else {refError[56][i] = ref[56][i];}
    if(counts[57][i] > 0) {refError[57][i] = ref[57][i]/sqrt(counts[57][i]);}
    else {refError[57][i] = ref[57][i];}
    if(counts[58][i] > 0) {refError[58][i] = ref[58][i]/sqrt(counts[58][i]);}
    else {refError[58][i] = ref[58][i];}
    if(counts[59][i] > 0) {refError[59][i] = ref[59][i]/sqrt(counts[59][i]);}
    else {refError[59][i] = ref[59][i];}
    if(counts[60][i] > 0) {refError[60][i] = ref[60][i]/sqrt(counts[60][i]);}
    else {refError[60][i] = ref[60][i];}
    if(counts[61][i] > 0) {refError[61][i] = ref[61][i]/sqrt(counts[61][i]);}
    else {refError[61][i] = ref[61][i];}
    if(counts[62][i] > 0) {refError[62][i] = ref[62][i]/sqrt(counts[62][i]);}
    else {refError[62][i] = ref[62][i];}
    if(counts[63][i] > 0) {refError[63][i] = ref[63][i]/sqrt(counts[63][i]);}
    else {refError[63][i] = ref[63][i];}
    if(counts[64][i] > 0) {refError[64][i] = ref[64][i]/sqrt(counts[64][i]);}
    else {refError[64][i] = ref[64][i];}
    if(counts[65][i] > 0) {refError[65][i] = ref[65][i]/sqrt(counts[65][i]);}
    else {refError[65][i] = ref[65][i];}
    if(counts[66][i] > 0) {refError[66][i] = ref[66][i]/sqrt(counts[66][i]);}
    else {refError[66][i] = ref[66][i];}
    if(counts[67][i] > 0) {refError[67][i] = ref[67][i]/sqrt(counts[67][i]);}
    else {refError[67][i] = ref[67][i];}
    if(counts[68][i] > 0) {refError[68][i] = ref[68][i]/sqrt(counts[68][i]);}
    else {refError[68][i] = ref[68][i];}
    if(counts[69][i] > 0) {refError[69][i] = ref[69][i]/sqrt(counts[69][i]);}
    else {refError[69][i] = ref[69][i];}
    if(counts[70][i] > 0) {refError[70][i] = ref[70][i]/sqrt(counts[70][i]);}
    else {refError[70][i] = ref[70][i];}
    if(counts[71][i] > 0) {refError[71][i] = ref[71][i]/sqrt(counts[71][i]);}
    else {refError[71][i] = ref[71][i];}
    if(counts[72][i] > 0) {refError[72][i] = ref[72][i]/sqrt(counts[72][i]);}
    else {refError[72][i] = ref[72][i];}
    if(counts[73][i] > 0) {refError[73][i] = ref[73][i]/sqrt(counts[73][i]);}
    else {refError[73][i] = ref[73][i];}
    if(counts[74][i] > 0) {refError[74][i] = ref[74][i]/sqrt(counts[74][i]);}
    else {refError[74][i] = ref[74][i];}
    if(counts[75][i] > 0) {refError[75][i] = ref[75][i]/sqrt(counts[75][i]);}
    else {refError[75][i] = ref[75][i];}
    if(counts[76][i] > 0) {refError[76][i] = ref[76][i]/sqrt(counts[76][i]);}
    else {refError[76][i] = ref[76][i];}
    if(counts[77][i] > 0) {refError[77][i] = ref[77][i]/sqrt(counts[77][i]);}
    else {refError[77][i] = ref[77][i];}
    if(counts[78][i] > 0) {refError[78][i] = ref[78][i]/sqrt(counts[78][i]);}
    else {refError[78][i] = ref[78][i];}

    myOutFile0 << lambda[0][i] << ' ' << ref[0][i] << ' ' << refError[0][i] << "\n";
    myOutFile1 << lambda[1][i] << ' ' << ref[1][i] << ' ' << refError[1][i] << "\n";
    myOutFile2 << lambda[2][i] << ' ' << ref[2][i] << ' ' << refError[2][i] << "\n";
    myOutFile3 << lambda[3][i] << ' ' << ref[3][i] << ' ' << refError[3][i] << "\n";
    myOutFile4 << lambda[4][i] << ' ' << ref[4][i] << ' ' << refError[4][i] << "\n";
    myOutFile5 << lambda[5][i] << ' ' << ref[5][i] << ' ' << refError[5][i] << "\n";
    myOutFile6 << lambda[6][i] << ' ' << ref[6][i] << ' ' << refError[6][i] << "\n";
    myOutFile7 << lambda[7][i] << ' ' << ref[7][i] << ' ' << refError[7][i] << "\n";
    myOutFile8 << lambda[8][i] << ' ' << ref[8][i] << ' ' << refError[8][i] << "\n";
    myOutFile9 << lambda[9][i] << ' ' << ref[9][i] << ' ' << refError[9][i] << "\n";
    myOutFile10 << lambda[10][i] << ' ' << ref[10][i] << ' ' << refError[10][i] << "\n";
    myOutFile11 << lambda[11][i] << ' ' << ref[11][i] << ' ' << refError[11][i] << "\n";
    myOutFile12 << lambda[12][i] << ' ' << ref[12][i] << ' ' << refError[12][i] << "\n";
    myOutFile13 << lambda[13][i] << ' ' << ref[13][i] << ' ' << refError[13][i] << "\n";
    myOutFile14 << lambda[14][i] << ' ' << ref[14][i] << ' ' << refError[14][i] << "\n";
    myOutFile15 << lambda[15][i] << ' ' << ref[15][i] << ' ' << refError[15][i] << "\n";
    myOutFile16 << lambda[16][i] << ' ' << ref[16][i] << ' ' << refError[16][i] << "\n";
    myOutFile17 << lambda[17][i] << ' ' << ref[17][i] << ' ' << refError[17][i] << "\n";
    myOutFile18 << lambda[18][i] << ' ' << ref[18][i] << ' ' << refError[18][i] << "\n";
    myOutFile19 << lambda[19][i] << ' ' << ref[19][i] << ' ' << refError[19][i] << "\n";
    myOutFile20 << lambda[20][i] << ' ' << ref[20][i] << ' ' << refError[20][i] << "\n";
    myOutFile21 << lambda[21][i] << ' ' << ref[21][i] << ' ' << refError[21][i] << "\n";
    myOutFile22 << lambda[22][i] << ' ' << ref[22][i] << ' ' << refError[22][i] << "\n";
    myOutFile23 << lambda[23][i] << ' ' << ref[23][i] << ' ' << refError[23][i] << "\n";
    myOutFile24 << lambda[24][i] << ' ' << ref[24][i] << ' ' << refError[24][i] << "\n";
    myOutFile25 << lambda[25][i] << ' ' << ref[25][i] << ' ' << refError[25][i] << "\n";
    myOutFile26 << lambda[26][i] << ' ' << ref[26][i] << ' ' << refError[26][i] << "\n";
    myOutFile27 << lambda[27][i] << ' ' << ref[27][i] << ' ' << refError[27][i] << "\n";
    myOutFile28 << lambda[28][i] << ' ' << ref[28][i] << ' ' << refError[28][i] << "\n";
    myOutFile29 << lambda[29][i] << ' ' << ref[29][i] << ' ' << refError[29][i] << "\n";
    myOutFile30 << lambda[30][i] << ' ' << ref[30][i] << ' ' << refError[30][i] << "\n";
    myOutFile31 << lambda[31][i] << ' ' << ref[31][i] << ' ' << refError[31][i] << "\n";
    myOutFile32 << lambda[32][i] << ' ' << ref[32][i] << ' ' << refError[32][i] << "\n";
    myOutFile33 << lambda[33][i] << ' ' << ref[33][i] << ' ' << refError[33][i] << "\n";
    myOutFile34 << lambda[34][i] << ' ' << ref[34][i] << ' ' << refError[34][i] << "\n";
    myOutFile35 << lambda[35][i] << ' ' << ref[35][i] << ' ' << refError[35][i] << "\n";
    myOutFile36 << lambda[36][i] << ' ' << ref[36][i] << ' ' << refError[36][i] << "\n";
    myOutFile37 << lambda[37][i] << ' ' << ref[37][i] << ' ' << refError[37][i] << "\n";
    myOutFile38 << lambda[38][i] << ' ' << ref[38][i] << ' ' << refError[38][i] << "\n";
    myOutFile39 << lambda[39][i] << ' ' << ref[39][i] << ' ' << refError[39][i] << "\n";
    myOutFile40 << lambda[40][i] << ' ' << ref[40][i] << ' ' << refError[40][i] << "\n";
    myOutFile41 << lambda[41][i] << ' ' << ref[41][i] << ' ' << refError[41][i] << "\n";
    myOutFile42 << lambda[42][i] << ' ' << ref[42][i] << ' ' << refError[42][i] << "\n";
    myOutFile43 << lambda[43][i] << ' ' << ref[43][i] << ' ' << refError[43][i] << "\n";
    myOutFile44 << lambda[44][i] << ' ' << ref[44][i] << ' ' << refError[44][i] << "\n";
    myOutFile45 << lambda[45][i] << ' ' << ref[45][i] << ' ' << refError[45][i] << "\n";
    myOutFile46 << lambda[46][i] << ' ' << ref[46][i] << ' ' << refError[46][i] << "\n";
    myOutFile47 << lambda[47][i] << ' ' << ref[47][i] << ' ' << refError[47][i] << "\n";
    myOutFile48 << lambda[48][i] << ' ' << ref[48][i] << ' ' << refError[48][i] << "\n";
    myOutFile49 << lambda[49][i] << ' ' << ref[49][i] << ' ' << refError[49][i] << "\n";
    myOutFile50 << lambda[50][i] << ' ' << ref[50][i] << ' ' << refError[50][i] << "\n";
    myOutFile51 << lambda[51][i] << ' ' << ref[51][i] << ' ' << refError[51][i] << "\n";
    myOutFile52 << lambda[52][i] << ' ' << ref[52][i] << ' ' << refError[52][i] << "\n";
    myOutFile53 << lambda[53][i] << ' ' << ref[53][i] << ' ' << refError[53][i] << "\n";
    myOutFile54 << lambda[54][i] << ' ' << ref[54][i] << ' ' << refError[54][i] << "\n";
    myOutFile55 << lambda[55][i] << ' ' << ref[55][i] << ' ' << refError[55][i] << "\n";
    myOutFile56 << lambda[56][i] << ' ' << ref[56][i] << ' ' << refError[56][i] << "\n";
    myOutFile57 << lambda[57][i] << ' ' << ref[57][i] << ' ' << refError[57][i] << "\n";
    myOutFile58 << lambda[58][i] << ' ' << ref[58][i] << ' ' << refError[58][i] << "\n";
    myOutFile59 << lambda[59][i] << ' ' << ref[59][i] << ' ' << refError[59][i] << "\n";
    myOutFile60 << lambda[60][i] << ' ' << ref[60][i] << ' ' << refError[60][i] << "\n";
    myOutFile61 << lambda[61][i] << ' ' << ref[61][i] << ' ' << refError[61][i] << "\n";
    myOutFile62 << lambda[62][i] << ' ' << ref[62][i] << ' ' << refError[62][i] << "\n";
    myOutFile63 << lambda[63][i] << ' ' << ref[63][i] << ' ' << refError[63][i] << "\n";
    myOutFile64 << lambda[64][i] << ' ' << ref[64][i] << ' ' << refError[64][i] << "\n";
    myOutFile65 << lambda[65][i] << ' ' << ref[65][i] << ' ' << refError[65][i] << "\n";
    myOutFile66 << lambda[66][i] << ' ' << ref[66][i] << ' ' << refError[66][i] << "\n";
    myOutFile67 << lambda[67][i] << ' ' << ref[67][i] << ' ' << refError[67][i] << "\n";
    myOutFile68 << lambda[68][i] << ' ' << ref[68][i] << ' ' << refError[68][i] << "\n";
    myOutFile69 << lambda[69][i] << ' ' << ref[69][i] << ' ' << refError[69][i] << "\n";
    myOutFile70 << lambda[70][i] << ' ' << ref[70][i] << ' ' << refError[70][i] << "\n";
    myOutFile71 << lambda[71][i] << ' ' << ref[71][i] << ' ' << refError[71][i] << "\n";
    myOutFile72 << lambda[72][i] << ' ' << ref[72][i] << ' ' << refError[72][i] << "\n";
    myOutFile73 << lambda[73][i] << ' ' << ref[73][i] << ' ' << refError[73][i] << "\n";
    myOutFile74 << lambda[74][i] << ' ' << ref[74][i] << ' ' << refError[74][i] << "\n";
    myOutFile75 << lambda[75][i] << ' ' << ref[75][i] << ' ' << refError[75][i] << "\n";
    myOutFile76 << lambda[76][i] << ' ' << ref[76][i] << ' ' << refError[76][i] << "\n";
    myOutFile77 << lambda[77][i] << ' ' << ref[77][i] << ' ' << refError[77][i] << "\n";
    myOutFile78 << lambda[78][i] << ' ' << ref[78][i] << ' ' << refError[78][i] << "\n";

  }

  /*myOutFile0.close();
  myOutFile1.close();
  myOutFile2.close();
  myOutFile3.close();
  myOutFile4.close();
  myOutFile5.close();
  myOutFile6.close();
  myOutFile7.close();
  myOutFile8.close();
  myOutFile9.close();
  myOutFile10.close();
  myOutFile11.close();
  myOutFile12.close();
  myOutFile13.close();
  myOutFile14.close();
  myOutFile15.close();
  myOutFile16.close();
  myOutFile17.close();
  myOutFile18.close();
  myOutFile19.close();
  myOutFile20.close();
  myOutFile21.close();
  myOutFile22.close();
  myOutFile23.close();
  myOutFile24.close();
  myOutFile25.close();
  myOutFile26.close();
  myOutFile27.close();
  myOutFile28.close();
  myOutFile29.close();
  myOutFile30.close();
  myOutFile31.close();
  myOutFile32.close();
  myOutFile33.close();
  myOutFile34.close();
  myOutFile35.close();
  myOutFile36.close();
  myOutFile37.close();
  myOutFile38.close();
  myOutFile39.close();
  myOutFile40.close();
  myOutFile41.close();
  myOutFile42.close();
  myOutFile43.close();
  myOutFile44.close();
  myOutFile45.close();
  myOutFile46.close();
  myOutFile47.close();
  myOutFile48.close();
  myOutFile49.close();
  myOutFile50.close();
  myOutFile51.close();
  myOutFile52.close();
  myOutFile53.close();
  myOutFile54.close();
  myOutFile55.close();
  myOutFile56.close();
  myOutFile57.close();
  myOutFile58.close();
  myOutFile59.close();
  myOutFile60.close();
  myOutFile61.close();
  myOutFile62.close();
  myOutFile63.close();
  myOutFile64.close();
  myOutFile65.close();
  myOutFile66.close();
  myOutFile67.close();
  myOutFile68.close();
  myOutFile69.close();
  myOutFile70.close();
  myOutFile71.close();
  myOutFile72.close();
  myOutFile73.close();
  myOutFile74.close();
  myOutFile75.close();
  myOutFile76.close();
  myOutFile77.close();
  myOutFile78.close();*/

  for(int inc=0;inc<files;inc++) {
    Form("myOutFile%i.close()",inc);
  }

  //Now produce reflectivity graph for 90 degrees

  TCanvas *final_canvas3 = new TCanvas("final_canvas3","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr3;
  hr3 = new TH2F("hr3",graphname1,1000,170.0,890.0,140,0.0,1.10);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr3->GetYaxis()->SetLabelColor(1);
  hr3->GetYaxis()->SetTitleColor(1);
  hr3->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr3->GetYaxis()->SetTitleOffset(1.3);
  hr3->GetXaxis()->SetLabelColor(1);
  hr3->GetXaxis()->SetTitleColor(1);
  hr3->SetXTitle(xTitle);
  hr3->Draw();

  TGraphErrors *gr1a_ref_nist = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr1a_ref_nist->SetMarkerColor(kBlue);
  gr1a_ref_nist->SetMarkerStyle(20);   
  gr1a_ref_nist->SetMarkerSize(0.35);
  //gr1_nist->SetFillColor(0);
  //gr1a_ref_nist->SetLineColor(kBlue);
  gr1a_ref_nist->Draw("P");

  //  TGraphErrors *gr2a_ref = new TGraphErrors(points,lambda[31], ref[31], dummyError, refError[31]);
  TGraphErrors *gr2a_ref = new TGraphErrors(points,lambda[30], ref[30], dummyError, refError[30]);
  gr2a_ref->SetMarkerColor(kRed);
  gr2a_ref->SetMarkerStyle(20);   
  gr2a_ref->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2a_ref->Draw("P");

  TGraphErrors *gr5a_ref = new TGraphErrors(points,lambda[15], ref[15], dummyError, refError[15]);
  gr5a_ref->SetMarkerColor(kTeal+1);
  gr5a_ref->SetMarkerStyle(20);
  gr5a_ref->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5a_ref->Draw("P");

  TGraphErrors *gr6a_ref = new TGraphErrors(points,lambda[20], ref[20], dummyError, refError[20]);
  gr6a_ref->SetMarkerColor(kGreen+2);
  gr6a_ref->SetMarkerStyle(20);
  gr6a_ref->SetMarkerSize(0.35);
  //  gr6->SetFillColor(0);
  gr6a_ref->Draw("P");

  TGraphErrors *gr7a_ref = new TGraphErrors(points,lambda[25], ref[25], dummyError, refError[25]);
  gr7a_ref->SetMarkerColor(kOrange);
  gr7a_ref->SetMarkerStyle(20); 
  gr7a_ref->SetMarkerSize(0.35);
  //  gr7->SetFillColor(0);
  gr7a_ref->Draw("P");

  TGraphErrors *gr8a_ref = new TGraphErrors(points,lambda[71], ref[71], dummyError, refError[71]);
  gr8a_ref->SetMarkerColor(kGreen);
  gr8a_ref->SetMarkerStyle(20); 
  gr8a_ref->SetMarkerSize(0.35);
  //  gr8->SetFillColor(0);
  gr8a_ref->Draw("P");

  TGraphErrors *gr9a_ref = new TGraphErrors(points,lambda[36], ref[36], dummyError, refError[36]);
  gr9a_ref->SetMarkerColor(kMagenta);
  gr9a_ref->SetMarkerStyle(20); 
  gr9a_ref->SetMarkerSize(0.35);
  //  gr9->SetFillColor(0);
  gr9a_ref->Draw("P");

  TGraphErrors *gr10a_ref = new TGraphErrors(points,lambda[0], ref[0], dummyError, refError[0]);
  gr10a_ref->SetMarkerColor(kCyan);
  gr10a_ref->SetMarkerStyle(20); 
  gr10a_ref->SetMarkerSize(0.35);
  //  gr9->SetFillColor(0);
  gr10a_ref->Draw("P");

  TGraphErrors *gr4a_ref = new TGraphErrors(points,lambda[47], ref[47], dummyError, refError[47]);
  gr4a_ref->SetMarkerColor(kOrange+5);
  gr4a_ref->SetMarkerStyle(20);
  gr4a_ref->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4a_ref->Draw("P");

  //  TGraphErrors *gr3a_ref = new TGraphErrors(points,lambda[8], ref[8], dummyError, refError[8]);
  TGraphErrors *gr3a_ref = new TGraphErrors(points,lambda[43], ref[43], dummyError, refError[43]);
  gr3a_ref->SetMarkerColor(kMagenta+2);
  gr3a_ref->SetMarkerStyle(20);   
  gr3a_ref->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3a_ref->Draw("P");

  sprintf(GraphText1,"Reflectivity (~90 degree)");
  TPaveLabel *refl_90_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  refl_90_pt->SetBorderSize(0);
  refl_90_pt->SetTextColor(1);
  refl_90_pt->SetTextSize(0.85);
  refl_90_pt->SetFillColor(0);
  refl_90_pt->Draw();

  TPaveLabel *NIST_standard_pt = new TPaveLabel(0.7,0.46, 0.89,0.50,"NIST Standard","NDC");
  NIST_standard_pt->SetBorderSize(0);
  NIST_standard_pt->SetTextColor(kBlue);
  NIST_standard_pt->SetTextSize(0.75);
  NIST_standard_pt->SetFillColor(0);
  NIST_standard_pt->SetFillStyle(0);
  NIST_standard_pt->Draw();

  TPaveLabel *mil_1_mylar_pt = new TPaveLabel(0.7,0.42, 0.89,0.46,"1 mil Al. Mylar","NDC");
  mil_1_mylar_pt->SetBorderSize(0);
  mil_1_mylar_pt->SetTextColor(kRed);
  mil_1_mylar_pt->SetTextSize(0.75);
  mil_1_mylar_pt->SetFillColor(0);
  mil_1_mylar_pt->SetFillStyle(0);
  mil_1_mylar_pt->Draw();

  //  TPaveLabel *miro_IV_pt = new TPaveLabel(0.7,0.38, 0.89,0.42,"Miro-silver 4270","NDC");
  TPaveLabel *miro_IV_pt = new TPaveLabel(0.7,0.38, 0.89,0.42,"Miro IV","NDC");
  miro_IV_pt->SetBorderSize(0);
  miro_IV_pt->SetTextColor(kMagenta+2);
  miro_IV_pt->SetTextSize(0.75);
  miro_IV_pt->SetFillColor(0);
  miro_IV_pt->SetFillStyle(0);
  miro_IV_pt->Draw();

  TPaveLabel *miro_silver_sun_pt = new TPaveLabel(0.7,0.34, 0.89,0.38,"Miro-silver Sun","NDC");
  miro_silver_sun_pt->SetBorderSize(0);
  miro_silver_sun_pt->SetTextColor(kOrange+5);
  miro_silver_sun_pt->SetTextSize(0.75);
  miro_silver_sun_pt->SetFillColor(0);
  miro_silver_sun_pt->SetFillStyle(0);
  miro_silver_sun_pt->Draw();

  TPaveLabel *alzak_Ag_pt = new TPaveLabel(0.7,0.30, 0.89,0.34,"Alzak Ag.","NDC");
  alzak_Ag_pt->SetBorderSize(0);
  alzak_Ag_pt->SetTextColor(kTeal+1);
  alzak_Ag_pt->SetTextSize(0.75);
  alzak_Ag_pt->SetFillColor(0);
  alzak_Ag_pt->SetFillStyle(0);
  alzak_Ag_pt->Draw();

  TPaveLabel *alzak_Al_pt = new TPaveLabel(0.7,0.26, 0.89,0.30,"Alzak Al.", "NDC");
  alzak_Al_pt->SetBorderSize(0);
  alzak_Al_pt->SetTextColor(kGreen+2);
  alzak_Al_pt->SetTextSize(0.75);
  alzak_Al_pt->SetFillColor(0);
  alzak_Al_pt->SetFillStyle(0);
  alzak_Al_pt->Draw();

  TPaveLabel *anolux_I_pt = new TPaveLabel(0.7,0.22, 0.89,0.26,"Anolux I", "NDC");
  anolux_I_pt->SetBorderSize(0);
  anolux_I_pt->SetTextColor(kOrange);
  anolux_I_pt->SetTextSize(0.75);
  anolux_I_pt->SetFillColor(0);
  anolux_I_pt->SetFillStyle(0);
  anolux_I_pt->Draw();

  TPaveLabel *anolux_UVS_pt = new TPaveLabel(0.7,0.18, 0.89,0.22,"Anolux UVS", "NDC");
  anolux_UVS_pt->SetBorderSize(0);
  anolux_UVS_pt->SetTextColor(kGreen);
  anolux_UVS_pt->SetTextSize(0.75);
  anolux_UVS_pt->SetFillColor(0);
  anolux_UVS_pt->SetFillStyle(0);
  anolux_UVS_pt->Draw();

  TPaveLabel *miro_silver_27_pt = new TPaveLabel(0.7,0.14, 0.89,0.18,"Miro-silver 27", "NDC");
  miro_silver_27_pt->SetBorderSize(0);
  miro_silver_27_pt->SetTextColor(kMagenta);
  miro_silver_27_pt->SetTextSize(0.75);
  miro_silver_27_pt->SetFillColor(0);
  miro_silver_27_pt->SetFillStyle(0);
  miro_silver_27_pt->Draw();

  TPaveLabel *miro_2000Ag_pt = new TPaveLabel(0.7,0.10, 0.89,0.14,"Miro 2000ag (Diffuse)", "NDC");
  miro_2000Ag_pt->SetBorderSize(0);
  miro_2000Ag_pt->SetTextColor(kCyan);
  miro_2000Ag_pt->SetTextSize(0.75);
  miro_2000Ag_pt->SetFillColor(0);
  miro_2000Ag_pt->SetFillStyle(0);
  miro_2000Ag_pt->Draw();

  //TLine *l = new TLine(250,0,250,1.1);
  //l->SetLineStyle(2);
  //l->SetLineColor(kRed);
  //l->SetLineWidth(2);
  //l->Draw("same");

  TBox *b2 = new TBox(170,0,250,1.1);
  b2->SetFillStyle(3001);
  b2->SetLineColor(0);
  b2->SetFillColor(19);
  b2->Draw();

  sprintf(printname,"reflectivity_90deg.pdf");
  final_canvas3->Print(printname);


  //********************************************************************
  //Now produce reflectivity graph for Miro 2000Ag at different angles

  TCanvas *final_canvas4 = new TCanvas("final_canvas4","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr4;
  hr4 = new TH2F("hr4",graphname1,1000,170.0,890.0,140,0.0,1.10);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr4->GetYaxis()->SetLabelColor(1);
  hr4->GetYaxis()->SetTitleColor(1);
  hr4->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr3->GetYaxis()->SetTitleOffset(1.3);
  hr4->GetXaxis()->SetLabelColor(1);
  hr4->GetXaxis()->SetTitleColor(1);
  hr4->SetXTitle(xTitle);
  hr4->Draw();

  TGraphErrors *gr1b_ref_nist = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr1b_ref_nist->SetMarkerColor(kBlue);
  gr1b_ref_nist->SetMarkerStyle(20);   
  gr1b_ref_nist->SetMarkerSize(0.35);
  //gr1b_ref_nist->Draw("P");

  TGraphErrors *gr2b_ref = new TGraphErrors(points,lambda[0], ref[0], dummyError, refError[0]);
  gr2b_ref->SetMarkerColor(kCyan);
  gr2b_ref->SetMarkerStyle(20);   
  gr2b_ref->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2b_ref->Draw("P");

  TGraphErrors *gr3b_ref = new TGraphErrors(points,lambda[6], ref[6], dummyError, refError[6]);
  gr3b_ref->SetMarkerColor(kCyan+1);
  gr3b_ref->SetMarkerStyle(20);   
  gr3b_ref->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3b_ref->Draw("P");

  TGraphErrors *gr4b_ref = new TGraphErrors(points,lambda[5], ref[5], dummyError, refError[5]);
  gr4b_ref->SetMarkerColor(kCyan+3);
  gr4b_ref->SetMarkerStyle(20);
  gr4b_ref->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4b_ref->Draw("P");

  TGraphErrors *gr5b_ref = new TGraphErrors(points,lambda[4], ref[4], dummyError, refError[4]);
  gr5b_ref->SetMarkerColor(kCyan+4);
  gr5b_ref->SetMarkerStyle(20);   
  gr5b_ref->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5b_ref->Draw("P");


  sprintf(GraphText1,"Reflectivity: Miro 2000Ag (Diffuse)");
  TPaveLabel *miro_2000Ag_a_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  miro_2000Ag_a_pt->SetBorderSize(0);
  miro_2000Ag_a_pt->SetTextColor(1);
  miro_2000Ag_a_pt->SetTextSize(0.85);
  miro_2000Ag_a_pt->SetFillColor(0);
  miro_2000Ag_a_pt->Draw();

  TPaveLabel *miro_2000Ag_b_pt = new TPaveLabel(0.7,0.35, 0.89,0.40,"90 degree","NDC");
  miro_2000Ag_b_pt->SetBorderSize(0);
  miro_2000Ag_b_pt->SetTextColor(kCyan);
  miro_2000Ag_b_pt->SetTextSize(0.75);
  miro_2000Ag_b_pt->SetFillColor(0);
  miro_2000Ag_b_pt->SetFillStyle(0);
  miro_2000Ag_b_pt->Draw();

  TPaveLabel *miro_2000Ag_c_pt = new TPaveLabel(0.7,0.30, 0.89,0.35,"60 degree","NDC");
  miro_2000Ag_c_pt->SetBorderSize(0);
  miro_2000Ag_c_pt->SetTextColor(kCyan+1);
  miro_2000Ag_c_pt->SetTextSize(0.75);
  miro_2000Ag_c_pt->SetFillColor(0);
  miro_2000Ag_c_pt->SetFillStyle(0);
  miro_2000Ag_c_pt->Draw();

  TPaveLabel *miro_2000Ag_d_pt = new TPaveLabel(0.7,0.25, 0.89,0.30,"45 degree", "NDC");
  miro_2000Ag_d_pt->SetBorderSize(0);
  miro_2000Ag_d_pt->SetTextColor(kCyan+3);
  miro_2000Ag_d_pt->SetTextSize(0.75);
  miro_2000Ag_d_pt->SetFillColor(0);
  miro_2000Ag_d_pt->SetFillStyle(0);
  miro_2000Ag_d_pt->Draw();

  TPaveLabel *miro_2000Ag_e_pt = new TPaveLabel(0.7,0.20, 0.89,0.25,"30 degree", "NDC");
  miro_2000Ag_e_pt->SetBorderSize(0);
  miro_2000Ag_e_pt->SetTextColor(kCyan+4);
  miro_2000Ag_e_pt->SetTextSize(0.75);
  miro_2000Ag_e_pt->SetFillColor(0);
  miro_2000Ag_e_pt->SetFillStyle(0);
  miro_2000Ag_e_pt->Draw();


  TBox *b_miro2000 = new TBox(170,0,250,1.1);
  b_miro2000->SetFillStyle(3001);
  b_miro2000->SetLineColor(0);
  b_miro2000->SetFillColor(19);
  b_miro2000->Draw();

  sprintf(printname,"reflectivity_2000Ag.pdf");
  final_canvas4->Print(printname);

  //********************************************************************
  //Now produce reflectivity graph for 4270 at different angles

  TCanvas *final_canvas5 = new TCanvas("final_canvas5","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr5;
  hr5 = new TH2F("hr5",graphname1,1000,170.0,890.0,140,0.0,1.10);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr5->GetYaxis()->SetLabelColor(1);
  hr5->GetYaxis()->SetTitleColor(1);
  hr5->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr3->GetYaxis()->SetTitleOffset(1.3);
  hr5->GetXaxis()->SetLabelColor(1);
  hr5->GetXaxis()->SetTitleColor(1);
  hr5->SetXTitle(xTitle);
  hr5->Draw();

  TGraphErrors *gr1c_ref_nist = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr1c_ref_nist->SetMarkerColor(kBlue);
  gr1c_ref_nist->SetMarkerStyle(20);   
  gr1c_ref_nist->SetMarkerSize(0.35);
  //gr1c_ref_nist->Draw("P");

  TGraphErrors *gr2c_ref = new TGraphErrors(points,lambda[9], ref[9], dummyError, refError[9]);
  gr2c_ref->SetMarkerColor(kMagenta);
  gr2c_ref->SetMarkerStyle(20);   
  gr2c_ref->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2c_ref->Draw("P");

  TGraphErrors *gr3c_ref = new TGraphErrors(points,lambda[14], ref[14], dummyError, refError[14]);
  gr3c_ref->SetMarkerColor(kMagenta+1);
  gr3c_ref->SetMarkerStyle(20);   
  gr3c_ref->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3c_ref->Draw("P");

  TGraphErrors *gr4c_ref = new TGraphErrors(points,lambda[13], ref[13], dummyError, refError[13]);
  gr4c_ref->SetMarkerColor(kMagenta+3);
  gr4c_ref->SetMarkerStyle(20);   
  gr4c_ref->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4c_ref->Draw("P");

  TGraphErrors *gr5c_ref = new TGraphErrors(points,lambda[12], ref[12], dummyError, refError[12]);
  gr5c_ref->SetMarkerColor(kMagenta+4);
  gr5c_ref->SetMarkerStyle(20);   
  gr5c_ref->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5c_ref->Draw("P");


  sprintf(GraphText1,"Reflectivity: Miro-silver 4270");
  TPaveLabel *miro_silver4270_a_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  miro_silver4270_a_pt->SetBorderSize(0);
  miro_silver4270_a_pt->SetTextColor(1);
  miro_silver4270_a_pt->SetTextSize(0.85);
  miro_silver4270_a_pt->SetFillColor(0);
  miro_silver4270_a_pt->Draw();

  TPaveLabel *miro_silver4270_b_pt = new TPaveLabel(0.7,0.35, 0.89,0.40,"90 degree","NDC");
  miro_silver4270_b_pt->SetBorderSize(0);
  miro_silver4270_b_pt->SetTextColor(kMagenta);
  miro_silver4270_b_pt->SetTextSize(0.75);
  miro_silver4270_b_pt->SetFillColor(0);
  miro_silver4270_b_pt->SetFillStyle(0);
  miro_silver4270_b_pt->Draw();

  TPaveLabel *miro_silver4270_c_pt = new TPaveLabel(0.7,0.30, 0.89,0.35,"60 degree","NDC");
  miro_silver4270_c_pt->SetBorderSize(0);
  miro_silver4270_c_pt->SetTextColor(kMagenta+1);
  miro_silver4270_c_pt->SetTextSize(0.75);
  miro_silver4270_c_pt->SetFillColor(0);
  miro_silver4270_c_pt->SetFillStyle(0);
  miro_silver4270_c_pt->Draw();

  TPaveLabel *miro_silver4270_d_pt = new TPaveLabel(0.7,0.25, 0.89,0.30,"45 degree", "NDC");
  miro_silver4270_d_pt->SetBorderSize(0);
  miro_silver4270_d_pt->SetTextColor(kMagenta+3);
  miro_silver4270_d_pt->SetTextSize(0.75);
  miro_silver4270_d_pt->SetFillColor(0);
  miro_silver4270_d_pt->SetFillStyle(0);
  miro_silver4270_d_pt->Draw();

  TPaveLabel *miro_silver4270_e_pt = new TPaveLabel(0.7,0.20, 0.89,0.25,"30 degree", "NDC");
  miro_silver4270_e_pt->SetBorderSize(0);
  miro_silver4270_e_pt->SetTextColor(kMagenta+4);
  miro_silver4270_e_pt->SetTextSize(0.75);
  miro_silver4270_e_pt->SetFillColor(0);
  miro_silver4270_e_pt->SetFillStyle(0);
  miro_silver4270_e_pt->Draw();

  TBox *b_mirosilver4270 = new TBox(170,0,250,1.1);
  b_mirosilver4270->SetFillStyle(3001);
  b_mirosilver4270->SetLineColor(0);
  b_mirosilver4270->SetFillColor(19);
  b_mirosilver4270->Draw();

  sprintf(printname,"reflectivity_4270.pdf");
  final_canvas5->Print(printname);

  //********************************************************************
  //Now produce reflectivity graph for Alzak Ag at different angles

  TCanvas *final_canvas6 = new TCanvas("final_canvas6","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr6;
  hr6 = new TH2F("hr6",graphname1,1000,170.0,890.0,140,0.0,1.10);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr6->GetYaxis()->SetLabelColor(1);
  hr6->GetYaxis()->SetTitleColor(1);
  hr6->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr3->GetYaxis()->SetTitleOffset(1.3);
  hr6->GetXaxis()->SetLabelColor(1);
  hr6->GetXaxis()->SetTitleColor(1);
  hr6->SetXTitle(xTitle);
  hr6->Draw();

  TGraphErrors *gr1d_ref_nist = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr1d_ref_nist->SetMarkerColor(kBlue);
  gr1d_ref_nist->SetMarkerStyle(20);   
  gr1d_ref_nist->SetMarkerSize(0.35);
  //gr1d_ref_nist->Draw("P");

  TGraphErrors *gr2d_ref = new TGraphErrors(points,lambda[15], ref[15], dummyError, refError[15]);
  gr2d_ref->SetMarkerColor(kTeal);
  gr2d_ref->SetMarkerStyle(20);   
  gr2d_ref->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2d_ref->Draw("P");

  TGraphErrors *gr3d_ref = new TGraphErrors(points,lambda[19], ref[19], dummyError, refError[19]);
  gr3d_ref->SetMarkerColor(kTeal+1);
  gr3d_ref->SetMarkerStyle(20);   
  gr3d_ref->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3d_ref->Draw("P");

  TGraphErrors *gr4d_ref = new TGraphErrors(points,lambda[18], ref[18], dummyError, refError[18]);
  gr4d_ref->SetMarkerColor(kTeal+4);
  gr4d_ref->SetMarkerStyle(20);   
  gr4d_ref->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4d_ref->Draw("P");

  TGraphErrors *gr5d_ref = new TGraphErrors(points,lambda[17], ref[17], dummyError, refError[17]);
  gr5d_ref->SetMarkerColor(kTeal+3);
  gr5d_ref->SetMarkerStyle(20);   
  gr5d_ref->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5d_ref->Draw("P");


  sprintf(GraphText1,"Reflectivity: Alzak (Ag)");
  TPaveLabel *alzak_Ag_a_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  alzak_Ag_a_pt->SetBorderSize(0);
  alzak_Ag_a_pt->SetTextColor(1);
  alzak_Ag_a_pt->SetTextSize(0.85);
  alzak_Ag_a_pt->SetFillColor(0);
  alzak_Ag_a_pt->Draw();

  TPaveLabel *alzak_Ag_b_pt = new TPaveLabel(0.7,0.35, 0.89,0.40,"90 degree","NDC");
  alzak_Ag_b_pt->SetBorderSize(0);
  alzak_Ag_b_pt->SetTextColor(kTeal);
  alzak_Ag_b_pt->SetTextSize(0.75);
  alzak_Ag_b_pt->SetFillColor(0);
  alzak_Ag_b_pt->SetFillStyle(0);
  alzak_Ag_b_pt->Draw();

  TPaveLabel *alzak_Ag_c_pt = new TPaveLabel(0.7,0.30, 0.89,0.35,"60 degree","NDC");
  alzak_Ag_c_pt->SetBorderSize(0);
  alzak_Ag_c_pt->SetTextColor(kTeal+1);
  alzak_Ag_c_pt->SetTextSize(0.75);
  alzak_Ag_c_pt->SetFillColor(0);
  alzak_Ag_c_pt->SetFillStyle(0);
  alzak_Ag_c_pt->Draw();

  TPaveLabel *alzak_Ag_d_pt = new TPaveLabel(0.7,0.25, 0.89,0.30,"45 degree", "NDC");
  alzak_Ag_d_pt->SetBorderSize(0);
  alzak_Ag_d_pt->SetTextColor(kTeal+4);
  alzak_Ag_d_pt->SetTextSize(0.75);
  alzak_Ag_d_pt->SetFillColor(0);
  alzak_Ag_d_pt->SetFillStyle(0);
  alzak_Ag_d_pt->Draw();

  TPaveLabel *alzak_Ag_e_pt = new TPaveLabel(0.7,0.20, 0.89,0.25,"30 degree", "NDC");
  alzak_Ag_e_pt->SetBorderSize(0);
  alzak_Ag_e_pt->SetTextColor(kTeal+3);
  alzak_Ag_e_pt->SetTextSize(0.75);
  alzak_Ag_e_pt->SetFillColor(0);
  alzak_Ag_e_pt->SetFillStyle(0);
  alzak_Ag_e_pt->Draw();

  TBox *b_alzak_Ag = new TBox(170,0,250,1.1);
  b_alzak_Ag->SetFillStyle(3001);
  b_alzak_Ag->SetLineColor(0);
  b_alzak_Ag->SetFillColor(19);
  b_alzak_Ag->Draw();

  sprintf(printname,"reflectivity_alzakAg.pdf");
  final_canvas6->Print(printname);

  //********************************************************************
  //Now produce reflectivity graph for Alzal Al. at different angles

  TCanvas *final_canvas7 = new TCanvas("final_canvas7","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr7;
  hr7 = new TH2F("hr7",graphname1,1000,170.0,890.0,140,0.0,1.10);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr7->GetYaxis()->SetLabelColor(1);
  hr7->GetYaxis()->SetTitleColor(1);
  hr7->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr3->GetYaxis()->SetTitleOffset(1.3);
  hr7->GetXaxis()->SetLabelColor(1);
  hr7->GetXaxis()->SetTitleColor(1);
  hr7->SetXTitle(xTitle);
  hr7->Draw();

  TGraphErrors *gr1e_ref_nist = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr1e_ref_nist->SetMarkerColor(kBlue);
  gr1e_ref_nist->SetMarkerStyle(20);   
  gr1e_ref_nist->SetMarkerSize(0.35);
  //gr1e_ref_nist->Draw("P");

  TGraphErrors *gr2e_ref = new TGraphErrors(points,lambda[20], ref[20], dummyError, refError[20]);
  gr2e_ref->SetMarkerColor(kGreen);
  gr2e_ref->SetMarkerStyle(20);   
  gr2e_ref->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2e_ref->Draw("P");

  TGraphErrors *gr3e_ref = new TGraphErrors(points,lambda[24], ref[24], dummyError, refError[24]);
  gr3e_ref->SetMarkerColor(kGreen+1);
  gr3e_ref->SetMarkerStyle(20);   
  gr3e_ref->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3e_ref->Draw("P");

  TGraphErrors *gr4e_ref = new TGraphErrors(points,lambda[23], ref[23], dummyError, refError[23]);
  gr4e_ref->SetMarkerColor(kGreen+3);
  gr4e_ref->SetMarkerStyle(20);   
  gr4e_ref->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4e_ref->Draw("P");

  TGraphErrors *gr5e_ref = new TGraphErrors(points,lambda[22], ref[22], dummyError, refError[22]);
  gr5e_ref->SetMarkerColor(kGreen+4);
  gr5e_ref->SetMarkerStyle(20);   
  gr5e_ref->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5e_ref->Draw("P");


  sprintf(GraphText1,"Reflectivity: Alzak (Al)");
  TPaveLabel *alzak_Al_a_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  alzak_Al_a_pt->SetBorderSize(0);
  alzak_Al_a_pt->SetTextColor(1);
  alzak_Al_a_pt->SetTextSize(0.85);
  alzak_Al_a_pt->SetFillColor(0);
  alzak_Al_a_pt->Draw();

  TPaveLabel *alzak_Al_b_pt = new TPaveLabel(0.7,0.35, 0.89,0.40,"90 degree","NDC");
  alzak_Al_b_pt->SetBorderSize(0);
  alzak_Al_b_pt->SetTextColor(kGreen);
  alzak_Al_b_pt->SetTextSize(0.75);
  alzak_Al_b_pt->SetFillColor(0);
  alzak_Al_b_pt->SetFillStyle(0);
  alzak_Al_b_pt->Draw();

  TPaveLabel *alzak_Al_c_pt = new TPaveLabel(0.7,0.30, 0.89,0.35,"60 degree","NDC");
  alzak_Al_c_pt->SetBorderSize(0);
  alzak_Al_c_pt->SetTextColor(kGreen+1);
  alzak_Al_c_pt->SetTextSize(0.75);
  alzak_Al_c_pt->SetFillColor(0);
  alzak_Al_c_pt->SetFillStyle(0);
  alzak_Al_c_pt->Draw();

  TPaveLabel *alzak_Al_d_pt = new TPaveLabel(0.7,0.25, 0.89,0.30,"45 degree", "NDC");
  alzak_Al_d_pt->SetBorderSize(0);
  alzak_Al_d_pt->SetTextColor(kGreen+3);
  alzak_Al_d_pt->SetTextSize(0.75);
  alzak_Al_d_pt->SetFillColor(0);
  alzak_Al_d_pt->SetFillStyle(0);
  alzak_Al_d_pt->Draw();

  TPaveLabel *alzak_Al_e_pt = new TPaveLabel(0.7,0.20, 0.89,0.25,"30 degree", "NDC");
  alzak_Al_e_pt->SetBorderSize(0);
  alzak_Al_e_pt->SetTextColor(kGreen+4);
  alzak_Al_e_pt->SetTextSize(0.75);
  alzak_Al_e_pt->SetFillColor(0);
  alzak_Al_e_pt->SetFillStyle(0);
  alzak_Al_e_pt->Draw();

  TBox *b_alzak_Al = new TBox(170,0,250,1.1);
  b_alzak_Al->SetFillStyle(3001);
  b_alzak_Al->SetLineColor(0);
  b_alzak_Al->SetFillColor(19);
  b_alzak_Al->Draw();

  sprintf(printname,"reflectivity_alzakAl.pdf");
  final_canvas7->Print(printname);

  //********************************************************************
  //Now produce reflectivity graph for UVS at different angles

  TCanvas *final_canvas8 = new TCanvas("final_canvas8","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr8;
  hr8 = new TH2F("hr8",graphname1,1000,170.0,890.0,140,0.0,1.10);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr8->GetYaxis()->SetLabelColor(1);
  hr8->GetYaxis()->SetTitleColor(1);
  hr8->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr3->GetYaxis()->SetTitleOffset(1.3);
  hr8->GetXaxis()->SetLabelColor(1);
  hr8->GetXaxis()->SetTitleColor(1);
  hr8->SetXTitle(xTitle);
  hr8->Draw();

  TGraphErrors *gr1f_ref_nist = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr1f_ref_nist->SetMarkerColor(kBlue);
  gr1f_ref_nist->SetMarkerStyle(20);   
  gr1f_ref_nist->SetMarkerSize(0.35);
  //gr1f_ref_nist->Draw("P");

  TGraphErrors *gr2f_ref = new TGraphErrors(points,lambda[71], ref[71], dummyError, refError[71]);
  gr2f_ref->SetMarkerColor(kGreen);
  gr2f_ref->SetMarkerStyle(20);   
  gr2f_ref->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2f_ref->Draw("P");

  TGraphErrors *gr3f_ref = new TGraphErrors(points,lambda[77], ref[77], dummyError, refError[77]);
  gr3f_ref->SetMarkerColor(kGreen+1);
  gr3f_ref->SetMarkerStyle(20);   
  gr3f_ref->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3f_ref->Draw("P");

  TGraphErrors *gr4f_ref = new TGraphErrors(points,lambda[76], ref[76], dummyError, refError[76]);
  gr4f_ref->SetMarkerColor(kGreen+3);
  gr4f_ref->SetMarkerStyle(20);   
  gr4f_ref->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4f_ref->Draw("P");

  TGraphErrors *gr5f_ref = new TGraphErrors(points,lambda[75], ref[75], dummyError, refError[75]);
  gr5f_ref->SetMarkerColor(kGreen+4);
  gr5f_ref->SetMarkerStyle(20);   
  gr5f_ref->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5f_ref->Draw("P");


  sprintf(GraphText1,"Reflectivity: Anolux UVS");
  TPaveLabel *anolux_UVS_a_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  anolux_UVS_a_pt->SetBorderSize(0);
  anolux_UVS_a_pt->SetTextColor(1);
  anolux_UVS_a_pt->SetTextSize(0.85);
  anolux_UVS_a_pt->SetFillColor(0);
  anolux_UVS_a_pt->Draw();

  TPaveLabel *anolux_UVS_b_pt = new TPaveLabel(0.7,0.35, 0.89,0.40,"90 degree","NDC");
  anolux_UVS_b_pt->SetBorderSize(0);
  anolux_UVS_b_pt->SetTextColor(kGreen);
  anolux_UVS_b_pt->SetTextSize(0.75);
  anolux_UVS_b_pt->SetFillColor(0);
  anolux_UVS_b_pt->SetFillStyle(0);
  anolux_UVS_b_pt->Draw();

  TPaveLabel *anolux_UVS_c_pt = new TPaveLabel(0.7,0.30, 0.89,0.35,"60 degree","NDC");
  anolux_UVS_c_pt->SetBorderSize(0);
  anolux_UVS_c_pt->SetTextColor(kGreen+1);
  anolux_UVS_c_pt->SetTextSize(0.75);
  anolux_UVS_c_pt->SetFillColor(0);
  anolux_UVS_c_pt->SetFillStyle(0);
  anolux_UVS_c_pt->Draw();

  TPaveLabel *anolux_UVS_d_pt = new TPaveLabel(0.7,0.25, 0.89,0.30,"45 degree", "NDC");
  anolux_UVS_d_pt->SetBorderSize(0);
  anolux_UVS_d_pt->SetTextColor(kGreen+3);
  anolux_UVS_d_pt->SetTextSize(0.75);
  anolux_UVS_d_pt->SetFillColor(0);
  anolux_UVS_d_pt->SetFillStyle(0);
  anolux_UVS_d_pt->Draw();

  TPaveLabel *anolux_UVS_e_pt = new TPaveLabel(0.7,0.20, 0.89,0.25,"30 degree", "NDC");
  anolux_UVS_e_pt->SetBorderSize(0);
  anolux_UVS_e_pt->SetTextColor(kGreen+4);
  anolux_UVS_e_pt->SetTextSize(0.75);
  anolux_UVS_e_pt->SetFillColor(0);
  anolux_UVS_e_pt->SetFillStyle(0);
  anolux_UVS_e_pt->Draw();

  TBox *b_anolux_UVS = new TBox(170,0,250,1.1);
  b_anolux_UVS->SetFillStyle(3001);
  b_anolux_UVS->SetLineColor(0);
  b_anolux_UVS->SetFillColor(19);
  b_anolux_UVS->Draw();

  sprintf(printname,"reflectivity_uvs.pdf");
  final_canvas8->Print(printname);


  //********************************************************************
  //Now produce reflectivity graph for miro 27 at different angles

  TCanvas *final_canvas9 = new TCanvas("final_canvas9","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr9;
  hr9 = new TH2F("hr9",graphname1,1000,170.0,890.0,140,0.0,1.10);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr9->GetYaxis()->SetLabelColor(1);
  hr9->GetYaxis()->SetTitleColor(1);
  hr9->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr3->GetYaxis()->SetTitleOffset(1.3);
  hr9->GetXaxis()->SetLabelColor(1);
  hr9->GetXaxis()->SetTitleColor(1);
  hr9->SetXTitle(xTitle);
  hr9->Draw();

  TGraphErrors *gr1g_ref_nist = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr1g_ref_nist->SetMarkerColor(kBlue);
  gr1g_ref_nist->SetMarkerStyle(20);   
  gr1g_ref_nist->SetMarkerSize(0.35);
  //gr1g_ref_nist->Draw("P");

  TGraphErrors *gr2g_ref = new TGraphErrors(points,lambda[36], ref[36], dummyError, refError[36]);
  gr2g_ref->SetMarkerColor(kMagenta);
  gr2g_ref->SetMarkerStyle(20);   
  gr2g_ref->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2g_ref->Draw("P");

  TGraphErrors *gr3g_ref = new TGraphErrors(points,lambda[42], ref[42], dummyError, refError[42]);
  gr3g_ref->SetMarkerColor(kMagenta+1);
  gr3g_ref->SetMarkerStyle(20);   
  gr3g_ref->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3g_ref->Draw("P");

  TGraphErrors *gr4g_ref = new TGraphErrors(points,lambda[41], ref[41], dummyError, refError[41]);
  gr4g_ref->SetMarkerColor(kMagenta+3);
  gr4g_ref->SetMarkerStyle(20);   
  gr4g_ref->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4g_ref->Draw("P");

  TGraphErrors *gr5g_ref = new TGraphErrors(points,lambda[40], ref[40], dummyError, refError[40]);
  gr5g_ref->SetMarkerColor(kMagenta+4);
  gr5g_ref->SetMarkerStyle(20);   
  gr5g_ref->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5g_ref->Draw("P");


  sprintf(GraphText1,"Reflectivity: Miro-silver 27");
  TPaveLabel *Mirosilver_27_a_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  Mirosilver_27_a_pt->SetBorderSize(0);
  Mirosilver_27_a_pt->SetTextColor(1);
  Mirosilver_27_a_pt->SetTextSize(0.85);
  Mirosilver_27_a_pt->SetFillColor(0);
  Mirosilver_27_a_pt->Draw();

  TPaveLabel *Mirosilver_27_b_pt = new TPaveLabel(0.7,0.35, 0.89,0.40,"90 degree","NDC");
  Mirosilver_27_b_pt->SetBorderSize(0);
  Mirosilver_27_b_pt->SetTextColor(kMagenta);
  Mirosilver_27_b_pt->SetTextSize(0.75);
  Mirosilver_27_b_pt->SetFillColor(0);
  Mirosilver_27_b_pt->SetFillStyle(0);
  Mirosilver_27_b_pt->Draw();

  TPaveLabel *Mirosilver_27_c_pt = new TPaveLabel(0.7,0.30, 0.89,0.35,"60 degree","NDC");
  Mirosilver_27_c_pt->SetBorderSize(0);
  Mirosilver_27_c_pt->SetTextColor(kMagenta+1);
  Mirosilver_27_c_pt->SetTextSize(0.75);
  Mirosilver_27_c_pt->SetFillColor(0);
  Mirosilver_27_c_pt->SetFillStyle(0);
  Mirosilver_27_c_pt->Draw();

  TPaveLabel *Mirosilver_27_d_pt = new TPaveLabel(0.7,0.25, 0.89,0.30,"45 degree", "NDC");
  Mirosilver_27_d_pt->SetBorderSize(0);
  Mirosilver_27_d_pt->SetTextColor(kMagenta+3);
  Mirosilver_27_d_pt->SetTextSize(0.75);
  Mirosilver_27_d_pt->SetFillColor(0);
  Mirosilver_27_d_pt->SetFillStyle(0);
  Mirosilver_27_d_pt->Draw();

  TPaveLabel *Mirosilver_27_e_pt = new TPaveLabel(0.7,0.20, 0.89,0.25,"30 degree", "NDC");
  Mirosilver_27_e_pt->SetBorderSize(0);
  Mirosilver_27_e_pt->SetTextColor(kMagenta+4);
  Mirosilver_27_e_pt->SetTextSize(0.75);
  Mirosilver_27_e_pt->SetFillColor(0);
  Mirosilver_27_e_pt->SetFillStyle(0);
  Mirosilver_27_e_pt->Draw();

  TBox *b_Mirosilver_27 = new TBox(170,0,250,1.1);
  b_Mirosilver_27->SetFillStyle(3001);
  b_Mirosilver_27->SetLineColor(0);
  b_Mirosilver_27->SetFillColor(19);
  b_Mirosilver_27->Draw();

  sprintf(printname,"reflectivity_miro27.pdf");
  final_canvas9->Print(printname);


  //********************************************************************
  //Now produce reflectivity graph for tyvek at different angles

  TCanvas *final_canvas10 = new TCanvas("final_canvas10","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);
  final_canvas10->SetLogy(1);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr10;
  hr10 = new TH2F("hr10",graphname1,1000,170.0,890.0,140,0.0,1.10);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr10->GetYaxis()->SetLabelColor(1);
  hr10->GetYaxis()->SetTitleColor(1);
  hr10->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr3->GetYaxis()->SetTitleOffset(1.3);
  hr10->GetXaxis()->SetLabelColor(1);
  hr10->GetXaxis()->SetTitleColor(1);
  hr10->SetXTitle(xTitle);
  hr10->Draw();

  TGraphErrors *gr1h_ref_nist = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr1h_ref_nist->SetMarkerColor(kBlue);
  gr1h_ref_nist->SetMarkerStyle(20);   
  gr1h_ref_nist->SetMarkerSize(0.35);
  //gr1h_ref_nist->Draw("P");

  TGraphErrors *gr2h_ref = new TGraphErrors(points,lambda[65], ref[65], dummyError, refError[65]);
  gr2h_ref->SetMarkerColor(kOrange);
  gr2h_ref->SetMarkerStyle(20);   
  gr2h_ref->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2h_ref->Draw("P");

  TGraphErrors *gr3h_ref = new TGraphErrors(points,lambda[69], ref[69], dummyError, refError[69]);
  gr3h_ref->SetMarkerColor(kOrange+1);
  gr3h_ref->SetMarkerStyle(20);   
  gr3h_ref->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3h_ref->Draw("P");

  TGraphErrors *gr4h_ref = new TGraphErrors(points,lambda[68], ref[68], dummyError, refError[68]);
  gr4h_ref->SetMarkerColor(kOrange+4);
  gr4h_ref->SetMarkerStyle(20);   
  gr4h_ref->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4h_ref->Draw("P");

  TGraphErrors *gr5h_ref = new TGraphErrors(points,lambda[67], ref[67], dummyError, refError[67]);
  gr5h_ref->SetMarkerColor(kOrange+3);
  gr5h_ref->SetMarkerStyle(20);   
  gr5h_ref->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5h_ref->Draw("P");

  sprintf(GraphText1,"Reflectivity: Tyvek 1073B (diffuse)");
  TPaveLabel *tyvek_1073_a_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  tyvek_1073_a_pt->SetBorderSize(0);
  tyvek_1073_a_pt->SetTextColor(1);
  tyvek_1073_a_pt->SetTextSize(0.85);
  tyvek_1073_a_pt->SetFillColor(0);
  tyvek_1073_a_pt->Draw();

  TPaveLabel *tyvek_1073_b_pt = new TPaveLabel(0.7,0.35, 0.89,0.40,"90 degree","NDC");
  tyvek_1073_b_pt->SetBorderSize(0);
  tyvek_1073_b_pt->SetTextColor(kOrange);
  tyvek_1073_b_pt->SetTextSize(0.75);
  tyvek_1073_b_pt->SetFillColor(0);
  tyvek_1073_b_pt->SetFillStyle(0);
  tyvek_1073_b_pt->Draw();

  TPaveLabel *tyvek_1073_c_pt = new TPaveLabel(0.7,0.30, 0.89,0.35,"60 degree","NDC");
  tyvek_1073_c_pt->SetBorderSize(0);
  tyvek_1073_c_pt->SetTextColor(kOrange+1);
  tyvek_1073_c_pt->SetTextSize(0.75);
  tyvek_1073_c_pt->SetFillColor(0);
  tyvek_1073_c_pt->SetFillStyle(0);
  tyvek_1073_c_pt->Draw();

  TPaveLabel *tyvek_1073_d_pt = new TPaveLabel(0.7,0.25, 0.89,0.30,"45 degree", "NDC");
  tyvek_1073_d_pt->SetBorderSize(0);
  tyvek_1073_d_pt->SetTextColor(kOrange+4);
  tyvek_1073_d_pt->SetTextSize(0.75);
  tyvek_1073_d_pt->SetFillColor(0);
  tyvek_1073_d_pt->SetFillStyle(0);
  tyvek_1073_d_pt->Draw();

  TPaveLabel *tyvek_1073_e_pt = new TPaveLabel(0.7,0.20, 0.89,0.25,"30 degree", "NDC");
  tyvek_1073_e_pt->SetBorderSize(0);
  tyvek_1073_e_pt->SetTextColor(kOrange+3);
  tyvek_1073_e_pt->SetTextSize(0.75);
  tyvek_1073_e_pt->SetFillColor(0);
  tyvek_1073_e_pt->SetFillStyle(0);
  tyvek_1073_e_pt->Draw();

  TBox *b_tyvek = new TBox(170,0,250,1.1);
  b_tyvek->SetFillStyle(3001);
  b_tyvek->SetLineColor(0);
  b_tyvek->SetFillColor(19);
  b_tyvek->Draw();

  sprintf(printname,"reflectivity_tyvek.pdf");
  final_canvas10->Print(printname);


  //********************************************************************
  //Now produce reflectivity graph for nist at different angles

  TCanvas *final_canvas11 = new TCanvas("final_canvas11","Reflectivity Study Graph",0,0,600,400);
  
  gStyle->SetOptStat(kFALSE);
  final_canvas10->SetLogy(1);

  //  sprintf(graphname1,"#pi^{0} Photoproduction yield vs. #theta_{#pi^{0}} (%s)",histTitlePart);
  sprintf(graphname1,"");

  TH2F *hr11;
  hr11 = new TH2F("hr11",graphname1,1000,170.0,890.0,140,0.0,1.10);

  gStyle->SetTitleX(0.18);
  //  mass_ALL_th_e->SetTitleOffset(-10.0, "X");
  //  gStyle->SetLabelSize(0.05,"X");
  
  sprintf(xTitle,"Wavelength (nm)");  
  sprintf(yTitle,"Reflectivity");  
  hr11->GetYaxis()->SetLabelColor(1);
  hr11->GetYaxis()->SetTitleColor(1);
  hr11->SetYTitle(yTitle);
  //    hr1->GetXaxis()->CenterTitle();
  //    hr1->GetYaxis()->CenterTitle();
  //hr3->GetYaxis()->SetTitleOffset(1.3);
  hr11->GetXaxis()->SetLabelColor(1);
  hr11->GetXaxis()->SetTitleColor(1);
  hr11->SetXTitle(xTitle);
  hr11->Draw();

  TGraphErrors *gr1i_ref_nist = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr1i_ref_nist->SetMarkerColor(kBlue);
  gr1i_ref_nist->SetMarkerStyle(20);   
  gr1i_ref_nist->SetMarkerSize(0.35);
  //gr1i_ref_nist->Draw("P");

  TGraphErrors *gr2i_ref = new TGraphErrors(points,lambda[std], ref[std], dummyError, refError[std]);
  gr2i_ref->SetMarkerColor(kBlue);
  gr2i_ref->SetMarkerStyle(20);   
  gr2i_ref->SetMarkerSize(0.35);
  //  gr2->SetFillColor(0);
  gr2i_ref->Draw("P");

  TGraphErrors *gr3i_ref = new TGraphErrors(points,lambda[64], ref[64], dummyError, refError[64]);
  gr3i_ref->SetMarkerColor(kBlue+1);
  gr3i_ref->SetMarkerStyle(20);   
  gr3i_ref->SetMarkerSize(0.35);
  //  gr3->SetFillColor(0);
  gr3i_ref->Draw("P");

  TGraphErrors *gr4i_ref = new TGraphErrors(points,lambda[60], ref[60], dummyError, refError[60]);
  gr4i_ref->SetMarkerColor(kBlue+3);
  gr4i_ref->SetMarkerStyle(20);   
  gr4i_ref->SetMarkerSize(0.35);
  //  gr4->SetFillColor(0);
  gr4i_ref->Draw("P");

  TGraphErrors *gr5i_ref = new TGraphErrors(points,lambda[56], ref[56], dummyError, refError[56]);
  gr5i_ref->SetMarkerColor(kBlue+4);
  gr5i_ref->SetMarkerStyle(20);   
  gr5i_ref->SetMarkerSize(0.35);
  //  gr5->SetFillColor(0);
  gr5i_ref->Draw("P");

  sprintf(GraphText1,"Reflectivity: Nist Standard");
  TPaveLabel *NIST_standard_a_pt = new TPaveLabel(0.15,0.91, 0.80,0.97,GraphText1,"NDC");
  NIST_standard_a_pt->SetBorderSize(0);
  NIST_standard_a_pt->SetTextColor(1);
  NIST_standard_a_pt->SetTextSize(0.85);
  NIST_standard_a_pt->SetFillColor(0);
  NIST_standard_a_pt->Draw();

  TPaveLabel *NIST_standard_b_pt = new TPaveLabel(0.7,0.35, 0.89,0.40,"90 degree","NDC");
  NIST_standard_b_pt->SetBorderSize(0);
  NIST_standard_b_pt->SetTextColor(kBlue);
  NIST_standard_b_pt->SetTextSize(0.75);
  NIST_standard_b_pt->SetFillColor(0);
  NIST_standard_b_pt->SetFillStyle(0);
  NIST_standard_b_pt->Draw();

  TPaveLabel *NIST_standard_c_pt = new TPaveLabel(0.7,0.30, 0.89,0.35,"60 degree","NDC");
  NIST_standard_c_pt->SetBorderSize(0);
  NIST_standard_c_pt->SetTextColor(kBlue+1);
  NIST_standard_c_pt->SetTextSize(0.75);
  NIST_standard_c_pt->SetFillColor(0);
  NIST_standard_c_pt->SetFillStyle(0);
  NIST_standard_c_pt->Draw();

  TPaveLabel *NIST_standard_d_pt = new TPaveLabel(0.7,0.25, 0.89,0.30,"45 degree", "NDC");
  NIST_standard_d_pt->SetBorderSize(0);
  NIST_standard_d_pt->SetTextColor(kBlue+3);
  NIST_standard_d_pt->SetTextSize(0.75);
  NIST_standard_d_pt->SetFillColor(0);
  NIST_standard_d_pt->SetFillStyle(0);
  NIST_standard_d_pt->Draw();

  TPaveLabel *NIST_standard_e_pt = new TPaveLabel(0.7,0.20, 0.89,0.25,"30 degree", "NDC");
  NIST_standard_e_pt->SetBorderSize(0);
  NIST_standard_e_pt->SetTextColor(kBlue+4);
  NIST_standard_e_pt->SetTextSize(0.75);
  NIST_standard_e_pt->SetFillColor(0);
  NIST_standard_e_pt->SetFillStyle(0);
  NIST_standard_e_pt->Draw();

  TBox *b_NIST_standard = new TBox(170,0,250,1.1);
  b_NIST_standard->SetFillStyle(3001);
  b_NIST_standard->SetLineColor(0);
  b_NIST_standard->SetFillColor(19);
  b_NIST_standard->Draw();

  sprintf(printname,"reflectivity_nist.pdf");
  final_canvas11->Print(printname);

  return 0;
}
