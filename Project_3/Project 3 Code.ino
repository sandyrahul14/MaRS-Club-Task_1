#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define pin numbers for components
#define servo 6     // Servo motor connected to pin 6
#define tilt 2      // Tilt sensor connected to pin 2
#define buzzer 3    // Buzzer connected to pin 3

// Initialize LCD display with I2C address 0x27 (16x2 display)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Declare sensor values and button state variables
int tilt_value;    
float force_value; 
int button;        
Servo lockServo;   // Create Servo object
bool lock = false; // Lock state (false = unlocked, true = locked)

void setup() {
  pinMode(tilt, INPUT_PULLUP);  // Set tilt sensor as input with internal pull-up resistor
  pinMode(buzzer, OUTPUT);      // Set buzzer as output
  pinMode(A0, INPUT);           // Set force sensor (analog) as input
  pinMode(4, INPUT_PULLUP);     // Set button as input with internal pull-up resistor
  
  lockServo.attach(servo);  // Attach servo to pin 6
  lockServo.write(0);       // Initialize servo in locked position
  
  lcd.init();       // Initialize LCD
  lcd.backlight();  // Turn on LCD backlight
  Serial.begin(9600); // Start serial communication for debugging
}

void loop() {
  // Read sensor and button values
  tilt_value = digitalRead(tilt);
  force_value = analogRead(A0);
  button = digitalRead(4);

  // Print sensor values for debugging
  Serial.print("Tilt: ");
  Serial.print(tilt_value);
  Serial.print(" | Force: ");
  Serial.println(force_value);
  Serial.println(button);

  lcd.clear();  // Clear LCD before updating display
  lcd.setCursor(0, 0);  // Set cursor to the first row
  
  // Condition 1: Owner Command - Unlocking the Door
  if ((button == 0 && (tilt_value == 0 && force_value >= 100)) || (button == 0 && (force_value >= 100 && tilt_value == 1)) || button == 0) {
    if (lock == true) {
      lcd.setCursor(0, 0);
      lcd.print("OWNER COMMAND"); 
      lcd.setCursor(0, 1);
      lcd.print("UNLOCKING...");
      lockServo.write(-90);  // Move servo to unlock position
      lock = false;  // Update lock state
    }
    lcd.setCursor(0, 0);
    lcd.print("UNLOCKED..."); 
    delay(1000);
    lcd.clear();
  }

  // Condition 2: Unauthorized Movement Detected
  else if (tilt_value == 0 && force_value >= 100 && button == 1) {
    tone(buzzer, 1000); // Activate buzzer alarm
    
    lcd.print("ALERT!!!");
    delay(1000);
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("ABNORMAL");
    lcd.setCursor(0, 1);
    lcd.print("MOVEMENTS");
    delay(1000);
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("PERSON DETECTED");
    delay(1000);
    lcd.clear();
    
    lcd.setCursor(0, 0);
    lcd.print("SAFETY LOCK");
    lcd.setCursor(0, 1);
    lcd.print("IN ACTION");
    delay(1000);
    lcd.clear();
    
    noTone(buzzer); // Stop buzzer alarm
    if (lock == false) {
      lockServo.write(90);  // Move servo to locked position
      lock = true;  // Update lock state
    }
  } 

  // Condition 3: Force Applied, No Tilt Detected
  else if (force_value >= 100 && tilt_value == 1 && button == 1) {
    for (int i = 0; i <= 5; i++) {  // Alarm buzz loop
      tone(buzzer, 1000);
      delay(500);
      noTone(buzzer);
      delay(500);
    }
    
    digitalWrite(buzzer, LOW);  
    lcd.setCursor(0, 0);
    lcd.print("PERSON DETECTED...");
    delay(1000);
    lcd.clear();
      
    lcd.setCursor(0, 0);
    lcd.print("NO LOCK MOVEMENT");
    delay(1000);
    lcd.clear();
      
    lcd.setCursor(0, 0);
    lcd.print("SAFETY LOCK");
    lcd.setCursor(0, 1);
    lcd.print("IN ACTION");
    
    if (lock == false) {
      lockServo.write(90);  // Move servo to locked position
      lock = true;  // Update lock state
    }
    
    delay(1000);
    lcd.clear();
      
    lcd.setCursor(0, 0);
    lcd.print("DOOR LOCKED FOR");
    lcd.setCursor(0, 1);
    lcd.print("SAFETY PURPOSES");
    delay(1000);
    lcd.clear();
  } 

  // Condition 4: No Movement Detected
  else {
    lcd.setCursor(0, 0);
    lcd.print("NO MOVEMENT");
    lcd.setCursor(0, 1);
    lcd.print("SAFE...");
    delay(1000);
  }
}


   
 
