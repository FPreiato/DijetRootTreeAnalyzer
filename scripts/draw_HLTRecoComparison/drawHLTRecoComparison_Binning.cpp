#include <stdlib.h>
#include <sys/stat.h>  
#include <time.h>

#include "TParameter.h"
#include "TPaveText.h"
#include "TError.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TAxis.h"
#include <TColor.h>
#include "drawBase.h"
#include "ptBinning.h"
#include "mJJBinning.h"
#include "etaBinning.h"

void drawComparison_New(TFile* dataFile1, TFile* dataFile2, TFile* dataFile3, TFile* dataFile4, TFile* dataFile5, TFile* dataFile6, const char *nameHisto, const char *XTitle, const char *YTitle, bool Normalized, bool log, bool colz, double xmin, double xmax, double ymin, double ymax){

  TString HistoName =TString::Format(nameHisto);

  TH1F *h1 = (TH1F*)dataFile1->Get(HistoName);
  if( !h1 ) 
    TProfile *h1 = (TProfile*)dataFile1->Get(HistoName);
  TH1F *h2 = (TH1F*)dataFile2->Get(HistoName);
  if( !h2 ) 
    TProfile *h2 = (TProfile*)dataFile2->Get(HistoName);  
  TH1F *h3 = (TH1F*)dataFile3->Get(HistoName);
  if( !h3 ) 
    TProfile *h3 = (TProfile*)dataFile3->Get(HistoName);  
  TH1F *h4 = (TH1F*)dataFile4->Get(HistoName);
  if( !h4 ) 
    TProfile *h4 = (TProfile*)dataFile4->Get(HistoName);  
  TH1F *h5 = (TH1F*)dataFile5->Get(HistoName);
  if( !h5 ) 
    TProfile *h5 = (TProfile*)dataFile5->Get(HistoName);  
  TH1F *h6 = (TH1F*)dataFile6->Get(HistoName);
  if( !h6 ) 
    TProfile *h6 = (TProfile*)dataFile6->Get(HistoName);  

  /*    
  if( !h1 || !h2 || !h3 || !h4 || !h5 || !h6 ){
    std::cout<< std::endl;
    std::cout<< "Object doesn't found" << std::endl;
    return;
    } */

  TLegend* legend = new TLegend(0.78, 0.75, 0.90, 0.90);
  legend->SetTextFont(42);
  legend->SetBorderSize(0);
  legend->SetFillColor(kWhite);
  legend->SetFillStyle(0);
  legend->SetTextSize( 0.036);
  if(h1)  legend->AddEntry(h1, "ZeroBias", "LP");
  if(h2)  legend->AddEntry(h2, "DoubleMu", "LP");
  if(h3)  legend->AddEntry(h3, "CaloJet40", "LP");
  if(h4)  legend->AddEntry(h4, "L1HT150", "LP");
  if(h5)  legend->AddEntry(h5, "HT250", "LP");
  if(h6)  legend->AddEntry(h6, "HT450", "LP");
  
  if(Normalized){
    h1 -> Scale(1/h1->Integral());
    h2 -> Scale(1/h2->Integral());
    h3 -> Scale(1/h3->Integral());
    h4 -> Scale(1/h4->Integral());
    h5 -> Scale(1/h5->Integral());
    h6 -> Scale(1/h6->Integral());
  }

  //  if (h1->GetMaximum() >= h2->GetMaximum() ) ymax = h1->GetMaximum() ; 
  // if (h1->GetMaximum() < h2->GetMaximum() ) ymax = h2->GetMaximum() ; 
  //  h1 -> SetMaximum(ymax+ 0.1*ymax);
  TCanvas *canvas = new TCanvas("canvas","",800,800);
  if(log) gPad->SetLogy();
  h6->SetStats(0);
  h6->SetTitle(" ");
  h6->SetXTitle(XTitle);
  h6->GetXaxis()->SetRangeUser(xmin,xmax);
  h6->SetYTitle(YTitle);
  h6 -> SetMaximum(ymax);
  h6 -> SetMinimum(ymin);
  h6    -> GetYaxis()->SetTitleOffset(1.55);

  h6->SetLineColor(kBlue);
  h6->SetMarkerColor(kBlue);
  h6->SetMarkerStyle(7);
  h6->Draw();

  if(h1){
    h1->SetLineColor(kBlack);
    h1->SetMarkerColor(kBlack);
    h1->SetMarkerStyle(2);
    h1->Draw("same");
  } 
  if(h2){
    h2->SetLineColor(kRed);
    h2->SetMarkerColor(kRed);
    h2->SetMarkerStyle(3);
    h2->Draw("same");
  }
  if(h3){
    h3->SetLineColor(kGreen);
    h3->SetMarkerColor(kGreen);
    h3->SetMarkerStyle(4);
    h3->Draw("same");
  }
  if(h4){
    h4->SetLineColor(kYellow +2);
    h4->SetMarkerColor(kYellow +2);
    h4->SetMarkerStyle(5);
    h4->Draw("same");
  }
  if(h5){
    h5->SetLineColor(kViolet);
    h5->SetMarkerColor(kViolet);
    h5->SetMarkerStyle(6);
    h5->Draw("same");
  }

  legend->Draw();
  canvas ->SaveAs("Plot/Compare_"+HistoName+".png");
  std::cout<< "Saved: Compare_"<< HistoName << std::endl;
  if(pdfsave)  canvas ->SaveAs("Plot/Compare_"+HistoName+".pdf");
  if(rootsave)  canvas ->SaveAs("Plot/Compare_"+HistoName+".root");
  canvas ->Destructor();
}

//////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  std::string outputDir = "Plot";  
  mkdir(outputDir.c_str(), 0777); 


  TString dataFileName_ZeroBias; // #1
  dataFileName_ZeroBias = TString::Format("/cmshome/fpreiato/Scouting_Dijet/CMSSW_7_4_15/src/CMSDIJET/DijetRootTreeAnalyzer/output/HLTReco_mJJComparison/rootFile_JEC_HLT_v7_SamePtCuts_NoMjjCut_ZeroBias.root" );
  TString dataFileName_DoubleMu; // #2
  dataFileName_DoubleMu = TString::Format("/cmshome/fpreiato/Scouting_Dijet/CMSSW_7_4_15/src/CMSDIJET/DijetRootTreeAnalyzer/output/HLTReco_mJJComparison/rootFile_JEC_HLT_v7_SamePtCuts_NoMjjCut_DoubleMu.root" );
  TString dataFileName_CaloJet40; // #3
  dataFileName_CaloJet40 = TString::Format("/cmshome/fpreiato/Scouting_Dijet/CMSSW_7_4_15/src/CMSDIJET/DijetRootTreeAnalyzer/output/HLTReco_mJJComparison/rootFile_JEC_HLT_v7_SamePtCuts_NoMjjCut_CaloJet40.root" );
  TString dataFileName_L1HTT150; // #4
  dataFileName_L1HTT150 = TString::Format("/cmshome/fpreiato/Scouting_Dijet/CMSSW_7_4_15/src/CMSDIJET/DijetRootTreeAnalyzer/output/HLTReco_mJJComparison/rootFile_JEC_HLT_v7_SamePtCuts_NoMjjCut_L1HTT150.root" );
  TString dataFileName_HT250; // #5
  dataFileName_HT250 = TString::Format("/cmshome/fpreiato/Scouting_Dijet/CMSSW_7_4_15/src/CMSDIJET/DijetRootTreeAnalyzer/output/HLTReco_mJJComparison/rootFile_JEC_HLT_v7_SamePtCuts_NoMjjCut_HT250.root" );
  TString dataFileName_HT450; // #6
  dataFileName_HT450 = TString::Format("/cmshome/fpreiato/Scouting_Dijet/CMSSW_7_4_15/src/CMSDIJET/DijetRootTreeAnalyzer/output/HLTReco_mJJComparison/rootFile_JEC_HLT_v7_SamePtCuts_NoMjjCut_HT450.root" );


  TFile* dataFile_ZeroBias    = TFile::Open(dataFileName_ZeroBias);
  TFile* dataFile_DoubleMu = TFile::Open(dataFileName_DoubleMu);
  TFile* dataFile_CaloJet40  = TFile::Open(dataFileName_CaloJet40);
  TFile* dataFile_L1HTT150 = TFile::Open(dataFileName_L1HTT150);
  TFile* dataFile_HT250       = TFile::Open(dataFileName_HT250);
  TFile* dataFile_HT450       = TFile::Open(dataFileName_HT450);

  if (dataFile_ZeroBias) {
    std::cout << "Opened data file: '" << dataFileName_ZeroBias << "'." << std::endl;
  }
  if (dataFile_DoubleMu) {
    std::cout << "Opened data file: '" << dataFileName_DoubleMu << "'." << std::endl;
  }
  if (dataFile_CaloJet40) {
    std::cout << "Opened data file: '" << dataFileName_CaloJet40 << "'." << std::endl;
  }
  if (dataFile_L1HTT150) {
    std::cout << "Opened data file: '" << dataFileName_L1HTT150 << "'." << std::endl;
  }
  if (dataFile_HT250) {
    std::cout << "Opened data file: '" << dataFileName_HT250 << "'." << std::endl;
  }
  if (dataFile_HT450) {
    std::cout << "Opened data file: '" << dataFileName_HT450 << "'." << std::endl;
  }


  gErrorIgnoreLevel = kWarning;

  bool colz = true;
  bool log= true;

  /////////////////////////////////// starting draw

  drawComparison_New(dataFile_ZeroBias,  dataFile_DoubleMu, dataFile_CaloJet40, dataFile_L1HTT150, dataFile_HT250, dataFile_HT450, "mJJBias_vs_Mjj", "Mjj [GeV]", "mJJ Bias", false, false, false, 0, 2100, -0.1, 0.1);           


  /*
  drawComparison_New(dataFile_ZeroBias,  dataFile_DoubleMu, dataFile_CaloJet40, dataFile_L1HTT150, dataFile_HT250, dataFile_HT450, "AK4_Eta_JetHLT", "#eta", "Normalized", true, false, false, -2.5, 2.5, 0., 0.08);           

  drawComparison_New(dataFile_ZeroBias,  dataFile_DoubleMu, dataFile_CaloJet40, dataFile_L1HTT150, dataFile_HT250, dataFile_HT450, "AK4_pTBias_vs_Pt", "pT [GeV]", "pT Bias", false, false, false, 0, 2000, -0.1, 0.1);           

  drawComparison_New(dataFile_ZeroBias,  dataFile_DoubleMu, dataFile_CaloJet40, dataFile_L1HTT150, dataFile_HT250, dataFile_HT450, "AK4_pTBias_vs_Pt_Barrel", "pT [GeV]", "pT Bias", false, false, false, 0, 2000, -0.1, 0.1);           

  drawComparison_New(dataFile_ZeroBias,  dataFile_DoubleMu, dataFile_CaloJet40, dataFile_L1HTT150, dataFile_HT250, dataFile_HT450, "AK4_pTBias_vs_Pt_Endcap", "pT [GeV]", "pT Bias", false, false, false, 0, 2000, -0.1, 0.1);           

  PtBinning mPtBinning;
  size_t pTBinningSize = mPtBinning.size();
  for (size_t jj = 0; jj < pTBinningSize; jj++) {
    
    std::pair<float, float> ptBins = mPtBinning.getBinValue(jj);	 
    std::string AK4_pTBias_vs_Eta = TString::Format("AK4_pTBias_vs_Eta_pT_%i_%i", (int) ptBins.first, (int) ptBins.second ).Data();

    drawComparison_New(dataFile_ZeroBias,  dataFile_DoubleMu, dataFile_CaloJet40, dataFile_L1HTT150, dataFile_HT250, dataFile_HT450, AK4_pTBias_vs_Eta.c_str(), "#eta", "Normalized", false, false, false, -2.5, 2.5, -0.1, 0.1);           
    
    
  }
*/
  /*




  for(int ii =0 ; ii<3; ii++){
    TCanvas *c1 = new TCanvas("c1","",800,800);  
    
    TLegend* legend = new TLegend(0.40, 0.65, 0.90, 0.85);                                                                                                                
    legend->SetTextFont(42);                                                                                                                                              
    legend->SetBorderSize(0);                                                                                                                                             
    legend->SetFillColor(kWhite);                                                                                                                                         
    legend->SetFillStyle(0);                                                                                                                                              
    legend->SetTextSize( 0.036);                                                                                                                                          

    TH1D* h2;
    if(ii == 0)     h2 = (TH1D*)dataFile1->Get( "AK4_pTBias_vs_Eta");
    if(ii == 1)     h2 = (TH1D*)dataFile2->Get( "AK4_pTBias_vs_Eta");
    if(ii == 2)     h2 = (TH1D*)dataFile3->Get( "AK4_pTBias_vs_Eta");
    h2 -> SetLineColor(9); 
    h2 -> SetMarkerColor(9);  
    h2 -> SetMarkerStyle(9);  
    h2 -> SetLineWidth(2.5);        

    if(!h2) cout<< "Object not existing"<< endl;

    int ibin = 0;      

    for (size_t jj = 0; jj < pTBinningSize; jj++) {
	
      if(ii == 1 && jj >=2 ) continue;         
      if(ii == 2 && jj < 2) continue;     
      if(ii == 0 && jj < 3 ) continue;    
      
      std::pair<float, float> ptBins = mPtBinning.getBinValue(jj);	 
      std::string AK4_pTBias_vs_Eta = TString::Format("AK4_pTBias_vs_Eta_pT_%i_%i", (int) ptBins.first, (int) ptBins.second ).Data();
      
      //      int pTmax = (int) ptBins.second;

      TH1D* h1;
      if(ii == 0 )     h1 = (TH1D*)dataFile1->Get( AK4_pTBias_vs_Eta.c_str());
      if(ii == 1 )     h1 = (TH1D*)dataFile2->Get( AK4_pTBias_vs_Eta.c_str());
      if(ii == 2)      h1 = (TH1D*)dataFile3->Get( AK4_pTBias_vs_Eta.c_str());

      if(!h1) cout<< "Object not existing"<< endl;     

      legend->AddEntry(h1, Form("%i < pT < %i", (int) ptBins.first, (int) ptBins.second ), "LP");                                                                        

      double den; 
      double num; 
      if( ibin == 0 ){
	num = h1 -> GetBinContent(10) ;  
	cout<<"num = "<< num << endl;;  
	h1 -> SetTitle(" ");  
	h1 -> SetStats(0); 
	h1 -> SetXTitle("#eta"); 
	h1 -> SetYTitle("pT(Reco)-pT(HLT)/pT(HLT)"); 
	h1 -> GetYaxis()->SetTitleOffset(1.4);
	h1 -> GetXaxis()->SetRangeUser(-2.5, 2.5); 
	//  h1 -> SetLineColor(kBlue); 
	//  h1 -> SetMarkerColor(kBlue);  
	h1 -> SetLineColor(jj+1); 
	h1 -> SetMarkerColor(jj+1);  
	h1 -> SetMarkerStyle(jj);  
	h1 -> SetMaximum(0.1);
	h1 -> SetMinimum(-0.1);
	h1 -> Draw();
      }else{
	den = h1 -> GetBinContent(10) ;  
	cout<<" den = "<< den << endl;;  
	//	h1->Scale( num/den);
	h1->SetLineColor(jj+1);  
	h1->SetMarkerColor(jj+1);
	h1->SetMarkerStyle(jj);
	h1->Draw("same"); 
      }
      ibin++;
    }

    //    h2->Draw("same");

    legend->Draw();
    if(ii ==0)      c1 ->SaveAs("Plot/AK4_pTBias_vs_Eta_TriggerHT450.png"); 
    if(ii ==1)      c1 ->SaveAs("Plot/AK4_pTBias_vs_Eta_TriggerDoubleMu.png"); 
    if(ii ==2)      c1 ->SaveAs("Plot/AK4_pTBias_vs_Eta_TriggerL1HTT150.png"); 
  
  }

  ////////////////////////////////

    TCanvas *c3 = new TCanvas("c3","",800,800);  
    
    TLegend* legend2 = new TLegend(0.40, 0.65, 0.90, 0.85);                                                                                                                
    legend2->SetTextFont(42);                                                                                                                                              
    legend2->SetBorderSize(0);                                                                                                                                             
    legend2->SetFillColor(kWhite);                                                                                                                                         
    legend2->SetFillStyle(0);                                                                                                                                              
    legend2->SetTextSize( 0.036);                                                                                                                                          

    for (size_t jj = 0; jj < pTBinningSize; jj++) {
	
      std::pair<float, float> ptBins = mPtBinning.getBinValue(jj);	 
      std::string AK4_pTBias_vs_Eta = TString::Format("AK4_pTBias_vs_Eta_pT_%i_%i", (int) ptBins.first, (int) ptBins.second ).Data();
	
      TH1D* h_HT450       = (TH1D*)dataFile1->Get( AK4_pTBias_vs_Eta.c_str());
      TH1D* h_DoubleMu = (TH1D*)dataFile2->Get( AK4_pTBias_vs_Eta.c_str());
      TH1D* h_L1HTT150 = (TH1D*)dataFile3->Get( AK4_pTBias_vs_Eta.c_str());

      double num; 
      double den1; 
      double den2; 
      den1 = h_HT450 -> GetBinContent(10) ;  
      cout<<"num = "<< num << endl;;  

      num = h_DoubleMu -> GetBinContent(10) ;  
      cout<<" den1 = "<< den1 << endl;; 
      den2 = h_L1HTT150 -> GetBinContent(10) ;  
      cout<<" den2 = "<< den2 << endl;;  

      
      h_HT450 -> SetTitle(" ");  
      h_HT450 -> SetStats(0); 
      h_HT450 -> SetXTitle("#eta"); 
      h_HT450 -> SetYTitle("pT(Reco)-pT(HLT)/pT(HLT)"); 
      h_HT450 -> GetYaxis()->SetTitleOffset(1.4);
      h_HT450 -> GetXaxis()->SetRangeUser(-2.5, 2.5); 
      h_HT450 -> SetLineColor(kBlue); 
      h_HT450 -> SetMarkerColor(kBlue);  
      h_HT450 -> SetMarkerStyle(2);  
      h_HT450 -> SetMaximum(0.1);
      h_HT450 -> SetMinimum(-0.1);
      h_HT450 -> Draw();
      

      //      h_DoubleMu->Scale( num/den1);     
      /*
      h_DoubleMu -> SetTitle(" ");  
      h_DoubleMu -> SetStats(0); 
      h_DoubleMu -> SetXTitle("#eta"); 
      h_DoubleMu -> SetYTitle("pT(Reco)-pT(HLT)/pT(HLT)"); 
      h_DoubleMu -> GetYaxis()->SetTitleOffset(1.4);
      h_DoubleMu -> GetXaxis()->SetRangeUser(-2.5, 2.5); 
      h_DoubleMu -> SetLineColor(kRed);  
      h_DoubleMu -> SetMarkerColor(kRed);
      h_DoubleMu -> SetMarkerStyle(3);
      h_DoubleMu -> SetMaximum(0.1);
      h_DoubleMu -> SetMinimum(-0.1);
      h_DoubleMu -> Draw(); 
      */
  /* 
     //      h_L1HTT150->Scale( num/den2);     
      h_L1HTT150 -> SetLineColor(kGreen);  
      h_L1HTT150 -> SetMarkerColor(kGreen);
      h_L1HTT150 -> SetMarkerStyle(4);
      h_L1HTT150 -> Draw("same"); 

      TLegend* legend1 = new TLegend(0.70, 0.65, 0.90, 0.85);                                                                                                                
      legend1->SetTextFont(42);                                                                                                                                              
      legend1->SetBorderSize(0);                                                                                                                                             
      legend1->SetFillColor(kWhite);                                                                                                                                         
      legend1->SetFillStyle(0);                                                                                                                                              
      legend1->SetTextSize( 0.036);                                                                                                                                          

      // legend1->AddEntry(h_DoubleMu, "DoubleMu", "LP");                                                                        
      legend1->AddEntry(h_L1HTT150, "L1HTT150", "LP");                                                                        
      legend1->AddEntry(h_HT450, "HT450", "LP");                                                                        

      TString HistoName =TString::Format( AK4_pTBias_vs_Eta.c_str() ); 

      legend1 -> Draw();
      c3->SaveAs("Plot/"+HistoName+"_NoDoubleMu.png");


    }

    ////////////////////////////////////////////////////////


  TCanvas *c_AK4_mJJBias_vs_Mjj = new TCanvas("c_AK4_mJJBias_vs_Mjj","",800,800);

  cout<< "Disegno AK4_mJJBias_vs_Mjj"<<endl;

  TH1D* h_mJJBias_vs_Mjj_HT450       = (TH1D*)dataFile1->Get( "mJJBias_vs_Mjj" );
  TH1D* h_mJJBias_vs_Mjj_DoubleMu = (TH1D*)dataFile2->Get( "mJJBias_vs_Mjj" );
  TH1D* h_mJJBias_vs_Mjj_L1HTT150 = (TH1D*)dataFile3->Get( "mJJBias_vs_Mjj" );

  h_mJJBias_vs_Mjj_HT450 -> SetTitle(" ");  
  h_mJJBias_vs_Mjj_HT450 -> SetStats(0); 
  h_mJJBias_vs_Mjj_HT450 -> SetXTitle("Mjj [GeV]"); 
  h_mJJBias_vs_Mjj_HT450 -> SetYTitle("mJJ(Reco)-mJJ(HLT)/mJJ(HLT)"); 
  h_mJJBias_vs_Mjj_HT450 -> GetYaxis()->SetTitleOffset(1.5);
  h_mJJBias_vs_Mjj_HT450 -> GetXaxis()->SetRangeUser(0, 2000); 
  h_mJJBias_vs_Mjj_HT450 -> SetLineColor(kBlue); 
  h_mJJBias_vs_Mjj_HT450 -> SetMarkerColor(kBlue);  
  h_mJJBias_vs_Mjj_HT450 -> SetMarkerStyle(2);  
  h_mJJBias_vs_Mjj_HT450 -> SetMaximum(0.1);
  h_mJJBias_vs_Mjj_HT450 -> SetMinimum(-0.1);
  h_mJJBias_vs_Mjj_HT450 -> Draw();

  h_mJJBias_vs_Mjj_DoubleMu -> SetLineColor(kRed);  
  h_mJJBias_vs_Mjj_DoubleMu -> SetMarkerColor(kRed);
  h_mJJBias_vs_Mjj_DoubleMu -> SetMarkerStyle(3);
  h_mJJBias_vs_Mjj_DoubleMu -> Draw("same"); 

  h_mJJBias_vs_Mjj_L1HTT150 -> SetLineColor(kGreen);  
  h_mJJBias_vs_Mjj_L1HTT150 -> SetMarkerColor(kGreen);
  h_mJJBias_vs_Mjj_L1HTT150 -> SetMarkerStyle(4);
  h_mJJBias_vs_Mjj_L1HTT150 -> Draw("same"); 

  TLegend* legend111 = new TLegend(0.70, 0.65, 0.90, 0.85);                                                                                                                
  legend111->SetTextFont(42);                                                                                                                                              
  legend111->SetBorderSize(0);                                                                                                                                             
  legend111->SetFillColor(kWhite);                                                                                                                                         
  legend111->SetFillStyle(0);                                                                                                                                              
  legend111->SetTextSize( 0.036);                                                                                                                                          

  legend111->AddEntry(h_mJJBias_vs_Mjj_DoubleMu, "DoubleMu", "LP");                                                                        
  legend111->AddEntry(h_mJJBias_vs_Mjj_L1HTT150, "L1HTT150", "LP");                                                                        
  legend111->AddEntry(h_mJJBias_vs_Mjj_HT450, "HT450", "LP");                                                                        

  legend111 -> Draw();
  c_AK4_mJJBias_vs_Mjj->SaveAs("Plot/AK4_mJJBias_vs_Mjj.png");

  cout<< "Fatto"<<endl;

*/









    //  EtaBinning  mEtaBinning;
    //  mJJBinning mMjjBinning; 
    //  size_t etaBinningSize = mEtaBinning.size();  
    //  size_t mJJBinningSize = mMjjBinning.size();









    return 0;
 
}






















/*
  for (size_t ii = 0; ii < etaBinningSize; ii++) {
  std::string etaName = mEtaBinning.getBinName(ii);

  std::string AK4_mJJBias = TString::Format("AK4_mJJBias_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
  std::string AK4_mJJBias_vs_Nvtx = TString::Format("AK4_mJJBias_vs_Nvtx_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data(); 
  std::string AK4_mJJBias_vs_Mjj = TString::Format("AK4_mJJBias_vs_Mjj_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();

  FitTH1(dataFile1, AK4_mJJBias.c_str(),  "pT(HLT)-pT(Reco)/pT(Reco)",  "Events", false,  -0.5, 0.5);
  LinearFit(dataFile1, AK4_mJJBias_vs_Nvtx.c_str(),  "nVtx",  "pT(HLT)-pT(Reco)/pT(Reco)", false,  0, 25);

  DrawTProfile(dataFile1, AK4_mJJBias_vs_Mjj.c_str(),  "pT [GeV]",  "pT(HLT)-pT(Reco)/pT(Reco)", false, ptBins.first, ptBins.second); 

  std::string mJJBias = TString::Format("mJJBias_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
  std::string mJJBias_vs_Nvtx = TString::Format("mJJBias_vs_Nvtx_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
  std::string mJJBias_vs_Eta = TString::Format("mJJBias_vs_Eta_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
  std::string mJJBias_vs_Mjj = TString::Format("mJJBias_vs_Mjj_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
  FitTH1(dataFile1, mJJBias.c_str(),  "pT(HLT)-pT(Reco)/pT(Reco)",  "Events", false,  -0.5, 0.5);
  LinearFit(dataFile1, pTBias_vs_Nvtx.c_str(),  "nVtx",  "pT(HLT)-pT(Reco)/pT(Reco)", false,  0, 25);
  DrawTProfile(dataFile1, pTBias_vs_Eta.c_str(),  "#eta",  "pT(HLT)-pT(Reco)/pT(Reco)", false, -2.5, 2.5);
  DrawTProfile(dataFile1, pTBias_vs_Mjjyyyyyyy.c_str(),  "pT [GeV]",  "pT(HLT)-pT(Reco)/pT(Reco)", false, ptBins.first, ptBins.second);

  std::string Asymmetry = TString::Format("Asymmetry_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
  std::string AsymmetryReco = TString::Format("AsymmetryReco_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();

  DrawComparison(dataFile1, AsymmetryReco.c_str(), Asymmetry.c_str(), "Asymmetry", "Normalized", false, false, -0.5, 0.5);

  }
*/
/* 
   for (size_t ii = 0; ii < mJJBinningSize; ii++) {

   std::pair<float, float> mJJBins = mMjjBinning.getBinValue(ii);	 

   std::string mJJBias = TString::Format("mJJBias_mJJ_%i_%i", (int) mJJBins.first, (int) mJJBins.second ).Data();
   std::string mJJBias_vs_Nvtx = TString::Format("mJJBias_vs_Nvtx_mJJ_%i_%i", (int) mJJBins.first, (int) mJJBins.second ).Data();
   std::string mJJBias_vs_Mjj = TString::Format("mJJBias_vs_Mjj_mJJ_%i_%i", (int) mJJBins.first, (int) mJJBins.second ).Data();
   FitTH1(dataFile1, mJJBias.c_str(),  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)",  "Events", false,  -0.5, 0.5);
   LinearFit(dataFile1, mJJBias_vs_Nvtx.c_str(),  "nVtx",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false,  0, 25);
   DrawTProfile(dataFile1, mJJBias_vs_Mjj.c_str(),  "mJJ [GeV]",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false, mJJBins.first, mJJBins.second);
   }  
*/



// end code

////////////////////////////////////////
/*
  EtaBinning mEtaBinning;
  PtmakBinning mPtBinning;
  
  size_t etaBinningSize = mEtaBinning.size();
  size_t pTBinningSize = mPtBinning.size();
  double nEntriesTot=0;

  for (size_t ii = 0; ii < etaBinningSize; ii++) {
  for (size_t jj = 0; jj < pTBinningSize; jj++) {
 
  std::string etaName = mEtaBinning.getBinName(ii);
  std::pair<float, float> ptBins = mPtBinning.getBinValue(jj);	 
  std::string HistoName = TString::Format("pTBias_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
  std::cout << HistoName.c_str()<< std::endl;
  TH1D *h1 = (TH1D*)dataFile1->Get(HistoName.c_str());
  if( !h1) continue;
 
  double nEntries = h1->GetEntries();
  std::cout<< "nEntries = "<< nEntries << std::endl;
  nEntriesTot +=nEntries;
  }
  }
  std::cout<< "nEntries TOTALI = "<< nEntriesTot << std::endl;
*/

