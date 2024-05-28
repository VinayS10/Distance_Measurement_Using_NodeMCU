const int trigPin = D3;
const int echoPin = D0;
const int buzzer = D8;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

long duration;
int distance; 
int safetyDistance;

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output 
  pinMode(echoPin, INPUT);   // Sets the echoPin as an Input 
  pinMode(buzzer, OUTPUT);   // Sets the buzzer as an Output
  lcd.begin();
  lcd.backlight(); 
  
  Serial.begin(9600);       // Starts the serial communication

  lcd.backlight(); // Turn on the backlight
}

void loop() {
  // Sets trigPin HIGH
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(100); 
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  // Calculating distance
  distance = (duration / 2) / 29.1;
  
  Serial.print(distance);
  Serial.println("CM");
  delay(300);
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  safetyDistance = distance;
  
  // Display distance on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance(cm):");
  
  lcd.setCursor(0, 1);
  lcd.print(distance);

  // Sound buzzer if distance is less than or equal to 5
  if (safetyDistance <= 10) {
    digitalWrite(buzzer, HIGH);
    delay(100);
  } else {
    digitalWrite(buzzer, LOW);
  }
}
