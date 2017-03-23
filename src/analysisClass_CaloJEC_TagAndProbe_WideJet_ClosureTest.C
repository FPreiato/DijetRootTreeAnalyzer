#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TH1F.h>
#include <TF1.h>
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
//include "mJJBinning.h"

bool ClosureTest = true;

bool typeI = false; // HLT
bool typeII = false; // Reco
bool typeIII = true; // Random
bool typeIV = false; //Mean

int N_events;
int N_passJson;
int N_passTrigger;
int N_passJetID;
int N_passDeltaPhiJJ;
int N_passThirdJetReco;
int N_passThirdJetHLT;
int N_passMatching;
int N_jets;
int N_passEta;
int N_passZeroBias;
int N_passDoubleMu;
int N_passCaloJet40;
int N_passL1HTT;
int N_passCaloScoutingHT250;
int N_passPFScoutingHT410;
bool verbose;
double DeltaR_;
double alphacut_;
double DeltaEtaJJ_;
double MJJCut_;
//mJJBinning mMjjBinning; 

analysisClass::analysisClass(string * inputList, string * cutFile, string * treeName, string * outputFileName, string * cutEfficFile)
  :baseClass(inputList, cutFile, treeName, outputFileName, cutEfficFile)
{
  std::cout << "analysisClass::analysisClass(): begins " << std::endl;

  alphacut_ = getPreCutValue1("AlphaCut");
  DeltaR_ = getPreCutValue1("DeltaR");
  DeltaEtaJJ_ = getPreCutValue1("DeltaEtaJJ");
  MJJCut_ = getPreCutValue1("MJJCut");
  verbose = getPreCutValue1("verbose");

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
  double ptBins[] = {0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1200, 1400, 1600, 1800, 2000, 2500};
  int  binnum = sizeof(ptBins)/sizeof(double) -1;

  /////////initialize variables

  Long64_t nentries = fChain->GetEntriesFast();
  std::cout << "analysisClass::Loop(): nentries = " << nentries << std::endl;   

  ////// The following ~7 lines have been taken from rootNtupleClass->Loop() /////
  ////// If the root version is updated and rootNtupleClass regenerated,     /////
  ////// these lines may need to be updated.                                 /////    
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) { // running over all events
    //for (Long64_t jentry=0; jentry<1000000;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
    if(jentry < 10 || jentry%1000 == 0) std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
    //std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
    // if (Cut(ientry) < 0) continue;
   
    ////////////////////// User's code starts here ///////////////////////

    // if( nVtx > 5 || nVtxreco > 5 ) continue;
    // if( nVtx <=5 || nVtx > 15 || nVtxreco <=5 || nVtxreco >15 ) continue;
    // if( nVtx <= 15 || nVtxreco <= 15 ) continue;

    bool ZeroBias = false;            
    bool DoubleMu = false; 
    bool CaloJet40 = false; 
    bool L1HTT150 = false;  
    bool CaloScoutingHT250 = false;      
    bool PFScoutingHT410 = false;      
    
    if( passHLT_ZeroBias_BTagScouting || passHLT_ZeroBias_CaloScouting_PFScouting) ZeroBias = true;
    if( passHLT_L1DoubleMu_BTagScouting || passHLT_L1DoubleMu_CaloScouting_PFScouting) DoubleMu = true;
    if( passHLT_CaloJet40_BTagScouting || passHLT_CaloJet40_CaloScouting_PFScouting || passHLT_CaloJet40_CaloBTagScouting) CaloJet40 = true;
    if( passHLT_L1HTT_BTagScouting || passHLT_L1HTT_CaloBTagScouting || passHLT_L1HTT_CaloScouting_PFScouting)   L1HTT150 = true;        
    if( passHLT_CaloScoutingHT250 || passHLT_CaloBTagScoutingHT250 ) CaloScoutingHT250 = true;  	
    if( passHLT_BTagScoutingHT410 || passHLT_PFScoutingHT410) PFScoutingHT410 = true;
    
    N_events++;
    if(verbose){
      std::cout<<std::endl;
      std::cout<<"WIDEJET"<< std::endl;
      std::cout<<"Reco 1"<< std::endl;
      std::cout<<"Pt: "<<pTWJ_recoj1<<" eta: "<<etaWJ_recoj1<<" phi: "<<phiWJ_recoj1<< std::endl;
      std::cout<<"Reco 2"<< std::endl;
      std::cout<<"Pt: "<<pTWJ_recoj2<<" eta: "<<etaWJ_recoj2<<" phi: "<<phiWJ_recoj2<< std::endl;
      std::cout<<"AK4 Reco 3"<< std::endl;                                                                                                                                      
      std::cout<<"Pt: "<< pTAK4_recoj3<<" eta: "<<etaAK4_recoj3<<" phi: "<<phiAK4_recoj3<< std::endl;

      std::cout<<"HLT 1"<< std::endl;
      std::cout<<"Pt: "<<pTWJ_j1<<" eta: "<<etaWJ_j1<<" phi: "<<phiWJ_j1<< std::endl;
      std::cout<<"HLT 2"<< std::endl;
      std::cout<<"Pt: "<<pTWJ_j2<<" eta: "<<etaWJ_j2<<" phi: "<<phiWJ_j2<< std::endl;
      std::cout<<"AK4 HLT 3"<< std::endl;                                                                                                                                       
      std::cout<<"Pt: "<< pTAK4_j3<<" eta: "<<etaAK4_j3<<" phi: "<<phiAK4_j3<< std::endl;
    }
        
    if( PassJSON){      
      N_passJson++;
      if(verbose) cout<< "pass JSON"<< endl;
      
      if( ZeroBias || DoubleMu || CaloJet40 || L1HTT150 || CaloScoutingHT250 ){	
	N_passTrigger++;
	if(verbose) cout<< "pass Trigger"<< endl;
	
	// ID already applied	
	if( IdTight_recoj1>0.5 && IdTight_recoj2>0.5 && IdTight_j1>0.5 && IdTight_j2>0.5   ){
	  N_passJetID++;
	  if(verbose) cout<< "pass JetID"<< endl;
	  // back-to-back jets	  
	  if(deltaPHIjjreco > 2.8 && deltaPHIjj >2.8){
	    N_passDeltaPhiJJ++;
	    if(verbose) cout<< "pass DeltaPhiJJ"<< endl;	  
	    if(deltaETAjjreco <1.3 && deltaETAjj <1.3){
	      	      
	      vector<TLorentzVector> widejetsReco;
	      TLorentzVector wj1Reco, wj2Reco, wdijetReco; 	     
	      vector<TLorentzVector> widejets, widejetsCorr;
	      TLorentzVector wj1, wj2, wdijet ;
	      TLorentzVector j3, j3Reco;   
	      //Reco
	      wj1Reco.SetPtEtaPhiM(pTWJ_recoj1, etaWJ_recoj1, phiWJ_recoj1, massWJ_recoj1);
	      wj2Reco.SetPtEtaPhiM(pTWJ_recoj2, etaWJ_recoj2, phiWJ_recoj2, massWJ_recoj2);	     
	      widejetsReco.push_back( wj1Reco );
	      widejetsReco.push_back( wj2Reco );	    
	      j3Reco.SetPtEtaPhiM(pTAK4_recoj3, etaAK4_recoj3, phiAK4_recoj3, massAK4_recoj3);	     
	      //HLT
	      wj1.SetPtEtaPhiM(pTWJ_j1, etaWJ_j1, phiWJ_j1, massWJ_j1);
	      wj2.SetPtEtaPhiM(pTWJ_j2, etaWJ_j2, phiWJ_j2, massWJ_j2);
	      widejets.push_back( wj1 );
	      widejets.push_back( wj2 );
	      j3.SetPtEtaPhiM(pTAK4_j3, etaAK4_j3, phiAK4_j3, massAK4_j3);	     
	    
	      // HLT corrected
	      for(int ii=0; ii<widejets.size(); ii++){ // loop on jets                                                                                                                         
		TLorentzVector wjCorr_tmp; 
		// correction
		// ICHEP FUNCTION
		//	TF1 *f1 = new TF1("f1","[0]+[1]*log(x) + [2]*log(x)*log(x)");
		//	f1->FixParameter(0, -31.7198 );
		//	f1->FixParameter(1, 8.58611 );
		//	f1->FixParameter(2, -0.622092 );

		TF1 *f1 = new TF1("f1","[0]*pow(x,[1]) + [2]*pow(max(0.,log(x/700.)),1.2)");                                                                                       
		f1->FixParameter(0, -155.15 );
		f1->FixParameter(1, -0.709 );
		f1->FixParameter(2, -0.312 );
		
		double correction = f1->Eval( widejets[ii].Pt() );
		double ptCorr = widejets[ii].Pt() / (1 + correction/100) ; // corrected		 		  
		double massCorr = widejets[ii].M() / (1 + correction/100) ; // corrected //bug		 		  	      
		wjCorr_tmp.SetPtEtaPhiM(ptCorr, widejets[ii].Eta(), widejets[ii].Phi(), massCorr);    
		widejetsCorr.push_back( wjCorr_tmp );
	      }
	      TLorentzVector dijetCorr;      
	      double mjjCorr = 0;	
	      dijetCorr = widejetsCorr[0] + widejetsCorr[1];
	      mjjCorr = dijetCorr.M();    
	      
	      // cout << "HLT mjj " <<  mjj << endl;
	      // cout << "Reco mjj " <<  mjjreco << endl;
	      // cout << "HLT mjj corrected " <<  mjjCorr << endl;

	      //////////// matching	 
	      double DeltaReco1HLT1 = widejetsReco[0].DeltaR(widejets[0]);
	      double DeltaReco1HLT2 = widejetsReco[0].DeltaR(widejets[1]);
	      double DeltaReco2HLT1 = widejetsReco[1].DeltaR(widejets[0]);
	      double DeltaReco2HLT2 = widejetsReco[1].DeltaR(widejets[1]);	    
	      
	      if(verbose){
		cout << "deltaR Reco1-HLT1 " <<  DeltaReco1HLT1 << endl;
		cout << "deltaR Reco1-HLT2 " <<  DeltaReco1HLT2 << endl;
		cout << "deltaR Reco2-HLT1 " <<  DeltaReco2HLT1 << endl;
		cout << "deltaR Reco2-HLT2 " <<  DeltaReco2HLT2 << endl;
	      }       
	      CreateAndFillUserTH1D("deltaR", 500, 0, 5, DeltaReco1HLT1 );
	      CreateAndFillUserTH1D("deltaR", 500, 0, 5, DeltaReco2HLT1 );
	      
	      vector<int> IdxMatched;
	      vector<double> deltaR_min;
	      
	      if( DeltaReco1HLT1 <= DeltaReco1HLT2 )
		{
		  IdxMatched.push_back( 0 ) ; // index HLT
		  IdxMatched.push_back( 1 ) ;
		  deltaR_min.push_back( DeltaReco1HLT1 ) ;
		  deltaR_min.push_back( DeltaReco2HLT2 ) ;
		}else
		{
		  IdxMatched.push_back( 1 ) ; // index HLT
		  IdxMatched.push_back( 0 ) ;
		  deltaR_min.push_back( DeltaReco1HLT2 ) ;
		  deltaR_min.push_back( DeltaReco2HLT1 ) ;
		}  
	      // HLT-Reco Matched
	      if(verbose){
		cout << "deltaR_min 1 " << deltaR_min.at(0)  << endl;
		cout << "deltaR_min 2 " << deltaR_min.at(1)  << endl;
	      }
	      
	      // both jet matched
	      if(deltaR_min.at(0) < DeltaR_ && deltaR_min.at(1) < DeltaR_){                                                                                                      
		
		N_passMatching++;
		if(verbose) cout<< "pass Matching"<< endl;	  	      
		
		int random= -1;
		//random
		random = lrand48()%(2);

		for(int ii=0; ii<deltaR_min.size(); ii++){

		  double ptRatio;
		  if(ClosureTest){
		    ptRatio = widejetsCorr[IdxMatched.at(ii)].Pt() / widejetsReco[ii].Pt();
		  }else{
		    ptRatio = widejets[IdxMatched.at(ii)].Pt() / widejetsReco[ii].Pt();
		  }
		  
		  double ptRef ;
		  if(typeI)
		    { // pt ref : RECO
		      ptRef = widejetsReco[ii].Pt();
		    }else if(typeII)
		    { //pt ref: HLT
		      if(ClosureTest)
			{	
			  ptRef = widejetsCorr[IdxMatched.at(ii)].Pt();
			}else
			{
			  ptRef = widejets[IdxMatched.at(ii)].Pt();
			}
		    }else if(typeIII)
		    { // pt ref: RANDOM
		      if(random == 0)
			{
			  if(ClosureTest)
			    {	
			      ptRef = widejetsCorr[IdxMatched.at(ii)].Pt();
			    }else
			    {
			      ptRef = widejets[IdxMatched.at(ii)].Pt();
			    }
			}else if(random == 1)
			{
			  ptRef = widejetsReco[ii].Pt();
			}
		    }else if(typeIV)
		    { // pt ref : MEAN
		      if(ClosureTest)
			{	
			  ptRef = ( widejetsCorr[IdxMatched.at(ii)].Pt() + widejetsReco[ii].Pt() ) / 2;
			}else
			{
			  ptRef = ( widejets[IdxMatched.at(ii)].Pt() + widejetsReco[ii].Pt() ) / 2;
			}
		    }
					  
		  if( ZeroBias ){                                                                                                        
		    N_passZeroBias++;
		    CreateAndFillUserTH2D("h_ptRatio_vs_pt_ZeroBias", 56, 200, 3000, 1000, -5., 5., ptRef, ptRatio);		
		    CreateAndFillUserTProfile("p_ptRatio_vs_pt_ZeroBias",  56, 200, 3000, -5., 5., ptRef, ptRatio);		
		  }else if( DoubleMu ){                                                                                                        
		    N_passDoubleMu++;
		    CreateAndFillUserTH2D("h_ptRatio_vs_pt_DoubleMu", 56, 200, 3000, 1000, -5., 5., ptRef, ptRatio);		
		    CreateAndFillUserTProfile("p_ptRatio_vs_pt_DoubleMu",  56, 200, 3000, -5., 5., ptRef, ptRatio);		
		  }else if( CaloJet40 ){                                                                                                        
		    N_passCaloJet40++;
		    CreateAndFillUserTH2D("h_ptRatio_vs_pt_CaloJet40", 56, 200, 3000, 1000, -5., 5., ptRef, ptRatio);		 
		    CreateAndFillUserTProfile("p_ptRatio_vs_pt_CaloJet40",  56, 200, 3000, -5., 5., ptRef, ptRatio);		
		  }else if( L1HTT150 ){                                                                                                                                            
		    N_passL1HTT++;
		    CreateAndFillUserTH2D("h_ptRatio_vs_pt_L1HTT150", 56, 200, 3000, 1000, -5., 5., ptRef, ptRatio);		 
		    CreateAndFillUserTProfile("p_ptRatio_vs_pt_L1HTT150",  56, 200, 3000, -5., 5., ptRef, ptRatio);		
		  }else if( CaloScoutingHT250 ){                                                                                                                                  
		    N_passCaloScoutingHT250++;
		    CreateAndFillUserTH2D("h_ptRatio_vs_pt_CaloScoutingHT250", 56, 200, 3000, 1000, -5., 5., ptRef, ptRatio);		
		    CreateAndFillUserTProfile("p_ptRatio_vs_pt_CaloScoutingHT250",  56, 200, 3000, -5., 5., ptRef, ptRatio);		
		    CreateAndFillUserTProfileOptErrors("p_ptRatio_vs_pt_CaloScoutingHT250_OptS",  56, 200, 3000, -5., 5., ptRef, ptRatio);		
		  }
		}// for sui jet
		
		double mJJRatio;
		if(ClosureTest){
		  mJJRatio =mjjCorr / mjjreco;
		}else{
		  mJJRatio =mjj / mjjreco;
		}
		double mJJRef;
		if(typeI){ // mjj ref : RECO
		  mJJRef = mjjreco;
		}else if(typeII){ //mjj ref: HLT
		  if(ClosureTest){	
		    mJJRef = mjjCorr;
		  }else{
		    mJJRef = mjj;
		  }
		}else if(typeIII){ // mjj ref: RANDOM
		  if(random == 0){
		    if(ClosureTest){	
		      mJJRef = mjjCorr;
		    }else{
		      mJJRef = mjj;
		    }
		  }else if(random == 1){
		    mJJRef = mjjreco;
		  }
		}else if(typeIV){ // mjj ref : MEAN
		  if(ClosureTest){	
		    mJJRef = ( mjjCorr + mjjreco ) / 2;
		  }else{
		    mJJRef = ( mjj + mjjreco ) / 2;
		  }
		}	
		
		if( ZeroBias ){                                                                                                        
		  N_passZeroBias++;
		  CreateAndFillUserTH2D("h_mJJRatio_vs_mJJ_ZeroBias", 52, 450, 3050, 1000, -5., 5., mJJRef, mJJRatio);		
		  CreateAndFillUserTProfile("p_mJJRatio_vs_mJJ_ZeroBias",  52, 450, 3050, -5., 5., mJJRef, mJJRatio);		
		}else if( DoubleMu ){                                                                                                        
		  N_passDoubleMu++;
		  CreateAndFillUserTH2D("h_mJJRatio_vs_mJJ_DoubleMu", 52, 450, 3050, 1000, -5., 5., mJJRef, mJJRatio);		
		  CreateAndFillUserTProfile("p_mJJRatio_vs_mJJ_DoubleMu",  52, 450, 3050, -5., 5., mJJRef, mJJRatio);		
		}else if( CaloJet40 ){                                                                                                        
		  N_passCaloJet40++;
		  CreateAndFillUserTH2D("h_mJJRatio_vs_mJJ_CaloJet40", 52, 450, 3050, 1000, -5., 5., mJJRef, mJJRatio);		 
		  CreateAndFillUserTProfile("p_mJJRatio_vs_mJJ_CaloJet40",  52, 450, 3050, -5., 5., mJJRef, mJJRatio);		
		}else if( L1HTT150 ){                                                                                                                                            
		  N_passL1HTT++;
		  CreateAndFillUserTH2D("h_mJJRatio_vs_mJJ_L1HTT150", 52, 450, 3050, 1000, -5., 5., mJJRef, mJJRatio);		 
		  CreateAndFillUserTProfile("p_mJJRatio_vs_mJJ_L1HTT150",  52, 450, 3050, -5., 5., mJJRef, mJJRatio);		
		}else if( CaloScoutingHT250 ){                                                                                                                                  
		  N_passCaloScoutingHT250++;

		  if(ClosureTest){
		    CreateAndFillUserTH1D("h_mJJHLT_CaloScoutingHT250", 52, 450, 3050, mjjCorr );		
		  }else{
		    CreateAndFillUserTH1D("h_mJJHLT_CaloScoutingHT250", 52, 450, 3050, mjj );		
		  }
		  CreateAndFillUserTH1D("h_mJJReco_CaloScoutingHT250", 52, 450, 3050, mjjreco);		
		  
		  CreateAndFillUserTH2D("h_mJJRatio_vs_mJJ_CaloScoutingHT250", 52, 450, 3050, 1000, -5., 5., mJJRef, mJJRatio);		
		  CreateAndFillUserTProfile("p_mJJRatio_vs_mJJ_CaloScoutingHT250",  52, 450, 3050, -5., 5., mJJRef, mJJRatio);		
		  CreateAndFillUserTProfileOptErrors("p_mJJRatio_vs_mJJ_CaloScoutingHT250_OptS",  52, 450, 3050, -5., 5., mJJRef, mJJRatio);		
		}

	      }// Matching	    
	    }// deltaETA JJ
	  }// deltaPhiJJ
	}// jetID	
      }//trigger
    } // passJson
    
    /////////////////////////////////////////////////////////////////
    
    //== Fill Variables ==
    fillVariableWithValue("PassJSON", PassJSON);     
    fillVariableWithValue("MJJ_reco", mjjreco);     
    fillVariableWithValue("MJJ", mjj);     
    fillVariableWithValue("deltaETAjj_reco", deltaETAjjreco);     
    fillVariableWithValue("deltaETAjj", deltaETAjj);     
    
    ////////////////////////////////////////
    
    // Evaluate cuts (but do not apply them)
    evaluateCuts();
    
    //     if( passedAllPreviousCuts("mjj") && passedCut("mjj") ) 
    //       {
    fillReducedSkimTree();
    
    ////////////////////// User's code ends here ///////////////////////
    
  } // End loop over events
  
  //////////write histos 
  
  std::cout << "Tot events = " << N_events <<std::endl;   
  std::cout << "Pass Json = " << N_passJson <<std::endl;
  std::cout << "Pass Trigger = " << N_passTrigger <<std::endl;
  std::cout << "Pass JetID = " << N_passJetID <<std::endl;   
  std::cout << "Pass DeltaPhiJJ = " << N_passDeltaPhiJJ <<std::endl;   
  std::cout << "Pass ThirdJet Reco = " << N_passThirdJetReco <<std::endl;   
  std::cout << "Pass ThirdJet HLT = " << N_passThirdJetHLT <<std::endl;   
  std::cout << "Pass Matching = " << N_passMatching <<std::endl;   
  std::cout << "N jets = " << N_jets <<std::endl;   
  std::cout << "Pass |Eta| = " << N_passEta <<std::endl;   
  std::cout << "Pass ZeroBias = " << N_passZeroBias <<std::endl;   
  std::cout << "Pass DoubleMu = " << N_passDoubleMu <<std::endl;   
  std::cout << "Pass CaloJet40 = " << N_passCaloJet40 <<std::endl;   
  std::cout << "Pass L1HTT = " << N_passL1HTT <<std::endl;   
  std::cout << "Pass CaloScouting HT250 = " << N_passCaloScoutingHT250 <<std::endl;   		    
  std::cout << "Pass PFScouting HT410 = " << N_passPFScoutingHT410 <<std::endl;   		    

  std::cout << "analysisClass::Loop() ends" <<std::endl;   
}


/*	      
	      double DeltaRThirdJet_Reco1 = j3Reco.DeltaR(wj1Reco);
	      double DeltaRThirdJet_Reco2 = j3Reco.DeltaR(wj2Reco);
	      double DeltaRThirdJet_HLT1 = j3.DeltaR(wj1);
	      double DeltaRThirdJet_HLT2 = j3.DeltaR(wj2);
	      
	      double pTAveReco = (wj1Reco.Pt() + wj2Reco.Pt()) /2;
	      double pTAveHLT = (wj1.Pt() + wj2.Pt()) /2;
	      
	      if( DeltaRThirdJet_Reco1 > 1.1 && DeltaRThirdJet_Reco2 > 1.1 && j3Reco.Pt() > 0.3 * pTAveReco && verbose){
	      cout<< "DeltaR ThirdJet Reco1= "<<DeltaRThirdJet_Reco1 << endl; 
	      cout<< "DeltaR ThirdJet Reco2= "<<DeltaRThirdJet_Reco2 << endl; 
	      cout<< "pTAve Reco= "<<pTAveReco << endl; 
	      std::cout<<"Reco 1"<< std::endl;
	      std::cout<<"Pt: "<<pTWJ_recoj1<<" eta: "<<etaWJ_recoj1<<" phi: "<<phiWJ_recoj1<< std::endl;
	      std::cout<<"Reco 2"<< std::endl;
	      std::cout<<"Pt: "<<pTWJ_recoj2<<" eta: "<<etaWJ_recoj2<<" phi: "<<phiWJ_recoj2<< std::endl;	      
	      std::cout<<"AK4 Reco 3"<< std::endl;                                                                                                                                      
	      std::cout<<"Pt: "<< pTAK4_recoj3<<" eta: "<<etaAK4_recoj3<<" phi: "<<phiAK4_recoj3<< std::endl;
	      }
	      if( DeltaRThirdJet_Reco1 > 1.1 && DeltaRThirdJet_Reco2 > 1.1 && j3Reco.Pt() > 0.3 * pTAveReco) continue;
	      N_passThirdJetReco++;
	      if(verbose) cout<< "pass ThirdJet Reco"<< endl;

	      if( DeltaRThirdJet_HLT1 > 1.1 && DeltaRThirdJet_HLT2 > 1.1 && j3.Pt() > 0.3 * pTAveHLT && verbose){
	      cout<< "DeltaR ThirdJet HLT1= "<<DeltaRThirdJet_HLT1 << endl; 
	      cout<< "DeltaR ThirdJet HLT2= "<<DeltaRThirdJet_HLT2 << endl; 
	      cout<< "pTAve HLT= "<<pTAveHLT << endl; 
	      std::cout<<"HLT 1"<< std::endl;
	      std::cout<<"Pt: "<<pTWJ_j1<<" eta: "<<etaWJ_j1<<" phi: "<<phiWJ_j1<< std::endl;
	      std::cout<<"HLT 2"<< std::endl;
	      std::cout<<"Pt: "<<pTWJ_j2<<" eta: "<<etaWJ_j2<<" phi: "<<phiWJ_j2<< std::endl;  
	      std::cout<<"AK4 HLT 3"<< std::endl;                                                                                                                                       
	      std::cout<<"Pt: "<< pTAK4_j3<<" eta: "<<etaAK4_j3<<" phi: "<<phiAK4_j3<< std::endl;  
	      }
	      if( DeltaRThirdJet_HLT1 > 1.1 && DeltaRThirdJet_HLT2 > 1.1 && j3.Pt() > 0.3 * pTAveHLT) continue;
	      N_passThirdJetHLT++;
	      if(verbose) cout<< "pass ThirdJet HLT"<< endl;
*/
