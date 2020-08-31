
#include <Wire.h>
#include <EEPROM.h>
#include <MyRealTimeClock.h>
#include <LiquidCrystal_I2C.h>


#define but1 A0
#define but2 A1
#define but3 A2
#define but4 A3
#define but5 1
#define can1 2
#define can2 3
#define can3 4
#define can4 5
#define can5 6
#define can6 7
#define can7 8
#define can8 9
#define can9 10

 long screensaver = 0;
 long lightPause = 0;
 long pause4 = 0;
 long pause = 0;
 long switchMenuCounter = 1;
 long switchLightCounter = 1;
 bool menuFlag = true;
 bool light = true;
 int tempDay = 1;
 int tempMonth = 1;
 int tempYear = 2020;
 int tempDayOfWeek = 1;
 int tempHour = 0;
 int tempMinute = 0;
 int tempSecond = 0;

 MyRealTimeClock tm(11,12,13);
 LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

 
int years, months, days, hours, minutes, seconds, dayOfWeek;

typedef struct {
  String label;
  int minVal;
  int maxVal;
  int currentVal;
  void (*handler)();
} STRUCT_MENUPOS;

typedef enum {
  BUT1, BUT2, BUT3, BUT4, BUT5, NONE
} ENUM_BUTTON;

STRUCT_MENUPOS menu[3];

int currentMenuPos = 0;
int menuSize;
bool isInLowerLevel = false;
int tempVal;

 

  ENUM_BUTTON getButton() {
    
    
  if(digitalRead(A0) == HIGH) return BUT1;
  if(digitalRead(A1) == HIGH) return BUT2;
  if(digitalRead(A2) == HIGH) return BUT3;
  if(digitalRead(A3) == HIGH) return BUT4;
  if(digitalRead(1) == HIGH) return BUT5;
  

  return NONE;
}




void(* resetFunc) (void) = 0;

void handleNext() {
  if(isInLowerLevel) {
    tempVal++;
    if(tempVal > menu[currentMenuPos].maxVal) tempVal = menu[currentMenuPos].maxVal;
  } else {
    currentMenuPos = (currentMenuPos + 1) % menuSize;
  }
}

void handlePrev() {
  if(isInLowerLevel) {
    tempVal--;
    if(tempVal < menu[currentMenuPos].minVal) tempVal = menu[currentMenuPos].minVal;
  } else {
    currentMenuPos--;
    if(currentMenuPos < 0) currentMenuPos = menuSize - 1;
  }
}

void handleBack() {
  if(isInLowerLevel) {
    isInLowerLevel = false;
  }
}

void handleOk() {
  if(menu[currentMenuPos].handler != NULL && menu[currentMenuPos].maxVal <= menu[currentMenuPos].minVal) {
    (*(menu[currentMenuPos].handler))();
    return;
  }
  if(isInLowerLevel) {
    menu[currentMenuPos].currentVal = tempVal;
    isInLowerLevel = false;
  } else {
    tempVal = menu[currentMenuPos].currentVal;
    isInLowerLevel = true;
  }
}

int printTwoDigits(int number) {
  if(number < 10) {
    lcd.print("0");
    return number;
  }
  else {
    return number;
  }
  
}

class Canal {
  public:
   int startHour1, startMinute1, stopHour1, stopMinute1;
   int startHour2, startMinute2, stopHour2, stopMinute2;
   bool isActive1 = true;
   bool isActive2 = true;
   bool executingTime1 = false;
   bool executingTime2 = false;
  
   
  void setCanal() {
 
  delay(400);
  bool flag = true;
  long counter = 1;
  long tempPause = 0;
  long tempPause1 = 0;
  long tempPause2 = 0;
  long tempPause3 = 0;
  long tempPause4 = 0;
  long tempPause5 = 0;
  long tempPause6 = 0;
  long tempPause7 = 0;
 
  
  
  while(flag) {
   ENUM_BUTTON button = getButton();
   screensaver = millis();
    if(button == BUT1) {
      counter++;
    }
    if(counter == 1) {
     if(millis() - tempPause > 200) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("a:");
  
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(printTwoDigits(startMinute1));
  lcd.setCursor(8,0);
  lcd.print("|");
  lcd.setCursor(9,0);
  lcd.print(printTwoDigits(stopHour1));
  lcd.setCursor(11,0);
  lcd.print(":");
  lcd.setCursor(12,0);
  lcd.print(printTwoDigits(stopMinute1));
  lcd.setCursor(0,1);
  lcd.print("b:");
  lcd.setCursor(3,1);
  lcd.print(printTwoDigits(startHour2));
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(printTwoDigits(startMinute2));
  lcd.setCursor(8,1);
  lcd.print("|");
  lcd.setCursor(9,1);
  lcd.print(printTwoDigits(stopHour2));
  lcd.setCursor(11,1);
  lcd.print(":");
  lcd.setCursor(12,1);
  lcd.print(printTwoDigits(stopMinute2));
  delay(65);
  lcd.setCursor(3,0);
  lcd.print(printTwoDigits(startHour1));
  
 
   tempPause = millis();
 } 
     if(button == BUT4) {
       if(startHour1 <= 23) {
         startHour1++;
     if(startHour1 > 23) {
       startHour1 = 0;
     }
 }
   }
       
     if(button == BUT3) {
      if(startHour1 >= 0) {
    startHour1--;
      if(startHour1 < 0) {
        startHour1 = 23;
      }
 }
      }
    }

    if(counter == 2) {
     if(millis() - tempPause1 > 200) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("a:");
  lcd.setCursor(3,0);
  lcd.print(printTwoDigits(startHour1));
  lcd.setCursor(5,0);
  lcd.print(":");
  
  lcd.setCursor(8,0);
  lcd.print("|");
  lcd.setCursor(9,0);
  lcd.print(printTwoDigits(stopHour1));
  lcd.setCursor(11,0);
  lcd.print(":");
  lcd.setCursor(12,0);
  lcd.print(printTwoDigits(stopMinute1));
  lcd.setCursor(0,1);
  lcd.print("b:");
  lcd.setCursor(3,1);
  lcd.print(printTwoDigits(startHour2));
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(printTwoDigits(startMinute2));
  lcd.setCursor(8,1);
  lcd.print("|");
  lcd.setCursor(9,1);
  lcd.print(printTwoDigits(stopHour2));
  lcd.setCursor(11,1);
  lcd.print(":");
  lcd.setCursor(12,1);
  lcd.print(printTwoDigits(stopMinute2));
  delay(65);
  lcd.setCursor(6,0);
  lcd.print(printTwoDigits(startMinute1));

  
 
   tempPause1 = millis();
 } 
     if(button == BUT4) {
       if(startMinute1 <= 59) {
   startMinute1++;
     if(startMinute1 > 59) {
       startMinute1 = 0;
     }
   }
   }
       
     if(button == BUT3) {
       if(startMinute1 >= 0) {
    startMinute1--;
      if(startMinute1 < 0) {
        startMinute1 = 59;
      }
    }
      }
    }

     if(counter == 3) {
     if(millis() - tempPause2 > 200) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("a:");
  lcd.setCursor(3,0);
  lcd.print(printTwoDigits(startHour1));
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(printTwoDigits(startMinute1));
  lcd.setCursor(8,0);
  lcd.print("|");
  
  lcd.setCursor(11,0);
  lcd.print(":");
  lcd.setCursor(12,0);
  lcd.print(printTwoDigits(stopMinute1));
  lcd.setCursor(0,1);
  lcd.print("b:");
  lcd.setCursor(3,1);
  lcd.print(printTwoDigits(startHour2));
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(printTwoDigits(startMinute2));
  lcd.setCursor(8,1);
  lcd.print("|");
  lcd.setCursor(9,1);
  lcd.print(printTwoDigits(stopHour2));
  lcd.setCursor(11,1);
  lcd.print(":");
  lcd.setCursor(12,1);
  lcd.print(printTwoDigits(stopMinute2));
  delay(65);
  lcd.setCursor(9,0);
  lcd.print(printTwoDigits(stopHour1));
 

  
 
   tempPause2 = millis();
 } 
     if(button == BUT4) {
       if(stopHour1 <= 23) {
         stopHour1++;
     if(stopHour1 > 23) {
       stopHour1 = 0;
     }
 }
   }
       
     if(button == BUT3) {
        if(stopHour1 >= 0) {
    stopHour1--;
      if(stopHour1 < 0) {
        stopHour1 = 23;
      }
 }
      }
    }


     if(counter == 4) {
     if(millis() - tempPause3 > 200) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("a:");
  lcd.setCursor(3,0);
  lcd.print(printTwoDigits(startHour1));
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(printTwoDigits(startMinute1));
  lcd.setCursor(8,0);
  lcd.print("|");
  lcd.setCursor(9,0);
  lcd.print(printTwoDigits(stopHour1));
  lcd.setCursor(11,0);
  lcd.print(":");
  
  lcd.setCursor(0,1);
  lcd.print("b:");
  lcd.setCursor(3,1);
  lcd.print(printTwoDigits(startHour2));
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(printTwoDigits(startMinute2));
  lcd.setCursor(8,1);
  lcd.print("|");
  lcd.setCursor(9,1);
  lcd.print(printTwoDigits(stopHour2));
  lcd.setCursor(11,1);
  lcd.print(":");
  lcd.setCursor(12,1);
  lcd.print(printTwoDigits(stopMinute2));
  delay(65);
  lcd.setCursor(12,0);
  lcd.print(printTwoDigits(stopMinute1));
  
 

  
 
   tempPause3 = millis();
 } 
     if(button == BUT4) {
       if(stopMinute1 <= 59) {
   stopMinute1++;
     if(stopMinute1 > 59) {
       stopMinute1 = 0;
     }
   }
   }
       
     if(button == BUT3) {
        if(stopMinute1 >= 0) {
    stopMinute1--;
      if(stopMinute1 < 0) {
        stopMinute1 = 59;
      }
    }
      }
    }

     if(counter == 5) {
     if(millis() - tempPause4 > 200) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("a:");
  lcd.setCursor(3,0);
  lcd.print(printTwoDigits(startHour1));
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(printTwoDigits(startMinute1));
  lcd.setCursor(8,0);
  lcd.print("|");
  lcd.setCursor(9,0);
  lcd.print(printTwoDigits(stopHour1));
  lcd.setCursor(11,0);
  lcd.print(":");
  lcd.setCursor(12,0);
  lcd.print(printTwoDigits(stopMinute1));
  lcd.setCursor(0,1);
  lcd.print("b:");
  
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(printTwoDigits(startMinute2));
  lcd.setCursor(8,1);
  lcd.print("|");
  lcd.setCursor(9,1);
  lcd.print(printTwoDigits(stopHour2));
  lcd.setCursor(11,1);
  lcd.print(":");
  lcd.setCursor(12,1);
  lcd.print(printTwoDigits(stopMinute2));
  delay(65);
  lcd.setCursor(3,1);
  lcd.print(printTwoDigits(startHour2));
 

   tempPause4 = millis();
 } 
     if(button == BUT4) {
       if(startHour2 <= 23) {
         startHour2++;
     if(startHour2 > 23) {
       startHour2 = 0;
     }
 }
   }
       
     if(button == BUT3) {
       if(startHour2 >= 0) {
         startHour2--;
     if(startHour2 < 0) {
       startHour2 = 23;
     }
 }
      }
    }

    if(counter == 6) {
     if(millis() - tempPause5 > 200) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("a:");
  lcd.setCursor(3,0);
  lcd.print(printTwoDigits(startHour1));
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(printTwoDigits(startMinute1));
  lcd.setCursor(8,0);
  lcd.print("|");
  lcd.setCursor(9,0);
  lcd.print(printTwoDigits(stopHour1));
  lcd.setCursor(11,0);
  lcd.print(":");
  lcd.setCursor(12,0);
  lcd.print(printTwoDigits(stopMinute1));
  lcd.setCursor(0,1);
  lcd.print("b:");
  lcd.setCursor(3,1);
  lcd.print(printTwoDigits(startHour2));
  lcd.setCursor(5,1);
  lcd.print(":");
  
  lcd.setCursor(8,1);
  lcd.print("|");
  lcd.setCursor(9,1);
  lcd.print(printTwoDigits(stopHour2));
  lcd.setCursor(11,1);
  lcd.print(":");
  lcd.setCursor(12,1);
  lcd.print(printTwoDigits(stopMinute2));
  delay(65);
  lcd.setCursor(6,1);
  lcd.print(printTwoDigits(startMinute2));
 
 

   tempPause5 = millis();
 } 
     if(button == BUT4) {
       if(startMinute2 <= 59) {
   startMinute2++;
     if(startMinute2 > 59) {
       startMinute2 = 0;
     }
   }
   }
       
     if(button == BUT3) {
       if(startMinute2 >= 0) {
    startMinute2--;
      if(startMinute2 < 0) {
        startMinute2 = 59;
      }
    }
      }
    }

    if(counter == 7) {
     if(millis() - tempPause6 > 200) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("a:");
  lcd.setCursor(3,0);
  lcd.print(printTwoDigits(startHour1));
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(printTwoDigits(startMinute1));
  lcd.setCursor(8,0);
  lcd.print("|");
  lcd.setCursor(9,0);
  lcd.print(printTwoDigits(stopHour1));
  lcd.setCursor(11,0);
  lcd.print(":");
  lcd.setCursor(12,0);
  lcd.print(printTwoDigits(stopMinute1));
  lcd.setCursor(0,1);
  lcd.print("b:");
  lcd.setCursor(3,1);
  lcd.print(printTwoDigits(startHour2));
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(printTwoDigits(startMinute2));
  lcd.setCursor(8,1);
  lcd.print("|");
  
  lcd.setCursor(11,1);
  lcd.print(":");
  lcd.setCursor(12,1);
  lcd.print(printTwoDigits(stopMinute2));
  delay(65);
  lcd.setCursor(9,1);
  lcd.print(printTwoDigits(stopHour2));
 

   tempPause6 = millis();
 } 
     if(button == BUT4) {
      if(stopHour2 <=23) {
        stopHour2++;
        if(stopHour2 > 23) {
          stopHour2 = 0;
        }
      }
   }
       
     if(button == BUT3) {
         if(stopHour2 >= 0) {
     stopHour2--;
      if(stopHour2 < 0) {
        stopHour2 = 23;
  }
 }
      }
    }

  if(counter == 8) {
     if(millis() - tempPause7 > 200) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("a:");
  lcd.setCursor(3,0);
  lcd.print(printTwoDigits(startHour1));
  lcd.setCursor(5,0);
  lcd.print(":");
  lcd.setCursor(6,0);
  lcd.print(printTwoDigits(startMinute1));
  lcd.setCursor(8,0);
  lcd.print("|");
  lcd.setCursor(9,0);
  lcd.print(printTwoDigits(stopHour1));
  lcd.setCursor(11,0);
  lcd.print(":");
  lcd.setCursor(12,0);
  lcd.print(printTwoDigits(stopMinute1));
  lcd.setCursor(0,1);
  lcd.print("b:");
  lcd.setCursor(3,1);
  lcd.print(printTwoDigits(startHour2));
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(printTwoDigits(startMinute2));
  lcd.setCursor(8,1);
  lcd.print("|");
  lcd.setCursor(9,1);
  lcd.print(printTwoDigits(stopHour2));
  lcd.setCursor(11,1);
  lcd.print(":");
  delay(65);
  lcd.setCursor(12,1);
  lcd.print(printTwoDigits(stopMinute2));
 
 
 

   tempPause7 = millis();
 } 
     if(button == BUT4) {
       if(stopMinute2 <= 59) {
   stopMinute2++;
     if(stopMinute2 > 59) {
       stopMinute2 = 0;
     }
   }
   }
       
     if(button == BUT3) {
       if(stopMinute2 >= 0) {
    stopMinute2--;
      if(stopMinute2 < 0) {
        stopMinute2 = 59;
      }
    }
      }
    }
 if(counter == 9) {
  counter = 1;
 }

 if(button == BUT2) {
   
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
    
   
    delay(150);
   
  }

  }

  void executor(int canal) {

    if(startHour1 == 0 && startMinute1 == 0 && stopHour1 == 0 && stopMinute1 == 0) {
      isActive1 = false;
    }
    else {
      isActive1 = true;
    }
    if(startHour2 == 0 && startMinute2 == 0 && stopHour2 == 0 && stopMinute2 == 0) {
      isActive2 = false;
    }
    else {
      isActive2 = true;
    }
   
   if(isActive1) {
    if(startHour1 == hours && startMinute1 == minutes) {
      pinMode(canal, OUTPUT);
      executingTime1 = true;
    }
    if(stopHour1 == hours && stopMinute1 == minutes) {
      pinMode(canal, INPUT);
      executingTime1 = false;
    }
   }
   if(isActive2) {
    if(startHour2 == hours && startMinute2 == minutes) {
      pinMode(canal, OUTPUT);
      executingTime2 = true;
    }
    if(stopHour2 == hours && stopMinute2 == minutes) {
      pinMode(canal, INPUT);
      executingTime2 = false;
    }
   }
  }

  void displayCanalA(int canal, int rows, int cols) {
    lcd.setCursor(rows, cols);
    if(!isActive1) {
      lcd.print("-");
    }
    else if(executingTime1) {
      lcd.print("a");
    } else {
      lcd.print("*");
    }
  }
  void displayCanalB(int canal, int rows, int cols) {
    lcd.setCursor(rows, cols);
    if(!isActive2) {
      lcd.print("-");
    }
    else if(executingTime2) {
      lcd.print("b");
    } else {
      lcd.print("*");
    }
  }

};


Canal canal1;
Canal canal2;
Canal canal3;
Canal canal4;
Canal canal5;
Canal canal6;
Canal canal7;
Canal canal8;
Canal canal9;

void restartBattery() {
  tm.setDS1302Time(0,0,0,1,1,1,2020);
  resetFunc();
}

void displayActuallyTimes() {
  long pause = 0;
  if(millis() - pause > 200) {
  lcd.setCursor(0, 2);
  lcd.print("1");
  lcd.setCursor(2, 2);
  lcd.print("2");
  lcd.setCursor(4, 2);
  lcd.print("3");
  lcd.setCursor(6, 2);
  lcd.print("4");
  lcd.setCursor(8, 2);
  lcd.print("5");
  lcd.setCursor(10, 2);
  lcd.print("6");
  lcd.setCursor(12, 2);
  lcd.print("7");
  lcd.setCursor(14, 2);
  lcd.print("8");
  lcd.setCursor(16, 2);
  lcd.print("9");
  


  
   pause = millis();
  }
  

  
}

void prepareLcd() {
  lcd.begin(20, 4);
  lcd.setCursor(7, 1);
  lcd.print("Witaj !");
  delay(1000);
}



void prepareRtc() {
  tm.updateTime();
  years = tm.year;
  months = tm.month;
  days = tm.dayofmonth;
  hours = tm.hours;
  minutes = tm.minutes;
  seconds = tm.seconds;
  dayOfWeek = tm.dayofweek;
}

void mainDateAndTime() {
ENUM_BUTTON button = getButton();
  
if(millis() - pause > 900) {
lcd.clear(); 
lcd.print(printTwoDigits(days)); // Element 1
lcd.print("/"); 
lcd.print(printTwoDigits(months)); // Element 2
lcd.print("/");
lcd.print(printTwoDigits(years));
lcd.setCursor(11, 0);
lcd.print(displayDayOfWeek());
lcd.setCursor(0, 1);
lcd.print(printTwoDigits(hours)); // Element 4
lcd.print(":");
lcd.print(printTwoDigits(minutes)); // Element 5
lcd.print(":");
lcd.print(printTwoDigits(seconds)); // Element 6
lcd.print(" ");
displayActuallyTimes();
executor();
pause = millis();
}




}
  
String displayDayOfWeek() {
  
  switch(dayOfWeek) {
    case 1:
    return "PON";
    break;
    case 2:
    return "WTO";
    break;
    case 3:
    return "SRO";
    break;
    case 4:
    return "CZW";
    break;
    case 5:
    return "PT";
    break;
    case 6:
    return "SOB";
    break;
    case 7:
    return "NIE";
    break;
    
  }
}







void setTime() {
  bool flag = true;
  long counter = 3;
  
  
  while(flag) {
 canal1.executor(can1);
  canal2.executor(can2);
  canal3.executor(can3);
  canal4.executor(can4);
  canal5.executor(can5);
  canal6.executor(can6);
  canal7.executor(can7);
  canal8.executor(can8);
  canal9.executor(can9);
  
   ENUM_BUTTON button = getButton();
   screensaver = millis();
    if(button == BUT1) {
      counter++;
    }
    if(counter % 2 == 0) {
     firstNumberDelay(); 
     if(button == BUT4) {
       hourUp();
       }
     if(button == BUT3) {
      hourDown();
     }
    }
    if(counter % 2 != 0) {
      lastNumberDelay();
      if(button == BUT4) {
        minuteUp();
      }
      if(button == BUT3) {
        minuteDown();
      }
    }
    if(button == BUT2) {
      tm.setDS1302Time(0, tempMinute, tempHour, dayOfWeek, days, months, years);
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
      delay(400);
      isInLowerLevel = false;
      flag = false;
      
    
      
      
    }
    
   
    delay(150);
   
  }
 
  
  
}


  void displayFromMemory() {
   
  canal1.startHour1 = EEPROM.read(0);
  canal1.startMinute1 = EEPROM.read(1);
  canal1.stopHour1 = EEPROM.read(2);
  canal1.stopMinute1 = EEPROM.read(3);
  canal1.startHour2 = EEPROM.read(4);
  canal1.startMinute2 = EEPROM.read(5);
  canal1.stopHour2 = EEPROM.read(6);
  canal1.stopMinute2 = EEPROM.read(7);
  canal2.startHour1 = EEPROM.read(8);
  canal2.startMinute1 = EEPROM.read(9);
  canal2.stopHour1 = EEPROM.read(10);
  canal2.stopMinute1 = EEPROM.read(11);
  canal2.startHour2 = EEPROM.read(12);
  canal2.startMinute2 = EEPROM.read(13);
  canal2.stopHour2 = EEPROM.read(14);
  canal2.stopMinute2 = EEPROM.read(15);
  canal3.startHour1 = EEPROM.read(16);
  canal3.startMinute1 = EEPROM.read(17);
  canal3.stopHour1 = EEPROM.read(18);
  canal3.stopMinute1 = EEPROM.read(19);
  canal3.startHour2 = EEPROM.read(20);
  canal3.startMinute2 = EEPROM.read(21);
  canal3.stopHour2 = EEPROM.read(22);
  canal3.stopMinute2 = EEPROM.read(23);
  canal4.startHour1 = EEPROM.read(24);
  canal4.startMinute1 = EEPROM.read(25);
  canal4.stopHour1 = EEPROM.read(26);
  canal4.stopMinute1 = EEPROM.read(27);
  canal4.startHour2 = EEPROM.read(28);
  canal4.startMinute2 = EEPROM.read(29);
  canal4.stopHour2 = EEPROM.read(30);
  canal4.stopMinute2 = EEPROM.read(31);
  canal5.startHour1 = EEPROM.read(32);
  canal5.startMinute1 = EEPROM.read(33);
  canal5.stopHour1 = EEPROM.read(34);
  canal5.stopMinute1 = EEPROM.read(35);
  canal5.startHour2 = EEPROM.read(36);
  canal5.startMinute2 = EEPROM.read(37);
  canal5.stopHour2 = EEPROM.read(38);
  canal5.stopMinute2 = EEPROM.read(39);
  canal6.startHour1 = EEPROM.read(40);
  canal6.startMinute1 = EEPROM.read(41);
  canal6.stopHour1 = EEPROM.read(42);
  canal6.stopMinute1 = EEPROM.read(43);
  canal6.startHour2 = EEPROM.read(44);
  canal6.startMinute2 = EEPROM.read(45);
  canal6.stopHour2 = EEPROM.read(46);
  canal6.stopMinute2 = EEPROM.read(47);
  canal7.startHour1 = EEPROM.read(48);
  canal7.startMinute1 = EEPROM.read(49);
  canal7.stopHour1 = EEPROM.read(50);
  canal7.stopMinute1 = EEPROM.read(51);
  canal7.startHour2 = EEPROM.read(52);
  canal7.startMinute2 = EEPROM.read(53);
  canal7.stopHour2 = EEPROM.read(54);
  canal7.stopMinute2 = EEPROM.read(55);
  canal8.startHour1 = EEPROM.read(56);
  canal8.startMinute1 = EEPROM.read(57);
  canal8.stopHour1 = EEPROM.read(58);
  canal8.stopMinute1 = EEPROM.read(59);
  canal8.startHour2 = EEPROM.read(60);
  canal8.startMinute2 = EEPROM.read(61);
  canal8.stopHour2 = EEPROM.read(62);
  canal8.stopMinute2 = EEPROM.read(63);
  canal9.startHour1 = EEPROM.read(64);
  canal9.startMinute1 = EEPROM.read(65);
  canal9.stopHour1 = EEPROM.read(66);
  canal9.stopMinute1 = EEPROM.read(67);
  canal9.startHour2 = EEPROM.read(68);
  canal9.startMinute2 = EEPROM.read(69);
  canal9.stopHour2 = EEPROM.read(70);
  canal9.stopMinute2 = EEPROM.read(71);
 
}

void drawMenu() {
 
  static unsigned long lastRead = 0;
  static ENUM_BUTTON lastPressedButton = BUT4;
  static unsigned int isPressedSince = 0;
  int autoSwitchTime = 500;
  ENUM_BUTTON pressedButton = getButton();
  ENUM_BUTTON lastButton = NONE;
 
  

   
  

  if(pressedButton == NONE && lastRead != 0) {
    isPressedSince = 0;
    return;
  }
  

 
  if(pressedButton != lastPressedButton) {
    isPressedSince = 0;
  }

  if(isPressedSince > 3) autoSwitchTime = 70;
  if(lastRead != 0 && millis() - lastRead < autoSwitchTime && pressedButton == lastPressedButton) return;

  isPressedSince++;
  lastRead = millis();
  lastPressedButton = pressedButton;
  
  switch(pressedButton) {
    case BUT1: 
    handleOk();
    screensaver = millis();
    
    break;
    case BUT2: 
    
    screensaver = millis();
    break;
    case BUT3: 
    handleNext();
    screensaver = millis();
    break;
    case BUT4: 
    handlePrev();
    screensaver = millis();
    break;

    case BUT5:

    screensaver = millis();


    break;
    
  }


  lcd.home();
  lcd.clear();
  
  if(isInLowerLevel) {
    lcd.print(menu[currentMenuPos].label);
    lcd.setCursor(0, 1);
    lcd.print(F("> "));
  

    if(menu[currentMenuPos].handler != NULL) {
      (*(menu[currentMenuPos].handler))();
       canal1.executor(can1);
  
    } else {
      lcd.print(tempVal);
    }
  } else {

    lcd.print(F("Menu:"));
    lcd.setCursor(0, 2);
    lcd.print(F("> "));

    lcd.print(menu[currentMenuPos].label);
  }
}


 
void setup()  
{


 pinMode(but1, INPUT);
 pinMode(but2, INPUT);
 pinMode(but3, INPUT);
 pinMode(but4, INPUT);
 pinMode(but5, INPUT);


  menu[0] = {"Ustaw czas", 0, 9, 5, setTime};
  menu[1] = {"Ustaw kanaly", 0, 2, 0, setCanals};
  menu[2] = {"Ustaw date", 0, 2020, 10, setDate};


  menuSize = sizeof(menu)/sizeof(STRUCT_MENUPOS);
 
 prepareLcd();
 tm.updateTime();
 
 
}

void reset() {
  tm.setDS1302Time(0,0,0,1,1,1,2020);
  
}




void loop() 
{   

   if(years == 2000) {
     reset();
   }
 
   if(millis() - pause4 > 150) {
      ENUM_BUTTON button = getButton();
      
       displayFromMemory();
   
 
   
   if(button == BUT2) {
    switchMenuCounter++;
    screensaver = millis();
   }
   if(button == BUT5) {
    if(millis() - lightPause > 1000) {
    switchLightCounter++;
    screensaver = millis();
    lightPause = millis();
    }
   }
   if(switchLightCounter == 3) {
    switchLightCounter = 1;
   }
   
  
   
  
   
   if(switchMenuCounter % 2 != 0) {
      menuFlag = true;
      
   }
   if(switchMenuCounter % 2 == 0) {
      menuFlag = false;
   }
   if(switchLightCounter == 1) {
    light = true;
    if(button == NONE && millis() - screensaver > 300000) {
    light = false;
    switchLightCounter = 2;
    menuFlag = true;
    switchMenuCounter = 1;
   }
   }
   if(switchLightCounter == 2) {
    light = false;
   }
   
  
  

   if(menuFlag) {
     prepareRtc();
     mainDateAndTime();
   }
   if(!menuFlag) {
    drawMenu();
  
    
   }
   if(light) {
    lcd.backlight();
   }
   if(!light) {
    lcd.noBacklight();
   }
   

   pause4 = millis();

   
   }
   
}





  
void executor() {
  canal1.executor(can1);
  canal1.displayCanalA(can1, 0, 3);
  canal1.displayCanalB(can1, 1, 3);
  canal2.executor(can2);
  canal2.displayCanalA(can2, 2, 3);
  canal2.displayCanalB(can2, 3, 3);
  canal3.executor(can3);
  canal3.displayCanalA(can3, 4, 3);
  canal3.displayCanalB(can3, 5, 3);
  canal4.executor(can4);
  canal4.displayCanalA(can4, 6, 3);
  canal4.displayCanalB(can4, 7, 3);
  canal5.executor(can5);
  canal5.displayCanalA(can5, 8, 3);
  canal5.displayCanalB(can5, 9, 3);
  canal6.executor(can6);
  canal6.displayCanalA(can6, 10, 3);
  canal6.displayCanalB(can6, 11, 3); 
  canal7.executor(can7);
  canal7.displayCanalA(can7, 12, 3);
  canal7.displayCanalB(can7, 13, 3);
  canal8.executor(can8);
  canal8.displayCanalA(can8, 14, 3);
  canal8.displayCanalB(can8, 15, 3);
  canal9.executor(can9);
  canal9.displayCanalA(can9, 16, 3);
  canal9.displayCanalB(can9, 17, 3);
    
 



}

void firstNumberDelay() {
  int tempPause;
 if(millis() - tempPause > 200) {
    lcd.clear();
    lcd.setCursor(3, 0);
    lcd.print(printTwoDigits(tempMinute));
    lcd.setCursor(2, 0);
    lcd.print(":");
    delay(65);
    lcd.setCursor(0,0);
    lcd.print(printTwoDigits(tempHour));
    
    
    tempPause = millis();
    
    }
}

void lastNumberDelay() {
  int tempPause = 0;
  if(millis() - tempPause > 200) {
    lcd.clear();
    lcd.print(printTwoDigits(tempHour));
    lcd.print(":");
    delay(65);
    lcd.setCursor(3, 0);
    lcd.print(printTwoDigits(tempMinute));
    tempPause = millis();
    
    }
}

void hourUp() {
 if(tempHour <= 23) {
   tempHour++;
     if(tempHour > 23) {
       tempHour = 0;
     }
   }
 }

void hourDown() {
  if(tempHour >= 0) {
    tempHour--;
      if(tempHour < 0) {
        tempHour = 23;
      }
    }
  }

void minuteUp() {
  if(tempMinute <= 59) {
   tempMinute++;
     if(tempMinute > 59) {
       tempMinute = 0;
     }
   }
}

void minuteDown() {
  if(tempMinute >= 0) {
    tempMinute--;
      if(tempMinute < 0) {
        tempMinute = 59;
      }
    }
  }





String displayTempDayOfWeek() {
   switch(tempDayOfWeek) {
    case 1:
    return "PON";
    break;
    case 2:
    return "WTO";
    break;
    case 3:
    return "SRO";
    break;
    case 4:
    return "CZW";
    break;
    case 5:
    return "PT";
    break;
    case 6:
    return "SOB";
    break;
    case 7:
    return "NIE";
    break;
    
  }
}

void setDate() {

  bool flag = true;
  long counter = 0;
  long tempPause = 0;
  long tempPause1 = 0;
  long tempPause2 = 0;
  long tempPause3 = 0;
  
  
  while(flag) {
  canal1.executor(can1);
  canal2.executor(can2);
  canal3.executor(can3);
  canal4.executor(can4);
  canal5.executor(can5);
  canal6.executor(can6);
  canal7.executor(can7);
  canal8.executor(can8);
  canal9.executor(can9);
  
    screensaver = millis();
   ENUM_BUTTON button = getButton();
    if(button == BUT1) {
      counter++;
    }
    if(counter == 1) {
    if(millis() - tempPause > 100) {
      lcd.clear();
      lcd.setCursor(2,0);
  lcd.print("/");
  lcd.setCursor(0, 1);
  lcd.print(displayTempDayOfWeek());
  lcd.setCursor(6, 0);
  lcd.print(tempYear);
  lcd.setCursor(3, 0);
  lcd.print(printTwoDigits(tempMonth));
  lcd.print("/");
  delay(65);
  lcd.setCursor(0, 0);
  lcd.print(printTwoDigits(tempDay));
 
   tempPause = millis();
    }
   if(button == BUT4) {
       if(tempDay <= 32) {
        tempDay++;
        if(tempDay > 32) {
          tempDay = 0;
        }
       }
   }
     if(button == BUT3) {
       if(tempDay >= 0) {
        tempDay--;
        if(tempDay < 0) {
          tempDay = 32;
        }
       }
     }
    }
      
    

    if(counter == 2) {
       if(millis() - tempPause1 > 100) {
      lcd.clear();
      lcd.setCursor(0, 0);
  lcd.print(printTwoDigits(tempDay));
  lcd.print("/");
  lcd.setCursor(5, 0);
  lcd.print("/");
  lcd.print(tempYear);
  lcd.setCursor(0, 1);
  lcd.print(displayTempDayOfWeek());
  lcd.setCursor(3, 0);
  delay(65);
  lcd.print(printTwoDigits(tempMonth));
 
   tempPause1 = millis();
    }
   if(button == BUT4) {
       if(tempMonth <= 12) {
        tempMonth++;
        if(tempMonth > 12) {
          tempMonth = 1;
        }
       }
   }
     if(button == BUT3) {
       if(tempMonth >= 1) {
        tempMonth--;
        if(tempMonth < 1) {
          tempMonth = 12;
        }
       }
     }
    }
    

    if(counter == 3) {
       if(millis() - tempPause2 > 100) {
      lcd.clear();
      lcd.setCursor(0, 0);
  lcd.print(printTwoDigits(tempDay));
  lcd.print("/");
  lcd.setCursor(3, 0);
  lcd.print(printTwoDigits(tempMonth));
  lcd.print("/");
  lcd.setCursor(0, 1);
  lcd.print(displayTempDayOfWeek());
  lcd.setCursor(6, 0);
  delay(65);
  lcd.print(tempYear);
 
   tempPause2 = millis();
    }
   if(button == BUT4) {
       tempYear++;
   }
     if(button == BUT3) {
       tempYear--;
     }
    }

    if(counter == 4) {
      if(millis() - tempPause3 > 100) {
      lcd.clear();
      lcd.setCursor(0, 0);
  lcd.print(printTwoDigits(tempDay));
  lcd.print("/");
  lcd.setCursor(3, 0);
  lcd.print(printTwoDigits(tempMonth));
  lcd.print("/");
  lcd.setCursor(6, 0);
  lcd.print(tempYear);
  lcd.setCursor(0, 1);
  delay(65);
  lcd.print(displayTempDayOfWeek());
 
   tempPause3 = millis();
    }
   if(button == BUT4) {
    if(tempDayOfWeek <= 7) {
       tempDayOfWeek++;
       if(tempDayOfWeek > 7) {
        tempDayOfWeek = 1;
       }
    }

   } 
   
     if(button == BUT3) {
       if(tempDayOfWeek >= 1) {
      tempDayOfWeek--;
      if(tempDayOfWeek < 1) {
        tempDayOfWeek = 7;
      }
    }
     }
    }
    if(counter == 5) {
      counter = 1;
    }
    if(button == BUT2) {
      tm.setDS1302Time(seconds, minutes, hours, tempDayOfWeek, tempDay, tempMonth, tempYear);
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
    
    
  delay(150);
  }
   
}
 

void setCanals() {

  bool flag = true;
  int counter = 0;
  long tempPause = 0;
  long tempPause1 = 0;
  long tempPause2 = 0;
  long tempPause3 = 0;
  long tempPause4 = 0;
  long tempPause5 = 0;
  long tempPause6 = 0;
  long tempPause7 = 0;
  long tempPause8 = 0;
  long tempPause9 = 0;

  while(flag) {
  canal1.executor(can1);
  canal2.executor(can2);
  canal3.executor(can3);
  canal4.executor(can4);
  canal5.executor(can5);
  canal6.executor(can6);
  canal7.executor(can7);
  canal8.executor(can8);
  canal9.executor(can9);
  
   ENUM_BUTTON button = getButton();
   screensaver = millis();
    if(button == BUT1) {
      counter++;
    }
    if(counter == 1) {
     if(millis() - tempPause > 200) {
  lcd.clear();
  
  lcd.setCursor(3,0);
  lcd.print("K2");
  lcd.setCursor(6,0);
  lcd.print("K3");
  lcd.setCursor(9,0);
  lcd.print("K4");
  lcd.setCursor(12,0);
  lcd.print("K5");
  lcd.setCursor(0,1);
  lcd.print("K6");
  lcd.setCursor(3,1);
  lcd.print("K7");
  lcd.setCursor(6,1);
  lcd.print("K8");
  lcd.setCursor(9,1);
  lcd.print("K9");
  
  delay(65);
  lcd.setCursor(0,0);
  lcd.print("K1");
  
  
 
   tempPause = millis();
 } 

      if(button == BUT2) {
      canal1.setCanal();
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
       EEPROM.write(0, canal1.startHour1);
       EEPROM.write(1, canal1.startMinute1);
       EEPROM.write(2, canal1.stopHour1);
       EEPROM.write(3, canal1.stopMinute1);
       EEPROM.write(4, canal1.startHour2);
       EEPROM.write(5, canal1.startMinute2);
       EEPROM.write(6, canal1.stopHour2);
       EEPROM.write(7, canal1.stopMinute2);
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
  }

  if(counter == 2) {
     if(millis() - tempPause1 > 200) {
  lcd.clear();
  
  lcd.setCursor(6,0);
  lcd.print("K3");
  lcd.setCursor(9,0);
  lcd.print("K4");
  lcd.setCursor(12,0);
  lcd.print("K5");
  lcd.setCursor(0,1);
  lcd.print("K6");
  lcd.setCursor(3,1);
  lcd.print("K7");
  lcd.setCursor(6,1);
  lcd.print("K8");
  lcd.setCursor(9,1);
  lcd.print("K9");

  lcd.setCursor(0,0);
  lcd.print("K1");
  delay(65);
  lcd.setCursor(3,0);
  lcd.print("K2");
  
  
  
 
   tempPause1 = millis();
 } 

      if(button == BUT2) {
      canal2.setCanal();
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
       EEPROM.write(8, canal2.startHour1);
       EEPROM.write(9, canal2.startMinute1);
       EEPROM.write(10, canal2.stopHour1);
       EEPROM.write(11, canal2.stopMinute1);
       EEPROM.write(12, canal2.startHour2);
       EEPROM.write(13, canal2.startMinute2);
       EEPROM.write(14, canal2.stopHour2);
       EEPROM.write(15, canal2.stopMinute2);
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
  }

   if(counter == 3) {
     if(millis() - tempPause2 > 200) {
  lcd.clear();
  
 
  lcd.setCursor(9,0);
  lcd.print("K4");
  lcd.setCursor(12,0);
  lcd.print("K5");
  lcd.setCursor(0,1);
  lcd.print("K6");
  lcd.setCursor(3,1);
  lcd.print("K7");
  lcd.setCursor(6,1);
  lcd.print("K8");
  lcd.setCursor(9,1);
  lcd.print("K9");
 
  lcd.setCursor(0,0);
  lcd.print("K1");
  lcd.setCursor(3,0);
  lcd.print("K2");
  delay(65);
  lcd.setCursor(6,0);
  lcd.print("K3");
  
  
  
 
   tempPause2 = millis();
 } 

      if(button == BUT2) {
      canal3.setCanal();
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
       EEPROM.write(16, canal3.startHour1);
       EEPROM.write(17, canal3.startMinute1);
       EEPROM.write(18, canal3.stopHour1);
       EEPROM.write(19, canal3.stopMinute1);
       EEPROM.write(20, canal3.startHour2);
       EEPROM.write(21, canal3.startMinute2);
       EEPROM.write(22, canal3.stopHour2);
       EEPROM.write(23, canal3.stopMinute2);
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
  }

  if(counter == 4) {
     if(millis() - tempPause3 > 200) {
  lcd.clear();
  
 
  lcd.setCursor(12,0);
  lcd.print("K5");
  lcd.setCursor(0,1);
  lcd.print("K6");
  lcd.setCursor(3,1);
  lcd.print("K7");
  lcd.setCursor(6,1);
  lcd.print("K8");
  lcd.setCursor(9,1);
  lcd.print("K9");
  
  lcd.setCursor(0,0);
  lcd.print("K1");
  lcd.setCursor(3,0);
  lcd.print("K2");
  lcd.setCursor(6,0);
  lcd.print("K3");
  delay(65);
  lcd.setCursor(9,0);
  lcd.print("K4");
  
  
  
 
   tempPause3 = millis();
 } 

      if(button == BUT2) {
      canal4.setCanal();
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
       EEPROM.write(24, canal4.startHour1);
       EEPROM.write(25, canal4.startMinute1);
       EEPROM.write(26, canal4.stopHour1);
       EEPROM.write(27, canal4.stopMinute1);
       EEPROM.write(28, canal4.startHour2);
       EEPROM.write(29, canal4.startMinute2);
       EEPROM.write(30, canal4.stopHour2);
       EEPROM.write(31, canal4.stopMinute2);
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
  }

  if(counter == 5) {
     if(millis() - tempPause4 > 200) {
  lcd.clear();
  
 
  lcd.setCursor(0,1);
  lcd.print("K6");
  lcd.setCursor(3,1);
  lcd.print("K7");
  lcd.setCursor(6,1);
  lcd.print("K8");
  lcd.setCursor(9,1);
  lcd.print("K9");
 
  lcd.setCursor(0,0);
  lcd.print("K1");
  lcd.setCursor(3,0);
  lcd.print("K2");
  lcd.setCursor(6,0);
  lcd.print("K3");
  lcd.setCursor(9,0);
  lcd.print("K4");
  delay(65);
  lcd.setCursor(12,0);
  lcd.print("K5");
  
  
  
 
   tempPause4 = millis();
 } 

      if(button == BUT2) {
      canal5.setCanal();
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
       EEPROM.write(32, canal5.startHour1);
       EEPROM.write(33, canal5.startMinute1);
       EEPROM.write(34, canal5.stopHour1);
       EEPROM.write(35, canal5.stopMinute1);
       EEPROM.write(36, canal5.startHour2);
       EEPROM.write(37, canal5.startMinute2);
       EEPROM.write(38, canal5.stopHour2);
       EEPROM.write(39, canal5.stopMinute2);
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
  }

  if(counter == 6) {
     if(millis() - tempPause5 > 200) {
  lcd.clear();
 
  lcd.setCursor(3,1);
  lcd.print("K7");
  lcd.setCursor(6,1);
  lcd.print("K8");
  lcd.setCursor(9,1);
  lcd.print("K9");
 
  lcd.setCursor(0,0);
  lcd.print("K1");
  lcd.setCursor(3,0);
  lcd.print("K2");
  lcd.setCursor(6,0);
  lcd.print("K3");
  lcd.setCursor(9,0);
  lcd.print("K4");
  lcd.setCursor(12,0);
  lcd.print("K5");
  delay(65);
  lcd.setCursor(0,1);
  lcd.print("K6");
  
  
  
 
   tempPause5 = millis();
 } 

      if(button == BUT2) {
      canal6.setCanal();
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
       EEPROM.write(40, canal6.startHour1);
       EEPROM.write(41, canal6.startMinute1);
       EEPROM.write(42, canal6.stopHour1);
       EEPROM.write(43, canal6.stopMinute1);
       EEPROM.write(44, canal6.startHour2);
       EEPROM.write(45, canal6.startMinute2);
       EEPROM.write(46, canal6.stopHour2);
       EEPROM.write(47, canal6.stopMinute2);
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
  }

   if(counter == 7) {
     if(millis() - tempPause6 > 200) {
  lcd.clear();
 
  
  lcd.setCursor(6,1);
  lcd.print("K8");
  lcd.setCursor(9,1);
  lcd.print("K9");
  
  lcd.setCursor(0,0);
  lcd.print("K1");
  lcd.setCursor(3,0);
  lcd.print("K2");
  lcd.setCursor(6,0);
  lcd.print("K3");
  lcd.setCursor(9,0);
  lcd.print("K4");
  lcd.setCursor(12,0);
  lcd.print("K5");
  lcd.setCursor(0,1);
  lcd.print("K6");
  delay(65);
  lcd.setCursor(3,1);
  lcd.print("K7");
  
  
  
 
   tempPause6 = millis();
 } 

      if(button == BUT2) {
      canal7.setCanal();
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
       EEPROM.write(48, canal7.startHour1);
       EEPROM.write(49, canal7.startMinute1);
       EEPROM.write(50, canal7.stopHour1);
       EEPROM.write(51, canal7.stopMinute1);
       EEPROM.write(52, canal7.startHour2);
       EEPROM.write(53, canal7.startMinute2);
       EEPROM.write(54, canal7.stopHour2);
       EEPROM.write(55, canal7.stopMinute2);
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
  }

  if(counter == 8) {
     if(millis() - tempPause7 > 200) {
  lcd.clear();
 
  lcd.setCursor(9,1);
  lcd.print("K9");

  lcd.setCursor(0,0);
  lcd.print("K1");
  lcd.setCursor(3,0);
  lcd.print("K2");
  lcd.setCursor(6,0);
  lcd.print("K3");
  lcd.setCursor(9,0);
  lcd.print("K4");
  lcd.setCursor(12,0);
  lcd.print("K5");
  lcd.setCursor(0,1);
  lcd.print("K6");
  lcd.setCursor(3,1);
  lcd.print("K7");
  delay(65);
  lcd.setCursor(6,1);
  lcd.print("K8");
  
  
  
 
   tempPause7 = millis();
 } 

      if(button == BUT2) {
      canal8.setCanal();
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
       EEPROM.write(56, canal8.startHour1);
       EEPROM.write(57, canal8.startMinute1);
       EEPROM.write(58, canal8.stopHour1);
       EEPROM.write(59, canal8.stopMinute1);
       EEPROM.write(60, canal8.startHour2);
       EEPROM.write(61, canal8.startMinute2);
       EEPROM.write(62, canal8.stopHour2);
       EEPROM.write(63, canal8.stopMinute2);
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
  }

   if(counter == 9) {
     if(millis() - tempPause8 > 200) {
  lcd.clear();
 
 
 
  lcd.setCursor(0,0);
  lcd.print("K1");
  lcd.setCursor(3,0);
  lcd.print("K2");
  lcd.setCursor(6,0);
  lcd.print("K3");
  lcd.setCursor(9,0);
  lcd.print("K4");
  lcd.setCursor(12,0);
  lcd.print("K5");
  lcd.setCursor(0,1);
  lcd.print("K6");
  lcd.setCursor(3,1);
  lcd.print("K7");
  lcd.setCursor(6,1);
  lcd.print("K8");
  delay(65);
  lcd.setCursor(9,1);
  lcd.print("K9");
  
  
  
  
 
   tempPause8 = millis();
 } 

      if(button == BUT2) {
      canal9.setCanal();
      lcd.clear();
      lcd.print("Zapisac?");
      lcd.setCursor(0,2);
      lcd.print("ZAPISZ [MENU]");
      lcd.setCursor(0,3);
      lcd.print("POPRAW [AUTO]");
       EEPROM.write(64, canal9.startHour1);
       EEPROM.write(65, canal9.startMinute1);
       EEPROM.write(66, canal9.stopHour1);
       EEPROM.write(67, canal9.stopMinute1);
       EEPROM.write(68, canal9.startHour2);
       EEPROM.write(69, canal9.startMinute2);
       EEPROM.write(70, canal9.stopHour2);
       EEPROM.write(71, canal9.stopMinute2);
      delay(400);
      isInLowerLevel = false;
      flag = false;
    }
  }

 
  
    if(counter == 10) {
      counter = 1;
    }

    
    delay(150);
  }   
}


void lightOn() {
  
  lcd.clear();
  lcd.print("Swiatlo wlaczone");
  lcd.setCursor(0,1);
  lcd.print("Mozna czyscic");
  digitalWrite(14, LOW);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(17, LOW);

}
