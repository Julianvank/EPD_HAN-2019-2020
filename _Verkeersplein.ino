#include <Servo.h>

void setup() {
  Serial.begin(9600);
  buttonControlSetup();
  ledControlSetup();
  segmentDisplaySetup();
  verkeerspleinMainSetup();
  servoControlSetup();
}

void loop() {
  verkeerspleinMainLoop();
  buttonControlLoop();

}
