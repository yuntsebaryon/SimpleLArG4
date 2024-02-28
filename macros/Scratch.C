#include "TFile.h"
#include "TTree.h"
#include "TGraph.h"

void Scratch()
{
  double dE;
  int event;

  TFile *in = TFile::Open("out.root");
  TTree* tr = (TTree*)gDirectory->Get("edep");
  tr->SetBranchAddress("event",&event);
  tr->SetBranchAddress("dE",&dE);

  TH2F *h2d = new TH2F("h2d","",53,0,53,53,0,53);
  TH1F *h = new TH1F("h","",40,0,1);

  for (int idx = 0; idx < 99; idx++){

    double totWorld = 0;
    for (int i = 0; i < tr->GetEntries(); i++){
      tr->GetEntry(i);
      if (std::isnan(dE)) continue;
      if (event == idx)
	totWorld += dE;
    }

    in->cd(("evt_"+std::to_string(idx)).c_str());
    double tot = 0;
    for (int i = 0; i < 30; i++){
      for (int j = 0; j < 30; j++){
	TGraph *gr = (TGraph*)gDirectory->Get(("wireCharge_"+std::to_string(i)+"_"+std::to_string(j)).c_str());
	for (int k = 0; k < 75; k++){
	  double x,y;
	  gr->GetPoint(k,x,y);
	  if (std::isnan(y)) continue;
	  tot += y;
	}
      }
    }
    std::cout << idx << "  " << tot << "  " << totWorld << std::endl;
    h2d->Fill(totWorld,tot);
    std::cout << tot/totWorld << std::endl;
    h->Fill(tot/totWorld);
  }
  std::cout << h->GetMean() << std::endl;;
  return;

  TCanvas *can = new TCanvas();
  h->GetXaxis()->SetTitle("Charge in TPC / total charge");
  h->Draw("hist");
  can->SaveAs("Fig_fracCollected_isotropic.png");

  TCanvas *can2d = new TCanvas();
  h2d->SetMarkerStyle(8);
  h2d->GetXaxis()->SetTitle("True deposited energy (MeV)");
  h2d->GetXaxis()->CenterTitle();
  h2d->GetYaxis()->SetTitle("True collected energy (MeV)");
  h2d->GetYaxis()->CenterTitle();
  h2d->Draw("hist");
  can2d->SaveAs("Fig_migration_isotropic.png");
}
