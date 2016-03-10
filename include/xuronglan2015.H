/******************************************************************************
 * This is class XURONGLAN2015. It implemnents the plasmasphere model         *
 * developed by Xu Ronglan for ChangE-3 EUV image simulation.                 *
 ******************************************************************************/

#ifndef _XURONGLAN2015_H_
#define _XURONGLAN2015_H_

#include <math.h>

#include <ecclesandking1969.H>
#include <rpiozhogin2012.H>

class XURONGLAN2015{
public:
  XURONGLAN2015();
  ~XURONGLAN2015();
  double getDensity(double L, double mlat);
  double getDensity(double rho, double z);
private:
  ECCLESANDKING1969 f2;
  RPIOZHOGIN2012 ozhogin;
  double rIBottom;
  double rF2Bottom;
  double rF2Top;
  double rOzhoginBottom;
};


#endif

