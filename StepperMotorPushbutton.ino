/*
  Stepper Motor Demonstration 1
  StepperMotor.ino
  Demonstrates 28BYJ-48 Unipolar Stepper with ULN2003A Driver
  Uses Arduino Stepper Library

  BluIcedPen 2018
  https://www.linkedin.com/in/blueicedpen/
*/ 

//Include the Arduino Stepper Library
#include <Stepper.h>

// Define Constants

// Number of steps per internal motor revolution 
const float STEPS_PER_REVOLUTION = 32; 

//  Amount of Gear Reduction
const float GEAR_REDUCTION = 64;

// Number of steps per geared output rotation
const float STEPS_PER_OUT_REV = STEPS_PER_REVOLUTION * GEAR_REDUCTION;

// Define Variables

// Number of Steps Required
int StepsRequired;
int switchPin = 7;
//Extra Boolean variables to keep track of button and motor state
boolean current = LOW;
boolean last = LOW;
boolean isOpen = LOW;

// Create Instance of Stepper Class
// Specify Pins used for motor coils
// The pins used are 8,9,10,11 
// Connected to ULN2003 Motor Driver In1, In2, In3, In4 
// Pins entered in sequence 1-3-2-4 for proper step sequencing

Stepper steppermotor(STEPS_PER_REVOLUTION, 8, 10, 9, 11);

void setup()
{
// Nothing  (Stepper Library sets pins as outputs)
  pinMode(switchPin, INPUT);
}
//Corrects push button bounce (not the best debounce function)
boolean debounce(boolean inLast){
  boolean inCurrent = digitalRead(switchPin);
  if(inLast != current){
    delay(5);
    inCurrent = digitalRead(switchPin);
  }
  return inCurrent;
}

void garageAction(float factor){
  // Slow - 4-step CW sequence to observe lights on driver board
  
   // Rotate CW 1/2 turn slowly
  StepsRequired  =  STEPS_PER_OUT_REV*factor; 
//   This will make your steppermotor move slower or faster.
  steppermotor.setSpeed(1000);   
  steppermotor.step(StepsRequired);
  
  
  if(isOpen == LOW){
    delay(10000);
  }else if(isOpen == HIGH){
    delay(15);
  }
}

void loop()
{
  current = debounce(last);
  if(current == HIGH && last == LOW && isOpen == LOW){
    garageAction(2);
    isOpen = !isOpen;
  }
  if(current == HIGH && last == LOW && isOpen == HIGH){
    garageAction(-2);
    isOpen = !isOpen;
  }
}
