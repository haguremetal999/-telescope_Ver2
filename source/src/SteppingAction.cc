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
                      DetectorConstruction* det,
		      //                      const DetectorConstruction* det,
                      EventAction* event)
  : G4UserSteppingAction(),
    fEventAction(event)
{
  fDetConstruction=det;
  pixel0= det->Getapixel0();
  pixel1= det->Getapixel1();
  pixel2= det->Getapixel2();
  //  G4cout << "SSSSSS    pixel0/pixel1/pixel2 " << pixel0 << "/" << pixel1 << "/" << pixel2 << G4endl;
}


SteppingAction::~SteppingAction()  {}


//void SteppingAction::UserSteppingAction(const G4Step* step, const DetectorConstruction* fDetConstruction)
void SteppingAction::UserSteppingAction(const G4Step* step)
{
  auto chg= step->GetTrack()->GetDefinition()->GetPDGCharge() ;
  if(chg!=0) {
// get volume of the current step
     auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
     auto edep       = step->GetTotalEnergyDeposit();
     auto thetime    = step->GetPreStepPoint()->GetGlobalTime();
     auto stepLength = step->GetStepLength();
     auto analysisManager = G4AnalysisManager::Instance();
 
     if ( volume == pixel0->GetCmosPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel0->AddCmos(edep,stepLength,iy,ix);
       analysisManager->FillH1(6, thetime/ns, edep/keV);
     } else if ( volume == pixel0->GetDeplPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel0->AddDepl(edep,stepLength,iy,ix);
       analysisManager->FillH1(7, thetime/ns, edep/keV);
     } else if ( volume == pixel0->GetWaferPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel0->AddWafer(edep,stepLength,iy,ix);
       analysisManager->FillH1(8, thetime/ns, edep/keV);
     } else if ( volume == pixel1->GetCmosPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel1->AddCmos(edep,stepLength,iy,ix);
       analysisManager->FillH1(6, thetime/ns, edep/keV);
     } else if ( volume == pixel1->GetDeplPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel1->AddDepl(edep,stepLength,iy,ix);
       analysisManager->FillH1(7, thetime/ns, edep/keV);
     } else if ( volume == pixel1->GetWaferPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel1->AddWafer(edep,stepLength,iy,ix);
       analysisManager->FillH1(8, thetime/ns, edep/keV);
     } else if ( volume == pixel2->GetCmosPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel2->AddCmos(edep,stepLength,iy,ix);
       analysisManager->FillH1(6, thetime/ns, edep/keV);
     } else if ( volume == pixel2->GetDeplPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel2->AddDepl(edep,stepLength,iy,ix);
       analysisManager->FillH1(7, thetime/ns, edep/keV);
     } else if ( volume == pixel2->GetWaferPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel2->AddWafer(edep,stepLength,iy,ix);
       analysisManager->FillH1(8, thetime/ns, edep/keV);
     }
  }
}
