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
	  m_isGB = true;
	}
	else{
	  keepGoing = false;
	} 
	
        break;
	 
      case 4: //FULL_DESCRIPTION
        m_fullDescription = a;
	m_isWinOrPlace = testForWinOrPlace(a);
	if(m_isWinOrPlace == false) keepGoing = false;	
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
	//convert the date/time string to a ints/double member variables (private).
	ConvertTime(a);
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


//Input string is on format "DD-MM-YY HH:MM:SS", so firstly split sting in two, then 
// split up each half using strtok. 
void DataEntry::ConvertTime(std::string timeString){

  //split copy in to 2
  std::stringstream ss(timeString);
  std::string token;
  
  int index = 0;
  
  while( ss >> token)
  {
    //First half of string is the date DD-MM-YYYY 
    switch(index)
    {
      
      case 0:
      {
//	std::cout << "DEBUG case 0, token = " << token << std::endl;
	char* copy = strdup(token.c_str());
	char* b = strtok(copy,"-");
        
        int index1 = 0;  
        while(b != NULL)
        {
          switch(index1)
          {
            case 0:
	      m_day=atoi(b);
	      break;
	 
            case 1:
	      m_month = atoi(b);
	      break;

            case 2:
	      m_year = atoi(b);
	      break;

            default:
	      std::cout << "ERROR - Date is not written in expected format." << std::endl;
	      exit(0);
	      break;
          }
    
          b = strtok(NULL, "-");
          index1++;
     
        }
	
      }		
	break;
	
      case 1:
      {
//	std::cout << "DEBUG case 1, token = " << token << std::endl;
        char* copy = strdup(token.c_str());
        char* c = strtok(copy,":");

        int index2 = 0;  
        while(c != NULL)
        {
          switch(index2)
          {
            case 0:
	      m_hours=atof(c);
	      break;
	 
            case 1:
	      m_minutes = atof(c);
	      break;

            case 2:
	      m_seconds = atof(c);
	      break;

            default:
	      std::cout << "ERROR - Date is not written in expected format." << std::endl;
	      exit(0);
	      break;
          }
    
          c = strtok(NULL, ":");
          index2++;	
	}
	
      }	
	break;
	
      default:
	std::cout << "ERROR - Date is not written in expected format." << std::endl;
	exit(0);
	break;      
    }
    
  index++;  
  }  
}


bool DataEntry::testForPlace(std::string testString){
  
  bool isPlace = false;
  if(testString == "TO BE PLACED") isPlace = true;
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
  size_t nSlash = std::count(testString.begin(), testString.end(), '/');  
  if(nSlash ==1) isWinOrPlace = true;
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