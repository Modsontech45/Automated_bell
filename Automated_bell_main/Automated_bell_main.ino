
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <DS3231.h>
DS3231 clock;
RTCDateTime dt;


LiquidCrystal_I2C lcd(0x27,16,4); 

/////////////////////////////
const int btnChange = 2;
const int btnOK = 3;
const int btnMode = 4;

int alarmHour = 12;
int alarmMinutes = 0;
boolean hourMode = 0;
boolean alarmOn = 1;
int M = 12;
int D = 31;
int Y = 2023;
int day = 7;
int h = 23;
int m = 59;

int addrH[] = {0, 1, 2, 3, 4};
int addrM[] = {5, 6, 7, 8, 9};

float temp;
int mode = 1;
int submode = 1;


///////////////////

void setup()
{
 
 lcd.init();
 lcd.backlight();
 lcd.clear();
 clock.begin();
//clock.setDateTime( __DATE__ , __TIME__ );

  pinMode(btnChange, INPUT_PULLUP);
  pinMode(btnOK, INPUT_PULLUP);
  pinMode(btnMode, INPUT_PULLUP);
  Serial.begin(9600); 

}




void loop()
{
  
if (digitalRead(btnMode) == LOW) {
    mode++;
    Serial.println("btnMode press");
    if (mode == 3) {
      mode = 1;
    }
    submode = 0;
    lcd.clear();
    delay(100 );
  }

  if (mode == 1) {
  
  
    myshow();
    Temp();
    sendDateTime();
    
  }

  if (mode == 2) {
    setTime();
  
   
  }
delay(100);
}
///////////////////////////////////////////
void Temp(){
  clock.forceConversion();
   lcd.setCursor(1, 3);
  lcd.print("Temperature: "); 
  temp = clock.readTemperature() - 3;

  lcd.print(temp);
  delay(100);
  
}
void myshow() {
  static int lastSecond = -1; // To keep track of the last displayed second
  dt = clock.getDateTime();

  // Update only if the second has changed
  if (dt.second != lastSecond) {
    lastSecond = dt.second;

    char buffer[3]; // Buffer to hold padded numbers

    // Update the date
    lcd.setCursor(0, 0);
    switch (dt.dayOfWeek) {
      case 1: lcd.print("Monday    "); break;
      case 2: lcd.print("Tuesday   "); break;
      case 3: lcd.print("Wednesday "); break;
      case 4: lcd.print("Thursday  "); break;
      case 5: lcd.print("Friday    "); break;
      case 6: lcd.print("Saturday  "); break;
      case 7: lcd.print("Sunday    "); break;
    }
    lcd.setCursor(10, 0);

    sprintf(buffer, "%02d", dt.day);
    lcd.print(buffer);
    lcd.print('/');
    sprintf(buffer, "%02d", dt.month);
    lcd.print(buffer);
    lcd.print('/');
    lcd.print(dt.year);

    // Update the time
    lcd.setCursor(3, 1);
    lcd.print("Time: ");
    sprintf(buffer, "%02d", dt.hour);
    lcd.print(buffer);
    lcd.print(':');
    sprintf(buffer, "%02d", dt.minute);
    lcd.print(buffer);
    lcd.print(':');
    sprintf(buffer, "%02d", dt.second);
    lcd.print(buffer);

    // Update the static text
    lcd.setCursor(1, 2);
    lcd.print("AFRIPUL GROUP TOGO");

    delay(100);
  }
}

  
  void sendDateTime() {
     dt = clock.getDateTime();
  Serial.print(dt.dayOfWeek);
  Serial.print(",");
  Serial.print(dt.hour);
  Serial.print(",");
  Serial.print(dt.minute);
  Serial.print(",");
  Serial.println(dt.second);
  delay(100);
}
void setTime() {
  lcd.setCursor(0, 0);
  lcd.write(2);

  if (digitalRead(btnOK) == LOW) {
    submode++;
    if (submode > 7) {
      submode = 0;
    }
    delay(200);
    lcd.clear();
  }

  if (submode == 0) {
    lcd.setCursor(2, 0);
    lcd.print("Set Date/Time?");
    lcd.setCursor(0, 1);
    lcd.print("Press OK button");
  }
  if (submode == 1) {
    lcd.setCursor(2, 0);
    lcd.print("Set Month");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(btnChange) == LOW) {
      M++;
      if (M == 13) {
        M = 1;
      }
      delay(200);
    }
    lcd.print(M);
    lcd.print(" ");
  }
  if (submode == 2) {
    lcd.setCursor(2, 0);
    lcd.print("Set Day");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(btnChange) == LOW) {
      D++;
      if (D == 32) {
        D = 1;
      }
      delay(200);
    }
    lcd.print(D);
    lcd.print(" ");
  }
  if (submode == 3) {
    lcd.setCursor(2, 0);
    lcd.print("Set Year");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(btnChange) == LOW) {
      Y++;
      if (Y == 2050) {
        Y = 2000;
      }
      delay(200);
    }
    lcd.print(Y);
  }
  if (submode == 4) {
    lcd.setCursor(2, 0);
    lcd.print("Set Day of the Week");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(btnChange) == LOW) {
      day++;
      if (day == 8) {
        day = 1;
      }
      delay(200);
    }
    switch (day) {
      case 1: lcd.print("Monday ");
        break;
      case 2: lcd.print("Tuesday ");
        break;
      case 3: lcd.print("Wednesday ");
        break;
      case 4: lcd.print("Thursday ");
        break;
      case 5: lcd.print("Friday ");
        break;
      case 6: lcd.print("Saturday ");
        break;
      case 7: lcd.print("Sunday ");
        break;
    }
  }
  if (submode == 5) {
    lcd.setCursor(2, 0);
    lcd.print("Set Hour");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(btnChange) == LOW) {
      h++;
      if (h == 24) {
        h = 0;
      }
      delay(200);
    }
    lcd.print(h);
    lcd.print(" ");
  }
  if (submode == 6) {
    lcd.setCursor(2, 0);
    lcd.print("Set Minutes");
    lcd.setCursor(0, 1);
    lcd.print("--> ");
    if (digitalRead(btnChange) == LOW) {
      m++;
      if (m == 60) {
        m = 0;
      }
      delay(200);
    }
    lcd.print(m);
    lcd.print(" ");
  }
  if (submode == 7) {
    lcd.setCursor(2, 0);
    lcd.print("Date & Time");
    lcd.setCursor(0, 1);
    lcd.print("Updating");

    // Correct function to set the date and time
    clock.setDateTime(Y, M, D, h, m, 0);  // Set date and time without dayOfWeek

    delay(2000);
    lcd.clear();
    mode = 1;
  }
}
