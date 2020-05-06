#ifndef TSUBODEBUG
#include "G4NistManager.hh"
#endif
#include "ChargeShare.hh"
#include <iostream>
#include <cmath>
//using namespace std;

void ChargeShare::printShareYx(G4double y, G4double x) {
  setPositionYx(y,x);
  G4cout << "ysize " << wy << " xsize " << wx << " sigma " << sig << "  leak " << leak << "  NdivY " << NY << "  NdivX " << NX <<G4endl;
  G4cout << "Input Y/X=" << y << "/" << x <<G4endl;
  G4cout << getChargeShareYx( 1,-1) << " " << getChargeShareYx( 1,0) << " " << getChargeShareYx( 1,1) << " " <<G4endl
       << getChargeShareYx( 0,-1) << " " << getChargeShareYx( 0,0) << " " << getChargeShareYx( 0,1) << " " <<G4endl
       << getChargeShareYx(-1,-1) << " " << getChargeShareYx(-1,0) << " " << getChargeShareYx(-1,1) << " " <<G4endl;
}

void ChargeShare::setPositionYx(G4double ypos, G4double xpos){
  G4int  iy=round(ypos/wy*NY);
  G4int  ix=round(xpos/wx*NX);
  if(ix<-NX || ix>NX || iy<-NY || iy>NY) {
    G4cout << "ChargeShare: position error X/Y" << xpos << " " << ypos << G4endl;
    for(G4int ipy=0;ipy<3;ipy++) for(G4int ipx=0;ipx<3;ipx++)  w[ipy][ipx]=0.0;
    w[1][1]=1.0;
    wsum=1.0;
  } else {
    wsum=0;
    for(G4int ipy=-1;ipy<=1;ipy++) {
      for(G4int ipx=-1;ipx<=1;ipx++){
	//Data access --> considering the 4-fold symmetry
	w[ipy+1][ipx+1]=syx[abs(iy-ipy*2*NY)][abs(ix-ipx*2*NX)];
	wsum+=w[ipy+1][ipx+1];
      }
    }
  }
}

//Constructor
ChargeShare::ChargeShare (G4double width_y, G4double width_x, G4double sigma, G4double ll, G4int NdivY=20, G4int NdivX=20) {

  NY=NdivY;
  NX=NdivX;
  wx=width_x;
  wy=width_y;
  sig=sigma;
  leak=ll;
  G4cout << "ChargeShare y/x size="<<wy<<", "<<wx<< " Mesh="<<NY<<" , "<<NX<<" Leak factor "<<leak<<G4endl; 

  G4double *ey=new G4double[NdivY*8+1];
  G4double *ex=new G4double[NdivX*8+1];
  G4double wx2=(wx/sig/NX)*(wx/sig/NX)/2;
  G4double wy2=(wy/sig/NY)*(wy/sig/NY)/2;

  //   http://blog.northcol.org/2012/01/14/mdarray/
  syx = new G4double*[NY*3+1];
  for (G4int i = 0; i < NY*3+1; i++) {
    syx[i] = new double[NX*3+1];
  }

  for( G4int iy= -NY*4;iy<= NY*4;iy++) {ey[iy+NY*4]=exp(-iy*iy*wy2)+leak; };
  for( G4int ix= -NX*4;ix<= NX*4;ix++) {ex[ix+NX*4]=exp(-ix*ix*wx2)+leak; };
    
  G4double sum;
  for(G4int iy= 0;iy<= NY*3;iy++) {
    for(G4int ix= 0;ix<= NX*3;ix++) { 
      sum=0.0;
      for(G4int jy= -NY;jy<= NY;jy++) {
	for(G4int jx= -NX;jx<= NX;jx++) {
	  sum=sum+ey[jy+iy+NY*4]*ex[jx+ix+NX*4];
	}
      }
      syx[iy][ix]=sum;
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


