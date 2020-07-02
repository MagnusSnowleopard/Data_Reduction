#include "global.h"
#include <stdlib.h>

#include <TChannel.h>

#include <TFSU.h>
#include <GCutG.h> 

TFSU* gfsu =0;

GCutG* PID = 0; 
GCutG* pg_timing = 0; 

TChain* input(const char* iname) { 
  TChain* chain = new TChain("EventTree");
  //chain gets set to the branch address of fsu (TFSU*). 
  chain->Add(iname); //adding the data to the chain. 
  
  chain->SetBranchAddress("TFSU", &gfsu); 


  TChannel::ReadCalFile("fsu.cal");
  TFile* cut = new TFile("/home/derosa/workspace/derosa_cuts.cuts");
  PID = (GCutG*)cut->Get("all_particle");
  pg_timing = (GCutG*)cut->Get("pg_time"); 


  if(!PID || !pg_timing){ printf("YELLING\n");
                          exit(0); } 
  
  
  return chain; 
}
