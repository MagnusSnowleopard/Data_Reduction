#include<TTree.h>

#include<TFile.h>

void save_output(TTree* t){
  TFile* file = t->GetCurrentFile(); 
  
  file->cd(); 
  printf("Writing the tree now");  
  t->Write(); 
  
  file->Close(); 

  return; 
}
