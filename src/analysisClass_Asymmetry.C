#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <TProfile.h>
#include "ptBinning.h"
#include "etaBinning.h"
#include "vertexBinning.h"

bool verbose = true;
bool Smeared = true;
int Counter = 0;   // debugging -- can be erased    
double DeltaR_;
double alphacut_;
double DeltaEtaJJ_;
double MJJCut_;

analysisClass::analysisClass(string * inputList, string * cutFile, string * treeName, string * outputFileName, string * cutEfficFile)
  :baseClass(inputList, cutFile, treeName, outputFileName, cutEfficFile)
{
  std::cout << "analysisClass::analysisClass(): begins " << std::endl;

  //  std::string jetAlgo = getPreCutString1("jetAlgo");
  //  double rParam = getPreCutValue1("DeltaR");

  alphacut_ = getPreCutValue1("AlphaCut");
  DeltaR_ = getPreCutValue1("DeltaR");
  DeltaEtaJJ_ = getPreCutValue1("DeltaEtaJJ");
  MJJCut_ = getPreCutValue1("MJJCut");

  //  if( jetAlgo == "AntiKt" )
  //    fjJetDefinition = JetDefPtr( new fastjet::JetDefinition(fastjet::antikt_algorithm, rParam) );
  //  else if( jetAlgo == "Kt" )
  //    fjJetDefinition = JetDefPtr( new fastjet::JetDefinition(fastjet::kt_algorithm, rParam) );
  //  else 
  //    fjJetDefinition = JetDefPtr( new fastjet::JetDefinition(fastjet::cambridge_algorithm, rParam) );
  
  std::cout << "analysisClass::analysisClass(): ends " << std::endl;
}

analysisClass::~analysisClass()
{
  std::cout << "analysisClass::~analysisClass(): begins " << std::endl;

  std::cout << "analysisClass::~analysisClass(): ends " << std::endl;
}

void analysisClass::Loop()
{
  std::cout << "analysisClass::Loop() begins" <<std::endl;   

  srand48( time(0) );    
  if (fChain == 0) return;
   
  //////////book histos here


  /////////initialize variables

  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "analysisClass::Loop(): nentries = " << nentries << std::endl;   

  ////// The following ~7 lines have been taken from rootNtupleClass->Loop() /////
  ////// If the root version is updated and rootNtupleClass regenerated,     /////
  ////// these lines may need to be updated.                                 /////    
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) { // running over all events
    //   for (Long64_t jentry=0; jentry<25;jentry++) { //runnig over few events for test
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(jentry < 10 || jentry%1000 == 0) std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
    //std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
    // if (Cut(ientry) < 0) continue;
   
    ////////////////////// User's code starts here ///////////////////////

    //     verbose = true;

    if(verbose){
      std::cout<< std::endl;
      std::cout<<"Start"<< std::endl;
      std::cout<<"PassJSON "<< PassJSON<<std::endl;

      std::cout<<"RECO"<< std::endl;
      std::cout<<"AK4 jet1"<< std::endl;
      std::cout<<"Pt: "<< pTAK4_recoj1<<" eta: "<<etaAK4_recoj1<<" phi: "<<phiAK4_recoj1<< std::endl;
      std::cout<<"AK4 jet2"<< std::endl;
      std::cout<<"Pt: "<< pTAK4_recoj2<<" eta: "<<etaAK4_recoj2<<" phi: "<<phiAK4_recoj2<< std::endl;
      std::cout<<"AK4 jet3"<< std::endl;
      std::cout<<"Pt: "<< pTAK4_recoj3<<" eta: "<<etaAK4_recoj3<<" phi: "<<phiAK4_recoj3<< std::endl;

      std::cout<<"HLT"<< std::endl;
      std::cout<<"AK4 jet1"<< std::endl;
      std::cout<<"Pt: "<< pTAK4_j1<<" eta: "<<etaAK4_j1<<" phi: "<<phiAK4_j1<< std::endl;
      std::cout<<"AK4 jet2"<< std::endl;
      std::cout<<"Pt: "<< pTAK4_j2<<" eta: "<<etaAK4_j2<<" phi: "<<phiAK4_j2<< std::endl;
      std::cout<<"AK4 jet3"<< std::endl;
      std::cout<<"Pt: "<< pTAK4_j3<<" eta: "<<etaAK4_j3<<" phi: "<<phiAK4_j3<< std::endl;
    }
     
    //     if(PassJSON) 	   std::cout<<"Passed JSON"<< std::endl;
    //     if( mjjreco > MJJCut_ && mjj > MJJCut_ ) 	   std::cout<<"Passed MJJ"<< std::endl;
    //     if( deltaETAjjreco < DeltaEtaJJ_ && deltaETAjj < DeltaEtaJJ_) std::cout<<"Passed deltaEta"<< std::endl;

    //  if( passHLT_ZeroBias_BtagSeq || passHLT_ZeroBias || passHLT_L1DoubleMu_BtagSeq || passHLT_L1DoubleMu || passHLT_CaloJet40_BtagSeq || passHLT_CaloJet40 || passHLT_L1HTT150_BtagSeq || passHLT_L1HTT150 || passHLT_CaloScoutingHT250 || passHLT_HT450_BtagSeq || passHLT_HT450 || passHLT_PFHT800 || passHLT_PFHT650MJJ950 || passHLT_PFHT650MJJ900 ){

    if( PassJSON){
      // trigger selected
      //   if( passHLT_ZeroBias_BtagSeq || passHLT_ZeroBias ){ // #1
      //   if( passHLT_L1DoubleMu_BtagSeq || passHLT_L1DoubleMu ){ // #2
      //   if( passHLT_CaloJet40_BtagSeq || passHLT_CaloJet40 ){ // #3
      //   if( passHLT_L1HTT150_BtagSeq || passHLT_L1HTT150 ){ // #4
      //   if( passHLT_CaloScoutingHT250 ){ // #5
      if( passHLT_HT450_BtagSeq || passHLT_HT450 ){ // #6
	 
	// AK4 Jets
	vector<TLorentzVector> AK4recojets;
	TLorentzVector ak4j1Reco, ak4j2Reco, ak4dijetReco;             
	TLorentzVector ak4j3Reco ;
	   
	vector<TLorentzVector> AK4jets;
	TLorentzVector ak4j1, ak4j2, ak4dijet;      
	TLorentzVector ak4j3 ; 
       
	// Reco
	ak4j1Reco.SetPtEtaPhiM(pTAK4_recoj1, etaAK4_recoj1, phiAK4_recoj1, massAK4_recoj1);
	ak4j2Reco.SetPtEtaPhiM(pTAK4_recoj2, etaAK4_recoj2, phiAK4_recoj2, massAK4_recoj2);
	ak4j3Reco.SetPtEtaPhiM(pTAK4_recoj3, etaAK4_recoj3, phiAK4_recoj3, massAK4_recoj3);
	AK4recojets.push_back( ak4j1Reco );
	AK4recojets.push_back( ak4j2Reco );	 
	AK4recojets.push_back( ak4j3Reco );	 
       
	// HLT
	ak4j1.SetPtEtaPhiM(pTAK4_j1, etaAK4_j1, phiAK4_j1, massAK4_j1);
	ak4j2.SetPtEtaPhiM(pTAK4_j2, etaAK4_j2, phiAK4_j2, massAK4_j2);
	ak4j3.SetPtEtaPhiM(pTAK4_j3, etaAK4_j3, phiAK4_j3, massAK4_j3);
	AK4jets.push_back( ak4j1 );
	AK4jets.push_back( ak4j2 );
	AK4jets.push_back( ak4j3 );

	//////////// matching	 
	double DeltaReco1HLT1 = AK4recojets[0].DeltaR(AK4jets[0]);
	double DeltaReco1HLT2 = AK4recojets[0].DeltaR(AK4jets[1]);
	double DeltaReco2HLT1 = AK4recojets[1].DeltaR(AK4jets[0]);
	double DeltaReco2HLT2 = AK4recojets[1].DeltaR(AK4jets[1]);
	     
	if(verbose){
	  //	   cout << endl;
	  cout << "AK4: " << endl;
	  cout << "deltaR Reco1-HLT1 " <<  DeltaReco1HLT1 << endl;
	  cout << "deltaR Reco1-HLT2 " <<  DeltaReco1HLT2 << endl;
	  cout << "deltaR Reco2-HLT1 " <<  DeltaReco2HLT1 << endl;
	  cout << "deltaR Reco2-HLT2 " <<  DeltaReco2HLT2 << endl;
	}       
	     
	vector<int> IdxMatched;
	vector<double> deltaR_min;
	if( DeltaReco1HLT1 <= DeltaReco2HLT1 )
	  {
	    IdxMatched.push_back(0) ; // index Reco jets
	    IdxMatched.push_back(1) ; // index Reco jets
	    deltaR_min.push_back( DeltaReco1HLT1);
	    deltaR_min.push_back( DeltaReco2HLT2);
	  }else
	  {
	    IdxMatched.push_back(1) ; // index Reco jets
	    IdxMatched.push_back(0) ; // index Reco jets
	    deltaR_min.push_back( DeltaReco2HLT1);
	    deltaR_min.push_back( DeltaReco1HLT2);
	  }

	// HLT-Reco Matched : AK4
	if(verbose) cout << "deltaR_min_1_1 " << deltaR_min.at(0)  << endl;
	if(verbose) cout << "deltaR_min_2_2 " << deltaR_min.at(1)  << endl;

	// Asymmetry
	if(deltaR_min.at(0) < DeltaR_ && deltaR_min.at(1) < DeltaR_ ){   

	  int random;
	  random = lrand48()%(2);
	  if(verbose) std::cout<< "random = " <<random << std::endl;
	       
	  double pTaveReco = ( ak4j1Reco.Pt() + ak4j2Reco.Pt() ) / 2;
	  if(verbose) std::cout<< "Average pT Reco = " << pTaveReco << std::endl;
	  CreateAndFillUserTH1D("pTaveReco", 30 , 0, 3000, pTaveReco);	     
	  double alphaReco = ak4j3Reco.Pt() / pTaveReco ;
	  if(verbose) std::cout<< "alpha Reco = " << alphaReco << std::endl;
	  CreateAndFillUserTH1D("alphaReco", 100 , 0, 2, alphaReco);
	  double AsymmetryReco;

	  EtaBinning mEtaBinning;                                                                                                               
	  PtBinning mPtBinning; 
	     
	  int etaBin_j1Reco = mEtaBinning.getBin( fabs(ak4j1Reco.Eta()) );
	  int etaBin_j2Reco = mEtaBinning.getBin( fabs(ak4j2Reco.Eta()) );
	  int ptBin_Reco = mPtBinning.getPtBin( pTaveReco );
	  std::pair<float, float> ptBins_Reco = mPtBinning.getBinValue(ptBin_Reco);

	  if(verbose){       
	    cout<<"|Eta_ak4j1Reco| =   "<<fabs(ak4j1Reco.Eta())<<endl;
	    cout<<"|Eta_ak4j2Reco| =   "<<fabs(ak4j2Reco.Eta())<<endl;

	    std::pair<float, float> etaBins_j1 = mEtaBinning.getBinValue(etaBin_j1Reco);
	    std::pair<float, float> etaBins_j2 = mEtaBinning.getBinValue(etaBin_j2Reco);
	    cout<<"EtaBin_j1 =   "<<etaBin_j1Reco<<endl;
	    cout<<"EtaBin_j2 =   "<<etaBin_j2Reco<<endl;
	    cout<<"pTBin =   "<<ptBin_Reco<<endl;
	    cout<<"j1: etaBin.first  "<< etaBins_j1.first << "    etaBin.second   "<<etaBins_j1.second<<endl;
	    cout<<"j2: etaBin.first  "<< etaBins_j2.first << "    etaBin.second   "<<etaBins_j2.second<<endl;
	    cout<<"ptBin.first  "<< ptBins_Reco.first << "    ptBin.second   "<<ptBins_Reco.second<<endl;
	  }

	  /// HLT
	  double pTave = ( ak4j1.Pt() + ak4j2.Pt() ) /2;
	  if(verbose) std::cout<< "Average pT = " << pTave << std::endl;
	  CreateAndFillUserTH1D("pTave", 30 , 0, 3000, pTave);
	  double alpha = ak4j3.Pt() / pTave ;
	  if(verbose) std::cout<< "alpha = " << alpha << std::endl;
	  CreateAndFillUserTH1D("alpha", 100 , 0, 2, alpha);
	  double Asymmetry;
	       
	  int etaBin_j1 = mEtaBinning.getBin( fabs(ak4j1.Eta()) );
	  int etaBin_j2 = mEtaBinning.getBin( fabs(ak4j2.Eta()) );
	  int ptBin = mPtBinning.getPtBin( pTave );
	  std::pair<float, float> ptBins = mPtBinning.getBinValue(ptBin);	       
	   
	  if(verbose){
	    cout<<"|Eta_ak4j1| =   "<<fabs(ak4j1.Eta())<<endl;
	    cout<<"|Eta_ak4j2| =   "<<fabs(ak4j2.Eta())<<endl;
	       
	    std::pair<float, float> etaBins_j1 = mEtaBinning.getBinValue(etaBin_j1);
	    std::pair<float, float> etaBins_j2 = mEtaBinning.getBinValue(etaBin_j2);
	    cout<<"EtaBin_j1 =   "<<etaBin_j1<<endl;
	    cout<<"EtaBin_j2 =   "<<etaBin_j2<<endl;
	    cout<<"pTBin =   "<<ptBin <<endl;
	    cout<<"j1: etaBin.first  "<< etaBins_j1.first << "    etaBin.second   "<<etaBins_j1.second<<endl;
	    cout<<"j2: etaBin.first  "<< etaBins_j2.first << "    etaBin.second   "<<etaBins_j2.second<<endl;
	    cout<<"ptBin.first  "<< ptBins.first << "    ptBin.second   "<<ptBins.second<<endl;
	  }

      	  // seleziono gli stessi eventi	     
	  if(etaBin_j1Reco == etaBin_j2Reco){ // same eta bin RECO
	    std::string etaNameReco = mEtaBinning.getBinName(etaBin_j1Reco);	     
	    if(etaBin_j1 == etaBin_j2){ // same eta bin HLT
	      std::string etaName = mEtaBinning.getBinName(etaBin_j1);	     
	      if(alphaReco < alphacut_ ){	// alpha cut RECO
		if(alpha < alphacut_ ){	// alpha cut HLT		    

		  cout<< "PASSED"<< endl;
		  /// HLT
		  // introduco uno smearing 
		  /*
		    Devi cambiare il pT di tutti i jet che usi.
		    pTnew = pTold * smear
		    dove smear e’ un numero generato random secondo una distribuzione Gaussiana
		    di media=1 e sigma usuale allo smearing che vuoi mettere (es. 10%=0.1)
		  */
		  vector<TLorentzVector> AK4jetsSmeared;
		  // for(int ii = 0; ii < AK4jets.size(); ii++){
		  for(int ii = 0; ii < 2; ii++){
		    TLorentzVector ak4jetSmeared;      
		    double PtSmeared;      
		    double smear;      
		    TRandom *factor=new TRandom3(0);  //factor -> SetSeed(0);
		    smear = factor -> Gaus(1, 0.1);
		    PtSmeared= AK4jets[ii].Pt() * smear;
		    
		    ak4jetSmeared.SetPtEtaPhiM(PtSmeared, AK4jets[ii].Eta(), AK4jets[ii].Phi(), AK4jets[ii].M() );
		    AK4jetsSmeared.push_back(ak4jetSmeared);
		    
		    if(verbose){
		      std::cout<<"smearing factor = "<< smear << std::endl;
		      std::cout<<"HLT SMEARED"<< std::endl;
		      std::cout<<"AK4 smeared "<< ii << std::endl;
		      std::cout<<"Pt: "<< AK4jetsSmeared[ii].Pt() <<" eta: "<< AK4jetsSmeared[ii].Eta() <<" phi: "<< AK4jetsSmeared[ii].Phi() << std::endl;
		    }
		  } // end smearing
		  
		  double pTaveSmeared = ( AK4jetsSmeared[0].Pt() + AK4jetsSmeared[1].Pt() ) /2;
		  if(verbose) std::cout<< "Average pT = " << pTaveSmeared << std::endl;
		  CreateAndFillUserTH1D("pTaveSmeared", 300 , 0, 3000, pTaveSmeared);
		  //	    double alphaSmeared = AK4jetsSmeared[2].Pt() / pTaveSmeared ;
		  //	    if(verbose) std::cout<< "alpha Smeared = " << alphaSmeared << std::endl;
		  //	    CreateAndFillUserTH1D("alphaSmeared", 100 , 0, 2, alphaSmeared);
		  double AsymmetrySmeared;
		  
		  if(random == 0){
		    AsymmetryReco = ( ak4j1Reco.Pt() - ak4j2Reco.Pt() ) / ( ak4j1Reco.Pt() + ak4j2Reco.Pt() ) ;
		    Asymmetry        = ( ak4j1.Pt() - ak4j2.Pt() ) / ( ak4j1.Pt() + ak4j2.Pt() ) ;
		    AsymmetrySmeared = ( AK4jetsSmeared[0].Pt() - AK4jetsSmeared[1].Pt() ) / ( AK4jetsSmeared[0].Pt() + AK4jetsSmeared[1].Pt() ) ;
		  }else if(random == 1){
		    AsymmetryReco = ( ak4j2Reco.Pt() - ak4j1Reco.Pt() ) / ( ak4j1Reco.Pt() + ak4j2Reco.Pt() ) ; 
		    Asymmetry        = ( ak4j2.Pt() - ak4j1.Pt() ) / ( ak4j1.Pt() + ak4j2.Pt() ) ; 
		    AsymmetrySmeared = ( AK4jetsSmeared[1].Pt() - AK4jetsSmeared[0].Pt() ) / ( AK4jetsSmeared[0].Pt() + AK4jetsSmeared[1].Pt() ) ; 
		  }
		  std::string HistoNameReco = TString::Format("AsymmetryReco_%s_pT_%i_%i", etaNameReco.c_str(), (int) ptBins_Reco.first, (int) ptBins_Reco.second ).Data();	 	     
		  if(verbose) std::cout << HistoNameReco.c_str()<< std::endl;
		  if(verbose) std::cout<< "Asymmetry Reco = " << AsymmetryReco << std::endl; 
		  CreateAndFillUserTH1D(HistoNameReco.c_str(), 300, -2, 2, AsymmetryReco);
		  std::string HistoName = TString::Format("Asymmetry_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();	 	     
		  if(verbose) std::cout << HistoName.c_str()<< std::endl;
		  if(verbose) std::cout<< "Asymmetry  = " << Asymmetry << std::endl; 
		  CreateAndFillUserTH1D(HistoName.c_str(), 300, -2, 2, Asymmetry);
		  std::string HistoNameSmeared = TString::Format("AsymmetrySmeared_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();	 	     
		  if(verbose) std::cout << HistoNameSmeared.c_str()<< std::endl;
		  if(verbose) std::cout<< "Asymmetry Smeared  = " << AsymmetrySmeared << std::endl; 
		  CreateAndFillUserTH1D(HistoNameSmeared.c_str(), 300, -2, 2, AsymmetrySmeared);

		}else{//alpha cut HLT
		  if(verbose) std::cout<< "HLT: alpha too large = "<<alpha<<std::endl;
		}
	      }else{
		if(verbose) std::cout<< "Reco: alpha too large = "<<alphaReco<<std::endl;
	      }
	    }// eta bin HLT
	  } // eta bin Reco

	}// both jet matched
      }// trigger
    }// pass json
     
    /////////////////////////////////////////////////////////////////
     
    //== Fill Variables ==
    fillVariableWithValue("PassJSON", PassJSON);     
    fillVariableWithValue("MJJ_reco", mjjreco);     
    fillVariableWithValue("MJJ", mjj);     
    fillVariableWithValue("deltaETAjj_reco", deltaETAjjreco);     
    fillVariableWithValue("deltaETAjj", deltaETAjj);     
    
    ////////////////////////////////////////

    //no cuts on these variables, just to store in output
    // if(!isData)
    //   fillVariableWithValue("trueVtx",PileupInteractions->at(idx_InTimeBX));
    // else if(isData)
    //   fillVariableWithValue("trueVtx",999);     

    // Trigger
    //int NtriggerBits = triggerResult->size();
    /*   
	 if (isData)
	 {
	 fillVariableWithValue("passHLT_ZeroBias_BtagSeq",triggerResult->at(8));// DST_ZeroBias_BTagScouting_v* (run>=259636)
	 fillVariableWithValue("passHLT_ZeroBias",triggerResult->at(7));// DST_ZeroBias_PFScouting_v* (run>=259636)

	 fillVariableWithValue("passHLT_L1DoubleMu_BtagSeq",triggerResult->at(9));// DST_L1DoubleMu_BTagScouting_v* (run>=259636)
	 fillVariableWithValue("passHLT_L1DoubleMu",triggerResult->at(10));// DST_L1DoubleMu_PFScouting_v* (run>=259636)

	 fillVariableWithValue("passHLT_CaloJet40_BtagSeq",triggerResult->at(0));//  DST_CaloJet40_PFReco_PFBTagCSVReco_PFScouting_v* (257933<=run<259636) 
	 //  OR DST_CaloJet40_BTagScouting_v* (run>=259636)
	 fillVariableWithValue("passHLT_CaloJet40",triggerResult->at(1));// DST_CaloJet40_CaloScouting_PFScouting_v*  (run>=259636)

	 fillVariableWithValue("passHLT_L1HTT150_BtagSeq",triggerResult->at(2));// DST_L1HTT125ORHTT150ORHTT175_PFReco_PFBTagCSVReco_PFScouting_v* (257933<=run<259636) 
	 // OR DST_L1HTT_BTagScouting_v* (run>=259636)    
	 fillVariableWithValue("passHLT_L1HTT150",triggerResult->at(3));// DST_L1HTT_CaloScouting_PFScouting_v* (run>=259636)

	 fillVariableWithValue("passHLT_HT450_BtagSeq",triggerResult->at(5));// DST_HT450_PFReco_PFBTagCSVReco_PFScouting_v* (257933<=run<259636) 
	 // OR DST_HT450_BTagScouting_v* (run>=259636)    
	 fillVariableWithValue("passHLT_HT450",triggerResult->at(6));// DST_HT450_PFScouting_v* (run>=259636)        

	 fillVariableWithValue("passHLT_PFHT800",triggerResult->at(13));// HLT_PFHT800_v* (all runs)   
	 fillVariableWithValue("passHLT_PFHT650MJJ950",triggerResult->at(22));// HLT_PFHT650_WideJetMJJ950DEtaJJ1p5_v* (all runs)        
	 fillVariableWithValue("passHLT_PFHT650MJJ900",triggerResult->at(23));// HLT_PFHT650_WideJetMJJ900DEtaJJ1p5_v* (all runs)        
	 }
    */
    // Evaluate cuts (but do not apply them)
    evaluateCuts();
     
    // optional call to fill a skim with the full content of the input roottuple
    //if( passedCut("nJetFinal") ) fillSkimTree();
    /*
      if( passedCut("PassJSON")
      && passedCut("nVtx") 
      && passedCut("IdTight_j1")
      && passedCut("IdTight_j2")
      && passedCut("nJet")
      && passedCut("pTWJ_j1")
      && passedCut("etaWJ_j1")
      && passedCut("pTWJ_j2")
      && passedCut("etaWJ_j2")
      && getVariableValue("deltaETAjj") <  getPreCutValue1("DetaJJforTrig") ){

      h_mjj_NoTrigger -> Fill(MJJWideReco); 
       
      if( (getVariableValue("passHLT_ZeroBias_BtagSeq")||getVariableValue("passHLT_ZeroBias")) )
      h_mjj_HLTpass_ZeroBias -> Fill(MJJWideReco);  
      if( (getVariableValue("passHLT_ZeroBias_BtagSeq")||getVariableValue("passHLT_ZeroBias")) 
      && (getVariableValue("passHLT_L1HTT150_BtagSeq")||getVariableValue("passHLT_L1HTT150")) )
      h_mjj_HLTpass_ZeroBias_L1HTT150 -> Fill(MJJWideReco);  

      if( (getVariableValue("passHLT_L1HTT150_BtagSeq")||getVariableValue("passHLT_L1HTT150")) )
      h_mjj_HLTpass_L1HTT150 -> Fill(MJJWideReco);  

      if( (getVariableValue("passHLT_L1HTT150_BtagSeq")||getVariableValue("passHLT_L1HTT150")) 
      && (getVariableValue("passHLT_HT450_BtagSeq")||getVariableValue("passHLT_HT450")) )
      h_mjj_HLTpass_L1HTT150_HT450 -> Fill(MJJWideReco);  
       
      }
    */
    // optional call to fill a skim with a subset of the variables defined in the cutFile (use flag SAVE)

    //     if( passedAllPreviousCuts("mjj") && passedCut("mjj") ) 
    //       {
    fillReducedSkimTree();

    // ===== Take a look at this =====
    // //Example on how to investigate quickly the data
    // if(getVariableValue("mjj")>4000)
    //   {
    //     //fast creation and filling of histograms
    //     CreateAndFillUserTH1D("h_dphijj_mjjgt4000", 100, 0, 3.15, getVariableValue("deltaPHIjj"));
    //     CreateAndFillUserTH1D("h_htak4_mjjgt4000", 1000, 0, 10000, getVariableValue("HTAK4reco"));
    //     CreateAndFillUserTH1D("h_nvtx_mjjgt4000", 31, -0.5, 30.5, getVariableValue("nVtx"));
    //   }

    //       }

    // ===== Example of mjj spectrum after HLT selection =====
    // if( passedAllPreviousCuts("mjj") )
    //   {
    // 	 if(getVariableValue("passHLT")>0)
    // 	   {
    // 	     //fast creation and filling of histograms
    // 	     CreateAndFillUserTH1D("h_mjj_passHLT", getHistoNBins("mjj"), getHistoMin("mjj"), getHistoMax("mjj"), getVariableValue("mjj"));
    // 	   }
    //   }

    // reject events that did not pass level 0 cuts
    //if( !passedCut("0") ) continue;
    // ......
     
    // reject events that did not pass level 1 cuts
    //if( !passedCut("1") ) continue;
    // ......

    // reject events that did not pass the full cut list
    //if( !passedCut("all") ) continue;
    // ......

    // if( widejets.size() >= 2) {
    //  h_nJetFinal->Fill(widejets.size());
    //  h_DijetMass->Fill(wdijet.M());
    //  h_pT1stJet->Fill(widejets[0].Pt());
    //  h_pT2ndJet->Fill(widejets[1].Pt());
    //  h_eta1stJet->Fill(widejets[0].Eta());
    //  h_eta2ndJet->Fill(widejets[1].Eta());
    // }
    ////////////////////// User's code ends here ///////////////////////

  } // End loop over events

  //////////write histos 


  //  h_mjj_NoTrigger -> Write();
  //  h_mjj_HLTpass_ZeroBias -> Write();
  //  h_mjj_HLTpass_ZeroBias_L1HTT150 -> Write();
  //  h_mjj_HLTpass_L1HTT150 -> Write();
  //  h_mjj_HLTpass_L1HTT150_HT450 -> Write();

  // h_nVtx->Write();
  // h_trueVtx->Write();
  // h_nJetFinal->Write();
  // h_pT1stJet->Write();
  // h_pT2ndJet->Write();
  // h_DijetMass->Write();
  // h_eta1stJet->Write();
  // h_eta2ndJet->Write();

  // //pT of both jets, to be built using the histograms produced automatically by baseClass
  // TH1F * h_pTJets = new TH1F ("h_pTJets","", getHistoNBins("pT1stJet"), getHistoMin("pT1stJet"), getHistoMax("pT1stJet"));
  // h_pTJets->Add( & getHisto_noCuts_or_skim("pT1stJet") ); // all histos can be retrieved, see other getHisto_xxxx methods in baseClass.h
  // h_pTJets->Add( & getHisto_noCuts_or_skim("pT2ndJet") );
  // //one could also do:  *h_pTJets = getHisto_noCuts_or_skim("pT1stJet") + getHisto_noCuts_or_skim("pT2ndJet");
  // h_pTJets->Write();
  // //one could also do:   const TH1F& h = getHisto_noCuts_or_skim// and use h


  std::cout << "analysisClass::Loop() ends" <<std::endl;   
}

//Federico

/*
// analysis in bin of number of vertices
VertexBinning mVtxBinning;
	     
int vtxBinReco = mVtxBinning.getVertexBin( nVtxreco );
int vtxBinHLT = mVtxBinning.getVertexBin( nVtx );
	     
std::pair<int, int> vtxBinsReco = mVtxBinning.getBinValue(vtxBinReco);
std::pair<int, int> vtxBinsHLT = mVtxBinning.getBinValue(vtxBinHLT);
	     
if(verbose){
cout<<"vtxReco  "<< nVtxreco <<endl;
cout<<"vtx  "<< nVtx <<endl;
cout<<"vtxBin(Reco)  "<< vtxBinReco<<endl;
cout<<"vtxBin.first  "<< vtxBinsReco.first << "    vtxBin.second   "<<vtxBinsReco.second<<endl;
cout<<"vtxBin(HLT)  "<< vtxBinHLT <<endl;
cout<<"vtxBin.first  "<< vtxBinsHLT.first << "    vtxBin.second   "<<vtxBinsHLT.second<<endl;
}
	     
std::string HistoNameReco = TString::Format("pTWJ_recoj1_nvtx_%i_%i",  vtxBinsReco.first, vtxBinsReco.second ).Data();
std::string HistoNameHLT  = TString::Format("pTWJ_j1_nvtx_%i_%i",  vtxBinsHLT.first, vtxBinsHLT.second ).Data();
	     
std::cout << HistoNameReco.c_str()<< std::endl;
std::cout << HistoNameHLT.c_str()<< std::endl;
	     
CreateAndFillUserTH1D(HistoNameReco.c_str(), 300, -2, 2, pTWJ_recoj1 );
CreateAndFillUserTH1D(HistoNameHLT.c_str(), 300, -2, 2, pTWJ_j1 );
*/


/* jet non smearati
	   double pTave = ( ak4j1.Pt() + ak4j2.Pt() ) /2;
	   if(verbose) std::cout<< "Average pT = " << pTave << std::endl;
	   CreateAndFillUserTH1D("pTave", 300 , 0, 3000, pTave);
	 
	   double alpha = ak4j3.Pt() / pTave ;
	   if(verbose) std::cout<< "alpha = " << alpha << std::endl;
	   CreateAndFillUserTH1D("alpha", 100 , 0, 2, alpha);
	   double Asymmetry = 999;
	 
	   int etaBin_j1 = mEtaBinning.getBin( fabs(ak4j1.Eta()) );
	   int etaBin_j2 = mEtaBinning.getBin( fabs(ak4j2.Eta()) );
	   int ptBin = mPtBinning.getPtBin( pTave );
	 
	   if(verbose){
	     cout<<" |Eta_ak4j1| =   "<<fabs(ak4j1.Eta())<<endl;
	     cout<<" |Eta_ak4j2| =   "<<fabs(ak4j2.Eta())<<endl;
	   }
	 
	   std::pair<float, float> ptBins = mPtBinning.getBinValue(ptBin);
	 
	   if(verbose){
	     std::pair<float, float> etaBins_j1 = mEtaBinning.getBinValue(etaBin_j1);
	     std::pair<float, float> etaBins_j2 = mEtaBinning.getBinValue(etaBin_j2);
	     cout<<" EtaBin_j1 =   "<<etaBin_j1<<endl;
	     cout<<" EtaBin_j2 =   "<<etaBin_j2<<endl;
	     cout<<" pTBin =   "<<ptBin <<endl;
	     cout<<"j1: etaBin.first  "<< etaBins_j1.first << "    etaBin.second   "<<etaBins_j1.second<<endl;
	     cout<<"j2: etaBin.first  "<< etaBins_j2.first << "    etaBin.second   "<<etaBins_j2.second<<endl;
	     cout<<"ptBin.first  "<< ptBins.first << "    ptBin.second   "<<ptBins.second<<endl;
	   }
	 
	   if(etaBin_j1 == etaBin_j2){
	     std::string etaName = mEtaBinning.getBinName(etaBin_j1);	     
	   
	     if(alpha < alphacut_ ){	
	     
	       if(random == 0){
		 Asymmetry = ( ak4j1.Pt() - ak4j2.Pt() ) / ( ak4j1.Pt() + ak4j2.Pt() ) ;
	       }else if(random == 1){
		 Asymmetry = ( ak4j2.Pt() - ak4j1.Pt() ) / ( ak4j1.Pt() + ak4j2.Pt() ) ; 
	       }
	     
	       std::string HistoName = TString::Format("Asymmetry_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();	 	     
	       if(verbose) std::cout << HistoName.c_str()<< std::endl;
	       if(verbose) std::cout<< "Asymmetry  = " << Asymmetry << std::endl; 
	       CreateAndFillUserTH1D(HistoName.c_str(), 300, -2, 2, Asymmetry);
	     }//alpha cut
	   }// same eta region
 */
