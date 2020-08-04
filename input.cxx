#include "global.h"
#include <stdlib.h>

#include <TChannel.h>

#include <TFSU.h>
#include <GCutG.h> 

TFSU* gfsu =0;

GCutG* PID = 0; 
GCutG* pg_timing = 0; 
GCutG* bg_timing = 0; 

TChain* input(const char* iname) { 
  TChain* chain = new TChain("EventTree");
  //chain gets set to the branch address of fsu (TFSU*). 
  chain->Add(iname); //adding the data to the chain. 
  
  chain->SetBranchAddress("TFSU", &gfsu); 


  TChannel::ReadCalFile("fsu.cal");
//   TFile* cut = new TFile("/home/derosa/notebooks/36S_14C_cuts.cuts");
//   PID = (GCutG*)cut->Get("Proton");
  //PID = (GCutG*)cut->Get("Tritium");
  //PID = (GCutG*)cut->Get("all_particle"); 
  
  TFile* cut1 = new TFile("/home/derosa/workspace/derosa_cuts.cuts");
   pg_timing = (GCutG*)cut1->Get("pg_time"); 
   bg_timing = (GCutG*)cut1->Get("bg_time"); 
  //pg_timing = (GCutG*)cut->Get("pg_time"); 
  //PID = (GCutG*)cut->Get("Proton");

  TFile* cut = new TFile("/home/oshea/sort_FSU/mycuts.cuts");
 // pg_timing = (GCutG*)cut->Get("dEg_timing"); 
  PID = (GCutG*)cut->Get("alpha_gate"); 

  if(!PID || !pg_timing){ printf("YELLING\n");
                          exit(0); } 
  
  
  return chain; 
}
