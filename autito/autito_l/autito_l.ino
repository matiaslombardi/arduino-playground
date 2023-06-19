// Motor A connections
int enA = 9;
int in1 = 8;
int in2 = 7;
// Motor B connections
int enB = 3;
int in3 = 5;
int in4 = 4;
// Sensor connections
const int trigPin = 12;  
const int echoPin = 11;

// Variables for sensor
float duration, distance;  

bool first;

void setup() {
	// Set all the motor control pins to outputs
	pinMode(enA, OUTPUT);
	pinMode(enB, OUTPUT);
	pinMode(in1, OUTPUT);
	pinMode(in2, OUTPUT);
	pinMode(in3, OUTPUT);
	pinMode(in4, OUTPUT);
	
	// Turn off motors - Initial state
	digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);

    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
    Serial.begin(9600); 

    first = true;
      Serial.begin(9600);

}

void loop() {
  // From https://projecthub.arduino.cc/Isaac100/7cabe1ec-70a7-4bf8-a239-325b49b53cd4
  // It works by sending sound waves from the transmitter, which then bounce off of an object and then return to the receiver.  
  // It can determine how far away something is by the time it takes for the sound waves to get back to the sensor.
	
    digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);  
    distance = (duration*.0343)/2;  

     Serial.print("Distance: ");
	Serial.println(distance);


    if(distance < 40) {
        analogWrite(enA, 200);
        analogWrite(enB, 200);

    } else if (distance < 15) {
      analogWrite(enA, 0);
        analogWrite(enB, 0);
    }
    else {
        analogWrite(enA, 100);
        analogWrite(enB, 200);
    }

}
