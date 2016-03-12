/******************************************************************************
 * This is class XURONGLAN2015. It implemnents the plasmasphere model         *
 * developed by Xu Ronglan for ChangE-3 EUV image simulation.                 *
 ******************************************************************************/

#include "../include/xuronglan2015.H"

/*=============================================================================
  XURONGLAN2015() - constructor
  ============================================================================*/
XURONGLAN2015::XURONGLAN2015(){
  double EarthRadius=6371.0;
  double hIBottom=0;
  double hF2=390;
  double tF2=160;
  double hF2Bottom=hF2-tF2/2;
  double hF2Top=hF2+tF2/2;
  
  rIBottom=(EarthRadius+hIBottom)/EarthRadius;
  rF2Bottom=(EarthRadius+hF2Bottom)/EarthRadius;
  rF2Top=(EarthRadius+hF2Top)/EarthRadius;
  rOzhoginBottom=1.5;
  
  epsilon=1e-5;
}


/*=============================================================================
  ~XURONGLAN2015() - destructor
  ============================================================================*/
XURONGLAN2015::~XURONGLAN2015(){
  
}


/*=============================================================================
  double getDensityRhoZ(double rho, double z) - return density in cm^{-3}
  for the position (rho,z) in Re in the cylindrical SM coordinate
  system.
  ============================================================================*/
double XURONGLAN2015::getDensityRhoZ(double rho, double z){
  if(rho<epsilon) return 0;
  double r=sqrt(rho*rho+z*z);
  double cosmlat=rho/r;
  if(cosmlat<epsilon) return 0;
  double mlat=acos(cosmlat)/M_PI*180;
  double L=r/cosmlat/cosmlat;
  
  return getDensityLMlat(L,mlat);
}


/*=============================================================================
  double getDensityLMlat(double L, double mlat) - return density in
  electrons per cm^-3
  
  double L - L-shell in Re
  double mlat - magnetic latitude in degrees
  ============================================================================*/
double XURONGLAN2015::getDensityLMlat(double L, double mlat){
  double cosmlat=cos(mlat/180*M_PI);
  double r=L*cosmlat*cosmlat;
  double rho;
  
  // Now select model region dependeng on radial distance
  if(r<rIBottom){ // Inside Earth
    rho=0;
  }
  else if(r<rF2Bottom){ // Linear increase from bottom of ionosphere
			// to bottom of F2 peak region
    double rhoF2=f2.getDensity(mlat);
    rho=rhoF2/(rF2Bottom-rIBottom)*(r-rIBottom);
  }
  else if(r<rF2Top){ // Constant in F2 peak region
    rho=f2.getDensity(mlat);
  }
  else if(r<rOzhoginBottom){ // Exponential drop from top of F2 peak
			     // region to bottom of Ozhogin model
    // First find the parameter A and h of a model Ae^{-r/h} which
    // goes from F2 peak to bottom side of the Ozhogin model
    double rhoF2=f2.getDensity(mlat);
    double LOzhoginBottom=rOzhoginBottom/cosmlat/cosmlat;
    double rhoOB=ozhogin.getDensity(LOzhoginBottom,mlat);
    double h=(rOzhoginBottom-rF2Top)/log(rhoF2/rhoOB);
    double A=exp(log(rhoF2)+rF2Top/h);
    rho=A*exp(-r/h);
  }
  else{ // Ozhogin model
    rho=ozhogin.getDensity(L,mlat);
  }
  
  return rho;
}
