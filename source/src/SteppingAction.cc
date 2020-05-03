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
  G4cout << "SSSSSS   Stepping action constructor is called" << G4endl;
}


SteppingAction::~SteppingAction()  {}


//void SteppingAction::UserSteppingAction(const G4Step* step, const DetectorConstruction* fDetConstruction)
void SteppingAction::UserSteppingAction(const G4Step* step)
{
       G4int NNN=0;
  auto chg= step->GetTrack()->GetDefinition()->GetPDGCharge() ;
  G4cout <<  "SSSTEP " << NNN++ << G4endl;
  if(chg!=0) {
// get volume of the current step
  G4cout <<  "SSSTEP " << NNN++ << G4endl;
     auto volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume();
// energy deposit and time
     G4cout <<  "SSSTEP " << NNN++ << " Volume "<< volume << G4endl;
     auto edep       = step->GetTotalEnergyDeposit();
  G4cout <<  "SSSTEPC " << NNN++ << G4endl;
     auto thetime    = step->GetPreStepPoint()->GetGlobalTime();
  G4cout <<  "SSSTEPD " << NNN++ << G4endl;
     auto stepLength = step->GetStepLength();
  G4cout <<  "SSSTEPE " << NNN++ << G4endl;
     auto analysisManager = G4AnalysisManager::Instance();
  G4cout <<  "SSSTEPGa " << NNN++ << G4endl;
     auto v1=pixel0 -> GetCmosPV();
  G4cout <<  "SSSTEPF " << NNN++ << v1 << G4endl;
 
     if ( volume == pixel0->GetCmosPV() ) {
       NNN++;
       //        G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       //G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       //   pixel0->AddCmos(edep,stepLength,iy,ix);
       //       analysisManager->FillH1(6, thetime/ns, edep/keV);
     } else if ( volume == pixel0->GetDeplPV() ) {
       NNN++;
       //  G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       //G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       //  pixel0->AddDepl(edep,stepLength,iy,ix);
       //  analysisManager->FillH1(7, thetime/ns, edep/keV);
     } else if ( volume == pixel0->GetWaferPV() ) {
       NNN++;
       //       G4cout << "C";
       // G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       //G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       //  pixel0->AddWafer(edep,stepLength,iy,ix);
       // analysisManager->FillH1(8, thetime/ns, edep/keV);
     }
     G4cout <<  "KAISUU "<< NNN << G4endl;
  }
       G4cout << "Z " << G4endl;
}
