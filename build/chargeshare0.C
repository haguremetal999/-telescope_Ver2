// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x p2.C
#include <iostream>
#include <sstream>

{
  TCanvas* c1 = new TCanvas("c1","",20,20,800,400);
  c1-> Divide(2,1);
  const Int_t NRGBs = 5;   //Steps
  const Int_t NCont = 255; //Resolution
 
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.80, 1.00 };
  Double_t Red[NRGBs]   = { 1.00, 0.30, 0.67, 1.00, 0.51 };
  Double_t Green[NRGBs] = { 1.00, 0.61, 0.80, 0.20, 0.00 };
  Double_t Blue[NRGBs]  = { 1.00, 0.99, 0.30, 0.30, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, Red, Green, Blue, NCont);
  gStyle->SetNumberContours(NCont);


#define NX (20)
#define NY (20)
  Double_t wx=50.0,wy=50.0, sig=10.0;          // um
  Double_t wx2=wx*wx/sig/sig/NX/NX,wy2=wy*wy/sig/sig/NY/NY; // um

  Double_t ey[NY*8+1],ex[NX*8+1];
  TH2F *hist1 = new TH2F("hist1","hist1",4*NX+1,wx*(-NX*2-0.5)/NX,wx*(NX*2+0.5)/NX,4*NY+1,wy*(-NY*2-0.5)/NY,wy*(NY*2+0.5)/NY);
  //  TH2F *hist2 = new TH2F("hist2","hist2",2*NX,-wx,wx,2*NY,-wy,wy);
  TH2F *hist2 = new TH2F("hist2","hist2",2*NX,0.0,2*wx,2*NY,0.0,2*wy);
  for( Int_t iy=-NY*4;iy<=NY*4;iy++) {ey[iy+NY*4]=exp(-iy*iy*wy2); if(0) {cout << -iy*iy*wy2 << " IY  " << ey[iy+NY*4]<<endl;} };
  for( Int_t ix=-NX*4;ix<=NX*4;ix++) {ex[ix+NX*4]=exp(-ix*ix*wx2); if(0) {cout << -ix*ix*wx2 << " IX  " << ex[ix+NX*4]<<endl;} };
 
  Double_t syx[NY*4+1][NX*4+1];
  Double_t sum;
  for(Int_t iy=-NY*2;iy<=NY*2;iy++) {
     for(Int_t ix=-NX*2;ix<=NX*2;ix++) { 
       sum=0.0;
      for(Int_t jy=iy-NY;jy<=iy+NY;jy++) {
	for(Int_t jx=ix-NX;jx<=ix+NX;jx++) {
      	  sum=sum+ey[jy+NY*4]*ex[jx+NX*4];
	}
      }
      hist1->Fill(wx*ix/NX,wy*iy/NY,sum/NX/NY);
      syx[iy+NY*2][ix+NX*2]=sum;
    }
  }
  if(1) {

    for( Int_t jy=-NY;jy<NY;jy++) {
      for( Int_t jx=-NX;jx<NX;jx++) {
	Double_t sum=0;
	for(Int_t ipy=-NY;ipy<=NY;ipy+=NY) {
	  for(Int_t ipx=-NX;ipx<=NX;ipx+=NX) {
            if(jy+ipy+2*NY<0 || jy+ipy+2*NY>4*NY || jx+ipx+2*NX<0 || jx+ipx+2*NY>4*NX) { 
	      cout << "Out of range " << jy << " "<< jx << " "<< iy << " "<< ix << " " << endl;
	    } else {
	      sum=sum+syx[jy+ipy+2*NY][jx+ipx+2*NX];
	      //	      cout << "C" << jy+ipy << " and " <<jx+ipx << " syx " << syx[jy+ipy+2*NY][jx+ipx+2*NX] << "   SUM "<< sum << endl; 
	    }
	  }
	}
	//	cout << "E " << jy << " and " <<jx << "S " << sum << " syx "<< syx[jy+2*NY][jx+2*NX] << " " << syx[jy+2*NY][jx+2*NX]/sum <<  endl; 
	hist2 ->Fill(wx*(jx+NX)/NX,wy*(jy+NY)/NY,syx[jy+2*NX][jx+2*NX]/sum);
      }
    }
  }
  c1->cd(1); hist1->Draw("colz");
  c1->cd(2); hist2->Draw("colz");

}
