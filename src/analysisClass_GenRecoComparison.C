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
//#include "ptBinning.h"
//#include "etaBinning.h"
//#include "mJJBinning.h"

bool verbose;
//int Counter = 0;   // debugging -- can be erased    
double DeltaR_;
//double alphacut_;
//double DeltaEtaJJ_;
//double MJJCut_;
//mJJBinning mMjjBinning; 

analysisClass::analysisClass(string * inputList, string * cutFile, string * treeName, string * outputFileName, string * cutEfficFile)
  :baseClass(inputList, cutFile, treeName, outputFileName, cutEfficFile)
{
  std::cout << "analysisClass::analysisClass(): begins " << std::endl;

  //  std::string jetAlgo = getPreCutString1("jetAlgo");
  //  double rParam = getPreCutValue1("DeltaR");

  //  alphacut_ = getPreCutValue1("AlphaCut");
  //  DeltaEtaJJ_ = getPreCutValue1("DeltaEtaJJ");
  //  MJJCut_ = getPreCutValue1("MJJCut");
  DeltaR_ = getPreCutValue1("DeltaR");
  verbose = getPreCutValue1("verbose");

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

    //    N_events++;
    if(verbose){
      std::cout<<std::endl;
      std::cout<<"AK4 Jets"<< std::endl;
      std::cout<<"Gen 1"<< std::endl;
      std::cout<<"Pt: "<<pTAK4_Genj1<<" eta: "<<etaAK4_Genj1<<" phi: "<<phiAK4_Genj1<< std::endl;
      std::cout<<"Gen 2"<< std::endl;
      std::cout<<"Pt: "<<pTAK4_Genj2<<" eta: "<<etaAK4_Genj2<<" phi: "<<phiAK4_Genj2<< std::endl;
      std::cout<<"Reco 1"<< std::endl;
      std::cout<<"Pt: "<<pTAK4_j1<<" eta: "<<etaAK4_j1<<" phi: "<<phiAK4_j1<< std::endl;
      std::cout<<"Reco 2"<< std::endl;
      std::cout<<"Pt: "<<pTAK4_j2<<" eta: "<<etaAK4_j2<<" phi: "<<phiAK4_j2<< std::endl;
    }
    
    // back-to-back jets	  
    //	    if(deltaPHIjjreco > 2.8 && deltaPHIjj >2.8){
    //	    N_passDeltaPhiJJ++;
    //	    if(verbose) cout<< "pass DeltaPhiJJ"<< endl;	  	  
	    
    vector<TLorentzVector> AK4_Genjets;
    TLorentzVector AK4_Genj1, AK4_Genj2, AK4Gendijet; 	     

    vector<TLorentzVector> AK4_jets;
    TLorentzVector AK4_j1, AK4_j2, AK4_dijet; 
	    
    //Gen
    AK4_Genj1.SetPtEtaPhiM(pTAK4_Genj1, etaAK4_Genj1, phiAK4_Genj1, massAK4_Genj1);
    AK4_Genj2.SetPtEtaPhiM(pTAK4_Genj2, etaAK4_Genj2, phiAK4_Genj2, massAK4_Genj2);	     
    AK4_Genjets.push_back( AK4_Genj1 );
    AK4_Genjets.push_back( AK4_Genj2 );
    
    // Reco
    AK4_j1.SetPtEtaPhiM(pTAK4_j1, etaAK4_j1, phiAK4_j1, massAK4_j1);
    AK4_j2.SetPtEtaPhiM(pTAK4_j2, etaAK4_j2, phiAK4_j2, massAK4_j2);
    AK4_jets.push_back( AK4_j1 );
    AK4_jets.push_back( AK4_j2 );
          
    //////////// matching	 
    double AK4_DeltaGen1Reco1 = AK4_Genjets[0].DeltaR(AK4_jets[0]);
    double AK4_DeltaGen1Reco2 = AK4_Genjets[0].DeltaR(AK4_jets[1]);
    double AK4_DeltaGen2Reco1 = AK4_Genjets[1].DeltaR(AK4_jets[0]);
    double AK4_DeltaGen2Reco2 = AK4_Genjets[1].DeltaR(AK4_jets[1]);	    

    if(verbose)
      {
	cout << "AK4 JETS " << endl;
	cout << "deltaR Gen1-Reco1 " <<  AK4_DeltaGen1Reco1 << endl;
	cout << "deltaR Gen1-Reco2 " <<  AK4_DeltaGen1Reco2 << endl;
	cout << "deltaR Gen2-Reco1 " <<  AK4_DeltaGen2Reco1 << endl;
	cout << "deltaR Gen2-Reco2 " <<  AK4_DeltaGen2Reco2 << endl;
      }       
    
    //   CreateAndFillUserTH1D("AK4_deltaR", 500, 0, 5, AK4_DeltaGen1Reco1 );
    //    CreateAndFillUserTH1D("AK4_deltaR", 500, 0, 5, AK4_DeltaGen2Reco1 );
    
    vector<int> AK4_IdxMatched;
    vector<double> AK4_deltaR_min;
    
    if( AK4_DeltaGen1Reco1 <= AK4_DeltaGen2Reco1 )
      {
	AK4_IdxMatched.push_back( 0 ) ; // index Gen
	AK4_IdxMatched.push_back( 1 ) ;
	AK4_deltaR_min.push_back( AK4_DeltaGen1Reco1 ) ;
	AK4_deltaR_min.push_back( AK4_DeltaGen2Reco2 ) ;
      }
    else
      {
	AK4_IdxMatched.push_back( 1 ) ; // index Gen
	AK4_IdxMatched.push_back( 0 ) ;
	AK4_deltaR_min.push_back( AK4_DeltaGen2Reco1 ) ;
	AK4_deltaR_min.push_back( AK4_DeltaGen1Reco2 ) ;
      }
    //////////////////////////////////////////////

    // both matched
    if(AK4_deltaR_min.at(0) < DeltaR_ && AK4_deltaR_min.at(1) < DeltaR_ ){
      
      for(int ii=0 ; ii<AK4_deltaR_min.size() ; ii++){

	// solo uno matcheato	
	//if(deltaR_min.at(ii) < DeltaR_){
	
	// Gen-Reco Matched
	if(verbose){
	  cout << "ii:  " << ii  << endl;
	  cout << "deltaR_min  " << AK4_deltaR_min.at(ii)  << endl;
	}
	
	//////////////////////// Histograms:
	
	CreateAndFillUserTH1D("pTAK4_Gen", 260, 0, 13000, AK4_Genjets[AK4_IdxMatched.at(ii)].Pt() );
	CreateAndFillUserTH1D("pTAK4"        , 260, 0, 13000, AK4_jets[ii].Pt() );

	CreateAndFillUserTH1D("MjjAK4_Gen", 260, 0, 13000, GenDijet_MassAK4 );
	CreateAndFillUserTH1D("MjjAK4"        , 260, 0, 13000, Dijet_MassAK4 );

      }// loop over jets    
    }// matching


    /////////////////////////////// WIDEJETS ///////////////////////////////////////////

    if(verbose){
      std::cout<<std::endl;
      std::cout<<"WIDEJET"<< std::endl;
      std::cout<<"Gen 1"<< std::endl;
      std::cout<<"Pt: "<<pTWJ_Genj1<<" eta: "<<etaWJ_Genj1<<" phi: "<<phiWJ_Genj1<< std::endl;
      std::cout<<"Gen 2"<< std::endl;
      std::cout<<"Pt: "<<pTWJ_Genj2<<" eta: "<<etaWJ_Genj2<<" phi: "<<phiWJ_Genj2<< std::endl;
      std::cout<<"Reco 1"<< std::endl;
      std::cout<<"Pt: "<<pTWJ_j1<<" eta: "<<etaWJ_j1<<" phi: "<<phiWJ_j1<< std::endl;
      std::cout<<"Reco 2"<< std::endl;
      std::cout<<"Pt: "<<pTWJ_j2<<" eta: "<<etaWJ_j2<<" phi: "<<phiWJ_j2<< std::endl;
    }
    	    
    vector<TLorentzVector> Genwidejets;
    TLorentzVector Genwj1, Genwj2, Genwdijet; 	     

    vector<TLorentzVector> widejets;
    TLorentzVector wj1, wj2, wdijet; 
	    
    //Gen
    Genwj1.SetPtEtaPhiM(pTWJ_Genj1, etaWJ_Genj1, phiWJ_Genj1, massWJ_Genj1);
    Genwj2.SetPtEtaPhiM(pTWJ_Genj2, etaWJ_Genj2, phiWJ_Genj2, massWJ_Genj2);	     
    Genwidejets.push_back( Genwj1 );
    Genwidejets.push_back( Genwj2 );
    
    // Reco
    wj1.SetPtEtaPhiM(pTWJ_j1, etaWJ_j1, phiWJ_j1, massWJ_j1);
    wj2.SetPtEtaPhiM(pTWJ_j2, etaWJ_j2, phiWJ_j2, massWJ_j2);
    widejets.push_back( wj1 );
    widejets.push_back( wj2 );
          
    //////////// matching	 
    double DeltaGen1Reco1 = Genwidejets[0].DeltaR(widejets[0]);
    double DeltaGen1Reco2 = Genwidejets[0].DeltaR(widejets[1]);
    double DeltaGen2Reco1 = Genwidejets[1].DeltaR(widejets[0]);
    double DeltaGen2Reco2 = Genwidejets[1].DeltaR(widejets[1]);	    

    if(verbose)
      {
	cout << "WIDEJETS " << endl;
	cout << "deltaR Gen1-Reco1 " <<  DeltaGen1Reco1 << endl;
	cout << "deltaR Gen1-Reco2 " <<  DeltaGen1Reco2 << endl;
	cout << "deltaR Gen2-Reco1 " <<  DeltaGen2Reco1 << endl;
	cout << "deltaR Gen2-Reco2 " <<  DeltaGen2Reco2 << endl;
      }       
    
    // CreateAndFillUserTH1D("deltaR", 500, 0, 5, DeltaGen1Reco1 );
    // CreateAndFillUserTH1D("deltaR", 500, 0, 5, DeltaGen2Reco1 );
    
    vector<int> IdxMatched;
    vector<double> deltaR_min;
    
    if( DeltaGen1Reco1 <= DeltaGen2Reco1 )
      {
	IdxMatched.push_back( 0 ) ; // index Gen
	IdxMatched.push_back( 1 ) ;
	deltaR_min.push_back( DeltaGen1Reco1 ) ;
	deltaR_min.push_back( DeltaGen2Reco2 ) ;
      }
    else
      {
	IdxMatched.push_back( 1 ) ; // index Gen
	IdxMatched.push_back( 0 ) ;
	deltaR_min.push_back( DeltaGen2Reco1 ) ;
	deltaR_min.push_back( DeltaGen1Reco2 ) ;
      }
    //////////////////////////////////////////////

    // both matched
    if(deltaR_min.at(0) < DeltaR_ && deltaR_min.at(1) < DeltaR_ ){
      
      for(int ii=0 ; ii<deltaR_min.size() ; ii++){

	// solo uno matcheato	
	//      if(deltaR_min.at(ii) < DeltaR_){

	
	// Gen-Reco Matched
	if(verbose){
	  cout << "ii:  " << ii  << endl;
	  cout << "deltaR_min  " << deltaR_min.at(ii)  << endl;
	}
	
	//////////////////////// Histogrammi che vuoi:
	
	CreateAndFillUserTH1D("pTWJ_Gen", 260, 0, 13000, Genwidejets[IdxMatched.at(ii)].Pt() );
	CreateAndFillUserTH1D("pTWJ"        , 260, 0, 13000, widejets[ii].Pt() );

	CreateAndFillUserTH1D("Mjj_Gen", 260, 0, 13000, Genmjj );
	CreateAndFillUserTH1D("Mjj"        , 260, 0, 13000, mjj );
    
      }// matching
    }// loop over jets


  
    //  }// deltaPhi
    //  }// JetID
    //  }// trigger
    //  }// pass json
    
    /////////////////////////////////////////////////////////////////
    
    //== Fill Variables ==
    // fillVariableWithValue("PassJSON", PassJSON);     
    // fillVariableWithValue("GenMJJ", Genmjj);     
    // fillVariableWithValue("MJJ", mjj);     
    // fillVariableWithValue("GendeltaETAjj", GendeltaETAjj);     
    // fillVariableWithValue("deltaETAjj", deltaETAjj);     
    
    ////////////////////////////////////////

    // Evaluate cuts (but do not apply them)
    evaluateCuts();
     
    //     if( passedAllPreviousCuts("mjj") && passedCut("mjj") ) 
    //       {
    fillReducedSkimTree();
    
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

	      // double pTaveReco = ( wj1Reco.Pt() + wj2Reco.Pt() ) / 2;
	      // if(verbose) std::cout<< "Average pT Reco = " << pTaveReco << std::endl;
	      // CreateAndFillUserTH1D("pTaveReco", 30 , 0, 3000, pTaveReco);	     
	      // double alphaReco = ak4j3Reco.Pt() / pTaveReco ;
	      // if(verbose) std::cout<< "alpha Reco = " << alphaReco << std::endl;
	      // CreateAndFillUserTH1D("alphaReco", 100 , 0, 2, alphaReco);
	  
	      /// HLT
	      // double pTave = ( wj1.Pt() + wj2.Pt() ) /2;
	      // if(verbose) std::cout<< "Average pT = " << pTave << std::endl;
	      // CreateAndFillUserTH1D("pTave", 30 , 0, 3000, pTave);
	      // double alpha = ak4j3.Pt() / pTave ;
	      // if(verbose) std::cout<< "alpha = " << alpha << std::endl;
	      // CreateAndFillUserTH1D("alpha", 100 , 0, 2, alpha);	      	      	  			

	      // same events selected
	      // if(alphaReco < alphacut_ ){	// alpha cut RECO
	      // if(alpha < alphacut_ ){	// alpha cut HLT		    


/*
	      /// HLT
	      // introduco uno smearing 
	     // Devi cambiare il pT di tutti i jet che usi.
	     //	    pTnew = pTold * smear
	     //	    dove smear e’ un numero generato random secondo una distribuzione Gaussiana
	     //	    di media=1 e sigma usuale allo smearing che vuoi mettere (es. 10%=0.1)
	     
		    vector<TLorentzVector> AK4jetsSmeared;
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
		  int ptBinSmeared = mPtBinning.getPtBin( pTaveSmeared );
		  std::pair<float, float> ptBinsSmeared = mPtBinning.getBinValue(ptBinSmeared);	       
		  
		  double AsymmetrySmeared;

 */
