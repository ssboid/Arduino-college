#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
const char* ssid = "Exodia Contagion";  // Enter SSID here
const char* password = "9999redcrits";  //Enter Password here

ESP8266WebServer server(80);
uint8_t LEDpin = D4;
bool LEDstatus = LOW;
void setup() {
  Serial.begin(9600);
  pinMode(LEDpin, OUTPUT);
   WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  delay(100);
  
  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  server.handleClient();
  if(LEDstatus)
  digitalWrite(LEDpin, HIGH);
  else
  digitalWrite(LEDpin, LOW);
}

void handle_OnConnect() 
{
  LEDstatus = LOW;
  server.send(200, "text/html", SendHTML(false)); 
}
void handle_ledon()
{
  LEDstatus = HIGH;
  server.send(200, "text/html", SendHTML(true)); 
}
void handle_ledoff()
{
  LEDstatus = LOW;
  server.send(200, "text/html", SendHTML(false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led){
  String ptr = "<!DOCTYPE html>\n";
  ptr +="<html>\n";
  ptr +="<head>\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>LED</h1>\n";
  ptr +="<p>Click to switch LED on and off.</p>\n";
  ptr +="<form method=\"get\">\n";
  if(led)
  ptr +="<input type=\"button\" value=\"LED OFF\" onclick=\"window.location.href='/ledoff'\">\n";
  else
  ptr +="<input type=\"button\" value=\"LED ON\" onclick=\"window.location.href='/ledon'\">\n";
  ptr +="</form>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
