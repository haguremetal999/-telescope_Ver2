#ifndef CHARGESHAREHH
#define CHARGESHAREHH

class ChargeShare {
private: 
  int NY;
  int NX;
  double wy;
  double wx;
  double wsum;
  double **syx;
  double w[3][3];
  double sig;
  double leak;
public:
  ChargeShare(double , double , double, double, int, int);
  ~ChargeShare(){;};
  void setPositionYx(double , double );
  void setShareParam(double Cs) {sig=Cs; };
  double getChargeShareYx(int iy, int ix) const {  return w[iy+1][ix+1]/wsum; };
  void  printShareYx(double , double ) ;
};

#endif

