#include "EventRecord.hh"

#include <iostream>

EventRecord::EventRecord()
{
  for (int iX = 0; iX < nPixPerSide; iX++){
    for (int iY = 0; iY < nPixPerSide; iY++){
      fWireCharge[iX][iY] = new TGraph(nSamplesPerDrift);
      for (int iZ = 0; iZ < nSamplesPerDrift; iZ++){
	fWireCharge[iX][iY]->SetPoint(iZ,iZ,0);
      }
    }
  }
}

EventRecord::~EventRecord()
{
}

void EventRecord::AddEDepToWireCharge(int iX, int iY, int iZ, double dE)
{
  double x,y;
  fWireCharge[iX][iY]->GetPoint(iZ,x,y);
  fWireCharge[iX][iY]->SetPoint(iZ,x,y+dE);
}

void EventRecord::SaveTo(TDirectory* dir)
{
  TDirectory *cdir = gDirectory;
  dir->cd();
  for (int iX = 0; iX < nPixPerSide; iX++){
    for (int iY = 0; iY < nPixPerSide; iY++){
      fWireCharge[iX][iY]->Write(("wireCharge_"+std::to_string(iX)+"_"+std::to_string(iY)).c_str());
    }
  }
  cdir->cd();
}
