#ifndef APIXELHH_HH 
#define APIXELHH_HH
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
   G4LogicalVolume* Getlogvol() const {  return logVol_PixEnvG;};
   G4int GetNPixY() const {return NPixY;};
   G4int GetNPixX() const {return NPixX;};
   G4VPhysicalVolume* GetCmosPV()   const {return fCmosPV;};
   G4VPhysicalVolume* GetDeplPV()   const {return fDeplPV;};
   G4VPhysicalVolume* GetWaferPV()  const {return fWaferPV;};
   void AddCmos (G4double de, G4double dl, G4int iy, G4int ix ) { fEnergyCmos  += de; fTrackLCmos += dl;  col_dum=iy+ix;};
   void AddWafer(G4double de, G4double dl, G4int iy, G4int ix ) { fEnergyWafer += de; fTrackLWafer += dl; col_dum=iy+ix;};
   void AddDepl(G4double de, G4double dl, G4int iy, G4int ix ) {
     if (iy>NPixY) G4cout << "Index error iy " << iy << " > " << NPixY << G4endl;
     if (ix>NPixX) G4cout << "Index error ix " << ix << " > " << NPixX << G4endl;
     fEnergyDepl += de;
     fTrackLDepl += dl;
     pixelData[iy][ix] +=de;
   }

   void ClearApixel()  {
     for (int iy=0;iy<NPixY;iy++)  for (int ix=0;ix<NPixX;ix++) pixelData[iy][ix]=0.0;;
     fEnergyCmos=0.0;
     fEnergyDepl=0.0;
     fEnergyWafer=0.0;
     fTrackLCmos=0.0;
     fTrackLDepl=0.0;
     fTrackLWafer=0.0;
     col_dum=0;
   };

   G4double  GetECmos() const  { return  fEnergyCmos; } ;
   G4double  GetEDepl() const  { return  fEnergyDepl; };
   G4double  GetEWafer() const  { return  fEnergyWafer; };
   G4double  GetLCmos() const  { return  fTrackLCmos; };
   G4double  GetLDepl() const  { return  fTrackLDepl; };
   G4double  GetLWafer()  const { return  fTrackLWafer; };
   G4double  GetPixYX(G4int iy, G4int ix) const { return pixelData[iy][ix];};
};

#endif
