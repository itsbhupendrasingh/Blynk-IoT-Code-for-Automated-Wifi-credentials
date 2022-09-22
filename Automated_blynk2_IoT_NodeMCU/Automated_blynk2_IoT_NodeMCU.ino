// Repalce below credentials for your blynk 
#define BLYNK_TEMPLATE_ID "Template ID"
#define BLYNK_DEVICE_NAME "DeviceID"
#define BLYNK_AUTH_TOKEN "Token"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Baba home";
char pass[] = "home@baba";

#include "DHT.h"
DHT dht(D2, DHT11);

BlynkTimer timer;
int led=D5;

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
