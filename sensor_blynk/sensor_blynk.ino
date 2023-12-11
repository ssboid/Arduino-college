

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

 const int trigPin = D5;   
 const int echoPin = D6;   
 long duration;  
 int distance;

 BlynkTimer timer;
 void mytimer()
 {
  Blynk.virtualWrite(V2, distance);
 }
void setup()
{
  // Debug console  
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output  
 pinMode(echoPin, INPUT); // Sets the echoPin as an Input  
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100l,mytimer);
}

void loop()
{
  // Clears the trigPin  
 digitalWrite(trigPin, LOW);  
 delayMicroseconds(2);  
 // Sets the trigPin on HIGH state for 10 micro seconds  
 digitalWrite(trigPin, HIGH);  
 delayMicroseconds(10);  
 digitalWrite(trigPin, LOW);  
 // Reads the echoPin, returns the sound wave travel time in microseconds  
 duration = pulseIn(echoPin, HIGH);  
 // Calculating the distance  
 distance= duration*0.034/2;  
 // Prints the distance on the Serial Monitor  
 Serial.print("Distance: ");  
 Serial.println(distance);  
 delay(100);  
  Blynk.run();
  timer.run();
}
