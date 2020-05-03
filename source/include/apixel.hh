#ifndef _APIXELHH 
#define _APIXELHH
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

class apixel
//class apixel:   public G4VuserLogicalVolume
 {
private:
   //Pixel properties
  G4int  NPixY;
  G4int  NPixX;
  G4double  SPixY;
  G4double  SPixX;
  G4double TPixCmos;
  G4double TPixDepl;
  G4double TPixWafer;
  G4VPhysicalVolume* fCmosPV;
  G4VPhysicalVolume* fDeplPV;
  G4VPhysicalVolume* fWaferPV;
  G4LogicalVolume* logVol_PixEnvG;
  G4int CopyNumBase;
   // Event data
  G4double **pixelData; 
   G4double  fEnergyCmos;
   G4double  fEnergyDepl;
   G4double  fEnergyWafer;
   G4double  fTrackLCmos;
   G4double  fTrackLDepl;
   G4double  fTrackLWafer;
   G4int col_dum;

public:
   apixel(
    G4int  CN,
    G4int  NY=50,
    G4int  NX=30,
    G4double SY=20.0*um,
    G4double SX=20.0*um,
    G4double TC=10.0*um,
    G4double TD=50.0*um,
    G4double TW=440.0*um
	  );
   ~apixel();
   G4LogicalVolume* Getlogvol();
   //inline get method
   G4int GetNPixY() ;
   G4int GetNPixX() ;
   G4VPhysicalVolume* GetCmosPV();
   G4VPhysicalVolume* GetDeplPV();
   G4VPhysicalVolume* GetWaferPV();
   void AddCmos(G4double de, G4double dl, G4int col, G4int row );
   void AddDepl(G4double de, G4double dl, G4int col, G4int row );
   void AddWafer(G4double de, G4double dl, G4int col, G4int row );
   void ClearApixel() ;
   G4double  GetECmos()  ;
   G4double  GetEDepl()  ;
   G4double  GetEWafer() ;
   G4double  GetLCmos()  ;
   G4double  GetLDepl()  ;
   G4double  GetLWafer() ;
   G4double  GetPixYX(G4int iy, G4int ix) ;
};

#endif
