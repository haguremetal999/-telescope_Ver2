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
  G4double BeamPosX0;
  G4double BeamPosY0;
  G4double BeamPosZ0;
  G4double BeamMomX0;
  G4double BeamMomY0;
  G4double BeamMomZ0;

  //  static G4int Maxhits=0;   // static over the runs
public:
    void SetBeaminfo(G4double posx, G4double posy, G4double posz, G4double momx, G4double momy, G4double momz)
  {BeamPosX0=posx;BeamPosY0=posy;BeamPosZ0=posz,BeamMomX0=momx,BeamMomY0=momy,BeamMomZ0=momz;};
  double GetBeamPosZ0() const {return BeamPosZ0;};
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
};
#endif


    
