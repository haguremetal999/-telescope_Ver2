/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4RotationMatrix.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
//#include "aPixel.hh"
// For the sensitive volume
//#include "G4SDManager.hh"
//#include "SensitiveVolume.hh"
#include "DetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
  //                   ID  NX     NY   NN   Wy         Wx    sig   t(cmos)   t(depl)  t(wafer)
  fpix0    = new aPixel(10, 128,  128,  2,  8.0*um,  8.0*um,  5*um, 10*um, 50*um, 440*um);
  fpix1    = new aPixel(20, 128,  128,  2,  8.0*um,  8.0*um,  5*um, 10*um, 50*um, 440*um);
  sofist0  = new aPixel(30,  50,   50,  2, 20.0*um, 20.0*um,  5*um, 10*um, 50*um, 440*um);
  sofist1  = new aPixel(40,  50,   50,  2, 20.0*um, 20.0*um,  5*um, 10*um, 50*um, 440*um);
  fpix2    = new aPixel(50, 128,  128,  2,  8.0*um,  8.0*um,  5*um, 10*um, 50*um, 440*um);
  fpix3    = new aPixel(60, 128,  128,  2,  8.0*um,  8.0*um,  5*um, 10*um, 50*um, 440*um);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
// Define materials 
DefineMaterials();

// Define volumes
return DefineVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
// Lead material defined using NIST Manager
//auto nistManager = G4NistManager::Instance();
//nistManager->FindOrBuildMaterial("G4_Pb");

G4double a;  // mass of a mole;
G4double z;  // z=mean number of protons;  
G4double density; 
 G4String symbol;
 G4int ncomponents, natoms;
//new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
     // The argon by NIST Manager is a gas with a different density

// Vacuum
new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
	      kStateGas, 2.73*kelvin, 3.e-18*pascal);

// new G4Material("Aluminium", z=13., a=26.98*g/mole, density=2.700*g/cm3);
// new G4Material("Nitrogen", z=7.0,  a=14*g/mole, density=0.1*g/cm3);
 G4Element* Nit = new G4Element("Nitrogen",symbol="N" , z= 7., a= 14.0*g/mole);
 G4Element* Alu = new G4Element("Aluminum",symbol="Al" , z= 13., a= 26.9*g/mole);
 G4Material* AlN = new G4Material("AlN",density= 3.200*g/cm3, ncomponents=2);
 AlN->AddElement(Alu, natoms=1);
 AlN->AddElement(Nit , natoms=1);

// Print materials
G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
G4cout << "DETCON start" << G4endl;

// Get pointer to 'Material Manager'
G4NistManager* materi_Man = G4NistManager::Instance();

// Define 'World Volume'
// Define the shape of solid
G4double leng_X_World = 0.2*m;         // X-full-length of world
G4double leng_Y_World = 0.2*m;         // Y-full-length of world
G4double leng_Z_World = 0.5*m;         // Z-full-length of world
G4Box* solid_World =
 new G4Box("Solid_World", leng_X_World/2.0, leng_Y_World/2.0, leng_Z_World/2.0);

// Define logical volume
G4Material* materi_World = materi_Man->FindOrBuildMaterial("G4_AIR");
G4LogicalVolume* logVol_World =
 new G4LogicalVolume(solid_World, materi_World, "LogVol_World");
logVol_World->SetVisAttributes (G4VisAttributes::Invisible);

// Placement of logical volume
G4int copyNum_World = 0;               // Set ID number of world
G4PVPlacement* physVol_World  =
 new G4PVPlacement(G4Transform3D(), "PhysVol_World", logVol_World, 0, false, copyNum_World);

// Prepare pixel sensors
 G4LogicalVolume *lV_fpix0  = fpix0   ->Getlogvol();
 G4LogicalVolume *lV_fpix1  = fpix1   ->Getlogvol();
 G4LogicalVolume *lV_fpix2  = fpix2   ->Getlogvol();
 G4LogicalVolume *lV_fpix3  = fpix3   ->Getlogvol();
 G4LogicalVolume *lV_sofist0= sofist0 ->Getlogvol();
 G4LogicalVolume *lV_sofist1= sofist1 ->Getlogvol();

//   G4cout << "DETCON lv0/lv1=" << lV_Pixel0 << "/" <<lV_Pixel1 << G4endl;



// Placement of the pixels to the world: Put the 'global envelop'

 G4double pos_X, pos_Y, pos_Z;
 G4ThreeVector vec;
 G4RotationMatrix rot;
 G4Transform3D trans;
 G4int cN;

pos_X = 0.0*mm;
pos_Y = 0.0*mm;
pos_Z = 0.0*mm;
vec = G4ThreeVector(pos_X, pos_Y, pos_Z);
rot = G4RotationMatrix();
trans = G4Transform3D(rot, vec);
cN = 1000;    
new G4PVPlacement(trans, "PV_fpix0", lV_fpix0, physVol_World,false, cN);

pos_X =  0.0*mm;
pos_Y =  0.0*mm;
pos_Z = 30.0*mm;
vec = G4ThreeVector(pos_X, pos_Y, pos_Z);
rot =  G4RotationMatrix();
//rot.rotateZ(0*deg);
trans = G4Transform3D(rot, vec);
cN=cN+10;
new G4PVPlacement(trans, "PV_fpix1", lV_fpix1, physVol_World,false, cN);

pos_X = 0.0*cm;
pos_Y = 0.0*cm;
pos_Z = 60*mm;
vec = G4ThreeVector(pos_X, pos_Y, pos_Z);
rot = G4RotationMatrix();
trans = G4Transform3D(rot, vec);
 cN=cN+10;
 new G4PVPlacement(trans, "PV_sofist0", lV_sofist0, physVol_World,false, cN);

pos_X = 0.0*cm;
pos_Y = 0.0*cm;
pos_Z = 90*mm;
vec = G4ThreeVector(pos_X, pos_Y, pos_Z);
rot = G4RotationMatrix();
trans = G4Transform3D(rot, vec);
 cN=cN+10;
new G4PVPlacement(trans, "PV_sofist1", lV_sofist1, physVol_World,false, cN);

// Kyocera ceramic package
G4Material* AlN = materi_Man->FindOrBuildMaterial("AlN");

G4Box* AlNplate= new G4Box("AlNplate", 1.0*mm , 1.0*mm, 1.27*mm/2.0);
G4LogicalVolume* lV_AlNplate = new G4LogicalVolume(AlNplate, AlN, "AlNplate");
pos_X = 0.0*cm;
pos_Y = 0.0*cm;
pos_Z = 93*mm;
vec = G4ThreeVector(pos_X, pos_Y, pos_Z);
rot = G4RotationMatrix();
trans = G4Transform3D(rot, vec);
 cN=cN+10;
new G4PVPlacement(trans, "PV_AlNplate", lV_AlNplate, physVol_World,false, cN);



pos_X =  0.0*mm;
pos_Y =  0.0*mm;
pos_Z = 120.0*mm;
vec = G4ThreeVector(pos_X, pos_Y, pos_Z);
rot =  G4RotationMatrix();
//rot1.rotateX(45.*deg);
trans = G4Transform3D(rot, vec);
cN=cN+10;
new G4PVPlacement(trans, "PV_fpix2", lV_fpix2, physVol_World,false, cN);

pos_X =  0.0*mm;
pos_Y =  0.0*mm;
pos_Z = 150.0*mm;
vec = G4ThreeVector(pos_X, pos_Y, pos_Z);
rot =  G4RotationMatrix();
//rot.rotateX(45.*deg);
trans = G4Transform3D(rot, vec);
cN=cN+10;
new G4PVPlacement(trans, "PV_fpix3", lV_fpix3, physVol_World,false, cN);

#if 0
// Sensitive Volume

// The name is arbitrary
auto aCmos= new SensitiveVolume("Cmos_SV");
// Add sensitivity to the logical volume
logVol_PixCmos -> SetSensitiveDetector(aCmos);
//register to the SensitiveDetectorManager
   auto SDman= G4SDManager::GetSDMpointer();
   SDman->AddNewDetector(aCmos);  

// The name is arbitrary
   auto aDepl= new SensitiveVolume("Depl_SV");
// Add sensitivity to the logical volume
   logVol_PixDepl  -> SetSensitiveDetector(aDepl);
//register to the SensitiveDetectorManager
//   auto SDman= G4SDManager::GetSDMpointer();
   SDman->AddNewDetector(aDepl);  

// The name is arbitrary
   auto aWafer= new SensitiveVolume("Wafer_SV");
// Add sensitivity to the logical volume
   logVol_PixWafer  -> SetSensitiveDetector(aWafer);
//register to the SensitiveDetectorManager
//   auto SDman= G4SDManager::GetSDMpointer();
   SDman->AddNewDetector(aWafer);  
#endif

   
   
// Return the physical world
//   logVol_World->SetVisAttributes (G4VisAttributes::GetInvisible());

//  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
//  simpleBoxVisAtt->SetVisibility(true);
//  calorLV->SetVisAttributes(simpleBoxVisAtt);

  //
  // Always return the physical World
  //
   return physVol_World;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::ConstructSDandField()
{ 
  // Create global magnetic field messenger.
  // Uniform magnetic field is then created automatically if
  // the field value is not zero.
  G4ThreeVector fieldValue;
  fMagFieldMessenger = new G4GlobalMagFieldMessenger(fieldValue);
  fMagFieldMessenger->SetVerboseLevel(1);
  
  // Register the field messenger for deleting
  G4AutoDelete::Register(fMagFieldMessenger);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
