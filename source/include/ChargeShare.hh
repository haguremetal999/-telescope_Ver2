#ifndef CHARGESHAREHH
#define CHARGESHAREHH

class ChargeShare {
 private: 
  int NN; // Number of neighbors;
  int NY;  
  int NX;
  double wy; 
  double wx;
  double wsum;
  double **syx;
  double **w;
  //  double w[Neighbors*2+1][Neighbors*2+1];
  double sig;
  double leak;
public:
  ChargeShare(double , double , double, double, int , int, int);
  ~ChargeShare(){;};
  void setPosition0Yx(double , double );
  void setPositionYx(double , double );
  void setShareParam(double Cs) {sig=Cs; };
  void  printShareYx(double , double ) ;
  int GetNeighbors() const {return NN;};   // Number of neighbors (calculated in the program)
  double getChargeShareYx(int iy, int ix) const {  return w[iy+NN][ix+NN]/wsum; };
};

#endif

