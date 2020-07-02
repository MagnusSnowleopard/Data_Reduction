#include "global.h"


TChain* input(const char* iname);  
TTree* output(const char* oname);
bool check_pid(double dE_energy, double E_energy);
bool check_time(double dE_time, double gtime, double gEnergy);
std::vector<HIT> process_hits(std::vector<TFSUHit> array, double dEtime);
void fill_tree(std::vector<HIT> array, TTree* t);
void save_output(TTree* t); 


int main(int argc, char* argv[]) {

  TChain* chain = input(argv[1]);    
  TTree* tree = output("fsu_output.root"); 

  long x = 0; 
  long ne = chain->GetEntries(); 

  for(x = 0; x < ne; x++){
    chain->GetEntry(x); 
    if((x%5000) ==0) { 
      printf("   %lu / %lu                  \r", x, ne);
      fflush(stdout); //force it to print. 
    }
    if(check_pid(gfsu->GetDeltaE().GetEnergy(),
          gfsu->GetE().GetEnergy()) == false) {continue;}

    std::vector<TFSUHit> vect; 

    for(size_t h = 0; h < gfsu->Size();h++){
      TFSUHit hit1 = gfsu->GetFSUHit(h); 

      if(check_time(gfsu->GetDeltaE().GetTime(),
            hit1.GetTime(),
            hit1.GetEnergy()) == false) {continue;}

      vect.push_back(TFSUHit(hit1));


    }
    std::vector<HIT> phits = process_hits(vect,gfsu->GetDeltaE().GetTime());    
    if(phits.size() > 0){ 

    fill_tree(phits, tree);    
    }
  }  
  printf("   %lu / %lu                  \n", x , ne);
  save_output(tree); 

  return 0;
}






