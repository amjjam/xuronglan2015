/******************************************************************************
 * Test program. Computes density in rho 0 to 15 and z -15 to 15 in 0.1 Re    *
 * steps and writes the results to a file.                                    *
 ******************************************************************************/

#include <stdio.h>
#include "../../include/xuronglan2015.H"

int main(int argc, char *argv[]){
  XURONGLAN2015 model;
  
  int iRho,nRho=1501,iZ,nZ=1501;
  double rho,rho0=0,dRho=0.01,z,z0=-7.5,dZ=0.01;
  double density;
  
  FILE *fp=fopen("/tmp/test.dat","w");
  fwrite(&nRho,sizeof(int),1,fp);
  fwrite(&nZ,sizeof(int),1,fp);
  
  for(iRho=0;iRho<nRho;iRho++){
    rho=rho0+dRho*iRho;
    fwrite(&rho,sizeof(double),1,fp);
  }
  
  for(iZ=0;iZ<nZ;iZ++){
    z=z0+dZ*iZ;
    fwrite(&z,sizeof(double),1,fp);
  }
  
  for(iRho=0;iRho<nRho;iRho++){
    rho=rho0+dRho*iRho;
    for(iZ=0;iZ<nZ;iZ++){
      z=z0+dZ*iZ;
      density=model.getDensityRhoZ(rho,z);
      fwrite(&density,sizeof(double),1,fp);
      //      printf("%10.3f %10.3f %10.3f\n",rho,z,density);
    }  
  }
  
  fclose(fp);
  
  return 0;
}
