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
#include "G4UIExecutive.hh"

#include "time.h"
#include <fstream>
#include <cstdlib>

#include "QGSP_BERT.hh"

int main(int argc, char **argv){

    // Detect interactive mode (if no arguments) and define UI session
    //
    G4UIExecutive* ui = nullptr;
    if ( argc == 1 ) { ui = new G4UIExecutive(argc, argv); }
    
    long seed = time(0);
    G4Random::setTheSeed(seed);

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

    G4UImanager* UIm = G4UImanager::GetUIpointer();

    if ( !ui ) {
        // batch mode
        G4String command = "/control/execute ";
        G4String macroName = argv[1];
        UIm->ApplyCommand(command+macroName);
    }
    else {
        // interactive mode
        UIm->ApplyCommand("/control/execute run.mac");
        ui->SessionStart();
        delete ui;
    }

    delete visManager;
    delete rm;

    return 0;
}
