#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6mew721_o"
#define BLYNK_TEMPLATE_NAME "blinkmf"
#define BLYNK_AUTH_TOKEN "E8-oQd1ai7GEBoDaV4MF5pVNJ43IJO6c"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
char ssid[] = "Virinchi LAB";
char pass[] = "tech&inovation";
char auth[] = "E8-oQd1ai7GEBoDaV4MF5pVNJ43IJO6c";

int irdata;

BlynkTimer timer;

void mytimer()
{
  int invertedValue = !irdata;  // Invert the sensor value

  Blynk.virtualWrite(V6, invertedValue);
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  pinMode(12, INPUT);
  timer.setInterval(100l, mytimer);
}

void loop()                                                                                                                                                                                     
{
  irdata = digitalRead(12);
  Serial.println(irdata);
  Blynk.run();
  timer.run();
}
