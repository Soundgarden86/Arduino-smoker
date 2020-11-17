#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "max6675.h";

// Blynk auth key
char auth[] = "";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "";
char pass[] = "";

// Pins
int ktcSO = 16;
int ktcCS = 17;
int ktcCLK = 18;

MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
 
  float t = ktc.readCelsius(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(t)) {
    Serial.println("Failed to read from k-thermocouple sensor!");
    return;
  }
  
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
