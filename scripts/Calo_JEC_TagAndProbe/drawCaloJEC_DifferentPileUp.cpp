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

  //TFile *f_TypeI;
  //TFile *f_TypeII;

  //TFile *f_TypeIV;

  TFile *f_TypeIII_LowPU;
  TFile *f_TypeIII_MediumPU;
  TFile *f_TypeIII_HighPU;

  if(ClosureTest){
    f_TypeIII_LowPU = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_vs_nVtx_Low_TypeIII_20160727_170712/rootFile_OriginalBias_TypeIII_LowPU.root ","READ");
    f_TypeIII_MediumPU = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_vs_nVtx_Medium_TypeIII_20160727_171912/rootFile_OriginalBias_TypeIII_MediumPU.root ","READ");
    f_TypeIII_HighPU = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_vs_nVtx_High_TypeIII_20160727_172839/rootFile_OriginalBias_TypeIII_HighPU.root ","READ");
  }else{
    f_TypeIII_LowPU = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_vs_nVtx_Low_TypeIII_20160727_170712/rootFile_OriginalBias_TypeIII_LowPU.root ","READ");
    f_TypeIII_MediumPU = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_vs_nVtx_Medium_TypeIII_20160727_171912/rootFile_OriginalBias_TypeIII_MediumPU.root ","READ");
    f_TypeIII_HighPU = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_vs_nVtx_High_TypeIII_20160727_172839/rootFile_OriginalBias_TypeIII_HighPU.root ","READ");

  }
    
  if (f_TypeIII_LowPU) {
    std::cout << "Opened data file 'TypeIII LowPU' " << std::endl;
  }
  if (f_TypeIII_MediumPU) {
    std::cout << "Opened data file 'TypeIII MediumPU' " << std::endl;
  }
  if (f_TypeIII_HighPU) {
    std::cout << "Opened data file 'TypeIII HighPU' " << std::endl;
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
  //legend->SetHeader("On X-axis");
  TString label;   
    
  for(int ii = 0 ; ii < 3 ; ii++ ){
    
    std::cout<< "ii ="<< ii <<std::endl;
    
    if(ii == 0){     
      p_mJJRatio_vs_mJJ = (TProfile*)f_TypeIII_LowPU->Get("p_mJJRatio_vs_mJJ_CaloScoutingHT250");
      p_ptRatio_vs_pt = (TProfile*)f_TypeIII_LowPU->Get("p_ptRatio_vs_pt_CaloScoutingHT250");
      label = TString::Format("Low PU");
    }else if(ii == 1){
      p_mJJRatio_vs_mJJ = (TProfile*)f_TypeIII_MediumPU->Get("p_mJJRatio_vs_mJJ_CaloScoutingHT250");
      p_ptRatio_vs_pt = (TProfile*)f_TypeIII_MediumPU->Get("p_ptRatio_vs_pt_CaloScoutingHT250");
      label = TString::Format("Medium PU");
    }else if(ii == 2){
      p_mJJRatio_vs_mJJ = (TProfile*)f_TypeIII_HighPU->Get("p_mJJRatio_vs_mJJ_CaloScoutingHT250");
      p_ptRatio_vs_pt = (TProfile*)f_TypeIII_HighPU->Get("p_ptRatio_vs_pt_CaloScoutingHT250");
      label = TString::Format("High PU");
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
    if(ii ==2) legend->Draw();
    if(ClosureTest){
      c1 ->SaveAs("Plot/CaloJEC_mJJClosureTest_DifferentPU.png");        
      c1 ->SaveAs("Plot/CaloJEC_mJJClosureTest_DifferentPU.pdf");        
    }else{
      c1 ->SaveAs("Plot/CaloJEC_mJJOriginalBias_DifferentPU.png");        
      c1 ->SaveAs("Plot/CaloJEC_mJJOriginalBias_DifferentPU.pdf");        
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
    if(ii==2) legend->Draw();
    if(ClosureTest){
      c2 ->SaveAs("Plot/CaloJEC_ptClosureTest_DifferentPU.png");        
      c2 ->SaveAs("Plot/CaloJEC_ptClosureTest_DifferentPU.pdf");        
    }else{
      c2 ->SaveAs("Plot/CaloJEC_ptOriginalBias_DifferentPU.png");        
      c2 ->SaveAs("Plot/CaloJEC_ptOriginalBias_DifferentPU.pdf");        
    }
  } // different method



}
