// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x p2.C
#include <iostream>
#include <sstream>

{
  TCanvas* c1 = new TCanvas("c1","",20,20,800,800);
  c1-> Divide(2,2);
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
  Double_t wx=8.0,wy=8.0, sig=3.0;          // um
  Double_t wx2=wx*wx/sig/sig/NX/NX,wy2=wy*wy/sig/sig/NY/NY; // um

  Double_t ey[NY*8+1],ex[NX*8+1];
  TH2F *hist0 = new TH2F("hist0","hist0",6*NX+1,1.5*wx*(-NX*2-0.5)/NX,1.5*wx*(NX*2+0.5)/NX,6*NY+1,1.5*wy*(-NY*2-0.5)/NY,1.5*wy*(NY*2+0.5)/NY);
  TH2F *hist1 = new TH2F("hist1","hist1",2*NX,0.0,2*wx,2*NY,0.0,2*wy);
  TH2F *hist2 = new TH2F("hist2","hist2",2*NX,0.0,2*wx,2*NY,0.0,2*wy);
  TH2F *hist3 = new TH2F("hist3","hist3",2*NX,0.0,2*wx,2*NY,0.0,2*wy);
  TH2F *hist4 = new TH2F("hist4","hist4",2*NX,0.0,2*wx,2*NY,0.0,2*wy);

  Double_t leak=0.005;
  for( Int_t iy=-NY*4;iy<=NY*4;iy++) {ey[iy+NY*4]=exp(-iy*iy*wy2)+leak; if(0) {cout << -iy*iy*wy2 << " IY  " << ey[iy+NY*4]<<endl;} };
  for( Int_t ix=-NX*4;ix<=NX*4;ix++) {ex[ix+NX*4]=exp(-ix*ix*wx2)+leak; if(0) {cout << -ix*ix*wx2 << " IX  " << ex[ix+NX*4]<<endl;} };
 
  Double_t syx[NY*6+1][NX*6+1];
  Double_t sum,sumx;
  for(Int_t iy=-NY*3;iy<=NY*3;iy++) {
    for(Int_t ix=-NX*3;ix<=NX*3;ix++) { 
      sum=0.0;
      for(Int_t jy=iy-NY;jy<=iy+NY;jy++) {
        sumx=0;
	for(Int_t jx=ix-NX;jx<=ix+NX;jx++) {
      	  sumx=sumx+ex[jx+NX*4];
	}
	sum=sum+sumx*ey[jy+NY*4];
      }
      if(0)      hist0->Fill(wx*ix/NX,wy*iy/NY,sum/NX/NY);
      syx[iy+NY*3][ix+NX*3]=sum;
    }
  }
  if(1) {

    for( Int_t jy=-NY;jy<NY;jy++) {
      for( Int_t jx=-NX;jx<NX;jx++) {
	Double_t sum=0;
	for(Int_t ipy=-NY*2;ipy<=NY*2;ipy+=NY*2) {
	  for(Int_t ipx=-NX*2;ipx<=NX*2;ipx+=NX*2) {
            if(jy+ipy+3*NY<0 || jy+ipy+3*NY>6*NY || jx+ipx+3*NX<0 || jx+ipx+2*NY>6*NX) { 
	      cout << "Out of range " << jy << " "<< jx << " "<< ipy << " "<< ipx << " " << endl;
	    } else {
	      sum=sum+syx[jy+ipy+3*NY][jx+ipx+3*NX];
	    }
	  }
	}
	if(1){
	hist1 ->Fill(wx*(jx+NX)/NX,wy*(jy+NY)/NY,syx[-jy+5*NY][ jx+3*NX]/sum);
	hist2 ->Fill(wx*(jx+NX)/NX,wy*(jy+NY)/NY,syx[ jy+3*NY][ jx+3*NX]/sum);
	hist3 ->Fill(wx*(jx+NX)/NX,wy*(jy+NY)/NY,syx[ jy+3*NY][-jx+5*NX]/sum);
	hist4 ->Fill(wx*(jx+NX)/NX,wy*(jy+NY)/NY,syx[-jy+NY*5][-jx+5*NX]/sum);
	}
      }
    }
  }



  int mode_kesu=0;
  gStyle->SetOptStat(mode_kesu);

  c1->cd(1); hist1->Draw("colz");
  c1->cd(3); hist2->Draw("colz");
  c1->cd(4); hist3->Draw("colz");
  c1->cd(2); hist4->Draw("colz");

}
