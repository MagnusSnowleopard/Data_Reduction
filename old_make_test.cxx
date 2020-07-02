#include<cstdio>
#include<map>

#include<TChain.h>
#include<TFile.h>
#include<TTree.h>
#include<TVector3.h>

#include<GCutG.h>
#include<TFSU.h>
#include<TChannel.h>


#define MAXID 9 

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

//Global stuff
GCutG* PID; 
GCutG* pg_timing; 


//Lets make a Detector_Map.
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
}

//change this to get id 
int get_id(int num) {
  int junk = -1;
  switch(num){

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




struct HIT { 
  int    Detid;  //The Detector ID 
  double Time;   //The Timing of each det. 
  double Theta;  //The Angle of each det. 
  double Energy; //The energy of each det. 
}; 



std::vector<TFSUHit> find_good_hits(TFSU* fsu){
  std::vector<TFSUHit> vect; 

  double dt = fsu->GetDeltaE().GetTime();

  for(int k = 0;k<fsu->Size();k++) {
    TFSUHit hit = fsu->GetFSUHit(k); 
    dt = dt - hit.GetTime(); 

    if(!pg_timing->IsInside(dt, hit.GetEnergy())){ continue; }
    vect.push_back(TFSUHit(hit)); //copy and a push back at the same time for our good hits.
  }

  return vect; 
} 


//This function transforms good_hits its going to return our defined structure khit type HIT.  
std::vector<HIT> transform_hits(std::vector<TFSUHit> good_hits){
  std::vector<HIT> khit; //good hits into khits 


  std::map<int,double> add_energy; //int det#, double summed energy. 
  std::map<int,double>::iterator it;
  int CLVID = 0; 
  int NCLV = 0; 

  long x = 0; 
  long y = 0; 
  //This loop is made to interate over good hits into khits. 
  for(x = 0; x < good_hits.size(); x++){
    TFSUHit hit1= good_hits.at(x); 
    //Mapping the clover id:
    if(get_id(gmap[hit1.GetNumber()])<7){
      CLVID = get_id(gmap[hit1.GetNumber()]);  //det 6<
    }

    if(get_id(gmap[hit1.GetNumber()])>6){
      NCLV = get_id(gmap[hit1.GetNumber()]);        // det 7,8,9   
    }

    //Then all the crystal hits with the same id will be summed:        
    add_energy[CLVID] += hit1.GetEnergy();

    for(int j = 1;j<=CLVID;j++){
      khit.at(j).Detid = CLVID;  //Clovers 1 - 6

    }
    for(int n = 7;n<=NCLV;n++){
      khit.at(n).Detid = NCLV;  //FSU7 and SB1&2
    }

    for(y = x +1 ; y<good_hits.size();y++) {
      TFSUHit hit2 = good_hits.at(y); 
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

        khit.at(CLVID).Time = gt ;    

        khit.at(NCLV).Time = hit1.GetTime(); 

        Double_t angle = position.Theta(); 
        khit.at(CLVID).Theta = angle;
        TVector3 rpos; 
        rpos = hit1.GetPosition(); 
        Double_t rangle = rpos.Theta();  
        khit.at(NCLV).Theta = rangle; 
      }
    }
    //Using the available information about the different energies of each hit, we need to take the highest energy deposition for each clover and return the position of that hit. 


    for(it = add_energy.begin();it!=add_energy.end();it++) {
      if(it->first < 0){continue;}

      if(it->first > 0){
        khit.at(it->first).Energy = it->second; 

      }
    }
    for(int r = 7; r<=NCLV; r++){
      khit.at(r).Energy = good_hits.at(x).GetEnergy(); 
    }


  }
  return khit;   
} 


int main(int argc, char* argv[]){

//Read input data file, setup tree/chain branches
// -------------------------------

  initmap();
  printf("I pass %i arguments\n", argc);  
  for (int i =0; i<argc; i++) {
    printf("\t argv[%i] = %s\n", i, argv[i]); 

  }
  TFile* c = new TFile("/home/derosa/workspace/derosa_cuts.cuts");
  PID = (GCutG*)c->Get("PID");  
  pg_timing = (GCutG*)c->Get("pg_timing");
  printf("\t it worked line : 250, cuts loaded\n"); 
  TChain* Chain = new TChain("EventTree"); 
  Chain->Add(argv[1]);
  TChannel::ReadCalFile("fsu.cal"); 

  printf("\t it worked line : 255, file added to chain\n"); 
  long nentries = Chain->GetEntries(); //how many rows are in the tree  
  long x = 0; 
  long y = 0; 
  TFSU* fsu = 0; 
  Chain->SetBranchAddress("TFSU", &fsu);
  
  printf("\t it worked until line : 262, chain set to fsu\n"); 
// -------------------------------
// Setup output data file and Tree
// -------------------------------

  int    ndet;          //Number of Detectors fired
  double dE;            //Delta E detector energy
  double E;             //E detector energy 

  int    Detid[MAXID];  //The Detector ID 
  double Time[MAXID];   //The Timing of each det. 
  double Theta[MAXID];  //The Angle of each det. 
  double Energy[MAXID]; //The energy of each det. 

  TFile* file = new TFile("FSU.root","recreate");

  TTree* tree = new TTree("tree", "Simple FSU Tree");

  tree->Branch("ndet",&ndet,"ndet/I");
  tree->Branch("dE",&dE, "dE/D"); 
  tree->Branch("E", &E, "E/D"); 

  tree->Branch("Detid", &Detid, "Detid[ndet]/I");
  tree->Branch("Time",&Time, "Time[ndet]/D"); 
  tree->Branch("Theta", &Theta, "Theta[ndet]/D");
  tree->Branch("Energy", &Energy, "Energy[ndet]/D");


  printf("\t it worked until line : 290, tree initialized and set\n"); 
// -------------------------------
//Loop over input file enties
// -------------------------------

  for(x = 0; x < 10; x++){
    // for(x = 0; x < nentries; x++)

    Chain->GetEntry(x); //getting the x entry out of the chain. 
    dE = fsu->GetDeltaE().GetEnergy(); 
    E = fsu->GetE().GetEnergy();

    //PID CUT CHECK HERE// 
    if(!PID->IsInside(E,dE)){continue; }

  printf("\t it worked until line : 305, got x entry, dE/E and pid check\n"); 
    //IF PID PASS, List of Detectors 
    //If not, just go to the next x or continue. 
    //loop over fsu hits, if they dont pass the timing cut, ignore them, 

    std::vector<TFSUHit> goodhits = find_good_hits(fsu); 

  printf("\t it worked until line : 312, find good hits worked, good hits vector set\n"); 
    //if they do pass, use the ones we want to look at for more detail. 
    //create a list that contains those 4 items, detid, time, theta,energy. 

    std::vector<HIT> phit = transform_hits(goodhits);  

  printf("\t it worked until line : 318, Transform hits function, phit set\n"); 
    ndet = phit.size(); //number of detectors fired. 

    for(int e = 0; e<ndet ;e++){

      Detid[e] = phit.at(e).Detid;  //The Detector ID 
      Time[e] = phit.at(e).Time;   //The Timing of each det. 
      Theta[e] = phit.at(e).Theta;  //The Angle of each det. 
      Energy[e] = phit.at(e).Energy; //The energy of each det. 

      //fill the transform hits function

    }  

    tree->Fill(); 
  } 
  tree->Write(); 
  file->Close();

  return 0; 

}
