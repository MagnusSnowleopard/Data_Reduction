#include "global.h"
#include <stdio.h>
#include <cstdio>

TChain* input(const char* iname);  

TTree* output(const char* oname);

bool check_pid(double dE_energy, double E_energy);

bool check_time(double dE_time, double gtime, double gEnergy);

std::vector<HIT> process_hits(std::vector<TFSUHit> array, double dEtime, double dEEnergy, double EEnergy);

void fill_tree(std::vector<HIT> array, TTree* t);

void save_output(TTree* t); 


int main(int argc, char* argv[]) {

  TChain* chain = input(argv[1]);
/* 
  std::vector<char> run_o; 
  
  std::string run_i (argv[1]); 
  
  for(int k = 0; k < sizeof(run_i); k++){
    
    run_o.push_back(run_i[k]);   
  
  }
  
  for(int p = 0; p < sizeof(run_o); p++){ 

    // remove and replace things in run_o to make output file name here;
    std::cout << "\t the content of run_o is :" << run_o[p] <<std::endl; 
  }  
  std::cout <<"\t  run output size is : " << run_o.size() << std::endl; 
*/
  

  TTree* tree = output("run1277_s.root"); 
  
  long x = 0; 
  long ne = chain->GetEntries(); 

  
  for(x = 0; x < ne; x++){
    chain->GetEntry(x); 
    if((x%10000) ==0) { 
      printf("   %lu / %lu                  \r", x, ne);
      fflush(stdout); //force it to print. 
    }
    if(check_pid(gfsu->GetDeltaE().GetEnergy(), gfsu->GetE().GetEnergy()) == false) {continue;}

    std::vector<TFSUHit> vect; 

    for(size_t h = 0; h < gfsu->Size();h++){
      TFSUHit hit1 = gfsu->GetFSUHit(h); 

      if(check_time(gfsu->GetDeltaE().GetTime(),
            hit1.GetTime(),
            hit1.GetEnergy()) == false) {continue;}

      vect.push_back(TFSUHit(hit1));


    }
    std::vector<HIT> phits = process_hits(vect,gfsu->GetDeltaE().GetTime()
                                              ,gfsu->GetDeltaE().GetEnergy()
                                              ,gfsu->GetE().GetEnergy());    
    if(phits.size() > 0){ 
      fill_tree(phits, tree);    
    }
  }  
  printf("   %lu / %lu                  \n", x , ne);
  save_output(tree); 

  return 0;
}






