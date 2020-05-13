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
class EventAction : public G4UserEventAction
{
  public:
    EventAction(DetectorConstruction*);
    virtual ~EventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
  private:
  DetectorConstruction* fDetConstruction;
  void pixeltotuple(aPixel *, int );
  G4int pixelhits;    
  G4int Maxhits;   
  G4int Bufsize;   // Ntuple buffer size
  G4int ptr;   // pointer for the ntuple
  //  static G4int Maxhits=0;   // static over the runs

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
};
#endif


    
