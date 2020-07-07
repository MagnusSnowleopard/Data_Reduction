#include<TTree.h>

#include<TFile.h>

void save_output(TTree* t){
  TFile* file = t->GetCurrentFile(); 
  
  file->cd();
  printf("\t |----------------------| \n");  
  printf("\t |  Reduction complete  |\n");
  printf("\t |                      |\n");  
  printf("\t | Writing the tree now |\n");  
  printf("\t |----------------------|\n");  
  t->Write(); 
  
  file->Close(); 

  return; 
}
