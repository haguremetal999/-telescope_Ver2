#define testclass_cxx
#include "testclass.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <TH2.h>
#include <TH3.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TString.h>
#include <TGraph2D.h>
#include <cstdlib>  // abs() for integer
#include <cmath>    // abs() for float, and fabs()
#include "OneLoopAnalysis.h"
#include <random>

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
//    ientry for TTree::GetEntry and TBranch::GetEntry//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   bool debug0 = true;
   bool debug1 = false;
   bool debug2 = false;
   bool debug3 = false; 
   
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   int maxhits = 0;
   int analysisnumber =1;
   
   int hitl;
   int IADRl[200];
   double energylossl[200];
   int NN =2;
   int PixelNumber=1000;

   std::cout << "---------- Please input loop number! ----------" << std::endl;
   std::cin >> analysisnumber;
   if(analysisnumber > nentries){
     std::cout << "---------- Error! loop number is over entries!  ----------" << std::endl;
     return;
   }
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     if(debug1)     std::cout << "=========================================================== "  << jentry << "th event start" <<std::endl;        
     Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(jentry!=analysisnumber) continue;
      
      //------------------------------------------------------ hit number check -------------------------------------------------------
      
      if(debug1) std::cout << "******************************** hit number check" << std::endl;
      hitl=Nhits;
      if(debug1) std::cout << "Nhits = "  << hitl << ", jentry = " << jentry <<std::endl;
      if(Nhits > maxhits)  maxhits = Nhits;
      
      //---------------------------------------------------- first position setting-------------------------------------------------
      if(debug2)    std::cout << "***************************************** first position  setting" << std::endl;
      
      //first position histgram making
       if(debug2) std::cout << "j=" << jentry << " : (x,y) = ( " << BeamPosX0 <<", "<< BeamPosY0 << ")" << std::endl;
    

   //---------------------------------------IADR & Energyloss setting --------------------------------------
      
     //IADR setting
       IADRl[0]=IADR0;
       IADRl[1]=IADR1;
       IADRl[2]=IADR2;
       IADRl[3]=IADR3;
       IADRl[4]=IADR4;
       IADRl[5]=IADR5;
       IADRl[6]=IADR6;
       IADRl[7]=IADR7;
       IADRl[8]=IADR8;
       IADRl[9]=IADR9;
       IADRl[10]=IADR10;
       IADRl[11]=IADR11;
       IADRl[12]=IADR12;
       IADRl[13]=IADR13;
       IADRl[14]=IADR14;
       IADRl[15]=IADR15;
       IADRl[16]=IADR16;
       IADRl[17]=IADR17;
       IADRl[18]=IADR18;
       IADRl[19]=IADR19;
       IADRl[20]=IADR20;
       IADRl[21]=IADR21;
       IADRl[22]=IADR22;
       IADRl[23]=IADR23;
       IADRl[24]=IADR24;
       IADRl[25]=IADR25;
       IADRl[26]=IADR26;
       IADRl[27]=IADR27;
       IADRl[28]=IADR28;
       IADRl[29]=IADR29;
       IADRl[30]=IADR30;
       IADRl[31]=IADR31;
       IADRl[32]=IADR32;
       IADRl[33]=IADR33;
       IADRl[34]=IADR34;
       IADRl[35]=IADR35;
       IADRl[36]=IADR36;
       IADRl[37]=IADR37;
       IADRl[38]=IADR38;
       IADRl[39]=IADR39;
       IADRl[40]=IADR40;
       IADRl[41]=IADR41;
       IADRl[42]=IADR42;
       IADRl[43]=IADR43;
       IADRl[44]=IADR44;
       IADRl[45]=IADR45;
       IADRl[46]=IADR46;
       IADRl[47]=IADR47;
       IADRl[48]=IADR48;
       IADRl[49]=IADR49;
       IADRl[50]=IADR50;
       IADRl[51]=IADR51;
       IADRl[52]=IADR52;
       IADRl[53]=IADR53;
       IADRl[54]=IADR54;
       IADRl[55]=IADR55;
       IADRl[56]=IADR56;
       IADRl[57]=IADR57;
       IADRl[58]=IADR58;
       IADRl[59]=IADR59;
       IADRl[60]=IADR60;
       IADRl[61]=IADR61;
       IADRl[62]=IADR62;
       IADRl[63]=IADR63;
       IADRl[64]=IADR64;
       IADRl[65]=IADR65;
       IADRl[66]=IADR66;
       IADRl[67]=IADR67;
       IADRl[68]=IADR68;
       IADRl[69]=IADR69;
       IADRl[70]=IADR70;
       IADRl[71]=IADR71;
       IADRl[72]=IADR72;
       IADRl[73]=IADR73;
       IADRl[74]=IADR74;
       IADRl[75]=IADR75;
       IADRl[76]=IADR76;
       IADRl[77]=IADR77;
       IADRl[78]=IADR78;
       IADRl[79]=IADR79;
       IADRl[80]=IADR80;
       IADRl[81]=IADR81;
       IADRl[82]=IADR82;
       IADRl[83]=IADR83;
       IADRl[84]=IADR84;
       IADRl[85]=IADR85;
       IADRl[86]=IADR86;
       IADRl[87]=IADR87;
       IADRl[88]=IADR88;
       IADRl[89]=IADR89;
       IADRl[90]=IADR90;
       IADRl[91]=IADR91;
       IADRl[92]=IADR92;
       IADRl[93]=IADR93;
       IADRl[94]=IADR94;
       IADRl[95]=IADR95;
       IADRl[96]=IADR96;
       IADRl[97]=IADR97;
       IADRl[98]=IADR98;
       IADRl[99]=IADR99;
       IADRl[100]=IADR100;
       IADRl[101]=IADR101;
       IADRl[102]=IADR102;
       IADRl[103]=IADR103;
       IADRl[104]=IADR104;
       IADRl[105]=IADR105;
       IADRl[106]=IADR106;
       IADRl[107]=IADR107;
       IADRl[108]=IADR108;
       IADRl[109]=IADR109;
       IADRl[110]=IADR110;
       IADRl[111]=IADR111;
       IADRl[112]=IADR112;
       IADRl[113]=IADR113;
       IADRl[114]=IADR114;
       IADRl[115]=IADR115;
       IADRl[116]=IADR116;
       IADRl[117]=IADR117;
       IADRl[118]=IADR118;
       IADRl[119]=IADR119;
       IADRl[120]=IADR120;
       IADRl[121]=IADR121;
       IADRl[122]=IADR122;
       IADRl[123]=IADR123;
       IADRl[124]=IADR124;
       IADRl[125]=IADR125;
       IADRl[126]=IADR126;
       IADRl[127]=IADR127;
       IADRl[128]=IADR128;
       IADRl[129]=IADR129;
       IADRl[130]=IADR130;
       IADRl[131]=IADR131;
       IADRl[132]=IADR132;
       IADRl[133]=IADR133;
       IADRl[134]=IADR134;
       IADRl[135]=IADR135;
       IADRl[136]=IADR136;
       IADRl[137]=IADR137;
       IADRl[138]=IADR138;
       IADRl[139]=IADR139;
       IADRl[140]=IADR140;
       IADRl[141]=IADR141;
       IADRl[142]=IADR142;
       IADRl[143]=IADR143;
       IADRl[144]=IADR144;
       IADRl[145]=IADR145;
       IADRl[146]=IADR146;
       IADRl[147]=IADR147;
       IADRl[148]=IADR148;
       IADRl[149]=IADR149;
       IADRl[150]=IADR150;
       IADRl[151]=IADR151;
       IADRl[152]=IADR152;
       IADRl[153]=IADR153;
       IADRl[154]=IADR154;
       IADRl[155]=IADR155;
       IADRl[156]=IADR156;
       IADRl[157]=IADR157;
       IADRl[158]=IADR158;
       IADRl[159]=IADR159;
       IADRl[160]=IADR160;
       IADRl[161]=IADR161;
       IADRl[162]=IADR162;
       IADRl[163]=IADR163;
       IADRl[164]=IADR164;
       IADRl[165]=IADR165;
       IADRl[166]=IADR166;
       IADRl[167]=IADR167;
       IADRl[168]=IADR168;
       IADRl[169]=IADR169;
       IADRl[170]=IADR170;
       IADRl[171]=IADR171;
       IADRl[172]=IADR172;
       IADRl[173]=IADR173;
       IADRl[174]=IADR174;
       IADRl[175]=IADR175;
       IADRl[176]=IADR176;
       IADRl[177]=IADR177;
       IADRl[178]=IADR178;
       IADRl[179]=IADR179;
       IADRl[180]=IADR180;
       IADRl[181]=IADR181;
       IADRl[182]=IADR182;
       IADRl[183]=IADR183;
       IADRl[184]=IADR184;
       IADRl[185]=IADR185;
       IADRl[186]=IADR186;
       IADRl[187]=IADR187;
       IADRl[188]=IADR188;
       IADRl[189]=IADR189;
       IADRl[190]=IADR190;
       IADRl[191]=IADR191;
       IADRl[192]=IADR192;
       IADRl[193]=IADR193;
       IADRl[194]=IADR194;
       IADRl[195]=IADR195;
       IADRl[196]=IADR196;
       IADRl[197]=IADR197;
       IADRl[198]=IADR198;
       IADRl[199]=IADR199;
       
       //energy loss setting
       energylossl[0]=E0;
       energylossl[1]=E1;
       energylossl[2]=E2;
       energylossl[3]=E3;
       energylossl[4]=E4;
       energylossl[5]=E5;
       energylossl[6]=E6;
       energylossl[7]=E7;
       energylossl[8]=E8;
       energylossl[9]=E9;
       energylossl[10]=E10;
       energylossl[11]=E11;
       energylossl[12]=E12;
       energylossl[13]=E13;
       energylossl[14]=E14;
       energylossl[15]=E15;
       energylossl[16]=E16;
       energylossl[17]=E17;
       energylossl[18]=E18;
       energylossl[19]=E19;
       energylossl[20]=E20;
       energylossl[21]=E21;
       energylossl[22]=E22;
       energylossl[23]=E23;
       energylossl[24]=E24;
       energylossl[25]=E25;
       energylossl[26]=E26;
       energylossl[27]=E27;
       energylossl[28]=E28;
       energylossl[29]=E29;
       energylossl[30]=E30;
       energylossl[31]=E31;
       energylossl[32]=E32;
       energylossl[33]=E33;
       energylossl[34]=E34;
       energylossl[35]=E35;
       energylossl[36]=E36;
       energylossl[37]=E37;
       energylossl[38]=E38;
       energylossl[39]=E39;
       energylossl[40]=E40;
       energylossl[41]=E41;
       energylossl[42]=E42;
       energylossl[43]=E43;
       energylossl[44]=E44;
       energylossl[45]=E45;
       energylossl[46]=E46;
       energylossl[47]=E47;
       energylossl[48]=E48;
       energylossl[49]=E49;
       energylossl[50]=E50;
       energylossl[51]=E51;
       energylossl[52]=E52;
       energylossl[53]=E53;
       energylossl[54]=E54;
       energylossl[55]=E55;
       energylossl[56]=E56;
       energylossl[57]=E57;
       energylossl[58]=E58;
       energylossl[59]=E59;
       energylossl[60]=E60;
       energylossl[61]=E61;
       energylossl[62]=E62;
       energylossl[63]=E63;
       energylossl[64]=E64;
       energylossl[65]=E65;
       energylossl[66]=E66;
       energylossl[67]=E67;
       energylossl[68]=E68;
       energylossl[69]=E69;
       energylossl[70]=E70;
       energylossl[71]=E71;
       energylossl[72]=E72;
       energylossl[73]=E73;
       energylossl[74]=E74;
       energylossl[75]=E75;
       energylossl[76]=E76;
       energylossl[77]=E77;
       energylossl[78]=E78;
       energylossl[79]=E79;
       energylossl[80]=E80;
       energylossl[81]=E81;
       energylossl[82]=E82;
       energylossl[83]=E83;
       energylossl[84]=E84;
       energylossl[85]=E85;
       energylossl[86]=E86;
       energylossl[87]=E87;
       energylossl[88]=E88;
       energylossl[89]=E89;
       energylossl[90]=E90;
       energylossl[91]=E91;
       energylossl[92]=E92;
       energylossl[93]=E93;
       energylossl[94]=E94;
       energylossl[95]=E95;
       energylossl[96]=E96;
       energylossl[97]=E97;
       energylossl[98]=E98;
       energylossl[99]=E99;
       energylossl[100]=E100;
       energylossl[101]=E101;
       energylossl[102]=E102;
       energylossl[103]=E103;
       energylossl[104]=E104;
       energylossl[105]=E105;
       energylossl[106]=E106;
       energylossl[107]=E107;
       energylossl[108]=E108;
       energylossl[109]=E109;
       energylossl[110]=E110;
       energylossl[111]=E111;
       energylossl[112]=E112;
       energylossl[113]=E113;
       energylossl[114]=E114;
       energylossl[115]=E115;
       energylossl[116]=E116;
       energylossl[117]=E117;
       energylossl[118]=E118;
       energylossl[119]=E119;
       energylossl[120]=E120;
       energylossl[121]=E121;
       energylossl[122]=E122;
       energylossl[123]=E123;
       energylossl[124]=E124;
       energylossl[125]=E125;
       energylossl[126]=E126;
       energylossl[127]=E127;
       energylossl[128]=E128;
       energylossl[129]=E129;
       energylossl[130]=E130;
       energylossl[131]=E131;
       energylossl[132]=E132;
       energylossl[133]=E133;
       energylossl[134]=E134;
       energylossl[135]=E135;
       energylossl[136]=E136;
       energylossl[137]=E137;
       energylossl[138]=E138;
       energylossl[139]=E139;
       energylossl[140]=E140;
       energylossl[141]=E141;
       energylossl[142]=E142;
       energylossl[143]=E143;
       energylossl[144]=E144;
       energylossl[145]=E145;
       energylossl[146]=E146;
       energylossl[147]=E147;
       energylossl[148]=E148;
       energylossl[149]=E149;
       energylossl[150]=E150;
       energylossl[151]=E151;
       energylossl[152]=E152;
       energylossl[153]=E153;
       energylossl[154]=E154;
       energylossl[155]=E155;
       energylossl[156]=E156;
       energylossl[157]=E157;
       energylossl[158]=E158;
       energylossl[159]=E159;
       energylossl[160]=E160;
       energylossl[161]=E161;
       energylossl[162]=E162;
       energylossl[163]=E163;
       energylossl[164]=E164;
       energylossl[165]=E165;
       energylossl[166]=E166;
       energylossl[167]=E167;
       energylossl[168]=E168;
       energylossl[169]=E169;
       energylossl[170]=E170;
       energylossl[171]=E171;
       energylossl[172]=E172;
       energylossl[173]=E173;
       energylossl[174]=E174;
       energylossl[175]=E175;
       energylossl[176]=E176;
       energylossl[177]=E177;
       energylossl[178]=E178;
       energylossl[179]=E179;
       energylossl[180]=E180;
       energylossl[181]=E181;
       energylossl[182]=E182;
       energylossl[183]=E183;
       energylossl[184]=E184;
       energylossl[185]=E185;
       energylossl[186]=E186;
       energylossl[187]=E187;
       energylossl[188]=E188;
       energylossl[189]=E189;
       energylossl[190]=E190;
       energylossl[191]=E191;
       energylossl[192]=E192;
       energylossl[193]=E193;
       energylossl[194]=E194;
       energylossl[195]=E195;
       energylossl[196]=E196;
       energylossl[197]=E197;
       energylossl[198]=E198;
       energylossl[199]=E199;

       //////////////////////////////////////////       
       OneLoopAnalysis a(jentry);
       a.SetUp(IADRl, energylossl,Nhits,PixelNumber);
       a.SetThreshold(-1,-1);
       a.SetRange(128,64,64);
       a.SetDUTRange(1000,500,500);
       a.SetHitPixel();
       a.MakeCluster(NN);
       a.Set2DHist();
       //       a.SetProjectionX();
       //       a.SetCut2DHist();
       //       a.Set3DGraph();
       //       a.Set3DGraphSame();
       //       a.Set3DSlice();
       //////////////////////////////////////////
       
     for(int mm=0;mm<Nhits;mm++){
       if(debug1){       
	 std::cout << "================================================" << std::endl;
	 std::cout << "IADRl["<< jentry << "][" << mm  << "]= "  << IADRl[mm] << std::endl;
	 std::cout << "ID   ["<< jentry << "][" << mm  << "]= "  << a.GetID()[mm] << std::endl;
	 std::cout << "posx ["<< jentry << "][" << mm  << "]= "  << a.GetX()[mm] << std::endl;
	 std::cout << "poxy ["<< jentry << "][" << mm  << "]= "  << a.GetY()[mm] << std::endl;
	 std::cout << "loss ["<< jentry << "][" << mm  << "]= "  << a.GetLoss()[mm] << std::endl;
       }       
     } // mm 
   } //jentry
}


