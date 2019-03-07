
#include <AFMotor.h>

AF_DCMotor M_FRONT(3);
AF_DCMotor M_BACK(2);

int LED_FRONT = A5;
int LED_BACK = A3;
int BUZZ = A0;

int data;

void setup()
{
  Serial.begin(9600);

  pinMode(LED_FRONT, OUTPUT);
  pinMode(LED_BACK, OUTPUT);
  pinMode(BUZZ, OUTPUT);

  M_BACK.setSpeed(255);
}

void loop()
{

  /*
    motor.run(FORWARD); //Gira o motor sentido horario
    delay(5000);
    motor.run(RELEASE); //Desliga o motor

    delay(5000);
    motor.run(BACKWARD); //Gira o motor sentido horario
    delay(5000);
    motor.run(RELEASE); //Desliga o motor
    delay(5000);
  */

  if (Serial.available() > 0)
  {
    data = Serial.read();
    Serial.print(data);
    Serial.print("\n");
    if (data == '1')         {
      digitalWrite(LED_FRONT, HIGH);
      digitalWrite(LED_BACK, HIGH);
    }  else if (data == '0') {
      digitalWrite(LED_FRONT, LOW);
      digitalWrite(LED_BACK, LOW);
    } else if (data == '2') {
      tone(BUZZ, 2000);
      delay(100);
      noTone(BUZZ);
    } else if (data == '5')   {
      M_BACK.run(FORWARD);
    }    else if (data == '6') {
      M_BACK.run(BACKWARD);
    } else if (data == '7') {
      M_BACK.run(RELEASE);
    }
  }
}
