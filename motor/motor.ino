
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6mew721_o"
#define BLYNK_TEMPLATE_NAME "blinkmf"
#define BLYNK_AUTH_TOKEN "E8-oQd1ai7GEBoDaV4MF5pVNJ43IJO6c"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Virinchi LAB";
char pass[] = "tech&inovation";
char auth[] = "E8-oQd1ai7GEBoDaV4MF5pVNJ43IJO6c";


int servoPin1 = 12;
Servo myservo1;
BLYNK_WRITE(V8) {
  int led1 = param.asInt();
  digitalWrite(relay1, led1);
  Serial.println(led1);
}


void setup() {
  // Debug console
  myservo1.write(0);
  delay(1000);

  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
