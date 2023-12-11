#include <ESP8266WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <espnow.h>
uint8_t broadcastAddress[] = {0x48, 0x55, 0x19, 0xDF, 0xF4, 0x55};
float incomingTemp;
float incomingHum;
const long interval = 10000; 
unsigned long previousMillis = 0;   
String success;
typedef struct struct_message {
    float temp;
    float hum;
    float temp1;
    float hum1;
    float temp2;
    float hum2;
} struct_message;

// Create a struct_message called DHTReadings to hold sensor readings
struct_message DHTReadings;

// Create a struct_message to hold incoming sensor readings
struct_message incomingReadings;

// Callback when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Last Packet Send Status: ");
  if (sendStatus == 0){
    Serial.println("Delivery success");
  }
  else{
    Serial.println("Delivery fail");
  }
}

// Callback when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
  Serial.print("Bytes received: ");
  Serial.println(len);
  incomingTemp = incomingReadings.temp;
  incomingHum = incomingReadings.hum;
}



void printIncomingReadings(){
  // Display Readings in Serial Monitor
  Serial.println("INCOMING READINGS");
  Serial.print("Temperature: ");
  Serial.print(incomingTemp);
  Serial.println(" ºC");
  Serial.print("Humidity: ");
  Serial.print(incomingHum);
  Serial.println(" %");
}
 
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Set ESP-NOW Role
  esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
  esp_now_register_send_cb(OnDataSent);
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);
  
  // Register for a callback function that will be called when data is received
  esp_now_register_recv_cb(OnDataRecv);
}
 
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you updated the DHT values
    previousMillis = currentMillis;

    //Set values to send
    DHTReadings.temp = 22;
    DHTReadings.hum = 33;
     DHTReadings.temp1= 232;
    DHTReadings.hum1 = 53;
     DHTReadings.temp2 = 2112;
    DHTReadings.hum2 = 331;

    // Send message via ESP-NOW
    esp_now_send(broadcastAddress, (uint8_t *) &DHTReadings, sizeof(DHTReadings));

    // Print incoming readings
    printIncomingReadings();
  }
}
