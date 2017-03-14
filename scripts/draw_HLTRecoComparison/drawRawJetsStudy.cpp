#include <stdlib.h>
#include <sys/stat.h>  
#include <time.h>

#include "TParameter.h"
#include "TPaveText.h"
#include "TError.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TAxis.h"
#include "drawBase.h"
#include "ptBinning.h"
#include "mJJBinning.h"
#include "etaBinning.h"

#include <TColor.h>

int main(int argc, char* argv[]) {

  if (argc != 2 && argc != 3) {
    std::cout << "USAGE: ./drawPhotonJet [file.root]" << std::endl;
    exit(23);
  }

  // rootFile_JEC_HLT_v7_RecoLowerCuts10GeV_RawJets_DoubleMu_HT450.root

  std::string outputDir = "Plot";                 
  mkdir(outputDir.c_str(), 0777); 

  std::string data1_dataset(argv[1]);

  TString dataFileName1;
  dataFileName1 = TString::Format("%s", data1_dataset.c_str() );

  TFile* dataFile1 = TFile::Open(dataFileName1);

  if (dataFile1) {
    std::cout << "Opened data file '" << dataFileName1 << "'." << std::endl;
  }

  gErrorIgnoreLevel = kWarning;

  bool colz = true;
  bool log= true;
 
  DrawTH1(dataFile1, "AK4_pTBias", "pT Bias", "Events", false, -0.5, 0.5);
  DrawTH1(dataFile1, "AK4_CHFBias", "CHF Bias", "Events", false, -0.5, 0.5);
  DrawTH1(dataFile1, "AK4_NHFBias", "NHF Bias", "Events", false, -0.5, 0.5);
  DrawTH1(dataFile1, "AK4_CEFBias", "CEF Bias", "Events", false, -0.5, 0.5);
  DrawTH1(dataFile1, "AK4_NEFBias", "NEF Bias", "Events", false, -0.5, 0.5);
  DrawTH1(dataFile1, "AK4_MuFBias", "MuF Bias", "Events", false, -0.5, 0.5);
  
  EtaBinning mEtaBinning;
  size_t etaBinningSize = mEtaBinning.size();
  PtBinning mPtBinning;
  size_t pTBinningSize = mPtBinning.size();
  
  // Bias vs pT bins
  for (size_t ii = 0; ii < etaBinningSize; ii++) {
    for (size_t jj = 0; jj < pTBinningSize; jj++) {
      
      if(jj > 8) continue;	
      
      std::string AK4_etaName = mEtaBinning.getBinName( ii );
      std::pair<float, float> AK4_ptBins = mPtBinning.getBinValue( jj );
      std::string AK4_Bin = TString::Format("%s_pT_%i_%i", AK4_etaName.c_str(), (int) AK4_ptBins.first, (int) AK4_ptBins.second ).Data(); 
      
      DrawTH1(dataFile1, Form("AK4_pTBias_%s", AK4_Bin.c_str() ), "pT Bias", "Events", false, -0.5, 0.5);
      DrawTH1(dataFile1, Form("AK4_CHFBias_%s", AK4_Bin.c_str() ), "CHF Bias", "Events", false, -0.5, 0.5);
      DrawTH1(dataFile1, Form("AK4_NHFBias_%s", AK4_Bin.c_str() ), "NHF Bias", "Events", false, -0.5, 0.5);
      DrawTH1(dataFile1, Form("AK4_CEFBias_%s", AK4_Bin.c_str() ), "CEF Bias", "Events", false, -0.5, 0.5);
      DrawTH1(dataFile1, Form("AK4_NEFBias_%s", AK4_Bin.c_str() ), "NEF Bias", "Events", false, -0.5, 0.5);
      DrawTH1(dataFile1, Form("AK4_MuFBias_%s", AK4_Bin.c_str() ), "MuF Bias", "Events", false, -0.5, 0.5);
      
    }
  }
  
  // Bias vs Eta
  DrawTProfile(dataFile1, "AK4_pTBias_vs_Eta",  "#eta",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
  DrawTProfile(dataFile1, "AK4_pTBias_vs_Pt",  "pT [GeV]",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
  //  DrawCompareProfile(dataFile1, "AK4_pT_vs_Eta",  "#eta",  "pT [GeV]", false, false, -2.5, 2.5);
  // Bias vs energy fraction
  DrawTProfile(dataFile1, "AK4_pTBias_vs_CHF",  "CHF",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_CHF_vs_Eta_",  "#eta",  "CHF", false, false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_CHF_vs_Pt_",  "pT [GeV]",  "CHF", false, false, -2.5, 2.5);
  DrawTProfile(dataFile1, "AK4_pTBias_vs_NHF",  "NHF",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_NHF_vs_Eta_",  "#eta",  "NHF", false, false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_NHF_vs_Pt_",  "pT [GeV]",  "NHF", false, false, -2.5, 2.5);
  DrawTProfile(dataFile1, "AK4_pTBias_vs_CEF",  "CEF",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_CEF_vs_Eta_",  "#eta",  "CEF", false, false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_CEF_vs_Pt_",  "pT [GeV]",  "CEF", false, false, -2.5, 2.5);
  DrawTProfile(dataFile1, "AK4_pTBias_vs_NEF",  "NEF",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_NEF_vs_Eta_",  "#eta",  "NEF", false, false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_NEF_vs_Pt_",  "pT [GeV]",  "NEF", false, false, -2.5, 2.5);
  DrawTProfile(dataFile1, "AK4_pTBias_vs_MuF",  "MuF",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_MuF_vs_Eta_",  "#eta",  "MuF", false, false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_MuF_vs_Pt_",  "pT [GeV]",  "MuF", false, false, -2.5, 2.5);

  // variable vs eta in pt bins
  for (size_t jj = 0; jj < pTBinningSize; jj++) {
      
      if(jj > 8) continue;
      
      std::pair<float, float> AK4_ptBins = mPtBinning.getBinValue(jj);	       
      std::string AK4_PtBin = TString::Format("pT_%i_%i", (int) AK4_ptBins.first, (int) AK4_ptBins.second ).Data();
      
	// pT Bias vs Eta
	DrawTProfile(dataFile1, Form("AK4_pTBias_vs_Eta_%s", AK4_PtBin.c_str()),  "#eta",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
	// energy fraction vs Eta
	DrawCompareProfile(dataFile1, Form("AK4_CHF_vs_Eta_%s_", AK4_PtBin.c_str()),  "#eta",  "CHF", false, false, -2.5, 2.5);
	DrawCompareProfile(dataFile1, Form("AK4_NHF_vs_Eta_%s_", AK4_PtBin.c_str()),  "#eta",  "NHF", false, false, -2.5, 2.5);
	DrawCompareProfile(dataFile1, Form("AK4_CEF_vs_Eta_%s_", AK4_PtBin.c_str()),  "#eta",  "CEF", false, false, -2.5, 2.5);
	DrawCompareProfile(dataFile1, Form("AK4_NEF_vs_Eta_%s_", AK4_PtBin.c_str()),  "#eta",  "NEF", false, false, -2.5, 2.5);
	DrawCompareProfile(dataFile1, Form("AK4_MuF_vs_Eta_%s_", AK4_PtBin.c_str()),  "#eta",  "MuF", false, false, -2.5, 2.5);

	//DrawCompareProfile(dataFile1, Form("AK4_pT_vs_Eta_%s_", AK4_PtBin.c_str()),  "#eta",  "pT [GeV]", false, false, -2.5, 2.5);
	//DrawTProfile(dataFile1, Form("AK4_pTBias_vs_CHF_%s", AK4_PtBin.c_str()),  "CHF",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
	//DrawTProfile(dataFile1, Form("AK4_pTBias_vs_NHF_%s", AK4_PtBin.c_str()),  "NHF",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
	//DrawTProfile(dataFile1, Form("AK4_pTBias_vs_CEF_%s", AK4_PtBin.c_str()), "CEF", "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
	//DrawTProfile(dataFile1, Form("AK4_pTBias_vs_NEF_%s", AK4_PtBin.c_str()), "NEF",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);
	//DrawTProfile(dataFile1, Form("AK4_pTBias_vs_MuF_%s", AK4_PtBin.c_str()), "MuF",  "pT(Reco)-pT(HLT)/pT(HLT)", false, -2.5, 2.5);      
    }
  
  // variable vs pT in eta bins
  for (size_t ii = 0; ii < etaBinningSize; ii++) {
      
    std::string AK4_etaName = mEtaBinning.getBinName( ii );
    std::string AK4_EtaBin = TString::Format("%s", AK4_etaName.c_str() ).Data();
    
    // pT bias vs pT      
    DrawTProfile(dataFile1, Form("AK4_pTBias_vs_Pt_%s", AK4_EtaBin.c_str()),  "pT [GeV]",  "pT(Reco)-pT(HLT)/pT(HLT)", false, 0., 1000.);
    // energy fraction vs pT
    DrawCompareProfile(dataFile1, Form("AK4_CHF_vs_Pt_%s_", AK4_EtaBin.c_str()),  "pT [GeV]",  "CHF", false, false, 0., 1000.);
    DrawCompareProfile(dataFile1, Form("AK4_NHF_vs_Pt_%s_", AK4_EtaBin.c_str()),  "pT [GeV]",  "NHF", false, false, 0., 1000.);
    DrawCompareProfile(dataFile1, Form("AK4_CEF_vs_Pt_%s_", AK4_EtaBin.c_str()),  "pT [GeV]",  "CEF", false, false, 0., 1000.);
    DrawCompareProfile(dataFile1, Form("AK4_NEF_vs_Pt_%s_", AK4_EtaBin.c_str()),  "pT [GeV]",  "NEF", false, false, 0., 1000.);
    DrawCompareProfile(dataFile1, Form("AK4_MuF_vs_Pt_%s_", AK4_EtaBin.c_str()),  "pT [GeV]",  "MuF", false, false, 0., 1000.);
      
  }


  return 0;
  
}
