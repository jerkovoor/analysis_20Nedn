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

    // bool extTrigger = 0;
    bool thinTarget = 0;
    bool background = 1;
    bool collimator = 0;

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
    // chain->Add(InPath+"run50_DD.root");
    //chain->Add(InPath+"calib_60co_3_DD.root");//Hagrid 60Co calibration

    if(background){
       for(int run_num=1;run_num<14;run_num++){
            chain->Add(InPath+Form("bkgd_run_%d_DD.root", run_num));
        }
    }else if(collimator){
        chain->Add(InPath+"run49_DD.root");
    }else{//////////////Data//////////////
        if(thinTarget){//////////////////Thin target//////////////////////
            for(int run_num=19;run_num<49;run_num++){
                chain->Add(InPath+Form("run%d_DD.root", run_num));
            }
            chain->Add(InPath+"run50_DD.root");
            chain->Add(InPath+"run51_DD.root");
            chain->Add(InPath+"run52_DD.root");
            chain->Add(InPath+"run53_DD.root");
        }else{//////////////////Thick target///////////////////
            for(int run_num=14;run_num<19;run_num++){
                chain->Add(InPath+Form("run%d_DD.root", run_num));
            }
            chain->Add(InPath+"run54_DD.root");
            chain->Add(InPath+"run55_DD.root");
        }
    }
    
    
         

    // if(extTrigger){
    //     for(int run_num=23;run_num<27;run_num++){
    //         chain->Add(InPath+Form("run%d_DD.root", run_num));
    //     }
    //     for(int run_num=28;run_num<48;run_num++){
    //         chain->Add(InPath+Form("run%d_DD.root", run_num));
    //     }
    
    // }else{
    //     for(int run_num=1;run_num<23;run_num++){
    //         chain->Add(InPath+Form("run%d_DD.root", run_num));
    //     }
    //     chain->Add(InPath+"run27_DD.root");
    //     for(int run_num=48;run_num<56;run_num++){
    //         chain->Add(InPath+Form("run%d_DD.root", run_num));
    //     }
    // }
    

  
     

    return chain;
}
