#include <Servo.h>
int servoPin1 = 12;
Servo myservo1;
void setup() {
  pinMode(13, OUTPUT);
  myservo1.attach(servoPin1);
}

void loop() {
  int a = digitalRead(13);
  if (a == HIGH)
  {
    for (int i = 0; i <= 180; i++) {
      myservo1.write(i);
      delay(10);

    }
    delay(40);
    for (int j = 180; j >= 0; j--) {
      myservo1.write(j);
      delay(10);
    }
  }
  else{
    
  }
}
