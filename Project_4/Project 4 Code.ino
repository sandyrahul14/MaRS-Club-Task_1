#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);//Defining the LCD

int pir_value;
int slide;
float ldr;
unsigned long time = 0;  // Store motion detection time

void setup() {
  pinMode(4, INPUT_PULLUP);  // PIR Sensor
  pinMode(2, INPUT_PULLUP);  // Slide Switch
  pinMode(A0, INPUT);        // LDR Sensor
  pinMode(5, OUTPUT);        // LED
  Serial.begin(9600);
  lcd.init();				//LCD Initialization
  lcd.backlight();			//Backlight on
  digitalWrite(5, HIGH);
}

void loop() {
  ldr = analogRead(A0);		//Gets analog values from ldr
  slide = digitalRead(2);	//Gets switch state from switch
  pir_value = digitalRead(4);	//Gets motion state from the sensor

  Serial.print("LDR: ");
  Serial.print(ldr);
  Serial.print(" | PIR: ");
  Serial.print(pir_value);
  Serial.print(" | Slide: ");
  Serial.println(slide);//Serial monitor values for debugging

  switch (slide) {
    case 0://slide switch off
      if (ldr <= 100 && pir_value == HIGH) {  // Low light & motion detected
        time = millis();  // Store motion detection time
        lcd.setCursor(0, 0);
        lcd.print("MOTION DETECTED");
        lcd.setCursor(0, 1);
        lcd.print("LIGHT ON...");
        digitalWrite(5, LOW);
        delay(1000);
        lcd.clear();
      }

      if ((millis() - time >= 5000) && pir_value == LOW) {  // No motion for 5 sec
        digitalWrite(5, HIGH);//The time can be changed as required
        lcd.setCursor(0, 0);
        lcd.print("NO MOTION...");
        lcd.setCursor(0, 1);
        lcd.print("TURNING OFF...");
        delay(1000);
        lcd.clear();
      }
    if(ldr>100){//bright light condition
        lcd.setCursor(0, 0);
        lcd.print("ENOUGH LIGHT...");
        lcd.setCursor(0, 1);
        lcd.print("TURNING OFF...");
        digitalWrite(5, HIGH);
        delay(1000);
        lcd.clear();
    }
      break;

    case 1://slide switch on
      digitalWrite(5, LOW);//Turns on the Light
      lcd.setCursor(0, 0);
      lcd.print("LIGHT ON...");
      delay(1000);
      lcd.clear();
      
      lcd.setCursor(0, 0);
      lcd.print("SMART SYSTEM");//The system does not function
      lcd.setCursor(0, 1);
      lcd.print("OFF...");
      delay(1000);
      lcd.clear();
    
      break;
  }
  
  delay(50);  // Small delay to avoid flickering
}