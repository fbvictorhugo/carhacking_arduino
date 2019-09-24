#include <AFMotor.h>
#include <Ultrasonic.h>


AF_DCMotor M_BACK(2);
AF_DCMotor M_FRONT(3);

Ultrasonic ultrassom(9, 10);

int LED_FRONT = A5;
int LED_BACK = A3;
int BUZZ = A0;

int data;

long distancia;

const char BTN_LED_ON = 'a';
const char BTN_LED_OFF = 'b';

const char BTN_BUZZ = 'c';

const char AXIS_UP = 'd';
const char AXIS_DOWN = 'e';
const char AXIS_LEFT_UP = 'f';
const char AXIS_LEFT_DOWN = 'g';
const char AXIS_RIGHT_UP = 'h';
const char AXIS_RIGHT_DOWN = 'i';
const char AXIS_CENTERED = 'j';

bool moveToFront = false;

void setup()
{
  Serial.begin(9600);

  pinMode(LED_FRONT, OUTPUT);
  pinMode(LED_BACK, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  M_FRONT.setSpeed(255);
  M_BACK.setSpeed(255);
}

void loop()
{

  distancia = ultrassom.Ranging(CM);
  Serial.println(distancia);

  if (Serial.available() > 0)
  {
    data = Serial.read();
    moveToFront = false;

    switch (char(data)) {
      case BTN_LED_ON:
        digitalWrite(LED_FRONT, HIGH);
        digitalWrite(LED_BACK, HIGH);
        Serial.println("LED_ON");
        break;

      case BTN_LED_OFF:
        digitalWrite(LED_FRONT, LOW);
        digitalWrite(LED_BACK, LOW);
        Serial.println("LED_OFF");
        break;

      case BTN_BUZZ:
        buzz();
        break;

      case AXIS_UP:
        moveToFront = true;
        M_BACK.run(FORWARD);
        M_FRONT.run(RELEASE);
        Serial.println("AXIS_UP");

        break;

      case AXIS_LEFT_UP:
        moveToFront = true;
        M_BACK.run(FORWARD);
        M_FRONT.run(FORWARD);
        Serial.println("AXIS_LEFT_UP");

        break;

      case AXIS_RIGHT_UP:
        moveToFront = true;
        M_BACK.run(FORWARD);
        M_FRONT.run(BACKWARD);
        Serial.println("AXIS_RIGHT_UP");
        break;

      case AXIS_LEFT_DOWN:
        M_BACK.run(BACKWARD);
        M_FRONT.run(FORWARD);
        Serial.println("AXIS_LEFT_DOWN");
        break;

      case AXIS_RIGHT_DOWN:
        M_BACK.run(BACKWARD);
        M_FRONT.run(BACKWARD);
        Serial.println("AXIS_RIGHT_DOWN");
        break;

      case AXIS_DOWN:
        M_BACK.run(BACKWARD);
        M_FRONT.run(RELEASE);
        Serial.println("AXIS_DOWN");
        break;

      case AXIS_CENTERED:
        stopMove();
        Serial.println("AXIS_CENTERED");
        break;
    }
  } else if (!isSafeToUP() && moveToFront) {
    Serial.println("NOT SAFE !!!!");
    stopMove();
  }

}

void buzz() {
  //tone(BUZZ, 440, 200); //<-- conflito com o motor
  digitalWrite(BUZZ, HIGH);
  delay(200);
  digitalWrite(BUZZ, LOW);
  Serial.println("BTN_BUZZ");
}

bool isSafeToUP() {

  if (distancia > 20) {
    return true;
  } else {
    return false;
  }
}

void stopMove() {
  M_BACK.run(RELEASE);
  M_FRONT.run(RELEASE);
}


