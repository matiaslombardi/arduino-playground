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

    // TODO: check what to do for the first time with distance
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
      Serial.print("Distance: ");
      Serial.println(distance);
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

    // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);

    // TODO: this is speed, maybe change it depending on the robot
    analogWrite(enA, 255);
  }

  // TODO: maybe receive speed or direction, this method should change behaviour depending on the vehicle
  void Move(float dist) {
    if (dist <= 20) {
      // Turn on motor
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    } else {
      // Turn off motor
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
    }
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

SonicSensor sonicSensor(11, 10);

Motor motorA(9, 8, 7);
Motor motorB(3, 4, 5);

LightSensor lightSensor(A0);

void setup() {
  Serial.begin(9600);
  // This is to guarantee that the first distance is real
  delay(100);
}

void loop() {
  float dist = sonicSensor.Sense();
  motorA.Move(dist);
  motorB.Move(dist);

  Serial.print("Light: ");
  Serial.println(lightSensor.Sense());
}
