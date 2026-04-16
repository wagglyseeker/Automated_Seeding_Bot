#include <Servo.h>
#include <SoftwareSerial.h>

// Servo objects
Servo DRILL1;
Servo DRILL2;
Servo SEEDER;
Servo FLAP;

// Motor control pins
const int m1 = 4;
const int m2 = 5;
const int m3 = 6;
const int m4 = 7;

// Servo positions
int pos = 0;
int posf = 0;

// Motor pump control pins
const int mp = 12;
const int mn = 13;

// Moisture sensor pins
const int pinD0 = 1;
const int pinA0 = A0;
const int motorPin = 0;

// Sensor values
int A0value = 0;
int D0value = 0;

// Incoming serial value
char Incoming_value = 0;

// Software serial for Bluetooth communication (using pins 2 and 3)
SoftwareSerial BTSerial(2, 3); // RX, TX

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
  
  // Start Bluetooth serial communication
  BTSerial.begin(9600);

  // Attach servos
  DRILL1.attach(8);
  DRILL2.attach(9);
  SEEDER.attach(10);
  FLAP.attach(11);

  // Initialize servo positions
  DRILL1.write(0);
  DRILL2.write(180);
  SEEDER.write(0);
  FLAP.write(0);

  // Set pin modes
  pinMode(mp, OUTPUT);
  pinMode(mn, OUTPUT);
  pinMode(pinD0, INPUT);
  pinMode(pinA0, INPUT);
  pinMode(motorPin, OUTPUT);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);

  // Initialize Bluetooth module
  BTSerial.println("Bluetooth Ready");  // Signal that Bluetooth is ready
}

void loop() {
  // Read moisture sensor values at intervals
  static unsigned long lastSensorReadTime = 0;
  unsigned long currentTime = millis();

  if (currentTime - lastSensorReadTime > 1000) {
    lastSensorReadTime = currentTime;
    readMoistureSensor();
  }

  // Check for incoming Bluetooth data
  if (BTSerial.available() > 0) {
    Incoming_value = BTSerial.read();
    Serial.print("Received: ");
    Serial.println(Incoming_value);

    handleIncomingValue(Incoming_value);
  }

  delay(1000);  // Add a delay to avoid flooding the serial monitor
}

// Function to handle incoming values
void handleIncomingValue(char value) {
  switch (value) {
    case '1':
      moveForward();
      break;
    case '2':
      moveBackward();
      break;
    case '3':
      turnRight();
      break;
    case '4':
      turnLeft();
      break;
    case '5':
      stopMovement();
      break;
    case '6':
      drill();
      break;
    case '7':
      seed();
      break;
    case 'A':
      seed2();
      break;
    case '9':
      controlPump();
      break;
    case '8':
      operateFlapup();
      break;
    case 'B':
      automatedSequence();
      break;
    case 'C':
      automatedSequence2();
      break;
  }
}

// Function to read moisture sensor values
void readMoistureSensor() {
  A0value = analogRead(pinA0);   // Analog read for moisture level
  D0value = digitalRead(pinD0);  // Digital read for moisture threshold
  Serial.print("Moisture level: ");
  Serial.print(A0value);
  Serial.print(", Digital read: ");
  Serial.println(D0value);
}

// Movement functions
void moveForward() {
  setMotorState(HIGH, LOW, LOW, HIGH);
  Serial.println("Moving Forward");
}

void moveBackward() {
  setMotorState(LOW, HIGH, HIGH, LOW);
  Serial.println("Moving Backward");
}

void turnRight() {
  setMotorState(LOW, LOW, HIGH, LOW);
  Serial.println("Turning Right");
}

void turnLeft() {
  setMotorState(LOW, HIGH, LOW, LOW);
  Serial.println("Turning Left");
}

void stopMovement() {
  setMotorState(LOW, LOW, LOW, LOW);
  Serial.println("Stopped");
}

// Set motor state function
void setMotorState(int state1, int state2, int state3, int state4) {
  digitalWrite(m1, state1);
  digitalWrite(m2, state2);
  digitalWrite(m3, state3);
  digitalWrite(m4, state4);
}

// Drill functions
void drill() {
  Serial.println("Drilling");
  operateDrill(45, 5, 1500);
}

void drill2() {
  Serial.println("Drilling");
  operateDrill(45, 5, 6000);
}

void operateDrill(int targetPos, int delayTime, int holdTime) {
  for (pos = 0; pos <= targetPos; pos += 1) {
    DRILL1.write(pos);
    DRILL2.write(180 - pos);
    delay(delayTime);
    digitalWrite(mn, LOW);
    digitalWrite(mp, HIGH);
  }
  delay(holdTime);
  for (pos = targetPos; pos >= 0; pos -= 1) {
    DRILL1.write(pos);
    DRILL2.write(180 - pos);
    delay(delayTime - 1);
    digitalWrite(mp, LOW);
    digitalWrite(mn, LOW);
  }
}

// Pump control functions
void controlPump() {
  Serial.print("Moisture level: ");
  Serial.print(A0value);
  Serial.print(", Digital read: ");
  Serial.println(D0value);

  Serial.println("Moisture level is 400 or above. Motor ON.");
  digitalWrite(motorPin, HIGH);
  delay(5000);
  digitalWrite(motorPin, LOW);
  Serial.println("Pump is running");
}

void controlPump2() {
  readMoistureSensor();
  Serial.println("Moisture level is 400 or above. Motor ON.");
  digitalWrite(motorPin, HIGH);
  Serial.println("Pump is running");

  if (D0value == 0) {
    Serial.println("Moisture level is below 400. Motor OFF.");
    digitalWrite(11, LOW);
  } else if (D0value == 1) {
    Serial.println("Moisture level is 400 or above. Motor ON.");
    digitalWrite(11, HIGH);
    delay(3000);
    digitalWrite(11, LOW);
  }
}

// Seeding functions
void seed() {
  Serial.println("Seeding 1st Type");
  operateSeeder(90, 500);
}

void seed2() {
  Serial.println("Seeding 2nd Type");
  operateSeeder(180, 300);
}

void operateSeeder(int targetPos, int delayTime) {
  SEEDER.write(targetPos);
  delay(delayTime);
  SEEDER.write(0);
  delay(1000);
}

// Flap operation functions
void operateFlapup() {
  Serial.println("Flap Operation");
  operateFlap(35, 10);
}

void operateFlapdown() {
  Serial.println("Flap Operation");
  operateFlap(0, 10);
}

void operateFlap(int targetPos, int delayTime) {
  for (posf = 0; posf <= targetPos; posf += 1) {
    FLAP.write(posf);
    delay(delayTime);
  }
}

// Automated sequences
void automatedSequence() {
  Serial.println("Automated Sequence Start");

  drill();
  moveForward();
  delay(1350);
  stopMovement();
  seed();
  FLAP.write(35);
  controlPump();
  moveForward();
  delay(1500);
  stopMovement();
  FLAP.write(0);

  Serial.println("Automated Sequence End");
}

void automatedSequence2() {
  Serial.println("Automated Sequence 2nd Start");

  drill2();
  moveForward();
  delay(1500);
  stopMovement();
  seed2();
  operateFlapup();
  controlPump2();
  moveForward();
  delay(1500);
  stopMovement();
  delay(6500);
  operateFlapdown();

  Serial.println("Automated Sequence 2nd End");
}
