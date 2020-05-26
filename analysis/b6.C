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
  TFile f("B4_2MeV.root");
//  TFile f("B4_photon_20keV.root");
  TNtuple* tin=(TNtuple*)f.Get("B4");
  Int_t NPixXY, NPixX, NPixY,Nhits,Ixy,Nbuff;
  Double_t E;
  Int_t Apix[300];
  std::stringstream ss;
  Double_t Epix[300];
  //------------------------  

  cout << "FILE is opened" << endl;


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
  double rg=20.0;
  double rg2=0.002;
  TH2F *pi00 = new TH2F("pi00","pixel0",400,-500.0,500.0,400,-rg,rg);
  TH2F *pi01 = new TH2F("pi01","pixel1",400,-500.0,500.0,400,-100,100);
  TH2F *pi02 = new TH2F("pi02","pixel2",400,-rg2,rg2,400,-rg2, rg2);
  TH2F *pi03 = new TH2F("pi03","pixel3",400,-rg2,rg2,400,-rg2, rg2);
  TH1F *h001 = new TH1F("h001", "mRadian", 200, -10.0,10.0);
  TH1F *h002 = new TH1F("h002", "dx", 100, -200.0,200.0);


#define NL (6)
  Double_t e[NL],x[NL],y[NL];
  Int_t hits[NL];
  Double_t w[NL]={8,8,20,20,8,8};  //Pixel size um
  Double_t g[NL]={1,1,100,100,1,1};  //Resolution um square
  Double_t z[NL]={0,30000,60000,90000,120000,150000};  //z of the sensors
  Int_t    ofs[NL]={64,64,25,25,64,64};
  for(int i=0;i<Nbuff;i++) {
    ss.str(""); ss<< "IADR" << i;
    tin->SetBranchAddress(ss.str().c_str(),Apix+i);
    ss.str(""); ss<< "E" << i;
    tin->SetBranchAddress(ss.str().c_str(),Epix+i);
  }


  for(int ievent=0; ievent<Nev;ievent++) {
    tin->GetEntry(ievent);
    for(int il=0;il<NL;il++) {e[il]=0;x[il]=0;y[il]=0;hits[il]=0;}

    for(int i=0;i<Nhits;i++){
      int il= Apix[i]/1000000;
      int iy= (Apix[i]-il*1000000)/1000;
      int ix= Apix[i] % 1000;
      if(il>NL)  cout << "IL " << il << endl;
      hits[il] += 1;
      e[il] += Epix[i];
      x[il] += ix*Epix[i];
      y[il] += iy*Epix[i];
    }
    for(int il=0;il<NL;il++) if(e[il]>0.0) {	
	x[il] =w[il]*(x[il]/e[il]+0.5-ofs[il]);//+0.001*z[il]; 
	y[il] =w[il]*(y[il]/e[il]+0.5-ofs[il]); 
      }
    Double_t eth=5;
    if(e[0]>eth && e[1]>eth && e[2]>eth && e[3]>eth && e[4]>eth && e[5]>eth) {
      cout << "X" << x[0] << endl;
      pi00 -> Fill (x[2],x[2]-x[3]);
      pi01 -> Fill (y[0],y[2]-y[3]);

#if 0
      double angx0=(x[2]-x[0])/(z[5]-z[3]),
   	     angx1=(x[5]-x[3])/(z[5]-z[3]),
	     angy0=(x[2]-x[0])/(z[2]-z[0]),
	     angy1=(x[5]-x[3])/(z[5]-z[3]);
#elif 0
      double angx0=(x[1]-x[0])/(z[0]-z[1]),
	angx1=(x[2]-x[0])/(z[2]-z[0]),
	angy0=(x[1]-x[0])/(z[2]-z[1]),
	angy1=(x[2]-x[1])/(z[2]-z[1]);
#elif 1
      double gs0 =1/g[0]+1/g[1]+1/g[2];
      double sx0 =(x[0]/g[0]+x[1]/g[1]+x[2]/g[2])/gs0;
      double sz0 =(z[0]/g[0]+z[1]/g[1]+z[2]/g[2])/gs0;
      double sxz0=(x[0]*z[0]/g[0]+x[1]*z[1]/g[1]+x[2]*z[2]/g[2])/gs0;
      double szz0=(z[0]*z[0]/g[0]+z[1]*z[1]/g[1]+z[2]*z[2]/g[2])/gs0;
      double a0  =(sxz0-sx0*sz0)/(szz0-sz0*sz0);

      double gs1 =1/g[3]+1/g[4]+1/g[5];
      double sx1 =(x[3]/g[3]+x[4]/g[4]+x[5]/g[5])/gs1;
      double sz1 =(z[3]/g[3]+z[4]/g[4]+z[5]/g[5])/gs1;
      double sxz1=(x[3]*z[3]/g[3]+x[4]*z[4]/g[4]+x[5]*z[5]/g[5])/gs1;
      double szz1=(z[3]*z[3]/g[3]+z[4]*z[4]/g[4]+z[5]*z[5]/g[5])/gs1;
      double a1  =(sxz1-sx1*sz1)/(szz1-sz1*sz1);


#endif
      h001-> Fill((a1-a0)*1000);
      h002-> Fill(x[3]-x[2]);
      pi02 -> Fill (a0,a1);
	    //        pi03 -> Fill (angy0,angy1-angy0);


    };
    
    if (Nhits >nhitmax) {
      nhitmax=Nhits; 
      cout << "Entry is" << Nhits ;
      for(int il=0; il<NL;il++) cout << " " << hits[il];
      cout << endl; 
    }

  }
  //  int ch;
  c1 -> cd(1);
  pi00->Draw("colz");
  pi00->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.3);  //put aside
  c1 -> cd(2);
  h002->Draw("");
  h002->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.3);  //put aside


#if 1
  c1 -> cd(3);
  pi02->Draw("colz");
  pi02->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.3);  //put aside
  c1 -> cd(4);
  h001->Draw("");
  h001->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.3);  //put aside
#endif
  cout << "Nhitmax is "<< nhitmax << endl;
}
