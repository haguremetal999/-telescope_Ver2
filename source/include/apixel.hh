#ifndef APIXELHH_HH 
#define APIXELHH_HH
#include "ChargeShare.hh"
#include "G4ThreeVector.hh"

class aPixel
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
   ChargeShare* chgShare;
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
   aPixel(
    G4int  CN,        // pixel ID number 
    G4int  NY=50,     // Number of pixels in Y
    G4int  NX=50,     // Number of pixels in X
    G4double SY=20.0*um,  //Pixel size in Y
    G4double SX=20.0*um,  //Pixel size in X
    G4double CS=30.0*um,  //Charge share parameter
    G4double TC=10.0*um,  //Thickness of circuit
    G4double TD=50.0*um,  //Thickness of the depleted zone
    G4double TW=440.0*um  //Thickness of the supporting wafer
	  );
   ~aPixel();
   G4LogicalVolume* Getlogvol() const {  return logVol_PixEnvG;};
   G4int GetNPixY() const {return NPixY;};
   G4int GetNPixX() const {return NPixX;};
   G4VPhysicalVolume* GetCmosPV()   const {return fCmosPV;};
   G4VPhysicalVolume* GetDeplPV()   const {return fDeplPV;};
   G4VPhysicalVolume* GetWaferPV()  const {return fWaferPV;};
   void AddCmos (G4double de, G4double dl, G4double tt, G4int iy, G4int ix ) { fEnergyCmos  += de; fTrackLCmos += dl;  col_dum=iy+ix+tt;};
   void AddDepl(G4double de, G4double dl, G4double tt, G4int iy, G4int ix, G4ThreeVector lp0, G4ThreeVector lp1);
   void AddWafer(G4double de, G4double dl, G4double tt, G4int iy, G4int ix ) { fEnergyWafer += de; fTrackLWafer += dl; col_dum=iy+ix+tt;};
   ChargeShare* getChargeShare() const {return chgShare;}; 
   void ClearaPixel()  {
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
