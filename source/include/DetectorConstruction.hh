/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "apixel.hh"
// I am ashamed I can not forward information from Geometry to other functions


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

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    apixel*               Getapixel0() ;
    apixel*               Getapixel1() ;
     
  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
     
  apixel *Pixel0;
  apixel *Pixel1;
  //    G4VPhysicalVolume* fWaferPV;      // the wafer physical volume
  //    G4bool  fCheckOverlaps; // option to activate checking of volumes overlaps

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

