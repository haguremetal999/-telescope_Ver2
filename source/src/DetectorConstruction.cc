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

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
// For the sensitive volume
//#include "G4SDManager.hh"
//#include "SensitiveVolume.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4ThreadLocal 
G4GlobalMagFieldMessenger* DetectorConstruction::fMagFieldMessenger = nullptr; 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
 : G4VUserDetectorConstruction(),
   fCmosPV(nullptr),
   fDeplPV(nullptr),
   fWaferPV(nullptr),
   fCheckOverlaps(true)
{
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

// Define 'Pixel Detector' - Global Envelop

   G4int  nDiv_X=NPixX, nDiv_Y=NPixY;
   G4double leng_X_PixEnvG = NPixX*SPixX;     // X-full-length of pixel: global envelop
   G4double leng_Y_PixEnvG = NPixY*SPixY;     // Y-full-length of pixel: global envelop
   G4double leng_Z_PixEnvG = TPixCmos+TPixDepl+TPixWafer;     // Z-full-length of pixel: global envelop
   G4Box* solid_PixEnvG =
     new G4Box("Solid_PixEnvG", leng_X_PixEnvG/2.0, leng_Y_PixEnvG/2.0, leng_Z_PixEnvG/2.0);

   // Define logical volume of the global envelop
   G4Material* materi_PixEnvG = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_PixEnvG =
     new G4LogicalVolume(solid_PixEnvG, materi_PixEnvG, "LogVol_PixEnvG");
   logVol_PixEnvG->SetVisAttributes (G4VisAttributes::Invisible);

// Define 'Pixel Detector' - Local Envelop (divided the global envelop in Y-direction)
   // Define the shape of the local envelop
   G4double leng_X_PixEnvL = NPixX*SPixX;             // X-full-length of pixel: local envelop
   G4double leng_Y_PixEnvL = SPixY;                   // Y-full-length of pixel: local envelop
   G4double leng_Z_PixEnvL = TPixCmos+TPixDepl+TPixWafer;      // Z-full-length of pixel: local envelop

   G4Box* solid_PixEnvL =
     new G4Box("Solid_PixEnvL", leng_X_PixEnvL/2.0, leng_Y_PixEnvL/2.0, leng_Z_PixEnvL/2.0);


   // Define logical volume of the local envelop
   G4Material* materi_PixEnvL = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_PixEnvL =
     new G4LogicalVolume(solid_PixEnvL, materi_PixEnvL, "LogVol_PixEnvL");
   //logVol_PixEnvL->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of the local envelop to the global envelop using Replica
   new G4PVReplica("PhysVol_PixEnvL", logVol_PixEnvL, logVol_PixEnvG, kYAxis,
                   nDiv_Y , leng_Y_PixEnvL);

// Define 'Pixel Detector' - Pixel Element (divided the local envelop in X-direction)
   // Define the shape of the pixel element
   G4double leng_X_PixElmt = SPixX;                    // X-full-length of pixel: pixel element
   G4double leng_Y_PixElmt = SPixY;                    // Y-full-length of pixel: pixel element
   G4double leng_Z_PixElmt = TPixCmos+TPixDepl+TPixWafer;       // Z-full-length of pixel: pixel element
   G4Box* solid_PixElmt =
     new G4Box("Solid_PixElmt", leng_X_PixElmt/2.0, leng_Y_PixElmt/2.0, leng_Z_PixElmt/2.0);

   // Define logical volume of the pixel element
//   G4Material* materi_PixElmt = materi_Man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
   G4Material* materi_PixElmt = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_PixElmt =
     new G4LogicalVolume(solid_PixElmt, materi_PixElmt, "LogVol_PixElmt");
   //     logVol_PixElmt->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of pixel elements to the local envelop using Replica
   G4PVReplica* physVol_PixElmt=
   new G4PVReplica("PhysVol_PixElmt", logVol_PixElmt, logVol_PixEnvL, kXAxis,
                   nDiv_X, leng_X_PixElmt);
   //
// Pixel element = Cmos+Depl+Wafer   Define 'Pixel Detector' - Pixel Element (divided the local envelop in X-direction)

// Cmos circuit made of SiO2 

   // Define the shape of the pixel element
   G4double leng_X_PixCmos = SPixX;                    // X-full-length of pixel: pixel element
   G4double leng_Y_PixCmos = SPixY;                    // Y-full-length of pixel: pixel element
   G4double leng_Z_PixCmos = TPixCmos;                 // Z-full-length of pixel: pixel element
   G4Box* solid_PixCmos =
     new G4Box("Solid_PixCmos", leng_X_PixCmos/2.0, leng_Y_PixCmos/2.0, leng_Z_PixCmos/2.0);

   G4Material* materi_PixCmos = materi_Man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
   G4LogicalVolume* logVol_PixCmos =
     new G4LogicalVolume(solid_PixCmos, materi_PixCmos, "LogVol_PixCmos");
   //  logVol_PixCmos->SetVisAttributes (G4VisAttributes::Invisible);
   #if 0
   const G4VPhysicalVolume* GetCmosPV() const;
   const G4VPhysicalVolume* GetDeplPV() const;
   const G4VPhysicalVolume* GetWaferPV() const;
   #endif


// Depleted zone (signal generation)

   G4double leng_X_PixDepl = SPixX;                    // X-full-length of pixel: pixel element
   G4double leng_Y_PixDepl = SPixY;                    // Y-full-length of pixel: pixel element
   G4double leng_Z_PixDepl = TPixDepl;                 // Z-full-length of pixel: pixel element
   G4Box* solid_PixDepl =
     new G4Box("Solid_PixDepl", leng_X_PixDepl/2.0, leng_Y_PixDepl/2.0, leng_Z_PixDepl/2.0);

   G4Material* materi_PixDepl = materi_Man->FindOrBuildMaterial("G4_Si");
   G4LogicalVolume* logVol_PixDepl =
     new G4LogicalVolume(solid_PixDepl, materi_PixDepl, "LogVol_PixDepl");
   //  logVol_PixDepl->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of pixel elements to the local envelop using Replica
   //   new G4PVReplica("PhysVol_PixDepl", logVol_PixDepl, logVol_PixElmt, kXAxis,nDiv_X, leng_X_PixDepl);


// Si wafer

   // Define the shape of the pixel element
   G4double leng_X_PixWafer = SPixX;                    // X-full-length of pixel: pixel element
   G4double leng_Y_PixWafer = SPixY;                    // Y-full-length of pixel: pixel element
   G4double leng_Z_PixWafer = TPixWafer;                 // Z-full-length of pixel: pixel element
   G4Box* solid_PixWafer =
     new G4Box("Solid_PixWafer", leng_X_PixWafer/2.0, leng_Y_PixWafer/2.0, leng_Z_PixWafer/2.0);

   G4Material* materi_PixWafer = materi_Man->FindOrBuildMaterial("G4_Si");
   G4LogicalVolume* logVol_PixWafer =
     new G4LogicalVolume(solid_PixWafer, materi_PixWafer, "LogVol_PixWafer");
   //  logVol_PixWafer->SetVisAttributes (G4VisAttributes::Invisible);



   //Placement of Cmos/Depl/Wafer
   //Cmos
   G4double pos_X_LogV=0.0*um;
   G4double pos_Y_LogV=0.0*um;
   G4double pos_Z_LogV=-(TPixDepl+TPixWafer)/2;
   G4ThreeVector threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();
   G4Transform3D trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   
   G4int copyNum_LogV = 1000;                // Set ID number of LogV
   fCmosPV= new G4PVPlacement(trans3D_LogV, "PhysVol_PixCmos", logVol_PixCmos, physVol_PixElmt,
		     false, copyNum_LogV);
   
   //Depleted region
   pos_X_LogV=0.0*um;
   pos_Y_LogV=0.0*um;
   pos_Z_LogV=-(-TPixCmos+TPixWafer)/2;
   threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   rotMtrx_LogV = G4RotationMatrix();
   trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   
   copyNum_LogV = 2000;                // Set ID number of LogV
   fDeplPV= new G4PVPlacement(trans3D_LogV, "PhysVol_PixDepl", logVol_PixDepl, physVol_PixElmt,
		     false, copyNum_LogV);
   
   //Wafer
   pos_X_LogV=0.0*um;
   pos_Y_LogV=0.0*um;
   pos_Z_LogV=(TPixCmos+TPixDepl)/2;
   threeVect_LogV = G4ThreeVector(pos_X_LogV, pos_Y_LogV, pos_Z_LogV);
   rotMtrx_LogV = G4RotationMatrix();
   trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   
   copyNum_LogV = 3000;                // Set ID number of LogV
   fWaferPV= new G4PVPlacement(trans3D_LogV, "PhysVol_PixWafer", logVol_PixWafer, physVol_PixElmt,
      		     false, copyNum_LogV);
   
   /*
Calcuation of Z position
    |  t1  | t2  |        t3        | 
 zmin  z1    z2           Z3       zmax

zmin=-(t1+t2+t3)/2  ;   zmax=+(t1+t2+t3)/2  
z1=zmin+t1/2= -(t2+t3)
z2=zmin+t1+t2/2=(t1-t3)/2
z3=zmax-t3/2=(t1+t2)/2


    */

// Placement of the 'Pixel Detector' to the world: Put the 'global envelop'
   G4double pos_X_LogV_PixEnvG = 0.0*cm;       // X-location LogV_PixEnvG
   G4double pos_Y_LogV_PixEnvG = 0.0*cm;       // Y-location LogV_PixEnvG
   G4double pos_Z_LogV_PixEnvG = 0.0*cm;       // Z-location LogV_PixEnvG
   G4ThreeVector threeVect_LogV_PixEnvG =
     G4ThreeVector(pos_X_LogV_PixEnvG, pos_Y_LogV_PixEnvG, pos_Z_LogV_PixEnvG);
   G4RotationMatrix rotMtrx_LogV_PixEnvG = G4RotationMatrix();
   G4Transform3D trans3D_LogV_PixEnvG = G4Transform3D(rotMtrx_LogV_PixEnvG, threeVect_LogV_PixEnvG);

   G4int copyNum_LogV_PixEnvG = 4000;                // Set ID number of LogV_PixEnvG
   new G4PVPlacement(trans3D_LogV_PixEnvG, "PhysVol_PixEnvG", logVol_PixEnvG, physVol_World,
                     false, copyNum_LogV_PixEnvG);

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
  //
  // print parameters
  //
  G4cout
    << G4endl 
    << "------------------------------------------------------------" << G4endl
    << "---> The calorimeter is " << "nofLayers" << " layers of: [ "
    << "absoThickness/mm" << "mm of " << "absorberMaterial->GetName()" 
    << " + "
    << "gapThickness/mm" << "mm of " << "gapMaterial->GetName()" << " ] " << G4endl
    << "------------------------------------------------------------" << G4endl;
  
  //                                        
  // Visualization attributes
  //
//   logVol_World->SetVisAttributes (G4VisAttributes::GetInvisible());

//  auto simpleBoxVisAtt= new G4VisAttributes(G4Colour(1.0,1.0,1.0));
//  simpleBoxVisAtt->SetVisibility(true);
//  calorLV->SetVisAttributes(simpleBoxVisAtt);

  //
  // Always return the physical World
  //
   return physVol_World;
//  return worldPV;
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
