#ifndef __iamauniqueid_h__
#define __iamauniqueid_h__

#define MAXID 9
#include<cstdio>
#include <stdio.h> 
#include<map>

#include <TTree.h>
#include <TChain.h>
#include <TFile.h>

#include <GCutG.h> 
#include <TFSU.h>
#include <TFSUHit.h>
#include <TChannel.h> 

extern int    ndet;          //Number of Detectors fired
extern double dE;            //Delta E detector energy
extern double E;             //E detector energy 
 
extern int    Detid[MAXID];  //The Detector ID 
extern double Time[MAXID];   //The Timing of each det. 
extern double Theta[MAXID];  //The Angle of each det. 
extern double Energy[MAXID]; //The energy of each det.

extern TFSU* gfsu;

extern GCutG* PID; 
extern GCutG* pg_timing; 

struct HIT {
  
  HIT() {
    dE     = 0.0; 
    E      = 0.0; 

    Detid  = 0; 
    Time   = 0.0; 
    Theta  = 0.0; 
    Energy = 0.0; 
    Highest_energy = 0.0;  
  }
  
  double dE; 
  double E; 

  int    Detid;  //The Detector ID 
  double Time;   //The Timing of each det. 
  double Theta;  //The Angle of each det. 
  double Energy; //The energy of each det. 
  double Highest_energy; //only for clover

};





#endif 
