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

    // Turn on motors - Initial state
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    analogWrite(enA, 0);
  }

  void Move(float speed) {
    analogWrite(enA, speed);
  }

};

SonicSensor sonicSensor(12, 11);

Motor motorA(9, 8, 7);
Motor motorB(3, 4, 5);
bool left = true;
bool next_left = false;
int counter = 0;

void setup() {
    
  Serial.begin(9600);
  // This is to guarantee that the first distance is real
  delay(100);
  
}

void loop() {
    Serial.println(counter);
    float distance = sonicSensor.Sense();
    //Serial.print("Distance: ");
    if(distance < 30){
    motorA.Move(255);
    motorB.Move(255);
    delay(1000);
    }
   if (left && counter < 250) {
    motorA.Move(100);
    motorB.Move(0);
    counter++;
    if(counter == 250){
        counter = 0;
        if(next_left){
          next_left = false;
        }else{
            left = false;
            next_left = true;
        }

    }
   }else{
    motorA.Move(0);
    motorB.Move(100);
    counter++;
    if(counter == 250){
        counter = 0;
        if(!next_left){
          next_left = true;
        }else{
            left = true;
            next_left = false;
        }
      counter = 0;
      left = true;
     } 
    }
  
 
}