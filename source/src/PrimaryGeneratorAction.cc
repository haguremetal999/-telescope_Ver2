/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
#include <fstream>
#include <iostream>
#include <string>

#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4RunManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PrimaryVertex.hh"
#include "G4PrimaryParticle.hh"
#include "Randomize.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
 : G4VUserPrimaryGeneratorAction(),
   fParticleGun(nullptr)
{
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);
  
  // default particle kinematic
  //
  auto particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("mu-");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(3.*MeV);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
 
  //Use the default gun setting except the particle position
  //  auto primaryParticle=new G4PrimaryParticle(particle, momVect.x(), momVect.y(), momVect.z() ); 
  
  G4double pos_X = 0.9*NPixX*SPixX*( G4UniformRand()-0.5 );
  G4double pos_Y = 0.9*NPixY*SPixY*( G4UniformRand()-0.5 );
  G4double pos_Z = -5*mm;

  fParticleGun->SetParticlePosition(G4ThreeVector( pos_X, pos_Y, pos_Z ));

  G4double dir_X = 0.01*( G4UniformRand()-0.5 );
  G4double dir_Y = 0.01*( G4UniformRand()-0.5 );
  G4double dir_Z = 1;

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector( dir_X, dir_Y, dir_Z ));

  fParticleGun->GeneratePrimaryVertex(anEvent); 

}
