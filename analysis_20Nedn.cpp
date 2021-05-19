#define analysis_20Nedn_cxx
// The class definition in analysis_20Nedn.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("analysis_20Nedn.C")
// root> T->Process("analysis_20Nedn.C","some options")
// root> T->Process("analysis_20Nedn.C+")
//


#include "analysis_20Nedn.h"
#include <TH2.h>
#include <TStyle.h>

void analysis_20Nedn::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   //Defining histograms
   ev_num = 0;

   modules = new TH1F("modules","modules",11,0,11);
   NumModules = 11;
   lowT = 20;
   highT = 145;
   nbTOF = 125; 
   for(int i = 0; i < NumModules; i++) {
      tof_qdc[i] = new TH2D(Form("tof_qdc_%d",i),Form("Time of flight vs. QDC [Module %d]",i),nbTOF,lowT,highT,300,0,3E5);
      tof_qdc_psdgated[i] = new TH2D(Form("tof_qdc_psdgated_%d",i),Form("Time of flight vs. QDC [Module %d] gated by PSD",i),nbTOF,lowT,highT,300,0,3E5);
      position[i] = new TH2D(Form("position_%d",i),Form("Position Map [Module %d]",i),100,-1.0,1.0,100,-1.0,1.0);
      psd_qdc[i] = new TH2D(Form("psd_qdc_%d",i),Form("PSD vs. QDC [Module %d]",i),300,0,3E5,250,0,1);
      psd_tof[i] = new TH2D(Form("psd_tof_%d",i),Form("PSD vs. TOF [Module %d]",i),nbTOF,lowT,highT,250,0,1);
   }
   
   f_out = new TFile("histogramsTest.root", "RECREATE");



   psdcut0 = TFile::Open("../psdCut.root");
   psdcut1 = TFile::Open("../psdCut1.root");
   psdcut2_3 = TFile::Open("../psdCut2-3.root");
   psdcut4 = TFile::Open("../psdCut4.root");
   psdcut5 = TFile::Open("../psdCut5.root");
   psdcut6_10 = TFile::Open("../psdCut6-10.root");
   // for(int i = 0; i < NumModules; i++) {
   //    Form("psd_mod%d_cut",i) = (TCutG*) Form("psdcut%d",i)->Get(Form("psd_mod%d",i));
   // }
	psd_mod0_cut = (TCutG*) psdcut0->Get("psd_mod0");
   psd_mod1_cut = (TCutG*) psdcut1->Get("psd_mod1");
   psd_mod2_cut = (TCutG*) psdcut2_3->Get("psd_mod2");
   psd_mod3_cut = (TCutG*) psdcut2_3->Get("psd_mod3");
   psd_mod4_cut = (TCutG*) psdcut4->Get("psd_mod4");
   psd_mod5_cut = (TCutG*) psdcut5->Get("psd_mod5");
   psd_mod6_cut = (TCutG*) psdcut6_10->Get("psd_mod6");
   psd_mod7_cut = (TCutG*) psdcut6_10->Get("psd_mod7");
   psd_mod8_cut = (TCutG*) psdcut6_10->Get("psd_mod8");
   psd_mod9_cut = (TCutG*) psdcut6_10->Get("psd_mod9");
   psd_mod10_cut = (TCutG*) psdcut6_10->Get("psd_mod10");

}

void analysis_20Nedn::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t analysis_20Nedn::Process(Long64_t entry){

   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetLocalEntry(entry);
   if(ev_num%50000 == 0) std::cout << "Current event = " << ev_num << "\r"<< std::flush;
   ev_num++;

   // modules->Fill(next_vec__modNum[0]);

   if(!next_vec__modNum.IsEmpty()){
      modules->Fill(next_vec__modNum[0]);
      tof_qdc[next_vec__modNum[0]]->Fill(next_vec__tof[0],next_vec__qdc[0]);

      if(next_vec__modNum[0] == 0 && psd_mod0_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[0]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 1 && psd_mod1_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[1]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 2 && psd_mod2_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[2]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 3 && psd_mod3_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[3]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 4 && psd_mod4_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[4]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 5 && psd_mod5_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[5]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 6 && psd_mod6_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[6]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 7 && psd_mod7_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[7]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 8 && psd_mod8_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[8]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 9 && psd_mod9_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[9]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }else if (next_vec__modNum[0] == 10 && psd_mod10_cut->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_qdc_psdgated[10]->Fill(next_vec__tof[0],next_vec__qdc[0]);
      }
      
      
      position[next_vec__modNum[0]]->Fill(next_vec__QZpos[0],next_vec__QYpos[0]);
      psd_qdc[next_vec__modNum[0]]->Fill(next_vec__qdc[0],next_vec__psd[0]);
      psd_tof[next_vec__modNum[0]]->Fill(next_vec__tof[0],next_vec__psd[0]);
   }
   

   return kTRUE;
}

void analysis_20Nedn::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void analysis_20Nedn::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   f_out->cd();

   modules->Write();
   for(int i = 0; i < NumModules; i++) {
      tof_qdc[i]->Write();
      position[i]->Write();
      psd_qdc[i]->Write();
      psd_tof[i]->Write();
   }
   for(int i = 0; i < NumModules; i++) {
      tof_qdc_psdgated[i]->Write();
   }

   f_out->Close();

}