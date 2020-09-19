//In this class, all X/Y arguments are using [pixel] unit. And choose graph units [pixel] or [um] as neede.
//But X/Ydif and X/Yspread is calculated as [um] unit. 
class MakeHist{
 private : 
  TH1D * HX1D[4];
  TH1D * HY1D[4];
  TH2D * H2D[4];
  TF1 * FX1D[4];
  TF1 * FY1D[4];
  TF1 * F1D[2];
  TH2D * ReH2D;
  TF1 * DifFX1D;
  TF1 * DifFY1D;
  TH1D * DifHX1D;
  TH1D * DifHY1D;
  TH1D * HEnergy[4];
  TH1D * HTotalEnergy;
  TH2D * HFirst2D;
  TH1D * HCluster1D[4];
    
  int xbin,ybin,difbin,bin1D,DUTbin,Clusterbin;
  double xmin,ymin,min1D;
  double xmax,ymax,max1D;
  double DUTmax,DUTmin;
  double Xspread,Yspread;
  int difwidth,Clusterwidth;
  double Xdif,Ydif;
  int enebin,enemin,enemax;
  int enebinDUT,eneminDUT,enemaxDUT;
  double pixelsize;
  bool ImgFlag;
  int ImgNum;
  
 public :
  MakeHist(){
    xbin = 100;
    xmin = 450;
    xmax = 550;
    ybin = 100;
    ymin = 450;
    ymax = 550;

    bin1D = 100;
    min1D = 450;
    max1D = 550;
    
    enebin = 100;
    enemin = 0;
    enemax = 100;
    enebinDUT = 100;
    eneminDUT = 60;
    enemaxDUT = 200;
    
    difbin = 200;
    difwidth = 10;

    Clusterbin = 100;
    Clusterwidth = 100;
    
    gStyle->SetOptFit(1111);
    gStyle->SetStatH(0.15);
    gStyle->SetStatW(0.2);
    ImgFlag=false;
  }
  ~MakeHist(){}

  bool UnitFlag = false;

  //////////////////////////////// Getter  ////////////////////////////////
  double GetXspread(){ return Xspread; }
  double GetYspread(){ return Yspread; }
  double GetXdif(){ return Xdif; }
  double GetYdif(){ return Ydif; }

  //////////////////////////////// Setter  ////////////////////////////////
  void SetImgNum(int i){
    ImgNum = i;
    ImgFlag = true;
  }
  
  void SetPixelSize(double PixelSize){ pixelsize = PixelSize; }

  void SetRange1D(int bin,double min,double max){
    bin1D = bin;
    min1D = min;
    max1D = max;
  }
  
  void SetRange2D(int bin,double min,double max){
    xbin = bin;
    xmin = min;
    xmax = max;
    ybin = bin;
    ymin = min;
    ymax = max;
  }
  
  void SetDUTRange(int bin,double min,double max){
    DUTbin = bin;
    DUTmin = min;
    DUTmax = max;
  }
  
  void SetDifRange(int difb,double difw){
    difbin = difb;
    difwidth = difw;
  }

  void SetClusterRange(int bin,double width){
    Clusterbin = bin;
    Clusterwidth = width;
  }
  
  void SetEneBin(int eneBin,int eneMin,int eneMax,int eneBinDUT,int eneMinDUT,int eneMaxDUT){
    enebin = eneBin;
    enemin = eneMin;
    enemax = eneMax;
    enebinDUT = eneBinDUT;
    eneminDUT = eneMinDUT;
    enemaxDUT = eneMaxDUT;    
  }
  
  //////////////////////////////// 1D Distribution  ////////////////////////////////
  //--------------------- X ------------------------
  void SetHX1D(){
    for(int nn=0;nn<4;nn++){
      if(nn==3){ HX1D[nn] = new TH1D(Form("Tracker%dHX1D",nn),"DUT",DUTbin,DUTmin,DUTmax);}
      else{	HX1D[nn] = new TH1D(Form("Tracker%dHX1D",nn),Form("TRracker%d",nn),bin1D,min1D,max1D);}
      HX1D[nn]->SetXTitle("X [#mum]");
      //      HX1D[nn]->SetXTitle("X [#pixel]");
    }
  }  
  void PushDataHX1D(double X[4]){
    for(int nn=0;nn<4;nn++){
      if(nn!=3){ HX1D[nn]->Fill(X[nn]*pixelsize); }
      else{ HX1D[nn]->Fill(X[nn]); }
      //      HX1D[nn]->Fill(X[nn]);
    } // nn
  }
  void DrawHX1D(){
    TCanvas * cX1D = new TCanvas("cX1D","cX1D",1600,1200);
    cX1D->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      FX1D[nn] = new TF1(Form("Tracker%dFX1D",nn),"gaus");
      cX1D->cd(nn+1);
      HX1D[nn]->Fit(FX1D[nn],"Q","",min1D,max1D);
      HX1D[nn]->Draw();
    }
    if(ImgFlag){ cX1D->Print(Form("HX1D%d.png",ImgNum));}
    else{ cX1D->Print("HX1D.png"); }
    Xspread = FX1D[3]->GetParameter(2);
  }

  //--------------------- Y ------------------------
  void SetHY1D(){
    for(int nn=0;nn<4;nn++){
      if(nn==3){ HY1D[nn] = new TH1D(Form("Tracker%dHY1D",nn),"DUT",DUTbin,DUTmin,DUTmax);}
      else{	HY1D[nn] = new TH1D(Form("Tracker%dHY1D",nn),Form("TRracker%d",nn),bin1D,min1D,max1D);}
      HY1D[nn]->SetXTitle("Y [#mum]");
      //      HY1D[nn]->SetXTitle("Y [pixel]");
    }
  }  
  void PushDataHY1D(double Y[4]){
    for(int nn=0;nn<4;nn++){
      if(nn!=3){ HY1D[nn]->Fill(Y[nn]*pixelsize); }
      else{ HY1D[nn]->Fill(Y[nn]); }
      //      HY1D[nn]->Fill(Y[nn]);
    } // nn
  }
  void DrawHY1D(){
    TCanvas * cY1D = new TCanvas("cY1D","cY1D",1600,1200);
    cY1D->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      FY1D[nn] = new TF1(Form("Tracker%dFY1D",nn),"gaus");
      cY1D->cd(nn+1);
      HY1D[nn]->Fit(FY1D[nn],"Q","",min1D,max1D);
      HY1D[nn]->Draw();
    }
    if(ImgFlag){ cY1D->Print(Form("HY1D%d.png",ImgNum)); }
    else{ cY1D->Print("HY1D.png"); }
    Yspread = FY1D[3]->GetParameter(2);
	
  }
  
  //--------------------- DUT X and Y ------------------------
  void DrawH1D(){
    TCanvas * c1D = new TCanvas("c1D","c1D",800,1600);
    c1D->Divide(1,2);
    F1D[0] = new TF1("F1DX","gaus");
    F1D[1] = new TF1("F1DY","gaus");
    c1D->cd(1);
    HX1D[3]->Fit(F1D[0],"Q","",DUTmin,DUTmax);
    HX1D[3]->SetTitle("X axis");
    HX1D[3]->Draw();
    c1D->cd(2);
    HY1D[3]->Fit(F1D[1],"Q","",DUTmin,DUTmax);
    HY1D[3]->SetTitle("Y axis");
    HY1D[3]->Draw();
    if(ImgFlag){ c1D->Print(Form("H1D%d.png",ImgNum)); }
    else{ c1D->Print("H1D.png"); }
    Xspread = F1D[0]->GetParameter(2);
    Yspread = F1D[1]->GetParameter(2);
  }

  //////////////////////////////// 2D Distribution ////////////////////////////////
  void SetH2D(){
    for(int nn=0;nn<4;nn++){
      if(nn==3){ H2D[nn] = new TH2D(Form("Tracker%dH2D",nn),"DUT",DUTbin,DUTmin,DUTmax,DUTbin,DUTmin,DUTmax);}
      else{ H2D[nn] = new TH2D(Form("Tracker%dH2D",nn),Form("TRracker%d",nn),xbin,xmin,xmax,ybin,ymin,ymax);}
      if(UnitFlag){
	H2D[nn]->SetXTitle("X [#mum]");
	H2D[nn]->SetYTitle("Y [#mum]");
      }else{
	H2D[nn]->SetXTitle("X [pixel]");
	H2D[nn]->SetYTitle("Y [pixel]");
      }
    }
  }  
  void PushDataH2D(double X[4],double Y[4]){
    for(int nn=0;nn<4;nn++){
      if(UnitFlag){ 
	if(nn!=3){H2D[nn]->Fill(X[nn]*pixelsize,Y[nn]*pixelsize);}
	else{ H2D[nn]->Fill(X[nn],Y[nn]); }
      } // [um]
      else{ H2D[nn]->Fill(X[nn],Y[nn]); } // [px] 
    } // nn
  }
  void DrawH2D(){
    TCanvas * c2D = new TCanvas("c2D","c2D",1600,1200);
    gStyle->SetStatH(0.2);
    gStyle->SetStatW(0.3);
    c2D->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      c2D->cd(nn+1);
      H2D[nn]->Draw("COLZ");
    }
    c2D->Print("H2D.png");
  }
  
  //////////////////////////////// Reconstruction ////////////////////////////////
   void SetReconstructionH2D(){
     ReH2D = new TH2D("dReH2D","Reconstruction",xbin,xmin,xmax,ybin,ymin,ymax);
     if(UnitFlag){
       ReH2D->SetXTitle("X [#mum]");
       ReH2D->SetYTitle("Y [#mum]");
     }else{
       ReH2D->SetXTitle("X [pixel]");
       ReH2D->SetYTitle("Y [pixel]");
     }
   }
   void PushDataReconstructionH2D(double X,double Y){
     if(UnitFlag){ ReH2D->Fill(X*pixelsize,Y*pixelsize); }
     else{ ReH2D->Fill(X,Y); }
  }
  void DrawReconstructionH2D(){
    TCanvas * Rec2D = new TCanvas("Rec2D","Rec2D",800,1600);
    Rec2D->Divide(1,2);
    Rec2D->cd(1);
    H2D[3]->Draw("COLZ");
    Rec2D->cd(2);
    ReH2D->Draw("COLZ");
    Rec2D->Print("Reconstruction.png");
  }

  //////////////////////////////// Position  Resolution  ////////////////////////////////
  void SetDifH1D(){
    DifHX1D = new TH1D("DifHX1D","X Difference between DUT and Reconstruction",difbin,-difwidth,difwidth);
    DifHY1D = new TH1D("DifHY1D","Y Difference between DUT and Reconstruction",difbin,-difwidth,difwidth);
    DifHX1D->SetXTitle("Difference X[#mum]");
    DifHY1D->SetXTitle("Difference Y[#mum]");
  }
  void PushDataDifH1D(double difX,double difY){
    DifHX1D->Fill(difX);
    DifHY1D->Fill(difY);

  }
  void DrawDifH1D(){
    TCanvas * cDif1D = new TCanvas("cDif1D","cDif1D",800,1600);
    gStyle->SetStatH(0.15);
    gStyle->SetStatW(0.2);
    cDif1D->Divide(1,2);
    DifFX1D = new TF1("DifFX1D","gaus");
    DifFY1D = new TF1("DifFY1D","gaus");
    cDif1D->cd(1);
    DifHX1D->Fit(DifFX1D,"Q","");
    DifHX1D->Draw();
    Xdif = DifFX1D->GetParameter(2);
    cDif1D->cd(2);
    DifHY1D->Fit(DifFY1D,"Q","");
    DifHY1D->Draw();
    if(ImgFlag){ cDif1D->Print(Form("DifH1D%d.png",ImgNum));}
    else{ cDif1D->Print("DifH1D.png");}
    Ydif = DifFY1D->GetParameter(2);
  }

  //////////////////////////////// Energy Loss ////////////////////////////////
  void SetEnergyH1D(){
    for(int nn=0;nn<4;nn++){
      if(nn==3){ HEnergy[nn] = new TH1D(Form("EnergyLoss%d",nn),"DUT Energy Loss",enebinDUT,eneminDUT,enemaxDUT); }
      else { HEnergy[nn] = new TH1D(Form("EnergyLoss%d",nn),Form("Tracker%d Energy Loss",nn),enebin,enemin,enemax); }
      HEnergy[nn]->SetXTitle("Energy Loss [keV]");
    } // nn
    HTotalEnergy = new TH1D("Totalenergy","Total Energy Loss",enebinDUT,eneminDUT,enemaxDUT+100);
  }
  void PushDataEnergyH1D(double totalloss[4],double loss[200],int Nhits){
    for(int nn=0;nn<4;nn++){
      HEnergy[nn]->Fill(totalloss[nn]);
    }
    double totE=0;
    for(int mm=0;mm<Nhits;mm++){
      totE += loss[mm];
    }
    HTotalEnergy->Fill(totE);    
  } 
  void DrawEnergyH1D(){
    TCanvas * cEnergy = new TCanvas("cEnergy","cEnergy",1600,1200);
    TF1 * FEnergy[4];
    cEnergy->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      FEnergy[nn] = new TF1(Form("EnergyTF1%d",nn),"landau");
      cEnergy->cd(nn+1);
      if(nn==3){ HEnergy[nn]->Fit(FEnergy[nn],"Q","",eneminDUT,enemaxDUT);}
      else { HEnergy[nn]->Fit(FEnergy[nn],"Q","",enemin,enebin); 
      HEnergy[nn]->Draw();
      }
    cEnergy->Print("EnergyLoss.png");
    }
    TCanvas * cEnergyCheck = new TCanvas("cEnergyCheck","cEnergyCheck",1600,1200);
    TF1 *FEnergyCheck = new TF1("EnergyTCheck","landau");
    HTotalEnergy->Fit(FEnergyCheck,"Q","",eneminDUT,enemaxDUT+100);
    HTotalEnergy->Draw();
    cEnergyCheck->Print("EnergyCheck.png");
  }

  //////////////////////////////// First Position ////////////////////////////////  
  void SetFirstH2D(){
      HFirst2D = new TH2D("HFirst2D","First Position",xbin,xmin,xmax,ybin,ymin,ymax);
      HFirst2D->SetXTitle("X [pixel]");
      HFirst2D->SetYTitle("Y [pixel]");
  }  
  void PushDataFirstH2D(double X,double Y){
      HFirst2D->Fill(X,Y);
  }
  void DrawFirstH2D(){
    TCanvas * cFirst2D = new TCanvas("cFirst2D","cFirst2D",1600,1200);
    gStyle->SetStatH(0.2);
    gStyle->SetStatW(0.3);
    HFirst2D->Draw("COLZ");
    cFirst2D->Print("HFirst2D.png");
  }

  //////////////////////////////// Cluster Size ////////////////////////////////
    void SetHCluster1D(){
    for(int nn=0;nn<4;nn++){
      if(nn==3){ HCluster1D[nn] = new TH1D(Form("Tracker%dHCluster1D",nn),"DUT",Clusterbin,0,Clusterwidth);}
      else{	HCluster1D[nn] = new TH1D(Form("Tracker%dHCluster1D",nn),Form("TRracker%d",nn),Clusterbin,0,Clusterwidth);}
      HCluster1D[nn]->SetXTitle("Cluster Size");
    }
  }  
  void PushDataHCluster1D(int ClusterSize[4]){
    for(int nn=0;nn<4;nn++){
      HCluster1D[nn]->Fill(ClusterSize[nn]);
    } // nn
  }
  void DrawHCluster1D(){
    TCanvas * cCluster1D = new TCanvas("cCluster1D","cCluster1D",1600,1200);
    cCluster1D->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      cCluster1D->cd(nn+1);
      HCluster1D[nn]->Draw();
    }
    cCluster1D->Print("HCluster1D.png");
  }
  
};
