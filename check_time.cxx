#include "global.h"

#include<TFile.h>

#include<GCutG.h> 


bool check_time(double dE_time, double gtime, double gEnergy){
  
  bool a_boolean_value; 
  
// TFile* c = new TFile("/home/derosa/workspace/derosa_cuts.cuts");  
//  pg_timing = (GCutG*)c->Get("pg_timing");

  double dt = dE_time - gtime; 
  
  
  if(!pg_timing->IsInside(dt, gEnergy)) {a_boolean_value = false;}
  else{a_boolean_value = true;}
  


  return a_boolean_value; 
}   

