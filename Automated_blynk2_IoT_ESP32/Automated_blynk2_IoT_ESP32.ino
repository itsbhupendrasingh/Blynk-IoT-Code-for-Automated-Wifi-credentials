// Repalce below credentials for your blynk 
#define BLYNK_TEMPLATE_ID "Template Name"
#define BLYNK_DEVICE_NAME "TDevice Name"
#define BLYNK_AUTH_TOKEN "Token"

#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wifi Name";
char pass[] = "Wifi Password";

#include "DHT.h"
DHT dht(13, DHT11);

BlynkTimer timer;
int led=12;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V2)
{
  int s0 = param.asInt();
  digitalWrite(led, s0);
}
void mySensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Blynk.virtualWrite(V0, h);
  Blynk.virtualWrite(V1, t);
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.println(t);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(led, OUTPUT);
  dht.begin();
  timer.setInterval(1000L, mySensor);  
}

void loop()
{
  Blynk.run();
  timer.run();
}
