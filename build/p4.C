// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x p2.C
#include <iostream>
#include <sstream>

//void p2() {
{
  TCanvas* c1 = new TCanvas("c1","",20,20,600,600);
  c1 -> Divide(2,2);


  const Int_t NRGBs = 5;   //Steps
  const Int_t NCont = 255; //Resolution
 
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.80, 1.00 };
  Double_t Red[NRGBs]   = { 1.00, 0.30, 0.67, 1.00, 0.51 };
  Double_t Green[NRGBs] = { 1.00, 0.61, 0.80, 0.20, 0.00 };
  Double_t Blue[NRGBs]  = { 1.00, 0.99, 0.30, 0.30, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, Red, Green, Blue, NCont);
  gStyle->SetNumberContours(NCont);
  TFile f("B4_2MeV.root");
//  TFile f("B4_photon_20keV.root");
  TNtuple* tin=(TNtuple*)f.Get("B4");
  Int_t NPixXY, NPixX, NPixY,Nhits,Ixy,Nbuff;
  Double_t E;
  Int_t Apix[300];
  std::stringstream ss;
  Double_t Epix[300];
  //------------------------  
  c1 -> cd(1);
  TH1D* hist1 = (TH1D*)f.Get("EDepl");
  hist1->Draw("HIST");

  //------------------------  
  c1 -> cd(3);
  tin   -> Draw("Nhits");



  //------------------------  
  tin->SetBranchAddress("NPixXY", &NPixXY);
  tin->SetBranchAddress("NBuff", &Nbuff);
  tin->SetBranchAddress("EDepl", &E);
  tin->SetBranchAddress("Nhits", &Nhits);


  Int_t nhitmax=0;  

  
  //  analysisManager->FinishNtuple();
  const Int_t Nev = tin->GetEntries();
  tin->GetEntry(0);
  NPixY=NPixXY/1000;
  NPixX=NPixXY%1000;
  cout << "Nevents=" << Nev << " NPixY/NPixX=" << NPixY << "  "<< NPixX <<endl;
  TH2F *pixel0 = new TH2F("pixel0","pixel0",NPixX,0.0,NPixX,NPixY,0.0,NPixY);
  TH2F *pixel1 = new TH2F("pixel1","pixel1",NPixX,0.0,NPixX,NPixY,0.0,NPixY);
  TH2F *pixel2 = new TH2F("pixel2","pixel1",NPixX,0.0,NPixX,NPixY,0.0,NPixY);

  for(int i=0;i<Nbuff;i++) {
    ss.str(""); ss<< "IADR" << i;
    tin->SetBranchAddress(ss.str().c_str(),Apix+i);
    ss.str(""); ss<< "E" << i;
    tin->SetBranchAddress(ss.str().c_str(),Epix+i);
  }

  for(int ievent=0; ievent<Nev;ievent++) {
    tin->GetEntry(ievent);
    for(int i=0;i<Nhits;i++){
      int il= Apix[i]/1000000;
      int iy= (Apix[i]-il*1000000)/1000;
      int ix= Apix[i] % 1000;
      if(Nhits>nhitmax) cout << "MM Il "<<il <<" Iy " << iy << " Ix " << ix << " E " << Epix[i] << endl;
      if(il==0) pixel0->Fill(ix,iy,Epix[i]);
      if(il==1) pixel1->Fill(ix,iy,Epix[i]);
      if(il==2) pixel2->Fill(ix,iy,Epix[i]);
    }

    if (Nhits >nhitmax) {
      nhitmax=Nhits; 
      cout << "Entry is " << Nhits << endl; 
    }
  }
  //  int ch;
  c1 -> cd(2);
  pixel0->Draw("colz");
  pixel0->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside

  c1 -> cd(3);
  pixel1->Draw("colz");
  pixel1->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside

  c1 -> cd(4);
  pixel2->Draw("colz");
  pixel2->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside



  cout << "Nhitmax is "<< nhitmax << endl;

}
