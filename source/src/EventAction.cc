//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>
#include <vector>
#include "RunAction.hh"
#include "Analysis.hh"
#include "aPixel.hh"
#include "EventAction.hh"
#include "NtupleBuffsize.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction(DetectorConstruction* detectorConstruction)
  : G4UserEventAction()
  ,   fDetConstruction(detectorConstruction)
{
  Maxhits = 0;
  Bufsize = NTUPLEBUFFSIZE;    // defined in "NtupleBuffsize.hh" 
  G4cout << "EEEEE  Event action constructor Bufsize is " << Bufsize << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{ 
  //  G4cout << "beginofEvent" << G4endl;
  fDetConstruction -> Getfpix0() -> ClearaPixel();
  fDetConstruction -> Getfpix1() -> ClearaPixel();
  fDetConstruction -> Getfpix2() -> ClearaPixel();
  fDetConstruction -> Getfpix3() -> ClearaPixel();
  fDetConstruction -> Getsofist0() -> ClearaPixel();
  fDetConstruction -> Getsofist1() -> ClearaPixel();
  BeamPosZ0=-10000.0*mm;
}

void EventAction::pixeltotuple(aPixel *pixel, G4int offset) {
  auto analysisManager = G4AnalysisManager::Instance();
  G4int NPixY= pixel -> GetNPixY();
  G4int NPixX= pixel -> GetNPixX();
  for (G4int iy=0; iy<NPixY; iy++) {
    for (G4int ix=0; ix<NPixX; ix++) {
      G4double Eyx= pixel->GetPixYX(iy, ix);
      if(Eyx>0.5*eV) {  // Discard if less than 0.5 eV
	if(pixelhits<Bufsize) {
	  pixelhits++;
	  analysisManager->FillNtupleIColumn(ptr++, offset+iy*1000+ix);  // 9,11,13,15...
	  analysisManager->FillNtupleDColumn(ptr++, Eyx/keV);  //10,12,14...
	}
      }
    }
  }
}




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventAction::EndOfEventAction(const G4Event* event)
{  // Accumulate statistics

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  aPixel* fpix0  = fDetConstruction -> Getfpix0();
  aPixel* fpix1  = fDetConstruction -> Getfpix1();
  aPixel* fpix2  = fDetConstruction -> Getfpix2();
  aPixel* fpix3  = fDetConstruction -> Getfpix3();
  aPixel* sofist0= fDetConstruction -> Getsofist0();
  aPixel* sofist1= fDetConstruction -> Getsofist1();
// fill histograms
  G4int NPixY= fpix0 -> GetNPixY();
  G4int NPixX= fpix0 -> GetNPixX();

  //  Histograms 6-8 are filled in the Stepping action.
  
  // fill ntuple
  analysisManager->FillNtupleIColumn(0, NPixY*1000+NPixX);
  analysisManager->FillNtupleIColumn(1, Bufsize);

  analysisManager->FillNtupleDColumn(2, BeamPosX0/mm);
  analysisManager->FillNtupleDColumn(3, BeamPosY0/mm);
  analysisManager->FillNtupleDColumn(4, BeamPosZ0/mm);
  analysisManager->FillNtupleDColumn(5, BeamMomX0/MeV);
  analysisManager->FillNtupleDColumn(6, BeamMomY0/MeV);
  analysisManager->FillNtupleDColumn(7, BeamMomZ0/MeV);

  ptr=NTUPLEPIXELPTR ;  // defined in  "NtupleBuffsize.hh"
  pixelhits=0;
  int nn0,nn1,nn2,nn3,nn4,nn5;
  pixeltotuple(fpix0,         0);  nn0=pixelhits;
  pixeltotuple(fpix1,   1000000);  nn1=pixelhits;
  pixeltotuple(sofist0, 2000000);  nn2=pixelhits;
  pixeltotuple(sofist1, 3000000);  nn3=pixelhits;
  pixeltotuple(fpix2,   4000000);  nn4=pixelhits;
  pixeltotuple(fpix3,   5000000);  nn5=pixelhits;
  if(pixelhits>=Maxhits) {
    auto eventID = event->GetEventID();
    G4cout << "End of Events: EventID" << eventID << " Maxhits " << pixelhits << "hits are stored" <<G4endl;  Maxhits=pixelhits;
    G4cout << "Hits are " << nn0 <<" " << nn1-nn0 <<" "<< nn2-nn1 <<" "<< nn3-nn2 <<" "<< nn4-nn3 <<" "<< nn5-nn4 <<G4endl;
}
  analysisManager->FillNtupleIColumn(8,pixelhits);
  analysisManager->AddNtupleRow();       // Weite to file.
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if( printModulo > 0 ) {
    auto eventID = event->GetEventID();
    if ( eventID % printModulo == 0 ) {
      G4cout << "Hits are " << nn0 <<" " << nn1-nn0 <<" "<< nn2-nn1 <<" "<< nn3-nn2 <<" "<< nn4-nn3 <<" "<< nn5-nn4 <<G4endl;
    }
  }
}
