// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x p2.C
#include <iostream>
#include <sstream>
#include <fstream>
//using namespace std;
//void p2() {
{
  TCanvas* c1 = new TCanvas("c1","",20,20,600,900);
  c1 -> Divide(2,3);

  const Int_t NRGBs = 5;   //Steps
  const Int_t NCont = 255; //Resolution
 
  Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.80, 1.00 };
  Double_t Red[NRGBs]   = { 1.00, 0.30, 0.67, 1.00, 0.51 };
  Double_t Green[NRGBs] = { 1.00, 0.61, 0.80, 0.20, 0.00 };
  Double_t Blue[NRGBs]  = { 1.00, 0.99, 0.30, 0.30, 0.00 };
  TColor::CreateGradientColorTable(NRGBs, stops, Red, Green, Blue, NCont);
  gStyle->SetNumberContours(NCont);
  TFile f("../B4_2MeV.root");
//  TFile f("B4_photon_20keV.root");
  TNtuple* tin=(TNtuple*)f.Get("B4");
  Int_t NPixXY, NPixX, NPixY,Nhits,Ixy,Nbuff;
  Double_t E;
  Int_t Apix[300];
  std::stringstream ss;
  Double_t Epix[300];
  double F=0.26967233145831580803;
  double beamX0;
  //  double beamY0;

  std::string filename="wdata.tmp";
  std::ofstream fout(filename,std::ios::out);
  //------------------------  

  //  cout << "FILE is opened" << endl;


  //------------------------  
  tin->SetBranchAddress("NPixXY", &NPixXY);
  tin->SetBranchAddress("NBuff", &Nbuff);
  tin->SetBranchAddress("Nhits", &Nhits);
  tin->SetBranchAddress("BeamPosX0", &beamX0);
  //                         BeamPOSX0
  //  tin->SetBranchAddress("BeamPosY0", &beamY0);



  Int_t nhitmax=0;  
  
  //  analysisManager->FinishNtuple();
  Int_t Nev = tin->GetEntries();
  tin->GetEntry(0);
  NPixY=NPixXY/1000;
  NPixX=NPixXY%1000;
  cout << "Nevents=" << Nev << " NPixY/NPixX=" << NPixY << "  "<< NPixX <<endl;
  double rg=20.0;
  double rg2=0.002;
  TH2F *pi00 = new TH2F("pi00","fpix",400,-20.0,20.0,400,-20.0,20.0);
  TH2F *pi01 = new TH2F("pi01","sofist",400,-50.0,50.0,400,-50.0,50.0);
  TH2F *pi02 = new TH2F("pi02","ang1/ang0",400,-1.0,1.0,400,-1.0,1.0);
  TH1F *h000 = new TH1F("h00", "fpix", 400, -10.0,10.0);
  TH1F *h001 = new TH1F("h01", "sofist", 400, -10.0,10.0);
    TH1F *h002 = new TH1F("h02", "ang1-ang0", 400, -20.0,20.0);
  //   TH1F *h002 = new TH1F("h02", "ang1-ang0", 400, -5.0,5.0);
       //   TH1F *h002 = new TH1F("h02", "ang1-ang0", 400, -1.0,1.0);


#define NL (6)
  Double_t e[NL],x[NL],y[NL];
  Int_t hits[NL];
  Double_t w[NL]={8,8,20,20,8,8};  //Pixel size um
  Double_t g[NL]={1,1,100,100,1,1};  //Resolution um square
  Double_t z[NL]={0,30000,60000,90000,120000,150000};  //z of the sensors
  Double_t    ofs[NL]={64-0.5,64-0.5,25-0.5,25-0.5,64-0.5,64-0.5};
  for(int i=0;i<Nbuff;i++) {
    ss.str(""); ss<< "IADR" << i;
    tin->SetBranchAddress(ss.str().c_str(),Apix+i);
    ss.str(""); ss<< "E" << i;
    tin->SetBranchAddress(ss.str().c_str(),Epix+i);
  }


  for(int ievent=0; ievent<Nev;ievent++) {
    tin->GetEntry(ievent);
    for(int il=0;il<NL;il++) {e[il]=0;x[il]=0;y[il]=0;hits[il]=0;}

    int dumplayer=2;
    int dumpthisevent=0;
    int dumppix=10;
    for(int i=0;i<Nhits;i++){
      int il= Apix[i]/1000000;
      int iy= (Apix[i]-il*1000000)/1000;
      int ix= Apix[i] % 1000;
      if(il>NL)  cout << "IL " << il << endl;
      hits[il] += 1;
      e[il] += Epix[i];
      x[il] += ix*Epix[i];
      y[il] += iy*Epix[i];
      if(il==dumplayer && ix==dumppix) dumpthisevent=1;
      if(il==dumplayer && ix==dumppix+1) dumpthisevent=1;
    }
    if(0& dumpthisevent) {
      for(int i=0;i<Nhits;i++){
	int il= Apix[i]/1000000;
	if(il==dumplayer)  {
	  int iy= (Apix[i]-il*1000000)/1000;
	  int ix= Apix[i] % 1000;
	  cout << " Event "<<ievent<<", L=" << il <<", Y=" << iy <<", X="<< ix <<", E="<< Epix[i] <<endl;
	  fout << " I "<<ievent<<" L " << il <<" Y " << iy <<" X "<< ix <<" E "<< Epix[i] <<endl;
	}
      }
      fout << "EVENT" << endl;
    }

    for(int il=0;il<NL;il++) if(e[il]>0.0) {	
	x[il] =w[il]*(x[il]/e[il]-ofs[il]);
	y[il] =w[il]*(y[il]/e[il]-ofs[il]); 
      }
    Double_t eth=5.0;
    if(e[0]>eth && e[1]>eth && e[2]>eth && e[3]>eth && e[4]>eth && e[5]>eth) {
      double xb=beamX0*1000;
      double x00=x[0]-4;
      double zz=16;
      while(1) {
	if (x00< 0 ) x00 = x00+zz;
	else if (x00>zz) x00 = x00-zz;
	else  break;
      }
      //      cout << " EVENT " <<ievent << " BeamX0 (um) " << xb << endl;
      pi00 -> Fill((x[0]+x[5])/2,(x[1]+x[4])/2);
      pi00 -> Fill(xb,xb);
      h000 -> Fill((x[0]+x[5])/2-(x[1]+x[4])/2);

      pi01 -> Fill((x[0]+2*x[1]+2*x[4]+x[5])/6,(x[2]+x[3])/2);
      pi01 -> Fill(x[0],x[0]);
      h001->  Fill((x[0]+x[1]+x[4]+x[5])/4-(x[2]+x[3])/2);

#if 0   //0123 vs 45
      double angx0=(x[3]-x[0])/(z[3]-z[0]);
      double angx1=(x[5]-x[4])/(z[5]-z[4]);
      double angy0=(y[3]-y[0])/(z[3]-z[0]);
      double angy1=(y[5]-y[4])/(z[5]-z[4]);

#elif 0   //012 vs 345
      double gs0 =1/g[0]+1/g[1]+1/g[2];
      double sx0 =(x[0]/g[0]+x[1]/g[1]+x[2]/g[2])/gs0;
      double sz0 =(z[0]/g[0]+z[1]/g[1]+z[2]/g[2])/gs0;
      double sxz0=(x[0]*z[0]/g[0]+x[1]*z[1]/g[1]+x[2]*z[2]/g[2])/gs0;
      double szz0=(z[0]*z[0]/g[0]+z[1]*z[1]/g[1]+z[2]*z[2]/g[2])/gs0;
      double angx0  =(sxz0-sx0*sz0)/(szz0-sz0*sz0);

      double gs1 =1/g[3]+1/g[4]+1/g[5];
      double sx1 =(x[3]/g[3]+x[4]/g[4]+x[5]/g[5])/gs1;
      double sz1 =(z[3]/g[3]+z[4]/g[4]+z[5]/g[5])/gs1;
      double sxz1=(x[3]*z[3]/g[3]+x[4]*z[4]/g[4]+x[5]*z[5]/g[5])/gs1;
      double szz1=(z[3]*z[3]/g[3]+z[4]*z[4]/g[4]+z[5]*z[5]/g[5])/gs1;
      double angx1  =(sxz1-sx1*sz1)/(szz1-sz1*sz1);
#elif 1  //0123 vs 45
      double gs0 =1/g[0]+1/g[1]+1/g[2]+1/g[3];
      double sx0 =(x[0]/g[0]+x[1]/g[1]+x[2]/g[2]+x[3]/g[3])/gs0;
      double sz0 =(z[0]/g[0]+z[1]/g[1]+z[2]/g[2]+z[3]/g[3])/gs0;
      double sxz0=(x[0]*z[0]/g[0]+x[1]*z[1]/g[1]+x[2]*z[2]/g[2]+x[3]*z[3]/g[3])/gs0;
      double szz0=(z[0]*z[0]/g[0]+z[1]*z[1]/g[1]+z[2]*z[2]/g[2]+z[3]*z[3]/g[3])/gs0;
      double angx0  =(sxz0-sx0*sz0)/(szz0-sz0*sz0);

      double gs1 =1/g[4]+1/g[5];
      double sx1 =(x[4]/g[4]+x[5]/g[5])/gs1;
      double sz1 =(z[4]/g[4]+z[5]/g[5])/gs1;
      double sxz1=(x[4]*z[4]/g[4]+x[5]*z[5]/g[5])/gs1;
      double szz1=(z[4]*z[4]/g[4]+z[5]*z[5]/g[5])/gs1;
      double angx1  =(sxz1-sx1*sz1)/(szz1-sz1*sz1);
#endif

      pi02 -> Fill (angx0*1000,angx1*1000);
      h002 -> Fill (angx1*1000-angx0*1000);


    };
    
    if (Nhits >nhitmax) {
      nhitmax=Nhits; 
      if(0) {
	cout << "Nhits  " << Nhits ;
	for(int il=0; il<NL;il++) cout << " " << hits[il];
	cout << endl; 
      }
    }
  }
  //  int ch;
  c1 -> cd(1);
  pi00->Draw("colz");
  pi00->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.3);  //put aside
  c1 -> cd(2);
  h000->Draw("");
  h000->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.3);  //put aside

  c1 -> cd(3);
  pi01->Draw("colz");
  pi01->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.3);  //put aside
  c1 -> cd(4);
  h001->Draw("");
  h001->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.5);  //put aside

  c1 -> cd(5);
  pi02->Draw("colz");
  pi02->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.3);  //put aside
  c1 -> cd(6);
  h002->Draw("");
  h002->SetTitle(0);         //Erase title
  gStyle->SetStatX(0.5);  //put aside

  fout.close();
  cout << "Nhitmax is "<< nhitmax << endl;
  cout << "More command" << endl << "new TBrowser" << endl;
  cout << "TH1D* hist4 = (TH1D*)f.Get(\"TDepl\");  hist4->Draw(\"\"); hist4 -> Fit(\"expo\");"  << endl;
}
