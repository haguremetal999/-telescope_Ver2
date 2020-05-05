//#include "G4NistManager.hh"
#include "ChargeShare.hh"
#include <iostream>
#include <cmath>
using namespace std;

void ChargeShare::printShareYx(double y, double x) {
  setPositionYx(y,x);
  cout << "ysize " << wy << " xsize " << wx << " sigma " << sig << "  leak " << leak << "  NdivY " << NY << "  NdivX " << NX <<endl;
  cout << "Input Y/X=" << y << "/" << x <<endl;
  cout << getChargeShareYx(-1,-1) << " " << getChargeShareYx(-1,0) << " " << getChargeShareYx(-1,1) << " " <<endl
       << getChargeShareYx( 0,-1) << " " << getChargeShareYx( 0,0) << " " << getChargeShareYx( 0,1) << " " <<endl
       << getChargeShareYx( 1,-1) << " " << getChargeShareYx( 1,0) << " " << getChargeShareYx( 1,1) << " " <<endl;
}


void ChargeShare::setPositionYx(double ypos, double xpos){
  int  iy=round(ypos/wy*NY);
  int  ix=round(xpos/wx*NX);
  if(ix<-NX || ix>NX || iy<-NY || iy>NY) {
    cout << "ChargeShare: position error X/Y" << xpos << " " << ypos << endl;
    for(int ipy=0;ipy<3;ipy++) for(int ipx=0;ipx<3;ipx++)  w[ipy][ipx]=0.0;
    w[1][1]=1.0;
    wsum=1.0;
  } else {
    wsum=0;
    for(int ipy=-1;ipy<=1;ipy++) {
      for(int ipx=-1;ipx<=1;ipx++){
	w[ipy+1][ipx+1]=syx[iy+(ipy*2+3)*NY][ix+(ipx*2+3)*NX];
	wsum+=w[ipy+1][ipx+1];
      }
    }
  }
}

//Constructor
ChargeShare::ChargeShare (double width_y, double width_x, double sigma, double ll, int NdivY=20, int NdivX=20) {
  //   http://blog.northcol.org/2012/01/14/mdarray/
  NY=NdivY;
  NX=NdivX;
  wx=width_x;
  wy=width_y;
  sig=sigma;
  leak=ll;

  double *ey=new double[NdivY*8+1];
  double *ex=new double[NdivX*8+1];
  double wx2=wx*wx/sig/sig/NX/NX;
  double wy2=wy*wy/sig/sig/NY/NY;

  syx = new double*[NY*6+1];
  for (int i = 0; i < NY*6+1; i++) {
    syx[i] = new double[NX*6+1];
  }

  for( int iy= -NY*4;iy<= NY*4;iy++) {ey[iy+NY*4]=exp(-iy*iy*wy2)+leak; };
  for( int ix= -NX*4;ix<= NX*4;ix++) {ex[ix+NX*4]=exp(-ix*ix*wx2)+leak; };
    
  double sum;
  for(int iy= -NY*3;iy<= NY*3;iy++) {
    for(int ix= -NX*3;ix<= NX*3;ix++) { 
      sum=0.0;
      for(int jy= -NY;jy<= NY;jy++) {
	for(int jx= -NX;jx<= NX;jx++) {
	  sum=sum+ey[jy+iy+NY*4]*ex[jx+ix+NX*4];
	}
      }
      syx[iy+NY*3][ix+NX*3]=sum;
    }
  }
}


  
/*
   Charge share. Assumption: the charge in silicon "somehow" spread with gaussian with sigma "sig".
   The gaussian function is integrated in the pixel. center and +/- 1 neighbors. 
   Also an additional parameter "leak" is introduced to spread charge as a cross talk.
   You can set it 0 to disable.   The intergrasion is done in mesh size specified by NX and NY.
   You can set them to 20 (One pixel is subdivided to 40).  The est root program is  build/chargeshare.C.
*/


