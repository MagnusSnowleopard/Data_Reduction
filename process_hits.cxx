#include<map> 
#include<cstdio>
#include"global.h"

#include <TVector3.h> 

#include<TFSU.h> 
#include<TFSUHit.h> 



#define G1 1
#define G2 2
#define G3 3
#define G4 4
#define G5 9
#define G6 10
#define G7 11
#define G8 12
#define G9 17
#define G10 18
#define G11 19
#define G12 20
#define G13 23
#define G14 25
#define G15 26
#define G16 27
#define G17 28
#define G18 33
#define G19 34
#define G20 35
#define G21 36
#define G22 39
#define G23 40
#define G24 41 
#define G25 42
#define G26 43
#define G27 44
std::map<int,int> gmap;


void initmap(){
  gmap[G1]= 1;
  gmap[G2]= 2;
  gmap[G3]= 3;
  gmap[G4]= 4;
  gmap[G5]= 5;
  gmap[G6]= 6;
  gmap[G7]= 7;
  gmap[G8]= 8;
  gmap[G9]= 9;
  gmap[G10]= 10;
  gmap[G11]= 11;
  gmap[G12]= 12;
  gmap[G13]= 13;//not clover 
  gmap[G14]= 14;
  gmap[G15]= 15;
  gmap[G16]= 16;
  gmap[G17]= 17;
  gmap[G18]= 18;
  gmap[G19]= 19;
  gmap[G20]= 20;
  gmap[G21]= 21;
  gmap[G22]= 22;//not clover
  gmap[G23]= 23;//not clover
  gmap[G24]= 24;
  gmap[G25]= 25;
  gmap[G26]= 26;
  gmap[G27]= 27;
  //Using this map, we exclude white-spaces in det num. 
  return;
}

int get_id(int mapped_num) {
  int junk = -1;
  switch(mapped_num){

    case 1 ... 4:
      junk = 1;
      break; 
    case 5 ... 8:
      junk = 2;
      break; 
    case 9 ... 12:
      junk = 3;
      break; 
    case 13: 
      junk = 7;
      break; 
    case 14 ... 17:
      junk = 4; 
      break; 
    case 18 ... 21:
      junk = 5; 
      break; 
    case 22: 
      junk = 8;
      break; 
    case 23: 
      junk = 9;
      break; 
    case 24 ... 27:
      junk = 6; 
      break; 
  }

  return junk;
}

void copy_hit(TFSUHit fhit, HIT* phit, int ID, double dE_time) {

  //for every det that needs addback, non zero initials 

  if (phit->Detid != 0) { 

    //addback energies; 
    phit->Energy += fhit.GetEnergy(); 

    if(fhit.GetEnergy() > phit->Highest_energy) {

      phit->Time   = dE_time - fhit.GetTime(); 
      phit->Theta  = fhit.GetPosition().Theta(); 
      phit->Highest_energy = fhit.GetEnergy(); 
    }

  }
  else {

    phit->Highest_energy = fhit.GetEnergy();  

    phit->Detid  = ID; 
    phit->Time   = dE_time - fhit.GetTime(); 
    phit->Theta  = fhit.GetPosition().Theta(); 
    phit->Energy = fhit.GetEnergy(); 
  }
  return; 
}





std::vector<HIT> process_hits(std::vector<TFSUHit> array, double dEtime){

  std::map<int,HIT> hit_map; //this maps a detector id to a HIT. 
  std::map<int,HIT>::iterator hit_map_it; 

  std::vector<HIT> hit_box; //contains 4 data types, allows us to pushback into ghit. 

  std::vector<HIT> ghit;   //dont reserve a size.  
  initmap(); //this is for the detector maps



  long x = 0; 
  //Loop over TFSUHits

  for(x = 0; x<array.size(); x++) {
    TFSUHit hit1 = array.at(x); 

    //Get the new Detector id. 
    int ID = get_id(gmap[hit1.GetNumber()]); //returns 1 - 9. 
    //std::cout << "ID = " << ID << std::endl; 

    HIT h; 
    if(hit_map.count(ID)) { h = hit_map[ID]; } 

    copy_hit(hit1, &h, ID, dEtime); 



    hit_map[ID] = h; 
  }   
  for(hit_map_it = hit_map.begin(); hit_map_it != hit_map.end();hit_map_it++) {
    //the iterator is a pointer to an element (first or second); 
    ghit.push_back(hit_map_it->second);   

  }       
  return ghit; 
}
