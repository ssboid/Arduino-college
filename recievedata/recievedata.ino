#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <espnow.h>

Adafruit_MPU6050 mpu;

// A4:CF:12:C6:2C:F3

// int ENA = 4;

// int IN1 = 0;

// int IN2 = 2;


int ENA = 2;

int IN1 = 3;

int IN2 = 4;

// Ena d5
// in1 d3
// int2 d4
// in3 d7 
// in4 d8 
// end d6


uint8_t broadcastAddress[] = {0xA4, 0xCF, 0x12, 0xC6, 0x2C, 0xF3};
const long interval = 10000;
unsigned long previousMillis = 0;

float velocity_x = 0.0;
float velocity_y = 0.0;
float velocity_z = 0.0;

float position_x = 0.0;
float position_y = 0.0;
float position_z = 0.0;

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

void OnDataRecv(uint8_t *mac, uint8_t *incomingData, uint8_t len) {
    memcpy(&incomingReadings, incomingData, sizeof(incomingReadings));
    Serial.print("Bytes received: ");
    Serial.println(len);

    // Print incoming sensor readings
    Serial.print("Incoming Acceleration X: ");
    Serial.print(incomingReadings.accelX);
    Serial.print(", Y: ");
    Serial.print(incomingReadings.accelY);
    Serial.print(", Z: ");
    Serial.print(incomingReadings.accelZ);
    Serial.println(" m/s^2");

    Serial.print("Incoming Rotation X: ");
    Serial.print(incomingReadings.gyroX);
    Serial.print(", Y: ");
    Serial.print(incomingReadings.gyroY);
    Serial.print(", Z: ");
    Serial.print(incomingReadings.gyroZ);
    Serial.println(" rad/s");

/* Calculate the velocity using integration */
  float dt = 0.5; // Sample time in seconds (adjust as needed)  incomingReadings.accelX
  // velocity_x += a.acceleration.x * dt;  
  velocity_x += incomingReadings.accelX * dt;  
  velocity_y += incomingReadings.accelY * dt;
  velocity_z += incomingReadings.accelZ * dt;

  /* Calculate the position using integration */
  position_x += velocity_x * dt;
  position_y += velocity_y * dt;
  position_z += velocity_z * dt;

   Serial.print("Velocity X: ");
  Serial.print(velocity_x);
  Serial.print(", Y: ");
  Serial.print(velocity_y);
  Serial.print(", Z: ");
  Serial.print(velocity_z);
  Serial.println(" m/s");

  Serial.print("Position X: ");
  Serial.print(position_x);
  Serial.print(", Y: ");
  Serial.print(position_y);
  Serial.print(", Z: ");
  Serial.print(position_z);
  Serial.println(" meters");

  Serial.println("");
  delay(100);


}

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

    esp_now_register_recv_cb(OnDataRecv);


    // set all the motor control pins to outputs

pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);


}


// this is for testing motors
// this function will run the motors in both directions at a fixed speed

void testOne() {

// turn on motor

digitalWrite(ENA, HIGH); // set speed to 200 out of possible range 0~255
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);

delay(2000); // now change motor directions

digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);

delay(2000); // now turn off motors

digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
}

// this function will run the motors across the range of possible speeds

// note that maximum speed is determined by the motor itself and the operating voltage
// the PWM values sent by analogWrite() are fractions of the maximum speed possible by your hardware

void testTwo() {

// turn on motors

digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);

// accelerate from zero to maximum speed

for (int i = 0; i < 256; i++)

{
    analogWrite(ENA, i);
    delay(50);
}

// decelerate from maximum speed to zero

for (int i = 255; i >= 0; --i)
{
      analogWrite(ENA, i);
      delay(50);
}

// now turn off motors

digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
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

        // // Print sensor readings
        // Serial.print("Acceleration X: ");
        // Serial.print(sensorReadings.accelX);
        // Serial.print(", Y: ");
        // Serial.print(sensorReadings.accelY);
        // Serial.print(", Z: ");
        // Serial.print(sensorReadings.accelZ);
        // Serial.println(" m/s^2");

        // Serial.print("Rotation X: ");
        // Serial.print(sensorReadings.gyroX);
        // Serial.print(", Y: ");
        // Serial.print(sensorReadings.gyroY);
        // Serial.print(", Z: ");
        // Serial.print(sensorReadings.gyroZ);
        // Serial.println(" rad/s");



        // Print incoming readings
        // This is now done in the OnDataRecv function

        testOne();   
	// delay(1000);   
  	// testTwo();   
  	// delay(1000);
    }
}