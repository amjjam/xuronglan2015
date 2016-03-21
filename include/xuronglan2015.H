/******************************************************************************
 * This is class XURONGLAN2015. It implemnents the plasmasphere model         *
 * developed by Xu Ronglan for ChangE-3 EUV image simulation.                 *
 ******************************************************************************/

#ifndef _XURONGLAN2015_H_
#define _XURONGLAN2015_H_

#include <math.h>

#include "../submodules/ecclesandking1969/include/ecclesandking1969.H"
#include "../submodules/rpiozhogin2012/include/rpiozhogin2012.H"

class XURONGLAN2015{
public:
  XURONGLAN2015(bool ionosphere=true);
  ~XURONGLAN2015();
  void setEandK1969Params(double A, double B);
  double getDensityRhoZ(double rho, double z);
  double getDensityLMlat(double L, double mlat);
private:
  ECCLESANDKING1969 f2;
  RPIOZHOGIN2012 ozhogin;
  bool ionosphere;
  double rIBottom;
  double rF2Bottom;
  double rF2Top;
  double rOzhoginBottom;
  double epsilon;
};


#endif

