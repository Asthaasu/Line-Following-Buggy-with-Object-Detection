const int ledPin = 9;
const int trigPin = 13;
const int echoPin = 12;
int pin = 4;

long duration;
int distanceCm, distanceInch;
unsigned value;
long st = millis();
int count = 0;
int flag = 0;

// Motor control pins
const int motorPin1 = 5;
const int motorPin2 = 6;
const int motorPin3 = 7;
const int motorPin4 = 8;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  for (int i = 5; i < 9; i++) {
    pinMode(i, OUTPUT);
  }

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(pin, INPUT);

  Serial.begin(9600);
}

void stop() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void forward() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void backward() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
}

void left() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

void right() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
}

void loop() {
  if (Serial.read() == 'Q' || flag == 1) {
    flag = 1;

    // Distance measurement
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);
    distanceCm = (duration * 0.0343) / 2;

    // Obstacle check
    if (distanceCm <= 20) {
      stop();
      delay(1000);
    } else {
      forward();
    }

    // Gantry check
    if (digitalRead(pin) > 0) {
      value = pulseIn(pin, HIGH);
      Serial.print("Value = ");
      Serial.println(value);
      if (value > 2500 && value < 4000) {
        Serial.println("Gantry 1 Crossed");
        stop();
        delay(500);
      }
    }

    // IR sensors logic
    int r = digitalRead(A0);
    int l = digitalRead(A1);

    if (l == 1 && r == 1) {
      forward();
    } else if (l == 1 && r == 0) {
      left();
    } else if (l == 0 && r == 1) {
      right();
    } else {
      long endt = millis();
      if (endt - st > 500) {
        count++;
        Serial.print("Group 1 count = ");
        Serial.println(count);
        st = millis();
      }

      switch (count) {
        case 0:
        case 1:
          forward();
          break;
        case 2:
          right();
          break;
        case 3:
        case 4:
          forward();
          break;
        case 5:
          right();
          break;
        case 6:
          forward();
          break;
        case 7:
          stop();     // Stop when count reaches 7
          flag = 0;   // Reset flag to stop further execution
          break;
      }
    }
  }
}