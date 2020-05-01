// root[0] .x plotHisto.C

{
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  
  // Draw histos filled by Geant4 simulation 
  //   

  // Open file filled by Geant4 simulation 
//  TFile f("B4.root");
//  TFile f("B4_3MeV.root");
  TFile f("B4_2MeV.root");

  // Create a canvas and divide it into 2x2 pads
  TCanvas* c1 = new TCanvas("c1", "", 20, 20, 1000, 400);
  c1->Divide(4,1);
  
  // Draw Eabs histogram in the pad 1
  c1->cd(1);
  TH1D* hist1 = (TH1D*)f.Get("ECmos");
  hist1->Draw("HIST");
  
  // Draw Labs histogram in the pad 2
  c1->cd(2);
  TH1D* hist2 = (TH1D*)f.Get("EDepl");
  hist2->Draw("HIST");
  
  // Draw Egap histogram in the pad 3
  // with logaritmic scale for y
  TH1D* hist3 = (TH1D*)f.Get("EWafer");
  c1->cd(3);
//  gPad->SetLogy(1);
  hist3->Draw("HIST");

  TH1D* hist4 = (TH1D*)f.Get("TDepl");
  c1->cd(4);
  hist4->Draw("HIST");


  if(0) {
  // Draw Lgap histogram in the pad 4
  // Draw Eabs histogram in the pad 1
  c1->cd(2);
  TH1D* hist4 = (TH1D*)f.Get("LCmos");
  hist4->Draw("HIST");
  
  // Draw Labs histogram in the pad 2
  c1->cd(4);
  TH1D* hist5 = (TH1D*)f.Get("LDepl");
  hist5->Draw("HIST");
  
  // Draw Egap histogram in the pad 3
  // with logaritmic scale for y
  TH1D* hist6 = (TH1D*)f.Get("LWafer");
  c1->cd(6);
//  gPad->SetLogy(1);
  hist6->Draw("HIST");
  }
  // Draw Lgap histogram in the pad 4
  // with logaritmic scale for y
//  c1->cd(4);
//  gPad->SetLogy(1);
//  TH1D* hist4 = (TH1D*)f.Get("Lgap");
//  hist4->Draw("HIST");
}  
