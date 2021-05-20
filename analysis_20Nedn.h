//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 14 00:38:54 2021 by ROOT version 6.14/04
// from TTree PixTree/Pixie Event Tree
// found on file: a102_prod005_DD.root
//////////////////////////////////////////////////////////

#ifndef analysis_20Nedn_h
#define analysis_20Nedn_h

#include <TChain.h>
#include <TCutG.h>
#include <TF1.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2.h>
#include <TMath.h>
#include <TRandom3.h>
#include <TROOT.h>
#include <TSelector.h>
#include <TStyle.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>
#include <TVector3.h>

#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <utility>
// Headers needed by this particular selector


class analysis_20Nedn : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   // TTreeReaderValue<unsigned int> fUniqueID = {fReader, "fUniqueID"};
   // TTreeReaderValue<unsigned int> fBits = {fReader, "fBits"};
   // TTreeReaderValue<ULong64_t> externalTS1 = {fReader, "externalTS1"};
   // TTreeReaderValue<ULong64_t> externalTS2 = {fReader, "externalTS2"};
   // TTreeReaderValue<Double_t> eventNum = {fReader, "eventNum"};
   // TTreeReaderValue<string> fileName = {fReader, "fileName"};
   // TTreeReaderArray<vector<double>> bato_vec__pQDCsums = {fReader, "bato_vec_.pQDCsums"};
   // TTreeReaderArray<Double_t> bato_vec__time = {fReader, "bato_vec_.time"};
   // TTreeReaderArray<Double_t> bato_vec__energy = {fReader, "bato_vec_.energy"};
   // TTreeReaderArray<Double_t> bato_vec__qdc = {fReader, "bato_vec_.qdc"};
   // TTreeReaderArray<Int_t> bato_vec__detNum = {fReader, "bato_vec_.detNum"};
   // TTreeReaderArray<Double_t> clover_vec__energy = {fReader, "clover_vec_.energy"};
   // TTreeReaderArray<Double_t> clover_vec__rawEnergy = {fReader, "clover_vec_.rawEnergy"};
   // TTreeReaderArray<Double_t> clover_vec__time = {fReader, "clover_vec_.time"};
   // TTreeReaderArray<Int_t> clover_vec__detNum = {fReader, "clover_vec_.detNum"};
   // TTreeReaderArray<Int_t> clover_vec__cloverNum = {fReader, "clover_vec_.cloverNum"};
   // TTreeReaderArray<Bool_t> clover_vec__cloverHigh = {fReader, "clover_vec_.cloverHigh"};
   // TTreeReaderArray<Int_t> doublebeta_vec__detNum = {fReader, "doublebeta_vec_.detNum"};
   // TTreeReaderArray<Double_t> doublebeta_vec__energy = {fReader, "doublebeta_vec_.energy"};
   // TTreeReaderArray<Double_t> doublebeta_vec__rawEnergy = {fReader, "doublebeta_vec_.rawEnergy"};
   // TTreeReaderArray<Double_t> doublebeta_vec__timeAvg = {fReader, "doublebeta_vec_.timeAvg"};
   // TTreeReaderArray<Double_t> doublebeta_vec__timeDiff = {fReader, "doublebeta_vec_.timeDiff"};
   // TTreeReaderArray<Double_t> doublebeta_vec__timeL = {fReader, "doublebeta_vec_.timeL"};
   // TTreeReaderArray<Double_t> doublebeta_vec__timeR = {fReader, "doublebeta_vec_.timeR"};
   // TTreeReaderArray<Double_t> doublebeta_vec__barQdc = {fReader, "doublebeta_vec_.barQdc"};
   // TTreeReaderArray<Double_t> doublebeta_vec__tMaxValL = {fReader, "doublebeta_vec_.tMaxValL"};
   // TTreeReaderArray<Double_t> doublebeta_vec__tMaxValR = {fReader, "doublebeta_vec_.tMaxValR"};
   // TTreeReaderArray<Bool_t> doublebeta_vec__isLowResBeta = {fReader, "doublebeta_vec_.isLowResBeta"};
   // TTreeReaderArray<Bool_t> doublebeta_vec__isHighResBeta = {fReader, "doublebeta_vec_.isHighResBeta"};
   // TTreeReaderArray<Double_t> gammascint_vec__energy = {fReader, "gammascint_vec_.energy"};
   // TTreeReaderArray<Double_t> gammascint_vec__rawEnergy = {fReader, "gammascint_vec_.rawEnergy"};
   // TTreeReaderArray<Double_t> gammascint_vec__qdc = {fReader, "gammascint_vec_.qdc"};
   // TTreeReaderArray<Bool_t> gammascint_vec__isDynodeOut = {fReader, "gammascint_vec_.isDynodeOut"};
   // TTreeReaderArray<Int_t> gammascint_vec__detNum = {fReader, "gammascint_vec_.detNum"};
   // TTreeReaderArray<Double_t> gammascint_vec__time = {fReader, "gammascint_vec_.time"};
   // TTreeReaderArray<TString> gammascint_vec__group = {fReader, "gammascint_vec_.group"};
   // TTreeReaderArray<TString> gammascint_vec__subtype = {fReader, "gammascint_vec_.subtype"};
   // TTreeReaderArray<Bool_t> logic_vec__tapeCycleStatus = {fReader, "logic_vec_.tapeCycleStatus"};
   // TTreeReaderArray<Bool_t> logic_vec__beamStatus = {fReader, "logic_vec_.beamStatus"};
   // TTreeReaderArray<Bool_t> logic_vec__tapeMoving = {fReader, "logic_vec_.tapeMoving"};
   // TTreeReaderArray<Double_t> logic_vec__lastTapeCycleStartTime = {fReader, "logic_vec_.lastTapeCycleStartTime"};
   // TTreeReaderArray<Double_t> logic_vec__lastBeamOnTime = {fReader, "logic_vec_.lastBeamOnTime"};
   // TTreeReaderArray<Double_t> logic_vec__lastBeamOffTime = {fReader, "logic_vec_.lastBeamOffTime"};
   // TTreeReaderArray<Double_t> logic_vec__lastTapeMoveStartTime = {fReader, "logic_vec_.lastTapeMoveStartTime"};
   // TTreeReaderArray<Double_t> logic_vec__lastProtonPulseTime = {fReader, "logic_vec_.lastProtonPulseTime"};
   // TTreeReaderArray<Double_t> logic_vec__lastSuperCycleTime = {fReader, "logic_vec_.lastSuperCycleTime"};
   // TTreeReaderArray<Int_t> logic_vec__cycleNum = {fReader, "logic_vec_.cycleNum"};
   TTreeReaderArray<Double_t> next_vec__tof = {fReader, "next_vec_.tof"};
   TTreeReaderArray<Double_t> next_vec__corTof = {fReader, "next_vec_.corTof"};
   TTreeReaderArray<Double_t> next_vec__qdcPos = {fReader, "next_vec_.qdcPos"};
   TTreeReaderArray<Double_t> next_vec__phaseL = {fReader, "next_vec_.phaseL"};
   TTreeReaderArray<Double_t> next_vec__phaseR = {fReader, "next_vec_.phaseR"};
   TTreeReaderArray<Double_t> next_vec__Zpos = {fReader, "next_vec_.Zpos"};
   TTreeReaderArray<Double_t> next_vec__Ypos = {fReader, "next_vec_.Ypos"};
   TTreeReaderArray<Double_t> next_vec__FZpos = {fReader, "next_vec_.FZpos"};
   TTreeReaderArray<Double_t> next_vec__FYpos = {fReader, "next_vec_.FYpos"};
   TTreeReaderArray<Double_t> next_vec__QZpos = {fReader, "next_vec_.QZpos"};
   TTreeReaderArray<Double_t> next_vec__QYpos = {fReader, "next_vec_.QYpos"};
   TTreeReaderArray<Bool_t> next_vec__saturation = {fReader, "next_vec_.saturation"};
   TTreeReaderArray<Double_t> next_vec__qdc = {fReader, "next_vec_.qdc"};
   TTreeReaderArray<Double_t> next_vec__pqdc = {fReader, "next_vec_.pqdc"};
   TTreeReaderArray<Double_t> next_vec__lqdc = {fReader, "next_vec_.lqdc"};
   TTreeReaderArray<Double_t> next_vec__rqdc = {fReader, "next_vec_.rqdc"};
   TTreeReaderArray<Double_t> next_vec__aqdc = {fReader, "next_vec_.aqdc"};
   TTreeReaderArray<Int_t> next_vec__modNum = {fReader, "next_vec_.modNum"};
   TTreeReaderArray<Double_t> next_vec__lftqdc = {fReader, "next_vec_.lftqdc"};
   TTreeReaderArray<Double_t> next_vec__lfbqdc = {fReader, "next_vec_.lfbqdc"};
   TTreeReaderArray<Double_t> next_vec__lbtqdc = {fReader, "next_vec_.lbtqdc"};
   TTreeReaderArray<Double_t> next_vec__lbbqdc = {fReader, "next_vec_.lbbqdc"};
   TTreeReaderArray<Double_t> next_vec__rftqdc = {fReader, "next_vec_.rftqdc"};
   TTreeReaderArray<Double_t> next_vec__rfbqdc = {fReader, "next_vec_.rfbqdc"};
   TTreeReaderArray<Double_t> next_vec__rbtqdc = {fReader, "next_vec_.rbtqdc"};
   TTreeReaderArray<Double_t> next_vec__rbbqdc = {fReader, "next_vec_.rbbqdc"};
   TTreeReaderArray<Double_t> next_vec__lfttqdc = {fReader, "next_vec_.lfttqdc"};
   TTreeReaderArray<Double_t> next_vec__lfbtqdc = {fReader, "next_vec_.lfbtqdc"};
   TTreeReaderArray<Double_t> next_vec__lbttqdc = {fReader, "next_vec_.lbttqdc"};
   TTreeReaderArray<Double_t> next_vec__lbbtqdc = {fReader, "next_vec_.lbbtqdc"};
   TTreeReaderArray<Double_t> next_vec__rfttqdc = {fReader, "next_vec_.rfttqdc"};
   TTreeReaderArray<Double_t> next_vec__rfbtqdc = {fReader, "next_vec_.rfbtqdc"};
   TTreeReaderArray<Double_t> next_vec__rbttqdc = {fReader, "next_vec_.rbttqdc"};
   TTreeReaderArray<Double_t> next_vec__rbbtqdc = {fReader, "next_vec_.rbbtqdc"};
   TTreeReaderArray<Double_t> next_vec__alqdc = {fReader, "next_vec_.alqdc"};
   TTreeReaderArray<Double_t> next_vec__altqdc = {fReader, "next_vec_.altqdc"};
   TTreeReaderArray<Double_t> next_vec__arqdc = {fReader, "next_vec_.arqdc"};
   TTreeReaderArray<Double_t> next_vec__artqdc = {fReader, "next_vec_.artqdc"};
   TTreeReaderArray<Double_t> next_vec__psd = {fReader, "next_vec_.psd"};
   TTreeReaderArray<Double_t> next_vec__Lpsd = {fReader, "next_vec_.Lpsd"};
   TTreeReaderArray<Double_t> next_vec__Rpsd = {fReader, "next_vec_.Rpsd"};
   TTreeReaderArray<Double_t> next_vec__rMax = {fReader, "next_vec_.rMax"};
   TTreeReaderArray<Double_t> next_vec__lMax = {fReader, "next_vec_.lMax"};
   TTreeReaderArray<Double_t> next_vec__lMaxPos = {fReader, "next_vec_.lMaxPos"};
   TTreeReaderArray<Double_t> next_vec__rMaxPos = {fReader, "next_vec_.rMaxPos"};
   TTreeReaderArray<Double_t> next_vec__lAveBase = {fReader, "next_vec_.lAveBase"};
   TTreeReaderArray<Double_t> next_vec__rAveBase = {fReader, "next_vec_.rAveBase"};
   TTreeReaderArray<Double_t> next_vec__lSdBase = {fReader, "next_vec_.lSdBase"};
   TTreeReaderArray<Double_t> next_vec__rSdBase = {fReader, "next_vec_.rSdBase"};
   TTreeReaderArray<Double_t> next_vec__tdiff = {fReader, "next_vec_.tdiff"};
   TTreeReaderArray<unsigned int> next_vec__sNum = {fReader, "next_vec_.sNum"};
   TTreeReaderArray<Int_t> next_vec__vMulti = {fReader, "next_vec_.vMulti"};
   TTreeReaderArray<Double_t> next_vec__sTime = {fReader, "next_vec_.sTime"};
   TTreeReaderArray<Double_t> next_vec__sQdc = {fReader, "next_vec_.sQdc"};
   TTreeReaderArray<Double_t> next_vec__slMax = {fReader, "next_vec_.slMax"};
   TTreeReaderArray<Double_t> next_vec__slAveBase = {fReader, "next_vec_.slAveBase"};
   TTreeReaderArray<Double_t> next_vec__slSdBase = {fReader, "next_vec_.slSdBase"};
   TTreeReaderArray<Double_t> next_vec__sMax = {fReader, "next_vec_.sMax"};
   TTreeReaderArray<Double_t> next_vec__sAveBase = {fReader, "next_vec_.sAveBase"};
   TTreeReaderArray<Double_t> next_vec__sSdBase = {fReader, "next_vec_.sSdBase"};
   TTreeReaderArray<Double_t> next_vec__srMax = {fReader, "next_vec_.srMax"};
   TTreeReaderArray<Double_t> next_vec__srAveBase = {fReader, "next_vec_.srAveBase"};
   TTreeReaderArray<Double_t> next_vec__srSdBase = {fReader, "next_vec_.srSdBase"};
   TTreeReaderArray<Int_t> next_vec__sCount = {fReader, "next_vec_.sCount"};
   TTreeReaderArray<Double_t> next_vec__sYPos = {fReader, "next_vec_.sYPos"};
   TTreeReaderArray<Double_t> next_vec__sXPos = {fReader, "next_vec_.sXPos"};
   // TTreeReaderArray<Double_t> pid_vec__rfq_time = {fReader, "pid_vec_.rfq_time"};
   // TTreeReaderArray<Double_t> pid_vec__fp_time = {fReader, "pid_vec_.fp_time"};
   // TTreeReaderArray<Double_t> pid_vec__pinCfd_time = {fReader, "pid_vec_.pinCfd_time"};
   // TTreeReaderArray<Double_t> pid_vec__pin_0_time = {fReader, "pid_vec_.pin_0_time"};
   // TTreeReaderArray<Double_t> pid_vec__pin_1_time = {fReader, "pid_vec_.pin_1_time"};
   // TTreeReaderArray<Double_t> pid_vec__pin_0_energy = {fReader, "pid_vec_.pin_0_energy"};
   // TTreeReaderArray<Double_t> pid_vec__pin_1_energy = {fReader, "pid_vec_.pin_1_energy"};
   // TTreeReaderArray<Double_t> pid_vec__tac_0 = {fReader, "pid_vec_.tac_0"};
   // TTreeReaderArray<Double_t> pid_vec__tac_1 = {fReader, "pid_vec_.tac_1"};
   // TTreeReaderArray<Double_t> pid_vec__tof0 = {fReader, "pid_vec_.tof0"};
   // TTreeReaderArray<Double_t> pid_vec__tof1 = {fReader, "pid_vec_.tof1"};
   // TTreeReaderArray<Double_t> pspmt_vec__energy = {fReader, "pspmt_vec_.energy"};
   // TTreeReaderArray<Double_t> pspmt_vec__qdc = {fReader, "pspmt_vec_.qdc"};
   // TTreeReaderArray<Double_t> pspmt_vec__time = {fReader, "pspmt_vec_.time"};
   // TTreeReaderArray<TString> pspmt_vec__subtype = {fReader, "pspmt_vec_.subtype"};
   // TTreeReaderArray<TString> pspmt_vec__tag = {fReader, "pspmt_vec_.tag"};
   // TTreeReaderArray<Double_t> pspmt_vec__traceMaxVal = {fReader, "pspmt_vec_.traceMaxVal"};
   // TTreeReaderArray<Int_t> pspmt_vec__traceMaxPos = {fReader, "pspmt_vec_.traceMaxPos"};
   // TTreeReaderArray<Double_t> pspmt_vec__preBaseAvg = {fReader, "pspmt_vec_.preBaseAvg"};
   // TTreeReaderArray<Double_t> pspmt_vec__postBaseAvg = {fReader, "pspmt_vec_.postBaseAvg"};
   // TTreeReaderArray<Bool_t> pspmt_vec__invalidTrace = {fReader, "pspmt_vec_.invalidTrace"};
   // TTreeReaderArray<Double_t> mtasbeta_vec__YPos = {fReader, "mtasbeta_vec_.YPos"};
   // TTreeReaderArray<Double_t> mtasbeta_vec__XPos = {fReader, "mtasbeta_vec_.XPos"};
   // TTreeReaderArray<Int_t> mtasbeta_vec__count = {fReader, "mtasbeta_vec_.count"};
   // TTreeReaderArray<Int_t> mtasbeta_vec__multi = {fReader, "mtasbeta_vec_.multi"};
   // TTreeReaderArray<vector<double>> mtasbeta_vec__energy = {fReader, "mtasbeta_vec_.energy"};
   // TTreeReaderArray<vector<double>> mtasbeta_vec__qdc = {fReader, "mtasbeta_vec_.qdc"};
   // TTreeReaderArray<vector<double>> mtasbeta_vec__time = {fReader, "mtasbeta_vec_.time"};
   // TTreeReaderArray<vector<double>> mtasbeta_vec__pqdc = {fReader, "mtasbeta_vec_.pqdc"};
   // TTreeReaderArray<vector<TString>> mtasbeta_vec__subtype = {fReader, "mtasbeta_vec_.subtype"};
   // TTreeReaderArray<vector<TString>> mtasbeta_vec__tag = {fReader, "mtasbeta_vec_.tag"};
   // TTreeReaderArray<Double_t> rootdev_vec__energy = {fReader, "rootdev_vec_.energy"};
   // TTreeReaderArray<Double_t> rootdev_vec__rawEnergy = {fReader, "rootdev_vec_.rawEnergy"};
   // TTreeReaderArray<Double_t> rootdev_vec__timeSansCfd = {fReader, "rootdev_vec_.timeSansCfd"};
   // TTreeReaderArray<Double_t> rootdev_vec__time = {fReader, "rootdev_vec_.time"};
   // TTreeReaderArray<Bool_t> rootdev_vec__cfdForcedBit = {fReader, "rootdev_vec_.cfdForcedBit"};
   // TTreeReaderArray<Double_t> rootdev_vec__cfdFraction = {fReader, "rootdev_vec_.cfdFraction"};
   // TTreeReaderArray<Int_t> rootdev_vec__cfdSourceBit = {fReader, "rootdev_vec_.cfdSourceBit"};
   // TTreeReaderArray<Int_t> rootdev_vec__detNum = {fReader, "rootdev_vec_.detNum"};
   // TTreeReaderArray<Int_t> rootdev_vec__modNum = {fReader, "rootdev_vec_.modNum"};
   // TTreeReaderArray<Int_t> rootdev_vec__chanNum = {fReader, "rootdev_vec_.chanNum"};
   // TTreeReaderArray<TString> rootdev_vec__subtype = {fReader, "rootdev_vec_.subtype"};
   // TTreeReaderArray<TString> rootdev_vec__group = {fReader, "rootdev_vec_.group"};
   // TTreeReaderArray<Bool_t> rootdev_vec__pileup = {fReader, "rootdev_vec_.pileup"};
   // TTreeReaderArray<Bool_t> rootdev_vec__saturation = {fReader, "rootdev_vec_.saturation"};
   // TTreeReaderArray<vector<unsigned int>> rootdev_vec__trace = {fReader, "rootdev_vec_.trace"};
   // TTreeReaderArray<Double_t> rootdev_vec__baseline = {fReader, "rootdev_vec_.baseline"};
   // TTreeReaderArray<Double_t> rootdev_vec__stdBaseline = {fReader, "rootdev_vec_.stdBaseline"};
   // TTreeReaderArray<Double_t> rootdev_vec__phase = {fReader, "rootdev_vec_.phase"};
   // TTreeReaderArray<Double_t> rootdev_vec__tqdc = {fReader, "rootdev_vec_.tqdc"};
   // TTreeReaderArray<Int_t> rootdev_vec__maxPos = {fReader, "rootdev_vec_.maxPos"};
   // TTreeReaderArray<Double_t> rootdev_vec__maxVal = {fReader, "rootdev_vec_.maxVal"};
   // TTreeReaderArray<Double_t> rootdev_vec__extMaxVal = {fReader, "rootdev_vec_.extMaxVal"};
   // TTreeReaderArray<Double_t> rootdev_vec__highResTime = {fReader, "rootdev_vec_.highResTime"};
   // TTreeReaderArray<vector<unsigned int>> rootdev_vec__qdcSums = {fReader, "rootdev_vec_.qdcSums"};
   // TTreeReaderArray<Bool_t> rootdev_vec__hasValidTimingAnalysis = {fReader, "rootdev_vec_.hasValidTimingAnalysis"};
   // TTreeReaderArray<Bool_t> rootdev_vec__hasValidWaveformAnalysis = {fReader, "rootdev_vec_.hasValidWaveformAnalysis"};
   // TTreeReaderArray<Int_t> singlebeta_vec__detNum = {fReader, "singlebeta_vec_.detNum"};
   // TTreeReaderArray<Double_t> singlebeta_vec__energy = {fReader, "singlebeta_vec_.energy"};
   // TTreeReaderArray<Double_t> singlebeta_vec__rawEnergy = {fReader, "singlebeta_vec_.rawEnergy"};
   // TTreeReaderArray<Double_t> singlebeta_vec__time = {fReader, "singlebeta_vec_.time"};
   // TTreeReaderArray<Double_t> singlebeta_vec__qdc = {fReader, "singlebeta_vec_.qdc"};
   // TTreeReaderArray<Double_t> singlebeta_vec__tMaxVal = {fReader, "singlebeta_vec_.tMaxVal"};
   // TTreeReaderArray<Bool_t> singlebeta_vec__isLowResBeta = {fReader, "singlebeta_vec_.isLowResBeta"};
   // TTreeReaderArray<Bool_t> singlebeta_vec__isHighResBeta = {fReader, "singlebeta_vec_.isHighResBeta"};
   // TTreeReaderArray<Bool_t> singlebeta_vec__hasTraceFit = {fReader, "singlebeta_vec_.hasTraceFit"};
   // TTreeReaderArray<string> vandle_vec__barType = {fReader, "vandle_vec_.barType"};
   // TTreeReaderArray<Double_t> vandle_vec__tof = {fReader, "vandle_vec_.tof"};
   // TTreeReaderArray<Double_t> vandle_vec__corTof = {fReader, "vandle_vec_.corTof"};
   // TTreeReaderArray<Double_t> vandle_vec__qdcPos = {fReader, "vandle_vec_.qdcPos"};
   // TTreeReaderArray<Double_t> vandle_vec__qdc = {fReader, "vandle_vec_.qdc"};
   // TTreeReaderArray<Int_t> vandle_vec__barNum = {fReader, "vandle_vec_.barNum"};
   // TTreeReaderArray<Double_t> vandle_vec__tAvg = {fReader, "vandle_vec_.tAvg"};
   // TTreeReaderArray<Double_t> vandle_vec__tDiff = {fReader, "vandle_vec_.tDiff"};
   // TTreeReaderArray<Double_t> vandle_vec__wcTavg = {fReader, "vandle_vec_.wcTavg"};
   // TTreeReaderArray<Double_t> vandle_vec__wcTdiff = {fReader, "vandle_vec_.wcTdiff"};
   // TTreeReaderArray<Int_t> vandle_vec__sNum = {fReader, "vandle_vec_.sNum"};
   // TTreeReaderArray<Int_t> vandle_vec__vMulti = {fReader, "vandle_vec_.vMulti"};
   // TTreeReaderArray<Double_t> vandle_vec__sTime = {fReader, "vandle_vec_.sTime"};
   // TTreeReaderArray<Double_t> vandle_vec__sQdc = {fReader, "vandle_vec_.sQdc"};
   // TTreeReaderArray<Double_t> vandle_vec__psd = {fReader, "vandle_vec_.psd"};


   analysis_20Nedn(TTree * /*tree*/ =0) { }
   virtual ~analysis_20Nedn() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   // virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   // virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(analysis_20Nedn,0);

   int NumModules;

   long ev;
   long ev_num;

   TFile *psdcut0;
   TCutG *psdCuts[11];

   double lowT,highT,nbTOF;
   TH1D *modules, *tof[11], *tof_psdgated[11];
   TH2D *psd_qdc[11];
   TH2D *tof_qdc[11];
   TH2D *tof_qdc_psdgated[11];
   TH2D *psd_tof[11];
   TH2D *position[11];
   TH2D *position_psdgated[11];
   TFile *f_out;

};

#endif

#ifdef analysis_20Nedn_cxx
void analysis_20Nedn::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t analysis_20Nedn::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef analysis_20Nedn_cxx
