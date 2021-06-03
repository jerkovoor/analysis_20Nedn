#include "analysis_20Nedn.h"

TChain* MakeChain();

int main() {
    TChain *chain = MakeChain();

    // Mode 0
    auto *analysis20Ne = new analysis_20Nedn();
    chain->Process(analysis20Ne);

    return 0;
}

TChain* MakeChain() {
    auto *chain = new TChain("PixTree");

    bool extTrigger = 1;

    bool server = 1;//Turn this on to run on the server

    TString InPath;

    if(server){
        InPath = "/home/jkovoor/data_20Nedn/root_files/";
    }else{
        InPath = "/mnt/c/Users/jerom/Desktop/12Be_exp/NEXT_MSU_REA6/data/";
    }

    // chain->Add(InPath+"bkgd_run_6_DD.root");
    // chain->Add(InPath+"bkgd_run_7_DD.root");
    // chain->Add(InPath+"run16_DD.root");
    chain->Add(InPath+"run50_DD.root");
    // chain->Add(InPath+"calib_60co_3_DD.root");//Hagrid 60Co calibration

    // if(extTrigger){
    //     for(int run_num=28;run_num<39;run_num++){
    //         chain->Add(InPath+Form("run%d_DD.root", run_num));
    //     }
        
    // }else{
    //     for(int run_num=1;run_num<23;run_num++){
    //         chain->Add(InPath+Form("run%d_DD.root", run_num));
    //     }
    // }
    

  
     

    return chain;
}