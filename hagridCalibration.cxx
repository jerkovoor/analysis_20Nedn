using namespace std;

#include <TFile.h>
#include "TString.h"
#include "string"
#include "iostream"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include <vector>
#include "TF1.h"
#include "TSpectrum.h"
#include "fstream"
#include "TGraph.h"
#include "TCanvas.h"



void hagridCalibration(){

    int NoHagModules = 2;
    TGraph* gr[2];
    double module[2], peaks[2][4];//Two modules; origin, two 60Co peaks and La+K peak


    ifstream cal_peaks;
    cal_peaks.open("Hagrid_Co60_Peaks.txt");

    if(cal_peaks.is_open()){
        for(int i=0;i<NoHagModules;i++){
        cal_peaks >> module[i] >> peaks[i][0] >> peaks[i][1] >> peaks[i][2] >> peaks[i][3];
        }
    }else{
        cout << "No file found " << endl;
    }
    cal_peaks.close();


    ofstream CalParam;
    CalParam.open("Hagrid_Calibration_Parameters.txt");
    CalParam << " Module / gain / offset  \n";

    TF1 *fit_lin = new TF1 ( "fit_lin","[0]*x+[1]",0,100000);

    double Energy[4] = {0,1173.2,1332.5,1450};

    for(int i=0;i<NoHagModules;i++){
        gr[i] = new TGraph(4,peaks[i],Energy);
    }
    

    TCanvas *c1 = new TCanvas ( "c1" );
    c1->Divide ( 2,1 );


    for ( int i=0; i<NoHagModules; i++ ){
        c1->cd ( i+1 );
        gr[i]->Draw ( "AP*" );
        gr[i]->Fit ( "fit_lin","","",0,100000);
        CalParam << i << " "  << fit_lin->GetParameter ( 0 ) << " " << fit_lin->GetParameter ( 1 ) << endl;
    }
}