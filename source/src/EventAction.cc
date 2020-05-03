//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "DetectorConstruction.hh"
#include "EventAction.hh"
#include "RunAction.hh"
#include "Analysis.hh"
#include "apixel.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>
#include <vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//EventAction::EventAction(DetectorConstruction* det)
//  :G4UserEventAction(),fDetector(det)
//{ }
EventAction::EventAction(DetectorConstruction* detectorConstruction)
  : G4UserEventAction()
  ,   fDetConstruction(detectorConstruction)

{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* /*event*/)
{  
  fDetConstruction -> Getapixel0() -> ClearApixel();
  fDetConstruction -> Getapixel1() -> ClearApixel();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
int Maxhits=0;
void EventAction::EndOfEventAction(const G4Event* event)

{  // Accumulate statistics

  // get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

 apixel* pixel0= fDetConstruction -> Getapixel0();
  //  apixel pixel1=detectorConcstruction -> Getapixel0();
// fill histograms
 G4double fEnergyCmos = pixel0 ->  GetECmos();
 G4double fEnergyDepl = pixel0 ->  GetEDepl();
 G4double fEnergyWafer = pixel0 ->  GetEWafer();
 G4double fTrackLCmos =  pixel0 ->  GetLCmos();
 G4double fTrackLDepl =  pixel0 ->  GetLDepl();
 G4double fTrackLWafer =  pixel0 ->  GetLWafer();
 G4int NPixY= pixel0 -> GetNPixY();
 G4int NPixX= pixel0 -> GetNPixX();

  if (fEnergyCmos>0)  analysisManager->FillH1(0, fEnergyCmos/keV);
  if (fEnergyDepl>0)  analysisManager->FillH1(1, fEnergyDepl/um);
  if (fEnergyWafer>0) analysisManager->FillH1(2, fEnergyWafer/keV);
  if (fTrackLCmos>0)  analysisManager->FillH1(3, fTrackLCmos/um);
  if (fTrackLDepl>0)  analysisManager->FillH1(4, fTrackLDepl/keV);
  if (fTrackLWafer>0) analysisManager->FillH1(5, fTrackLWafer/um);
  //  Histograms 6-8 are filled in the Stepping action.
  
  // fill ntuple
  analysisManager->FillNtupleIColumn(0, NPixY*1000+NPixX);
  analysisManager->FillNtupleIColumn(1, Nbuff);
  analysisManager->FillNtupleDColumn(2, fEnergyCmos/keV);
  analysisManager->FillNtupleDColumn(3, fEnergyDepl/keV);
  analysisManager->FillNtupleDColumn(4, fEnergyWafer/keV);
  analysisManager->FillNtupleDColumn(5, fTrackLCmos/um);
  analysisManager->FillNtupleDColumn(6, fTrackLDepl/um);
  analysisManager->FillNtupleDColumn(7, fTrackLWafer/um);
  G4int ptr=9;
  G4int nhits=0;

  for (G4int iy=0; iy<NPixY; iy++) {
    for (G4int ix=0; ix<NPixX; ix++) {
      G4double Eyx= pixel0->GetPixYX(iy, ix);
      if(Eyx>0) {
	if(nhits<Nbuff) {
	  nhits++;
	  analysisManager->FillNtupleIColumn(ptr++, iy*1000+ix);  // 9,11,13,15...
	  analysisManager->FillNtupleDColumn(ptr++, Eyx/keV);  //10,12,14...
	  if(0)  G4cout << iy*1000+ix << " " << Eyx/keV << G4endl;
	}
      }
    }
  }
  if(0)  G4cout <<  "Ntuple: " << nhits << "hits are stored" <<G4endl;
  if(nhits>Maxhits) {G4cout <<  "Ntuple: " << nhits << "hits are stored" <<G4endl;  Maxhits=nhits;}
  analysisManager->FillNtupleIColumn(8,nhits);
  analysisManager->AddNtupleRow();       // Weite to file.
  auto printModulo = G4RunManager::GetRunManager()->GetPrintProgress();
  if( printModulo > 0 ) {
    auto eventID = event->GetEventID();
    if ( eventID % printModulo == 0 ) {
      G4cout << "---> End of event: " << eventID << G4endl
       << "       SOI total Energy  : " << std::setw(7)
                                        << G4BestUnit(fEnergyCmos,"Energy")
       << "       total track length: " << std::setw(7)
                                        << G4BestUnit(fTrackLCmos,"Length")
       << G4endl

       << "       Depl: total energy: " << std::setw(7)
                                        << G4BestUnit(fEnergyDepl,"Energy")
       << "       total track length: " << std::setw(7)
                                        << G4BestUnit(fTrackLDepl,"Length")
       << G4endl

       << "      Wafer: total energy: " << std::setw(7)
                                        << G4BestUnit(fEnergyWafer,"Energy")
       << "       total track length: " << std::setw(7)
                                        << G4BestUnit(fTrackLWafer,"Length")
       << G4endl;
    }
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
