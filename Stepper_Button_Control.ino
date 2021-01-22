#include <Stepper.h>

//Stepper motor
int stepsPerRevolution=2048;
int motSpeed=3;
int dt=500;

//Button
int motDir=1;         //motor direction5
int buttonPin=2;

int buttonValNew;     //present state of the button
int buttonValOld=1;   //not pressed

Stepper myStepper(stepsPerRevolution,8,10,9,11);

void setup() {
  Serial.begin(9600);
  myStepper.setSpeed(motSpeed);
  pinMode(buttonPin, INPUT);
//  pinMode(buttonPin, OUTPUT); 
  digitalWrite(buttonPin, HIGH);     //  Puts 5v on it..
}

void loop() {
buttonValNew=digitalRead(buttonPin);
if (buttonValOld==1 && buttonValNew==0) {
  motDir=motDir*(-1);
  }
 
//else {
//  (buttonValOld==1 && buttonValNew==0); 
//  motDir=motDir*(0);
//}
  myStepper.step(motDir*1);
}
