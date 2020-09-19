/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
#include <fstream>
#include <iostream>
#include <string>

#include "PrimaryGeneratorAction.hh"

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
  auto particleDefinition = G4ParticleTable::GetParticleTable()->FindParticle("proton");
  fParticleGun->SetParticleDefinition(particleDefinition);
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
  fParticleGun->SetParticleEnergy(120*GeV);
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
  //  G4double Size=0.5*mm;  //default size
  G4double Size=100.0*um;
  //  static int N0=0;
  static G4double pos_Y=-Size;  
  static G4double pos_X=-Size;  
  G4double pos_Z = -3*mm;
  
  if(0)  {
    pos_X=pos_X+0.26967233145831580803*um;
    if(pos_X > Size) pos_X=-Size;
  }
  else      pos_X = Size*( G4UniformRand()-0.5 );
  
  if(0)     pos_Y=pos_Y+0.25*um;
  else      pos_Y = Size*( G4UniformRand()-0.5 );

  //  pos_X = 0;
  //  pos_Y = 0;
  fParticleGun->SetParticlePosition(G4ThreeVector( pos_X, pos_Y, pos_Z ));

#if 0
  //  G4double dir_X = 0.010*( G4UniformRand()-0.5 );
  //  G4double dir_Y = 0.010*( G4UniformRand()-0.5 );
#elif 1
  //  G4double dir_X = G4RandGauss::shoot(0.0,0.001);  //defalt setup
  //  G4double dir_Y = G4RandGauss::shoot(0.0,0.001);  //defalt setup
  G4double dir_X = G4RandGauss::shoot(0.0,0.001);
  G4double dir_Y = G4RandGauss::shoot(0.0,0.001);
#elif 0
  G4double dir_X = 0.0001;
  G4double dir_Y = 0.0001;
#else
  G4double dir_X = 0.0;
  G4double dir_Y = 0.0;
#endif
  //  G4double dir_Z = 1;  //default setup
  G4double dir_Z = 1;

  //  dir_X = 0;
  //  dir_Y = 0; 
  
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector( dir_X, dir_Y, dir_Z ));
  fParticleGun->GeneratePrimaryVertex(anEvent); 
}
