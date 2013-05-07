//Data Entry Class
#include "DataEntry.h"
#include <ios>

//Constructor for DataEntry
DataEntry::DataEntry(std::string dataString)
{
  //Take string corresponding to all data for this entry
  //Split the string up and set the member variables accordingly
   
  m_isGB = false;
  m_isWin = false;
  m_isPlace = false;
  m_isWinOrPlace = false;
  
  //always expect same fields in same order?!? if YES use an int to control which field is which;
  int index = 0;
  char* a;
  char* copy = strdup(dataString.c_str());
   
  a = strtok(copy, ",\"");     
  
  bool keepGoing = true;
  
  while ((a != NULL) && (keepGoing == true))
  {
  //std::printf ("%s\n",a);
    std::cout << "DEBUG 0."<<index<<", a = " << a << std::endl;       
    switch(index)
    { 
      case 0: //SPORTS_ID
        m_sportsId =  atoi(a);
        break;
	 
      case 1: //EVENT_ID
        m_eventId =  atoi(a);
        break;
	 
      case 2: //SETTLED_DATE
        m_settledDate = a;
        break;
	 
      case 3: //COUNTRY
        m_country = a;
	if(strcmp(a, "GB") == 0)
	{ 
	  std::cout << "Debug: FOUND GB!" << std::endl;
	  m_isGB = true;
	}
	else{
	  keepGoing = false;
	} 
	
        break;
	 
      case 4: //FULL_DESCRIPTION
        m_fullDescription = a;
	m_isWinOrPlace = testForWinOrPlace(a);
	if(!m_isWinOrPlace) keepGoing = false;	
        break;
	 
      case 5: //COURSE
        m_course = a;
        break;
	 
      case 6: //SCHEDULED_OFF
        m_scheduledOff = a;
        break;
	 
      case 7: //EVENT
        m_event = atof(a);
	m_isPlace = testForPlace(a);
	m_isWin = testForWin(a);//if it's not a PLACE it must be WIN (if WinOrPlace is true)
	//if(m_isPlace) {std::cout << "DEBUG: " << m_fullDescription << std::endl;}
        break;
	 
      case 8: //ACTUAL_OFF	
        m_actualOff = a;
	//convert the string to a double if GB win or place market
	
	m_actualOff_d = ConvertTime(a);
        break;
	 
      case 9: //SELECTION_ID
        m_selectionId = atoi(a);
        break;
	 
      case 10: //SELECTION
        m_selection = a;
	break;
	 
      case 11: //ODDS
        m_odds = atof(a);
	break;
	 
      case 12: //NUMBER_BETS
        m_numberBets = atof(a);
	break;
	 
      case 13: //VOLUME_MATCHED
        m_volumeMatched = atof(a);
	break;
	 
      case 14: //LATEST_TAKEN
        m_latestTaken = a;
	break;
	 
      case 15: //FIRST_TAKEN
        m_firstTaken = a;
	break;
	 
      case 16: //WIN_FLAG - Set to true if = 1, false if = 0
        m_winFlag = (atoi(a) == 1) ? (true) : (false);
	break;
	 
      case 17: //IN_PLAY
        m_inPlay = a;
	break;	 
	 
      default:
	std::cout << " Error in Splitting string into data fields!" << std::endl; 
	break;
    }
     
    a = strtok(NULL, ",\""); 
    index++;       
  }    

}

double DataEntry::ConvertTime(std::string timeString){
  
  char* a;
  std::cout << "Debug: ConvertTime timeString (input) =  " << timeString << std::endl;
  char* copy = strdup(timeString.c_str());
   
  a = strtok(copy, " ");
  std::cout << "Debug: ConvertTime a = " <<  a << std::endl;
  
  return atof(a);
  
  
}


bool DataEntry::testForPlace(std::string testString){
  
  bool isPlace = false;
  if(testString == "TO BE PLACED") isPlace = true;
  
  //Debug:
  std::cout << "Found place market " << std::endl;

  return isPlace;
  
}

bool DataEntry::testForWin(std::string testString){
  
  bool isWin = false;
  if(!m_isPlace) isWin = true;
  return isWin;
   
}

//Test if an entry relates to a win or place marke by looking at the number of
// forward-slashes in the full description, win or place markets only have 1, match bets/AvsB have > 1.
bool DataEntry::testForWinOrPlace(std::string testString)
{
  
  bool isWinOrPlace = false;
  int nSlash = 0;
     
  char* a;
  char* copy = strdup(testString.c_str());
  a = strtok(copy, "");

  while(a != NULL)
  {
    a = strtok(NULL, "/"); 
    nSlash++;       
  }
   
  if(nSlash==1)
  {
    //std::cout << "Found a win or place market! " << testString << std::endl;
    isWinOrPlace = true;
  }
     
  return isWinOrPlace; 
}

//Only to be called after the non-default contructor has been used!
bool DataEntry::Keep(){
  
  bool keep = false;
  if(m_isWinOrPlace) keep = true;
  return keep;  
  
}



//A function to print the contents of 
void DataEntry::print()
{
 std::cout << " ----------------------------------------------------- " << std::endl; 
 std::cout << std::setw(32) << std::right << " SPORTS_ID = " << std::setw(12) << std::left << m_sportsId << std::endl; 
 std::cout << std::setw(32) << std::right << " EVENT_ID = " << std::setw(12) << std::left << m_eventId << std::endl; 
 std::cout << std::setw(32) << std::right << " SETTLED_DATE = " << std::setw(12) << std::left << m_settledDate << std::endl; 
 std::cout << std::setw(32) << std::right << " COUNTRY = " << std::setw(12) << std::left << m_country << std::endl; 
 std::cout << std::setw(32) << std::right << " FULL_DESCRIPTION = " << std::setw(12) << std::left << m_fullDescription << std::endl; 
 std::cout << std::setw(32) << std::right << " COURSE = " << std::setw(12) << std::left << m_course << std::endl; 
 std::cout << std::setw(32) << std::right << " SCHEDULED_OFF = " << std::setw(12) << std::left << m_scheduledOff << std::endl; 
 std::cout << std::setw(32) << std::right << " EVENT = " << std::setw(12) << std::left << m_event << std::endl; 
 std::cout << std::setw(32) << std::right << " ACTUAL_OFF = " << std::setw(12) << std::left << m_actualOff << std::endl; 
 std::cout << std::setw(32) << std::right << " SELECTION_ID = " << std::setw(12)<< std::left  << m_selectionId << std::endl; 
 std::cout << std::setw(32) << std::right << " SELECTION = " << std::setw(12) << std::left << m_selection << std::endl; 
 std::cout << std::setw(32) << std::right << " ODDS = " << std::setw(12) << std::left << m_odds << std::endl; 
 std::cout << std::setw(32) << std::right << " NUMBER_BETS = " << std::setw(12) << std::left << m_numberBets << std::endl; 
 std::cout << std::setw(32) << std::right << " VOLUME_MATCHED = " << std::setw(12) << std::left << m_volumeMatched << std::endl; 
 std::cout << std::setw(32) << std::right << " LATEST_TAKEN = " << std::setw(12) << std::left << m_latestTaken << std::endl; 
 std::cout << std::setw(32) << std::right << " FIRST_TAKEN = " << std::setw(12) << std::left << m_firstTaken << std::endl; 
 std::cout << std::setw(32) << std::right << " WIN_FLAG = " << std::setw(12) << std::left << m_winFlag << std::endl; 
 std::cout << std::setw(32) << std::right << " IN_PLAY = " << std::setw(12) << std::left << m_inPlay << std::endl; 

}