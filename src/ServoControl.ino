int servoPin = 3;
Servo servo;
int slagboomHoek;
int slagboomOpen = 180;
int slagboomGesloten = 90;
int slagboomSnelheid = 50;

unsigned long int previousMillisServo;

void servoControlSetup() {
  servo.attach(servoPin);
  slagboomHoek = slagboomGesloten;
  servo.write(slagboomHoek);
}

void servoControlOpenSlagboom() {
  while (slagboomHoek < slagboomOpen) {
    if (currentMillis() >= previousMillisServo + slagboomSnelheid) {
      slagboomHoek++;
      servo.write(slagboomHoek);
      previousMillisServo = currentMillis();
    }
    buzzerControlTik(100);
    segmentDisplaySetShiftRegister(segmentDisplayHalt());
  }
}
void servoControlSluitSlagboom() {
  while (slagboomHoek > slagboomGesloten) {
    if (currentMillis() >= previousMillisServo + slagboomSnelheid) {
      slagboomHoek--;
      servo.write(slagboomHoek);
      previousMillisServo = currentMillis();
    }
    buzzerControlTik(100);
    segmentDisplaySetShiftRegister(segmentDisplayHalt());
  }
}
void servoControlOpenSlagboomNacht() {
  while (slagboomHoek < slagboomOpen) {
    if (currentMillis() >= previousMillisServo + slagboomSnelheid) {
      slagboomHoek++;
      servo.write(slagboomHoek);
      previousMillisServo = currentMillis();
    }
    buzzerControlTik(buzzerLengteRustig());
    segmentDisplaySetShiftRegister(segmentDisplayHalt());
  }
}

void servoControlSluitSlagboomNacht() {
  while (slagboomHoek > slagboomGesloten) {
    if (currentMillis() >= previousMillisServo + slagboomSnelheid) {
      slagboomHoek--;
      servo.write(slagboomHoek);
      previousMillisServo = currentMillis();
    }
    buzzerControlTik(buzzerLengteRustig());
    segmentDisplaySetShiftRegister(segmentDisplayHalt());
    ledControlSetShiftRegister(ledControlPatronen(BEIDE_ORANJE()));
  }
}
