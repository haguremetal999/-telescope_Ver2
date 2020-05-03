/// \file SteppingAction.hh
/// \brief Definition of the SteppingAction class

#ifndef SteppingAction_h
#define SteppingAction_h 1

#include "G4UserSteppingAction.hh"

class DetectorConstruction;
class EventAction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track 
/// lengths of charged particles in Absober and Gap layers and
/// updated in EventAction.

class SteppingAction : public G4UserSteppingAction
{
public:
  //  SteppingAction(const DetectorConstruction* , EventAction* );
  SteppingAction( DetectorConstruction* , EventAction* );
  virtual ~SteppingAction();

  //  virtual void UserSteppingAction(const G4Step* , const DetectorConstruction* );
  virtual void UserSteppingAction(const G4Step* );
    
private:
  //  const DetectorConstruction* fDetConstruction;
  DetectorConstruction* fDetConstruction;
  EventAction*  fEventAction;  
  apixel* pixel0;
  apixel* pixel1;
};

#endif
