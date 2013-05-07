//Classs Header for dataEntry
#ifndef DATAENTRY_H
#define DATAENTRY_H

#include <iomanip>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "TTree.h"
#include "TFile.h"


class DataEntry{
  
  
public:
  
  //Default Constructor and Destructor
  DataEntry(){};
  virtual ~DataEntry(){};
  
  DataEntry(std::string);
  
  void print();
  

  
  bool Keep();
  
  
  //convert string for date to a double
  double ConvertTime(std::string);
  
  //getter functions
  std::string getCountry(){return m_country;};
  bool getWinFlag(){return m_winFlag;};
  double getEvent(){return m_event;};
  double getOdds(){return m_odds;};
  double getNumberBets(){return m_numberBets;};
  double getVolumeMatched(){return m_volumeMatched;};
  int getSelectionId(){return m_selectionId;};
   
private:
  
  int m_sportsId;
  int m_eventId;
  std::string m_settledDate;
  std::string m_country;
  std::string m_fullDescription;
  std::string m_course;
  std::string m_scheduledOff;
  double m_event;
  std::string m_actualOff;
  double m_actualOff_d;

  int m_selectionId;
  std::string m_selection;
  double m_odds;
  double m_numberBets;
  double m_volumeMatched;
  std::string m_latestTaken;
  std::string m_firstTaken;
  bool m_winFlag;
  std::string m_inPlay;
 
  //test to see if it is a win or place market from full description.
  bool testForWin(std::string);
  bool testForPlace(std::string);
  bool testForWinOrPlace(std::string);

  bool m_isGB;
  bool m_isWin;
  bool m_isPlace;
  bool m_isWinOrPlace;

  
//   std::string m_sportsId;
//   std::string m_eventId;
//   std::string m_settledDate;
//   std::string m_country;
//   std::string m_fullDescription;
//   std::string m_course;
//   std::string m_scheduledOff;
//   std::string m_event;
//   std::string m_actualOff;
//   std::string m_selectionId;
//   std::string m_selection;
//   std::string m_odds;
//   std::string m_numberBets;
//   std::string m_volumeMatched;
//   std::string m_latestTaken;
//   std::string m_firstTaken;
//   std::string m_winFlag;
//   std::string m_inPlay;
};

#endif