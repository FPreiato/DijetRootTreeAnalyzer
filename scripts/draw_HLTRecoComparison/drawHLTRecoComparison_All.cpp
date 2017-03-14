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
  // AK4 Jets
  DrawTH1(dataFile1, "AK4_deltaR",  "#Delta R",  "Events", log,  0, 5);
  DrawTH1(dataFile1, "AK4_deltaR_minimum",  "#Delta R",  "Events", log,  0, 1);
  DrawTH1(dataFile1, "AK4_deltaR_minimum_AfterMatch",  "#Delta R",  "Events", log,  0, 1);
  DrawComparison(dataFile1, "AK4_pT_Jet", "pT [GeV]", "Events", false, false, 0, 1300);
  DrawTH2(dataFile1, "AK4_pT_Jet",  "pT(Reco) [GeV]",  "pT(HLT) [GeV]", log, colz,  0., 1300., 0., 1300.);
  DrawComparison(dataFile1, "AK4_Eta_Jet", "#eta", "Events", false, false, -2.5, 2.5);
  DrawTH2(dataFile1, "AK4_Eta_Jet",  "#eta(Reco)",  "#eta(HLT)", log, colz,  -2.5, 2.5, -2.5, 2.5);
  DrawComparison(dataFile1, "AK4_Phi_Jet", "#phi", "Events", false, false, -3.15, 3.15);
  DrawTH2(dataFile1, "AK4_Phi_Jet",  "#phi(Reco)",  "#phi(HLT)", log, colz,  -3.15, 3.15, -3.15, 3.15);
  DrawComparison(dataFile1, "AK4_chargedHadEnFrac", "CHF", "Events", log, false, 0, 1);
  DrawTH2(dataFile1, "AK4_chargedHadEnFrac",  "CHF Reco",  "CHF HLT", log, colz,  0., 1., 0., 1.);
  DrawComparison(dataFile1, "AK4_neutrHadEnFrac", "NHF", "Events", log, false, 0, 1);
  DrawTH2(dataFile1, "AK4_neutrHadEnFrac",  "NHF Reco",  "NHF HLT", log, colz,  0., 1., 0., 1.);
  DrawComparison(dataFile1, "AK4_chargedElectromFrac", "CEMF", "Events", log, false, 0, 1);
  DrawTH2(dataFile1, "AK4_chargedElectromFrac",  "CEMF Reco",  "CEMF HLT", log, colz,  0., 1., 0., 1.);
  DrawComparison(dataFile1, "AK4_neutrElectromFrac", "NEMF", "Events", log, false, 0, 1);
  DrawTH2(dataFile1, "AK4_neutrElectromFrac",  "NEMF Reco",  "NEMF HLT", log, colz,  0., 1., 0., 1.);
  DrawComparison(dataFile1, "AK4_muEnFrac", "MUF", "Events", log, false, 0, 1);
  DrawTH2(dataFile1, "AK4_muEnFrac",  "MUF Reco",  "MUF HLT", log, colz,  0., 1., 0., 1.);
  DrawComparison(dataFile1, "AK4_chargedMult", "CM", "Events", log, false, 0, 100);
  DrawTH2(dataFile1, "AK4_chargedMult",  "CM Reco",  "CM HLT", log, colz,  0., 100., 0., 100.);
  DrawComparison(dataFile1, "AK4_neutrMult", "NM", "Events", log, false, 0, 100);
  DrawTH2(dataFile1, "AK4_neutrMult",  "NM Reco",  "NM HLT", log, colz,  0., 100., 0., 100.);
  DrawComparison(dataFile1, "AK4_photonMult", "PM", "Events", log, false, 0, 100);
  DrawTH2(dataFile1, "AK4_photonMult",  "PM Reco",  "PM HLT", log, colz,  0., 100., 0., 100.);
  DrawComparison(dataFile1, "AK4_jetCSVAK4", "CSV", "Events", log, false, 0, 1);
  DrawTH2(dataFile1, "AK4_jetCSVAK4",  "CSV Reco",  "CSV HLT", log, colz,  0., 1., 0., 1.);

  DrawTH1(dataFile1, "AK4_pTBias",  "pT(HLT)-pT(Reco)/pT(Reco)",  "Events", false,  -0.5, 0.5);
  FitTH1(dataFile1, "AK4_pTBias",  "pT(HLT)-pT(Reco)/pT(Reco)",  "Events", false,  -0.5, 0.5);

  // AK4 vs Nvtx
  //  DrawTProfile(dataFile1, "AK4_pTBias_vs_Nvtx",  "nVtx",  "pT(HLT)-pT(Reco)/pT(Reco)", false, 0, 25);
  LinearFit(dataFile1, "AK4_pTBias_vs_Nvtx",  "nVtx",  "pT(HLT)-pT(Reco)/pT(Reco)", false,  0, 25);
  DrawCompareProfile(dataFile1, "AK4_pT_vs_Nvtx",  "nVtx",  "pT [GeV]", false, false, 0, 25);
  // AK4 vs Eta
  DrawTProfile(dataFile1, "AK4_pTBias_vs_Eta",  "#eta",  "pT(HLT)-pT(Reco)/pT(Reco)", false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "AK4_pT_vs_Eta",  "#eta",  "pT [GeV]", false, false, -2.5, 2.5);
  // AK4 vs Pt
  DrawTProfile(dataFile1, "AK4_pTBias_vs_Pt",  "pT [GeV]",  "pT(HLT)-pT(Reco)/pT(Reco)", false, 0, 1300);
  DrawCompareProfile(dataFile1, "AK4_pT_vs_Pt",  "pT [GeV]",  "pT [GeV]", false, false, 0, 1300);

  ////////////////////////// WideJets

  DrawTH1(dataFile1, "deltaR",  "#Delta R",  "Events", log,  0, 5);
  DrawTH1(dataFile1, "deltaR_minimum",  "#Delta R",  "Events", log,  0, 1);
  DrawTH1(dataFile1, "deltaR_minimum_AfterMatch",  "#Delta R",  "Events", log,  0, 1);
  DrawComparison(dataFile1, "pT_WideJet", "pT [GeV]", "Events", false, false, 0, 1300);
  DrawTH2(dataFile1, "pT_WideJet",  "pT(Reco) [GeV]",  "pT(HLT) [GeV]", log, colz,  0., 1300., 0., 1300.);
  DrawComparison(dataFile1, "Eta_WideJet", "#eta", "Events", false, false, -2.5, 2.5);
  DrawTH2(dataFile1, "Eta_WideJet",  "#eta(Reco)",  "#eta(HLT)", log, colz,  -2.5, 2.5, -2.5, 2.5);
  DrawComparison(dataFile1, "Phi_WideJet", "#phi", "Events", false, false, -3.15, 3.15);
  DrawTH2(dataFile1, "Phi_WideJet",  "#phi(Reco)",  "#phi(HLT)", log, colz,  -3.15, 3.15, -3.15, 3.15);

  DrawTH1(dataFile1, "pTBias",  "pT(HLT)-pT(Reco)/pT(Reco)",  "Events", false,  -0.5, 0.5);
  FitTH1(dataFile1, "pTBias",  "pT(HLT)-pT(Reco)/pT(Reco)",  "Events", false,  -0.5, 0.5);

  // vs Nvtx
  //  DrawTProfile(dataFile1, "pTBias_vs_Nvtx",  "nVtx",  "pT(HLT)-pT(Reco)/pT(Reco)", false, 0, 25);
  LinearFit(dataFile1, "pTBias_vs_Nvtx",  "nVtx",  "pT(HLT)-pT(Reco)/pT(Reco)", false,  0, 25);
  DrawCompareProfile(dataFile1, "pT_vs_Nvtx",  "nVtx",  "pT [GeV]", false, false, 0, 25);
  // vs Eta
  DrawTProfile(dataFile1, "pTBias_vs_Eta",  "#eta",  "pT(HLT)-pT(Reco)/pT(Reco)", false, -2.5, 2.5);
  DrawCompareProfile(dataFile1, "pT_vs_Eta",  "#eta",  "pT [GeV]", false, false, -2.5, 2.5);
  // vs Pt
  DrawTProfile(dataFile1, "pTBias_vs_Pt",  "pT [GeV]",  "pT(HLT)-pT(Reco)/pT(Reco)", false, 0, 1300);
  DrawCompareProfile(dataFile1, "pT_vs_Pt",  "pT [GeV]",  "pT [GeV]", false, false, 0, 1300);

  DrawComparison(dataFile1, "met", "MET [GeV]", "Events", log, false, 0, 1300);
  DrawTH2(dataFile1, "met",  "MET(Reco) [GeV]",  "MET(HLT) [GeV]", log, colz,  0., 1300., 0., 1300.);
  DrawComparison(dataFile1, "metSig", "MET Significance", "Events", log, false, 0, 1);
  DrawTH2(dataFile1, "metSig",  "MET Sig (Reco)",  "MET Sig (HLT)", log, colz,  0., 1., 0., 1.);
  DrawComparison(dataFile1, "NVertex", "n vertex", "Events", false, false, 0, 25);
  DrawTH2(dataFile1, "NVertex",  "nVtx(Reco)",  "nVtx(HLT)", log, colz,  0, 25, 0, 25);
  DrawComparison(dataFile1, "deltaETAjj", "#Delta #eta (jj)", "Events", log, false, 0, 3);
  DrawTH2(dataFile1, "deltaETAjj",  "#Delta #eta (jj) (Reco)",  "#Delta #eta (jj) (HLT)", log, colz,  0., 3., 0., 3.);

  DrawTH1(dataFile1, "mJJBias",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)",  "Events", false,  -0.5, 0.5);
  FitTH1(dataFile1, "mJJBias",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)",  "Events", false,  -0.5, 0.5);
  // vs Nvtx
  //  DrawTProfile(dataFile1, "mJJBias_vs_Nvtx",  "nVtx",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false,  0, 25);
  LinearFit(dataFile1, "mJJBias_vs_Nvtx",  "nVtx",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false,  0, 25);
  DrawCompareProfile(dataFile1, "mJJ_vs_Nvtx",  "nVtx",  "mJJ [GeV]", false, false,  0, 25);
  //vs Eta
  DrawTProfile(dataFile1, "mJJBias_vs_Eta",  "#eta",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false,  -2.5, 2.5);
  DrawCompareProfile(dataFile1, "mJJ_vs_Eta",  "#eta",  "mJJ [GeV]", false, false,  -2.5, 2.5);
  //vs pT
  DrawTProfile(dataFile1, "mJJBias_vs_Pt",  "pT [GeV]",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false,  0, 1300);
  DrawCompareProfile(dataFile1, "mJJ_vs_Pt",  "pT [GeV]",  "mJJ [GeV]", false, false,  0, 1300);
  // vs mJJ
  DrawTProfile(dataFile1, "mJJBias_vs_Mjj",  "mJJ [GeV]",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false, 0, 2000);
  DrawCompareProfile(dataFile1, "mJJ_vs_Mjj",  "mJJ [GeV]",  "mJJ [GeV]", false, false,  0, 2000);

  //  LinearFit(dataFile1, "pTBias_vs_Nvtx",  "nVtx",  "pT(HLT)-pT(Reco)/pT(Reco)", false,  0, 25);
  //  LinearFit(dataFile1, "pT_vs_NvtxHLT",  "nVtx",  "pT(HLT)", false,  0, 25);

  //  LinearFit(dataFile1, "mJJBias_vs_Nvtx",  "nVtx",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false,  0, 25);
  //  LinearFit(dataFile1, "mJJ_vs_NvtxHLT",  "nVtx",  "mJJ(HLT)", false,  0, 25);

  //////////////////// drawing in in eta and pT bins
  EtaBinning mEtaBinning;
  PtBinning mPtBinning;
  mJJBinning mMjjBinning; 
  
  
  size_t etaBinningSize = mEtaBinning.size();
  size_t pTBinningSize = mPtBinning.size();
  size_t mJJBinningSize = mMjjBinning.size();

  for (size_t ii = 0; ii < etaBinningSize; ii++) {
    for (size_t jj = 0; jj < pTBinningSize; jj++) {

      std::string etaName = mEtaBinning.getBinName(ii);
      std::pair<float, float> ptBins = mPtBinning.getBinValue(jj);	       
      
      std::string AK4_pTBias = TString::Format("AK4_pTBias_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string AK4_pTBias_vs_Nvtx = TString::Format("AK4_pTBias_vs_Nvtx_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string AK4_pTBias_vs_Eta = TString::Format("AK4_pTBias_vs_Eta_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string AK4_pTBias_vs_Pt = TString::Format("AK4_pTBias_vs_Pt_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      FitTH1(dataFile1, AK4_pTBias.c_str(),  "pT(HLT)-pT(Reco)/pT(Reco)",  "Events", false,  -0.5, 0.5);
      LinearFit(dataFile1, AK4_pTBias_vs_Nvtx.c_str(),  "nVtx",  "pT(HLT)-pT(Reco)/pT(Reco)", false,  0, 25);
      DrawTProfile(dataFile1, AK4_pTBias_vs_Eta.c_str(),  "#eta",  "pT(HLT)-pT(Reco)/pT(Reco)", false, -2.5, 2.5);
      DrawTProfile(dataFile1, AK4_pTBias_vs_Pt.c_str(),  "pT [GeV]",  "pT(HLT)-pT(Reco)/pT(Reco)", false, ptBins.first, ptBins.second);

      std::string pTBias = TString::Format("pTBias_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string pTBias_vs_Nvtx = TString::Format("pTBias_vs_Nvtx_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string pTBias_vs_Eta = TString::Format("pTBias_vs_Eta_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string pTBias_vs_Pt = TString::Format("pTBias_vs_Pt_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      FitTH1(dataFile1, pTBias.c_str(),  "pT(HLT)-pT(Reco)/pT(Reco)",  "Events", false,  -0.5, 0.5);
      LinearFit(dataFile1, pTBias_vs_Nvtx.c_str(),  "nVtx",  "pT(HLT)-pT(Reco)/pT(Reco)", false,  0, 25);
      DrawTProfile(dataFile1, pTBias_vs_Eta.c_str(),  "#eta",  "pT(HLT)-pT(Reco)/pT(Reco)", false, -2.5, 2.5);
      DrawTProfile(dataFile1, pTBias_vs_Pt.c_str(),  "pT [GeV]",  "pT(HLT)-pT(Reco)/pT(Reco)", false, ptBins.first, ptBins.second);

      std::string Asymmetry = TString::Format("Asymmetry_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string AsymmetryReco = TString::Format("AsymmetryReco_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();      

      DrawComparison(dataFile1, AsymmetryReco.c_str(), Asymmetry.c_str(), "Asymmetry", "Normalized", false, false, -0.5, 0.5);

    }
  }

  for (size_t ii = 0; ii < mJJBinningSize; ii++) {

      std::pair<float, float> mJJBins = mMjjBinning.getBinValue(ii);	       

    std::string mJJBias = TString::Format("mJJBias_mJJ_%i_%i", (int) mJJBins.first, (int) mJJBins.second ).Data();
    std::string mJJBias_vs_Nvtx = TString::Format("mJJBias_vs_Nvtx_mJJ_%i_%i", (int) mJJBins.first, (int) mJJBins.second ).Data();
    std::string mJJBias_vs_Mjj = TString::Format("mJJBias_vs_Mjj_mJJ_%i_%i", (int) mJJBins.first, (int) mJJBins.second ).Data();
    FitTH1(dataFile1, mJJBias.c_str(),  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)",  "Events", false,  -0.5, 0.5);
    LinearFit(dataFile1, mJJBias_vs_Nvtx.c_str(),  "nVtx",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false,  0, 25);
    DrawTProfile(dataFile1, mJJBias_vs_Mjj.c_str(),  "mJJ [GeV]",  "mJJ(HLT)-mJJ(Reco)/mJJ(Reco)", false, mJJBins.first, mJJBins.second);
  }  



  return 0;
  
}

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

