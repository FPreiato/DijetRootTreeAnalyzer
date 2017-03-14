#include <stdlib.h>
#include <sys/stat.h>  
#include <time.h>
#include "TParameter.h"
#include "TPaveText.h"
#include "TError.h"
#include "TFormula.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TAxis.h"
#include "drawBase.h"
#include "ptBinning.h"
#include "etaBinning.h"
#include <TColor.h>

map<std::string , TGraphErrors*> userTGraphs_;                                                  
void CreateAndFillUserTGraph(const char* nameAndTitle, Int_t npoint, Double_t xvalue, Double_t yvalue, Double_t xErr, Double_t yErr)         
{                                                                                                                                            
  map<std::string , TGraphErrors*>::iterator nh_h = userTGraphs_.find(std::string(nameAndTitle));                                            
  TGraphErrors * h;                                                                                                                          
  if( nh_h == userTGraphs_.end() )                                                                                                           
    {                                                                                                                                                                                                                                               
      h = new TGraphErrors(0);                                                                                                               
      userTGraphs_[std::string(nameAndTitle)] = h;                                                                                           
      h->SetPoint(npoint, xvalue, yvalue);                                                                                                   
      h->SetPointError(npoint, xErr, yErr);                                                                                                  
    }                                                                                                                                        
  else                                                                                                                                       
    {                                                                                                                                        
      nh_h->second->SetPoint(npoint, xvalue, yvalue);                                                                                        
      nh_h->second->SetPointError(npoint, xErr, yErr);                                                                                       
    }                                                                                                                                        
}    
///////////////////////////////////

int main(int argc, char* argv[]) {

  std::string outputDir = "Plot";                 
  mkdir(outputDir.c_str(), 0777); 

  TString dataFileName;
  //  dataFileName = TString::Format("../../output/ReducedNtuples_TagAndProbe_2017-01-12/_20170112_155123/rootfile_CaloScouting_Run2016BCDEFG_2017-01-12_JEC_CaloHLT_Spring16_25nsV10_reduced_20170112_155123.root");
  //  dataFileName = TString::Format("../../output/ReducedNtuples_TagAndProbe_LowerCuts_2017-01-13/_20170113_093035/rootfile_CaloScouting_Run2016BCDEFG_LowerCuts_2017-01-13_JEC_CaloHLT_Spring16_25nsV10_LowerCuts_reduced_20170113_093035.root");

  // latest file
  // dataFileName = TString::Format("../../output/ReducedNtuples_TagAndProbe_LowerCuts_IOVsystem_2017-01-16/_20170116_115423/rootfile_CaloScouting_Run2016BCDEFG_LowerCuts_IOVsystem_2017-01-16_JEC_CaloHLT_p2Res_RecoIOV_20170116_115423.root");

  // with deltaETAjj cut
  //  dataFileName = TString::Format("../../output/ReducedNtuples_TagAndProbe_LowerCuts_IOVsystem_deltaETAjjCut_2017-01-18/merged/rootfile_CaloScouting_Run2016BCDEFG_LowerCuts_IOVsystem_2017-01-16_WithDeltaETAjj_20170118_101411.root");
  /////////////////////////////////////////////////////////////////////////////////////////////////////////

  // IOVSystem also for Calo -- Full Dataset
  dataFileName = TString::Format("../../ReducedNtuples_TagAndProbe_LowerCuts_IOVSystemForCalo_2017-03-02/rootfile_CaloScouting_Run2016BCDEFG_LowerCuts_IOVsystemForCalo_2017-03-02_HLTRecoComparison_20170302_164446.root");

  // IOVSystem also for Calo -- Run2016BCD
  //dataFileName = TString::Format("../../ReducedNtuples_Run2016BCD_TagAndProbe_LowerCuts_IOVSystemForCalo_2017-03-03/rootfile_CaloScouting_Run2016BCDEFG_LowerCuts_IOVsystemForCalo_2017-03-02_HLTRecoComparison_20170303_125607.root");

  // IOVSystem also for Calo -- Run2016E
  //dataFileName = TString::Format("../../ReducedNtuples_Run2016E_TagAndProbe_LowerCuts_IOVSystemForCalo_2017-03-03/rootfile_CaloScouting_Run2016BCDEFG_LowerCuts_IOVsystemForCalo_2017-03-02_Run2016E_HLTRecoComparison_20170303_130931.root");

  // IOVSystem also for Calo -- Run2016F
  //dataFileName = TString::Format("../../ReducedNtuples_Run2016F_TagAndProbe_LowerCuts_IOVSystemForCalo_2017-03-03/rootfile_CaloScouting_Run2016BCDEFG_LowerCuts_IOVsystemForCalo_2017-03-02_Run2016F_HLTRecoComparison_20170303_132011.root");

  // IOVSystem also for Calo -- Run2016G
  // dataFileName = TString::Format("../../ReducedNtuples_Run2016G_TagAndProbe_LowerCuts_IOVSystemForCalo_2017-03-03/rootfile_CaloScouting_Run2016BCDEFG_LowerCuts_IOVsystemForCalo_2017-03-02_Run2016G_HLTRecoComparison_20170303_133033.root");

  TFile* dataFile = TFile::Open(dataFileName);
  if (dataFile) {
    std::cout << "Opened data file '" << dataFileName << "'." << std::endl;
  }
  gErrorIgnoreLevel = kWarning;

  // List available triggers
  vector<string> triggers;
  triggers.push_back("ZeroBias");
  triggers.push_back("DoubleMu");
  triggers.push_back("CaloJet40");
  triggers.push_back("L1HTT150");
  triggers.push_back("CaloScoutingHT250");
  //  triggers.push_back("PFScoutingHT410");  
  std::cout<<"# Triggers used = "<<  triggers.size() << std::endl;

  for(int i = 0; i<triggers.size(); i++){

    const char *t = triggers[i].c_str();
    DrawTH1(dataFile, Form("pTTag_passHLT_%s", t), "pT tag", "Events", false, 0, 1000);  
    DrawTProfile(dataFile, Form("CaloProbe_vs_Tag_%s",t), "pT tag", "Calo probe", false, 0, 3000);  
    DrawTProfile(dataFile, Form("RatioProbe_vs_Tag_%s",t), "pT tag", "Calo,probe/PF,probe", false, 0, 3000);  
    DrawTProfile(dataFile, Form("RatioCaloTag_vs_Tag_%s",t), "pT tag", "Calo,probe/tag", false, 0, 3000);  
    DrawTProfile(dataFile, Form("RatioPFTag_vs_Tag_%s",t), "pT tag", "PF,probe/tag", false, 0, 3000);  
    
    TProfile *h_Mean1 = (TProfile*)dataFile->Get(Form("RatioCaloTag_vs_Tag_%s",t));
    TProfile *h_Mean2 = (TProfile*)dataFile->Get(Form("RatioPFTag_vs_Tag_%s",t));
    TProfile *h_Mean3 = (TProfile*)dataFile->Get(Form("RatioProbe_vs_Tag_%s",t));
    TProfile *h_Mean4 = (TProfile*)dataFile->Get(Form("CaloProbe_vs_Tag_%s",t));

    TH1F *ph_Mean1 = (TH1F*)h_Mean1->ProjectionX(Form("ph_Mean1_%s",t));
    ph_Mean1 -> Sumw2();
    TH1F *ph_Mean2 = (TH1F*)h_Mean2->ProjectionX(Form("ph_Mean2_%s",t));
    ph_Mean2 -> Sumw2();
    TH1F *h_Ratio_1_2 = (TH1F*)ph_Mean1->Clone(Form("h_Ratio_1_2_%s",t));
    h_Ratio_1_2->Divide(ph_Mean2);
    
    TGraphErrors *h_Final = new TGraphErrors(0);
    h_Final -> SetName(Form("MoneyPlot_%s",t));
    
    for(int ii=1 ; ii !=h_Mean3->GetNbinsX()+1 ; ++ii){
      
      if(h_Mean3->GetBinEntries(ii) >0){
	int n = h_Final->GetN();
	cout<< "n= " << n << endl;
	double xValue      =  h_Mean4 -> GetBinContent(ii);
	double xValueErr  =  h_Mean4 -> GetBinError(ii);
	double yValue      =   h_Ratio_1_2 -> GetBinContent(ii);
	double yValueErr =  max(0.028, h_Mean3 -> GetBinError(ii)) / sqrt(h_Mean3 -> GetBinEntries(ii) );
	cout<< "xvalue = "<< xValue <<" +- "<< xValueErr<< endl;
	cout<< "yvalue = "<< yValue <<" +- "<< yValueErr<< endl;      
	h_Final->SetPoint(n, xValue, yValue);
	h_Final->SetPointError(n, xValueErr, yValueErr);      
      }
    }

    TFile* outputFile= new TFile(Form("CaloJEC_TagAndProbeMethod_%s.root",t),"RECREATE"); 
    //TFile* outputFile= new TFile(Form("CaloJEC_TagAndProbeMethod_ClosureTest_%s.root",t),"RECREATE"); 
    outputFile->cd(); 
    h_Mean1 -> Write();
    h_Mean2 -> Write();
    h_Mean3 -> Write();
    h_Mean4 -> Write();
    ph_Mean1 -> Write();
    ph_Mean2 -> Write();
    h_Ratio_1_2 -> Write();
    h_Final->Write();
    outputFile->Close();   
    // Plotting
    TCanvas *cMean1 = new TCanvas("cMean1","", 800, 800);
    ph_Mean1->SetTitle("");
    ph_Mean1->GetXaxis()->SetRangeUser(0,500);
    ph_Mean1->Draw();
    cMean1->SaveAs(Form("Plot/Project_Mean1_%s.png",t));                        
    cMean1 -> Destructor();
    TCanvas *cMean2 = new TCanvas("cMean2","", 800, 800);
    ph_Mean2 -> SetTitle("");
    ph_Mean2->GetXaxis()->SetRangeUser(0,500);
    ph_Mean2 -> Draw();
    cMean2 -> SaveAs(Form("Plot/Project_Mean2_%s.png",t));                        
    cMean2 -> Destructor();

    TCanvas *canvas = new TCanvas("canvas","",800,800);                                                                                                                         
    h_Ratio_1_2    -> SetTitle(" ");                                                                                                                                                     
    h_Ratio_1_2    -> SetStats(0);                                                                                                                                                       
    h_Ratio_1_2    -> SetMarkerStyle(20);                                                                                                                                                
    h_Ratio_1_2    -> SetXTitle("pT tag");                                                                                                                                                 
    h_Ratio_1_2    -> SetYTitle("<Calo,probe>/<PF,probe>");                                                                                                                                                 
    h_Ratio_1_2    -> GetYaxis()->SetTitleOffset(1.5);                           
    h_Ratio_1_2    -> GetYaxis()->SetRangeUser(0.95, 1.08);                                                                                                                               
    h_Ratio_1_2    -> GetXaxis()->SetRangeUser(0, 500);                                                                                                                               
    h_Ratio_1_2    -> Draw();                                                                                                                                                            
    canvas->SetLeftMargin(0.13);                                                                                                                                                
    canvas ->SaveAs(Form("Plot/Ratio_Mean1_Mean2_%s.png",t));                                                                                                                                
    canvas -> Destructor();

    TCanvas *canvas1 = new TCanvas("canvas1","",800,800);                                                                                                                         
    h_Mean4    -> SetTitle(" ");                                                                                                                                                     
    h_Mean4    -> SetStats(0);                                                                                                                                                       
    h_Mean4    -> SetMarkerStyle(20);                                                                                                                                                
    h_Mean4    -> SetXTitle("pT tag");                                                                                                                                                 
    h_Mean4    -> SetYTitle("Calo,probe");                                                                                                                                                 
    h_Mean4    -> GetYaxis()->SetTitleOffset(1.5);                                                                                                                                   
    // h_Mean4    -> GetXaxis()->SetRangeUser(0, 1000);                          
    // h_Mean4    -> GetYaxis()->SetRangeUser(-0.1, 0.1);                                                                                                                               
    h_Mean4    -> Draw();                                                                                                                                                            
    canvas1->SetLeftMargin(0.13);                                                                                                                                                
    canvas1 ->SaveAs(Form("Plot/Mean4_%s.png",t));                                                                                                                                
    canvas1 -> Destructor();

    TCanvas *canvas2 = new TCanvas("canvas2","",800,800);                                                                                                                         
    h_Final    -> SetTitle(" ");                                                                                                                                                     
    // h_Final    -> SetStats(0);                                                                                                                                                       
    // h_Final    -> GetXaxis()->SetRangeUser(0, 3000);                                                                                                                              
    h_Final    -> SetMarkerStyle(20);                                                                                                                                                
    h_Final    -> GetXaxis()-> SetTitle("Calo,probe");                                                                                                                                                 
    h_Final    -> GetYaxis()-> SetTitle("<Calo,probe>/<PF,probe>");  
    h_Final    -> GetYaxis()->SetTitleOffset(1.7);                                                                                                                                   
    h_Final    -> GetYaxis()->SetRangeUser(0.95, 1.08);                                                                                                                               
    h_Final    -> Draw("ZAP");                                                                                                                                                            
    canvas2->SetLeftMargin(0.13);                                                                                                                                                
    canvas2 ->SaveAs(Form("Plot/Final_%s.png",t));                                                                                                                                
    canvas2 -> Destructor();
  }
  
}
