#include "DetectorConstruction.hh"
#include "globals.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Sphere.hh"
#include "G4Torus.hh"
#include "G4UnitsTable.hh"
#include "G4NistManager.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "TMath.h"
#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

DetectorConstruction::DetectorConstruction(){}

DetectorConstruction::~DetectorConstruction(){}

G4VPhysicalVolume* DetectorConstruction::Construct(){

  G4bool checkOverlaps = true; //true;

  G4NistManager* nist = G4NistManager::Instance();

  // world volume

  G4NistManager* man = G4NistManager::Instance();
  G4Material* Air = man->FindOrBuildMaterial("G4_AIR");
  G4Material* Concrete = man->FindOrBuildMaterial("G4_CONCRETE");

  // vacuum as a material
  G4Material* Vac = nist->FindOrBuildMaterial("G4_Galactic");

  G4double worldRmin = 0.*m;
  G4double worldRmax = 30.0*m;
  G4double worldSPhi = 0*degree;
  G4double worldDPhi = 360*degree;
  G4double worldSTheta = 0*degree;
  G4double worldDTheta = 360*degree;

  G4Sphere* solid_world = new G4Sphere("world_sphere",
				       worldRmin,
				       worldRmax,
				       worldSPhi,
				       worldDPhi,
				       worldSTheta,
				       worldDTheta);


  G4LogicalVolume* logical_world = new G4LogicalVolume(solid_world, Vac, "logical_vol_world", 0,0,0);
  G4VPhysicalVolume* physical_world = new G4PVPlacement(0, G4ThreeVector(0,0,0), logical_world, "physical_vol_world", 0, false, 0);

  logical_world->SetVisAttributes(G4VisAttributes::GetInvisible());

  G4double a,z,density;
  G4int ncomponents, natoms;
  G4double fractionmass;
  G4double pressure;
  G4double temperature;

  // simplified Hg target

  // Argon
  G4Element* ar36  = new G4Element("Ar36", "Ar36" , z= 18., a=36.*g/mole);
  G4Element* ar38  = new G4Element("Ar38", "Ar38" , z= 18., a=38.*g/mole);
  G4Element* ar40  = new G4Element("Ar40", "Ar40" , z= 18., a=40.*g/mole);

  G4Material* ar = new G4Material("Argon",density = 1.39*g/cm3, ncomponents=3);
  ar->AddElement(ar36,fractionmass=0.3336*perCent);
  ar->AddElement(ar38,fractionmass=0.0629*perCent);
  ar->AddElement(ar40,fractionmass=99.6035*perCent);

  G4double larRadius = 46.*cm;
  G4double larH      = 61.*cm;

  G4Tubs* solid_lar = new G4Tubs("lar_volume", 0., larRadius, larH, 0., CLHEP::twopi);
  G4LogicalVolume* logical_lar = new G4LogicalVolume(solid_lar, ar, "logical_vol_lar", 0,0,0);
  G4VPhysicalVolume* LAr = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logical_lar, "physical_vol_lar", logical_world, false, 0);

  // Active volume of LArTPC
  G4double larX     = 30.*cm;
  G4double larY     = 25.*cm;
  G4double larZ     = 30.*cm;

  G4Box* solid_lartpc = new G4Box("lartpc_volume", larX, larY, larZ);
  G4LogicalVolume* logical_lartpc = new G4LogicalVolume(solid_lartpc, ar, "logical_vol_lartpc", 0, 0, 0);
  G4VPhysicalVolume* LArTPC = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logical_lartpc, "physical_vol_lartpc", logical_world, false, 0);

  // The concrete overburden
  G4double concreteX = 10.*m;
  G4double concreteY = 10.*m;
  G4double concreteZ = 2.2*m;

  G4Box* solid_concrete = new G4Box("concrete_volume", concreteX, concreteY, concreteZ);
  G4LogicalVolume* logical_concrete = new G4LogicalVolume(solid_concrete, Concrete, "logical_vol_concrete", 0, 0, 0);
  G4VPhysicalVolume* overburden = new G4PVPlacement(0, G4ThreeVector(0., 0., 4.8*m), logical_concrete, "physical_vol_concrete", logical_world, false, 0);

  return physical_world;
}
