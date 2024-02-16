#ifndef MARLEYGenerator_h
#define MARLEYGenerator_h 1

#include "G4VPrimaryGenerator.hh"
#include "G4ParticleDefinition.hh"
#include "G4Event.hh"


class G4Event;

class MARLEYGenerator : public G4VPrimaryGenerator
{
public:
  MARLEYGenerator();
  ~MARLEYGenerator();

  void GeneratePrimaryVertex(G4Event *evt);

private:
  int idxMARLEY;
  G4ParticleDefinition *particle_definition;
};

#endif


