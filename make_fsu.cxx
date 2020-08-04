#include "global.h"
#include <stdio.h>
#include <cstdio>

#include <TGRUTUtilities.h>

TChain* input(const char* iname);  


TTree* output(const char* oname);

bool check_pid(double dE_energy, double E_energy);

int check_time(double dE_time, double gtime, double gEnergy);

std::vector<HIT> process_hits(std::vector<std::pair<TFSUHit,int> > array, double dEtime, double dEEnergy, double EEnergy);

void fill_tree(std::vector<HIT> array, TTree* t);

void save_output(TTree* t); 


int main(int argc, char* argv[]) {

  TChain* chain = input(argv[1]);

  //allows us to create the file name here. 
  std::string run_number = get_run_number(argv[1]);   
  
  std::string o_file_name = PID->GetName();

  o_file_name.append(run_number);

  o_file_name.append(".root");  
    
  TTree* tree = output(o_file_name.c_str()); //std::string into a const char*  
  
  long x = 0; 
  long ne = chain->GetEntries(); 

  
  for(x = 0; x < ne; x++){
    chain->GetEntry(x); 
    if((x%10000) ==0) { 
      printf("   %lu / %lu                  \r", x, ne);
      fflush(stdout); //force it to print. 
    }
    if(check_pid(gfsu->GetDeltaE().GetEnergy(), gfsu->GetE().GetEnergy()) == false) {continue;}
    
   // std::vector<TFSUHit> vect; 
    std::vector<std::pair<TFSUHit,int> > vect;
    
    for(size_t h = 0; h < gfsu->Size();h++){
      TFSUHit hit1 = gfsu->GetFSUHit(h); 
      //why did this print as an unassigned/ uninitialized number. ??
     //  printf("\t I am here %f \n",(float)gfsu->GetDeltaE().GetTime());


      int check = check_time(gfsu->GetDeltaE().GetTime(),hit1.GetTime(),hit1.GetEnergy());
      if(check == 0) {continue;}




//      vect.push_back(TFSUHit(hit1));
      vect.push_back(std::make_pair(TFSUHit(hit1),check));

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






