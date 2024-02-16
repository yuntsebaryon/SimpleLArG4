#ifndef EventRecord_h
#define EventRecord_h 1

#include "TGraph.h"
#include "TDirectory.h"


const int nPixPerSide = 30;
const double driftSpeed = 4 / 0.001; // Approximate from DUNE (m / ms)
const int nSamplesPerDrift = 1 + (0.30 / driftSpeed)/1e-6; // tick = 1 us

class EventRecord
{
public:
  EventRecord();
  ~EventRecord();

  void AddEDepToWireCharge(int iX, int iY, int iZ, double dE);
  void SaveTo(TDirectory *dir);

private:
  double a;
  TGraph *fWireCharge[nPixPerSide][nPixPerSide];
};


#endif
