#include "ChargeShare.hh"
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

#include "aPixel.hh"
#include <cmath>

//Constructor
aPixel::aPixel(
         G4int    CN,
	 G4int    NY,
	 G4int    NX,
	 G4double SY,
	 G4double SX,
	 G4double Csh,
	 G4double TC,
	 G4double TD,
	 G4double TW
	       )
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

//   http://blog.northcol.org/2012/01/14/mdarray/
    pixelData = new double*[NPixY];
    for (int i = 0; i < NPixY; i++) {
      pixelData[i] = new double[NPixX];
    }

    //Charge sharing handler
    chgShare = new ChargeShare(SPixY,SPixX,Csh,0.0,20,20);

   G4NistManager* materi_Man = G4NistManager::Instance();
   G4Box* solid_PixEnvG = new G4Box("Solid_PixEnvG", (NPixX*SPixX)/2.0, (NPixY*SPixY)/2.0, (TPixCmos+TPixDepl+TPixWafer)/2.0);

   G4Material* materi_PixEnvG = materi_Man->FindOrBuildMaterial("G4_AIR");

   logVol_PixEnvG =  new G4LogicalVolume(solid_PixEnvG, materi_PixEnvG, "LogVol_PixEnvG");
   //   logVol_PixEnvG->SetVisAttributes (G4VisAttributes::Invisible);    The outer envelope is visible

// Define 'Pixel Detector' - Local Envelop (divided the global envelop in Y-direction)
   // Define the shape of the local envelop
   G4Box* solid_PixEnvL = new G4Box("Solid_PixEnvL", (NPixX*SPixX)/2.0, SPixY/2.0, (TPixCmos+TPixDepl+TPixWafer)/2.0);
 
   // Define logical volume of the local envelop
   G4Material* materi_PixEnvL = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_PixEnvL = new G4LogicalVolume(solid_PixEnvL, materi_PixEnvL, "LogVol_PixEnvL");
   logVol_PixEnvL->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of the local envelop to the global envelop using Replica
   new G4PVReplica("PhysVol_PixEnvL", logVol_PixEnvL, logVol_PixEnvG, kYAxis,      NPixY , SPixY);

// Define 'Pixel Detector' - Pixel Element (divided the local envelop in X-direction)
   // Define the shape of the pixel element
   G4Box* solid_PixElmt = new G4Box("Solid_PixElmt", SPixX/2.0, SPixY/2.0, (TPixCmos+TPixDepl+TPixWafer)/2.0);

   // Define logical volume of the pixel element
//   G4Material* materi_PixElmt = materi_Man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
   G4Material* materi_PixElmt = materi_Man->FindOrBuildMaterial("G4_AIR");
   G4LogicalVolume* logVol_PixElmt = new G4LogicalVolume(solid_PixElmt, materi_PixElmt, "LogVol_PixElmt");
   logVol_PixElmt->SetVisAttributes (G4VisAttributes::Invisible);

   // Placement of pixel elements to the local envelop using Replica
   G4PVReplica* physVol_PixElmt= new G4PVReplica("PhysVol_PixElmt", logVol_PixElmt, logVol_PixEnvL, kXAxis, NPixX, SPixX);
   //
// Cmos circuit made of SiO2 

   // Define the shape of the pixel element
   G4Box* solid_PixCmos = new G4Box("Solid_PixCmos", SPixX/2.0, SPixY/2.0, TPixCmos/2.0);

   G4Material* materi_PixCmos = materi_Man->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
   G4LogicalVolume* logVol_PixCmos = new G4LogicalVolume(solid_PixCmos, materi_PixCmos, "LogVol_PixCmos");
   logVol_PixCmos->SetVisAttributes (G4VisAttributes::Invisible);

// Depleted zone (signal generation)
   G4Box* solid_PixDepl = new G4Box("Solid_PixDepl", SPixX/2.0, SPixY/2.0, TPixDepl/2.0);

   G4Material* materi_PixDepl = materi_Man->FindOrBuildMaterial("G4_Si");
   G4LogicalVolume* logVol_PixDepl = new G4LogicalVolume(solid_PixDepl, materi_PixDepl, "LogVol_PixDepl");
 //  logVol_PixDepl->SetVisAttributes (G4VisAttributes::Invisible);

// Si wafer
   // Define the shape of the pixel element
   G4Box* solid_PixWafer = new G4Box("Solid_PixWafer", SPixX/2.0, SPixY/2.0, TPixWafer/2.0);

   G4Material* materi_PixWafer = materi_Man->FindOrBuildMaterial("G4_Si");
   G4LogicalVolume* logVol_PixWafer = new G4LogicalVolume(solid_PixWafer, materi_PixWafer, "LogVol_PixWafer");
   logVol_PixWafer->SetVisAttributes (G4VisAttributes::Invisible);

   //Placement of Cmos/Depl/Wafer

   //Cmos
   G4ThreeVector threeVect_LogV = G4ThreeVector(0.0, 0.0, -(TPixDepl+TPixWafer)/2);
   G4RotationMatrix rotMtrx_LogV = G4RotationMatrix();
   G4Transform3D trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   G4int copyNum_LogV = CopyNumBase;                // Set ID number of LogV
   fCmosPV= new G4PVPlacement(trans3D_LogV, "PhysVol_PixCmos", logVol_PixCmos, physVol_PixElmt, false, copyNum_LogV);
   
   //Depleted region
   threeVect_LogV = G4ThreeVector(0.0, 0.0, -(-TPixCmos+TPixWafer)/2);
   rotMtrx_LogV = G4RotationMatrix();
   trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   
   copyNum_LogV = CopyNumBase+1;                // Set ID number of LogV
   fDeplPV= new G4PVPlacement(trans3D_LogV, "PhysVol_PixDepl", logVol_PixDepl, physVol_PixElmt, false, copyNum_LogV);
   
   //Wafer
   threeVect_LogV = G4ThreeVector(0.0, 0.0, (TPixCmos+TPixDepl)/2);
   rotMtrx_LogV = G4RotationMatrix();
   trans3D_LogV = G4Transform3D(rotMtrx_LogV, threeVect_LogV);
   
   copyNum_LogV = CopyNumBase+2;                // Set ID number of LogV
   fWaferPV= new G4PVPlacement(trans3D_LogV, "PhysVol_PixWafer", logVol_PixWafer, physVol_PixElmt, false, copyNum_LogV);
   
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

void aPixel::AddDepl(G4double de, G4double dl, G4int iy, G4int ix, G4ThreeVector lp0, G4ThreeVector lp1)
 {
   if(0) return;
   fTrackLDepl += dl;
   G4double x0=lp0.getX();
   G4double y0=lp0.getY();
   G4double x1=lp1.getX();
   G4double y1=lp1.getY();

   G4double d=sqrt((x0-x1)*(x0-x1)+(y0-y1)*(y0-y1));
   G4double MINL=2*um;
   G4int NDIV=(d/MINL)+1;

   //   G4cout << "OK AppDepl length " << d/um << " NDIV=" << NDIV <<G4endl;
   //G4cout << "x0/y0/x1/y1 " << x0/um << " "  << y0/um << " "  << x1/um << " "  << y1/um << " " << G4endl;

   for(int idiv=0;idiv<NDIV;idiv++) {
     double xp=(x1*(2*idiv+1)+x0*(2*NDIV-(2*idiv+1)))/(2*NDIV);
     double yp=(y1*(2*idiv+1)+y0*(2*NDIV-(2*idiv+1)))/(2*NDIV);
     //     G4cout << "Deposite Local coordinateY/X (um) " << yp/um << "  " << xp/um << "  E=" << de/NDIV/keV << " keV " <<G4endl; 
     chgShare -> setPositionYx(yp,xp);
     for(G4int jy=-1;jy<=1;jy++) {
       if(jy+iy >=0 && jy+iy <NPixY) {
	 for(G4int jx=-1;jx<=1;jx++) {
	   if(jx+ix >=0 && jx+ix <NPixX) {
	     G4double w=chgShare -> getChargeShareYx(jy,jx);
	     pixelData[jy+iy][jx+ix] +=w*de/NDIV;
	     fEnergyDepl += w*de/NDIV;
	     //	     G4cout << "      Store JY" <<  jy+iy << "/" << jx+ix << " E=" << w*de/NDIV/keV << " keV " << G4endl;
	   }
         }
       }
     }
   }
 }
