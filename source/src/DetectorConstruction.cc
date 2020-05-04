/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
#include "DetectorConstruction.hh"

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
#include "apixel.hh"
// For the sensitive volume
//#include "G4SDManager.hh"
//#include "SensitiveVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction()
{
   Pixel0= new apixel(100);
   Pixel1= new apixel(110);
   Pixel2= new apixel(120);

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

//apixel* DetectorConstruction::Getapixel0() { return Pixel0;  }
//apixel* DetectorConstruction::Getapixel1() { return Pixel1;  }
//apixel* DetectorConstruction::Getapixel2() { return Pixel2;  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{ 
  // Lead material defined using NIST Manager
  auto nistManager = G4NistManager::Instance();
  nistManager->FindOrBuildMaterial("G4_Pb");
  
  // Liquid argon material
  G4double a;  // mass of a mole;
  G4double z;  // z=mean number of protons;  
  G4double density; 
  new G4Material("liquidArgon", z=18., a= 39.95*g/mole, density= 1.390*g/cm3);
         // The argon by NIST Manager is a gas with a different density

  // Vacuum
  new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,
                  kStateGas, 2.73*kelvin, 3.e-18*pascal);

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
   G4double leng_Z_World = 0.2*m;         // Z-full-length of world
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
     new G4PVPlacement(G4Transform3D(), "PhysVol_World", logVol_World, 0,
                       false, copyNum_World);

   // Prepare pixel sensors
   G4LogicalVolume *lV_Pixel0= Pixel0 ->Getlogvol();
   G4LogicalVolume *lV_Pixel1= Pixel1 ->Getlogvol();
   G4LogicalVolume *lV_Pixel2= Pixel2 ->Getlogvol();
   //   G4cout << "DETCON lv0/lv1=" << lV_Pixel0 << "/" <<lV_Pixel1 << G4endl;
 
// Placement of the 'Pixel0' to the world: Put the 'global envelop'
   G4double pos_X0 = 0.0*cm;
   G4double pos_Y0 = 0.0*cm;
   G4double pos_Z0 = 0.0*cm;
   G4ThreeVector vec0 = G4ThreeVector(pos_X0, pos_Y0, pos_Z0);
   G4RotationMatrix rot0 = G4RotationMatrix();
   G4Transform3D trans0 = G4Transform3D(rot0, vec0);
   G4int cN0 = 1000;    
   new G4PVPlacement(trans0, "PV_Pixel0", lV_Pixel0, physVol_World,false, cN0);




// Placement of the 'Pixel1' to the world: Put the 'global envelop'
   G4double pos_X1 = 0.0*cm;
   G4double pos_Y1 = 0.0*cm;
   G4double pos_Z1 = 3.0*cm;
   G4ThreeVector vec1 = G4ThreeVector(pos_X1, pos_Y1, pos_Z1);
   G4RotationMatrix rot1 =  G4RotationMatrix();
   rot1.rotateX(30.*deg);

   G4Transform3D trans1 = G4Transform3D(rot1, vec1);
   G4int cN1 = 1001;    
   new G4PVPlacement(trans1, "PV_Pixel1", lV_Pixel1, physVol_World,false, cN1);

// Placement of the 'Pixel2' to the world: Put the 'global envelop'
   G4double pos_X2 = 0.0*cm;
   G4double pos_Y2 = 0.0*cm;
   G4double pos_Z2 = 6.0*cm;
   G4ThreeVector vec2 = G4ThreeVector(pos_X2, pos_Y2, pos_Z2);
   G4RotationMatrix rot2 = G4RotationMatrix();
   G4Transform3D trans2 = G4Transform3D(rot2, vec2);
   G4int cN2 = 1002;    
   new G4PVPlacement(trans2, "PV_Pixel2", lV_Pixel2, physVol_World,false, cN2);





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
