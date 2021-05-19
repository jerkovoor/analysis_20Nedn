using namespace std;

#include "TFile.h" 
#include "TMath.h"
#include <cmath>
#include "iostream"
#include "fstream"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TLegend.h"


void Ne20_histogramReader(){
    TString path = "/mnt/c/Users/jerom/Desktop/12Be_exp/NEXT_MSU_REA6/build/";

    TFile *f = new TFile(path + "histogramsTest.root");

    TH2D *htof_qdc_psdgated[11];
    TH2D *psd_qdc[11];


    for(int i = 0; i < 11; i++) {
      htof_qdc_psdgated[i] = (TH2D*)f->Get(Form("tof_qdc_psdgated_%d",i));
      psd_qdc[i] = (TH2D*)f->Get(Form("psd_qdc_%d",i));
    }

    TCanvas *d1 = new TCanvas ( "d1" );
    
    d1->Divide(3,4);

    for(int i = 0; i < 11; i++) {
        d1->cd(i+1);
        htof_qdc_psdgated[i]->Draw("colz");
    }
    TCanvas *d2 = new TCanvas ( "d2" );
    d2->Divide(3,4);

    for(int i = 0; i < 11; i++) {
        d2->cd(i+1);
        psd_qdc[i]->Draw("colz");
    }
}