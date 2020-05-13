/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "aPixel.hh"
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

   aPixel* Getfpix0() const { return fpix0;}
   aPixel* Getfpix1() const { return fpix1;}
   aPixel* Getfpix2() const { return fpix2;}
   aPixel* Getfpix3() const { return fpix3;}
   aPixel* Getsofist0() const { return sofist0;}
   aPixel* Getsofist1() const { return sofist1;}

  private:
    // methods
    //
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
  
    // data members
    //
    static G4ThreadLocal G4GlobalMagFieldMessenger*  fMagFieldMessenger; 
                                      // magnetic field messenger
     
  aPixel *fpix0;
  aPixel *fpix1;
  aPixel *fpix2;
  aPixel *fpix3;
  aPixel *sofist0;
  aPixel *sofist1;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

