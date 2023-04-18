const int trigPin = 9;  
const int echoPin = 10;
const int LED_BLINK = 13;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);
	Serial.begin(9600);
  pinMode(LED_BLINK, OUTPUT);

}

void loop() {
  digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
	Serial.println(distance);

  if(distance <= 5) {
    digitalWrite(LED_BLINK, HIGH);
  } else {
    digitalWrite(LED_BLINK, LOW);
  }
	delay(100); 

}
