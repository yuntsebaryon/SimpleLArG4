#include "EventAction.hh"
#include "RunAction.hh"
#include "G4Event.hh"

EventAction::EventAction(RunAction* run)
  : fRun(run)
  , fEvtID(0)
{
  fEventRecord = new EventRecord();
}

EventAction::~EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event* evt)
{
  fEventRecord = new EventRecord();

  for (int iX = 0; iX < nPixPerSide; iX++){
    for (int iY = 0; iY < nPixPerSide; iY++){
      for (int iZ = 0; iZ < nSamplesPerDrift; iZ++){
	fEDep[iX][iY][iZ] = 0;
      }
    }
  }

  fEvtID = evt->GetEventID();
}

void EventAction::EndOfEventAction(const G4Event* evt)
{
  std::cout << "End of action" << std::endl;
  /* Yun-Tse start
  FillEventRecord();
  fRun->AddEventRecord(fEventRecord);
  Yun-Tse end */

  /*
  double t = 0;
  for (int iX = 0; iX < nPixPerSide; iX++){
    for (int iY = 0; iY < nPixPerSide; iY++){
      for (int iZ = 0; iZ < nSamplesPerDrift; iZ++){
	std::cout << iZ << " here " << fEDep[iX][iY][iZ] << std::endl;;
	t+=fEDep[iX][iY][iZ];
      }
    }
  }
  std::cout << t << std::endl;
  */
}

void EventAction::AddEDep(int iX, int iY, int iZ, double edep)
{
  fEDep[iX][iY][iZ] += edep;
}

void EventAction::FillEventRecord()
{
  for (int iX = 0; iX < nPixPerSide; iX++){
    for (int iY = 0; iY < nPixPerSide; iY++){
      for (int iZ = 0; iZ < nSamplesPerDrift; iZ++){
	fEventRecord->AddEDepToWireCharge(iX,iY,iZ,fEDep[iX][iY][iZ]);
      }
    }
  }
}
