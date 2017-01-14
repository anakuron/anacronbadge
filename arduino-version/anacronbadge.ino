
#include <Wire.h>  // Comes with Arduino IDE
#include <LiquidCrystal_I2C.h>
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads

//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//VAR
const int  buttonPin = 2;

void setup()
{
  Serial.begin(9600);

  lcd.begin(16,2);

// -------
  for(int i = 0; i< 3; i++)
  {
    lcd.clear();
    lcd.print("BLINK BLINK");
    lcd.backlight();
    delay(100);
    lcd.noBacklight();
    delay(100);
  }
  lcd.backlight(); // finish with backlight on  

//-------- Write characters on the display ------------------
  lcd.setCursor(0,0); //Start at character 4 on line 0
 
  lcd.clear();
  lcd.print("hello! my name");
  lcd.setCursor(0,1);
  lcd.print("is anacron");
  delay(8000);
  for (int positionCounter = 0; positionCounter < 14; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }
  lcd.clear();
lcd.setCursor(0,0);
lcd.print("--- anacron ---");

}/*--(end setup )---*/


void loop()
{
  {
    // when chNaracters arrive over the serial port...
    
    if (Serial.available()) {
      // wait a bit for the entire message to arrive
      delay(100);
      
      lcd.setCursor(0,1);
      // read all the available characters
      while (Serial.available() > 0) {
        // display each character to the LCD
        lcd.write(Serial.read());
      }
    }
  }

}


