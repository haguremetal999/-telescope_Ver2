#define testclass_cxx
#include "testclass.h"
#include <vector>
#include <string>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TString.h>
#include <cstdlib>  // abs() for integer
#include <cmath>    // abs() for float, and fabs()
#include "AnalysisClass.h"

void testclass::Loop()
{
//   In a ROOT session, you can do:
//      root> .L testclass.C
//      root> testclass t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   
   bool DUTmode     = false;
   bool Trackermode = false;
   bool MeanCalmode = true;
   bool debug1 = true;   //hit number
   bool debug2 = false;  //IADR  setting
   bool debug3 = false;  //energy loss setting
   bool debug4 = false;  //first position
   bool debug5 = false;  //energy loss analysis
   bool debug6 = false;  //IADR analysis
   bool debug7 = false;  //beam reconstruction
   bool debug8 = false;  //hit number in each Pixcel check
   bool debug9 = false;  //non neighbor
   
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   int maxhits = 0;
   int evecut = 100;

   int posi_bin = 1000;
   int ene_bin =1000;
   int diff_bin = 1000;

   double tr_pitch = 30.0 * 1000; //[um]
   
   //*********************************************************** hit number check ********************************************************
   int hitl[nentries];
   double energylossl[nentries][200];
   
   std::cout << "********************************************************* hit number check *************************************************" << std::endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;

      hitl[jentry]=Nhits;
      if(debug1){
      std::cout << "Nhits = "  << hitl[jentry] << ", jentry = " << jentry <<std::endl;
      if(Nhits > maxhits){
	maxhits = Nhits;
      }
      }
   }
      std::cout << "maxhits = "  << maxhits <<std::endl;
      
      
   //*******************************************IADR & Energyloss setting ************************************************      
   int IADRl[nentries][200];
   int pos_X[nentries][200];
   int pos_Y[nentries][200];
   int ID[nentries][200];
   
   
   std::cout << "********************************* IADR & Energyloss setting *****************************************" << std::endl;
   for (Long64_t jentry=0; jentry<nentries;jentry++){
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;

     //IADR setting
       IADRl[jentry][0]=IADR0;
       IADRl[jentry][1]=IADR1;
       IADRl[jentry][2]=IADR2;
       IADRl[jentry][3]=IADR3;
       IADRl[jentry][4]=IADR4;
       IADRl[jentry][5]=IADR5;
       IADRl[jentry][6]=IADR6;
       IADRl[jentry][7]=IADR7;
       IADRl[jentry][8]=IADR8;
       IADRl[jentry][9]=IADR9;
       IADRl[jentry][10]=IADR10;
       IADRl[jentry][11]=IADR11;
       IADRl[jentry][12]=IADR12;
       IADRl[jentry][13]=IADR13;
       IADRl[jentry][14]=IADR14;
       IADRl[jentry][15]=IADR15;
       IADRl[jentry][16]=IADR16;
       IADRl[jentry][17]=IADR17;
       IADRl[jentry][18]=IADR18;
       IADRl[jentry][19]=IADR19;
       IADRl[jentry][20]=IADR20;
       IADRl[jentry][21]=IADR21;
       IADRl[jentry][22]=IADR22;
       IADRl[jentry][23]=IADR23;
       IADRl[jentry][24]=IADR24;
       IADRl[jentry][25]=IADR25;
       IADRl[jentry][26]=IADR26;
       IADRl[jentry][27]=IADR27;
       IADRl[jentry][28]=IADR28;
       IADRl[jentry][29]=IADR29;
       IADRl[jentry][30]=IADR30;
       IADRl[jentry][31]=IADR31;
       IADRl[jentry][32]=IADR32;
       IADRl[jentry][33]=IADR33;
       IADRl[jentry][34]=IADR34;
       IADRl[jentry][35]=IADR35;
       IADRl[jentry][36]=IADR36;
       IADRl[jentry][37]=IADR37;
       IADRl[jentry][38]=IADR38;
       IADRl[jentry][39]=IADR39;
       IADRl[jentry][40]=IADR40;
       IADRl[jentry][41]=IADR41;
       IADRl[jentry][42]=IADR42;
       IADRl[jentry][43]=IADR43;
       IADRl[jentry][44]=IADR44;
       IADRl[jentry][45]=IADR45;
       IADRl[jentry][46]=IADR46;
       IADRl[jentry][47]=IADR47;
       IADRl[jentry][48]=IADR48;
       IADRl[jentry][49]=IADR49;
       IADRl[jentry][50]=IADR50;
       IADRl[jentry][51]=IADR51;
       IADRl[jentry][52]=IADR52;
       IADRl[jentry][53]=IADR53;
       IADRl[jentry][54]=IADR54;
       IADRl[jentry][55]=IADR55;
       IADRl[jentry][56]=IADR56;
       IADRl[jentry][57]=IADR57;
       IADRl[jentry][58]=IADR58;
       IADRl[jentry][59]=IADR59;
       IADRl[jentry][60]=IADR60;
       IADRl[jentry][61]=IADR61;
       IADRl[jentry][62]=IADR62;
       IADRl[jentry][63]=IADR63;
       IADRl[jentry][64]=IADR64;
       IADRl[jentry][65]=IADR65;
       IADRl[jentry][66]=IADR66;
       IADRl[jentry][67]=IADR67;
       IADRl[jentry][68]=IADR68;
       IADRl[jentry][69]=IADR69;
       IADRl[jentry][70]=IADR70;
       IADRl[jentry][71]=IADR71;
       IADRl[jentry][72]=IADR72;
       IADRl[jentry][73]=IADR73;
       IADRl[jentry][74]=IADR74;
       IADRl[jentry][75]=IADR75;
       IADRl[jentry][76]=IADR76;
       IADRl[jentry][77]=IADR77;
       IADRl[jentry][78]=IADR78;
       IADRl[jentry][79]=IADR79;
       IADRl[jentry][80]=IADR80;
       IADRl[jentry][81]=IADR81;
       IADRl[jentry][82]=IADR82;
       IADRl[jentry][83]=IADR83;
       IADRl[jentry][84]=IADR84;
       IADRl[jentry][85]=IADR85;
       IADRl[jentry][86]=IADR86;
       IADRl[jentry][87]=IADR87;
       IADRl[jentry][88]=IADR88;
       IADRl[jentry][89]=IADR89;
       IADRl[jentry][90]=IADR90;
       IADRl[jentry][91]=IADR91;
       IADRl[jentry][92]=IADR92;
       IADRl[jentry][93]=IADR93;
       IADRl[jentry][94]=IADR94;
       IADRl[jentry][95]=IADR95;
       IADRl[jentry][96]=IADR96;
       IADRl[jentry][97]=IADR97;
       IADRl[jentry][98]=IADR98;
       IADRl[jentry][99]=IADR99;
       IADRl[jentry][100]=IADR100;
       IADRl[jentry][101]=IADR101;
       IADRl[jentry][102]=IADR102;
       IADRl[jentry][103]=IADR103;
       IADRl[jentry][104]=IADR104;
       IADRl[jentry][105]=IADR105;
       IADRl[jentry][106]=IADR106;
       IADRl[jentry][107]=IADR107;
       IADRl[jentry][108]=IADR108;
       IADRl[jentry][109]=IADR109;
       IADRl[jentry][110]=IADR110;
       IADRl[jentry][111]=IADR111;
       IADRl[jentry][112]=IADR112;
       IADRl[jentry][113]=IADR113;
       IADRl[jentry][114]=IADR114;
       IADRl[jentry][115]=IADR115;
       IADRl[jentry][116]=IADR116;
       IADRl[jentry][117]=IADR117;
       IADRl[jentry][118]=IADR118;
       IADRl[jentry][119]=IADR119;
       IADRl[jentry][120]=IADR120;
       IADRl[jentry][121]=IADR121;
       IADRl[jentry][122]=IADR122;
       IADRl[jentry][123]=IADR123;
       IADRl[jentry][124]=IADR124;
       IADRl[jentry][125]=IADR125;
       IADRl[jentry][126]=IADR126;
       IADRl[jentry][127]=IADR127;
       IADRl[jentry][128]=IADR128;
       IADRl[jentry][129]=IADR129;
       IADRl[jentry][130]=IADR130;
       IADRl[jentry][131]=IADR131;
       IADRl[jentry][132]=IADR132;
       IADRl[jentry][133]=IADR133;
       IADRl[jentry][134]=IADR134;
       IADRl[jentry][135]=IADR135;
       IADRl[jentry][136]=IADR136;
       IADRl[jentry][137]=IADR137;
       IADRl[jentry][138]=IADR138;
       IADRl[jentry][139]=IADR139;
       IADRl[jentry][140]=IADR140;
       IADRl[jentry][141]=IADR141;
       IADRl[jentry][142]=IADR142;
       IADRl[jentry][143]=IADR143;
       IADRl[jentry][144]=IADR144;
       IADRl[jentry][145]=IADR145;
       IADRl[jentry][146]=IADR146;
       IADRl[jentry][147]=IADR147;
       IADRl[jentry][148]=IADR148;
       IADRl[jentry][149]=IADR149;
       IADRl[jentry][150]=IADR150;
       IADRl[jentry][151]=IADR151;
       IADRl[jentry][152]=IADR152;
       IADRl[jentry][153]=IADR153;
       IADRl[jentry][154]=IADR154;
       IADRl[jentry][155]=IADR155;
       IADRl[jentry][156]=IADR156;
       IADRl[jentry][157]=IADR157;
       IADRl[jentry][158]=IADR158;
       IADRl[jentry][159]=IADR159;
       IADRl[jentry][160]=IADR160;
       IADRl[jentry][161]=IADR161;
       IADRl[jentry][162]=IADR162;
       IADRl[jentry][163]=IADR163;
       IADRl[jentry][164]=IADR164;
       IADRl[jentry][165]=IADR165;
       IADRl[jentry][166]=IADR166;
       IADRl[jentry][167]=IADR167;
       IADRl[jentry][168]=IADR168;
       IADRl[jentry][169]=IADR169;
       IADRl[jentry][170]=IADR170;
       IADRl[jentry][171]=IADR171;
       IADRl[jentry][172]=IADR172;
       IADRl[jentry][173]=IADR173;
       IADRl[jentry][174]=IADR174;
       IADRl[jentry][175]=IADR175;
       IADRl[jentry][176]=IADR176;
       IADRl[jentry][177]=IADR177;
       IADRl[jentry][178]=IADR178;
       IADRl[jentry][179]=IADR179;
       IADRl[jentry][180]=IADR180;
       IADRl[jentry][181]=IADR181;
       IADRl[jentry][182]=IADR182;
       IADRl[jentry][183]=IADR183;
       IADRl[jentry][184]=IADR184;
       IADRl[jentry][185]=IADR185;
       IADRl[jentry][186]=IADR186;
       IADRl[jentry][187]=IADR187;
       IADRl[jentry][188]=IADR188;
       IADRl[jentry][189]=IADR189;
       IADRl[jentry][190]=IADR190;
       IADRl[jentry][191]=IADR191;
       IADRl[jentry][192]=IADR192;
       IADRl[jentry][193]=IADR193;
       IADRl[jentry][194]=IADR194;
       IADRl[jentry][195]=IADR195;
       IADRl[jentry][196]=IADR196;
       IADRl[jentry][197]=IADR197;
       IADRl[jentry][198]=IADR198;
       IADRl[jentry][199]=IADR199;
       
       //energy loss setting
       energylossl[jentry][0]=E0;
       energylossl[jentry][1]=E1;
       energylossl[jentry][2]=E2;
       energylossl[jentry][3]=E3;
       energylossl[jentry][4]=E4;
       energylossl[jentry][5]=E5;
       energylossl[jentry][6]=E6;
       energylossl[jentry][7]=E7;
       energylossl[jentry][8]=E8;
       energylossl[jentry][9]=E9;
       energylossl[jentry][10]=E10;
       energylossl[jentry][11]=E11;
       energylossl[jentry][12]=E12;
       energylossl[jentry][13]=E13;
       energylossl[jentry][14]=E14;
       energylossl[jentry][15]=E15;
       energylossl[jentry][16]=E16;
       energylossl[jentry][17]=E17;
       energylossl[jentry][18]=E18;
       energylossl[jentry][19]=E19;
       energylossl[jentry][20]=E20;
       energylossl[jentry][21]=E21;
       energylossl[jentry][22]=E22;
       energylossl[jentry][23]=E23;
       energylossl[jentry][24]=E24;
       energylossl[jentry][25]=E25;
       energylossl[jentry][26]=E26;
       energylossl[jentry][27]=E27;
       energylossl[jentry][28]=E28;
       energylossl[jentry][29]=E29;
       energylossl[jentry][30]=E30;
       energylossl[jentry][31]=E31;
       energylossl[jentry][32]=E32;
       energylossl[jentry][33]=E33;
       energylossl[jentry][34]=E34;
       energylossl[jentry][35]=E35;
       energylossl[jentry][36]=E36;
       energylossl[jentry][37]=E37;
       energylossl[jentry][38]=E38;
       energylossl[jentry][39]=E39;
       energylossl[jentry][40]=E40;
       energylossl[jentry][41]=E41;
       energylossl[jentry][42]=E42;
       energylossl[jentry][43]=E43;
       energylossl[jentry][44]=E44;
       energylossl[jentry][45]=E45;
       energylossl[jentry][46]=E46;
       energylossl[jentry][47]=E47;
       energylossl[jentry][48]=E48;
       energylossl[jentry][49]=E49;
       energylossl[jentry][50]=E50;
       energylossl[jentry][51]=E51;
       energylossl[jentry][52]=E52;
       energylossl[jentry][53]=E53;
       energylossl[jentry][54]=E54;
       energylossl[jentry][55]=E55;
       energylossl[jentry][56]=E56;
       energylossl[jentry][57]=E57;
       energylossl[jentry][58]=E58;
       energylossl[jentry][59]=E59;
       energylossl[jentry][60]=E60;
       energylossl[jentry][61]=E61;
       energylossl[jentry][62]=E62;
       energylossl[jentry][63]=E63;
       energylossl[jentry][64]=E64;
       energylossl[jentry][65]=E65;
       energylossl[jentry][66]=E66;
       energylossl[jentry][67]=E67;
       energylossl[jentry][68]=E68;
       energylossl[jentry][69]=E69;
       energylossl[jentry][70]=E70;
       energylossl[jentry][71]=E71;
       energylossl[jentry][72]=E72;
       energylossl[jentry][73]=E73;
       energylossl[jentry][74]=E74;
       energylossl[jentry][75]=E75;
       energylossl[jentry][76]=E76;
       energylossl[jentry][77]=E77;
       energylossl[jentry][78]=E78;
       energylossl[jentry][79]=E79;
       energylossl[jentry][80]=E80;
       energylossl[jentry][81]=E81;
       energylossl[jentry][82]=E82;
       energylossl[jentry][83]=E83;
       energylossl[jentry][84]=E84;
       energylossl[jentry][85]=E85;
       energylossl[jentry][86]=E86;
       energylossl[jentry][87]=E87;
       energylossl[jentry][88]=E88;
       energylossl[jentry][89]=E89;
       energylossl[jentry][90]=E90;
       energylossl[jentry][91]=E91;
       energylossl[jentry][92]=E92;
       energylossl[jentry][93]=E93;
       energylossl[jentry][94]=E94;
       energylossl[jentry][95]=E95;
       energylossl[jentry][96]=E96;
       energylossl[jentry][97]=E97;
       energylossl[jentry][98]=E98;
       energylossl[jentry][99]=E99;
       energylossl[jentry][100]=E100;
       energylossl[jentry][101]=E101;
       energylossl[jentry][102]=E102;
       energylossl[jentry][103]=E103;
       energylossl[jentry][104]=E104;
       energylossl[jentry][105]=E105;
       energylossl[jentry][106]=E106;
       energylossl[jentry][107]=E107;
       energylossl[jentry][108]=E108;
       energylossl[jentry][109]=E109;
       energylossl[jentry][110]=E110;
       energylossl[jentry][111]=E111;
       energylossl[jentry][112]=E112;
       energylossl[jentry][113]=E113;
       energylossl[jentry][114]=E114;
       energylossl[jentry][115]=E115;
       energylossl[jentry][116]=E116;
       energylossl[jentry][117]=E117;
       energylossl[jentry][118]=E118;
       energylossl[jentry][119]=E119;
       energylossl[jentry][120]=E120;
       energylossl[jentry][121]=E121;
       energylossl[jentry][122]=E122;
       energylossl[jentry][123]=E123;
       energylossl[jentry][124]=E124;
       energylossl[jentry][125]=E125;
       energylossl[jentry][126]=E126;
       energylossl[jentry][127]=E127;
       energylossl[jentry][128]=E128;
       energylossl[jentry][129]=E129;
       energylossl[jentry][130]=E130;
       energylossl[jentry][131]=E131;
       energylossl[jentry][132]=E132;
       energylossl[jentry][133]=E133;
       energylossl[jentry][134]=E134;
       energylossl[jentry][135]=E135;
       energylossl[jentry][136]=E136;
       energylossl[jentry][137]=E137;
       energylossl[jentry][138]=E138;
       energylossl[jentry][139]=E139;
       energylossl[jentry][140]=E140;
       energylossl[jentry][141]=E141;
       energylossl[jentry][142]=E142;
       energylossl[jentry][143]=E143;
       energylossl[jentry][144]=E144;
       energylossl[jentry][145]=E145;
       energylossl[jentry][146]=E146;
       energylossl[jentry][147]=E147;
       energylossl[jentry][148]=E148;
       energylossl[jentry][149]=E149;
       energylossl[jentry][150]=E150;
       energylossl[jentry][151]=E151;
       energylossl[jentry][152]=E152;
       energylossl[jentry][153]=E153;
       energylossl[jentry][154]=E154;
       energylossl[jentry][155]=E155;
       energylossl[jentry][156]=E156;
       energylossl[jentry][157]=E157;
       energylossl[jentry][158]=E158;
       energylossl[jentry][159]=E159;
       energylossl[jentry][160]=E160;
       energylossl[jentry][161]=E161;
       energylossl[jentry][162]=E162;
       energylossl[jentry][163]=E163;
       energylossl[jentry][164]=E164;
       energylossl[jentry][165]=E165;
       energylossl[jentry][166]=E166;
       energylossl[jentry][167]=E167;
       energylossl[jentry][168]=E168;
       energylossl[jentry][169]=E169;
       energylossl[jentry][170]=E170;
       energylossl[jentry][171]=E171;
       energylossl[jentry][172]=E172;
       energylossl[jentry][173]=E173;
       energylossl[jentry][174]=E174;
       energylossl[jentry][175]=E175;
       energylossl[jentry][176]=E176;
       energylossl[jentry][177]=E177;
       energylossl[jentry][178]=E178;
       energylossl[jentry][179]=E179;
       energylossl[jentry][180]=E180;
       energylossl[jentry][181]=E181;
       energylossl[jentry][182]=E182;
       energylossl[jentry][183]=E183;
       energylossl[jentry][184]=E184;
       energylossl[jentry][185]=E185;
       energylossl[jentry][186]=E186;
       energylossl[jentry][187]=E187;
       energylossl[jentry][188]=E188;
       energylossl[jentry][189]=E189;
       energylossl[jentry][190]=E190;
       energylossl[jentry][191]=E191;
       energylossl[jentry][192]=E192;
       energylossl[jentry][193]=E193;
       energylossl[jentry][194]=E194;
       energylossl[jentry][195]=E195;
       energylossl[jentry][196]=E196;
       energylossl[jentry][197]=E197;
       energylossl[jentry][198]=E198;
       energylossl[jentry][199]=E199;
       
       
       for(int mm=0;mm<200;mm++){
	 ID[jentry][mm]    = IADRl[jentry][mm]/1000000;
	 pos_X[jentry][mm] = (IADRl[jentry][mm] - ID[jentry][mm]*1000000)/1000; 
	 pos_Y[jentry][mm] = (IADRl[jentry][mm] - ID[jentry][mm]*1000000 -pos_X[jentry][mm]*1000);
       }
      
       
       if(debug2){       
	 std::cout << "============= "  << jentry << "th event start" <<std::endl;        
	 for(int mm=0;mm<200;mm++){
	   std::cout << "IADRl["<< jentry << "][" << mm  << "]= "  << IADRl[jentry][mm] << std::endl;
	 }//for(int mm
       }  //if(debug2
       
       if(debug3){       
	 std::cout << "============= "  << jentry << "th event start" <<std::endl;        
	 for(int mm=0;mm<200;mm++){
	   std::cout << "energylossl["<< jentry << "][" << mm  << "]= "  << energylossl[jentry][mm] << std::endl;
	 }//for(int mm
       }  //if(debug3
      
   }  //for (Long64

  
   //************************************************ first position &  last position setting******************************************
   std::cout << "***************************************** first position analysis & last positon setting ****************************************" << std::endl;

      int lastIADR[nentries];
      int position_x[nentries],position_y[nentries],detector_id[nentries];


   TH2D *h1 = new TH2D("first position","first position",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);  //graph area ajust
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;

     for(int mm=0;mm<200;mm++){
       if(IADRl[jentry][mm]==0){
	 break;
       }
       lastIADR[jentry] = IADRl[jentry][mm];
     }//  mm

     //last position setting
          detector_id[jentry] = lastIADR[jentry]/1000000;
          position_x[jentry] = (lastIADR[jentry] - detector_id[jentry]*1000000)/1000; 
          position_y[jentry] = (lastIADR[jentry] - detector_id[jentry]*1000000 -position_x[jentry]*1000);

     //first position histgram making
     if(debug4){
       std::cout << "j=" << jentry << " : (x,y) = ( " << BeamPosX0 <<", "<< BeamPosY0 << ")" << std::endl;
     }
     h1->Fill(BeamPosX0*1000+500,BeamPosY0*1000+500);
   }  // jentry
   h1->SetXTitle("X [um]");
   h1->SetXTitle("Y [um]");
   h1->SetStats(1);

   
   //***********************************************DUT mode***************************************************
   if(DUTmode){
     std::cout << "********************************************DUT mode**************************************************" << std::endl;     

     //==========================last position===========================
     std::cout << "=================last position analysis================" << std::endl;
     TH2D *h0 = new TH2D("last position","last position",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *hx = new TH1D("X scattering","X scattering",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *hy = new TH1D("Y scattering","Y scattering",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
     
     if(debug6){
       std::cout << "j=" << jentry << " : (IADR,x,y,ID) = ( " << lastIADR[jentry] << ", "<< position_x[jentry] <<", "<< position_y[jentry] << ", " << detector_id[jentry] << ")" << std::endl;
     }
     if(detector_id[jentry]==3 && hitl[jentry]<evecut){
       h0->Fill(position_x[jentry],position_y[jentry]);
       hx->Fill(position_x[jentry]);
       hy->Fill(position_y[jentry]);
     }
     }  // jentry

   TCanvas *c0 = new TCanvas("c0","c0",750,1500);
   c0->Divide(1,2);
   h0->SetXTitle("X [um]");
   h0->SetXTitle("Y [um]");
   h0->SetStats(1);
   //first position draw
   c0->cd(1);
   h1->Draw("colz");
   //lastposition draw
   c0->cd(2);
   h0->Draw("colz");


   TCanvas *cxy = new TCanvas("cxy","cxy",750,1500);
   cxy->Divide(1,2);
   hx->SetXTitle("X [um]");
   hy->SetXTitle("Y [um]");
   gStyle->SetOptFit(1111);
   cxy->cd(1);
   hx->Fit("gaus");
   hx->Draw();
   cxy->cd(2);
   hy->Fit("gaus");
   hy->Draw();
         
   //==========================energy loss===========================
   std::cout << "=================energy loss analysis================" << std::endl; 
   
   TH1D *h2 = new TH1D("Energy Loss","Energy Loss",1000,0,1000);
   double totalloss[nentries];
     
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = fChain->GetEntry(jentry);   nbytes += nb;
     // if (Cut(ientry) < 0) continue;
     totalloss[jentry]=0;
     for(int mm=0;mm<200;mm++){
       totalloss[jentry] += energylossl[jentry][mm]; 
     }//  mm
     if(debug5){
       std::cout << "j=" << jentry << " : total loss = " << totalloss[jentry]<< std::endl;
     }
     if(detector_id[jentry]==3 && hitl[jentry]<evecut){
       h2->Fill(totalloss[jentry]);
     }
   }  // jentry

   TCanvas *c1 = new TCanvas("Energy Loss","Energy Loss");
   TF1 *f0 = new TF1("f0","gaus");
   h2->Fit(f0);
   h2->SetXTitle("Energy Loss [keV]");
   h2->Draw("Same");   

   }  //  if(DUTmode



   //****************************************************** Tracker mode********************************************************
   if(Trackermode){
     
     std::cout << "**********************************************Tracker mode********************************************" << std::endl;
     
     int Tracker[3][nentries];
     Long64_t Trackerx[3][nentries];   
     Long64_t Trackery[3][nentries];
     int Trackerid[3][nentries];
     /*
     TH2D *h_tr0 = new TH2D("Tracker0 Scattering","Tracker0 Scattering",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH2D *h_tr1 = new TH2D("Tracker1 Scattering","Tracker1 Scattering",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH2D *h_tr2 = new TH2D("Tracker2 Scattering","Tracker2 Scattering",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);     

     TH1D *h_tr0_x = new TH1D("Tracker0 X scattering","Tracker0 X scattering",posi_bin, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *h_tr0_y = new TH1D("Tracker0 Y scattering","Tracker0 Y scattering",posi_bin, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *h_tr1_x = new TH1D("Tracker1 X scattering","Tracker1 X scattering",posi_bin, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *h_tr1_y = new TH1D("Tracker1 Y scattering","Tracker1 Y scattering",posi_bin, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *h_tr2_x = new TH1D("Tracker2 X scattering","Tracker2 X scattering",posi_bin, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *h_tr2_y = new TH1D("Tracker2 Y scattering","Tracker2 Y scattering",posi_bin, 500-posi_bin/2, 500+posi_bin/2);     
     */     
     for (Long64_t jentry=0; jentry<nentries;jentry++) {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;

       for(int nn=0;nn<3;nn++){
	 for(int mm=0;mm<200;mm++){
	   if(IADRl[jentry][mm]/1000000==nn+1){
	     break;
	   }
	   Tracker[nn][jentry] = IADRl[jentry][mm];
	 }   //  for(int mm
	 
	 Trackerid[nn][jentry] = Tracker[nn][jentry]/1000000;
	 Trackerx[nn][jentry] = (Tracker[nn][jentry] - Trackerid[nn][jentry]*1000000)/1000; 
	 Trackery[nn][jentry] = (Tracker[nn][jentry] - Trackerid[nn][jentry]*1000000 -Trackerx[nn][jentry]*1000);
	 if(debug6){
	   std::cout << "(j=" << jentry << ", nn = " << nn <<  " ) : (Tracker,x,y,ID) = ( " << Tracker[nn][jentry] << ", "<< Trackerx[nn][jentry] <<", "<< Trackery[nn][jentry] << ", " << Trackerid[nn][jentry] << ")" << std::endl;
	 }
	 /*
	 if(hitl[jentry]<evecut){
	   if(nn==0){
	     h_tr0->Fill(Trackerx[nn][jentry],Trackery[nn][jentry]);
	     h_tr0_x->Fill(Trackerx[nn][jentry]);
	     h_tr0_y->Fill(Trackery[nn][jentry]);
	   }else if(nn==1){
	     h_tr1->Fill(Trackerx[nn][jentry],Trackery[nn][jentry]);
	     h_tr1_x->Fill(Trackerx[nn][jentry]);
	     h_tr1_y->Fill(Trackery[nn][jentry]);
	   }else{
	     h_tr2->Fill(Trackerx[nn][jentry],Trackery[nn][jentry]);
	     h_tr2_x->Fill(Trackerx[nn][jentry]);
	     h_tr2_y->Fill(Trackery[nn][jentry]);
	   }
	 }
	 */
       }  //  for(int nn++
     }  // jentry
     /*
     TCanvas *c_tr = new TCanvas("c_tr1","c_tr1",1500,1500);
     c_tr->Divide(2,2);
      
     h_tr0->SetXTitle("X [um]");
     h_tr0->SetXTitle("Y [um]");
     h_tr1->SetXTitle("X [um]");
     h_tr1->SetXTitle("Y [um]");
     h_tr2->SetXTitle("X [um]");
     h_tr2->SetXTitle("Y [um]");
     h_tr0->SetStats(1);
     h_tr1->SetStats(1);
     h_tr2->SetStats(1);
     
     //first position draw
     c_tr->cd(1);
     h1->Draw("colz");
     //Tracker0 draw   
     c_tr->cd(2);
     h_tr0->Draw("colz");
     //Tracker1 draw   
     c_tr->cd(3);
     h_tr1->Draw("colz");
     //Tracker2 draw   
     c_tr->cd(4);
     h_tr2->Draw("colz");
          
     TCanvas *c_tr_xy = new TCanvas("c_tr_xy","c_tr_xy",1500,750);
     c_tr_xy->Divide(3,2);
     h_tr0_x->SetXTitle("X [um]");
     h_tr0_y->SetXTitle("Y [um]");
     h_tr1_x->SetXTitle("X [um]");
     h_tr1_y->SetXTitle("Y [um]");
     h_tr2_x->SetXTitle("X [um]");
     h_tr2_y->SetXTitle("Y [um]");
     gStyle->SetOptFit(1111);
     //Tracker0 x  draw   
     c_tr_xy->cd(1);
     h_tr0_x->Fit("gaus");
     h_tr0_x->Draw();
     //Tracker0 y draw   
     c_tr_xy->cd(4);
     h_tr0_y->Fit("gaus");
     h_tr0_y->Draw();
     //Tracker1 x  draw   
     c_tr_xy->cd(2);
     h_tr1_x->Fit("gaus");
     h_tr1_x->Draw();
     //Tracker1 y draw   
     c_tr_xy->cd(5);
     h_tr1_y->Fit("gaus");
     h_tr1_y->Draw();
     //Tracker2 x  draw   
     c_tr_xy->cd(3);
     h_tr2_x->Fit("gaus");
     h_tr2_x->Draw();
     //Tracker2 y draw   
     c_tr_xy->cd(6);
     h_tr2_y->Fit("gaus");
     h_tr2_y->Draw();
     */
       
     //==========================energy loss===========================
     /*
     std::cout << "=================energy loss analysis================" << std::endl; 
     
     TH1D *h_E_tr0 = new TH1D("Tracker0 Energy Loss","Tracker0 Energy Loss",ene_bin,0,ene_bin);
     TH1D *h_E_tr1 = new TH1D("Tracker1 Energy Loss","Tracker1 Energy Loss",ene_bin,0,ene_bin);
     TH1D *h_E_tr2 = new TH1D("Tracker2 Energy Loss","Tracker2 Energy Loss",ene_bin,0,ene_bin);
          
     double totalloss[3][nentries];
     
     for (Long64_t jentry=0; jentry<nentries;jentry++) {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;

       for(int nn=0;nn<3;nn++){
	 totalloss[nn][jentry]=0;
	 for(int mm=0;mm<200;mm++){
	   if(IADRl[jentry][mm]/1000000==nn){
	     totalloss[nn][jentry] += energylossl[jentry][mm]; 
	   }
	   }//  mm
	 
	 if(debug5){
	   std::cout << "(j=" << jentry <<", nn = " << nn << " ) : total loss = " << totalloss[nn][jentry]<< std::endl;
	 }
	 if(detector_id[jentry]==3 && hitl[jentry]<evecut){
	   if(nn==0){
	     h_E_tr0->Fill(totalloss[nn][jentry]);
	   }else if(nn==1){
	     h_E_tr1->Fill(totalloss[nn][jentry]);
	   }else{
	     h_E_tr2->Fill(totalloss[nn][jentry]);
	   }
	 }
       }  //  nn
     }  // jentry
     
     TCanvas *c1 = new TCanvas("Energy Loss","Energy Loss",1500,750);
     c1->Divide(3,1);
     h_E_tr0->SetXTitle("Energy Loss [keV]");
     h_E_tr1->SetXTitle("Energy Loss [keV]");
     h_E_tr2->SetXTitle("Energy Loss [keV]");
     //Tracker0 Energyloss draw 
     c1->cd(1);
     h_E_tr0->Fit("gaus");
     h_E_tr0->Draw();
     //Tracker0 Energyloss draw 
     c1->cd(2);
     h_E_tr1->Fit("gaus");
     h_E_tr1->Draw();   
     //Tracker0 Energyloss draw 
     c1->cd(3);
     h_E_tr2->Fit("gaus");
     h_E_tr2->Draw();
     */
     //==========================beam reconstruction===========================
     std::cout << "==================beam reconstruction================" << std::endl; 

     posi_bin = 100;
     double S = 0.5;
     
     double grad_tr1x[nentries];
     double grad_tr1y[nentries];
     double grad_tr2x[nentries];
     double grad_tr2y[nentries];
     Long64_t DUT_re_position_x[nentries];
     Long64_t DUT_re_position_y[nentries];
     Long64_t difference_x[nentries];
     Long64_t difference_y[nentries];
     double diff = 0.0005;

     
     TH2D *h_DUT = new TH2D("h_DUT","DUT Position",posi_bin*1, 500-posi_bin/2, 500+posi_bin/2, posi_bin*1, 500-posi_bin/2, 500+posi_bin/2);
     TH2D *h_re_DUT = new TH2D("h_re_DUT","Reconstructed DUT Position",posi_bin*1, 500-posi_bin/2, 500+posi_bin/2, posi_bin*1, 500-posi_bin/2, 500+posi_bin/2);
     //     TH2D *h_re_DUT = new TH2D("h_re_DUT","Reconstructed DUT Position",posi_bin*1, 0-posi_bin/2, 0+posi_bin/2, posi_bin*1, 0-posi_bin/2, 0+posi_bin/2);
     TH2D *h_grad2D = new TH2D("h_grad2D","grad2D",posi_bin*1, 0-posi_bin/2, 0+posi_bin/2, posi_bin*1, 0-posi_bin/2, 0+posi_bin/2);
     TH1D *h_differenceX = new TH1D("difference","Differnce between Original X and Reconsted X",diff_bin, 0-diff_bin/2, 0+diff_bin/2);
     TH1D *h_differenceY = new TH1D("difference","Differnce between Original Y and Reconstructed Y",diff_bin, 0-diff_bin/2, 0+diff_bin/2);
     TH1D *h_dxdz1 = new TH1D("dxdz1","dxdz1",10, 0-diff/2, 0+diff/2);
     TH1D *h_dydz1 = new TH1D("dydz1","dydz1",10, 0-diff/2, 0+diff/2);
     TH1D *h_dxdz = new TH1D("dxdz","dxdz",10, 0-diff/2, 0+diff/2);
     TH1D *h_dydz = new TH1D("dydz","dydz",10, 0-diff/2, 0+diff/2);
     

     for (Long64_t jentry=0; jentry<nentries;jentry++) {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;
       
       //       grad_tr2x[jentry] = (Trackerx[2][jentry] - Trackerx[0][jentry]) / (2 * tr_pitch);
       //       grad_tr2y[jentry] = (Trackery[2][jentry] - Trackery[0][jentry]) / (2 * tr_pitch);

       
       grad_tr1x[jentry] =  (Trackerx[1][jentry]-Trackerx[0][jentry])/(1 * tr_pitch);
       grad_tr1y[jentry] =  (Trackery[1][jentry]-Trackery[0][jentry])/(1 * tr_pitch);
       grad_tr2x[jentry] =  (Trackerx[2][jentry]-Trackerx[0][jentry])/(2 * tr_pitch);
       grad_tr2y[jentry] =  (Trackery[2][jentry]-Trackery[0][jentry])/(2 * tr_pitch);

       
       //       DUT_re_position_x[jentry] = (Trackerx[2][jentry]) + (grad_tr2x[jentry]);
       //       DUT_re_position_y[jentry] = (Trackery[2][jentry]) + (grad_tr2y[jentry]);
       
       DUT_re_position_x[jentry] = Trackerx[2][jentry]  + 30.0*1000 * grad_tr2x[jentry];
       DUT_re_position_y[jentry] = Trackery[2][jentry]  + 30.0*1000 * grad_tr2y[jentry];
       
       difference_x[jentry] = position_x[jentry] - DUT_re_position_x[jentry];
       difference_y[jentry] = position_y[jentry] - DUT_re_position_y[jentry];

       //       if(std::abs(DUT_re_position_x[jentry]-500)<S || std::abs(DUT_re_position_y[jentry]-500)<S ){
	 if(std::abs(Trackerx[2][jentry]+grad_tr1x[jentry]-500)<S || std::abs(Trackery[2][jentry]+grad_tr1y[jentry]-500)<S ){
	 std::cout << "============================================================================= what's happen? ================" << std::endl;      
       //       std::cout << "(j = " << jentry << " ) : Tracker_0(x, y)        = " << Trackerx[0][jentry] << ", " << Trackery[0][jentry] << ")" << std::endl;
              std::cout << "(j = " << jentry << " ) : Tracker_2(x, y)        = " << "( "  << Trackerx[2][jentry] << ", " << Trackery[2][jentry] << ")" << std::endl;
              std::cout << "(j = " << jentry << " ) : grad_tr1 (x, y)        = " << "( "  << grad_tr1x[jentry] << ", " << grad_tr1x[jentry] << ")" << std::endl;
              std::cout << "(j = " << jentry << " ) : grad_tr2 (x, y)        = " << "( "  << grad_tr2x[jentry] << ", " << grad_tr2y[jentry] << ")" << std::endl;
	      std::cout << "(j = " << jentry << " ) : DUT_re_position1 (x, y)= " << "( "  << Trackerx[2][jentry]+grad_tr1x[jentry] << ", " << Trackery[2][jentry]+grad_tr1y[jentry] << ")" << std::endl;
	      std::cout << "(j = " << jentry << " ) : DUT_re_position2 (x, y)= " << "( "  << DUT_re_position_x[jentry] << ", " << DUT_re_position_y[jentry] << ")" << std::endl;
	      std::cout << "(j = " << jentry << " ) : grad tr2-tr1 (x, y)    = " << "( "  << grad_tr2x[jentry]-grad_tr1x[jentry] << ", " << grad_tr2y[jentry]+grad_tr1y[jentry] << ")" << std::endl;
	 }
     
       if(debug7){
	 std::cout << "(j = " << jentry << " ) : grad_tr2 (x, y) = " << "=( "  << grad_tr2y[jentry] << ", " << grad_tr2y[jentry] << ")" << std::endl;
	 std::cout << "(j = " << jentry << " ) : DUT_re_position (x, y) = " << "=( "  << DUT_re_position_x[jentry] << ", " << DUT_re_position_y[jentry] << ")" << std::endl;
	 std::cout << "(j = " << jentry << " ) : DUT_position (x, y) = " << "=( "  << position_x[jentry] << ", " << position_y[jentry] << ")" << std::endl;
	 std::cout << "(j = " << jentry << " ) : difference (x, y) = " << "=( "  << difference_x[jentry] << ", " << difference_y[jentry] << ")" << std::endl;
       }
	 if(detector_id[jentry]==3 && hitl[jentry]<evecut){
	   //	   if(std::abs(DUT_re_position_x[jentry]-500)<S || std::abs(DUT_re_position_y[jentry]-500)<S ){
	   //	   if(std::abs(Trackerx[2][jentry]+grad_tr1x[jentry]-500)<S || std::abs(Trackery[2][jentry]+grad_tr1y[jentry]-500)<S ){
	     //	   h_DUT->Fill(position_x[jentry],position_y[jentry]);
	     //	     h_DUT->Fill(position_x[jentry],position_y[jentry]);
	     h_DUT->Fill(Trackerx[2][jentry]+grad_tr1x[jentry],Trackery[2][jentry]+grad_tr1y[jentry] );
	     h_re_DUT->Fill(DUT_re_position_x[jentry], DUT_re_position_y[jentry]);
	     h_differenceX->Fill(difference_x[jentry]);
	     h_differenceY->Fill(difference_y[jentry]);
	     //  	   h_grad2D->Fill(grad_tr2x[jentry],grad_tr2y[jentry]);
	     h_dxdz->Fill(grad_tr2x[jentry]);
	     h_dydz->Fill(grad_tr2y[jentry]);
	     h_dxdz1->Fill(grad_tr1x[jentry]);
	     h_dydz1->Fill(grad_tr1y[jentry]);
	     
	     //		   }
	 }
     }  // jentry
     
       h_DUT->SetXTitle("X [um]");
       h_DUT->SetXTitle("Y [um]");
       h_DUT->SetStats(1);

     if(debug7){  
       TCanvas *c_DUT = new TCanvas("DUT","DUT",750,1500);
       c_DUT->Divide(1,2);
       //first position draw
       c_DUT->cd(1);
       h1->Draw("colz");
       //lastposition draw
       c_DUT->cd(2);
       h_DUT->Draw("colz");
     }
     
     TCanvas *c_re_DUT = new TCanvas("c_re_DUT","Reconsted DUT Position",750,1500);
     c_re_DUT->Divide(1,2);
     h_re_DUT->SetXTitle("X [um]");
     h_re_DUT->SetXTitle("Y [um]");
     h_re_DUT->SetStats(1);
     //DUT position draw
     c_re_DUT->cd(1);
     //     h_tr2->Draw("colz");
          h_DUT->Draw("colz");
     //Reconstructed position draw
     c_re_DUT->cd(2);
     h_re_DUT->Draw("colz");

     TCanvas *c_difference = new TCanvas("c_difference","Differnce between Origin and Reconstruction",800,1600);
     c_difference->Divide(1,2);
     h_differenceX->SetXTitle("Differnce X[#mum]");
     h_differenceY->SetXTitle("Differnce Y[#mum]");
     gStyle->SetOptFit(1111);
     //difference x  draw
     c_difference->cd(1);
     h_differenceX->Fit("gaus");
     h_differenceX->Draw();
     //difference y  draw
     c_difference->cd(2);
     h_differenceY->Fit("gaus");
     h_differenceY->Draw();
     
     TCanvas *c_dxdz = new TCanvas("c_dxdz","dxdz",1600,800);
     c_dxdz->Divide(2,2);
     c_dxdz->cd(1);
     h_dxdz->Draw();
     c_dxdz->cd(2);
     h_dydz->Draw();
     c_dxdz->cd(3);
     h_dxdz1->Draw();
     c_dxdz->cd(4);
     h_dydz1->Draw();

     
     /*     
     TCanvas *c_grad2D = new TCanvas("c_grad2D","grad2D",800,1600);
     h_grad2D->SetYTitle("X[#mum]");
     h_grad2D->SetXTitle("Y[#mum]");
     h_grad2D->Draw("calz");
     */
     
   }  //  if(Trackermode

   
   //****************************************************** Mean Cal mode********************************************************
   if(MeanCalmode){
     std::cout << "**********************************************Mean Cal  mode********************************************" << std::endl;
     
     //========================== hit number in each Pixcel check  ===========================
     std::cout << "==================hit number in each Pixcel check================" << std::endl; 
     int PixcelhitNumber[4][nentries];
     double maxEnergyLoss[nentries][4];
     int maxhitID[nentries][4];
     int NN = 10;
     int mean_pos_X[nentries][4];
     int mean_pos_Y[nentries][4];
     int counter[nentries][4];
     int hit_count[nentries][4];
     
     double grad_X[nentries];
     double grad_Y[nentries];
     double DUT_re_position_X[nentries];
     double DUT_re_position_Y[nentries];
     double difference_X[nentries];
     double difference_Y[nentries];

          
     //     TTree *tree = new TTree("event tree","RECREATE");
     TH1D *h_Nneighbor = new TH1D("Non neighbor hit","Non neighbor hit",100,-100,100);
     TH2D *mean2Dhist0 = new TH2D("Tracker0","Tracker0",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH2D *mean2Dhist1 = new TH2D("Tracker1","Tracker1",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH2D *mean2Dhist2 = new TH2D("Tracker2","Tracker2",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH2D *mean2DhistDUT = new TH2D("DUT","DUT",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *mean_h_X = new TH1D("mean_h_X","mean_h_X",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *mean_h_Y = new TH1D("mean_h_y","mean_h_Y",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);

     TH2D *h_DUT = new TH2D("h_DUT","DUT Position",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH2D *h_re_DUT = new TH2D("h_re_DUT","Reconstructed DUT Position",posi_bin/1, 500-posi_bin/2, 500+posi_bin/2, posi_bin/1, 500-posi_bin/2, 500+posi_bin/2);
     TH1D *h_differenceX = new TH1D("difference","Differnce between Original X and Reconsted X",diff_bin, 0-diff_bin/2, 0+diff_bin/2);
     TH1D *h_differenceY = new TH1D("difference","Differnce between Original Y and Reconstructed Y",diff_bin, 0-diff_bin/2, 0+diff_bin/2);
     
     TH1D *h_hit0 = new TH1D("Tracker0 Hit Count","Tracker0 Hit Count",30,0,30);
     TH1D *h_hit1 = new TH1D("Tracker1 Hit Count","Tracker1 Hit Count",30,0,30);
     TH1D *h_hit2 = new TH1D("Tracker2 Hit Count","Tracker2 Hit Count",30,0,30);
     TH1D *h_hitDUT = new TH1D("DUT Hit Count","DUT Hit Count",30,0,30);
     
     
     AnalysisClass *a;
     a= new AnalysisClass();
     a->SetUp(-1);
     a->SetTestDataX(501);
     a->SetTestDataX(502);
     a->SetTestDataX(503);
     
     AnalysisClass *b;
     b = new AnalysisClass[nentries];
     
     for (Long64_t jentry=0; jentry<nentries;jentry++) {

       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;

       b[jentry].SetUp(jentry);
       for(int nn=0;nn<4;nn++){
	 PixcelhitNumber[nn][jentry] = 0;
	 for(int mm=0;mm<200;mm++){
	   if(IADRl[jentry][mm]==0) break;
	   if(IADRl[jentry][mm]/1000000==nn){
	     //hit count
	     PixcelhitNumber[nn][jentry] += 1;
	   }
	 }//  mm
       }  //  nn
     }  // for( jentry

     
     if(debug8){
     for (Long64_t jentry=0; jentry<nentries;jentry++) {
       Long64_t ientry = LoadTree(jentry);
       if (ientry < 0) break;
       nb = fChain->GetEntry(jentry);   nbytes += nb;
       // if (Cut(ientry) < 0) continue;
       
       for(int nn=0;nn<4;nn++){
	 std::cout << "PixcelhitNumber[" << nn <<"][" << jentry << "] = " << PixcelhitNumber[nn][jentry] << std::endl;
       }
       std::cout << "hitl[" << jentry << "] = " << hitl[jentry] << std::endl;
     }
     }
          
     for (Long64_t jentry=0; jentry<nentries;jentry++) {
       if(debug8)  std::cout << "....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......" << jentry << " th entry started!"  << std::endl;
       for(int nn=0;nn<4;nn++){
	 hit_count[jentry][nn]=0;
	 if(debug8)  std::cout << "....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......" << nn << " th tracker started!"  << std::endl;
	 for(int mm=0;mm<200;mm++){
	   if(IADRl[jentry][mm]==0) break;
	   if(ID[jentry][mm]==nn){
	     if(debug8){
	       std::cout << "IADRl[" << jentry << "][" << mm << "] = " << IADRl[jentry][mm] << std::endl;
	       std::cout << "energyloss[" << jentry << "][" << mm << "] = " << energylossl[jentry][mm] << std::endl;
	     }
	     hit_count[jentry][nn] ++;
	     if(energylossl[jentry][mm]>maxEnergyLoss[jentry][nn]){
	       maxEnergyLoss[jentry][nn] = energylossl[jentry][mm];
	       maxhitID[jentry][nn] = mm;
	     }
	   }
	 }//  mm
	 if(debug8){
	   std::cout << "max energy loss["<< jentry  << "]["<< nn  << "] = " << maxEnergyLoss[jentry][nn] << std::endl;
	   std::cout << "max hit ID ["<< jentry  << "]["<< nn <<"] = " << maxhitID[jentry][nn] << std::endl;
	 }
       } // nn
       //       if(1){
       if(detector_id[jentry]==3 && hitl[jentry]<evecut){
	 h_hit0->Fill(hit_count[jentry][0]);
	 h_hit1->Fill(hit_count[jentry][1]);
	 h_hit2->Fill(hit_count[jentry][2]);
	 h_hitDUT->Fill(hit_count[jentry][3]);
       }
       for(int nn=0;nn<4;nn++){
	 
	 counter[jentry][nn]=0;
	 if(debug8)  std::cout << "....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......" << nn << " th tracker started!"  << std::endl;
	 for(int mm=0;mm<200;mm++){
	     
	   if(IADRl[jentry][mm]==0) break;

	   if( ID[jentry][mm]==nn && std::abs(pos_X[jentry][mm]-pos_X[jentry][maxhitID[jentry][nn]])>NN ){
	     if(debug8){
	       std::cout << "abs_x[" << jentry << "][" << mm << "] = " << (pos_X[jentry][mm]-pos_X[jentry][maxhitID[jentry][nn]]);
	       std::cout << ", abs_y[" << jentry << "][" << mm << "] = " << (pos_Y[jentry][mm]-pos_Y[jentry][maxhitID[jentry][nn]]) <<std::endl;
	     }
	     h_Nneighbor->Fill((pos_X[jentry][mm]-pos_X[jentry][maxhitID[jentry][nn]]));
	       }else if( ID[jentry][mm]==nn && std::abs(pos_Y[jentry][mm]-pos_Y[jentry][maxhitID[jentry][nn]])>NN ){
	     if(debug8){
	       std::cout << "abs_x[" << jentry << "][" << mm << "] = " << (pos_X[jentry][mm]-pos_X[jentry][maxhitID[jentry][nn]]);
	       std::cout << ", abs_y[" << jentry << "][" << mm << "] = " << (pos_Y[jentry][mm]-pos_Y[jentry][maxhitID[jentry][nn]]) << std::endl;
	     }
	     //	     h_Nneighbor->Fill((pos_Y[jentry][mm]-pos_Y[jentry][maxhitID[jentry][nn]]));
	   }else if(ID[jentry][mm]==nn){
	     mean_pos_X[jentry][nn] += pos_X[jentry][mm];
	     mean_pos_Y[jentry][nn] += pos_Y[jentry][mm];
	     counter[jentry][nn] += 1;
	   if(debug8){	     
	     std::cout << "counter[jentry" << jentry << "][" << nn << "] = " << counter[jentry][nn];	     
	     std::cout << " : mean_pos_X[jentry" << jentry << "][" << nn << "] = " << mean_pos_X[jentry][nn];
	     std::cout << ", mean_pos_Y[jentry" << jentry << "][" << nn << "] = " << mean_pos_Y[jentry][nn] << std::endl;
	   }
	   }
	   
	   } // mm   

	 mean_pos_X[jentry][nn] /= counter[jentry][nn];
	 mean_pos_Y[jentry][nn] /= counter[jentry][nn];
	 
	 //	 mean_pos_X[jentry][nn] = pos_X[jentry][maxhitID[jentry][nn]];
	 //	 mean_pos_Y[jentry][nn] = pos_Y[jentry][maxhitID[jentry][nn]];
	 
	 if(nn!=3){
	   b[jentry].SetTestDataX(mean_pos_X[jentry][nn]);
	   b[jentry].SetTestDataY(mean_pos_Y[jentry][nn]);
	 }
	 if(debug8){  
	   std::cout << "maxhitID[jentry" << jentry << "][" << nn << "] = " << maxhitID[jentry][nn];
	   std::cout << " : mean_pos_X[jentry" << jentry << "][" << nn << "] = " << mean_pos_X[jentry][nn];
	   std::cout << ", mean_pos_Y[jentry" << jentry << "][" << nn << "] = " << mean_pos_Y[jentry][nn] << std::endl;
	 }
	 
	 if(nn==0 && detector_id[jentry]==3 && hitl[jentry]<evecut) mean2Dhist0->Fill(mean_pos_X[jentry][nn],mean_pos_Y[jentry][nn]);
	 if(nn==1 && detector_id[jentry]==3 && hitl[jentry]<evecut) mean2Dhist1->Fill(mean_pos_X[jentry][nn],mean_pos_Y[jentry][nn]);
	 if(nn==2 && detector_id[jentry]==3 && hitl[jentry]<evecut) mean2Dhist2->Fill(mean_pos_X[jentry][nn],mean_pos_Y[jentry][nn]);
	 if(nn==3 && detector_id[jentry]==3 && hitl[jentry]<evecut){
	   mean2DhistDUT->Fill(mean_pos_X[jentry][nn],mean_pos_Y[jentry][nn]);
	   mean_h_X->Fill(mean_pos_X[jentry][3]);
	   mean_h_Y->Fill(mean_pos_Y[jentry][3]);
	   }
	 
	
       } // nn

       b[jentry].SetHist0X();
       b[jentry].SetHist0Y();
       grad_X[jentry] = b[jentry].GetGradX();
       grad_Y[jentry] = b[jentry].GetGradY();
       
       //       grad_X[jentry] = (mean_pos_X[jentry][2] - mean_pos_X[jentry][0]) / (2 * tr_pitch);
       //       grad_Y[jentry] = (mean_pos_Y[jentry][2] - mean_pos_Y[jentry][0]) / (2 * tr_pitch);
       
       DUT_re_position_X[jentry] = mean_pos_X[jentry][2]  + 30.0*1000 * grad_X[jentry];
       DUT_re_position_Y[jentry] = mean_pos_Y[jentry][2]  + 30.0*1000 * grad_Y[jentry];
       difference_X[jentry] = pos_X[jentry][3] - DUT_re_position_X[jentry];
       difference_Y[jentry] = pos_Y[jentry][3] - DUT_re_position_Y[jentry];

       if(debug9){
	 std::cout << "....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......" << jentry << " th entry started!"  << std::endl;
	 std::cout << " grad_X[" << jentry << "] = " << grad_X[jentry];
	 std::cout << " grad_Y[" << jentry << "] = " << grad_Y[jentry] << std::endl;
	 std::cout << " DUT_re_position_X[" << jentry << "] = " << DUT_re_position_X[jentry];
	 std::cout << " DUT_re_position_Y[" << jentry << "] = " << DUT_re_position_Y[jentry] << std::endl;
	 std::cout << " difference_X[" << jentry << "] = " << difference_X[jentry];
	 std::cout << " difference_X[" << jentry << "] = " << difference_Y[jentry] << std::endl;
       }
     
       if(detector_id[jentry]==3 && hitl[jentry]<evecut){
	 
	 h_DUT->Fill(mean_pos_X[jentry][3],mean_pos_Y[jentry][3]);
	 h_re_DUT->Fill(DUT_re_position_X[jentry], DUT_re_position_Y[jentry]);
	 h_differenceX->Fill(difference_X[jentry]);
	 h_differenceY->Fill(difference_Y[jentry]);
	 
       }

     }  // jentry
     
     TCanvas *c_neighbor = new TCanvas("non neighbor number","non neighbor number",1600,1200); 
     h_Nneighbor->SetXTitle("XorY distance from Emax Pixel [#mum]");
     h_Nneighbor->Draw();
     
     TCanvas *c_mean2D = new TCanvas("mean2D","mean2D",1600,1200); 
     c_mean2D->Divide(2,2);
     mean2Dhist0->SetXTitle("X axis [#mum]");
     mean2Dhist1->SetXTitle("X axis [#mum]");
     mean2Dhist2->SetXTitle("X axis [#mum]");
     mean2DhistDUT->SetXTitle("X axis [#mum]");
     mean2Dhist0->SetYTitle("Y axis [#mum]");
     mean2Dhist1->SetYTitle("Y axis [#mum]");
     mean2Dhist2->SetYTitle("Y axis [#mum]");
     mean2DhistDUT->SetYTitle("Y axis [#mum]");
     c_mean2D->cd(1);
     mean2Dhist0->Draw("colz");
     c_mean2D->cd(2);
     mean2Dhist1->Draw("colz");
     c_mean2D->cd(3);
     mean2Dhist2->Draw("colz");
     c_mean2D->cd(4);
     mean2DhistDUT->Draw("colz");
     
     TCanvas *c_mean1D = new TCanvas("mean1D","mean1D",800,1600);      
     c_mean1D->Divide(1,2);
     c_mean1D->cd(1);
     mean_h_X->Draw();
     c_mean1D->cd(2);
     mean_h_Y->Draw();

     
     TCanvas *c_re_DUT = new TCanvas("c_re_DUT","Reconsted DUT Position",750,1500);
     c_re_DUT->Divide(1,2);
     h_re_DUT->SetXTitle("X [um]");
     h_re_DUT->SetXTitle("Y [um]");
     h_re_DUT->SetStats(1);
     //DUT position draw
     c_re_DUT->cd(1);
     h_DUT->Draw("colz");
     //Reconstructed position draw
     c_re_DUT->cd(2);
     h_re_DUT->Draw("colz");
     
     TCanvas *c_difference = new TCanvas("c_difference","Differnce between Origin and Reconstruction",800,1600);
     c_difference->Divide(1,2);
     h_differenceX->SetXTitle("Differnce X[#mum]");
     h_differenceY->SetXTitle("Differnce Y[#mum]");
     gStyle->SetOptFit(1111);
     //difference x  draw
     c_difference->cd(1);
     h_differenceX->Fit("gaus");
     h_differenceX->Draw();
     //difference y  draw
     c_difference->cd(2);
     h_differenceY->Fit("gaus");
     h_differenceY->Draw();
          
     
     TCanvas *c_hit = new TCanvas("hit number","hit number",1600,1200);
     c_hit->Divide(2,2);
     c_hit->cd(1);
     h_hit0->SetXTitle("Hit Count");
     h_hit0->SetStats(1);
     h_hit0->Draw();
     c_hit->cd(2);
     h_hit1->SetXTitle("Hit Count");
     h_hit1->SetStats(1);
     h_hit1->Draw();
     c_hit->cd(3);
     h_hit2->SetXTitle("Hit Count");
     h_hit2->SetStats(1);
     h_hit2->Draw();
     c_hit->cd(4);
     h_hitDUT->SetXTitle("Hit Count");
     h_hitDUT->SetStats(1);
     h_hitDUT->Draw();
     
     /*
     std::cout << "ID is :" <<  b[5].GetID()  << std::endl;
     
     for(int ii=0;ii<b[5].GetTestDataX().size();ii++){
       std::cout << "vector is :" <<  b[5].GetTestDataX()[ii]  << std::endl;
     }     
     TCanvas *test  = new TCanvas("test","test",1000,1000);
     TH2D    * frame = new TH2D("frame","frame",1,0,100000,1,490,520);
     frame->Draw();
     b[0].GetGraph0X()->Draw("PSame");
     std::cout << "grad is : " <<  b[0].GetGradX()  << std::endl;
     */
     
   }  //  if(MeanCalmode
}


