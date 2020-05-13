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
  SteppingAction( DetectorConstruction* , EventAction* );
  virtual ~SteppingAction();

  virtual void UserSteppingAction(const G4Step* );
    
private:
  DetectorConstruction* fDetConstruction;
  EventAction*  fEventAction;  
  aPixel* fpix0;
  aPixel* fpix1;
  aPixel* fpix2;
  aPixel* fpix3;
  aPixel* sofist0;
  aPixel* sofist1;
};

#endif
