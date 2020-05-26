#include <cmath>
// multiple coulomb scattering
{
  double thick     = 1.27;   // Unit=mm
  double X0_vacuum = 303921;  // Unit=mm
  double X0_AlN  = 85.6;
  double X0_Al2O3  = 73.4;
  double X0_SiO2  = 116.5;
  double X0_Si    = 93.7; 
  double X0_Iron  = 17.5;
  string Mat[6] ={"Air", "SiO2", "Si", "AlN", "Al2O3","Iron"};
  double X0[6] ={303921,116.5,  93.7, 85.6,  73.4,    17.5};

  double C=13.6 ; //MeV
  double z=1.0;
  string particle[3]={"Proton","Proton","e-"};
  double mass[3]={945.0,945.0,0.511};   //mass   in MeV/c2
  double mom[3]={120000,10000,1000};    //Momemnutum in MeV/c

  for(int im=0; im<3; im++) {
    double beta=mom[im]/sqrt(mom[im]*mom[im]+mass[im]*mass[im]);
    for(int ij=0; ij<6; ij++) {
      double SQRT=sqrt(thick/X0[ij]);
      double AA=1.0+0.038*log(thick*z*z/(X0[ij]*beta*beta));
      double theta0=C/(beta*mom[im])*z*SQRT*AA;
      cout << "Material " << Mat[ij] << " Particle " << particle[im] << " Momentum " << mom[im]/1000.0 << " GeV/c" << endl;
      cout << "theta0= "<< theta0*1000 << " mradian" << endl;
    }
  }
} 
