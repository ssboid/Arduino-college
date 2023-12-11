#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

Adafruit_MPU6050 mpu;
//18:FE:34:D9:23:AA
//32     CC:DB:A7:12:48:88
uint8_t broadcastAddress[] = {0xCC, 0xDB, 0xA7, 0x12, 0x48, 0x88};
const long interval = 1000;
unsigned long previousMillis = 0;

typedef struct struct_message {
    float accelX;
    float accelY;
    float accelZ;
    float gyroX;
    float gyroY;
    float gyroZ;
} struct_message;

struct_message sensorReadings;

struct_message incomingReadings;

void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
    Serial.print("Last Packet Send Status: ");
    if (sendStatus == 0) {
        Serial.println("Delivery success");
    } else {
        Serial.println("Delivery fail");
    }
}

// void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
//     memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
//     Serial.print("Bytes received: ");
//     Serial.println(len);

//     // Print incoming sensor readings
//     Serial.print("Incoming Acceleration X: ");
//     Serial.print(incomingReadings.accelX);
//     Serial.print(", Y: ");
//     Serial.print(incomingReadings.accelY);
//     Serial.print(", Z: ");
//     Serial.print(incomingReadings.accelZ);
//     Serial.println(" m/s^2");

//     Serial.print("Incoming Rotation X: ");
//     Serial.print(incomingReadings.gyroX);
//     Serial.print(", Y: ");
//     Serial.print(incomingReadings.gyroY);
//     Serial.print(", Z: ");
//     Serial.print(incomingReadings.gyroZ);
//     Serial.println(" rad/s");
// }

void setup() {
    Serial.begin(115200);
    while (!Serial)
        delay(10);

    Serial.println("Adafruit MPU6050 test!");

    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) {
            delay(10);
        }
    }
    Serial.println("MPU6050 Found!");

    // Initialize WiFi and ESP-NOW
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    if (esp_now_init() != 0) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);
    esp_now_register_send_cb(OnDataSent);
    esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_COMBO, 1, NULL, 0);

    // esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        // Get new sensor events with the readings
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

        // Set sensor readings
        sensorReadings.accelX = a.acceleration.x;
        sensorReadings.accelY = a.acceleration.y;
        sensorReadings.accelZ = a.acceleration.z;
        sensorReadings.gyroX = g.gyro.x;
        sensorReadings.gyroY = g.gyro.y;
        sensorReadings.gyroZ = g.gyro.z; 

        // Send sensor readings via ESP-NOW
        esp_now_send(broadcastAddress, (uint8_t *)&sensorReadings, sizeof(sensorReadings));

        // Print sensor readings
        Serial.print("Acceleration X: ");
        Serial.print(sensorReadings.accelX);
        Serial.print(", Y: ");
        Serial.print(sensorReadings.accelY);
        Serial.print(", Z: ");
        Serial.print(sensorReadings.accelZ);
        Serial.println(" m/s^2");

        Serial.print("Rotation X: ");
        Serial.print(sensorReadings.gyroX);
        Serial.print(", Y: ");
        Serial.print(sensorReadings.gyroY);
        Serial.print(", Z: ");
        Serial.print(sensorReadings.gyroZ);
        Serial.println(" rad/s");

        // Print incoming readings
        // This is now done in the OnDataRecv function
    }
}  

