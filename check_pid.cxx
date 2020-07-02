#include "global.h"
#include <TFile.h>
#include <GCutG.h>

bool check_pid(double dE_energy, double E_energy){
  bool A_boolean_value; 

//  TFile* cut = new TFile("/home/derosa/workspace/derosa_cuts.cuts");
//  PID = (GCutG*)cut->Get("PID");


  if(!PID->IsInside(E_energy,dE_energy)){A_boolean_value = false;} 
  else {A_boolean_value = true;} 

  return A_boolean_value; 
}
// If its not inside the pid, it will return false and will continue in the main code, otherwise it will return true and its a good hit. 




