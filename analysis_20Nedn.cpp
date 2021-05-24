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

   NumModules = 11;
   lowT = 20;
   highT = 145;

   lowT_TOFCorrected = lowT-100;
   highT_TOFCorrected = highT-100;

   nbTOF = 125;
   modules = new TH1D("modules","modules",NumModules,0,NumModules);
   for(int i = 0; i < NumModules; i++) {
      tof[i] = new TH1D(Form("tof_%d",i),Form("Time of flight [Module %d]",i),nbTOF,lowT,highT);
      tof_TOFCorrected[i] = new TH1D(Form("tof_TOFCorrected_%d",i),Form("Time of flight_TOFCorrected [Module %d]",i),nbTOF,lowT_TOFCorrected,highT_TOFCorrected);
      tof_psdgated[i] = new TH1D(Form("tof_psdgated_%d",i),Form("Time of flight [Module %d] gated by PSD",i),nbTOF,lowT,highT);

      tof_qdc[i] = new TH2D(Form("tof_qdc_%d",i),Form("Time of flight vs. QDC [Module %d]",i),nbTOF,lowT,highT,300,0,3E5);
      tof_qdc_psdgated[i] = new TH2D(Form("tof_qdc_psdgated_%d",i),Form("Time of flight vs. QDC [Module %d] gated by PSD",i),nbTOF,lowT,highT,300,0,3E5);
      tof_qdc_TOFCorrected_psdgated[i] = new TH2D(Form("tof_qdc_TOFCorrected_psdgated%d",i),Form("Time of flight vs. QDC_TOFCorrected[Module %d] gated by PSD",i),nbTOF,lowT_TOFCorrected,highT_TOFCorrected,300,0,3E5);
      
      position[i] = new TH2D(Form("position_%d",i),Form("Position Map [Module %d]",i),100,-1.0,1.0,100,-1.0,1.0);
      position_psdgated[i] = new TH2D(Form("position_psdgated_%d",i),Form("Position Map [Module %d] gated by PSD",i),100,-1.0,1.0,100,-1.0,1.0);
      
      psd_qdc[i] = new TH2D(Form("psd_qdc_%d",i),Form("PSD vs. QDC [Module %d]",i),300,0,3E5,250,0,1);
      
      psd_tof[i] = new TH2D(Form("psd_tof_%d",i),Form("PSD vs. TOF [Module %d]",i),nbTOF,lowT,highT,250,0,1);
   }
   
   f_out = new TFile("histogramsTest.root", "RECREATE");

   psdcut0 = TFile::Open("../gates_Run50.root");

   for(int i = 0; i < NumModules; i++) {
      psdCuts[i] = (TCutG*) psdcut0->Get(Form("psd_mod%d",i));
   }

   std::ifstream module_gammaPeak("../TOF_GammaPeaks.txt");
   assert(module_gammaPeak.is_open());
   while(module_gammaPeak >> moduleID >> peakPosition) {
      GammaPeakPosition[moduleID] = peakPosition;
      // std::cout << moduleID << "\t" << GammaPeakPosition[moduleID] << std::endl;
   }
   module_gammaPeak.close();


   // ofstream module_gammaPeak;
   // module_gammaPeak.open (path + "../TOF_GammaPeaks.txt" );
   // module_gammaPeak << " Module    Peak  \n";
}

// void analysis_20Nedn::SlaveBegin(TTree * /*tree*/)
// {
//    // The SlaveBegin() function is called after the Begin() function.
//    // When running with PROOF SlaveBegin() is called on each slave server.
//    // The tree argument is deprecated (on PROOF 0 is passed).

//    TString option = GetOption();

// }

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

   if(!next_vec__modNum.IsEmpty()){
      modules->Fill(next_vec__modNum[0]);
      tof[next_vec__modNum[0]]->Fill(next_vec__tof[0]);
      tof_TOFCorrected[next_vec__modNum[0]]->Fill(next_vec__tof[0]-GammaPeakPosition[next_vec__modNum[0]]);
      // std::cout << next_vec__modNum[0] << "\t" << GammaPeakPosition[next_vec__modNum[0]] << std::endl;
      tof_qdc[next_vec__modNum[0]]->Fill(next_vec__tof[0],next_vec__qdc[0]);

      ///////////////////////PSD gated module wise tof-qdc//////////////////////

      if(psdCuts[next_vec__modNum[0]]->IsInside(next_vec__qdc[0],next_vec__psd[0])){
         tof_psdgated[next_vec__modNum[0]]->Fill(next_vec__tof[0]);
         tof_qdc_psdgated[next_vec__modNum[0]]->Fill(next_vec__tof[0],next_vec__qdc[0]);
         tof_qdc_TOFCorrected_psdgated[next_vec__modNum[0]]->Fill(next_vec__tof[0]-GammaPeakPosition[next_vec__modNum[0]],next_vec__qdc[0]);
         position_psdgated[next_vec__modNum[0]]->Fill(next_vec__QZpos[0],next_vec__QYpos[0]);
      }      
      
      position[next_vec__modNum[0]]->Fill(next_vec__QZpos[0],next_vec__QYpos[0]);
      psd_qdc[next_vec__modNum[0]]->Fill(next_vec__qdc[0],next_vec__psd[0]);
      psd_tof[next_vec__modNum[0]]->Fill(next_vec__tof[0],next_vec__psd[0]);
   }
   

   return kTRUE;
}

// void analysis_20Nedn::SlaveTerminate()
// {
//    // The SlaveTerminate() function is called after all entries or objects
//    // have been processed. When running with PROOF SlaveTerminate() is called
//    // on each slave server.

// }

void analysis_20Nedn::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   f_out->cd();

   modules->Write();
   for(int i = 0; i < NumModules; i++) {
      tof[i]->Write();
      tof_TOFCorrected[i]->Write();
      tof_qdc[i]->Write();
      position[i]->Write();
      psd_qdc[i]->Write();
      psd_tof[i]->Write();
      tof_psdgated[i]->Write();
      tof_qdc_psdgated[i]->Write();
      tof_qdc_TOFCorrected_psdgated[i]->Write();
      position_psdgated[i]->Write();
   }

   f_out->Close();

}