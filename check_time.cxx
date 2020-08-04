#include "global.h"

#include<TFile.h>

#include<GCutG.h> 


int check_time(double dE_time, double gtime, double gEnergy){
  
  
  
  double dt = dE_time - gtime; 
  
  
  if(pg_timing->IsInside(dt,gEnergy)) {
    return 1; 
  }
  if(bg_timing->IsInside(dt,gEnergy)) {
    return 2; 
  }


  return 0; 
}   

