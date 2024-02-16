#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"

#include "TFile.h"
#include "TTree.h"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>

RunAction::RunAction(std::string fout)
  : fOutName(fout)
{
  fOutFile = new TFile(fout.c_str(),"recreate");
  fEventRecords = {};
  //fEdep = new TTree();
}

RunAction::~RunAction(){}

int event;
int pdg;
int trackID;
int motherID;
double startE;
double dE;
double startX;
double startY;
double startZ;
double endX;
double endY;
double endZ;

void RunAction::BeginOfRunAction(const G4Run* aRun)
{
  std::cout << "Starting MARLEY run " << std::endl;;

  fEdep = new TTree();
  fEdep->Branch("event",&event);
  fEdep->Branch("pdg",&pdg);
  fEdep->Branch("trackID",&trackID);
  fEdep->Branch("motherID",&motherID);
  fEdep->Branch("startE",&startE);
  fEdep->Branch("dE",&dE);
  fEdep->Branch("startX",&startX);
  fEdep->Branch("startY",&startY);
  fEdep->Branch("startZ",&startZ);
  fEdep->Branch("endX",&endX);
  fEdep->Branch("endY",&endY);
  fEdep->Branch("endZ",&endZ);
}

void RunAction::EndOfRunAction(const G4Run* aRun)
{
  std::cout << "Ending MARLEY run " << std::endl;;
  //TFile *fout = new TFile(fOutName.c_str(),"recreate");
  fOutFile->cd();
  fEdep->Write("edep");
  /*
  std::cout << fEventRecords[0] << std::endl;
  for (int i = 0; i < int(fEventRecords.size()); i++){
    std::cout << i << " writing out EventRecord" << std::endl;
    fEventRecords[i]->Write(("evt_"+std::to_string(i)).c_str());
  }
  */
  /* Yun-Tse comment out start
  for (int i = 0; i < int(fEventRecords.size()); i++){
    fEventRecords[i]->SaveTo(fOutFile->mkdir(("evt_"+std::to_string(i)).c_str()));
  } Yun-Tse end */
  fOutFile->Close();
}

void RunAction::FillTree(int cevent,
			 int cpdg,
			 int ctrackID,
			 int cmotherID,
			 double cstartE,
			 double cdE,
			 double cstartX,
			 double cstartY,
			 double cstartZ,
			 double cendX,
			 double cendY,
			 double cendZ)
{
  event = cevent;
  pdg = cpdg;
  trackID = ctrackID;
  motherID = cmotherID;
  startE = cstartE;
  dE = cdE;
  startX = cstartX;
  startY = cstartY;
  startZ = cstartZ;
  endX = cendX;
  endY = cendY;
  endZ = cendZ;

  fEdep->Fill();
}

void RunAction::AddEventRecord(EventRecord* er)
{
  fEventRecords.push_back(er);
}
