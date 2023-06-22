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

    // Turn on motors - Initial state
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);

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

Motor motorA(9, 8, 7);
Motor motorB(3, 4, 5);

LightSensor lightSensor(A0);

void setup() {
  Serial.begin(9600);
  // This is to guarantee that the first distance is real
  delay(100);
}

void loop() {

    int intensity = lightSensor.Sense();

    if(intensity > 300) {
        motorA.Move(200);
        motorB.Move(200);
    } else {
        motorA.Move(100);
        motorB.Move(200);
    }

}
