#include "PrimaryGeneratorAction.hh"
#include "globals.hh"
#include "G4GeneralParticleSource.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction(){

   cosmic = new CosmicGenerator();
}

PrimaryGeneratorAction::~PrimaryGeneratorAction(){

    delete cosmic;
}

#include "G4Event.hh"
#include "Randomize.hh"
#include "CLHEP/Random/RandomEngine.h"

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
  cosmic->GeneratePrimaryVertex(anEvent);
}
