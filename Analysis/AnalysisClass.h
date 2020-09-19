class AnalysisClass{
 private :
  int ClassID;
  std::vector<double> testDataX;
  std::vector<double> testDataY;
  TF1 * f0X;
  TF1 * f0Y;
  TGraphErrors * g0X;
  TGraphErrors * g0Y; 
  double gradX;
  double gradY;

 public:  
  AnalysisClass(){}  
  AnalysisClass(int ID){
    ClassID = ID;
  }
  ~AnalysisClass(){}

  int GetID(){ return ClassID; }
  std::vector<double> GetTestDataX(){ return testDataX; }
  std::vector<double> GetTestDataY(){ return testDataY; }
  TGraphErrors * GetGraph0X(){ return g0X; }
  TGraphErrors * GetGraph0Y(){ return g0Y; }
  double GetGradX(){ return gradX; }
  double GetGradY(){ return gradY; }

  void SetUp(int ID){
    ClassID = ID;
    testDataX.push_back(500.0);
    testDataY.push_back(500.0);
  }
  void SetID( int ID ){ ClassID=ID; }
  void SetTestDataX(int data){ testDataX.push_back(data); }
  void SetTestDataY(int data){ testDataY.push_back(data); }
  void SetHist0X(){
    std::vector<double> testError;
    double z[4];
    double zError[4];
    for(int ii=0;ii<4;ii++){
      testError.push_back(1.0);
      z[ii]=30.0*1000*ii;
      zError[ii]=0;
    }
    f0X = new TF1(Form("f0X%d",ClassID),"pol1");    
    g0X = new TGraphErrors(4,z,&testDataX[0],zError,&testError[0]);
    g0X->SetMarkerStyle(22);
    g0X->SetMarkerSize(2);
    g0X->Fit(f0X,"0 Q","",0,90000);
    gradX = f0X->GetParameter(1);
  }
  void SetHist0Y(){
    std::vector<double> testError;
    double z[4];
    double zError[4];
    for(int ii=0;ii<4;ii++){
      testError.push_back(1.0);
      z[ii]=30.0*1000*ii;
      zError[ii]=0;
    }
    f0Y = new TF1(Form("f0Y%d",ClassID),"pol1");    
    g0Y = new TGraphErrors(4,z,&testDataY[0],zError,&testError[0]);
    g0Y->SetMarkerStyle(22);
    g0Y->SetMarkerSize(2);
    g0Y->Fit(f0Y,"0 Q","",0,90000);
    gradY = f0Y->GetParameter(1);
  }

  
};
