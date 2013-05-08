//Betfair Historical Data Analysis V1.0
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "DataEntry.h"
//ROOT includes:
// #include <TFile.h>
// #include <TTree.h>


int main(int argc, char **argv)
{
  
  //make a ROOT file
  TFile* p_rootFile = new TFile("output.root", "RECREATE");
  
  
  std::cout << "Betfair Historical Data Analysis." << std::endl;
  std::cout << "Reading in data files in list.txt..." << std::endl;
  
  
  //Open Data Files
  std::ifstream* myFile = new std::ifstream; 
  myFile->open("/home/Joseph/Work/BetfairAnalysis/Data/2012/bfinf_horse_111226to120101_120104120936.csv", std::ios::in);
   
  //read in 1st line of data file, containing column headings.
  std::string firstLine;
  if(myFile->is_open())
  {
    if( myFile->good())
    {
      getline(*myFile,firstLine,'\n');
 
      //Get the Field titles (check the order has not changed over time)
      char* pch;
      char* dup = strdup(firstLine.c_str());
    
      pch = strtok(dup, ",\"");

      while (pch != NULL)
      {
	//std::printf ("%s\n",pch);
	pch = strtok(NULL, ",\"");
      }
    }    
  }
       
  
  //create a vector of DataEntry objects.
  std::vector<DataEntry* >* p_allData = new std::vector<DataEntry* >;
  
  //For each of the data entries create a DataEntry object. put these in vector
  std::string line;
  if(myFile->is_open())
  {
    int n = 0;      
      
    while( myFile->good() /*&& (n<10000)*/)
    {

      getline(*myFile,line,'\n');
      
      DataEntry* thisEntry = new DataEntry(line);    
      //Only want to store GB win or Place
      if(thisEntry->Keep())
      {
	 p_allData->push_back(thisEntry);	 
      }     
     // thisEntry->print();
      n++;
  
    }    
    myFile->close();  
  }
  
//   //Filter GB races
//   std::vector<DataEntry* >* p_gbData = new std::vector<DataEntry* >;
//   for(uint i = 0; i<p_allData->size(); i++)
//   {
//     if(p_allData->at(i)->getCountry() == "GB")
//     {
//      // p_allData->at(i)->print();
//       p_gbData->push_back(p_allData->at(i));
//     }
//   }
    
    
  //Create ROOT TTrees
  TTree *tree = new TTree("Tree","An example of a ROOT tree"); 

  //set branches
  //test win or not
  bool winFlag;
  double firstTaken;
  double lastTaken;
  double volumeMatched;
  double nBets;
  double odds;
  double actualOff;
  double selectionId;
  double eventId;
  
  tree->Branch("winFlag", &winFlag);
  tree->Branch("firstTaken", &firstTaken);
  tree->Branch("lastTaken", &lastTaken);
  tree->Branch("volumeMatched", &volumeMatched);
  tree->Branch("nBets", &nBets);
  tree->Branch("actualOff", &actualOff );
  tree->Branch("selectionId", &selectionId);
  tree->Branch("eventId", &eventId);
  tree->Branch("odds", &odds );  
  
  //fill the tree
  for(uint i = 0; i < p_allData->size(); i++)
  { 
    winFlag = p_allData->at(i)->getWinFlag();
    firstTaken = p_allData->at(i)->getFirstTaken();
    lastTaken = p_allData->at(i)->getLastTaken();
    volumeMatched = p_allData->at(i)->getVolumeMatched();
    nBets = p_allData->at(i)->getNumberBets();
    actualOff = p_allData->at(i)->getActualOff();
    selectionId = p_allData->at(i)->getSelectionId();
    odds = p_allData->at(i)->getOdds();
    eventId = p_allData->at(i)->getEventId();
    tree->Fill();
       
  }
    
  //s tree->Write();   
  p_rootFile->WriteObject(tree,tree->GetName(),tree->GetName());
  p_rootFile->Close();
    
  return 0;
}



