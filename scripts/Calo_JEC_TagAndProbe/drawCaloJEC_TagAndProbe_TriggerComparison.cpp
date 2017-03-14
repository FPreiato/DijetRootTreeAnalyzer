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

int main(int argc, char* argv[]) {

  std::string outputDir = "Plot";                 
  mkdir(outputDir.c_str(), 0777); 

  TString dataFileName_ZeroBias;
  dataFileName_ZeroBias = TString::Format("CaloJEC_TagAndProbeMethod_ZeroBias.root");
  TFile* dataFile_ZeroBias = TFile::Open(dataFileName_ZeroBias);
  if (dataFile_ZeroBias) {
    std::cout << "Opened data file '" << dataFileName_ZeroBias << "'." << std::endl;
  }

  TString dataFileName_DoubleMu;
  dataFileName_DoubleMu = TString::Format("CaloJEC_TagAndProbeMethod_DoubleMu.root");
  TFile* dataFile_DoubleMu = TFile::Open(dataFileName_DoubleMu);
  if (dataFile_DoubleMu) {
    std::cout << "Opened data file '" << dataFileName_DoubleMu << "'." << std::endl;
  }

  TString dataFileName_CaloJet40;
  dataFileName_CaloJet40 = TString::Format("CaloJEC_TagAndProbeMethod_CaloJet40.root");
  TFile* dataFile_CaloJet40 = TFile::Open(dataFileName_CaloJet40);
  if (dataFile_CaloJet40) {
    std::cout << "Opened data file '" << dataFileName_CaloJet40 << "'." << std::endl;
  }

  TString dataFileName_L1HTT150;
  dataFileName_L1HTT150 = TString::Format("CaloJEC_TagAndProbeMethod_L1HTT150.root");
  TFile* dataFile_L1HTT150 = TFile::Open(dataFileName_L1HTT150);
  if (dataFile_L1HTT150) {
    std::cout << "Opened data file '" << dataFileName_L1HTT150 << "'." << std::endl;
  }

  TString dataFileName_CaloScoutingHT250;
  dataFileName_CaloScoutingHT250 = TString::Format("CaloJEC_TagAndProbeMethod_CaloScoutingHT250.root");
  TFile* dataFile_CaloScoutingHT250 = TFile::Open(dataFileName_CaloScoutingHT250);
  if (dataFile_CaloScoutingHT250) {
    std::cout << "Opened data file '" << dataFileName_CaloScoutingHT250 << "'." << std::endl;
  }

  gErrorIgnoreLevel = kWarning;

  //  TProfile *h_Mean1_ZeroBias = (TProfile*)dataFile_ZeroBias->Get("RatioCaloTag_vs_Tag_ZeroBias");
  //  TProfile *h_Mean2_ZeroBias = (TProfile*)dataFile_ZeroBias->Get("RatioPFTag_vs_Tag_ZeroBias");
  TH1D *ph_Mean1_ZeroBias = (TH1D*)dataFile_ZeroBias->Get("ph_Mean1_ZeroBias");
  TH1D *ph_Mean2_ZeroBias = (TH1D*)dataFile_ZeroBias->Get("ph_Mean2_ZeroBias");
  TH1D *h_Ratio_1_2_ZeroBias = (TH1D*)dataFile_ZeroBias->Get("h_Ratio_1_2_ZeroBias");
  TProfile *h_Mean3_ZeroBias = (TProfile*)dataFile_ZeroBias->Get("RatioProbe_vs_Tag_ZeroBias");
  TProfile *h_Mean4_ZeroBias = (TProfile*)dataFile_ZeroBias->Get("CaloProbe_vs_Tag_ZeroBias");
  TGraphErrors *MoneyPlot_ZeroBias = (TGraphErrors*)dataFile_ZeroBias->Get("MoneyPlot_ZeroBias");

  //  TProfile *h_Mean1_DoubleMu = (TProfile*)dataFile_DoubleMu->Get("RatioCaloTag_vs_Tag_DoubleMu");
  //  TProfile *h_Mean2_DoubleMu = (TProfile*)dataFile_DoubleMu->Get("RatioPFTag_vs_Tag_DoubleMu");
  TH1D *ph_Mean1_DoubleMu = (TH1D*)dataFile_DoubleMu->Get("ph_Mean1_DoubleMu");
  TH1D *ph_Mean2_DoubleMu = (TH1D*)dataFile_DoubleMu->Get("ph_Mean2_DoubleMu");
  TH1D *h_Ratio_1_2_DoubleMu = (TH1D*)dataFile_DoubleMu->Get("h_Ratio_1_2_DoubleMu");
  TProfile *h_Mean3_DoubleMu = (TProfile*)dataFile_DoubleMu->Get("RatioProbe_vs_Tag_DoubleMu");
  TProfile *h_Mean4_DoubleMu = (TProfile*)dataFile_DoubleMu->Get("CaloProbe_vs_Tag_DoubleMu");
  TGraphErrors *MoneyPlot_DoubleMu = (TGraphErrors*)dataFile_DoubleMu->Get("MoneyPlot_DoubleMu");

  //  TProfile *h_Mean1_CaloJet40 = (TProfile*)dataFile_CaloJet40->Get("RatioCaloTag_vs_Tag_CaloJet40");
  //  TProfile *h_Mean2_CaloJet40 = (TProfile*)dataFile_CaloJet40->Get("RatioPFTag_vs_Tag_CaloJet40");
  TH1D *ph_Mean1_CaloJet40 = (TH1D*)dataFile_CaloJet40->Get("ph_Mean1_CaloJet40");
  TH1D *ph_Mean2_CaloJet40 = (TH1D*)dataFile_CaloJet40->Get("ph_Mean2_CaloJet40");
  TH1D *h_Ratio_1_2_CaloJet40 = (TH1D*)dataFile_CaloJet40->Get("h_Ratio_1_2_CaloJet40");
  TProfile *h_Mean3_CaloJet40 = (TProfile*)dataFile_CaloJet40->Get("RatioProbe_vs_Tag_CaloJet40");
  TProfile *h_Mean4_CaloJet40 = (TProfile*)dataFile_CaloJet40->Get("CaloProbe_vs_Tag_CaloJet40");
  TGraphErrors *MoneyPlot_CaloJet40 = (TGraphErrors*)dataFile_CaloJet40->Get("MoneyPlot_CaloJet40");

  //  TProfile *h_Mean1_L1HTT150 = (TProfile*)dataFile_L1HTT150->Get("RatioCaloTag_vs_Tag_L1HTT150");
  //  TProfile *h_Mean2_L1HTT150 = (TProfile*)dataFile_L1HTT150->Get("RatioPFTag_vs_Tag_L1HTT150");
  TH1D *ph_Mean1_L1HTT150 = (TH1D*)dataFile_L1HTT150->Get("ph_Mean1_L1HTT150");
  TH1D *ph_Mean2_L1HTT150 = (TH1D*)dataFile_L1HTT150->Get("ph_Mean2_L1HTT150");
  TH1D *h_Ratio_1_2_L1HTT150 = (TH1D*)dataFile_L1HTT150->Get("h_Ratio_1_2_L1HTT150");
  TProfile *h_Mean3_L1HTT150 = (TProfile*)dataFile_L1HTT150->Get("RatioProbe_vs_Tag_L1HTT150");
  TProfile *h_Mean4_L1HTT150 = (TProfile*)dataFile_L1HTT150->Get("CaloProbe_vs_Tag_L1HTT150");
  TGraphErrors *MoneyPlot_L1HTT150 = (TGraphErrors*)dataFile_L1HTT150->Get("MoneyPlot_L1HTT150");

  //  TProfile *h_Mean1_CaloScoutingHT250 = (TProfile*)dataFile_CaloScoutingHT250->Get("RatioCaloTag_vs_Tag_CaloScoutingHT250");
  //  TProfile *h_Mean2_CaloScoutingHT250 = (TProfile*)dataFile_CaloScoutingHT250->Get("RatioPFTag_vs_Tag_CaloScoutingHT250");
  TH1D *ph_Mean1_CaloScoutingHT250 = (TH1D*)dataFile_CaloScoutingHT250->Get("ph_Mean1_CaloScoutingHT250");
  TH1D *ph_Mean2_CaloScoutingHT250 = (TH1D*)dataFile_CaloScoutingHT250->Get("ph_Mean2_CaloScoutingHT250");
  TH1D *h_Ratio_1_2_CaloScoutingHT250 = (TH1D*)dataFile_CaloScoutingHT250->Get("h_Ratio_1_2_CaloScoutingHT250");
  TProfile *h_Mean3_CaloScoutingHT250 = (TProfile*)dataFile_CaloScoutingHT250->Get("RatioProbe_vs_Tag_CaloScoutingHT250");
  TProfile *h_Mean4_CaloScoutingHT250 = (TProfile*)dataFile_CaloScoutingHT250->Get("CaloProbe_vs_Tag_CaloScoutingHT250");
  TGraphErrors *MoneyPlot_CaloScoutingHT250 = (TGraphErrors*)dataFile_CaloScoutingHT250->Get("MoneyPlot_CaloScoutingHT250");

  TLegend* legend = new TLegend(0.58, 0.68, 0.80, 0.90);                                                                                                                  
  legend->SetTextFont(42);                                                                                                                                                
  legend->SetBorderSize(0);                                                                                                                                               
  legend->SetFillColor(kWhite);                                                                                                                                           
  legend->SetFillStyle(0);                                                                                                                                                
  legend->SetTextSize( 0.036);                                                                                                                                            
  legend->AddEntry(ph_Mean1_ZeroBias, "ZeroBias", "LP"); 
  legend->AddEntry(ph_Mean1_DoubleMu, "DoubleMu", "LP"); 
  legend->AddEntry(ph_Mean1_CaloJet40, "CaloJet40", "LP"); 
  legend->AddEntry(ph_Mean1_L1HTT150, "L1HT", "LP");                                                                                                                                      
  legend->AddEntry(ph_Mean1_CaloScoutingHT250, "HT250", "LP"); 
  legend->Draw(); 

  TCanvas *cMean1 = new TCanvas("cMean1","", 800, 800);
  ph_Mean1_ZeroBias    -> SetStats(0); 
  ph_Mean1_DoubleMu    -> SetStats(0); 
  ph_Mean1_CaloJet40    -> SetStats(0); 
  ph_Mean1_L1HTT150   -> SetStats(0); 
  ph_Mean1_CaloScoutingHT250   -> SetStats(0); 

  ph_Mean1_CaloScoutingHT250 -> SetTitle("");
  ph_Mean1_CaloScoutingHT250 -> SetXTitle("p_{T}(RECO,tag)");
  ph_Mean1_CaloScoutingHT250 -> SetYTitle("p_{T}(HLT,probe)/p_{T}(RECO,tag)");
  ph_Mean1_CaloScoutingHT250 -> GetXaxis()->SetRangeUser(0,500);
  ph_Mean1_CaloScoutingHT250 -> GetYaxis()->SetTitleOffset(1.4);           
  ph_Mean1_CaloScoutingHT250 -> SetMarkerStyle(20);
  ph_Mean1_CaloScoutingHT250 -> Draw();
  ph_Mean1_L1HTT150->SetMarkerStyle(20);
  ph_Mean1_L1HTT150->SetMarkerColor(kRed);
  ph_Mean1_L1HTT150->SetLineColor(kRed);
  ph_Mean1_CaloJet40->SetMarkerStyle(20);
  ph_Mean1_CaloJet40->SetMarkerColor(kBlue);
  ph_Mean1_CaloJet40->SetLineColor(kBlue);
  ph_Mean1_DoubleMu->SetMarkerStyle(20);
  ph_Mean1_DoubleMu->SetMarkerColor(kBlue - 6);
  ph_Mean1_DoubleMu->SetLineColor(kBlue - 6);
  ph_Mean1_ZeroBias->SetMarkerStyle(20);
  ph_Mean1_ZeroBias->SetMarkerColor(kGreen);
  ph_Mean1_ZeroBias->SetLineColor(kGreen);
  ph_Mean1_L1HTT150->Draw("same");
  ph_Mean1_CaloJet40->Draw("same");
  ph_Mean1_DoubleMu->Draw("same");
  ph_Mean1_ZeroBias->Draw("same");
  legend->Draw();
  cMean1->SaveAs("Plot/Var1_ProjectMean1_TriggerComparison.png");         
  cMean1->SaveAs("Plot/Var1_ProjectMean1_TriggerComparison.pdf");         

  TCanvas *cMean2 = new TCanvas("cMean2","", 800, 800);
  ph_Mean2_CaloJet40    -> SetStats(0); 
  ph_Mean2_L1HTT150   -> SetStats(0); 
  ph_Mean2_CaloScoutingHT250   -> SetStats(0); 
  ph_Mean2_CaloScoutingHT250    -> GetYaxis()->SetTitleOffset(1.4);           
  ph_Mean2_CaloScoutingHT250 -> SetTitle("");
  ph_Mean2_CaloScoutingHT250->SetXTitle("p_{T}(RECO,tag)");
  ph_Mean2_CaloScoutingHT250->SetYTitle("p_{T}(RECO,probe)/p_{T}(RECO,tag)");
  ph_Mean2_CaloScoutingHT250->GetXaxis()->SetRangeUser(0,500);
  ph_Mean2_CaloScoutingHT250->SetMarkerStyle(20);
  ph_Mean2_CaloScoutingHT250 -> Draw();
  ph_Mean2_L1HTT150->SetMarkerStyle(20);
  ph_Mean2_L1HTT150->SetMarkerColor(kRed);
  ph_Mean2_L1HTT150->SetLineColor(kRed);
  ph_Mean2_CaloJet40->SetMarkerStyle(20);
  ph_Mean2_CaloJet40->SetMarkerColor(kBlue);
  ph_Mean2_CaloJet40->SetLineColor(kBlue);
  ph_Mean2_DoubleMu->SetMarkerStyle(20);
  ph_Mean2_DoubleMu->SetMarkerColor(kBlue - 6);
  ph_Mean2_DoubleMu->SetLineColor(kBlue - 6);
  ph_Mean2_ZeroBias->SetMarkerStyle(20);
  ph_Mean2_ZeroBias->SetMarkerColor(kGreen);
  ph_Mean2_ZeroBias->SetLineColor(kGreen);
  ph_Mean2_L1HTT150->Draw("same");
  ph_Mean2_CaloJet40->Draw("same");
  ph_Mean2_DoubleMu->Draw("same");
  ph_Mean2_ZeroBias->Draw("same");
  legend->Draw();
  cMean2 -> SaveAs("Plot/Var2_ProjectMean2_TriggerComparison.png");         
  cMean2 -> SaveAs("Plot/Var2_ProjectMean2_TriggerComparison.pdf");         

  TCanvas *canvas = new TCanvas("canvas","",800,800); 
  h_Ratio_1_2_CaloScoutingHT250    -> SetTitle(" ");              
  h_Ratio_1_2_CaloScoutingHT250    -> SetStats(0); 
  h_Ratio_1_2_CaloScoutingHT250    -> SetMarkerStyle(20);         
  h_Ratio_1_2_CaloScoutingHT250    -> SetXTitle("p_{T}(RECO,tag)");          
  h_Ratio_1_2_CaloScoutingHT250    -> SetYTitle("<p_{T}(HLT,probe)>/<p_{T}(RECO,probe)>");          
  h_Ratio_1_2_CaloScoutingHT250    -> GetYaxis()->SetTitleOffset(1.5);           
  h_Ratio_1_2_CaloScoutingHT250    -> GetYaxis()->SetRangeUser(0.95, 1.08);         
  h_Ratio_1_2_CaloScoutingHT250    -> GetXaxis()->SetRangeUser(0, 2000);   
  h_Ratio_1_2_CaloScoutingHT250    -> Draw();      
  h_Ratio_1_2_L1HTT150  -> SetMarkerStyle(20);
  h_Ratio_1_2_L1HTT150->SetMarkerColor(kRed);
  h_Ratio_1_2_L1HTT150->SetLineColor(kRed);
  h_Ratio_1_2_CaloJet40  -> SetMarkerStyle(20);         
  h_Ratio_1_2_CaloJet40->SetMarkerColor(kBlue);
  h_Ratio_1_2_CaloJet40->SetLineColor(kBlue);
  h_Ratio_1_2_DoubleMu->SetMarkerStyle(20);
  h_Ratio_1_2_DoubleMu->SetMarkerColor(kBlue - 6);
  h_Ratio_1_2_DoubleMu->SetLineColor(kBlue - 6);
  h_Ratio_1_2_ZeroBias->SetMarkerStyle(20);
  h_Ratio_1_2_ZeroBias->SetMarkerColor(kGreen);
  h_Ratio_1_2_ZeroBias->SetLineColor(kGreen);
  h_Ratio_1_2_L1HTT150->Draw("same");
  h_Ratio_1_2_CaloJet40->Draw("same");
  h_Ratio_1_2_DoubleMu->Draw("same");
  h_Ratio_1_2_ZeroBias->Draw("same");
  legend->Draw();
  canvas->SetLeftMargin(0.13);         
  canvas ->SaveAs("Plot/RatioVar12_TriggerComparison.png");        
  canvas ->SaveAs("Plot/RatioVar12_TriggerComparison.pdf");        

  TCanvas *cMean3 = new TCanvas("cMean3","",800,800); 
  h_Mean3_CaloScoutingHT250    -> SetTitle(" ");              
  h_Mean3_CaloScoutingHT250    -> SetStats(0); 
  h_Mean3_CaloScoutingHT250    -> SetMarkerStyle(20);         
  h_Mean3_CaloScoutingHT250    -> SetXTitle("p_{T}(RECO,tag)");          
  h_Mean3_CaloScoutingHT250    -> SetYTitle("p_{T}(HLT,probe)/p_{T}(RECO,probe)");          
  h_Mean3_CaloScoutingHT250    -> GetYaxis()->SetTitleOffset(1.5);           
  h_Mean3_CaloScoutingHT250    -> GetYaxis()->SetRangeUser(0.95, 1.08);         
  h_Mean3_CaloScoutingHT250    -> GetXaxis()->SetRangeUser(0, 1000);   
  h_Mean3_CaloScoutingHT250    -> Draw();     
  h_Mean3_L1HTT150->SetMarkerStyle(20);
  h_Mean3_L1HTT150->SetMarkerColor(kRed);
  h_Mean3_L1HTT150->SetLineColor(kRed);
  h_Mean3_CaloJet40->SetMarkerStyle(20);
  h_Mean3_CaloJet40->SetLineColor(kBlue); 
  h_Mean3_CaloJet40->SetMarkerColor(kBlue);
  h_Mean3_DoubleMu->SetMarkerStyle(20);
  h_Mean3_DoubleMu->SetMarkerColor(kBlue - 6);
  h_Mean3_DoubleMu->SetLineColor(kBlue - 6);
  h_Mean3_ZeroBias->SetMarkerStyle(20);
  h_Mean3_ZeroBias->SetMarkerColor(kGreen);
  h_Mean3_ZeroBias->SetLineColor(kGreen);
  h_Mean3_L1HTT150->Draw("same");
  h_Mean3_CaloJet40->Draw("same");
  h_Mean3_DoubleMu->Draw("same");
  h_Mean3_ZeroBias->Draw("same");
  legend->Draw();
  cMean3->SetLeftMargin(0.13);         
  cMean3 ->SaveAs("Plot/Var3_RatioProbe_vs_Tag_TriggerComparison.png");        
  cMean3 ->SaveAs("Plot/Var3_RatioProbe_vs_Tag_TriggerComparison.pdf");        

  TCanvas *cMean4 = new TCanvas("cMean4","",800,800); 
  h_Mean4_CaloScoutingHT250    -> SetTitle(" ");              
  h_Mean4_CaloScoutingHT250    -> SetStats(0); 
  h_Mean4_CaloScoutingHT250    -> SetMarkerStyle(20);         
  h_Mean4_CaloScoutingHT250    -> SetXTitle("p_{T}(RECO,tag)");          
  h_Mean4_CaloScoutingHT250    -> SetYTitle("p_{T}(HLT,probe)");          
  h_Mean4_CaloScoutingHT250    -> GetYaxis()->SetTitleOffset(1.5);           
  //  h_Mean4_CaloScoutingHT250    -> GetYaxis()->SetRangeUser(0.95, 1.08);         
  h_Mean4_CaloScoutingHT250    -> GetXaxis()->SetRangeUser(0, 3000);   
  h_Mean4_CaloScoutingHT250    -> Draw();     
  h_Mean4_L1HTT150->SetMarkerStyle(20);
  h_Mean4_L1HTT150->SetLineColor(kRed);
  h_Mean4_L1HTT150->SetMarkerColor(kRed);
  h_Mean4_CaloJet40->SetMarkerStyle(20);
  h_Mean4_CaloJet40->SetLineColor(kBlue); 
  h_Mean4_CaloJet40->SetMarkerColor(kBlue);
  h_Mean4_DoubleMu->SetMarkerStyle(20);
  h_Mean4_DoubleMu->SetMarkerColor(kBlue - 6);
  h_Mean4_DoubleMu->SetLineColor(kBlue - 6);
  h_Mean4_ZeroBias->SetMarkerStyle(20);
  h_Mean4_ZeroBias->SetMarkerColor(kGreen);
  h_Mean4_ZeroBias->SetLineColor(kGreen);
  h_Mean4_L1HTT150->Draw("same");
  h_Mean4_CaloJet40->Draw("same");
  h_Mean4_DoubleMu->Draw("same");
  h_Mean4_ZeroBias->Draw("same");
  legend->Draw();
  cMean4->SetLeftMargin(0.13);         
  cMean4 ->SaveAs("Plot/Var4_CaloProbe_vs_Tag_TriggerComparison.png");        
  cMean4 ->SaveAs("Plot/Var4_CaloProbe_vs_Tag_TriggerComparison.pdf");        

  TCanvas *canvas2 = new TCanvas("canvas2","",800,800); 
  MoneyPlot_CaloScoutingHT250    -> SetTitle(" ");              
  //  MoneyPlot_CaloScoutingHT250    -> SetStats(0); 
  MoneyPlot_CaloScoutingHT250    -> SetMarkerStyle(20);         
  MoneyPlot_CaloScoutingHT250    -> GetXaxis()-> SetTitle("<p_{T}(HLT,probe)>");          
  MoneyPlot_CaloScoutingHT250    -> GetYaxis()-> SetTitle("<p_{T}(HLT,probe)>/<p_{T}(RECO,probe)>");  
  MoneyPlot_CaloScoutingHT250    -> GetYaxis()->SetTitleOffset(1.7);           
  MoneyPlot_CaloScoutingHT250    -> GetXaxis()->SetRangeUser(0, 2000);      
  MoneyPlot_CaloScoutingHT250    -> GetYaxis()->SetRangeUser(0.95, 1.08);       
  MoneyPlot_CaloScoutingHT250    -> Draw("ZAP");      
  MoneyPlot_L1HTT150    -> SetMarkerStyle(20);         
  MoneyPlot_L1HTT150->SetMarkerColor(kRed);
  MoneyPlot_L1HTT150->SetLineColor(kRed);
  MoneyPlot_CaloJet40   -> SetMarkerStyle(20);         
  MoneyPlot_CaloJet40->SetLineColor(kBlue);
  MoneyPlot_CaloJet40->SetMarkerColor(kBlue);
  MoneyPlot_DoubleMu->SetMarkerStyle(20);
  MoneyPlot_DoubleMu->SetMarkerColor(kBlue - 6);
  MoneyPlot_DoubleMu->SetLineColor(kBlue - 6);
  MoneyPlot_ZeroBias->SetMarkerStyle(20);
  MoneyPlot_ZeroBias->SetMarkerColor(kGreen);
  MoneyPlot_ZeroBias->SetLineColor(kGreen);
  MoneyPlot_L1HTT150->Draw("Psame");
  MoneyPlot_CaloJet40->Draw("Psame");
  MoneyPlot_DoubleMu->Draw("Psame");
  MoneyPlot_ZeroBias->Draw("Psame");
  legend->Draw();
  canvas2->SetLeftMargin(0.13);         
  canvas2 ->SaveAs("Plot/Final_TriggerComparison.png");        
  canvas2 ->SaveAs("Plot/Final_TriggerComparison.pdf");        


}
