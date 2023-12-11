
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
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


int relay1 = 12;  //D6 pin
BLYNK_WRITE(V0) {
  int led1 = param.asInt();
  digitalWrite(relay1, led1);
  Serial.println(led1);
}

int relay2 = 2;  //D4 pin
BLYNK_WRITE(V1) {
  int led2 = param.asInt();
  digitalWrite(relay2, led2);
  Serial.println(led2);
}

void setup() {
  // Debug console
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  digitalWrite(relay1, LOW);
  digitalWrite(relay2, LOW);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  Blynk.run();
}
