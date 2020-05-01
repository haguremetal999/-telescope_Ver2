/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
/// Event action class
///
/// It defines data members to hold the energy deposit and track lengths
/// of charged particles in Absober and Gap layers:
/// - fEnergyAbs, fEnergyGap, fTrackLAbs, fTrackLGap
/// which are collected step by step via the functions
/// - AddAbs(), AddGap()

class EventAction : public G4UserEventAction
{
  public:
    EventAction();
    virtual ~EventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
//    void AddAbs(G4double de, G4double dl);
//    void AddGap(G4double de, G4double dl);
  void AddCmos(G4double de, G4double dl, G4int col, G4int row );
  void AddDepl(G4double de, G4double dl, G4int col, G4int row );
  void AddWafer(G4double de, G4double dl, G4int col, G4int row );
    
  private:
    G4double  fEnergyCmos;
    G4double  fEnergyDepl;
    G4double  fEnergyWafer;
    G4double  fTrackLCmos; 
    G4double  fTrackLDepl;
    G4double  fTrackLWafer;
    G4int col_dum;
    G4double  pixelData[NPixY][NPixX];
};


// inline functions

inline void EventAction::AddCmos(G4double de, G4double dl, G4int iy, G4int ix) {
  fEnergyCmos += de; 
  fTrackLCmos += dl;
  col_dum=iy+ix;
}

inline void EventAction::AddDepl(G4double de, G4double dl, G4int iy, G4int ix ) {
  if (iy>NPixY) G4cout << "Index error iy " << iy << " > " << NPixY << G4endl;
  if (ix>NPixX) G4cout << "Index error ix " << ix << " > " << NPixX << G4endl;
  fEnergyDepl += de; 
  fTrackLDepl += dl;
  pixelData[iy][ix] +=de;
}
                     
inline void EventAction::AddWafer(G4double de, G4double dl, G4int iy, G4int ix ) {
  fEnergyWafer += de; 
  fTrackLWafer += dl;
  col_dum=iy+ix;
}
                     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


    
