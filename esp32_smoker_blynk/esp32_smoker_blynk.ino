#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Stepper.h>
#include "DHT.h";
#define DHTPIN 32
#define DHTTYPE DHT11

char auth[] = "";


char ssid[] = "";
char pass[] = "";

BlynkTimer timer;

DHT dht(DHTPIN, DHTTYPE);

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
 
  int thermo = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(thermo)) {
    Serial.println("Failed to read from k-thermocouple sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V6, thermo);
}




//Stepper motor
const int stepsPerRevolution=1500;

int desirednumdberofdegrees = 90;
int numofsteps = stepsPerRevolution * 0.25;
int temp = 26; 


bool didFunction = false;
bool didFunction2 = false;

Stepper myStepper(stepsPerRevolution,12,27,14,26);

int xVal=512;

void setup() {
  myStepper.setSpeed(20);
  dht.begin();
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);


  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  
}

void loop() { 
  int thermo = dht.readTemperature();
  Blynk.run();
  timer.run();
  Serial.println(thermo);
  if(didFunction == false && thermo > temp){
  function();
  } 
  else if(didFunction2 == false && thermo < temp){
    function2();
  }
  
  if ((xVal < 500)){
    myStepper.step(1);
    delayMicroseconds(3000);
    } else if ((xVal > 550)){
    myStepper.step(-1);
    delayMicroseconds(3000);
    }
}


BLYNK_WRITE(V1){
  xVal = param[0].asInt();
  }

BLYNK_WRITE(V2){
  if( param.asInt()== 1){
    xVal = 0;
    }else{
      xVal = 512;}
  }

BLYNK_WRITE(V3){
   if( param.asInt()== 1){
    xVal = 1000;
    }else{
      xVal = 512;}
  }

  BLYNK_WRITE(V4){
    Serial.println(temp);
   temp = param.asInt();
   
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
