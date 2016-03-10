/******************************************************************************
 * This is class XURONGLAN2015. It implemnents the plasmasphere model         *
 * developed by Xu Ronglan for ChangE-3 EUV image simulation.                 *
 ******************************************************************************/

#include "../include/xuronglan2015.H"

/*=============================================================================
  XURONGLAN2015() - constructor
  ============================================================================*/
XURGONGLAN2015::XURONGLAN2015(){
  double EarthRadius=6371.0;
  double hIBottom=0;
  double hF2=390;
  double tF2=160;
  double hF2Bottom=hF2-tF2/2;
  double hF2Top=hF2+tF2/2;

  double rIBottom=(EarthRadius+hIBottom)/EarthRadius;
  double rF2Bottom=(EarthRadius+hF2Bottom)/EarthRadius;
  double rF2Top=(EarthRadius+hF2Top)/EarthRadius;
  double rOzhoginBottom=1.5;

  double epsilon=1e-5;
}


/*=============================================================================
  ~XURONGLAN2015() - destructor
  ============================================================================*/
XURONGLAN2015::~XURONGLAN2015(){
  
}


/*=============================================================================
  double getDensity(double rho, double z) - return density in cm^{-3}
  for the position (rho,z) in Re in the cylindrical SM coordinate
  system.
  ============================================================================*/
double XURONGLAN::getDensity(double rho, double z){
  if(rho<epsilon) return 0;
  double r=sqrt(rho*rho+z*z);
  double cosmlat=r/rho;
  if(cosmlat<epsilon) return 0;
  double mlat=acos(cosmlat)/M_PI*180;
  double L=r/cosmlat/cosmlat;
  
  return getDensity(L,mlat);
}


/*=============================================================================
  double getDensity(double L, double mlat) - return density in
  electrons per cm^-3

  double L - L-shell in Re
  double mlat - magnetic latitude in degrees
  ============================================================================*/
double getDensity(double L, double mlat){
  double cosmlat=cos(mlat/180*M_PI);
  double r=L*cosmlat*cosmlat;
  doublr rho,rhoF2,rhoOB;
  
  // Now select model region dependeng on radial distance
  if(r<rIBottom){ // Inside Earth
    rho=0;
  }
  else if(r<rF2Bottom){ // Linear increase from bottom of ionosphere
			// to bottom of F2 peak region
    rhoF2=f2.getDensity(mlat);
    rho=rhoF2/(rF2Bottom-rIBottom)*(r-rIBottom)
  }
  else if(r<rF2Top){ // Constant in F2 peak region
    rho=f2.getDensity(mlat);
  }
  else if(r<rOzhoginBottom){ // Exponential drop from top of F2 peak
			     // region to bottom of Ozhogin model
    // First find the parameter A and h of a model Ae^{-r/h} which
    // goes from F2 peak to bottom side of the Ozhogin model
    rhoF2=f2.getDensity(mlat);
    LOzhoginBottom=rOzhoginBottom/cosmlat/cosmlat;
    rhoOB=ozhogin.getDensity(LOshoginBottom,mlat);
    h=(rOzhoginBottom-rF2Top)/log(rhoF2/rhoOB);
    A=log(rhoF2)+rF2Top/h;
    rho=A*exp(-r/h);
  }
  else{ // Ozhogin model
    rho=ozhogin.getDensity(L,mlat);
  }
  
  return rho;
}
