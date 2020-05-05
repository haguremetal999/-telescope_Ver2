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
  void setPositionYx(double y, double x);
  double getChargeShareYx(int iy, int ix){  return w[iy+1][ix+1]/wsum; };
  void  printShareYx(double y, double x);
};

#endif

