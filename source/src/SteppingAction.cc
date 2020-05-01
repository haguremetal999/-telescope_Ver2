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

#if 0
static G4double PPP=-1.0;
#endif

void SteppingAction::UserSteppingAction(const G4Step* step)
{
  auto chg= step->GetTrack()->GetDefinition()->GetPDGCharge() ;
  if(chg!=0) {
// get volume of the current step
    auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
// energy deposit
    auto edep = step->GetTotalEnergyDeposit();
    auto thetime = step->GetPreStepPoint()->GetGlobalTime();
//  auto thetime1= step->GetPreStepPoint()->GetProperTime();
//  auto thetime2 = step->GetPreStepPoint()->GetLocalTime();
  
    auto stepLength = step->GetStepLength();

#if 0    
  auto mass=step->GetPreStepPoint()->GetMass();
  if(mass != PPP) {
    auto ee=step -> GetPreStepPoint()->GetKineticEnergy();
    G4cout << " Mass=" << mass/MeV  << " MeV. E=" << ee << " MeV T="  << thetime/ns << " nsec " << G4endl;
    PPP=mass;
  }
#endif

  auto analysisManager = G4AnalysisManager::Instance();
  if ( volume == fDetConstruction->GetCmosPV() ) {
     G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
     G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
     fEventAction->AddCmos(edep,stepLength,iy,ix);
     analysisManager->FillH1(6, thetime/ns, edep/keV);
  } else if ( volume == fDetConstruction->GetDeplPV() ) {
     G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
     G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
     fEventAction->AddDepl(edep,stepLength,iy,ix);
     analysisManager->FillH1(7, thetime/ns, edep/keV);
  } else if ( volume == fDetConstruction->GetWaferPV() ) {
     G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
     G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
     fEventAction->AddWafer(edep,stepLength,iy,ix);
     analysisManager->FillH1(8, thetime/ns, edep/keV);
  }
}
}
