#include "IOV.h"

namespace jec{

void IOV::add(string id, int runmin, int runmax, bool isdata) {

    // sanity checks to avoid IOV overlaps
    assert(runmax>=runmin);
    assert(jecs.find(runmin)==jecs.end());
    for (IOVmap::const_iterator it = jecs.begin(); it != jecs.end(); ++it) {
      if (it->first < runmin) assert(it->second.first < runmin);
      if (it->first > runmin) assert(it->first > runmax);
    }

    const char *s;
    const char *dir = "data/Spring16_25nsV10_DATA/";
    const char *tag = "Spring16_25nsV10";
    const char *dtype = "_DATA";
    const char *a = "AK4PFchs";
    
    JetCorrectorParameters *par_l1;
    JetCorrectorParameters *par_l2;
    JetCorrectorParameters *par_l3;

    if(_algo=="AK4PFchs")
      {      
	//	std::cout<<"Sono dentro IOV for PFReco" << std::endl;
	// L1FastJet
	s = Form("%s%s%s%s_L1FastJet_%s.txt",dir,tag,id.c_str(),dtype,a); cout<<s<<endl<<flush;
	par_l1 = new JetCorrectorParameters(s);
	// L2Relative
	s = Form("%s%s%s%s_L2Relative_%s.txt",dir,tag,id.c_str(),dtype,a); cout<<s<<endl<<flush;
	par_l2 = new JetCorrectorParameters(s);
	// L3Absolute
	s = Form("%s%s%s%s_L3Absolute_%s.txt",dir,tag,id.c_str(),dtype,a); cout<<s<<endl<<flush;
	par_l3 = new JetCorrectorParameters(s);   

      }else if(_algo=="AK4CaloHLT")
      {
	//	std::cout<<"Sono dentro IOV for CaloHLT" << std::endl;
	// L1FastJet
	s = Form("data/80X_dataRun2_HLT_frozen_v12/80X_dataRun2_HLT_frozen_v12_L1FastJet_AK4CaloHLT.txt"); cout<<s<<endl<<flush;
	par_l1 = new JetCorrectorParameters(s);
	// L2Relative
	s = Form("data/80X_dataRun2_HLT_frozen_v12/80X_dataRun2_HLT_frozen_v12_L2Relative_AK4CaloHLT.txt"); cout<<s<<endl<<flush;
	par_l2 = new JetCorrectorParameters(s);
	// L3Absolute
	s = Form("data/80X_dataRun2_HLT_frozen_v12/80X_dataRun2_HLT_frozen_v12_L3Absolute_AK4CaloHLT.txt"); cout<<s<<endl<<flush;
	par_l3 = new JetCorrectorParameters(s);
      }

    // L2L3Residual
    s = Form("%s%s%s%s_L2L3Residual_%s.txt",dir,tag,id.c_str(),dtype,a); cout<<s<<endl<<flush;
    JetCorrectorParameters *par_l2l3res = new JetCorrectorParameters(s);

    vector<JetCorrectorParameters> vpar;
    vpar.push_back(*par_l1);
    vpar.push_back(*par_l2);
    vpar.push_back(*par_l3);
    if (isdata) vpar.push_back(*par_l2l3res);
    FactorizedJetCorrector *jec = new FactorizedJetCorrector(vpar);
    
    jecs[runmin] = pair<int, FactorizedJetCorrector*>(runmax, jec);
  } // add
  
  FactorizedJetCorrector *IOV::get(int run) {
    assert(jecs.size()!=0);
    for (IOVmap::const_iterator it = jecs.begin(); it != jecs.end(); ++it) {
      if (it->first <= run && run <= it->second.first)
        return it->second.second;
    }
    cout << "IOV for run " << run << " not found!!" << endl << flush;
    assert(false);
    return 0;
  } // get

} //namespace jec
