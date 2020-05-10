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
       G4cout << s << "  ";
     }
     G4cout << G4endl;
   }
   G4cout << " <Y>="<<sy*2 << " <Y>=" << sx*2 <<" Sum=" << ss << G4endl;
   //   G4cout << std::resetiosflags;
}

void ChargeShare::setPositionYx(G4double ypos, G4double xpos){
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
  if(NdivY==0) 
    NY=(wy/sig)*4+1;
    else
    NY=NdivY;
  if(NdivX==0) 
    NX=(wx/sig)*4+1;
  else
    NX=NdivX;
  G4cout << "ChargeShare y/x size="<<wy/um <<", "<<wx/um<< " Sig=" << sig/um << " Neighbors=" << NN << "  Mesh="<<NY<<" , "<<NX<<" Leak factor "<<leak<<G4endl; 

  G4double *ey=new G4double[NY*NI*2+1];
  G4double *ex=new G4double[NX*NI*2+1];
  G4double wx2=(wx/sig/NX)*(wx/sig/NX)/2;
  G4double wy2=(wy/sig/NY)*(wy/sig/NY)/2;

  //   http://blog.northcol.org/2012/01/14/mdarray/
  w= new double*[NT];
  for(int i=0 ; i<NT;i++) w[i]= new double[NT];

  syx = new G4double*[NY*NT+1];
  for (G4int i = 0; i < NY*NT+1; i++)  syx[i] = new double[NX*NT+1];
  
  //  for( G4int iy= -NY*4;iy<= NY*4;iy++) {ey[iy+NY*4]=exp(-iy*iy*wy2)+leak; };
  //  for( G4int ix= -NX*4;ix<= NX*4;ix++) {ex[ix+NX*4]=exp(-ix*ix*wx2)+leak; };
  ey[0]=exp(-(NY*NI)*(NY*NI)*wy2)+leak;
  ex[0]=exp(-(NX*NI)*(NX*NI)*wx2)+leak;
  for( G4int iy= -NY*NI+1;iy<= NY*NI;iy++) {ey[iy+NY*NI]=ey[iy-1+NY*NI]+exp(-iy*iy*wy2)+leak; };
  for( G4int ix= -NX*NI+1;ix<= NX*NI;ix++) {ex[ix+NX*NI]=ex[ix-1+NX*NI]+exp(-ix*ix*wx2)+leak; };

  for(G4int iy= 0;iy<= NY*NT;iy++) {
    for(G4int ix= 0;ix<= NX*NT;ix++) { 
      //      syx[iy][ix]=(ey[iy+NY*(NI+1)]-ey[iy+NY*(NI-1)])*(ex[ix+NX*(NI+1)]-ex[ix+NX*(NI-1)]);
      syx[iy][ix]=(ey[iy+NY*(NI+1)]-ey[iy+NY*(NI-1)])*(ex[ix+NX*(NI+1)]-ex[ix+NX*(NI-1)]);
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


