
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6mew721_o"
#define BLYNK_TEMPLATE_NAME "blinkmf"
#define BLYNK_AUTH_TOKEN "E8-oQd1ai7GEBoDaV4MF5pVNJ43IJO6c"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "Virinchi LAB";
char pass[] = "tech&inovation";
char auth[] = "E8-oQd1ai7GEBoDaV4MF5pVNJ43IJO6c";

float h,t;

#include "DHT.h"
#define DHTPIN 14     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

 BlynkTimer timer;
 void mytimer()
 {
  Blynk.virtualWrite(V3, t);
  Blynk.virtualWrite(V4, h);
 }
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100l,mytimer);
  dht.begin();
}

void loop()
{
  Blynk.run();
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  timer.run();
}
