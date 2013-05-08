//Classs Header for dataEntry
#ifndef DATAENTRY_H
#define DATAENTRY_H

#include <iomanip>
#include <cstring>
#include <iostream>
#include <sstream>  
#include <algorithm> 
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
  void ConvertTime(const std::string&) ;
  void ConvertFirstTaken(const std::string&);
  void ConvertLastTaken(const std::string&);

    
  //getter functions
  std::string getCountry(){return m_country;};
  bool getWinFlag(){return m_winFlag;};
  double getEvent(){return m_event;};
  double getOdds(){return m_odds;};
  double getNumberBets(){return m_numberBets;};
  double getVolumeMatched(){return m_volumeMatched;};
  double getSelectionId(){return m_selectionId;};
  double getFirstTaken(){return m_firstTaken;};
  double getLastTaken(){return m_lastTaken;};
  double getActualOff(){return m_actualOff;};
  double getEventId(){return m_eventId;};
  
private:
  
  int m_sportsId;
  double m_eventId;
  std::string m_settledDate;
  std::string m_country;
  std::string m_fullDescription;
  std::string m_course;
  std::string m_scheduledOff;
  double m_event;

  //date
  int m_day;
  int m_month;
  int m_year;
  int m_dayFirst;
  int m_monthFirst;
  int m_yearFirst;
  int m_dayLast;
  int m_monthLast;
  int m_yearLast;
  
  double m_hours;
  double m_minutes;
  double m_seconds;
  
  double m_hoursFirst;
  double m_minutesFirst;
  double m_secondsFirst;
  
  double m_hoursLast;
  double m_minutesLast;
  double m_secondsLast;  
  
  double m_actualOff;
  double m_lastTaken;
  double m_firstTaken;
  
  
  
  
  double m_selectionId;
  std::string m_selection;
  double m_odds;
  double m_numberBets;
  double m_volumeMatched;

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

};

#endif