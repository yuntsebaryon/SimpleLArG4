#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "RunAction.hh"
#include "EventRecord.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction
{
public:

  EventAction(RunAction*);
  ~EventAction();
  
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

  void AddEDep(int iX, int iY, int iZ, double edep); // added each step

  void FillEventRecord();
  void AddEDepToWireCharge(int iX, int iY, int iZ, double edep); // 1/ per evt

  int GetEventID()
  {
    return fEvtID;
  }
 
  int fEvtID;
  RunAction *fRun;
  EventRecord *fEventRecord;
  double fEDep[nPixPerSide][nPixPerSide][nSamplesPerDrift];
};

#endif

    
