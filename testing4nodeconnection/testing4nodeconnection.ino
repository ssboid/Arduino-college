// ESP8266 code
#include <ESP8266WiFi.h>

const char* ssid = "iPhone";
const char* password = "1234567890";

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    
    Serial.println("Connected to WiFi");
}

void loop() {
    // Send data to ESP32 via Serial
    Serial.println("Hello from ESP8266!");

    delay(5000); // Adjust delay as needed
}
