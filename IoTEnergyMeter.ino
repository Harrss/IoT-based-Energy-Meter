#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "xxxxxxxxxxxxx"
#define BLYNK_TEMPLATE_NAME "xxxxxxxxxxxxx"
#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxx"

#include "EmonLib.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
EnergyMonitor emon;
#define vCalibration 106.8
#define currCalibration 0.52

BlynkTimer timer;

char auth[] = "xxxxxxx";
char ssid[] = "xxxxxxx";
char pass[] = "xxxxxxxx";



float kWh = 0;
unsigned long lastmillis = millis();
void myTimerEvent() {
emon.calcVI(20, 2000);
 Serial.print("Vrms: ");
Serial.print(emon.Vrms, 2);
Serial.print("V");
Blynk.virtualWrite(V0, emon.Vrms);
Serial.print("\tIrms: ");
Serial.print(emon.Irms, 4);
Serial.print("A");
Blynk.virtualWrite(V1, emon.Irms);
Serial.print("\tPower: ");
Serial.print(emon.apparentPower, 4);
Serial.print("W");
 Blynk.virtualWrite(V2, emon.apparentPower);
 Serial.print("\tkWh: ");
kWh = kWh + emon.apparentPower*(millis()-lastmillis)/3600000000.0;
Serial.print(kWh, 4);
Serial.println("kWh");
lastmillis = millis();
Blynk.virtualWrite(V3, kWh);
}
void setup() {
Serial.begin(9600);
 emon.voltage(35, vCalibration, 1.7); 
 emon.current(34, currCalibration); 
 Blynk.begin(auth, ssid, pass);
 timer.setInterval(5000L, myTimerEvent);
}

void loop() {
 Blynk.run();
 timer.run();
}