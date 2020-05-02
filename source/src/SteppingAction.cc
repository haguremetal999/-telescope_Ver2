/// \file SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "DetectorConstruction.hh"
#include "SteppingAction.hh"
#include "EventAction.hh"

#include "Analysis.hh"
#include "G4Event.hh"
#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


SteppingAction::SteppingAction(
                      const DetectorConstruction* detectorConstruction,
                      EventAction* eventAction)
  : G4UserSteppingAction(),
    fDetConstruction(detectorConstruction),
    fEventAction(eventAction)
{}


SteppingAction::~SteppingAction()
{}


void SteppingAction::UserSteppingAction(const G4Step* step)
{
  auto chg= step->GetTrack()->GetDefinition()->GetPDGCharge() ;
  if(chg!=0) {
// get volume of the current step
     auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
// energy deposit and time
     auto edep    = step->GetTotalEnergyDeposit();
     auto thetime = step->GetPreStepPoint()->GetGlobalTime();
     auto stepLength = step->GetStepLength();

     auto analysisManager = G4AnalysisManager::Instance();
     if ( volume == fDetConstruction->Getapixel0()->GetCmosPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       fEventAction->AddCmos(edep,stepLength,iy,ix);
       analysisManager->FillH1(6, thetime/ns, edep/keV);
     } else if ( volume == fDetConstruction->Getapixel0()->GetDeplPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       fEventAction->AddDepl(edep,stepLength,iy,ix);
       analysisManager->FillH1(7, thetime/ns, edep/keV);
     } else if ( volume == fDetConstruction->Getapixel0()->GetWaferPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       fEventAction->AddWafer(edep,stepLength,iy,ix);
       analysisManager->FillH1(8, thetime/ns, edep/keV);
     }
  }
}
