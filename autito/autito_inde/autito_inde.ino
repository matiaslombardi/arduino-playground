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
	digitalWrite(in1, LOW);
	digitalWrite(in2, LOW);
	digitalWrite(in3, LOW);
	digitalWrite(in4, LOW);

  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);  
	Serial.begin(9600); 

  first = true;
}

void loop() {

  // Drifting
  if (first) {
    delay(1000);
    Serial.print("First: ");  
	  Serial.println(distance); 
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(enA, 210);
    analogWrite(enB, 190);
    first = false;
  }

  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  
	digitalWrite(trigPin, HIGH);  
	delayMicroseconds(10);  
	digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  
  distance = (duration*.0343)/2;  
  // Serial.print("Distance: ");  
	// Serial.println(distance); 

  // To know if the motors are on

  bool foward = digitalRead(in1) == LOW && digitalRead(in2) == HIGH && digitalRead(in3) == HIGH && digitalRead(in4) == LOW;


  // If the vehicle is closer than 10 cm to an object and the morots are on, decelerate from maximum speed to zero
  if(distance < 25) {
    if(foward) {
      analogWrite(enA, 0);
      analogWrite(enB, 0);

      Serial.println("Distance is < 25");  
	    
      //Turn motors off
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);

      delay(1000);

      // Turn motors directions
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);

      analogWrite(enA, 210);
      analogWrite(enB, 190); 
      delay(2000);
    }
  }

  // If the vehicle is farther than 10 cm to an object and the motors are off, accelerate from zero to maximum speed
	else {
    if(!foward) {
      analogWrite(enA, 0);
      analogWrite(enB, 0);

      // Trun motors off
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);

      delay(1000);

      // Turn motors directions
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);

      analogWrite(enA, 210);
      analogWrite(enB, 190);
  
      
    }
  }
}
