// In this class, Tracker X/Y units are [pixel], and gradX/Y unit is [pixel/um]. Only difX/Y usees [um] unit.
//DUT X/Y unit is 1[px] = 1[um].
// Changing units from [pixel] to [um] is done in (MakeHist.h) file.
class LoopAnalysis{
 private :
  int ClassID;
  int Entry;
  int hitNumber[4];
  int lasthit[4];
  double X[200],Y[200],loss[200];
  int ID[200],IADR[200];
  double totalloss[4];
  double threshold[4];

  int counter[4];
  double meanX[4];
  double meanY[4];
  double shareEnergy[4];

  double gradX;
  double gradY;
  double pitch;
  double reX;
  double reY;
  double difX;
  double difY;
  double pixelsize;
  double pixelnumber; 
  
  std::vector<int> hitPixel[4];
  std::vector<double> hitPixelEnergy[4];
  std::vector<double> hitPixelX[4];
  std::vector<double> hitPixelY[4];

 public:
  
  LoopAnalysis(){
    pitch = 30.0*1000;
    pixelsize = 1.0;
  }  
  LoopAnalysis(int ID){
    ClassID = ID;
  }
  ~LoopAnalysis(){}

  //////////////////////////////// Getter  ////////////////////////////////
  int GetClassID(){ return ClassID; }
  double * GetX(){ return X; }
  double * GetY(){ return Y; }
  int * GetID(){ return ID; }
  double * GetLoss(){ return loss; }
  double * GetTotalLoss(){ return totalloss; }

  double * GetMeanX(){ return meanX; }
  double * GetMeanY(){ return meanY; }
  double * GetShareEnergy(){ return shareEnergy; }

  double GetReX(){ return reX; }
  double GetReY(){ return reY; }
  double GetDifX(){ return difX; }
  double GetDifY(){ return difY; }
  int * GetLastHit(){ return lasthit; }
  int * GetClusterSize(){ return counter; }

  //////////////////////////////// Setter  ////////////////////////////////
  void SetUp(int *IADRl, double *energylossl, int hitN,double PixelSize, int PixelNumber ){
    pixelnumber = PixelNumber;
    Entry = hitN;
    pixelsize = PixelSize;
    for(int mm=0;mm<Entry;mm++){
      //      if(IADRl[mm]==0) {IADRl[mm]=-1;}
      //      else {IADR[mm] = IADRl[mm];}
      IADR[mm] = IADRl[mm];
      ID[mm]    = IADRl[mm]/1000000;
      X[mm] = (IADRl[mm] - ID[mm]*1000000)/1000; 
      Y[mm] = (IADRl[mm] - ID[mm]*1000000 -X[mm]*1000);
      loss[mm] = energylossl[mm];
      //      std::cout << "["<< mm <<"] : (ID,X,Y,loss) = ( " << ID[mm] <<", "<< X[mm] << "," << Y[mm] <<", "<< loss[mm] <<")" << std::endl;
    }
    for(int nn=0;nn<4;nn++){
      hitNumber[nn]=0;      
    }
    for(int nn=0;nn<4;nn++){
      totalloss[nn] = 0;
      lasthit[nn] = 0;
      threshold[nn] = 0;
      if(nn==3)  threshold[nn] =0;
      //      std::cout << "==========================" << std::endl;
      for(int mm=0;mm<Entry;mm++){
	if(ID[mm]==nn){
	  hitNumber[nn]++;
	  lasthit[nn] = mm;
	  totalloss[nn] += loss[mm];
	}
	//	std::cout << "lasthit["<< mm << "] = " << hitNumber[nn]  << std::endl;
      } // mm
      //      std::cout << "totalloss[" << nn <<"] = "<< totalloss[nn] << std::endl;)
    } //nn
    //    if(lasthit[3]==0) std::cout << "==================No last hit!" << std::endl;
  }

  void SetThreshold(double threTr,double threDUT){
    for(int nn=0;nn<4;nn++){
      threshold[nn] = threTr;
      if(nn==3)  threshold[nn] =threDUT;
    }   
  }
  
  void SetPitch(double pitchlength){
    pitch = pitchlength;
  }
  
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
      //      std::cout << "==================================" << std::endl;
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	//	std::cout << "hitPixel      [" << nn << "][" << mm <<"] = " << hitPixel[nn][mm] << std::endl;
	//	std::cout << "hitPixelEnergy[" << nn << "][" << mm <<"] = " << hitPixelEnergy[nn][mm] << std::endl;
      }
    }
  }
  
  //////////////////////////////// Cluster  ////////////////////////////////
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
      meanX[nn]=0;
      meanY[nn]=0;
      counter[nn]=0;
      shareEnergy[nn]=0;
      for(int mm=0;mm<hitPixel[nn].size();mm++){

	if(hitPixelEnergy[nn][mm]>maxEnergy[nn]){
	  maxhitN[nn]=mm;
	  maxhitX[nn]=hitPixelX[nn][mm];
	  maxhitY[nn]=hitPixelY[nn][mm];
	  maxEnergy[nn]=hitPixelEnergy[nn][mm];
	}
	//	std::cout << "(X, Y, E) ["<< nn << "]["<< mm <<"] = "<< hitPixelX[nn][mm] << ", " << hitPixelY[nn][mm] << ", " << hitPixelEnergy[nn][mm]  <<std::endl;
      }
      //      std::cout << "================(N, maxX, maxY)[" << nn << "] = "<< maxhitN[nn] << ", " << maxhitX[nn] << ", " << maxhitY[nn] << std::endl;
    }

    for(int nn=0;nn<4;nn++){
      //      std::cout << "----------------- nn = " << nn  << std::endl;
      for(int mm=0;mm<hitPixel[nn].size();mm++){
	if( abs(hitPixelX[nn][mm]-maxhitX[nn])<NN+1 && abs(hitPixelY[nn][mm]-maxhitY[nn])<NN+1 && hitPixelEnergy[nn][mm]>threshold[nn]){
	  meanX[nn] += hitPixelX[nn][mm]*hitPixelEnergy[nn][mm];
	  meanY[nn] += hitPixelY[nn][mm]*hitPixelEnergy[nn][mm];
	  shareEnergy[nn] += hitPixelEnergy[nn][mm];
	  counter[nn]++;
	  //	  std::cout <<"["<< nn << "][" << mm << "] : "  << hitPixel[nn][mm] << std::endl;
	}
      }
      if(nn!=3){
	meanX[nn] = meanX[nn]/shareEnergy[nn] - (pixelnumber/2-0.5);  //[px]
	meanY[nn] = meanY[nn]/shareEnergy[nn] - (pixelnumber/2-0.5);  //[px]
	//	meanX[nn] *= pixelsize;
	//	meanY[nn] *= pixelsize;
      }else{
	meanX[nn] = meanX[nn]/shareEnergy[nn] - (1000/2-0.5);  //1[px]=1[um]
	meanY[nn] = meanY[nn]/shareEnergy[nn] - (1000/2-0.5);  //1[px]=1[um]
      }
      //      std::cout << "(meanX, meanY)["<< nn << "] = "<< meanX[nn] << ", " << meanY[nn] << std::endl;
      //      std::cout << counter[nn] << " is calculated! "  << std::endl;
    }
  }

  //////////////////////////////// Reconstruction  ////////////////////////////////
  void SetReconstruction(){
    //    TCanvas * ctmp = new TCanvas("tmpTCanvas","tmpTCanvas",1000,1000);
    //    ctmp->Divide(1,2);
    TGraphErrors *grX = new TGraphErrors;
    TGraphErrors *grY = new TGraphErrors;
    TF1 * f1X = new TF1("tmpTF1X","pol1");
    TF1 * f1Y = new TF1("tmpTF1Y","pol1");
    for(int nn=0;nn<3;nn++){
      grX->SetPoint(nn, pitch*nn+3.0*1000, meanX[nn]);  //[px]/[um]
      grX->SetPointError(nn, 0, 1.0);
      grY->SetPoint(nn, pitch*nn+3.0*1000, meanY[nn]);  //[px]/[um]
      grY->SetPointError(nn, 0, 1.0);
    }
    //    ctmp->cd(1);
    grX->Fit(f1X,"Q","",0,70000);
    grX->SetMarkerStyle(22);
    grX->SetMarkerSize(2);
    //    grX->Draw();
    //    ctmp->cd(2);
    grY->Fit(f1Y,"Q","",0,70000);
    grY->SetMarkerStyle(22);
    grY->SetMarkerSize(2);
    //    grY->Draw();
    
    //    gradX = (meanX[2]-meanX[0]) / (2*pitch);
    //    gradY = (meanY[2]-meanY[0]) / (2*pitch);
    gradX = f1X->GetParameter(1);  //  [px]/[um]
    gradY = f1Y->GetParameter(1);  //  [px]/[um]
    reX = meanX[2] + (30.0*1000*gradX); //  [px]
    reY = meanY[2] + (30.0*1000*gradY); //  [px]
    difX = meanX[3] - reX*pixelsize; // [um] 
    difY = meanY[3] - reY*pixelsize; // [um]
  }
  
};
