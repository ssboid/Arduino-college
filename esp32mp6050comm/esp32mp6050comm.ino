#include <WiFi.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
Adafruit_MPU6050 mpu;
 
 
const char *ssid = "ESP32-Receiver1"; // Change to the receiver's SSID
const char *password = "password123";   // Change to the receiver's password
 
const char *receiverIP = "192.168.4.1"; // IP address of the receiver
 
WiFiClient client;
 
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
 
  Serial.println("Connected to WiFi");
  while (!Serial)
  delay(10); // will pause Zero, Leonardo, etc until serial console opens
 
Serial.println("Adafruit MPU6050 test!");
 
// Try to initialize!
if (!mpu.begin()) {
  Serial.println("Failed to find MPU6050 chip");
  while (1) {
    delay(10);
  }
}
Serial.println("MPU6050 Found!");
 
Serial.println("");
delay(100);
}
 
void loop() {
  client = WiFiClient();
 
  if (client.connect(receiverIP, 80)) {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
 
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");
  Serial.println("");
  delay(500);
 
  client.print(a.acceleration.x);
  client.print(",");
  client.print(a.acceleration.y);
  client.print(",");
  client.print(a.acceleration.z);
  client.stop();
  }
 
  delay(10); // Adjust delay if needed
}