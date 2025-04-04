

#include <Wire.h>   

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);	//Defining the LCD

float analog_reading;
float voltage;
float temp_c;
int button1;
int button2;
int gas;

void setup()
{
  pinMode(A0, INPUT);		//Setting up analog pin for temperatur sensor
  pinMode(2, INPUT_PULLUP); //Setting up digital pins for boolean like inputs
  pinMode(4, INPUT_PULLUP);
  pinMode(A1, INPUT);
  lcd.init();
  lcd.backlight();		//Initializibg the LCD and turning on backlight
  lcd.setCursor(0,0);	//Setting the cursor to first row and first column
  
}

void loop()
{
  button1=digitalRead(4);	//Reading the values of button using the digital pins
  button2=digitalRead(2);
  
  
  if(button2==LOW){					//Condition if button 2 is pressed
    delay(200);						//Delay for 0.2 seconds to neglect multiple detections
    analog_reading=analogRead(A0);	//Reads the temperature values
    voltage=(analog_reading*5.0)/1024;//coverts analog readings to voltage
    temp_c=100*(voltage-0.5);		//converts volatages to temperature in celsius
    lcd.clear();					//clears the LCD
    lcd.setCursor(0,0);
    lcd.print("Temp=");
    lcd.print(temp_c);				//Prints the value of temperature in screen
    lcd.print("*c");
    delay(1000);
  }
  else if(button1==LOW){			//Condition if button 1 is pressed
    lcd.clear();
    lcd.setCursor(0,0);
    gas=analogRead(A1);				//reads the analog values of the gas sensor
    	if(gas>=150){				//checks if analog value of gas sensor is greater or equal to 150
    		lcd.print("Smoke Detected");//prints if smoke is detected
    		}
    	else{
    		lcd.print("No Smoke");		//prints if smoke is not detected
    }
    delay(1000);
   }
  else{									//condition if none of the buttons are pressed
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Press 1 or 2");			//asks the user to press any of the button
    delay(2000);
          }
	
}//100% my own work...