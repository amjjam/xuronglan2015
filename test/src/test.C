/******************************************************************************
 * Test program. Computes density in rho 0 to 15 and z -15 to 15 in 0.1 Re    *
 * steps and writes the results to a file.                                    *
 ******************************************************************************/

#include "../../include/xuronglan2015.H"

int main(int argc, char *argv[]){
  XURONGLAN model;
  
  int iRho,nRho=151,iZ,nZ=301;
  double rho,rhoMin=0,dRho=0.1,z,z0=-15,dZ=0.1;
  
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
      density=model.getDensity(rho,z);
      fwrite(&density,sizeof(double),1,fp);
    }  
  }
  
  fclose(fp);
  
  return 0;
}
