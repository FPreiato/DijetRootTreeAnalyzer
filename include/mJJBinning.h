#pragma once

#include <cmath>
#include <vector>
#include <utility>

class mJJBinning {
  public:
    mJJBinning() {
      fillmJJBins();
    }

    int getBin(float mjj) {
      std::vector<std::pair<float, float> >::const_iterator it = mJJBins.begin();
      for (; it != mJJBins.end(); ++it) {
        std::pair<float, float> bin = *it;
        if (mjj >= bin.first && mjj < bin.second) {
          return it - mJJBins.begin();
        }
      }

      return -1;
    }

    size_t size() const {
      return mJJBins.size();
    }

    std::pair<float, float> getBinValue(int bin) const {
      return mJJBins[bin];
    }

    std::vector<std::pair<float, float> > getBinning(int n = -1) const {
      if (n < 0) {
        n = size();
      }
      return std::vector<std::pair<float, float> >(mJJBins.begin(), mJJBins.begin() + n);
    }

    std::vector<std::pair<float, float> > getBinning(unsigned int from, unsigned int to) const {
      if (to > size()) {
        to = size();
      }

      return std::vector<std::pair<float, float> >(mJJBins.begin() + from, mJJBins.begin() + to);
    }

    int get_mJJStep(){   
      return step_mjj;
    }


  private:
    std::vector<std::pair<float, float> > mJJBins;
    int step_mjj = 100;
    int mjj_max= 3000;

    void fillmJJBins() {

      
      // ogni bin uguale -- per adesso faccio Macrobins      
      int n_bin = mjj_max/ step_mjj;
      
      for(int jj=5; jj<n_bin ; jj++){	 
      int mjj_min = ( (jj-1)*step_mjj)+step_mjj;
      int mjj_max = (jj*step_mjj)+step_mjj;
      
      mJJBins.push_back(std::make_pair(mjj_min, mjj_max));
      }
      
      
      //      mJJBins.push_back(std::make_pair(500.,  600.));                        
      //      mJJBins.push_back(std::make_pair(600.,  700.));                        
      //      mJJBins.push_back(std::make_pair(700.,  800.));
      //      mJJBins.push_back(std::make_pair(800.,  1000.));
      //      mJJBins.push_back(std::make_pair(1000., 1100.));


    
    }
};

// if we want a variable binning

//      mJJBins.push_back(std::make_pair(60., 85.));                                                                                             
//mJJBins.push_back(std::make_pair(85., 100.));                                                                                                  
// mJJBins.push_back(std::make_pair(100., 130.));                                                                                                
// mJJBins.push_back(std::make_pair(130., 175.));                                                                                                
// mJJBins.push_back(std::make_pair(175., 250.));                                                                                                
// mJJBins.push_back(std::make_pair(250., 300.));                                                                                                
// mJJBins.push_back(std::make_pair(300., 400.));                                                                                                
// mJJBins.push_back(std::make_pair(400., 1100.));
