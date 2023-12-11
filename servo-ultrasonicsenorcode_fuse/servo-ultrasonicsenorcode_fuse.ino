#include <ESP32Servo.h>


#define SERVO_PIN 26 // ESP32 pin GPIO26 connected to servo motor

Servo servoMotor;

const int trigPin = 14;  
const int echoPin = 12;  

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;
float distanceInch;


//  ------------------------------------ultra sonic --------------------------------------------------------------------------

int ENA = 5;
int IN1 = 23;
int IN2 = 22;

int ENB = 2;  // Assuming the second motor is connected to these pins
int IN3 = 18;
int IN4 = 19;



void moveForward() {
  digitalWrite(ENA, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}

void moveBackward() {
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(ENB, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  // for going left

// ENA -- stop
// ENB -- run

  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

    digitalWrite(ENB, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  // for going right

// ENA -- run
// ENB -- stop

   digitalWrite(ENA, HIGH);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

    digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  
    digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
}




void run() {
  do {
    // Clears the trigPin
 

    moveForward();

  //   while (distanceCm >= 100) {
  //     servoMotor.write(25);

  //     if (distanceCm <= 100) {
  //       turnLeft();
  //       servoMotor.write(90);
  //     }

  //     delay(100); // Adjust the delay if needed

  //     servoMotor.write(130);

  //     if (distanceCm <= 100) {
  //       turnRight();
  //       servoMotor.write(90);
  //     } else {
  //       stopMotors();
  //     }
  //   }

  } while (distanceCm <= 100);

  servoMotor.write(25);

      if (distanceCm <= 100) {
        turnLeft();
        servoMotor.write(90);
      }

      delay(3000); // Adjust the delay if needed

      servoMotor.write(130);

      if (distanceCm <= 100) {
        turnRight();
        servoMotor.write(90);
      } else {
        stopMotors();
      }
}


void setup() {
  // put your setup code here, to run once:

    servoMotor.attach(SERVO_PIN);  // attaches the servo on ESP32 pin
  servoMotor.write(90);
  Serial.begin(115200); // Starts the serial communication
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

}

void loop() {
   digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distanceCm = duration * SOUND_SPEED / 2;

    // Prints the distance in the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

    delay(10);

while(distanceCm>50)
{
  turnLeft();
  delay(800);
   digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculate the distance
    distanceCm = duration * SOUND_SPEED / 2;

    // Prints the distance in the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

}
if(distanceCm<50 && distanceCm>10)
{
 moveForward();
Serial.println("moving forware");
}
else
{
  stopMotors() ;
  
}
}
