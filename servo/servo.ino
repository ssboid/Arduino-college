#include <Servo.h>
int servoPin1=12;
Servo myservo1;
void setup() {
  pinMode(2,OUTPUT);
  myservo1.attach(servoPin1);
}

void loop() {
  for(int i=0; i<=180; i++){
    myservo1.write(i);
    if (i==90){
      
      digitalWrite(2,LOW);
      delay(100);
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
      delay(100);
      digitalWrite(2,HIGH);
      delay(100);
    }
    else{
      digitalWrite(2,HIGH);
    }
    delay(10);
    
  }
  delay(40);
  for(int j=180; j>=0; j--){
    myservo1.write(j);
    if (j==90){
      
      digitalWrite(2,LOW);
      delay(100);
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
      delay(100);
      digitalWrite(2,HIGH);
      delay(100);
    }
    else{
      digitalWrite(2,HIGH);
    }
    
    delay(10);
  }

}
