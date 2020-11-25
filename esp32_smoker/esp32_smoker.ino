#include <Stepper.h>
#include "DHT.h";
#define DHTPIN 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);


//Stepper motor
const int stepsPerRevolution=1500;

int desirednumdberofdegrees = 90;
int numofsteps = stepsPerRevolution * 0.25;
int temp = 26; 


bool didFunction = false;
bool didFunction2 = false;

Stepper myStepper(stepsPerRevolution,12,27,14,26);

void setup() {
  myStepper.setSpeed(20);
  dht.begin();
  Serial.begin(9600);
  
}

void loop() { 
  float thermo = dht.readTemperature();
  Serial.println(thermo);
  if(didFunction == false && thermo > 23){
  function();
  } 
  if(didFunction2 == false && thermo < 23){
    function2();
  }
  delay(500);
}

void function() {
  //turn motor 90degrees clockwise "Funtion"
  myStepper.step(numofsteps);
  didFunction = true;
  didFunction2 = false;
  delay(500);
  }

void function2() {
    //turn motor 90degrees counterclockwise "Funtion2"
    myStepper.step(-numofsteps);
    didFunction2 = true;
    didFunction = false;
    delay(500);
  }  
    

    
