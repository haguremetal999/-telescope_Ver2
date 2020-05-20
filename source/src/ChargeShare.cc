#ifndef TSUBODEBUG
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#endif
#include "ChargeShare.hh"
#include <iostream>
#include <cmath>

void ChargeShare::printShareYx(G4double y, G4double x) {
  setPositionYx(y,x);
  G4cout << "ysize " << wy*2/um << " xsize " << wx*2/um << " sigma " << sig << "  leak " << leak << "  NdivY " << NY << "  NdivX " << NX << " Neighbors "<< NN <<
  G4endl << "Input Y/X=" << y << "/" << x <<G4endl;
  G4double sx=0,sy=0,ss=0;
  G4double share;
   for( int iy=+NN;iy>=-NN;iy--){
     G4cout << std::setw(16) << std::fixed;
     for( int ix=-NN;ix<=NN;ix++){
       share=getChargeShareYx(iy,ix);
       sx +=share*ix*wx; 
       sy +=share*iy*wy;
       ss +=share;
       G4cout << share << "  ";
     }
     G4cout << G4endl;
   }
   G4cout << " <Y>="<<sy*2 << " <X>=" << sx*2 <<" Sum=" << ss << G4endl;
   //   wx and wy are half pixel size.
}

void ChargeShare::setPositionYx(G4double yp, G4double xp){
  G4double xpos=xp/2, ypos=yp/2;
  if( (xpos<-wx*1.5 || xpos>wx*1.5 || ypos<-wy*1.5 || ypos>wy*1.5)) {
    G4cout << "ChargeShare: position error X/Y " << xpos << " " << ypos << G4endl;
    for(G4int ipy=0;ipy<=NN*2;ipy++) for(G4int ipx=0;ipx<=NN*2;ipx++)  w[ipy][ipx]=0.0;
    w[NN][NN]=1.0;
    wsum=1.0;
  } else {
    wsum=0;
    G4double ssx[20];
    G4double fy2=1.0/sig/sqrt(2);
    G4double fx2=1.0/sig/sqrt(2);
    for(G4int ipx=-NN;ipx<=NN;ipx++)  ssx[ipx+NN]=(erf((xpos-(ipx*2-1)*wx)*fx2)-erf((xpos-(ipx*2+1)*wx)*fx2));
    for(G4int ipy=-NN;ipy<=NN;ipy++) {
      double ssy=(erf((ypos-(ipy*2-1)*wy)*fy2)-erf((ypos-(ipy*2+1)*wy)*fy2));
      for(G4int ipx=-NN;ipx<=NN;ipx++){ 
	w[ipy+NN][ipx+NN]=ssy*ssx[ipx+NN];
	wsum+=w[ipy+NN][ipx+NN];
      }
    }
  }
}

//Constructor
ChargeShare::ChargeShare (
       G4double width_y,   // Half pixel size in Y 
       G4double width_x,   // Half pixel size in X 
       G4double sigma,     // Spread of charge
       G4double ll,        // Leak (can be 0)
       G4int Neighbors=0,    // Number of neighbor pixels to share the charge Normally 1-3, 0---Auto decision
       G4int NdivY=0,     //Division in a pixel  (5-50).   0---Auto decision 
       G4int NdivX=0      //Division in a pixel  (5-50).   0---Auto decision 
   ) {
    NN=NdivX+NdivY;  //Supperssing compilier warning.
  if(Neighbors==0) 
    NN=(sigma/width_x)+1;
  else 
    NN=Neighbors;
  int  NT=NN*2+1;   // size of the look up table
#if 0 
  wx=width_x/2;     //  wx and wy are half pixel size
  wy=width_y/2;     //  wx and wy are half pixel size
  sig=sigma;
#else
  wx=width_x/4;     //  wx and wy are half pixel size
  wy=width_y/4;     //  wx and wy are half pixel size
  sig=sigma/4;
#endif
  leak=ll;

  //   http://blog.northcol.org/2012/01/14/mdarray/
  w= new double*[NT];
  for(int i=0 ; i<NT;i++) w[i]= new double[NT];
};

/*
   Charge share. Assumption: the charge in silicon "somehow" spread with gaussian with sigma "sig".
   The gaussian function is integrated in the pixel. center and +/- 1 neighbors. 
   Also an additional parameter "leak" is introduced to spread charge as a cross talk.
   You can set it 0 to disable.   The intergrasion is done in mesh size specified by NX and NY.
   You can set them to 20 (One pixel is subdivided to 40).  The est root program is  build/chargeshare.C.
*/
