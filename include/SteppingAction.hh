#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include "G4ios.hh"
#include "G4Step.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "CLHEP/Units/SystemOfUnits.h"

class RunAction;
class EventAction;
class SNSRootManager;

class SteppingAction : public G4UserSteppingAction
{
public:
  SteppingAction(RunAction*, EventAction*);
  ~SteppingAction();
  
  void UserSteppingAction(const G4Step*);
  
private:
  RunAction* fRun;
  EventAction* fEvt;   
};

#endif
