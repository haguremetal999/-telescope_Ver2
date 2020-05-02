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

#include "apixel.hh"
G4LogicalVolume* apixel::Getlogvol(){return logVol_PixEnvG;}

apixel::apixel(
         G4int    CN,
	 G4int    NY,
	 G4int    NX,
	 G4double SY,
	 G4double SX,
	 G4double TC,
	 G4double TD,
	 G4double TW
	       )
//: G4LogicalVolume() 
{
    CopyNumBase=CN;
    NPixY=NY;
    NPixX=NX;
    SPixY=SY;
    SPixX=SX;
    TPixCmos=TC;
    TPixDepl=TD;
    TPixWafer=TW;

// Define 'Pixel Detector' - Global Envelop

   G4NistManager* materi_Man = G4NistManager::Instance();
   G4Box* solid_PixEnvG =
     new G4Box("Solid_PixEnvG", (NPixX*SPixX)/2.0, (NPixY*SPixY)/2.0, (TPixCmos+TPixDepl+TPixWafer)/2.0);

   // Define logical volume of the global envelop
   G4Material* materi_PixEnvG = materi_Man->FindOrBuildMaterial("G4_AIR");
   //   G4LogicalVolume* logVol_PixEnvG =
   logVol_PixEnvG =
     new G4LogicalVolume(solid_PixEnvG, materi_PixEnvG, "LogVol_PixEnvG");
   logVol_PixEnvG->SetVisAttributes (G4VisAttributes::Invisible);

// Define 'Pixel Detector' - Local Envelop (divided the global envelop in Y-direction)
   // Define the shape of the local envelop
   G4Box* solid_PixEnvL =
     new G4Box("Solid_PixEnvL", (NPixX*SPixX)/2.0, SPixY/2.0, (TPixCmos+TPixDepl+TPixWafer)/2.0);
 
   // Define logical volume of the local envelop
   G4Material* materi_PixEnvL = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_PixEnvL =
     new G4LogicalVolume(solid_PixEnvL, materi_PixEnvL, "LogVol_PixEnvL");
   //logVol_PixEnvL->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of the local envelop to the global envelop using Replica
   new G4PVReplica("PhysVol_PixEnvL", logVol_PixEnvL, logVol_PixEnvG, kYAxis,
                   NPixY , SPixY);

// Define 'Pixel Detector' - Pixel Element (divided the local envelop in X-direction)
   // Define the shape of the pixel element
   G4Box* solid_PixElmt =
     new G4Box("Solid_PixElmt", SPixX/2.0, SPixY/2.0, (TPixCmos+TPixDepl+TPixWafer)/2.0);

   // Define logical volume of the pixel element
//   G4Material* materi_PixElmt = materi_Man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
   G4Material* materi_PixElmt = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_PixElmt =
     new G4LogicalVolume(solid_PixElmt, materi_PixElmt, "LogVol_PixElmt");
   //     logVol_PixElmt->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of pixel elements to the local envelop using Replica
   G4PVReplica* physVol_PixElmt=
   new G4PVReplica("PhysVol_PixElmt", logVol_PixElmt, logVol_PixEnvL, kXAxis,
                   NPixX, SPixX);
   //
// Cmos circuit made of SiO2 

   // Define the shape of the pixel element
   G4Box* solid_PixCmos =
     new G4Box("Solid_PixCmos", SPixX/2.0, SPixY/2.0, TPixCmos/2.0);

   G4Material* materi_PixCmos = materi_Man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
   G4LogicalVolume* logVol_PixCmos =
     new G4LogicalVolume(solid_PixCmos, materi_PixCmos, "LogVol_PixCmos");

// Depleted zone (signal generation)
   G4Box* solid_PixDepl =
     new G4Box("Solid_PixDepl", SPixX/2.0, SPixY/2.0, TPixDepl/2.0);

   G4Material* materi_PixDepl = materi_Man->FindOrBuildMaterial("G4_Si");
   G4LogicalVolume* logVol_PixDepl =
     new G4LogicalVolume(solid_PixDepl, materi_PixDepl, "LogVol_PixDepl");
 //  logVol_PixDepl->SetVisAttributes (G4VisAttributes::Invisible);

// Si wafer
   // Define the shape of the pixel element
   G4Box* solid_PixWafer =
     new G4Box("Solid_PixWafer", SPixX/2.0, SPixY/2.0, TPixWafer/2.0);

   G4Material* materi_PixWafer = materi_Man->FindOrBuildMaterial("G4_Si");
   G4LogicalVolume* logVol_PixWafer =
     new G4LogicalVolume(solid_PixWafer, materi_PixWafer, "LogVol_PixWafer");
   //  logVol_PixWafer->SetVisAttributes (G4VisAttributes::Invisible);



   //Placement of Cmos/Depl/Wafer

   //Cmos
   G4ThreeVector threeVect_LogV = G4ThreeVector(0.0, 0.0, -(TPixDepl+TPixWafer)/2);
   G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();
   G4Transform3D trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   G4int copyNum_LogV = CopyNumBase;                // Set ID number of LogV
   fCmosPV= new G4PVPlacement(trans3D_LogV, "PhysVol_PixCmos", logVol_PixCmos, physVol_PixElmt,
		     false, copyNum_LogV);
   
   //Depleted region
   threeVect_LogV = G4ThreeVector(0.0, 0.0, -(-TPixCmos+TPixWafer)/2);
   rotMtrx_LogV = G4RotationMatrix();
   trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   
   copyNum_LogV = CopyNumBase+1;                // Set ID number of LogV
   fDeplPV= new G4PVPlacement(trans3D_LogV, "PhysVol_PixDepl", logVol_PixDepl, physVol_PixElmt,
		     false, copyNum_LogV);
   
   //Wafer
   threeVect_LogV = G4ThreeVector(0.0, 0.0, (TPixCmos+TPixDepl)/2);
   rotMtrx_LogV = G4RotationMatrix();
   trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   
   copyNum_LogV = CopyNumBase+2;                // Set ID number of LogV
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
  }



