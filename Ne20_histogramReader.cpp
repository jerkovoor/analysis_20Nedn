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

    TH2D *htof_qdc_psdgated[11], *psd_qdc[11], *position_psdgated[11];
    TH1D *tof[11], *tof_psdgated[11];


    for(int i = 0; i < 11; i++) {
      htof_qdc_psdgated[i] = (TH2D*)f->Get(Form("tof_qdc_psdgated_%d",i));
      psd_qdc[i] = (TH2D*)f->Get(Form("psd_qdc_%d",i));
      position_psdgated[i] = (TH2D*)f->Get(Form("position_psdgated_%d",i));
      tof[i] = (TH1D*)f->Get(Form("tof_%d",i));
      tof_psdgated[i] = (TH1D*)f->Get(Form("tof_psdgated_%d",i));
    }

    int NumCanvas = 5;

    TCanvas *c[NumCanvas];

    for(int i = 0; i < NumCanvas; i++) {
        c[i] = new TCanvas (Form("c_%d",i));
        c[i]->Divide(3,4);
    }


    for(int i = 0; i < 11; i++) {
        c[0]->cd(i+1);
        htof_qdc_psdgated[i]->Draw("colz");
    }

    for(int i = 0; i < 11; i++) {
        c[1]->cd(i+1);
        psd_qdc[i]->Draw("colz");
    }

    for(int i = 0; i < 11; i++) {
        c[2]->cd(i+1);
        position_psdgated[i]->Draw("colz");
    }


    for(int i = 0; i < 11; i++) {
        c[3]->cd(i+1);
        tof[i]->Draw();
    }

    for(int i = 0; i < 11; i++) {
        c[4]->cd(i+1);
        tof_psdgated[i]->Draw();
    }
}