// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x p2.C
#include <iostream>
#include <sstream>

//void p2() {
{
  TCanvas* c1 = new TCanvas("c1","",20,20,400,800);
   c1 -> Divide(1,2);


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

  TH2F *pi00 = new TH2F("pi00","pixel0",400,-40.0,40.0,400,-40.0,40.0);
  TH2F *pi01 = new TH2F("pi01","pixel1",400,-40.0,40.0,400,-40.0,40.0);
  TH2F *pi02 = new TH2F("pi02","pixel2",400,-40.0,40.0,400,-40.0,40.0);


  for(int i=0;i<Nbuff;i++) {
    ss.str(""); ss<< "IADR" << i;
    tin->SetBranchAddress(ss.str().c_str(),Apix+i);
    ss.str(""); ss<< "E" << i;
    tin->SetBranchAddress(ss.str().c_str(),Epix+i);
  }

  for(int ievent=0; ievent<Nev;ievent++) {
    tin->GetEntry(ievent);
    double esum0=0,xsum0=0,ysum0=0;
    double esum1=0,xsum1=0,ysum1=0;
    double esum2=0,xsum2=0,ysum2=0;
    for(int i=0;i<Nhits;i++){
      int il= Apix[i]/1000000;
      int iy= (Apix[i]-il*1000000)/1000;
      int ix= Apix[i] % 1000;
      if(Nhits>nhitmax) cout << "MM Il "<<il <<" Iy " << iy << " Ix " << ix << " E " << Epix[i] << endl;

      if(il==0 ) {
	//	pixel0->Fill(ix,iy,Epix[i]);
	cout << ievent << " " << il <<" Iy " << iy << " Ix " << ix << " E " << Epix[i] << endl;
        esum0 += Epix[i];
	xsum0 += ix*Epix[i];
	ysum0 += iy*Epix[i];
      }

      if(il==1 ) {
	//	pixel1->Fill(ix,iy,Epix[i]);
	cout << ievent << " " << il <<" Iy " << iy << " Ix " << ix << " E " << Epix[i] << endl;
        esum1 += Epix[i];
	xsum1 += ix*Epix[i];
	ysum1 += iy*Epix[i];
      }

      if(il==2 ) {
	//	pixel2->Fill(ix,iy,Epix[i]);
	cout << ievent << " " << il <<" Iy " << iy << " Ix " << ix << " E " << Epix[i] << endl;
        esum2 += Epix[i];
	xsum2 += ix*Epix[i];
	ysum2 += iy*Epix[i];
      }

    }
    if(esum1>5 && esum2>5.0 && esum0>5) {
      pi00 -> Fill (xsum1/esum1-xsum0/esum0, xsum0/esum0);
      pi01 -> Fill (ysum1/esum1-ysum0/esum0, ysum1/esum1);
    };
    //    getchar();

    if (Nhits >nhitmax) {
      nhitmax=Nhits; 
      cout << "Entry is " << Nhits << endl; 
    }
  }
  //  int ch;
  c1 -> cd(1);
  pi00->Draw("colz");
  pi00->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside
  c1 -> cd(2);
  pi01->Draw("colz");
  pi01->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside

  cout << "Nhitmax is "<< nhitmax << endl;

}
