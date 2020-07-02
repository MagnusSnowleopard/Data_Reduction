#include <vector>
#include <TTree.h>
#include "global.h"
void fill_tree(std::vector<HIT> phit, TTree* t){
  ndet = phit.size(); 
  if(ndet > 9) {printf("\tVERY VERY BAD WORRY\n");
                return;}
  for(int e = 0; e < ndet; e++) {

    Detid[e]  = phit.at(e).Detid;
    Time[e]   = phit.at(e).Time;
    Theta[e]  = phit.at(e).Theta;
    Energy[e] = phit.at(e).Energy;

  }   
  t->Fill();
  
  return; 
}
