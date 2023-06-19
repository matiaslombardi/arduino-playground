// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;

const int trigPin = 11;  
const int echoPin = 10;

float duration, distance;

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
  // Set radar pins
  	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);

  Serial.begin(9600);

  digitalWrite(trigPin, LOW);


	// Turn off motors - Initial state
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);
}

void loop() {
  digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
	Serial.println(distance);
  
  checkDistance(distance);
}


void checkDistance(float dist) {
  delay(100);

  analogWrite(enA, 255);
	analogWrite(enB, 255);
  
  if (dist <= 20) {
    // Turn on motor A & B
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);

    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

  } else {
    // Turn off motors
	  digitalWrite(in1, LOW);
	  digitalWrite(in2, LOW);
	  digitalWrite(in3, LOW);
	  digitalWrite(in4, LOW);
  }
}