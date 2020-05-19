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
  fParticleGun->SetParticleEnergy(3*MeV);
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

  //  static int N0=0;
  static G4double pos_Y=-0.5*mm;  
  static G4double pos_X=-0.51*mm;  
  G4double pos_Z = -3*mm;
  
  if(0) {
    pos_X=pos_X+0.49*um;
    pos_Y=pos_Y+0.51*um;
  }
  if(1){
     pos_X = 0.5*mm*( G4UniformRand()-0.5 );
     pos_Y = 0.5*mm*( G4UniformRand()-0.5 );
  }

  //  G4cout << "Generated " << pos_X/mm << " " << pos_Y/mm << " " << pos_Z/mm << "  " <<N0++ << G4endl;
  fParticleGun->SetParticlePosition(G4ThreeVector( pos_X, pos_Y, pos_Z ));

#if 0
  G4double dir_X = 0.010*( G4UniformRand()-0.5 );
  G4double dir_Y = 0.010*( G4UniformRand()-0.5 );
#else
  G4double dir_X = G4RandGauss::shoot(0.0,0.001);
  G4double dir_Y = G4RandGauss::shoot(0.0,0.001);
#endif
  G4double dir_Z = 1;

  fParticleGun->SetParticleMomentumDirection(G4ThreeVector( dir_X, dir_Y, dir_Z ));
  fParticleGun->GeneratePrimaryVertex(anEvent); 
}
