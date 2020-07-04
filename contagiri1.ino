#include <LiquidCrystal_I2C.h>
#include "pitches.h"
#include "themes.h"
int tRefresh = 1000;
int tSplash = 3000;
int Led = 8;
int buttonPin = 9;
int myCounter = 0;
int buzzerPin = 3;
int sensor = 13; //sensor pin
int flag = 0;
int frqSensorState = LOW;
int prevFrqSensorState = LOW;
int buttonState = LOW;
LiquidCrystal_I2C lcd(0x27, 16, 2);


void setup() {
  myinit();
  splashscreen();
}

void loop() {
  buttonState = digitalRead(buttonPin);
  frqSensorState = digitalRead(sensor); //Reads State of Input Pin
  if (frqSensorState == LOW) prevFrqSensorState = LOW; //Creates a previos state
  if (frqSensorState == HIGH && prevFrqSensorState == LOW) //Pulses Counter
  {
    myrun();
  }

  if (buttonState == HIGH) {
    reset();
  }
}

void myinit() {
  pinMode(Led, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(sensor, INPUT); //set sensor pin as input
  Serial.begin(9600);  
}

void myrun() {
  
  digitalWrite(Led, HIGH);
  prevFrqSensorState = frqSensorState;
  if(flag!=1)myCounter++;
  Serial.println(myCounter);
  lcd.setCursor(2, 0); lcd.print("GIRI ");
  lcd.print(myCounter);
  lcd.print("    ");
  flag=0;
}

void reset() {
  myCounter = 0;
  digitalWrite(Led, LOW);
  lcd.setCursor(2, 0); lcd.print("RESET\ ");
  lcd.print("    ");
  delay(tRefresh);
  digitalWrite(Led, HIGH);
  lcd.setCursor(2, 0); lcd.print("GIRI ");
  lcd.print(myCounter);
  lcd.print("    ");
}

void splashscreen() {
  lcd.begin();  // lcd 16x2
  lcd.setCursor(4, 0);
  lcd.print("contagiri");
  lcd.setCursor(0, 1);
  lcd.print("magnetico    1.0");
  delay(tSplash); // aspetta 3 secondi
  lcd.clear();
  flag=1;
}
