/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::ActionInitialization
                            (DetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ActionInitialization::~ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ActionInitialization::Build() const
{
  G4cout << "AAAAAAction action init Primary" << G4endl;
  SetUserAction(new PrimaryGeneratorAction);

  G4cout << "AAAAAAction action init Runaction" << G4endl;
  SetUserAction(new RunAction);

  G4cout << "AAAAAAction action init Eventaction" << G4endl;
  auto eventAction = new EventAction(fDetConstruction);

  SetUserAction(eventAction);
  G4cout << "AAAAAAction action init SteppingAction" << G4endl;

  SetUserAction(new SteppingAction(fDetConstruction,eventAction));
  G4cout << "AAAAAAction action init  Finish" << G4endl;
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
