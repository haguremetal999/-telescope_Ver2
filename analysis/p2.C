// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x p2.C
#include <iostream>
#include <sstream>

//void p2() {
{
  TCanvas* c1 = new TCanvas("c1","",20,20,600,300);
  c1 -> Divide(2,1);


  const Int_t NRGBs = 5;   //Steps
  const Int_t NCont = 255; //Resolution
 
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.80, 1.00 };
  Double_t Red[NRGBs]   = { 1.00, 0.30, 0.87, 1.00, 0.51 };
  Double_t Green[NRGBs] = { 1.00, 0.81, 0.60, 0.20, 0.00 };
  Double_t Blue[NRGBs]  = { 1.00, 0.50, 0.30, 0.30, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, Red, Green, Blue, NCont);
  gStyle->SetNumberContours(NCont);
  
  TFile f("B4_2MeV.root");
//  TFile f("B4_photon_20keV.root");
  TNtuple* tin=(TNtuple*)f.Get("B4");
  Int_t NPixX, NPixY;
  Double_t E;
  Double_t pixdata[300][300];
  std::stringstream ss;
  
  c1 -> cd(1);
  TH1D* hist1 = (TH1D*)f.Get("EDepl");
  hist1->Draw("HIST");

  c1 -> cd(2);
  tin->SetBranchAddress("NPixX", &NPixX);
  tin->SetBranchAddress("NPixY", &NPixY);
  tin->SetBranchAddress("EDepl", &E);
  
  //  analysisManager->FinishNtuple();
  const Int_t N = tin->GetEntries();
  tin->GetEntry(0);
  cout << "NPixY/NPixX=" << NPixY << "  "<< NPixX <<endl;
  TH2F *h2 = new TH2F("h2","h2",NPixX,0.0,NPixX,NPixY,0.0,NPixY);
  h2->Draw("color");
  int i=0;
  for(int iy=0;iy<NPixY;iy++) {
    for(int ix=0;ix<NPixX;ix++) {
      ss.str("");
      ss<< "Pixel" << i;
      tin->SetBranchAddress(ss.str().c_str(),&pixdata[iy][ix]);
      i++;
    }
  }

  cout << "Entry is " << N << endl; 
  int ch;
  for (Int_t ientry = 0; ientry < N; ientry++) {
    tin->GetEntry(ientry);   
//    cout << ientry<<" : ";
    for(int iy=0;iy<NPixY;iy++) {
      for(int ix=0;ix<NPixX;ix++) {
	if (pixdata[iy][ix]>0.0) {
//	  printf("%5d%5d%8.2f\n",iy,ix,pixdata[iy][ix]);
	  h2-> Fill(ix,iy,pixdata[iy][ix]);
	}
      }  
    }
  }
  h2->Draw("colz");
  h2->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside

  //  c1-> Update();
  // ch=getchar(); if(ch=='q') return;
}
