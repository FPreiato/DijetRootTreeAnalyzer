#pragma once

#include <cmath>
#include <vector>
#include <string>
#include <utility>

struct EtaBin {
  std::pair<float, float> bin;
  std::string name;
  std::string title;
};

class EtaBinning {
  public:
    EtaBinning() {
      fillEtaBins();
    }

    int getBin(float eta) const {
      //      eta = fabs(eta); // separo positivi e negativi
      std::vector<EtaBin>::const_iterator it = mEtaBins.begin();
      for (; it != mEtaBins.end(); ++it) {
        EtaBin bin = *it;
        if (eta >= bin.bin.first && eta < bin.bin.second) {
          return it - mEtaBins.begin();
        }
      }

      return -1;
    }

    std::string getBinName(int bin) const {
      return mEtaBins[bin].name;
    }

    std::string getBinTitle(int bin) const {
      return mEtaBins[bin].title;
    }

    std::pair<float, float> getBinValue(int bin) const {
      return mEtaBins[bin].bin;
    }


    size_t size() const {
      return mEtaBins.size();
    }

  private:
    std::vector<EtaBin> mEtaBins;

    void fillEtaBins() {

      EtaBin bin;
      //      bin.title = "|#eta| < 1.5";  
      /*
      bin.bin = std::make_pair(-2.5, -2.25); // #1
      bin.name = "eta_Minus_250_225";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(-2.25, -2.0); // #2
      bin.name = "eta_Minus_225_200";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(-2.0, -1.75); // #3
      bin.name = "eta_Minus_200_175";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(-1.75, -1.50); // #4
      bin.name = "eta_Minus_175_150";
      mEtaBins.push_back(bin);
*/

      bin.bin = std::make_pair(-2.50, -1.50); // #4  #1
      bin.name = "eta_Minus_250_150";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(-1.50, -1.25); // #5  #2
      bin.name = "eta_Minus_150_125";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(-1.25, -1.00); // #6  #3
      bin.name = "eta_Minus_125_100";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(-1.00, -0.75); // #7  #4
      bin.name = "eta_Minus_100_075";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(-0.75, -0.50); // #8  #5
      bin.name = "eta_Minus_075_050";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(-0.50, -0.25); // #9  #6
      bin.name = "eta_Minus_050_025";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(-0.25, 0.00); // #10  #7
      bin.name = "eta_Minus_025_000";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(0.00, 0.25); // #11  #8
      bin.name = "eta_Plus_000_025";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(0.25, 0.50); // #12  #9
      bin.name = "eta_Plus_025_050";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(0.50, 0.75); // #13  #10
      bin.name = "eta_Plus_050_075";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(0.75, 1.00); // #14  #11
      bin.name = "eta_Plus_075_100";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(1.00, 1.25); // #15  #12
      bin.name = "eta_Plus_100_125";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(1.25, 1.50); // #16  #13
      bin.name = "eta_Plus_125_150";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(1.50, 2.50); // #17  #14
      bin.name = "eta_Plus_150_250";
      mEtaBins.push_back(bin);

      /*
      bin.bin = std::make_pair(1.50, 1.75); // #17
      bin.name = "eta_Plus_150_175";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(1.75, 2.00); // #18
      bin.name = "eta_Plus_175_200";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(2.00, 2.25); // #19
      bin.name = "eta_Plus_200_225";
      mEtaBins.push_back(bin);

      bin.bin = std::make_pair(2.25, 2.50); // #20
      bin.name = "eta_Plus_225_250";
      mEtaBins.push_back(bin);
      */

    }
};
