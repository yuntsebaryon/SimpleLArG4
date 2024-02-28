#ifndef RunAction_h
#define RunAction_h 1

#include "G4GenericMessenger.hh"
#include "G4UserRunAction.hh"
#include "globals.hh"
#include "G4String.hh"

#include "EventRecord.hh"

class G4Run;
class TTree;
class TFile;

class RunAction : public G4UserRunAction
{
public:

  RunAction();
  ~RunAction();
  
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run*);

  void FillTree(int cevent, int cpdg, int ctrackID, int cmotherID, double cstartE, double cdE, double cstartX, double cstartY, double cstartZ, double cendX, double cendY, double cendZ);
  void AddEventRecord(EventRecord *er);

private:
  G4GenericMessenger* fMessenger = nullptr;
  G4String fOutName;
  TFile *fOutFile;
  TTree *fEdep;
  std::vector<EventRecord*> fEventRecords;
};

#endif


