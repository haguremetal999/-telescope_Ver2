#ifndef TSUBODEBUG
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#endif
#include "ChargeShare.hh"
#include <iostream>
#include <cmath>

void ChargeShare::printShareYx(G4double y, G4double x) {
  setPositionYx(y,x);
  G4cout << "ysize " << wy << " xsize " << wx << " sigma " << sig << "  leak " << leak << "  NdivY " << NY << "  NdivX " << NX << " Neighbors "<< NN <<
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
   //   G4cout << std::resetiosflags;
}

void ChargeShare::setPosition0Yx(G4double ypos, G4double xpos){
  int NT=NN*2+1;
  int  iy=round(ypos/wy*NY);
  int  ix=round(xpos/wx*NX);
  if(ix<-NX || ix>NX || iy<-NY || iy>NY) {
    G4cout << "ChargeShare: position error X/Y" << xpos << " " << ypos << G4endl;
    for(G4int ipy=0;ipy<NT;ipy++) for(G4int ipx=0;ipx<NT;ipx++)  w[ipy][ipx]=0.0;
    w[NN][NN]=1.0;
    wsum=1.0;
  } else {
    wsum=0;
    for(G4int ipy=-NN;ipy<=NN;ipy++) {
      for(G4int ipx=-NN;ipx<=NN;ipx++){  //Data access --> considering the 4-fold symmetry
	w[ipy+NN][ipx+NN]=syx[abs(iy-ipy*2*NY)][abs(ix-ipx*2*NX)];
	wsum+=w[ipy+NN][ipx+NN];
      }
    }
  }
}

void ChargeShare::setPositionYx(G4double ypos, G4double xpos){
  if( (xpos<-wx*2 || xpos>wx*2 || ypos<-wy*2 || ypos>wy*2)) {
    G4cout << "ChargeShare: position error X/Y " << xpos << " " << ypos << G4endl;
    for(G4int ipy=0;ipy<=NN*2;ipy++) for(G4int ipx=0;ipx<=NN*2;ipx++)  w[ipy][ipx]=0.0;
    w[NN][NN]=1.0;
    wsum=1.0;
  } else {
    wsum=0;
    G4double fy2=1.0/sig/sqrt(2);
    G4double fx2=1.0/sig/sqrt(2);
    for(G4int ipy=-NN;ipy<=NN;ipy++) {
      double ssy=(erf((ypos-(ipy*2-1)*wy)*fy2)-erf((ypos-(ipy*2+1)*wy)*fy2));
      for(G4int ipx=-NN;ipx<=NN;ipx++){  //Data access --> considering the 4-fold symmetry
	w[ipy+NN][ipx+NN]=ssy*(erf((xpos-(ipx*2-1)*wx)*fx2)-erf((xpos-(ipx*2+1)*wx)*fx2));
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
  if(Neighbors==0) 
    NN=(sigma/width_x)+1;
  else 
    NN=Neighbors;
  int  NT=NN*2+1;   // size of the look up table
  int  NI=NN*3+1;   //integration region    
  wx=width_x;
  wy=width_y;
  sig=sigma;
  leak=ll;

  //   http://blog.northcol.org/2012/01/14/mdarray/
  w= new double*[NT];
  for(int i=0 ; i<NT;i++) w[i]= new double[NT];

  if(1) return;

  if(NdivY==0) 
    NY=std::max(10,(int)((wy/sig)*4+1));
    else
    NY=NdivY;
  if(NdivX==0) 
    NX=std::max(10,(int)((wx/sig)*4+1));
  else
    NX=NdivX;
  G4cout << "ChargeShare y/x size="<<wy/um <<", "<<wx/um<< " Sig=" << sig/um << " Neighbors=" << NN << "  Mesh="<<NY<<" , "<<NX<<" Leak factor "<<leak<<G4endl; 



  syx = new G4double*[NY*NT+1];
  for (G4int i = 0; i < NY*NT+1; i++)  syx[i] = new double[NX*NT+1];

  G4double fy2=wy/sig/NY/sqrt(2);
  G4double fx2=wx/sig/NX/sqrt(2);
  for(G4int iy= 0;iy<= NY*NT;iy++) {
    for(G4int ix= 0;ix<= NX*NT;ix++) { 
      syx[iy][ix]=(erf((iy+NY)*fy2)-erf((iy-NY)*fy2))*(erf((ix+NX)*fx2)-erf((ix-NX)*fx2));
    }
  }
};
  


/*
   Charge share. Assumption: the charge in silicon "somehow" spread with gaussian with sigma "sig".
   The gaussian function is integrated in the pixel. center and +/- 1 neighbors. 
   Also an additional parameter "leak" is introduced to spread charge as a cross talk.
   You can set it 0 to disable.   The intergrasion is done in mesh size specified by NX and NY.
   You can set them to 20 (One pixel is subdivided to 40).  The est root program is  build/chargeshare.C.
*/


