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

    TString path;
    bool server = 1;
    if(server){
    	path = "/home/jkovoor/analysis_20Nedn/build/";
    }else{
    	path = "/mnt/c/Users/jerom/Desktop/12Be_exp/NEXT_MSU_REA6/build/";
    }
    

    TFile *f = new TFile(path + "histogramsTest_EFT.root");

    TF1* fit_func1 = new TF1 ( "fit_func1","[0]*TMath::Exp(-pow((x-[1]),2)/(2*[2]*[2]))",0,120 );
    fit_func1->SetParLimits (2,0.5,2);

    int NumModules = 11;

    TH2D *htof_qdc_psdgated[NumModules], *tof_qdc_TOFCorrected_psdgated[NumModules], *psd_qdc[NumModules], *position_psdgated[NumModules];
    TH1D *tof[NumModules], *tof_TOFCorrected[NumModules], *tof_psdgated[NumModules];

    


    for(int i = 0; i < NumModules; i++) {
      htof_qdc_psdgated[i] = (TH2D*)f->Get(Form("tof_qdc_psdgated_%d",i));
      tof_qdc_TOFCorrected_psdgated[i] = (TH2D*)f->Get(Form("tof_qdc_TOFCorrected_psdgated%d",i));
      psd_qdc[i] = (TH2D*)f->Get(Form("psd_qdc_%d",i));
      position_psdgated[i] = (TH2D*)f->Get(Form("position_psdgated_%d",i));
      tof[i] = (TH1D*)f->Get(Form("tof_%d",i));
      tof_TOFCorrected[i] = (TH1D*)f->Get(Form("tof_TOFCorrected_%d",i));
      tof_psdgated[i] = (TH1D*)f->Get(Form("tof_psdgated_%d",i));
    }



    //Search for peaks
    int npeaks=1;
    TSpectrum* s = new TSpectrum ( 2*npeaks );
    int nfound=0;
    double* txp = s->GetPositionX();
    
    //find peaks and fit it
    double gammaPeak[npeaks];
    double gammaPeakModule[NumModules];


    for ( int j=0; j<NumModules; j++ ){
        nfound = s->Search ( tof[j],2,"",0.2 );
        for ( int p=0; p<nfound; p++ ){gammaPeak[p] = txp[p];}
        gammaPeakModule[j] = gammaPeak[0];
        // std::cout << gammaPeakModule[j] << std::endl;
    }

    //open a txt file to store the positions of the peaks
    ofstream module_gammaPeak;
    module_gammaPeak.open (path + "../TOF_GammaPeaks.txt" );
    // module_gammaPeak << " Module    Peak  \n";

    int NumCanvas = 7;

    TCanvas *c[NumCanvas];

    for(int i = 0; i < NumCanvas; i++) {
        c[i] = new TCanvas (Form("c_%d",i));
        c[i]->Divide(3,4);
    }


    for(int i = 0; i < NumModules; i++) {
        c[0]->cd(i+1);
        htof_qdc_psdgated[i]->Draw("colz");
    }

    for(int i = 0; i < NumModules; i++) {
        c[1]->cd(i+1);
        psd_qdc[i]->Draw("colz");
    }

    for(int i = 0; i < NumModules; i++) {
        c[2]->cd(i+1);
        position_psdgated[i]->Draw("colz");
    }


    for(int i = 0; i < NumModules; i++) {
        c[3]->cd(i+1);
        fit_func1->SetParLimits ( 1,gammaPeakModule[i]-5,gammaPeakModule[i]+5 );
        tof[i]->Fit ( "fit_func1","","",90,120);
        module_gammaPeak << i << "\t"  << fit_func1->GetParameter ( 1 ) << endl;
        tof[i]->Draw();
    }

    for(int i = 0; i < NumModules; i++) {
        c[4]->cd(i+1);
        tof_psdgated[i]->Draw();
    }

    for(int i = 0; i < NumModules; i++) {
        c[5]->cd(i+1);
        tof_TOFCorrected[i]->Draw();
    }

    for(int i = 0; i < NumModules; i++) {
        c[6]->cd(i+1);
        tof_qdc_TOFCorrected_psdgated[i]->Draw("colz");
    }
}
