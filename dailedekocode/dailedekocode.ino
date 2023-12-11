#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL09mgzGQd"
#define BLYNK_TEMPLATE_NAME "project1"
#define BLYNK_AUTH_TOKEN "qT1XpiEBwwW-U54IdimqyOfrEtFFNHsp"
#include <Arduino.h>
#if defined(ESP32)
  #include <WiFi.h>
  #include <BlynkSimpleEsp32.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
  #include <BlynkSimpleEsp8266.h>
#endif
#include <WiFiClient.h>

char auth[] = "qT1XpiEBwwW-U54IdimqyOfrEtFFNHsp";
char ssid[] = "robotics_2";
char pass[] = "CLB422BFB0";
#define IN_1  18          // L298N in1 motors Right          
#define IN_2  19          // L298N in2 motors Right          
#define IN_3  22           // L298N in3 motors Left          
#define IN_4  23
#include <ESP32Servo.h>
 const int trigPin = 14;  
 const int echoPin = 12;  
 long duration;  
 int distance;
Servo ServoX1;
int servoPin1= 13;
int serval;
void setup()
{
  // Debug console
  Serial.begin(9600);
   pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output  
 pinMode(echoPin, INPUT);
 ServoX1.attach(servoPin1);
   ServoX1.write(90);
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
    digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
  Blynk.begin(auth, ssid, pass);

}

void loop()
{  
 
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
 delay(1000);
 
 if(distance<50 && distance>10)
 {
  goAhead();
 }
else
{
  stopRobot();
}
  Blynk.run();
 
}
void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
  }

void goRight()
{
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
 }

void goBack()
{

     digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
  }

void goAhead()
{
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
  }


void stopRobot()
{  
      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, HIGH);
      digitalWrite(IN_3, HIGH );
      digitalWrite(IN_4, HIGH);

 }