using namespace std;

#include "TFile.h" 
#include "TChain.h"
#include "TCutG.h"
#include "TVector3.h"
#include "TMath.h"
#include <cmath>
#include "iostream"
#include "fstream"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include <TRandom3.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>
// #include "EnergyLoss.h"


void singleRunTOF_shifting_20Ne(){
    bool server = 1;//Turn this on to run on the server

    TString InPath;

    if(server){
        InPath = "/home/jkovoor/data_20Nedn/root_files/";
    }else{
        InPath = "/mnt/c/Users/jerom/Desktop/12Be_exp/NEXT_MSU_REA6/data/";
    }


    TFile *f_out = new TFile(InPath + "Shifted_TOF.root","RECREATE");

    bool thinTarget = 1;
    // int runs[] = {19,42};
    int runs[] = {19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,50,51,52,53};

    // if(thinTarget){
    //     // int runs[] = {19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,50,51,52,53};
    //     int runs[] = {19,20};
    // }

    int len = sizeof(runs)/sizeof(runs[0]);

    TH2D *h_TOF_QDC_shifted[len][11];
    TH1D *h_TOF_shifted[len][11];
    TH1D *h_allRuns_TOF[11], *hagrid_CutLeftBanana_timeCut[2], *hagrid_CutRightBanana_timeCut[2];
    TH2D *h_allRuns_TOF_QDC[11], *tof_qdc_allRuns_hagridGated[11], *tof_qdc_psdgated[11];

    TH2D *tof_qdc_allRuns_allModules_hagridGated = new TH2D("tof_qdc_allRuns_allModules_hagridGated","tof_qdc_allRuns_allModules_hagridGated",300,-50,100,300,0,3E5);

    for(int i = 0; i < 2; i++) {
        hagrid_CutLeftBanana_timeCut[i] = new TH1D(Form("hagrid_CutLeftBanana_timeCut_%d",i),Form("Hagrid Energy with Left Banana and Time Cut [Module %d]",i),500,0,4000);
        hagrid_CutRightBanana_timeCut[i] = new TH1D(Form("hagrid_CutRightBanana_timeCut_%d",i),Form("Hagrid Energy with Right Banana and Time Cut [Module %d]",i),500,0,4000);
    }
    for(int i = 0; i < 11; i++) {
        h_allRuns_TOF_QDC[i] = new TH2D(Form("h_allRuns_TOF_QDC_%d",i),Form("h_allRuns_TOF_QDC [Module %d]",i),300,-50,100,300,0,3E5);
        h_allRuns_TOF[i] = new TH1D(Form("h_allRuns_TOF_%d",i),Form("h_allRuns_TOF [Module %d]",i),300,-50,100);
        tof_qdc_psdgated[i] = new TH2D(Form("tof_qdc_psdgated_%d",i),Form("Time of flight vs. QDC [Module %d] gated by PSD",i),300,-50,100,300,0,3E5);
        tof_qdc_allRuns_hagridGated[i] = new TH2D(Form("tof_qdc_allRuns_hagridGated_%d",i),Form("h_tof_qdc_allRuns_hagridGated [Module %d]",i),300,-50,100,300,0,3E5);
    }

    TFile *psdcut0, *bananaCuts;
    TCutG *psdCuts[11], *bananaCutLeft, *bananaCutRight;
    psdcut0 = TFile::Open("gates_Run50.root");
    bananaCuts = TFile::Open("BananaCuts.root");

    for(int i = 0; i < 11; i++) {
        psdCuts[i] = (TCutG*) psdcut0->Get(Form("psd_mod%d",i));
    }

    bananaCutLeft = (TCutG*) bananaCuts->Get("neutronBananaLeft");
    bananaCutRight = (TCutG*) bananaCuts->Get("neutronBananaRight");

    int runNo, NEXTmoduleID;
    double peakPosition;
    double GammaPeakPosition[55][11];

    double peakShift = 36.749; //from runs 42 to 55 including both

    std::ifstream module_gammaPeak("GammaPeaks_Run_Module_Runs16-55_shifted.txt");
    if(module_gammaPeak.is_open()){
        while(module_gammaPeak >> runNo >> NEXTmoduleID >> peakPosition) {
            if(runNo>41 && runNo<56){
                GammaPeakPosition[runNo-1][NEXTmoduleID] = peakPosition-peakShift;
            }else{
                GammaPeakPosition[runNo-1][NEXTmoduleID] = peakPosition;
            }
            // std::cout << runNo << "\t" << moduleID << "\t" << GammaPeakPosition[runNo-1][moduleID] << std::endl;
        }
    }else{
        std::cout << "Gamma peaks file not found" << std::endl;
    }
    module_gammaPeak.close();

    double gain, offset;
    int HagridmoduleID;
    std::pair<double, double> hagridCalibration[2];// Two modules


    //////////////////Hagrid Calibration////////////////////

    std::ifstream hagridCalParam("Hagrid_Calibration_Parameters.txt");
    if(hagridCalParam.is_open()){
        while(hagridCalParam >> HagridmoduleID >> gain >> offset) {
            hagridCalibration[HagridmoduleID] = std::make_pair(gain, offset);
            //std::cout << moduleID << "\t" << hagridCalibration[moduleID].first << hagridCalibration[moduleID].second << std::endl;
        }
    }else{
        std::cout << "Calibration file not found" << std::endl;
    }
    hagridCalParam.close();

	for(int num=0;num<len;num++){

        string f_name=Form(InPath + "run%d_DD.root",runs[num]);// new decode
        TFile* f_in = new TFile (f_name.c_str());
		TTree* tr_out = (TTree*)f_in->Get("PixTree");


        TTreeReader     fReader(tr_out);

        TTreeReaderArray<Double_t> logic_vec__lastProtonPulseTime = {fReader, "logic_vec_.lastProtonPulseTime"};

        TTreeReaderArray<Int_t> gammascint_vec__detNum (fReader, "gammascint_vec_.detNum");
        TTreeReaderArray<Double_t> gammascint_vec__qdc (fReader, "gammascint_vec_.qdc");

        TTreeReaderArray<Double_t> next_vec__sTime = {fReader, "next_vec_.sTime"};
        TTreeReaderArray<Double_t> next_vec__qdc (fReader, "next_vec_.qdc");
        TTreeReaderArray<Double_t> next_vec__tof (fReader, "next_vec_.tof");
        TTreeReaderArray<Int_t> next_vec__modNum (fReader, "next_vec_.modNum");
        TTreeReaderArray<Double_t> next_vec__psd (fReader, "next_vec_.psd");


        // vector<Double_t>* next_vec__tof = new vector<Double_t>();
        // vector<Int_t>* next_vec__modNum = new vector<Int_t>();

        // tr_out->SetBranchAddress ( "next_vec_.tof",&next_vec__tof );
        // tr_out->SetBranchAddress ( "next_vec_.modNum",&next_vec__modNum );



        cout << "\nRun Number" << "\t" << runs[num] << "\t\t" << "Iteration Number" << "\t" << num+1 << " out of " << len <<endl;

        for(int i = 0; i < 11; i++) {
            h_TOF_QDC_shifted[num][i] = new TH2D(Form("tof_qdc_shifted_%d_%d",runs[num],i),Form("Time of flight vs QDC [Run %d] [Module %d]",runs[num],i),300,-50,100,300,0,3E5);
            h_TOF_shifted[num][i] = new TH1D(Form("tof_shifted_%d_%d",runs[num],i),Form("Time of flight [Run %d] [Module %d]",runs[num],i),300,-50,100);
        }


        //start reading the tree
        int ev = tr_out->GetEntries(); //get the total number of entries
        cout << "Total number of events =" << ev << endl;
        int ev_num=0;
        
        ////////////////////////////////
        // Event by event starts here //
        ////////////////////////////////

        while(fReader.Next()){
            if ( ev_num%50000==0 ) cout << "Current event = " << ev_num << "\r"<< flush;

            if(!gammascint_vec__detNum.IsEmpty()){
                double HagEnergy = hagridCalibration[gammascint_vec__detNum[0]].first*gammascint_vec__qdc[0]+hagridCalibration[gammascint_vec__detNum[0]].second;
                if(!next_vec__modNum.IsEmpty()){
                    if(!logic_vec__lastProtonPulseTime.IsEmpty() && (next_vec__sTime[0]-logic_vec__lastProtonPulseTime[0])>5E6 && (next_vec__sTime[0]-logic_vec__lastProtonPulseTime[0])<12.5E6){//timing gate

                        if(next_vec__modNum[0] == 0 && bananaCutLeft->IsInside(next_vec__tof[0],next_vec__qdc[0])){
                            hagrid_CutLeftBanana_timeCut[gammascint_vec__detNum[0]]->Fill(HagEnergy);
                        }else if(next_vec__modNum[0] == 0 && bananaCutRight->IsInside(next_vec__tof[0],next_vec__qdc[0])){
                            hagrid_CutRightBanana_timeCut[gammascint_vec__detNum[0]]->Fill(HagEnergy);
                        }

                        
                        
                        if(gammascint_vec__detNum[0]==0){//Module 0
                            if((HagEnergy>360 && HagEnergy<420) || (HagEnergy>2750 && HagEnergy<2950)){//gate on the first and third excited states hagrid modue 0
                                tof_qdc_allRuns_hagridGated[next_vec__modNum[0]]->Fill(next_vec__tof[0]-GammaPeakPosition[runs[num]-1][next_vec__modNum[0]],next_vec__qdc[0]);
                                tof_qdc_allRuns_allModules_hagridGated->Fill(next_vec__tof[0]-GammaPeakPosition[runs[num]-1][next_vec__modNum[0]],next_vec__qdc[0]);
                            }
                        }else{//Module 1
                            if((HagEnergy>340 && HagEnergy<386) || (HagEnergy>2500 && HagEnergy<2650)){//gate on the first and third excited states hagrid modue 1
                                tof_qdc_allRuns_hagridGated[next_vec__modNum[0]]->Fill(next_vec__tof[0]-GammaPeakPosition[runs[num]-1][next_vec__modNum[0]],next_vec__qdc[0]); 
                                tof_qdc_allRuns_allModules_hagridGated->Fill(next_vec__tof[0]-GammaPeakPosition[runs[num]-1][next_vec__modNum[0]],next_vec__qdc[0]);
                            }
                        }
                    }
                }
            }

            if(!next_vec__modNum.IsEmpty()){
                if(!logic_vec__lastProtonPulseTime.IsEmpty() && (next_vec__sTime[0]-logic_vec__lastProtonPulseTime[0])>5E6 && (next_vec__sTime[0]-logic_vec__lastProtonPulseTime[0])<12.5E6){//timing gate
                    h_allRuns_TOF_QDC[next_vec__modNum[0]]->Fill(next_vec__tof[0]-GammaPeakPosition[runs[num]-1][next_vec__modNum[0]],next_vec__qdc[0]);
                    h_allRuns_TOF[next_vec__modNum[0]]->Fill(next_vec__tof[0]-GammaPeakPosition[runs[num]-1][next_vec__modNum[0]]);
                    h_TOF_QDC_shifted[num][next_vec__modNum[0]]->Fill(next_vec__tof[0]-GammaPeakPosition[runs[num]-1][next_vec__modNum[0]],next_vec__qdc[0]);
                    h_TOF_shifted[num][next_vec__modNum[0]]->Fill(next_vec__tof[0]-GammaPeakPosition[runs[num]-1][next_vec__modNum[0]]);


                    if(psdCuts[next_vec__modNum[0]]->IsInside(next_vec__qdc[0],next_vec__psd[0])){
                        tof_qdc_psdgated[next_vec__modNum[0]]->Fill(next_vec__tof[0]-GammaPeakPosition[runs[num]-1][next_vec__modNum[0]],next_vec__qdc[0]);
                    }
                }
            }
            ev_num = ev_num+1;
        }
        
                
        // for(int ev_num = 0; ev_num < ev; ev_num++) {
        //     if ( ev_num%50000==0 ) cout << "Current event = " << ev_num << "\r"<< flush;
        //     tr_out->GetEntry ( ev_num ); //get the current entry


        //     if(!next_vec__modNum.IsEmpty()){
        //         h_TOF[num]->Fill(next_vec__tof[0]);
        //     }
        // }

    }

    f_out->cd();

    for(int i=0; i<len; i++){
        for(int j=0;j<11;j++){
            h_TOF_QDC_shifted[i][j]->Write();
            h_TOF_shifted[i][j]->Write();
        }
    }

    for(int j=0;j<11;j++){
        h_allRuns_TOF_QDC[j]->Write();
        h_allRuns_TOF[j]->Write();
        tof_qdc_allRuns_hagridGated[j]->Write();
        tof_qdc_psdgated[j]->Write();
    }

    for(int i=0;i<2;i++){
        hagrid_CutLeftBanana_timeCut[i]->Write();
        hagrid_CutRightBanana_timeCut[i]->Write();
    }

    tof_qdc_allRuns_allModules_hagridGated->Write();

    f_out->Close();

}