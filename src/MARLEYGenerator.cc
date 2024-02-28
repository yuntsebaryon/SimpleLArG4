#include "MARLEYGenerator.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"

#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"

MARLEYGenerator::MARLEYGenerator()
{
  idxMARLEY = 0;
}

MARLEYGenerator::~MARLEYGenerator()
{}

void MARLEYGenerator::GeneratePrimaryVertex(G4Event *evt)
{
  std::vector<int> *pdgs = 0;
  std::vector<double> *Es = 0;
  std::vector<double> *pxs = 0;
  std::vector<double> *pys = 0;
  std::vector<double> *pzs = 0;

  TFile in("/Users/yuntse/work/coherent/preLArTPC/LArG4/in_MARLEY.root");
  TTree *t = (TTree*)in.Get("kin");
  t->SetBranchAddress("pdg",&pdgs);
  t->SetBranchAddress("E",&Es);
  t->SetBranchAddress("px",&pxs);
  t->SetBranchAddress("py",&pys);
  t->SetBranchAddress("pz",&pzs);

  t->GetEntry(idxMARLEY);

  double vtxx = gRandom->Uniform(-15,15);
  double vtxy = gRandom->Uniform(-15,15);
  double vtxz = gRandom->Uniform(-15,15);

  vtxx = 0;
  vtxy = 0;
  vtxz = 0;

  G4ThreeVector vtx(vtxx*CLHEP::cm,vtxy*CLHEP::cm,vtxz*CLHEP::cm);
  //G4ThreeVector vtx(15*CLHEP::cm,15*CLHEP::cm,15*CLHEP::cm);
  G4double t0 = 0.0*CLHEP::s;

  G4PrimaryVertex *vertex = new G4PrimaryVertex(vtx,t0);

  for (int i = 0; i < int(pdgs->size()); i++){
    std::cout << "Starting a particle " << pdgs->at(i) << "  " << Es->at(i) << std::endl;
    G4PrimaryParticle *initPart = new G4PrimaryParticle(pdgs->at(i),pxs->at(i)*CLHEP::MeV,pys->at(i)*CLHEP::MeV,pzs->at(i)*CLHEP::MeV);
    /*
      int pdg = pdgs->at(i);
      if (pdg==22) particle_definition = G4Gamma::GammaDefinition();
      if (pdg==11) particle_definition = G4Electron::ElectronDefinition();
      if (pdg==2212) particle_definition = G4Proton::ProtonDefinition();
      if (pdg==2112) particle_definition = G4Neutron::NeutronDefinition();
    */
    vertex->SetPrimary(initPart);
  }

  evt->AddPrimaryVertex(vertex);

  idxMARLEY++;
  delete t;

}
