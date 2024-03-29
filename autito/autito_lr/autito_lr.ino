class SonicSensor {
  int trigPin;
  int echoPin;
  float distance, threshold;
  unsigned long prevMillis;
  bool sentPulse;
  
  public:
  SonicSensor(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
    sentPulse = false;
    prevMillis = millis();

    // In case it doesn't sense anything for the first loop
    distance = 100;

    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    digitalWrite(trigPin, LOW);
  };

  float Sense() {
      if (!sentPulse) {
        digitalWrite(trigPin, HIGH);
        sentPulse = true;
      }
      
      long currentMillis = millis();
      if (sentPulse && (currentMillis - prevMillis) >= 100) {
          digitalWrite(trigPin, LOW);
          float duration = pulseIn(echoPin, HIGH);
          distance = (duration*.0343)/2;

          sentPulse = false;
          prevMillis = currentMillis;
      }
      //Serial.print("Distance: ");
      //Serial.println(distance);
      return distance;
  }
};

class Motor {
  int enA;
  int in1;
  int in2;

  public:
  Motor(int newEn, int newIn1, int newIn2) {
    enA = newEn;
    in1 = newIn1;
    in2 = newIn2;

    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    analogWrite(enA, 0);
  }

  void Move(float speed) {
    analogWrite(enA, speed);
  }

};

class LightSensor {
  int pResistor;
  int intensity;

  public:
  LightSensor(int newResistor) {
    pResistor = newResistor;
    pinMode(pResistor, INPUT);
  }

  int Sense() {
    intensity = analogRead(pResistor);
    return intensity;
  }
};

SonicSensor sonicSensor(12, 11);

Motor motorA(9, 8, 7);
Motor motorB(3, 4, 5);

LightSensor leftSensor(A0);

LightSensor rightSensor(A1);

void setup() {
  Serial.begin(9600);
  // This is to guarantee that the first distance is real
  delay(100);
}

void loop() {
  float dist = sonicSensor.Sense();
  float left = leftSensor.Sense();
  float right = rightSensor.Sense();
  if (dist < 20) {
    motorA.Move(255);
    motorB.Move(255);
  } else {
    if (left > 500 || right > 500) {
      if (abs(left - right) < 100) {
        motorA.Move(255);
        motorB.Move(255);
      } else if (left > right) {
        motorA.Move(255);
        motorB.Move(0);
        //motorB.Move(255 * 0.5);
      } else {
        motorA.Move(0);
        motorB.Move(255);
      }
    } else {
      motorA.Move(0);
        motorB.Move(0);
    }
  }

  Serial.print("Left: ");
  Serial.println(left);
  Serial.print("Right: ");
  Serial.println(right);
}
