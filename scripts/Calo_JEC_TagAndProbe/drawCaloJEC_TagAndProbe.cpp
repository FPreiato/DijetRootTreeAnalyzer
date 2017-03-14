#include <stdlib.h>
#include <sys/stat.h>  
#include <time.h>
#include "TParameter.h"
#include "TPaveText.h"
#include "TError.h"
#include "TFormula.h"
#include "TH1D.h"
#include "TH1F.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include "drawBase.h"
#include "ptBinning.h"
#include "etaBinning.h"
#include <TColor.h>

int main(int argc, char* argv[]) {

  std::string outputDir = "Plot";                 
  mkdir(outputDir.c_str(), 0777); 

  // hadd of the other files (Separated Triggers)
  TFile *f = new TFile("CaloJEC_TagAndProbeMethod_DifferentTrigger.root","READ");
  //TFile *f = new TFile("CaloJEC_TagAndProbeMethod_ClosureTest_DifferentTrigger.root","READ");

  if (f) {
    std::cout << "Opened data file" << std::endl;
  }

  gErrorIgnoreLevel = kWarning;

  // List available triggers
  vector<string> triggers;
  // triggers.push_back("_ZeroBias"); //
  triggers.push_back("_L1HTT150");
  triggers.push_back("_CaloScoutingHT250");
  map<string, pair<double,double> > trgthr;
  // trgthr["_ZeroBias"] =         pair<double,double>(60,150); //
  trgthr["_L1HTT150"] =          pair<double,double>(150,300);
  trgthr["_CaloScoutingHT250"] = pair<double,double>(300,3000);

  //  const int np = 2;
  const int np = triggers.size();
  TProfile *vct[np], *vpt[np], *vcp[np], *vc[np];
  for (int i = 0; i != np; ++i) {

    const char *t = triggers[i].c_str();
    vct[i] = (TProfile*)f->Get(Form("RatioCaloTag_vs_Tag%s",t)); //assert(vct[i]);
    vpt[i] = (TProfile*)f->Get(Form("RatioPFTag_vs_Tag%s",t));   //assert(vpt[i]);
    vcp[i] = (TProfile*)f->Get(Form("RatioProbe_vs_Tag%s",t));   //assert(vcp[i]);
    vc[i]  = (TProfile*)f->Get(Form("CaloProbe_vs_Tag%s",t));    //assert(vc[i]);
  }

  // Create tag-and-probe graph
  const int nmin = 10;//2;//10;
  TGraphErrors *g = new TGraphErrors(0);
  TGraphErrors *gf = new TGraphErrors(0);
  gf -> SetName("JEC_effectiveTriggers");
  for (int itrg = 0; itrg != np; ++itrg) {
    
    string t = triggers[itrg];
    std::cout << t.c_str() << std::endl;
    TProfile *ct = vct[itrg];
    TProfile *pt = vpt[itrg];
    TProfile *cp = vcp[itrg];
    TProfile *c  = vc[itrg];

    std::cout <<"TGraph Points" << std::endl;
    for (int i = 1; i != cp->GetNbinsX()+1; ++i) {

      cout << cp->GetBinLowEdge(i) << ", ";
      if (cp->GetBinEntries(i)>=nmin) {

	// All points
	int n = g->GetN();
	g->SetPoint(n, c->GetBinContent(i),
		    100.*(ct->GetBinContent(i) / pt->GetBinContent(i) - 1));
	g->SetPointError(n, c->GetBinError(i),
			 100.*max(0.028,cp->GetBinError(i)) /
			 sqrt(cp->GetBinEntries(i)));
	
	std::cout <<"x = " << c->GetBinContent(i) << " y = " << ct->GetBinContent(i) / pt->GetBinContent(i) << std::endl;
	
	// Only ones for effective triggers
	double x = c->GetBinContent(i);
	if (x >= trgthr[t].first && x < trgthr[t].second) {
	  int m = gf->GetN();
	  cout<< g->GetX()[n] << endl;
	  cout<< g->GetY()[n] << endl;
	  gf->SetPoint(m, g->GetX()[n], g->GetY()[n]);
	  gf->SetPointError(m, g->GetEX()[n], g->GetEY()[n]);
	}
      }
    }
    cout << cp->GetBinLowEdge(cp->GetNbinsX()+1) << endl;
  }

  // Background histogram for easy graphics settings
  TH1D *h = new TH1D("h",";#LTp_{T,HLT}#GT (GeV);"
		     "#LTp_{T,HLT}#GT / #LTp_{T,RECO}#GT - 1 (%)",
		     4000,0,4000);//2037, 0, 2037);
  h->SetMinimum(-6.5);//0.97);
  h->SetMaximum(1);//1.03);
  h->GetXaxis()->SetRangeUser(50,4000);
  h->GetXaxis()->SetMoreLogLabels();
  h->GetXaxis()->SetNoExponent();
  
  // Test suitable fit
  // TF1 *f1 = new TF1("f1","[0]+[1]*pow(0.001*x,[2])",160, 2000);//90,2037);
  // f1->SetParameters(-0.5, 1, -2.5);//(-0.7,0.6, -0.7);//-0.5,1,-2.5);
  //f1->FixParameter(2, -1);
  
  // 76X
  // TF1 *f1 = new TF1("f1","[0]+[1]*pow(x,[2])+[3]/x+gaus(4)",160,2000);
  // f1->SetParameters(0,-2,-0.7, -0.5, 1, 400,100); // 80X
  // f1->SetParameters(0,-2,-1, -1, 1, 300,50); // 80X
  // f1->SetParameters(0,-2,-0.7, -0.6, 2, 500,200); // 80X
  
  // TF1 *f1 = new TF1("f1","[0]+[1]*pow(x,[2])",160,2000);
  //f1->SetParameters(-2.5, -2, -0.7); // 80X
  //f1->FixParameter(0,-2.2); // 80X
  //f1->SetParLimits(1,-5,5); // 80X

  ////////////////////////////
  // f1->SetParameters(0.404, -5, -0.19, -0.5, 1.15, 399, 252); // 80X
  // f1->SetParameters(-0.63,63.6,-1, 0, 0,0,0); // 74X
  // f1->FixParameter(2,-1); // 74X
  // f1->FixParameter(3,0); // 74X
  // f1->FixParameter(4,0); // 74
  
  // Latest function used
  // TF1 *f1 = new TF1("f1","[0]+[1]*log(x) + [2]*log(x)*log(x)",160,2100);
  // f1->SetParameters(-0.5, 10, -0.5);
 
  // new function by Mikko
  // 2016 Full Dataset
  // TF1 *f1 = new TF1("f1","[0]*pow(x,[1]) + [2]*pow(max(0.,log(x/700.)),1.2)",180,2500);
  // f1->SetParameters(-142.3,-0.682,-0.375);

  // Testing a sigmoide
  TF1* f1 = new TF1("f1"," [0]*( [3] + TMath::Erf( (x-[1])/[2] ))", 0, 2500); 
  f1->SetParameters(10., -130., 250., -1.);

  gf -> Fit(f1,"RN");


  // Create nice canvas for money plot
  //  lumi_13TeV = "CaloScouting 1.9 fb^{-1}";

  TPaveText *fitlabel = new TPaveText(0.20, 0.15, 0.65, 0.30, "brNDC");
  fitlabel->SetTextSize(0.02);
  fitlabel->SetFillColor(0);
  //  TString fitLabelText0 = TString::Format("[p0]+[p1]*pow(x,[p2])+[p3]/x+[p4]*exp(-0.5*((x-[p5])/[p6])*((x-[p5])/[p6]))");
  TString fitLabelText0 = TString::Format("[p0]+[p1]*log(x)+[p2]*log(x)*log(x)");
  TString fitLabelText1 = TString::Format("p0 = %1.3g, p1 = %1.3g, p2 = %1.3g",
					  f1->GetParameter(0), f1->GetParameter(1), f1->GetParameter(2) );
  TString fitLabelText2 = TString::Format("#chi^{2} / NDF = %1.1f / %d",
  					  f1->GetChisquare(), f1->GetNDF());
  fitlabel->AddText(fitLabelText0);
  fitlabel->AddText(fitLabelText1);
  fitlabel->AddText(fitLabelText2);

  std::cout<< f1->GetChisquare() << "/" << f1->GetNDF() << std::endl;

  TLegend *leg = new TLegend(0.50,0.78,0.80,0.90);
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->SetFillStyle(0);
  leg->AddEntry(gf,"Data","PL");
  leg->AddEntry(f1,"Fit","L");

  ////////////////////////////// canvas

  TCanvas *c1 = new TCanvas("c1","",800,800); 

  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0); 
  pad1->SetBottomMargin(0); // Upper and lower plot are joined                                                                                      
  // pad1->SetGridx();         // Vertical grid                                                                                                        
  pad1->Draw();             // Draw the upper pad: pad1                                                                                             
  pad1->cd();
  
  gPad->SetLogx();
  h->SetStats(0);
  h->SetLineColor(kWhite);
  h->Draw();
  gf    -> SetMarkerStyle(20);      
  gf    -> Draw("Psame");      

  f1 -> Draw("SAME");
  //  fitlabel->Draw("same");
  leg->Draw();
  
  c1->cd();          // Go back to the main canvas before defining pad2                                                                              
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);                                                                                           
  pad2->SetTopMargin(0);                                                                                                                            
  pad2->SetBottomMargin(0.3);                   
  pad2->SetGridx(); // vertical grid                                                                                                                
  pad2->SetGridy(); // vertical grid                                                                                                                
  pad2->Draw();                                                                                                                                     
  pad2->cd();       // pad2 becomes the current pad 
  
  //Residual graph
  TGraphErrors *g_residual = new TGraphErrors(0);

  double ptBins[] = {0, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 450, 500, 550, 600, 650, 700, 800, 900, 1000, 1200, 1400, 1600, 1800, 2000, 2500,4000};
  int  binnum = sizeof(ptBins)/sizeof(double) -1;

  TH1F *h_fit_residual_vs_pT = new TH1F("h_fit_residual_vs_pT"," ",binnum, ptBins);
 
  int NBins = gf->GetN();

  for(int bin=0; bin<NBins; bin++){
    //Values and errors
    
    double    x_data = gf->GetX()[bin];
    double    value_data = gf->GetY()[bin];
    double    err_data = gf->GetEY()[bin];
    double    value_fit = f1->Eval( x_data );

    cout<< "x = "<< x_data << endl;
    cout<< "value Data = "<< value_data <<" +- " << err_data << endl;
    cout<< "value Fit ="<< value_fit << endl;

    double    err_tot_data = 0;
    err_tot_data = err_data ;

    double fit_residual = (value_data - value_fit) / err_tot_data;
    double err_fit_residual = 1 ;
    
    cout<< "Residual = "<< fit_residual << endl;

    g_residual->SetPoint(bin, x_data, fit_residual);
    // g_residual->SetPointError(bin, 0, err_fit_residual);	  
    g_residual->SetPointError(bin, 0, 0);	  
 
    double hist_bin = h_fit_residual_vs_pT -> FindBin(x_data);

    h_fit_residual_vs_pT -> SetBinContent(hist_bin,fit_residual);
    //h_fit_residual_vs_pT -> SetBinError(hist_bin,err_fit_residual);
    h_fit_residual_vs_pT -> SetBinError(hist_bin, 0);

  }

  gPad->SetLogx();

  // Background histogram for easy graphics settings
  /*
  TH1D *h2 = new TH1D("h2",";#LTp_{T,HLT}#GT (GeV);"
		     "(Data-Fit)/#sigma",
		     4000,0,4000);
  h2->SetMinimum(-4);//0.97);
  h2->SetMaximum(4);//1.03);
  h2->GetXaxis()->SetRangeUser(50,4000);
  h2->GetXaxis()->SetMoreLogLabels();
  h2->GetXaxis()->SetNoExponent();

  h2->SetStats(0);
  h2->SetLineColor(kWhite);
  h2->Draw();
  */

  h_fit_residual_vs_pT->SetMinimum(-4);//0.97);
  h_fit_residual_vs_pT->SetMaximum(4);//1.03);
  h_fit_residual_vs_pT->GetXaxis()->SetRangeUser(50,4000);
  h_fit_residual_vs_pT->GetXaxis()->SetMoreLogLabels();
  h_fit_residual_vs_pT->GetXaxis()->SetNoExponent();
  h_fit_residual_vs_pT->SetStats(0);  
  
  h_fit_residual_vs_pT->GetYaxis()->SetNdivisions(210,true);
  h_fit_residual_vs_pT->SetLineWidth(1);
  h_fit_residual_vs_pT->SetFillColor(kRed);
  h_fit_residual_vs_pT->SetLineColor(kBlack);
  h_fit_residual_vs_pT->GetYaxis()->SetTitleSize(2*0.06);
  h_fit_residual_vs_pT->GetYaxis()->SetLabelSize(2*0.05);
  h_fit_residual_vs_pT->GetYaxis()->SetTitleOffset(0.3);
  h_fit_residual_vs_pT->GetYaxis()->SetTitle("#frac{(Data-Fit)}{Uncertainty}");
  h_fit_residual_vs_pT->GetXaxis()->SetTitleSize(2*0.06);
  h_fit_residual_vs_pT->GetXaxis()->SetLabelSize(2*0.05);
  h_fit_residual_vs_pT->GetXaxis()->SetTitle("#LT p_{T,HLT} #GT [GeV]");
 
  h_fit_residual_vs_pT -> Draw();

  c1 ->SaveAs("Plot/MoneyPlot_JEC.png");        
  c1 ->SaveAs("Plot/MoneyPlot_JEC.pdf");        

  TFile* outputFile= new TFile("CaloJEC_TagAndProbeMethod.root","RECREATE"); 
  outputFile->cd(); 
  gf->Write();
  outputFile->Close();   


}
