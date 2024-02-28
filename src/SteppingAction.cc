#include "SteppingAction.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4SteppingManager.hh"
#include "G4TrackStatus.hh"
#include "G4StepStatus.hh"
#include "G4Material.hh"

#include <iostream>
#include <fstream>
#include <string>

using namespace CLHEP;

SteppingAction::SteppingAction (RunAction* run, EventAction *evt)
  : fRun(run)
  , fEvt(evt)
{}

SteppingAction::~SteppingAction()
{}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  int evt = fEvt->GetEventID();

  G4StepPoint* start = step->GetPreStepPoint();
  G4ThreeVector startXYZ = start->GetPosition();
  double startX = startXYZ[0];
  double startY = startXYZ[1];
  double startZ = startXYZ[2];
  double startE = start->GetTotalEnergy();

  G4StepPoint* end = step->GetPostStepPoint();
  G4ThreeVector endXYZ = end->GetPosition();
  double endX = endXYZ[0];
  double endY = endXYZ[1];
  double endZ = endXYZ[2];

  G4Track* tr = step->GetTrack();
  int trID = tr->GetTrackID();
  int motherID = tr->GetParentID();

  double dE = step->GetTotalEnergyDeposit();
  int cpdg = tr->GetDefinition()->GetPDGEncoding();

  //if (cpdg==11) std::cout << cpdg << "  " <<  startE << " " << dE << " " << startX << "  " << startY << "  " << startZ << "  " << start->GetMaterial()->GetName() << "  " << start->GetPhysicalVolume()->GetName() << std::endl;
  //std::cout << start->GetPhysicalVolume()->GetName() << "  " << end->GetPhysicalVolume()->GetName() << std::endl;
  //std::cout << "Event " << evt << " " << cpdg << " " << trID << "  " << motherID << "  " << dE << std::endl;


  fRun->FillTree(evt,
		 cpdg,
		 trID,
		 motherID,
		 startE,
		 dE,
		 startX,
		 startY,
		 startZ,
		 endX,
		 endY,
		 endZ);

  /*
  // Drifting charge to channel readout;
  double avgX = 0.5*(startX+endX);
  int iX = (avgX+150.) / (300./nPixPerSide);
  double avgY = 0.5*(startY+endY);
  int iY = (avgY+150.) / (300./nPixPerSide);

  if (start->GetPhysicalVolume()->GetName()!="larDriftVol" || start->GetPhysicalVolume()->GetName()!="larDriftVol") return;

  //if (dE>0.1) std::cout << "Filling " << dE << std::endl;

  double Zlo = std::min(startZ,endZ);
  double Zhi = std::max(startZ,endZ);

  Zlo += 150;
  Zhi += 150;

  if (Zlo <   0. && Zhi <   0.) return;
  if (Zhi > 300. && Zlo > 300.) return;

  int iTlo = Zlo*1e-3 / driftSpeed / 1e-6; // convert mm -> m
  int iThi = Zhi*1e-3 / driftSpeed / 1e-6;

  // Drift the ionization charge
  // Split the Z-extent of the charge into time ticks, and take the fraction
  // of the step that lies in vdrft * time tick
  for (int iT = iTlo; iT <= iThi; iT++){
    if (iT < 0 || iT > 75) continue;

    double frac = 0;

    double curZlo = 1e3 * 1e-6 * iT * driftSpeed;
    double curZhi = 1e3 * 1e-6 * (iT+1) * driftSpeed;

    if (curZlo < Zlo && curZhi > Zhi) frac = 1;
    else if (curZlo < Zlo)            frac = (curZhi-Zlo)/(Zhi-Zlo);
    else if (curZhi > Zhi)            frac = (Zhi-curZlo)/(Zhi-Zlo);
    else                              frac = (curZhi-curZlo)/(Zhi-Zlo);

    //if (iT==0) std::cout << "Pt " << Zlo << "  " << Zhi << "  " << iT << " " << curZlo << " " << curZhi  << "  " << dE << "  " << frac << std::endl;


    fEvt->AddEDep(iX,iY,iT,dE*frac);
  } */

}



