#pragma once

#include <cmath>
#include <vector>
#include <utility>

class PtBinning {
  public:
    PtBinning() {
      fillPtBins();
    }

    int getPtBin(float pt) {
      std::vector<std::pair<float, float> >::const_iterator it = mPtBins.begin();
      for (; it != mPtBins.end(); ++it) {
        std::pair<float, float> bin = *it;
        if (pt >= bin.first && pt < bin.second) {
          return it - mPtBins.begin();
        }
      }

      return -1;
    }

    size_t size() const {
      return mPtBins.size();
    }

    std::pair<float, float> getBinValue(int bin) const {
      return mPtBins[bin];
    }

    std::vector<std::pair<float, float> > getBinning(int n = -1) const {
      if (n < 0) {
        n = size();
      }
      return std::vector<std::pair<float, float> >(mPtBins.begin(), mPtBins.begin() + n);
    }

    std::vector<std::pair<float, float> > getBinning(unsigned int from, unsigned int to) const {
      if (to > size()) {
        to = size();
      }

      return std::vector<std::pair<float, float> >(mPtBins.begin() + from, mPtBins.begin() + to);
    }

    //    int get_PtStep(){   
    //   return step_pt;
    // }


  private:
    std::vector<std::pair<float, float> > mPtBins;
<<<<<<< HEAD
    int step_pt = 200;
    int pT_max= 5000;
=======
    //    int step_pt = 100;
    //    int pT_max= 3000;
>>>>>>> da78e7f5b677718b9fbbdc988cf98717054e0e18

    void fillPtBins() {
      
      int n_bin = pT_max/ step_pt;

      for(int jj=0; jj<n_bin ; jj++){	 
	int pt_min = ( (jj-1)*step_pt)+step_pt;
	int pt_max = (jj*step_pt)+step_pt;
	
      mPtBins.push_back(std::make_pair(pt_min, pt_max));
<<<<<<< HEAD
=======
      }
      */

      //  double ptBins[] = {60, 140, 190, 215, 240, 270, 300, 390, 10000};                                                           
      
      mPtBins.push_back(std::make_pair(30. , 100.));                        
      mPtBins.push_back(std::make_pair(100., 300.));                        
      mPtBins.push_back(std::make_pair(300., 400.)); 
      mPtBins.push_back(std::make_pair(400., 500.));                                               
      mPtBins.push_back(std::make_pair(500., 600.));                                               
      mPtBins.push_back(std::make_pair(600., 700.));
      //Per gli AK4 questo e' l'ultimo bin "buono"                                               
      mPtBins.push_back(std::make_pair(700., 800.));
      mPtBins.push_back(std::make_pair(800., 900.));
      mPtBins.push_back(std::make_pair(900., 1000.));
      mPtBins.push_back(std::make_pair(1000., 1200.));
      mPtBins.push_back(std::make_pair(1200., 1400.));
      mPtBins.push_back(std::make_pair(1400., 1600.));
      mPtBins.push_back(std::make_pair(1600., 1800.));
      mPtBins.push_back(std::make_pair(1800., 2000.)); 
      // bin 200 - Inf
      mPtBins.push_back(std::make_pair(2000., 2500.)); 
      
    }
};
>>>>>>> da78e7f5b677718b9fbbdc988cf98717054e0e18

	}
    } 
};

      //      mPtBins.push_back(std::make_pair(60., 85.));
      //mPtBins.push_back(std::make_pair(85., 100.));
      // mPtBins.push_back(std::make_pair(100., 130.));
      // mPtBins.push_back(std::make_pair(130., 175.));
      // mPtBins.push_back(std::make_pair(175., 250.));
      // mPtBins.push_back(std::make_pair(250., 300.));
      // mPtBins.push_back(std::make_pair(300., 400.));
      // mPtBins.push_back(std::make_pair(400., 1100.));
