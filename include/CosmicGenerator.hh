#ifndef CosmicGenerator_h
#define CosmicGenerator_h 1

#include "G4GenericMessenger.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"


class G4Event;

class CosmicGenerator : public G4VPrimaryGenerator
{
public:
  CosmicGenerator();
  ~CosmicGenerator();

  void GeneratePrimaryVertex(G4Event *evt);

private:
  G4GenericMessenger* fMessenger = nullptr;
  G4String infile;
  int idxCosmic;
  G4ParticleDefinition *particle_definition;
};

#endif


