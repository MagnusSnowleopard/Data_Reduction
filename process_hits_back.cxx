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





std::vector<HIT> process_hits(std::vector<TFSUHit> array){
  std::vector<HIT> ghit (array.size()); 
  initmap(); 
  std::map<int,double> add_energy; 
  std::map<int,double>::iterator it; 

  int CLVID = 0; 
  int NCLV  = 0; 

  long x = 0; 
  long y = 0;
  
  printf("\t if crystal_num = 42 = G25\n");
  printf("\t then gmap returns = %i\n",gmap[G25] );
  printf("\t which belongs to det# = %i\n", get_id(gmap[G25])); 

  
  for(x = 0; x<array.size(); x++) {
    TFSUHit hit1 = array.at(x); 

    if(get_id(gmap[hit1.GetNumber()])<7){
      CLVID = get_id(gmap[hit1.GetNumber()]);  //det 6<
    }

    if(get_id(gmap[hit1.GetNumber()])>6){
      NCLV = get_id(gmap[hit1.GetNumber()]);        // det 7,8,9   
    }

    //Then all the crystal hits with the same id will be summed: 
    add_energy[CLVID] += hit1.GetEnergy();

      
    
   
  
    printf("\t the size of array is %i\n", array.size());
 
    for(int j = 0;j<CLVID;j++){
      ghit.at(j).Detid = CLVID;  //Clovers 1 - 6

    }
    for(int n = 6;n<NCLV;n++){
      ghit.at(n).Detid = NCLV;  //FSU7 and SB1&2
    }    

    for(y = x +1 ; y<array.size();y++) {
      TFSUHit hit2 = array.at(y);
      if(get_id(gmap[hit1.GetNumber()]) == get_id(gmap[hit2.GetNumber()]) ){
        double gt = 0.0; 
        TVector3 position; 
        if(hit1.GetEnergy() < hit2.GetEnergy())
        {
          gt = hit2.GetTime();
          position = hit2.GetPosition(); 
        }
        else 
        {
          gt = hit1.GetTime();
          position = hit1.GetPosition();
        }

        ghit.at(CLVID).Time = gt ;    

        printf("\t the size of ghit.at(CLVID).Time is %i\n", ghit.at(CLVID).Time);
        
        ghit.at(NCLV).Time = hit1.GetTime();

        Double_t angle = position.Theta();
        ghit.at(CLVID).Theta = angle;
        TVector3 rpos; 
        rpos = hit1.GetPosition();
        Double_t rangle = rpos.Theta();
        ghit.at(NCLV).Theta = rangle; 
      }
    }
    for(it = add_energy.begin();it!=add_energy.end();it++) {
      if(it->first < 0){continue;}

      if(it->first > 0){
        ghit.at(it->first).Energy = it->second;

      }
    }
    for(int r = 7; r<=NCLV; r++){
      ghit.at(r).Energy = array.at(x).GetEnergy();
    }
  }   
  printf("\t the size of ghit is : %i\n", ghit.size());
  return ghit; 
}
