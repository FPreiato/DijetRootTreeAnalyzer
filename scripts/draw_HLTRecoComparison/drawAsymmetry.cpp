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

  //  DrawTH1(dataFile1, "deltaR_minimum",  "#Delta R",  "Events", log,  0, 1);

  //////////////////// drawing in in eta and pT bins
  EtaBinning mEtaBinning;
  PtBinning mPtBinning;
  
  size_t etaBinningSize = mEtaBinning.size();
  size_t pTBinningSize = mPtBinning.size();
  
  for (size_t ii = 0; ii < etaBinningSize; ii++) {
    for (size_t jj = 0; jj < pTBinningSize; jj++) {
      
      std::string etaName = mEtaBinning.getBinName(ii);
      std::pair<float, float> ptBins = mPtBinning.getBinValue(jj);	       
      
      std::string HistoName = TString::Format("Asymmetry_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string HistoName2 = TString::Format("AsymmetryReco_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();      

      //      std::cout << HistoName.c_str()<< std::endl;
      //      std::cout << HistoName2.c_str()<< std::endl;
      
      DrawComparison(dataFile1, HistoName.c_str(), HistoName2.c_str(), "Asymmetry", "Normalized", false, false, -0.5, 0.5);

    }
  }


  return 0;
  
}

// se facciamo un binning piu stretto e non esistono tutti gli istogramma possiamo fare cosi
//      TH1D *h_Reco = (TH1D*)dataFile1->Get(HistoName.c_str());
//      TH1D *h_HLT = (TH1D*)dataFile1->Get(HistoName2.c_str());
//      if( !h_Reco || !h_HLT) continue;
