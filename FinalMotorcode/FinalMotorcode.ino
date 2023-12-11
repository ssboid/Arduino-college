int ENA = 5;
int IN1 = 23;
int IN2 = 22;

int ENB = 2;  // Assuming the second motor is connected to these pins
int IN3 = 21;
int IN4 = 19;


void setup() {
    Serial.begin(115200);
    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Start the serial communication
  Serial.begin(9600);
}

void runMotors() {
    // Turn on both motors
    digitalWrite(ENA, HIGH);
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

    digitalWrite(ENB, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

    delay(2000); // Run for 2 seconds

    // Change direction for both motors
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    delay(2000); // Run for 2 seconds in the opposite direction

    // Turn off both motors
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}


// for changing the directions of motors
// Define functions to control the motors
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
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

    digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  // for going right

// ENA -- run
// ENB -- stop

   digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

    digitalWrite(ENB, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  // Stop both motors
  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
}


// test1 and test2 are for finding ena and enb
void test1(){
 digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

}

void test2(){
   digitalWrite(ENB, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}



void loop() {

  char da = Serial.read();

  

  if (da == 'w'){
    moveForward();

  } else if(da == 'a'){
    turnLeft();

  } else if(da == 'd'){
    turnRight();

  }else if (da == 's'){
    moveBackward();
  } else {
    stopMotors();
  }

delay(3000);
  // Print the received character
    Serial.print("You typed: ");
    Serial.println(da);

    // runMotors();
   
}