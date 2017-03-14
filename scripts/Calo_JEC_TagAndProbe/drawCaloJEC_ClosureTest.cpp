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

  TFile *f;
  if(ClosureTest){
    f = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_ClosureTest_20160722_145815/rootFile_ClosureTest.root","READ");
  }else{
    f = new TFile("../../output/CaloParkingScouting_7600pb/reducedFile_OriginalBias_NotCorrected_20160722_165712/rootFile_OriginalBias_NotCorrected.root","READ");
  }
  

 if (f) {
   std::cout << "Opened data file" << std::endl;
 }
 
 gErrorIgnoreLevel = kWarning;
 
 TProfile *p_mJJClosureTest = (TProfile*)f->Get("p_mJJRatio_vs_mJJ_CaloScoutingHT250");
 TH2D *h_mJJClosureTest = (TH2D*)f->Get("h_mJJRatio_vs_mJJ_CaloScoutingHT250");
 
 TProfile *p_ptClosureTest = (TProfile*)f->Get("p_ptRatio_vs_pt_CaloScoutingHT250");
 TH2D *h_ptClosureTest = (TH2D*)f->Get("h_ptRatio_vs_pt_CaloScoutingHT250");
 
 TCanvas *c1 = new TCanvas("c1","",800,600); 
  gPad->SetLogz();
  gStyle->SetPalette(55);
  h_mJJClosureTest->SetContour(100);
  h_mJJClosureTest->GetYaxis()->SetRangeUser(0.7, 1.3);
  h_mJJClosureTest->SetTitle(" ");
  h_mJJClosureTest->SetXTitle("mJJ [GeV] ");
  h_mJJClosureTest->SetYTitle("mJJ(HLT) / mJJ(Reco) ");
  h_mJJClosureTest->SetStats(0);
  h_mJJClosureTest->Draw("colz");
  p_mJJClosureTest ->Draw("same");
  if(ClosureTest){
    c1 ->SaveAs("Plot/CaloJEC_mJJClosureTest.png");        
    c1 ->SaveAs("Plot/CaloJEC_mJJClosureTest.pdf");        
  }else{
    c1 ->SaveAs("Plot/CaloJEC_mJJOriginalBias.png");        
    c1 ->SaveAs("Plot/CaloJEC_mJJOriginalBias.pdf");        
  }
  
  TCanvas *c2 = new TCanvas("c2","",800,600); 
  gPad->SetLogz();
  gStyle->SetPalette(55);
  h_ptClosureTest->SetContour(100);
  h_ptClosureTest->GetYaxis()->SetRangeUser(0.7, 1.3);
  h_ptClosureTest->GetXaxis()->SetRangeUser(200, 1500);
  h_ptClosureTest->SetTitle(" ");
  h_ptClosureTest->SetXTitle("pT [GeV] ");
  h_ptClosureTest->SetYTitle("pT(HLT) / pT(Reco) ");
  h_ptClosureTest ->SetStats(0);
  h_ptClosureTest->Draw("colz");
  p_ptClosureTest->Draw("same");
  if(ClosureTest){
    c2 ->SaveAs("Plot/CaloJEC_ptClosureTest.png");        
    c2 ->SaveAs("Plot/CaloJEC_ptClosureTest.pdf");        
  }else{
    c2 ->SaveAs("Plot/CaloJEC_ptOriginalBias.png");        
    c2 ->SaveAs("Plot/CaloJEC_ptOriginalBias.pdf");        
  }
  
}
