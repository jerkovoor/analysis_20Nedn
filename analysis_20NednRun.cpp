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

    bool extTrigger = 0;

    TString InPath;

    InPath = "/mnt/c/Users/jerom/Desktop/12Be_exp/NEXT_MSU_REA6/data/";

    // if(Server){
    //     InPath = "/home/reactions/Decoded_root";
    // }else{
    //     InPath = "/mnt/c/Users/jerom/Desktop/12Be_exp/Analysis/NewDecodeJosh";
    // }


    // TString PathToFilesBeT = InPath + "/Be/NewDecode_";
    // TString PathToFilesBeNT = InPath + "/Be_notarget/NewDecode_";
    // TString PathToFilesCT = InPath + "/C/NewDecode_";
    // TString PathToFilesCNT = InPath + "/C_notarget/NewDecode_";

    chain->Add(InPath+"run_050_DD.root");

    // if(extTrigger){
    //     for(int run_num=28;run_num<48;run_num++){
    //         chain->Add(InPath+Form("run%d_DD.root", run_num));
    //     }
        
    // }else{
    //     for(int run_num=1;run_num<23;run_num++){
    //         chain->Add(InPath+Form("run%d_DD.root", run_num));
    //     }
    // }
    

  
     

    return chain;
}