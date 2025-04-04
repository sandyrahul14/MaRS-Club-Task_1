#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //Defining the LCD
float analog_ambient;
float analog_soil;

void setup() {
  pinMode(A0, INPUT);//Setting the sensor pins as input
  pinMode(A1, INPUT);
  pinMode(2, OUTPUT);//Defining the pins for output
  pinMode(3, OUTPUT);
  digitalWrite(2, LOW);//Initializing the pins to low voltage
  digitalWrite(3, LOW);
  lcd.init();			//Initializing the lcd and turning on the backlight of lcd
  lcd.backlight();
  lcd.setCursor(0,0);	//Setting the position of cursor

}
void loop(){
  analog_ambient=analogRead(A0);	//Getting analog values from ambient light sensor
  analog_soil=analogRead(A1);		//Getting analog values from soil moisture sensors
  if (analog_ambient <= 300 && analog_soil <= 400) {//Checks the threshold values
    lcd.clear();
    lcd.print("LESS WATER...");
    lcd.setCursor(0, 1);
    lcd.print("LESS SUNLIGHT...");
    delay(2000);
	lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WATERING...");
    lcd.setCursor(0, 1);
    lcd.print("GROW LIGHT ON...");
    digitalWrite(2, HIGH);			//Turns on the grow light
    digitalWrite(3, HIGH);			//turns on the pump motor
    
    delay(2000);
    lcd.clear();
    
  } 
    else if(analog_ambient >= 300 && analog_soil <= 400){//Checks the threshold values
    	lcd.clear();
    	digitalWrite(3, LOW);//turns off the grow light since ambient light is greater than threshold
    	lcd.print("LESS WATER...");
    	lcd.setCursor(0, 1);
    	lcd.print("OPTIMUM SUNLIGHT");
    	delay(2000);
        lcd.clear();
      
    	lcd.setCursor(0, 0);
    	lcd.print("WATERING...");
    	digitalWrite(2, HIGH);
    	lcd.setCursor(0, 1);
    	lcd.print("OPTIMUM SUNLIGHT");
    	delay(2000);
    	lcd.clear();
    	delay(1000);
  }
  	else if(analog_ambient <= 300 && analog_soil >= 400){
    	lcd.clear();
    	digitalWrite(2, LOW);//turns off the motor since analog value is leszs than threshold value
    	lcd.print("OPTIMUM WATER..");
    	lcd.setCursor(0, 1);
    	lcd.print("LESS SUNLIGHT...");
    	delay(2000);
		lcd.clear();
      
    	lcd.setCursor(0, 0);
   		digitalWrite(3, HIGH);
    	lcd.print("NO WATER NEEDED");
    	lcd.setCursor(0, 1);
    	lcd.print("GROW LIGHT ON...");
    	delay(2000);
		lcd.clear();
    	delay(1000);
  }
  	else {//If all conditions are ok this block is executed
    	lcd.setCursor(0, 0);
    	lcd.print("Conditions OK");
    	digitalWrite(2, LOW);
    	lcd.setCursor(0, 1);
    	lcd.print("No Action Needed");
    	digitalWrite(3, LOW);
    	delay(2000);
  }
}

