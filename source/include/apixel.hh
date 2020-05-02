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
   G4int GetNPixY() const;
   G4int GetNPixX() const;
   const G4VPhysicalVolume* GetCmosPV() const;
   const G4VPhysicalVolume* GetDeplPV() const;
   const G4VPhysicalVolume* GetWaferPV() const;
};

//apixel:~apixel(){}
inline const G4VPhysicalVolume* apixel::GetCmosPV()  const {   return fCmosPV;  }
inline const G4VPhysicalVolume* apixel::GetDeplPV()  const {  return fDeplPV; }
inline const G4VPhysicalVolume* apixel::GetWaferPV() const {  return fWaferPV; }
inline G4int apixel::GetNPixY() const  {  return NPixY; }
inline G4int apixel::GetNPixX() const  {  return NPixX; }

#endif
