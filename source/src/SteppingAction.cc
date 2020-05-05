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
     // Test of local coordinate
     //From   BookForAppliDev.pdf   Page 283.
     //G4StepPoint* preStepPoint = step->GetPreStepPoint();
     //G4TouchableHandle theTouchable = preStepPoint->GetTouchableHandle();
     //G4ThreeVector worldPosition = preStepPoint->GetPosition();
     //G4ThreeVector localPosition = theTouchable->GetHistory()-> GetTopTransform().TransformPoint(worldPosition);
     G4StepPoint* p0 = step -> GetPreStepPoint();
     G4TouchableHandle t0 = p0 -> GetTouchableHandle();
     G4ThreeVector wp0 = p0 -> GetPosition();
     G4ThreeVector lp0 = t0-> GetHistory()-> GetTopTransform().TransformPoint(wp0);
     G4StepPoint* p1 = step -> GetPostStepPoint();
     G4ThreeVector wp1 = p1 -> GetPosition();
     G4ThreeVector lp1 = t0-> GetHistory()-> GetTopTransform().TransformPoint(wp1);
     G4cout << " p0(X Y Z)mm " << lp0.getX()/mm << " / "<< lp0.getY()/mm << " / "<< lp0.getZ()/mm 
            << " p1(X Y Z)mm " << lp1.getX()/mm << " / "<< lp1.getY()/mm << " / "<< lp1.getZ()/mm  <<G4endl;

     if ( volume == pixel0->GetCmosPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel0->AddCmos(edep,stepLength,iy,ix);
       analysisManager->FillH1(6, thetime/ns, edep/keV);
     } else if ( volume == pixel0->GetDeplPV() ) {
       G4int ix = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(1);
       G4int iy = step->GetPreStepPoint()->GetTouchableHandle()->GetReplicaNumber(2);
       pixel1->AddDepl(edep,stepLength,iy,ix);
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
       pixel0->AddDepl(edep,stepLength,iy,ix);
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
