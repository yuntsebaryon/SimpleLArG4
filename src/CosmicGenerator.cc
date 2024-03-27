#include "CosmicGenerator.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"


#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"

CosmicGenerator::CosmicGenerator()
{
  idxCosmic = 0;
  fMessenger = new G4GenericMessenger(this, "/LArG4/generator/", "Primary generator control");
  auto& infileCmd = fMessenger->DeclareProperty("infile", infile, "Name of the input file");
}

CosmicGenerator::~CosmicGenerator()
{ delete fMessenger; }

void CosmicGenerator::GeneratePrimaryVertex(G4Event *evt)
{
  std::vector<int> *pdgs = 0;
  std::vector<double> *Es = 0;
  std::vector<double> *pxs = 0;
  std::vector<double> *pys = 0;
  std::vector<double> *pzs = 0;

  // std::cout << "Event " << idxMARLEY << ", input file: " << infile << std::endl;
  TFile in(infile);
  TTree *t = (TTree*)in.Get("kin");
  t->SetBranchAddress("pdg",&pdgs);
  t->SetBranchAddress("E",&Es);
  t->SetBranchAddress("px",&pxs);
  t->SetBranchAddress("py",&pys);
  t->SetBranchAddress("pz",&pzs);

  t->GetEntry(idxCosmic);

  for (int i = 0; i < int(pdgs->size()); i++){
    
    double vtxx = gRandom->Uniform(-500, 500);
    double vtxy = gRandom->Uniform(-500, 500);
    double vtxz = 700;
    // vtxx = 0.;
    // vtxy = 0.;

    G4ThreeVector vtx( vtxx*CLHEP::cm, vtxy*CLHEP::cm, vtxz*CLHEP::cm );
    //G4ThreeVector vtx(15*CLHEP::cm,15*CLHEP::cm,15*CLHEP::cm);
    G4double t0 = 0.0*CLHEP::s;

    G4PrimaryVertex *vertex = new G4PrimaryVertex(vtx, t0);
    

    std::cout << "Starting a particle " << pdgs->at(i) << "  " << Es->at(i) << std::endl;
    G4PrimaryParticle *initPart = new G4PrimaryParticle(pdgs->at(i), pxs->at(i)*CLHEP::GeV, pys->at(i)*CLHEP::GeV, pzs->at(i)*CLHEP::GeV);
    /*
      int pdg = pdgs->at(i);
      if (pdg==22) particle_definition = G4Gamma::GammaDefinition();
      if (pdg==11) particle_definition = G4Electron::ElectronDefinition();
      if (pdg==2212) particle_definition = G4Proton::ProtonDefinition();
      if (pdg==2112) particle_definition = G4Neutron::NeutronDefinition();
    */
    
    vertex->SetPrimary(initPart);
    evt->AddPrimaryVertex(vertex);
  }

  
  idxCosmic++;
  delete t;

}
