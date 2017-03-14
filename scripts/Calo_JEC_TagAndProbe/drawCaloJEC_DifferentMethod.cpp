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

bool ClosureTest = false;

int main(int argc, char* argv[]) {

  std::string outputDir = "Plot";                 
  mkdir(outputDir.c_str(), 0777); 

  TFile *f_TypeI;
  TFile *f_TypeII;
  TFile *f_TypeIII;
  TFile *f_TypeIV;
  if(ClosureTest){
    // f_TypeI = new TFile("../../output/CaloParkingScouting_7600pb/reducedFileProcessed_BiasJEC_ClosureTest_TypeI_20160725_164038/rootFile_BiasJEC_ClosureTest_TypeI.root","READ");
    // f_TypeII = new TFile("../../output/CaloParkingScouting_7600pb/reducedFileProcessed_BiasJEC_ClosureTest_TypeII_20160725_164717/rootFile_BiasJEC_ClosureTest_TypeII.root","READ");
    // f_TypeIII = new TFile("../../output/CaloParkingScouting_7600pb/reducedFileProcessed_BiasJEC_ClosureTest_TypeIII_20160725_165315/rootFile_BiasJEC_ClosureTest_TypeIII.root","READ");
    // f_TypeIV = new TFile("../../output/CaloParkingScouting_7600pb/reducedFileProcessed_BiasJEC_ClosureTest_TypeIV_20160725_165843/rootFile_BiasJEC_ClosureTest_TypeIV.root","READ");

    //    f_TypeI = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_ClosureTest_TypeI_20160726_124555/rootFile_ClosureTest_TypeI_OldCuts.root","READ");
    f_TypeI = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_ClosureTest_TypeI_20160726_182457/rootFile_ClosureTest_TypeI_OldCuts.root","READ");
    f_TypeII = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_ClosureTest_TypeII_20160726_130010/rootFile_ClosureTest_TypeII_OldCuts.root","READ");
    f_TypeIII = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_ClosureTest_TypeIII_20160726_130447/rootFile_ClosureTest_TypeIII_OldCuts.root","READ");
    f_TypeIV = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_ClosureTest_TypeIV_20160726_131016/rootFile_ClosureTest_TypeIV_OldCuts.root ","READ");
  }else{
    // f_TypeI = new TFile("../../output/CaloParkingScouting_7600pb/reducedFileProcessed_BiasJEC_TypeI_20160725_120433/rootFile_BiasJEC_TypeI.root","READ");
    // f_TypeII = new TFile("../../output/CaloParkingScouting_7600pb/reducedFileProcessed_BiasJEC_TypeII_20160725_145229/rootFile_BiasJEC_TypeII.root","READ");
    // f_TypeIII = new TFile("../../output/CaloParkingScouting_7600pb/reducedFileProcessed_BiasJEC_TypeIII_20160725_150137/rootFile_BiasJEC_TypeIII.root","READ");
    // f_TypeIV = new TFile("../../output/CaloParkingScouting_7600pb/reducedFileProcessed_BiasJEC_TypeIV_20160725_153038/rootFile_BiasJEC_TypeIV.root","READ");

    f_TypeI = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_TypeI_20160726_155247/rootFile_OriginalBias_TypeI_OldCuts.root","READ");
    f_TypeII = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_TypeII_20160726_121404/rootFile_OriginalBias_TypeII_OldCuts.root","READ");
    f_TypeIII = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_TypeIII_20160726_122847/rootFile_OriginalBias_TypeIII_OldCuts.root ","READ");
    f_TypeIV = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_TypeIV_20160726_123655/rootFile_OriginalBias_TypeIV_OldCuts.root","READ");
  }
    
  if (f_TypeI) {
    std::cout << "Opened data file 'TypeI' " << std::endl;
 }
  if (f_TypeII) {
    std::cout << "Opened data file 'TypeII' " << std::endl;
 }
  if (f_TypeIII) {
    std::cout << "Opened data file 'TypeIII' " << std::endl;
 }
  if (f_TypeIV) {
    std::cout << "Opened data file 'TypeIV' " << std::endl;
 }
  
  gErrorIgnoreLevel = kWarning;

  TProfile *p_mJJRatio_vs_mJJ;
  // TH2D *h_mJJRatio_vs_mJJ;
  TProfile *p_ptRatio_vs_pt;
  // TH2D *h_ptRatio_vs_pt;

  TCanvas *c1 = new TCanvas("c1","",800,600); 
  //gPad->SetLogz();
  //gStyle->SetPalette(55);

  TCanvas *c2 = new TCanvas("c2","",800,600); 
  //gPad->SetLogz();
  //gStyle->SetPalette(55);

  TLegend* legend = new TLegend(0.58, 0.68, 0.80, 0.90);                                                                                                                      
  legend->SetTextFont(42);                                                                                                                                                    
  legend->SetBorderSize(0);                                                                                                                                                   
  legend->SetFillColor(kWhite);                                                                                                                                               
  legend->SetFillStyle(0);                                                                                                                                                    
  legend->SetTextSize( 0.036);
  legend->SetHeader("On X-axis");
  TString label;   
    
  for(int ii = 0 ; ii < 4 ; ii++ ){
    
    std::cout<< "ii ="<< ii <<std::endl;
    
    if(ii == 0){     
      p_mJJRatio_vs_mJJ = (TProfile*)f_TypeI->Get("p_mJJRatio_vs_mJJ_CaloScoutingHT250");
      p_ptRatio_vs_pt = (TProfile*)f_TypeI->Get("p_ptRatio_vs_pt_CaloScoutingHT250");
      label = TString::Format("Reco");
    }else if(ii == 1){
      p_mJJRatio_vs_mJJ = (TProfile*)f_TypeII->Get("p_mJJRatio_vs_mJJ_CaloScoutingHT250");
      p_ptRatio_vs_pt = (TProfile*)f_TypeII->Get("p_ptRatio_vs_pt_CaloScoutingHT250");
      label = TString::Format("HLT");
    }else if(ii == 2){
      p_mJJRatio_vs_mJJ = (TProfile*)f_TypeIII->Get("p_mJJRatio_vs_mJJ_CaloScoutingHT250");
      p_ptRatio_vs_pt = (TProfile*)f_TypeIII->Get("p_ptRatio_vs_pt_CaloScoutingHT250");
      label = TString::Format("Random");
    }else if(ii == 3){
      p_mJJRatio_vs_mJJ = (TProfile*)f_TypeIV->Get("p_mJJRatio_vs_mJJ_CaloScoutingHT250");
      p_ptRatio_vs_pt = (TProfile*)f_TypeIV->Get("p_ptRatio_vs_pt_CaloScoutingHT250");
      label = TString::Format("Mean");
    }

    if(p_mJJRatio_vs_mJJ && p_ptRatio_vs_pt){
      std::cout<< "TProfiles exist"<< std::endl;
    }else{
      std::cout<< "TProfiles don't exist"<< std::endl;
      continue;
    }
    
    legend->AddEntry(p_mJJRatio_vs_mJJ, label, "LP");

    /*
    TGraphErrors *g_mJJ = new TGraphErrors(0);
    TGraphErrors *g_pt = new TGraphErrors(0);

    for (int i = 1; i != p_mJJRatio_vs_mJJ->GetNbinsX()+1; ++i) {                                                                                                    
      
      double BinContent = p_mJJRatio_vs_mJJ->GetBinContent(i);                                                                                                           
      double BinError = p_mJJRatio_vs_mJJ->GetBinError(i);
      double BinCenter = p_mJJRatio_vs_mJJ->GetBinCenter(i);
      std::cout<<"BinContent = "<< BinContent << std::endl;
      std::cout<<"BinCenter = "<< BinCenter << std::endl;
      
      int n = g_mJJ->GetN();                                                                                                                            
      g_mJJ->SetPoint(n, BinCenter, (BinContent -1.) *100.);                                                                          
      g_mJJ->SetPointError(n, 0, 100.*BinError );         
      // double NewBinContent = (BinContent -1.)*100. ;
      // std::cout<<"New BinContent = "<< NewBinContent << std::endl;
      // p_mJJRatio_vs_mJJ->SetBinContent(i, NewBinContent);                                                                                               
      // std::cout<<"New BinContent = "<< p_mJJRatio_vs_mJJ -> GetBinContent(i) << std::endl;
	
    }
    for (int i = 1; i != p_ptRatio_vs_pt->GetNbinsX()+1; ++i) {                                                                                                    
      
      double BinContent = p_ptRatio_vs_pt->GetBinContent(i);                                                                                                           
      p_ptRatio_vs_pt->SetBinContent(i, (BinContent -1)*100);                                                                                               
      
    }
    */

    c1->cd();
    //p_mJJRatio_vs_mJJ->SetContour(100);
    p_mJJRatio_vs_mJJ->GetYaxis()->SetRangeUser(0.9, 1.1);
    p_mJJRatio_vs_mJJ->GetXaxis()->SetRangeUser(450, 2100);
    p_mJJRatio_vs_mJJ->SetTitle(" ");
    p_mJJRatio_vs_mJJ->SetXTitle("mJJ [GeV] ");
    p_mJJRatio_vs_mJJ->SetYTitle("mJJ(HLT) / mJJ(Reco) ");
    p_mJJRatio_vs_mJJ->GetYaxis()->SetTitleOffset(1.4);
    p_mJJRatio_vs_mJJ->SetStats(0);
    p_mJJRatio_vs_mJJ->SetMarkerColor(ii+1);
    p_mJJRatio_vs_mJJ->SetLineColor(ii+1);
    if(ii == 0){
      p_mJJRatio_vs_mJJ ->Draw();
    }else{
      p_mJJRatio_vs_mJJ ->Draw("same");
    }    
    if(ii==3) legend->Draw();
    if(ClosureTest){
      c1 ->SaveAs("Plot/CaloJEC_mJJClosureTest_DifferentMethod.png");        
      c1 ->SaveAs("Plot/CaloJEC_mJJClosureTest_DifferentMethod.pdf");        
    }else{
      c1 ->SaveAs("Plot/CaloJEC_mJJOriginalBias_DifferentMethod.png");        
      c1 ->SaveAs("Plot/CaloJEC_mJJOriginalBias_DifferentMethod.pdf");        
  }
    
   
    c2->cd();
    // p_ptRatio_vs_pt->SetContour(100);
    p_ptRatio_vs_pt->GetYaxis()->SetRangeUser(0.9, 1.1);
    p_ptRatio_vs_pt->GetXaxis()->SetRangeUser(200, 1500);
    p_ptRatio_vs_pt->SetTitle(" ");
    p_ptRatio_vs_pt->SetXTitle("pT [GeV] ");
    p_ptRatio_vs_pt->SetYTitle("pT(HLT) / pT(Reco) ");
    p_ptRatio_vs_pt->GetYaxis()->SetTitleOffset(1.4);
    p_ptRatio_vs_pt ->SetStats(0);
    p_ptRatio_vs_pt->SetMarkerColor(ii+1);
    p_ptRatio_vs_pt->SetLineColor(ii+1);
    if(ii == 0){
      p_ptRatio_vs_pt ->Draw();
    }else{
      p_ptRatio_vs_pt ->Draw("same");
    }    
    if(ii==3) legend->Draw();
    if(ClosureTest){
      c2 ->SaveAs("Plot/CaloJEC_ptClosureTest_DifferentMethod.png");        
      c2 ->SaveAs("Plot/CaloJEC_ptClosureTest_DifferentMethod.pdf");        
    }else{
      c2 ->SaveAs("Plot/CaloJEC_ptOriginalBias_DifferentMethod.png");        
      c2 ->SaveAs("Plot/CaloJEC_ptOriginalBias_DifferentMethod.pdf");        
    }
  } // different method


  TH1D *h_mJJHLT;
  TH1D *h_mJJReco;
  
  h_mJJHLT = (TH1D*)f_TypeI->Get("h_mJJHLT_CaloScoutingHT250");
  h_mJJReco = (TH1D*)f_TypeI->Get("h_mJJReco_CaloScoutingHT250");

  if(h_mJJHLT) std::cout<<"mJJ HLT exist" << std::endl;
  if(h_mJJReco) std::cout<<"mJJ Reco exist" << std::endl;
  
  TLegend* legend2 = new TLegend(0.58, 0.68, 0.80, 0.90);                                                                                                                      
  legend2->SetTextFont(42);                                                                                                                                                    
  legend2->SetBorderSize(0);                                                                                                                                                   
  legend2->SetFillColor(kWhite);                                                                                                                                               
  legend2->SetFillStyle(0);                                                                                                                                                    
  legend2->SetTextSize( 0.036);
  legend2->SetTextSize( 0.036);
  legend2->AddEntry(h_mJJHLT, "HLT", "LP");
  legend2->AddEntry(h_mJJReco, "Reco", "LP");
  
  TCanvas *c3 = new TCanvas("c3","",800,600); 
  //p_mJJRatio_vs_mJJ->GetYaxis()->SetRangeUser(0.9, 1.1);
  h_mJJHLT->GetXaxis()->SetRangeUser(450, 2100);
  h_mJJHLT->SetTitle(" ");
  h_mJJHLT->SetXTitle("mJJ [GeV]");
  h_mJJHLT->SetYTitle("Events");
  h_mJJHLT->GetYaxis()->SetTitleOffset(1.4);
  h_mJJHLT->SetStats(0);
  h_mJJHLT->SetLineColor(kBlue);
  h_mJJReco->SetLineColor(kRed);  
  h_mJJHLT ->Draw();
  h_mJJReco ->Draw("same");
  legend2->Draw();
  if(ClosureTest){
    c3 ->SaveAs("Plot/CaloJEC_mJJClosureTest.png");        
    c3 ->SaveAs("Plot/CaloJEC_mJJClosureTest.pdf");        
  }else{
    c3 ->SaveAs("Plot/CaloJEC_mJJOriginalBias.png");        
    c3 ->SaveAs("Plot/CaloJEC_mJJOriginalBias.pdf");        
  }

  TH1D *h_mJJRatio = (TH1D*)h_mJJHLT->Clone("h_mJJRatio");
  h_mJJRatio->Divide(h_mJJReco);
  
  TCanvas *c4 = new TCanvas("c4","",800,600); 
  h_mJJRatio->GetXaxis()->SetRangeUser(450, 2100);
  h_mJJRatio->GetYaxis()->SetRangeUser(0.7, 1.3);
  h_mJJRatio->SetTitle(" ");
  h_mJJRatio->SetXTitle("mJJ [GeV]");
  h_mJJRatio->SetYTitle("HLT/Reco");
  h_mJJRatio->GetYaxis()->SetTitleOffset(1.4);
  h_mJJRatio->SetStats(0);
  // h_mJJRatio->SetLineColor(kBlack); 
  h_mJJRatio->SetMarkerStyle(20); 
  h_mJJRatio->Draw();
  if(ClosureTest){
    c4 ->SaveAs("Plot/CaloJEC_mJJRatioClosureTest.png");        
    c4 ->SaveAs("Plot/CaloJEC_mJJRatioClosureTest.pdf");        
  }else{
    c4 ->SaveAs("Plot/CaloJEC_mJJRatioOriginalBias.png");        
    c4 ->SaveAs("Plot/CaloJEC_mJJRatioOriginalBias.pdf");        
  }
 


}
