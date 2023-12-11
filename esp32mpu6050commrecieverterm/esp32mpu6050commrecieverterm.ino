#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
 
const char *ssid = "ESP32-Receiver1";
const char *password = "password123";
 
WiFiServer server(80);
float Xaccel=0,Yaccel=0,Zaccel=0;
 
void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  Serial.println("Hotspot Establish");
  server.begin();
 
}
 
 
void loop() {
  WiFiClient client = server.available();
 
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();
 
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
 
    int comma1 = request.indexOf(',');
    int comma2 = request.indexOf(',', comma1 + 1);
    int comma3 = request.indexOf(',', comma2 + 1);
   // int comma4 = request.indexOf(',', comma3 + 1);
 
    Xaccel = request.substring(0, comma1).toInt(); 
    Serial.print("x: ");
    Serial.println( Xaccel);
    Yaccel = request.substring(comma1 + 1, comma2).toInt(); 
    Serial.print("y:");
     Serial.println(Yaccel);
    Zaccel = request.substring(comma2 + 1, comma3).toInt();
    Serial.print("z: ");
    Serial.println(Zaccel);
    Serial.println("");


 
  

 
  }
}