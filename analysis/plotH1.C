// ROOT macro file for plotting example B4 ntuple
// 
// Can be run from ROOT session:
// root[0] .x plotNtuple.C
#include <iostream>
#include <sstream>

void plotH1() {

  cout << "The program is obsolete"<< endl;
  return;
  
TFile f("B4_2MeV.root");
TNtuple* n=(TNtuple*)f.Get("B4");
//Double_t val[1000];
//tin->SetBranchAddress("mode", &mode);
//tin->SetBranchAddress("val", val);
 
//const Int_t N = tin->GetEntries();
// TH2F *h2 = new TH2F("htest","Test",50,0.0,50.0,50,0.0,50.0)
 int i=0,j,k;
 double a;
  std::stringstream ss;
//dd string ss;
 for (j=0;j<100 ;j++){
   for (k=0;k<10 ;k++) {
     ss.str("");
     ss << "pixel" <<i;
     cout << ss.str() << endl;
     n->Branch(ss.str().c_str(),&a);
     cout << a <<endl;
     i++;
   }
 }
//delete f;
delete n;

}  

 
//for (Int_t ientry = 0; ientry < N; ientry++) {
//    tin->GetEntry(ientry);
//    // <-- *** ここで、ientry番目のブランチの値（mode, val[100]）を取得する **
//    // この後は、mode, val[100]の値を使って、自分の好きなように解析する
//    printf("mode:%d, val[0]:%f\n", mode, val[0]);
//}
