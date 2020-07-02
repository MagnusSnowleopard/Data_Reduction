#include <TTree.h>
#include <TFile.h>
#include "global.h"



int    ndet;          //Number of Detectors fired
double dE;            //Delta E detector energy
double E;             //E detector energy 

int    Detid[MAXID];  //The Detector ID 
double Time[MAXID];   //The Timing of each det. 
double Theta[MAXID];  //The Angle of each det. 
double Energy[MAXID]; //The energy of each det.


 
TTree* output(const char* oname){
  TFile* file = new TFile(oname, "recreate");  
  TTree* tree = new TTree("tree", "Simple FSU Tree"); 
  


  tree->Branch("ndet",&ndet,"ndet/I");
//  tree->Branch("dE",&dE, "dE/D");
//  tree->Branch("E", &E, "E/D");

  tree->Branch("Detid", &Detid, "Detid[ndet]/I");
  tree->Branch("Time",&Time, "Time[ndet]/D");
  tree->Branch("Theta", &Theta, "Theta[ndet]/D");
  tree->Branch("Energy", &Energy, "Energy[ndet]/D");

  return tree; 
}
