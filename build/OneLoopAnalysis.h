// In this class, X/Y unit is [pixel], and gradX/Y unit is [pixel/um].
// If you need, Change units from [pixel] to [um]  in (MakeHist.h) file.
// Note that DUT piel size is 1[um] and Tracker0~2 pixel size is specified in Excutable file.
class OneLoopAnalysis{
 private :
  int ClassID;
  int Entry;
  int hitNumber[4];
  int lasthit[4];
  double X[200],Y[200],loss[200];
  int ID[200],IADR[200];
  double totalloss[4];
  int bin,Xcenter,Ycenter;
  double threshold[4];
  int DUTbin,DUTXcenter,DUTYcenter;
  int pixelnumber;
  int counter[4];
  
  std::vector<int> hitPixel[4];
  std::vector<double> hitPixelEnergy[4];
  std::vector<double> hitPixelX[4];
  std::vector<double> hitPixelY[4];
  std::vector<int> Cluster[4];
  std::vector<double> ClusterX[4];
  std::vector<double> ClusterY[4];
  std::vector<double> ClusterEnergy[4];
  double ClusterTotalEnergy[4];
  
  TH2D * h[4];
  TGraph2D * gr3D[4];
  TH2D * h_x[4];
  TH2D * h_y[4];
  TH1D * h_prX;

 public:  
  OneLoopAnalysis(){
    bin = 20;
    Xcenter = 500;
    Ycenter = 500;
    bin = 20;
    Xcenter = 500;
    Ycenter = 500;
    pixelnumber = 128;
  }  
  OneLoopAnalysis(int ID){
    ClassID = ID;
  }
  ~OneLoopAnalysis(){}
  
  //////////////////////////////// Getter  ////////////////////////////////
  int GetClassID(){ return ClassID; }
  int GetBin(){ return Xcenter; }
  TH2D * Get2DHist0(){ return h[0]; }
  TH2D * Get2DHist1(){ return h[1]; }
  TH2D * Get2DHist2(){ return h[2]; }
  TH2D * Get2DHist3(){ return h[3]; }
  TGraph2D * Get3DGraph0(){ return gr3D[0]; }
  
  double * GetX(){ return X; }
  double * GetY(){ return Y; }
  int * GetID(){ return ID; }
  double * GetLoss(){ return loss; }
  
  //////////////////////////////// Setter  ////////////////////////////////
  void SetRange(int binN, int posX, int posY){
    bin =binN;
    Xcenter = posX;
    Ycenter = posY;
  }
  
  void SetDUTRange(int binN, int posX, int posY){
    DUTbin =binN;
    DUTXcenter = posX;
    DUTYcenter = posY;
  }
  
  void SetThreshold(double threTr,double threDUT){
     for(int nn=0;nn<4;nn++){
       threshold[nn] = threTr;
       if(nn==3)  threshold[nn] =threDUT;
     }   
  }
  
  void SetID( int ID ){ ClassID=ID; }
  
  //////////////////////////////// Data processing  ////////////////////////////////
  void SetUp(int *IADRl, double *energylossl, int hitN,int PixelNumber){
    Entry = hitN;
    pixelnumber=PixelNumber;
    for(int mm=0;mm<Entry;mm++){
      IADR[mm] = IADRl[mm];
      ID[mm]    = IADRl[mm]/1000000;
      if(ID[mm]!=3){
	X[mm] = (IADRl[mm] - ID[mm]*1000000)/1000;// - pixelnumber/2; 
	Y[mm] = (IADRl[mm] - ID[mm]*1000000 -( (IADRl[mm] - ID[mm]*1000000)/1000)*1000);//-pixelnumber/2;
      }else{
	X[mm] = (IADRl[mm] - ID[mm]*1000000)/1000;// - 1000/2; 
	Y[mm] = (IADRl[mm] - ID[mm]*1000000 -( (IADRl[mm] - ID[mm]*1000000)/1000)*1000);//-1000/2;
      }
      loss[mm] = energylossl[mm];
      //      std::cout << "lasthit["<< mm <<"] : (ID,X,Y,loss) = ( " << ID[mm] <<", "<< X[mm] << "," << Y[mm] <<", "<< loss[mm] <<")" << std::endl;
    }
    for(int nn=0;nn<4;nn++){
      hitNumber[nn]=0;
    }
    for(int nn=0;nn<4;nn++){
      //      std::cout << "==========================" << std::endl;
      for(int mm=0;mm<Entry;mm++){
	if(ID[mm]==nn){
	  hitNumber[nn]++;
	  lasthit[nn] = mm;
	  totalloss[nn] += loss[mm];
	} 
	//	std::cout << "lasthit["<< mm << "] = " << hitNumber[nn]  << std::endl;
      } // mm
      //      std::cout << "totalloss[" << nn <<"] = "<< totalloss[nn] << std::endl;
    } //nn
  }

  //////////////////////////////// Seting Hit Pixel  ////////////////////////////////
  void SetHitPixel(){
    bool flag;
    for(int nn=0;nn<4;nn++){
    for(int mm=0;mm<Entry;mm++){
      flag = true;
      if(mm==0 && nn==0){
	hitPixel[nn].push_back(IADR[mm]);
	hitPixelX[nn].push_back(X[mm]);
	hitPixelY[nn].push_back(Y[mm]);
	hitPixelEnergy[nn].push_back(loss[mm]);
      }else if(ID[mm]==nn && mm==lasthit[nn-1]+1){
	hitPixel[nn].push_back(IADR[mm]);
	hitPixelX[nn].push_back(X[mm]);
	hitPixelY[nn].push_back(Y[mm]);
	hitPixelEnergy[nn].push_back(loss[mm]);
	//	std::cout << mm<< " th IADR, enrgy = " << IADR[mm] <<", " << loss[mm]<< std:: endl;
      }else{
	for(int ll=0;ll<hitPixel[nn].size();ll++){
	  if(IADR[mm]==hitPixel[nn][ll]){
	    flag = false;
	    hitPixelEnergy[nn][ll] += loss[mm];
	    break;
	  }
	} // ll
      	if(flag && ID[mm]==nn){
	  hitPixel[nn].push_back(IADR[mm]);
	  hitPixelX[nn].push_back(X[mm]);
	  hitPixelY[nn].push_back(Y[mm]);
	  hitPixelEnergy[nn].push_back(loss[mm]);
	  //	  std::cout << mm<< " th IADR, enrgy = " << IADR[mm] <<", " << loss[mm]<< std:: endl;
	}
      }
    } // mm
    } // nn
    for(int nn=0;nn<4;nn++){
      //      std::cout << "==========================" << std::endl;
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	//	std::cout << "hitPixel      [" << nn << "][" << mm <<"] = " << hitPixel[nn][mm] << std::endl;
	//	std::cout << "hitPixelEnergy[" << nn << "][" << mm <<"] = " << hitPixelEnergy[nn][mm] << std::endl;
      }
    }
  }


  //////////////////////////////// Making Cluster  ////////////////////////////////
  void MakeCluster(int NN){
    double maxhitN[4];
    double maxhitY[4];
    double maxhitX[4];
    double maxEnergy[4];
    
    for(int nn=0;nn<4;nn++){
      maxhitN[nn]=0;
      maxhitX[nn]=0;
      maxhitY[nn]=0;
      maxEnergy[nn]=0;
      counter[nn]=0;
      ClusterTotalEnergy[nn]=0;
      
      // Finding Seed
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	if(hitPixelEnergy[nn][mm]>maxEnergy[nn]){
	  maxhitN[nn]=mm;
	  maxhitX[nn]=hitPixelX[nn][mm];
	  maxhitY[nn]=hitPixelY[nn][mm];
	  maxEnergy[nn]=hitPixelEnergy[nn][mm];
	}
	//	std::cout << "(X, Y, E) ["<< nn << "]["<< mm <<"] = "<< hitPixelX[nn][mm] << ", " << hitPixelY[nn][mm] << ", " << hitPixelEnergy[nn][mm]  <<std::endl;
      }  // mm
      
      // Selecting Cluster
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	if( abs(hitPixelX[nn][mm]-maxhitX[nn])<NN+1 && abs(hitPixelY[nn][mm]-maxhitY[nn])<NN+1 && hitPixelEnergy[nn][mm]>threshold[nn]){
	  //	  std::cout << "(difX, difY) ["<< nn << "]["<< mm <<"] = "<< abs(hitPixelX[nn][mm]-maxhitX[nn]) << ", " << abs(hitPixelY[nn][mm]-maxhitY[nn]) << ", " << hitPixelEnergy[nn][mm]  <<std::endl;
	  Cluster[nn].push_back(hitPixel[nn][mm]);
	  ClusterX[nn].push_back(hitPixelX[nn][mm]);
	  ClusterY[nn].push_back(hitPixelY[nn][mm]);
	  ClusterEnergy[nn].push_back(hitPixelEnergy[nn][mm]);
	  ClusterTotalEnergy[nn] += hitPixelEnergy[nn][mm];
	}
      }  // mm
      for(int mm=0;mm<Cluster[nn].size();mm++){
	//	std::cout << "(X, Y) ["<< nn << "]["<< mm <<"] = "<< Cluster[nn][mm] << ", " << Cluster[nn][mm] << ", " << ClusterEnergy[nn][mm]  <<std::endl;
      }
      //      std::cout << "================(N, maxX, maxY)[" << nn << "] = "<< maxhitN[nn] << ", " << maxhitX[nn] << ", " << maxhitY[nn] << std::endl;
    } // nn
  }

  //////////////////////////////// 2D Hist  ////////////////////////////////
  void Set2DHist(){
    TCanvas *c2D = new TCanvas("c2D","c2D",1600,1200);
    c2D->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      //      std::cout << "threshold[" << nn << "] = " << threshold[nn] << std::endl;
      if(nn==3){ h[nn] = new TH2D(Form("Tracker%d",nn),"DUT",DUTbin,DUTXcenter-DUTbin/2,DUTXcenter+DUTbin/2,DUTbin,DUTYcenter-DUTbin/2,DUTYcenter+DUTbin/2);
      }else{  h[nn] = new TH2D(Form("Tracker%d",nn),Form("Tracker%d",nn),bin,Xcenter-bin/2,Xcenter+bin/2,bin,Ycenter-bin/2,Ycenter+bin/2);}
      h[nn]->SetXTitle("X [pixel]");
      h[nn]->SetYTitle("Y [pixel]");
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	h[nn]->Fill(hitPixelX[nn][mm],hitPixelY[nn][mm],hitPixelEnergy[nn][mm]);
	//	std::cout << mm  << "th energy : "<<hitPixelEnergy[nn][mm]  << "  =========filled" << std::endl;
      } // mm//
      c2D->cd(nn+1);
      gStyle->SetStatX(0.35);
      //      gStyle->SetStatY(0);
      h[nn]->Draw("COLZ");
    }
    c2D->Print("2Dhist.png");    
  }

  //////////////////////////////// Cut 2DHist  ////////////////////////////////
  void SetCut2DHist(){
    TCanvas *cCut2D = new TCanvas("cCut2D","cCut2D",1600,1200);
    cCut2D->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      //      std::cout << "threshold[" << nn << "] = " << threshold[nn] << std::endl;
      if(nn==3){ h[nn] = new TH2D(Form("Tracker%d",nn),"DUT",DUTbin,DUTXcenter-DUTbin/2,DUTXcenter+DUTbin/2,DUTbin,DUTYcenter-DUTbin/2,DUTYcenter+DUTbin/2);
      }else{     h[nn] = new TH2D(Form("Tracker%d",nn),Form("Tracker%d",nn),bin,Xcenter-bin/2,Xcenter+bin/2,bin,Ycenter-bin/2,Ycenter+bin/2);}
      //      for(int mm=0;mm<Entry.size();mm++){
      for(int mm=0;mm<Cluster[nn].size();mm++){
	h[nn]->Fill(ClusterX[nn][mm],ClusterY[nn][mm],ClusterEnergy[nn][mm]);
	  //	  std::cout << mm  << "th energy : "<<hitPixelEnergy[nn][mm]  << "  =========filled" << std::endl;
      } // mm//
      cCut2D->cd(nn+1);
      h[nn]->Draw("colz");
    }
    cCut2D->Print("Cut2Dhist.png");    
  }
  
  //////////////////////////////// 3D Graph  ////////////////////////////////
  void Set3DGraph(){
    TCanvas *c3D = new TCanvas("c3D","c3D",1600,1200);
    c3D->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      gr3D[nn] = new TGraph2D;
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	gr3D[nn]->SetPoint(mm,hitPixelX[nn][mm],hitPixelY[nn][mm],hitPixelEnergy[nn][mm]);
      }      
      c3D->cd(nn+1);
      gr3D[nn]->SetTitle(Form("3DGraph Tracker%d",nn));
      gr3D[nn]->SetName(Form("3DGraph Tracker%d",nn));
      gr3D[nn]->Draw("p0 tri1");
    }
    c3D->Print("3DGraph.png");
    //   c3D->Close();    
  }

    void Set3DGraphSame(){
    TH3D *frame[4];
    TCanvas *c3DSame = new TCanvas("c3DSame","c3DSame",1600,1200);
    c3DSame->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      if(nn==3){ frame[nn] = new TH3D(Form("3DGraph%d",nn),"DUT",1,DUTXcenter-DUTbin/2,DUTXcenter+DUTbin/2,1,DUTYcenter-DUTbin/2,DUTYcenter+DUTbin/2,1,0,15);
      }else{     frame[nn] = new TH3D(Form("3DGraph%d",nn),Form("Tracker%d",nn),1,Xcenter-bin/2,Xcenter+bin/2,1,Ycenter-bin/2,Ycenter+bin/2,1,0,15); }
      gr3D[nn] = new TGraph2D;
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	gr3D[nn]->SetPoint(mm,hitPixelX[nn][mm],hitPixelY[nn][mm],hitPixelEnergy[nn][mm]);
      }      
      c3DSame->cd(nn+1);
      frame[nn]->Draw();
      frame[nn]->SetStats(0);
      gr3D[nn]->SetTitle(Form("3DGraph Tracker%d",nn));
      gr3D[nn]->SetName(Form("3DGraph Tracker%d",nn));
      gr3D[nn]->Draw("p0 tri1 Same");
    }
    c3DSame->Print("3DGraphSame.png");
    //    c3DSame->Close();    
  }


    //////////////////////////////// 3D Slice  ////////////////////////////////
  void Set3DSlice(){
    TCanvas *c3DSliceX = new TCanvas("c3DSliceX","c3DSliceX",1600,1200);
    c3DSliceX->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      if(nn==3){ h_x[nn] = new TH2D(Form("3DXTracker%d",nn),"DUT",DUTbin,DUTXcenter-DUTbin/2,DUTXcenter+DUTbin/2,100,0,15);
      }else{     h_x[nn] = new TH2D(Form("3DXTracker%d",nn),Form("Tracker%d",nn),bin,Xcenter-bin/2,Xcenter+bin/2,100,0,2);}
      //      for(int mm=0;mm<Entry.size();mm++){
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	h_x[nn]->Fill(hitPixelX[nn][mm],hitPixelEnergy[nn][mm]);
	//	if(ID[mm]==nn) h[nn]->Fill(X[mm],Y[mm]);
      } // mm
      c3DSliceX->cd(nn+1);
      h_x[nn]->SetXTitle("X axix [um]");
      h_x[nn]->SetYTitle("Energy [kev]");
      h_x[nn]->SetMarkerSize(1);
      h_x[nn]->SetMarkerStyle(21);
      h_x[nn]->Draw("BOX");
    }
    c3DSliceX->Print("2DhistX.png");		

    TCanvas *c3DSliceY = new TCanvas("c3DSliceY","c3DSliceY",1600,1200);
    c3DSliceY->Divide(2,2);
    for(int nn=0;nn<4;nn++){
      if(nn==3){ h_y[nn] = new TH2D(Form("3DYTracker%d",nn),"DUT",DUTbin,DUTYcenter-DUTbin/2,DUTYcenter+DUTbin/2,100,0,15);
      }else{     h_y[nn] = new TH2D(Form("3DYTracker%d",nn),Form("Tracker%d",nn),bin,Ycenter-bin/2,Ycenter+bin/2,100,0,2);}
      //      for(int mm=0;mm<Entry.size();mm++){
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	h_y[nn]->Fill(hitPixelY[nn][mm],hitPixelEnergy[nn][mm]);
	//	if(ID[mm]==nn) h[nn]->Fill(X[mm],Y[mm]);
      } // mm
      c3DSliceY->cd(nn+1);
      h_y[nn]->SetXTitle("Y axix [um]");
      h_y[nn]->SetYTitle("Energy [kev]");
      h_y[nn]->SetMarkerSize(1);
      h_y[nn]->SetMarkerStyle(21);
      h_y[nn]->Draw("BOX");
    }
    c3DSliceY->Print("2DhistY.png");		
  }

  //////////////////////////////// Prohection  ////////////////////////////////
  void SetProjectionX(){
    TCanvas * c_prX = new TCanvas("c_prX","c_prX",1000,1000);
    h_prX = h[0]->ProjectionX("htest_banX",0,bin);
    h_prX->Fit("gaus");
    h_prX->Draw();
  }

  //////////////////////////////// Root File  ////////////////////////////////
  void SetRootFile(){
    TFile * file =  new TFile("Analysisfile.root","RECREATE");  
    
    for(int nn=0;nn<4;nn++){      
      h[nn]->Write();
      gr3D[nn]->Write();
    }
    file->Close();
  }
  
};
