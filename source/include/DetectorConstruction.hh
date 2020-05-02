/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "apixel.hh"
// I am ashamed I can not forward information from Geometry to other functions

#define  aNPixX (90)
#define  aNPixY (90)
#define  aSPixX (18*um)
#define  aSPixY (18*um)

class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

/// Detector construction class to define materials and geometry.
/// The calorimeter is a box made of a given number of layers. A layer consists
/// of an absorber plate and of a detection gap. The layer is replicated.
///
/// Four parameters define the geometry of the calorimeter :
///
/// - the thickness of an absorber plate,
/// - the thickness of a gap,
/// - the number of layers,
/// - the transverse size of the calorimeter (the input face is a square).
///
/// In addition a transverse uniform magnetic field is defined 
/// via G4GlobalMagFieldMessenger class.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

  public:
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    // get methods
    //
  const apixel*               Getapixel0() const;
  const apixel*               Getapixel1() const;
  //  const G4VPhysicalVolume* GetWaferPV() const;
     
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
     
  apixel *pixel0;
  apixel *pixel1;
  //    G4VPhysicalVolume* fWaferPV;      // the wafer physical volume
  //    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps

};

// inline functions
inline const apixel* DetectorConstruction::Getapixel0() const { return pixel0;  }
inline const apixel* DetectorConstruction::Getapixel1() const { return pixel1;  }

//inline const G4VPhysicalVolume* DetectorConstruction::GetDeplPV() const  {  return fDeplPV; }
//inline const G4VPhysicalVolume* DetectorConstruction::GetWaferPV() const  {  return fWaferPV; }
     
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

