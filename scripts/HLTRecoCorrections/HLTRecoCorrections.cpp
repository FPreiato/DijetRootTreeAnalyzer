#include <stdlib.h>
#include <sys/stat.h>  
#include <time.h>

#include "TParameter.h"
#include "TPaveText.h"
#include "TError.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TFile.h"
#include <TMap.h>
#include <TMath.h>
#include "ptBinning.h"
#include "etaBinning.h"
#include <TColor.h>
#include <TStyle.h>

using namespace std;

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


double pTMeanArray[] = {30, 100, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000};
int binnum = sizeof(pTMeanArray)/sizeof(double) - 1;
double etaBins[] = {-2.50, -1.50, -1.25, -1.00, -0.75, -0.50, -0.25, 0.00, 0.25, 0.50, 0.75, 1.00, 1.25, 1.50, 2.50};  
int  binnumEta = sizeof(etaBins)/sizeof(double) -1;                                                                                                      

TH2D *Histo_Corrections = new TH2D("Histo_Corrections","Corrections", binnumEta, etaBins, binnum, pTMeanArray);

/////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

  std::string outputDir = "Plot";                 
  mkdir(outputDir.c_str(), 0777); 

  TString dataFileName_DoubleMu;
  //  dataFileName_DoubleMu = TString::Format("../../output/HLTReco_Comparison/rootFile_JEC_HLT_v7_RecoLowerCuts_pTCut10GeV_FinerPtBin_DoubleMu.root");
  dataFileName_DoubleMu = TString::Format("../../output/HLTReco_Comparison/rootFile_JEC_HLT_v7_RecoLowerCuts_pTCut10GeV_ChangedEtaPtBin_DoubleMu.root");
  TFile* dataFile_DoubleMu = TFile::Open(dataFileName_DoubleMu);
  if (dataFile_DoubleMu) {
    std::cout << "Opened data file '" << dataFileName_DoubleMu << "'." << std::endl;
  }
  TString dataFileName_HT450;
  //  dataFileName_HT450 = TString::Format("../../output/HLTReco_Comparison/rootFile_JEC_HLT_v7_RecoLowerCuts_pTCut10GeV_FinerPtBin_HT450.root");
  dataFileName_HT450 = TString::Format("../../output/HLTReco_Comparison/rootFile_JEC_HLT_v7_RecoLowerCuts_pTCut10GeV_ChangedEtaPtBin_HT450.root");
  TFile* dataFile_HT450 = TFile::Open(dataFileName_HT450);
  if (dataFile_HT450) {
    std::cout << "Opened data file '" << dataFileName_HT450 << "'." << std::endl;
  }

  gErrorIgnoreLevel = kWarning;

  //////////////////////// disegno pTBias 1D
  EtaBinning mEtaBinning;
  size_t etaBinningSize = mEtaBinning.size();
  PtBinning mPtBinning;
  size_t pTBinningSize = mPtBinning.size();

  cout<< etaBinningSize << endl;

  for (size_t ii = 0; ii < etaBinningSize; ii++) {
    for (size_t jj = 0; jj < pTBinningSize; jj++) {

      std::string etaName = mEtaBinning.getBinName(ii);
      std::pair<float, float> ptBins = mPtBinning.getBinValue(jj);	       
      
      std::string HistoName = TString::Format("AK4_pTBias_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();

      cout<< HistoName.c_str() << endl;

      TH1D *h;
      if( jj < 2){ // pT<300
	h = (TH1D*)dataFile_DoubleMu->Get( HistoName.c_str() );
	cout << " Lo prendo dal DoubleMu" << endl;
      }else if(jj < 6){ // pT<700 due to low statistics
	h = (TH1D*)dataFile_HT450->Get( HistoName.c_str() );
	cout << " Lo prendo dal HT450" << endl;
      }else{ continue; }
      
      TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
      h -> SetMarkerStyle(20);
      h -> SetMarkerSize(1.5);
      h->GetXaxis()->SetRangeUser(-0.4, 0.4);
      h -> Draw();
      c1->SaveAs( Form("Plot/%s.png", HistoName.c_str() ) );

      /////////////////////////////////////////////////

      int pTMin = ptBins.first;
      int pTMax = ptBins.second;
      double pTMean= (pTMin + pTMax) /2. ;
      double BinMax      = h->GetMaximumBin();
      double pTBiasMax      = h->GetMaximum();
      double pTBias      = h->GetBinCenter(BinMax);
      double pTBiasErr  = h->GetBinError(BinMax);

      cout<< "pT mean = "<< pTMean <<endl;
      cout<< "pT Bias maximum = "<< pTBiasMax <<endl;
      cout<< "pT Bias = "<< pTBias <<endl;
      cout<< "sigma(pT Bias) = "<< pTBiasErr <<endl;


      std::string TGraphName = TString::Format("Test_AK4_pTBias_vs_pT_etabin_%i", ii).Data();
      CreateAndFillUserTGraph(TGraphName.c_str(), jj, pTMean, pTBias, 0, 0);

    }
  }

  for(int ii = 1; ii < (etaBinningSize+1) ; ii++){ 
   
    std::string TGraphName = TString::Format("Test_AK4_pTBias_vs_pT_etabin_%i", ii).Data();
    map<std::string , TGraphErrors*>::iterator nh_h = userTGraphs_.find( TGraphName );
    if( nh_h == userTGraphs_.end()) continue;

    TF1* functionFit = new TF1( "functionFit", "-[0]*(log(x)*log(x)) + [1]*log(x)", 30,700); // quadratica log
    // functionFit->SetParLimits(0, 0., 10000);
    // functionFit->SetParLimits(1, 0., 10000);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
    nh_h->second->SetMarkerStyle(20);
    nh_h->second->SetMarkerSize(1.5);
    //    nh_h->second->Fit(functionFit, "R");
    nh_h->second->Draw("ZAP");
    c1->SaveAs( Form("Plot/%s.png", TGraphName.c_str() ) );
  }




  /////////////////////////////////////////////////////////////////////
  // creating TGraph
  // PtBinning mPtBinning;
  //  size_t pTBinningSize = mPtBinning.size();

  for(int ii = 1; ii < (etaBinningSize+1) ; ii++){ //# bins in eta
    cout<< "Bin in eta # "<< ii << endl;
    for(size_t jj=0; jj < pTBinningSize; jj++){

      std::pair<float, float> ptBins = mPtBinning.getBinValue(jj);	       
      std::string Histo = TString::Format("AK4_pTBias_vs_Eta_VariableBin_pT_%i_%i", (int) ptBins.first, (int) ptBins.second ).Data();
      cout<< Histo.c_str() << endl;

      int pTMin = ptBins.first;
      int pTMax = ptBins.second;
      double pTMean= (pTMin + pTMax) /2. ;

      TH1D *h;
      if( jj < 2){ // pT<300
	h = (TH1D*)dataFile_DoubleMu->Get( Histo.c_str() );
	cout << " Lo prendo dal DoubleMu" << endl;
      }else if(jj < 6){ // pT<700 due to low statistics
	h = (TH1D*)dataFile_HT450->Get( Histo.c_str() );
	cout << " Lo prendo dal HT450" << endl;
      }else{ continue; }
      
      TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
      h->SetTitle("");
      h->SetXTitle("#eta");
      h->SetYTitle("pTBias");
      h->SetStats(0);
      h -> SetMarkerStyle(20);
      h -> SetMarkerSize(1.5);
      //      h->GetXaxis()->SetRangeUser(-0.4, 0.4);
      h -> Draw();
      c1->SaveAs( Form("Plot/%s.png", Histo.c_str() ) );


      double pTBias      = h->GetBinContent(ii);
      double pTBiasErr = h->GetBinError(ii);

      cout<< "pT mean = "<< pTMean <<endl;
      cout<< "pT Bias = "<< pTBias <<endl;
      cout<< "sigma(pT Bias) = "<< pTBiasErr <<endl;

      std::string TGraphName = TString::Format("AK4_pTBias_vs_pT_etabin_%i", ii).Data();
      CreateAndFillUserTGraph(TGraphName.c_str(), jj, pTMean, pTBias, 0, pTBiasErr);

    }// for sui pT
  }// for bin in eta
  /////////////////////////////// costruiti i TGraph da fittare

  for(int ii = 1; ii < (etaBinningSize+1) ; ii++){ 
   
    std::string TGraphName = TString::Format("AK4_pTBias_vs_pT_etabin_%i", ii).Data();
    map<std::string , TGraphErrors*>::iterator nh_h = userTGraphs_.find( TGraphName );
    if( nh_h == userTGraphs_.end()) continue;

    //    TF1* functionFit = new TF1( "functionFit", "[0] + [1]* TMath::Log(x)", 30,700); // linearLog
    TF1* functionFit = new TF1( "functionFit", "-[0]*(log(x)*log(x)) + [1]*log(x)", 30,700); // quadratica log
    //    TF1* functionFit = new TF1( "functionFit", "[0]*(log(x)*log(x)) + [1]*log(x)", 30,700); // quadratica log
    // TF1* functionFit = new TF1( "functionFit", "[0]*(log(x)*log(x)) + [1]*log(x) +[2]", 30,700); // quadratica log

    // functionFit->SetParLimits(0, 0., 10000);
    // functionFit->SetParLimits(1, 0., 10000);

    TCanvas *c1 = new TCanvas("c1", "c1", 800, 800);
    nh_h->second->SetMarkerStyle(20);
    nh_h->second->SetMarkerSize(1.5);
    //    nh_h->second->Fit(functionFit, "R");
    nh_h->second->Draw("ZAP");
    c1->SaveAs( Form("Plot/%s.png", TGraphName.c_str() ) );
    
    double Par0       =  functionFit->GetParameter(0);
    double Par1       =  functionFit->GetParameter(1);
    //    double Par2       =  functionFit->GetParameter(2);
    cout<< "Par 0 = " << Par0 << endl;
    cout<< "Par 1 = " << Par1 << endl;
    //    cout<< "Par 2 = " << Par2 << endl;

    for(int jj=0; jj < binnum; jj++){
      
      int pTMin = pTMeanArray[jj];
      int pTMax = pTMeanArray[jj+1];
      double pTMean= (pTMin + pTMax) /2. ;
      cout<<"pT Mean = " << pTMean <<endl;

      //   double pTBiasFit = Par0 + Par1* TMath::Log(pTMean);
      //      double pTBiasFit = -Par0*(log(pTMean)*log(pTMean)) + Par1*log(pTMean) +Par2;
      double pTBiasFit = Par0*(log(pTMean)*log(pTMean)) + Par1*log(pTMean);
      cout<<"pT Bias from fit = " << pTBiasFit <<endl;

      Histo_Corrections->SetBinContent(ii, jj+1, pTBiasFit);

    } //pT bin
  } // eta bin


    TCanvas *c2 = new TCanvas("c2", "c2", 900, 800);
    Histo_Corrections->SetStats(0);
    gStyle->SetPalette(55);
    Histo_Corrections->SetContour(100);
    Histo_Corrections->Draw("colz");
    c2->SetRightMargin(0.13);
    c2->SaveAs("Plot/Corrections.png");


    TFile* outputFile= new TFile("Corrections_JEC_HLT_v7.root","RECREATE");
    outputFile->cd();
    Histo_Corrections -> Write();
    outputFile->Close();


    return 0;
  
}

  /*
  EtaBinning mEtaBinning;
  size_t etaBinningSize = mEtaBinning.size();
  PtBinning mPtBinning;
  size_t pTBinningSize = mPtBinning.size();

  for (size_t ii = 0; ii < etaBinningSize; ii++) {
    for (size_t jj = 0; jj < pTBinningSize; jj++) {

      std::string etaName = mEtaBinning.getBinName(ii);
      std::pair<float, float> ptBins = mPtBinning.getBinValue(jj);	       
      
      std::string HistoName = TString::Format("pTResolution_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string HistoName2 = TString::Format("pt_WideJet_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();

      std::string HistoName3 = TString::Format("AK4_pTResolution_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
      std::string HistoName4 = TString::Format("AK4_pt_Jets_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();

      std::cout << HistoName.c_str()<< std::endl;

      // se facciamo un binning piu stretto e non esistono tutti gli istogramma possiamo fare cosi
      //      TH1D *h1 = (TH1D*)dataFile1->Get(HistoName.c_str());
      //      if( !h1) continue;

    }// pt binning
  }// eta binning

*/
