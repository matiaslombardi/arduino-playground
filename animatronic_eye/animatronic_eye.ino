//include library for servo
#include <Servo.h>

//define name of the servo motors
Servo upDownServo;
Servo rightLeftServo;

//define position name and value
#define left 60
#define right 120
#define middle 90
#define closed 60
#define fullOpen 160
#define halfOpen 120
#define waitTime 750

class Sweeper
{
  Servo servo;              // the servo
  int pos;              // current servo position 
  int prevPos;          // previous servo position
  int increment;        // increment to move for each interval
  int  updateInterval;      // interval between updates
  unsigned long lastUpdate; // last update of position

  int start;
  int end;

  int target;

public: 
  Sweeper(int startValue, int endValue)
  {
    start = startValue;
    end = endValue;
    target = end;
    servo.write(start);
    pos = start;
    increment = (end - start) / 5;
  }

  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }
  
  void Update()
  {
    pos += increment;
    servo.write(pos);
    if (pos >= end || pos <= start) {
      increment = -increment;
    }
    /*
    int newPos = 0.5 * pos;
    if (target == end) {
      newPos += 0.5 * target;
    } else {
      newPos -= 0.5 * target;
    }
    pos = increment;
    servo.write(pos);
    if (pos >= end) {
      target = start;
    } else if(pos <= start) {
      target = end;
    }
    */

  }
};

Sweeper upDown(60, 160);
Sweeper rightLeft(20, 120);

void setup() {
  //define pin numbers of the servo motors
  //upDownServo.attach(6);
  //rightLeftServo.attach(5);
  //starting position of the servo motors
  //delay(10);
  //upDownServo.write(closed);
  //rightLeftServo.write(middle);

  upDown.Attach(6);
  rightLeft.Attach(5);
}

void loop() {
  upDown.Update();
  delay(1000);
  // TODO: change to millis
  rightLeft.Update();
  
  /*
  delay(1000);
  upDownServo.write(halfOpen);
  delay(waitTime);
  rightLeftServo.write(right);
  delay(waitTime);
  rightLeftServo.write(left);
  delay(waitTime);
  rightLeftServo.write(middle);

  delay(1000);
  upDownServo.write(closed);
  delay(waitTime);
  upDownServo.write(fullOpen);
  delay(waitTime);
  upDownServo.write(closed);
  delay(waitTime);
  upDownServo.write(fullOpen);
  delay(waitTime);
  rightLeftServo.write(right);
  delay(waitTime);
  rightLeftServo.write(left);
  delay(waitTime);
  rightLeftServo.write(middle);
  upDownServo.write(halfOpen);
  delay(waitTime);
  rightLeftServo.write(right);
  delay(waitTime);
  rightLeftServo.write(left);
  delay(waitTime);
  rightLeftServo.write(middle);
  delay(waitTime);
  upDownServo.write(fullOpen);
  delay(waitTime);
  upDownServo.write(halfOpen);
  delay(waitTime);
  upDownServo.write(fullOpen);
  delay(waitTime);
  rightLeftServo.write(right);
  delay(waitTime);
  rightLeftServo.write(left);
  delay(waitTime);
  rightLeftServo.write(middle);
  */
}
