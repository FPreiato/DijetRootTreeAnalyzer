#define analysisClass_cxx
#include "analysisClass.h"
#include <TH2.h>
#include <TH1F.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLorentzVector.h>
#include <TVector2.h>
#include <TVector3.h>
#include <TProfile.h>
#include "ptBinning.h"
#include "etaBinning.h"
#include "mJJBinning.h"
#include "vertexBinning.h"

bool verbose;
bool AK4Comparison = true;
bool WJComparison = true; 
double DeltaR_;
double alphacut_;
double DeltaEtaJJ_;
double MJJCut_;
EtaBinning mEtaBinning;
PtBinning mPtBinning; 
mJJBinning mMjjBinning; 

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
    
   if (fChain == 0) return;
   
   //////////book histos here
   double ptBins[] = {30, 100, 300, 400, 500, 600, 700, 800, 900, 1000, 1200, 1400, 1600, 1800, 2000, 2500};                                                           
   int  binnum = sizeof(ptBins)/sizeof(double) -1;                                                                                                      
   TH1F* h_pTJet_Binned = new TH1F("pTJet_Binned","pTJet", binnum, ptBins);

   //   double etaBins[] = {-2.50, -1.50, -1.25, -1.00, -0.75, -0.50, -0.25, 0.00, 0.25, 0.50, 0.75, 1.00, 1.25, 1.50, 2.50};  
   double etaBins[] = {0.00, 0.50, 1.00, 1.50, 2.50};  
   int  binnumEta = sizeof(etaBins)/sizeof(double) -1;                                                                                                      

   /////////initialize variables

   Long64_t nentries = fChain->GetEntriesFast();
   std::cout << "analysisClass::Loop(): nentries = " << nentries << std::endl;   

   ////// The following ~7 lines have been taken from rootNtupleClass->Loop() /////
   ////// If the root version is updated and rootNtupleClass regenerated,     /////
   ////// these lines may need to be updated.                                 /////    
   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) { // running over all events
     //  for (Long64_t jentry=0; jentry<5000;jentry++) { //runnig over few events
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     if(jentry < 10 || jentry%1000 == 0) std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
     //std::cout << "analysisClass::Loop(): jentry = " << jentry << std::endl;   
     // if (Cut(ientry) < 0) continue;

     //     cout<<"Evento "<< jentry << endl;

     //  First Comparison without division
     //  uso eventi pari per estrarre le calibrazioni
     //  if( (int)jentry%2 ==! 0 ) continue;
     //  uso eventi dispari per il closure test
     //  cout<< "Usato "<< jentry << endl;

     ////////////////////// User's code starts here ///////////////////////

     if( PassJSON){     

       if( IdTight_recoj1<0.5 || IdTight_recoj2<0.5 || IdTight_j1<0.5 || IdTight_j2<0.5   ) continue;                                               
       if(verbose){                                                                                                                                 
	 if( IdTight_recoj1<0.5 || IdTight_recoj2<0.5 || IdTight_j1<0.5 || IdTight_j2<0.5   ) cout<< "Id not passed"<< endl;;                       
       }    
       
       if(verbose){
	 std::cout<< std::endl;
	 std::cout<<"Start"<< std::endl;
	 std::cout<<"PassJSON "<< PassJSON<<std::endl;
	 
	 std::cout<<"WIDEJET"<< std::endl;
	 std::cout<<"Reco 1"<< std::endl;
	 std::cout<<"Pt: "<<pTWJ_recoj1<<" eta: "<<etaWJ_recoj1<<" phi: "<<phiWJ_recoj1<< std::endl;
	 std::cout<<"Reco 2"<< std::endl;
	 std::cout<<"Pt: "<<pTWJ_recoj2<<" eta: "<<etaWJ_recoj2<<" phi: "<<phiWJ_recoj2<< std::endl;
	 std::cout<<"HLT 1"<< std::endl;
	 std::cout<<"Pt: "<<pTWJ_j1<<" eta: "<<etaWJ_j1<<" phi: "<<phiWJ_j1<< std::endl;
	 std::cout<<"HLT 2"<< std::endl;
	 std::cout<<"Pt: "<<pTWJ_j2<<" eta: "<<etaWJ_j2<<" phi: "<<phiWJ_j2<< std::endl;	 
       }
       
       if( passHLT_CaloJet40_BtagSeq || passHLT_CaloJet40 || passHLT_L1HTT150_BtagSeq || passHLT_L1HTT150 || passHLT_CaloScoutingHT250 ){

	 CreateAndFillUserTH1D("mJJ_passTriggers", 30, 0, 3000, mjj); 
	 CreateAndFillUserTH1D("deltaEtaJJ_passTriggers", 100, 0, 3, deltaETAjj); 
	 
	 // #1
	 CreateAndFillUserTH1D("passHLT_CaloJet40_BtagSeq", 2 , -0.5, 1.5, passHLT_CaloJet40_BtagSeq);
	 CreateAndFillUserTH1D("passHLT_CaloJet40", 2 , -0.5, 1.5, passHLT_CaloJet40);
	 if( passHLT_CaloJet40_BtagSeq || passHLT_CaloJet40 ){
	   CreateAndFillUserTH1D("mJJ_passHLT_CaloJet40", 30, 0, 3000, mjj); 
	   CreateAndFillUserTH1D("deltaEtaJJ_passHLT_CaloJet40", 100, 0, 3, deltaETAjj); 
	 }
	 // #2
	 CreateAndFillUserTH1D("passHLT_L1HTT150_BtagSeq", 2 , -0.5, 1.5, passHLT_L1HTT150_BtagSeq);
	 CreateAndFillUserTH1D("passHLT_L1HTT150", 2 , -0.5, 1.5, passHLT_L1HTT150);
	 if( passHLT_L1HTT150_BtagSeq || passHLT_L1HTT150 ){
	   CreateAndFillUserTH1D("mJJ_passHLT_L1HTT150", 30, 0, 3000, mjj); 
	   CreateAndFillUserTH1D("deltaEtaJJ_passHLT_L1HTT150", 100, 0, 3, deltaETAjj); 
	 }
	 // #3
	 CreateAndFillUserTH1D("passHLT_CaloScoutingHT250", 2 , -0.5, 1.5,  passHLT_CaloScoutingHT250);
	 if(  passHLT_CaloScoutingHT250 ){
	   CreateAndFillUserTH1D("mJJ_passHLT_CaloScoutingHT250", 30, 0, 3000, mjj); 
	   CreateAndFillUserTH1D("deltaEtaJJ_passHLT_CaloScoutingHT250", 100, 0, 3, deltaETAjj); 
	 }
	 
	 //////////////////// end of trigger study
	     
	 vector<TLorentzVector> widejetsReco;
	 TLorentzVector wj1Reco, wj2Reco, wdijetReco; 	     
	 vector<TLorentzVector> widejets;
	 TLorentzVector wj1, wj2, wdijet; 
	 
	 //Reco
	 wj1Reco.SetPtEtaPhiM(pTWJ_recoj1, etaWJ_recoj1, phiWJ_recoj1, massWJ_recoj1);
	 wj2Reco.SetPtEtaPhiM(pTWJ_recoj2, etaWJ_recoj2, phiWJ_recoj2, massWJ_recoj2);	     
	 widejetsReco.push_back( wj1Reco );
	 widejetsReco.push_back( wj2Reco );
	 
	 //HLT
	 wj1.SetPtEtaPhiM(pTWJ_j1, etaWJ_j1, phiWJ_j1, massWJ_j1);
	 wj2.SetPtEtaPhiM(pTWJ_j2, etaWJ_j2, phiWJ_j2, massWJ_j2);
	 widejets.push_back( wj1 );
	 widejets.push_back( wj2 );
	 
	 // Compare with WIDEJETS
	 //////////// matching	 
	 double DeltaReco1HLT1 = widejetsReco[0].DeltaR(widejets[0]);
	 double DeltaReco1HLT2 = widejetsReco[0].DeltaR(widejets[1]);
	 double DeltaReco2HLT1 = widejetsReco[1].DeltaR(widejets[0]);
	 double DeltaReco2HLT2 = widejetsReco[1].DeltaR(widejets[1]);
	 
	 if(verbose){
	   cout << "WIDEJETS " << endl;
	   cout << "deltaR Reco1-HLT1 " <<  DeltaReco1HLT1 << endl;
	   cout << "deltaR Reco1-HLT2 " <<  DeltaReco1HLT2 << endl;
	   cout << "deltaR Reco2-HLT1 " <<  DeltaReco2HLT1 << endl;
	   cout << "deltaR Reco2-HLT2 " <<  DeltaReco2HLT2 << endl;
	 }       
	 
	 CreateAndFillUserTH1D("deltaR", 500, 0, 5, DeltaReco1HLT1 );
	 CreateAndFillUserTH1D("deltaR", 500, 0, 5, DeltaReco2HLT1 );
	 
	 vector<int> IdxMatched;
	 vector<double> deltaR_min;
	 if( DeltaReco1HLT1 <= DeltaReco2HLT1 )
	   {
	     IdxMatched.push_back( 0 ) ; // index Reco
	       IdxMatched.push_back( 1 ) ;
	       deltaR_min.push_back( DeltaReco1HLT1 ) ;
	       deltaR_min.push_back( DeltaReco2HLT2 ) ;
	   }else
	   {
	     IdxMatched.push_back( 1 ) ; // index Reco
	     IdxMatched.push_back( 0 ) ;
	     deltaR_min.push_back( DeltaReco2HLT1 ) ;
	     deltaR_min.push_back( DeltaReco1HLT2 ) ;
	   }
	 	       
	   if(verbose){
	     std::cout<<"DeltaR min 0= "<<deltaR_min.at(0) << std::endl;
	     std::cout<<"DeltaR min 1= "<<deltaR_min.at(1) << std::endl;
	     std::cout<<"deltaEtaCut_ = "<< DeltaEtaJJ_ << std::endl;
	     std::cout<<"MJJCut_ = "<< MJJCut_ << std::endl;
	   }	     

	   //chiedo entrambi i jet matcheati per studiare variabili comuni
	   if(deltaR_min.at(0) < DeltaR_ && deltaR_min.at(1) < DeltaR_){
	     if(verbose) std::cout<<"Both jets matched " << std::endl;
	     if( deltaETAjj < DeltaEtaJJ_){ // cut only on HLT
	       if(verbose) std::cout<<"deltaEta Cut Passed " << std::endl;
	       //	       if( mjj > MJJCut_ ){ //mass HLT
	       //	 if(verbose) std::cout<<"mJJCut Passed " << std::endl;
		 		 
	       CreateAndFillUserTH1D("MJJ_WideJetHLT", 30, 0, 3000, mjj );
	       CreateAndFillUserTH1D("MJJ_WideJetReco", 30, 0, 3000, mjjreco );
	       CreateAndFillUserTH2D("MJJ_WideJet", 30, 0, 3000, 30, 0, 3000, mjjreco, mjj );
	       
	       // bias per la variabile mJJ
	       // mJJ(Reco) - mJJ(HLT) / mJJ(HLT)
	       double mJJBias =  (mjjreco - mjj) / mjj;
	       if(verbose) std::cout<<"mJJ Bias= "<<mJJBias << std::endl;
	       
	       int MjjBin   = mMjjBinning.getBin( mjj );
	       std::pair<float, float> mJJBins = mMjjBinning.getBinValue( MjjBin );
	       std::string mJJBin = TString::Format("mJJ_%i_%i", (int) mJJBins.first, (int) mJJBins.second ).Data();
	       
	       if( verbose ){	       
		 cout<<"WideJet: mJJ = "<< mjj << endl;
		 cout<<"mJJBin =   "<< MjjBin <<endl;
		 cout<<"mJJBin.first  "  << mJJBins.first  << "    mJJBin.second   "<< mJJBins.second<<endl;
		 cout<<"mJJBin  "  << mJJBin.c_str() <<endl;
	       }
	       
		 CreateAndFillUserTH1D("mJJBias", 300, -2, 2, mJJBias);  

		 ////// TProfile: mJJBias vs mJJ
		 // questo e' quello importante!!! basta fittare questo e ho le correzioni
		 CreateAndFillUserTProfile("mJJBias_vs_Mjj",  30, 0., 3000., -2., 2.,  mjj, mJJBias );
		 CreateAndFillUserTProfile("mJJ_vs_MjjReco", 50, 0., 5000., 0., 5000., mjjreco, mjjreco );
		 CreateAndFillUserTProfile("mJJ_vs_MjjHLT",  50, 0., 5000., 0., 5000., mjj, mjj );	      

	       // trigger selected
		 if( passHLT_CaloJet40_BtagSeq || passHLT_CaloJet40 ) CreateAndFillUserTProfile("mJJBias_vs_Mjj_CaloJet40", 30, 0., 3000., -2., 2.,  mjj, mJJBias );  
		 if( passHLT_L1HTT150_BtagSeq || passHLT_L1HTT150 ) CreateAndFillUserTProfile("mJJBias_vs_Mjj_L1HTT", 30, 0., 3000., -2., 2.,  mjj, mJJBias ); 
		 if( passHLT_CaloScoutingHT250 ) CreateAndFillUserTProfile("mJJBias_vs_Mjj_CaloHT250", 30, 0., 3000., -2., 2.,  mjj, mJJBias ); 
		 		 
		 //	       }// mjj > mCUT	  	  
	     }// deltaEtaJJ < cut	
	   }//both matched
     	  	   
       } // triggers
     } // passJson
       
       /////////////////////////////////////////////////////////////////
     
       //== Fill Variables ==
     fillVariableWithValue("PassJSON", PassJSON);     
     fillVariableWithValue("MJJ_reco", mjjreco);     
     fillVariableWithValue("MJJ", mjj);     
     fillVariableWithValue("deltaETAjj_reco", deltaETAjjreco);     
     fillVariableWithValue("deltaETAjj", deltaETAjj);     
     //	       fillVariableWithValue("WideJet_pTBias", pTBias);     
     //	       fillVariableWithValue("AK4_pTBias", pTBias);     

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

   h_pTJet_Binned -> Write();

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



/*	     
//////////////////// analysis in bin di pT e Eta	     
EtaBinning mEtaBinning;
PtBinning mPtBinning;
	     
int etaBin = mEtaBinning.getBin( fabs(widejetsReco[IdxMatched.at(ii)].Eta() ) );
int ptBin = mPtBinning.getPtBin( widejetsReco[IdxMatched.at(ii)].Pt() );
	       
std::pair<float, float> ptBins = mPtBinning.getBinValue(ptBin);	     
	       
if(verbose){
std::pair<float, float> etaBins = mEtaBinning.getBinValue(etaBin);
cout<<"etaReco  "<< fabs(widejetsReco[IdxMatched.at(ii)].Eta() )  << "    pT Reco   "<<  widejetsReco[IdxMatched.at(ii)].Pt() <<endl;
cout<<"etaBin  "<< etaBin << "    pTBin   "<<ptBin<<endl;
cout<<"etaBin.first  "<< etaBins.first << "    etaBin.second   "<<etaBins.second<<endl;
cout<<"ptBin.first  "<< ptBins.first << "    ptBin.second   "<<ptBins.second<<endl;
}
	       
std::string etaName = mEtaBinning.getBinName(etaBin); 
std::string HistoName = TString::Format("pTBias_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
std::string HistoName2 = TString::Format("pt_WideJet_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();
	       
if(verbose) std::cout << HistoName.c_str()<< std::endl;
	       
CreateAndFillUserTH1D(HistoName.c_str(), 300, -2, 2, pTBias.at(ii));
CreateAndFillUserTH2D(HistoName2.c_str(), 300, 0, 3000, 300, 0, 3000, widejetsReco[IdxMatched.at(ii)].Pt(), widejets[ii].Pt() );
*/
//	     }// loop on jets


	   /*
	   // only for AK4: jets Asymmetry --> Resolution
	   // Asymmetry only for events with 2 matched jets 
	   if(deltaR_min.at(0) < DeltaR_ && deltaR_min.at(1) < DeltaR_ ){   

	     int random;
	     random = lrand48()%(2);
	     if(verbose) std::cout<< "random = " <<random << std::endl;
	     // Reco
	     double pTaveReco = ( ak4j1Reco.Pt() + ak4j2Reco.Pt() ) / 2;
	     if(verbose) std::cout<< "Average pT Reco = " << pTaveReco << std::endl;
	     CreateAndFillUserTH1D("pTaveReco", 30 , 0, 3000, pTaveReco);
	     
	     double alphaReco = ak4j3Reco.Pt() / pTaveReco ;
	     if(verbose) std::cout<< "alpha Reco = " << alphaReco << std::endl;
	     CreateAndFillUserTH1D("alphaReco", 100 , 0, 2, alphaReco);
	     double AsymmetryReco = 999;
	     
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
	     double Asymmetry = 999;
	       
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
		   if(alpha < alphacut_ ){	// aloha cut HLT
		    
		     if(random == 0){
		       AsymmetryReco = ( ak4j1Reco.Pt() - ak4j2Reco.Pt() ) / ( ak4j1Reco.Pt() + ak4j2Reco.Pt() ) ;
		       Asymmetry        = ( ak4j1.Pt() - ak4j2.Pt() ) / ( ak4j1.Pt() + ak4j2.Pt() ) ;
		     }else if(random == 1){
		       AsymmetryReco = ( ak4j2Reco.Pt() - ak4j1Reco.Pt() ) / ( ak4j1Reco.Pt() + ak4j2Reco.Pt() ) ; 
		       Asymmetry        = ( ak4j2.Pt() - ak4j1.Pt() ) / ( ak4j1.Pt() + ak4j2.Pt() ) ; 
		     }
		     std::string HistoNameReco = TString::Format("AsymmetryReco_%s_pT_%i_%i", etaNameReco.c_str(), (int) ptBins_Reco.first, (int) ptBins_Reco.second ).Data();	 	     
		     if(verbose) std::cout << HistoNameReco.c_str()<< std::endl;
		     if(verbose) std::cout<< "Asymmetry Reco = " << AsymmetryReco << std::endl; 
		     CreateAndFillUserTH1D(HistoNameReco.c_str(), 300, -2, 2, AsymmetryReco);
		     
		     std::string HistoName = TString::Format("Asymmetry_%s_pT_%i_%i", etaName.c_str(), (int) ptBins.first, (int) ptBins.second ).Data();	 	     
		     if(verbose) std::cout << HistoName.c_str()<< std::endl;
		     if(verbose) std::cout<< "Asymmetry  = " << Asymmetry << std::endl; 
		     CreateAndFillUserTH1D(HistoName.c_str(), 300, -2, 2, Asymmetry);
		     
		   }else{//alpha cut HLT
		     if(verbose) std::cout<< "HLT: alpha too large = "<<alpha<<std::endl;
		   }
		 }else{
		   if(verbose) std::cout<< "Reco: alpha too large = "<<alphaReco<<std::endl;
		 }
	       }// eta bin HLT
	     } // eta bin Reco
	   }// both matched jets 	     
*/
