// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x p2.C
#include <iostream>
#include <sstream>

//void p2() {
{
  TCanvas* c1 = new TCanvas("c1","",20,20,800,800);
   c1 -> Divide(2,2);


  const Int_t NRGBs = 5;   //Steps
  const Int_t NCont = 255; //Resolution
 
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.80, 1.00 };
  Double_t Red[NRGBs]   = { 1.00, 0.30, 0.67, 1.00, 0.51 };
  Double_t Green[NRGBs] = { 1.00, 0.61, 0.80, 0.20, 0.00 };
  Double_t Blue[NRGBs]  = { 1.00, 0.99, 0.30, 0.30, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, Red, Green, Blue, NCont);
  gStyle->SetNumberContours(NCont);
  TFile f("B4_2MeV0.root");
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
  TH2F *pixel0 = new TH2F("pixel0","pixel0",NPixX,0.0,NPixX,NPixY,0.0,NPixY);
  TH2F *pixel1 = new TH2F("pixel1","pixel1",NPixX,0.0,NPixX,NPixY,0.0,NPixY);
  TH2F *pixel2 = new TH2F("pixel2","pixel1",NPixX,0.0,NPixX,NPixY,0.0,NPixY);

  Pixelsize=40;
  TH2F *pixel5 = new TH2F("pixel5","pixel5",1500,0.0,1500,400,0.0,Pixelsize*80.0);
  TH2F *pixel6 = new TH2F("pixel6","pixel6",1500,0.0,1500,400,0.0,Pixelsize*80.0);
  TH2F *nhits5= new TH2F("pixel5","pixel5",1500,0.0,1500,400,0.0,20);

  TH2F *pixel7 = new TH2F("pixel5","pixel5",1500,0.0,1500,400,0.0,Pixelsize*80.0);
  TH2F *pixel8 = new TH2F("pixel6","pixel6",1500,0.0,1500,400,0.0,Pixelsize*80.0);
  TH2F *nhits9= new TH2F("pixel5","pixel5",1500,0.0,1500,400,0.0,20);


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
    int phits0=0;
    int phits1=0;
    int phits2=0;
    for(int i=0;i<Nhits;i++){
      int il= Apix[i]/1000000;
      int iy= (Apix[i]-il*1000000)/1000;
      int ix= Apix[i] % 1000;
      if(Epix[i]<0.000001) continue;

      if(il==0 ) {
	pixel0->Fill(ix,iy,Epix[i]);
	cout << ievent << " " << il <<" Iy " << iy << " Ix " << ix << " E " << Epix[i] << endl;
        esum0 += Epix[i];
	xsum0 += ix*Epix[i];
	ysum0 += iy*Epix[i];
	if (Epix[i]>1.00) phits0++;
      }

      if(il==1 ) {
	pixel1->Fill(ix,iy,Epix[i]);
	cout << ievent << " " << il <<" Iy " << iy << " Ix " << ix << " E " << Epix[i] << endl;
        esum1 += Epix[i];
	xsum1 += ix*Epix[i];
	ysum1 += iy*Epix[i];
	if (Epix[i]>1.00) phits1++;
      }

      if(il==2 ) {
	pixel2->Fill(ix,iy,Epix[i]);
	cout << ievent << " " << il <<" Iy " << iy << " Ix " << ix << " E " << Epix[i] << endl;
        esum2 += Epix[i];
	xsum2 += ix*Epix[i];
	ysum2 += iy*Epix[i];
	if (Epix[i]>1.00) phits2++;
      }

    }
    if(esum0>5.0) {
   //   printf(" PP %5d, %10.3f, %10.3f, %10.3f\n",ievent,xsum2/esum2, ysum2/esum2, esum2); 
      pixel5 -> Fill (ievent, Pixelsize*xsum0/esum0, esum0);
      pixel5 -> Fill (ievent, Pixelsize*ysum0/esum0+200.0, esum0);
      nhits5 -> Fill (ievent, phits0);
    }

    if(esum1>5.0) {
   //   printf(" PP %5d, %10.3f, %10.3f, %10.3f\n",ievent,xsum2/esum2, ysum2/esum2, esum2); 
      pixel7 -> Fill (ievent, Pixelsize*xsum1/esum1, esum1);
      pixel7 -> Fill (ievent, Pixelsize*ysum1/esum1, esum1);
      nhits9 -> Fill (ievent, phits1);
    }

    if (phits0+phits1+phits2 >nhitmax) {
      nhitmax=phits0+phits1+phits2;
      cout << "Entry is " << Nhits << endl; 
    }
  }
  //  int ch;
  c1 -> cd(1);
  nhits5->Draw("colz");
  nhits5->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside
  c1 -> cd(2);
  nhits9->Draw("colz");
  nhits9->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside

  //  int ch;
  c1 -> cd(3);
  pixel5->Draw("colz");
  pixel5->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside
  c1 -> cd(4);
  pixel7->Draw("colz");
  pixel7->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.9);  //put aside
  cout << "Nhitmax is "<< nhitmax << endl;


}
