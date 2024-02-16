#ifndef PrimaryGeneratorAction_hh 
#define PrimaryGeneratorAction_hh 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "MARLEYGenerator.hh"

class G4GeneralParticleSource;

class G4Event;

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {

public:

    PrimaryGeneratorAction();
    ~PrimaryGeneratorAction();

public:

    void GeneratePrimaries(G4Event*);

private:

  MARLEYGenerator* marley;

};

#endif
