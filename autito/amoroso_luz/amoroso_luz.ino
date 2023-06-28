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

    analogWrite(enA, 255);
  }

  void Move(float light) {
    if (light >= 100) {
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

Motor motorA(9, 8, 7);
Motor motorB(3, 4, 5);

LightSensor lightSensor(A0);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int light = lightSensor.Sense();
  motorA.Move(light);
  motorB.Move(light);
}
