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
   G4int GetNPixY() const;
   G4int GetNPixX() const;
   const G4VPhysicalVolume* GetCmosPV() const;
   const G4VPhysicalVolume* GetDeplPV() const;
   const G4VPhysicalVolume* GetWaferPV() const;
   void AddCmos(G4double de, G4double dl, G4int col, G4int row );
   void AddDepl(G4double de, G4double dl, G4int col, G4int row );
   void AddWafer(G4double de, G4double dl, G4int col, G4int row );
   void ClearApixel() ;
   G4double  GetECmos()  const;
   G4double  GetEDepl()  const;
   G4double  GetEWafer() const;
   G4double  GetLCmos()  const;
   G4double  GetLDepl()  const;
   G4double  GetLWafer() const;
   G4double  GetPixYX(G4int iy, G4int ix) const;
};

inline const G4VPhysicalVolume* apixel::GetCmosPV()  const {   return fCmosPV;  }
inline const G4VPhysicalVolume* apixel::GetDeplPV()  const {  return fDeplPV; }
inline const G4VPhysicalVolume* apixel::GetWaferPV() const {  return fWaferPV; }
inline G4int apixel::GetNPixY() const  {  return NPixY; }
inline G4int apixel::GetNPixX() const  {  return NPixX; }
inline G4double  apixel::GetECmos()  const { return  fEnergyCmos; }
inline G4double  apixel::GetEDepl()  const { return  fEnergyDepl; }
inline G4double  apixel::GetEWafer() const { return  fEnergyWafer; }
inline G4double  apixel::GetLCmos()  const { return  fTrackLCmos; }
inline G4double  apixel::GetLDepl()  const { return  fTrackLDepl; }
inline G4double  apixel::GetLWafer() const { return  fTrackLWafer; }
inline G4double  apixel::GetPixYX(G4int iy, G4int ix) const { return pixelData[iy][ix];}




// inline functions

inline void apixel::AddCmos(G4double de, G4double dl, G4int iy, G4int ix) {
  fEnergyCmos += de;
  fTrackLCmos += dl;
  col_dum=iy+ix;
}

inline void apixel::AddDepl(G4double de, G4double dl, G4int iy, G4int ix ) {
  if (iy>NPixY) G4cout << "Index error iy " << iy << " > " << NPixY << G4endl;
  if (ix>NPixX) G4cout << "Index error ix " << ix << " > " << NPixX << G4endl;
  fEnergyDepl += de;
  fTrackLDepl += dl;
  pixelData[iy][ix] +=de;
}

inline void apixel::AddWafer(G4double de, G4double dl, G4int iy, G4int ix ) {
  fEnergyWafer += de;
  fTrackLWafer += dl;
  col_dum=iy+ix;
}

#endif
