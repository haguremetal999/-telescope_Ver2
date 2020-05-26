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
  //  std::stringstream ss;

  string ss;
  std::string filename="wdata.tmp";
  std::ifstream fin(filename);
  std::ofstream fout("test.csv");
  //------------------------  

  //  cout << "FILE is opened" << endl;


  //------------------------  

  int dummy;
  double pos;
  double e[128]={0.0};
  int xx=-10,ix0=7,ix1=15;
  double ee=-1.0;
  fout << "E";
  for(int i=ix0; i<ix1;i++) {fout << " I" << i ;}
  fout << endl;
  while(!fin.eof()) {
    fin >> ss;
    if (ss=="I") { fin >> dummy; pos=dummy*0.25;}
    else if (ss=="Y" || ss=="L")  {fin >> dummy;}
    else if (ss=="E") {fin >> ee;} 
    else if (ss=="X") {fin >> xx;}
    else if (ss=="EVENT") {
      double sum;
      fout << pos ;
      for (xx=ix0; xx<ix1; xx++) { fout << ", " << e[xx] ;sum=sum+e[xx];}
      fout << ", " << pos ;
      for (xx=ix0; xx<ix1; xx++) { fout << ", " << e[xx]/sum ;}
      for (xx=0; xx< 128; xx++)   e[xx]=0;

      fout << endl;
    }
    else cout << ss << endl;
    if(ee>0 && xx>=0){
      e[xx]=e[xx]+ee;
      ee=-1.0;
      xx=-1;
    }
  }
  fout.close();
}

