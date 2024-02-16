#include "G4RunManager.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "MARLEYGenerator.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

#include "G4UIterminal.hh"
#include "G4UImanager.hh"
#include "G4UItcsh.hh"
#include "G4VisExecutive.hh"

#include "time.h"
#include <fstream>
#include <cstdlib>

#include "QGSP_BERT.hh"

int main(int argc, char **argv){
    long seed = time(0);
    G4Random::setTheSeed(seed);

    //long seed = time(0);
    //CLHEP::HepRandom::setTheSeed(seed);
    int runNumber = 0;
    int NEvents = 0;
    G4String macroName = "/Users/yuntse/work/coherent/preLArTPC/LArTPCgeant4/run.mac";

    //If the input is valid, set output file name
    G4String outFile = "out_LArTPC.root";

    NEvents = 10;
    //NEvents = GetNEvents(macroName);

    std::cout << NEvents << " events to process " << std::endl;

    G4RunManager* rm = new G4RunManager();

    DetectorConstruction* detector = new DetectorConstruction();
    rm->SetUserInitialization(detector);
    rm->SetUserInitialization(new QGSP_BERT);
    rm->Initialize();

    G4VUserPrimaryGeneratorAction* pga = new PrimaryGeneratorAction();
    RunAction* run = new RunAction("out.root");
    EventAction* evt = new EventAction(run);
    SteppingAction* step = new SteppingAction(run,evt);
    rm->SetUserAction(pga);
    rm->SetUserAction(run);
    rm->SetUserAction(evt);
    rm->SetUserAction(step);

    G4VisManager* visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UIsession* session = new G4UIterminal(new G4UItcsh);
    G4UImanager* UI = G4UImanager::GetUIpointer();

    G4String command = "/control/execute ";
    UI->ApplyCommand(command+macroName);
    session->SessionStart();

    delete session;

    delete visManager;
    delete rm;

    return 0;
}
