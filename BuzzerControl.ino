int buzzerPin = 4;
int buzzerTone = 1000;
int buzzerLengte = 1000;

int buzzerLengteRustig(){
  return 500;
}
boolean buzzerAan;

//Software timer
unsigned long int previousMillisBuzzer;

boolean tikken = true;
int tikFase = 0;

const int KNIPPER_SNELHEID = 50;
const int KNIPPER_PAUZE = 650;


void buzzerControlSetup() {
  pinMode(buzzerPin, OUTPUT);
}



void buzzerControlTik(int interval) {
  if (currentMillis() >= previousMillisBuzzer + interval) {
    if (!buzzerAan) {
      tone(buzzerPin, buzzerTone);
      buzzerAan = !buzzerAan;
    } else {
      noTone(buzzerPin);
      buzzerAan = !buzzerAan;
    }
    previousMillisBuzzer = currentMillis();
  }
}
void buzzerControlTone() {
  tone(buzzerPin, buzzerTone);
}
void buzzerControlStop() {
  noTone(buzzerPin);
}
void buzzerControlTikInstelbaar() {
  tone(buzzerPin, buzzerTone, buzzerLengte);
}

void buzzerControlTikSpeciaal() {
  if (tikFase < 6) {
    if (currentMillis() >= previousMillisBuzzer + KNIPPER_SNELHEID) {
      if (tikken) {
        buzzerControlTone();
        tikken = !tikken;
      } else {
        buzzerControlStop();
        tikken = !tikken;
      }
      tikFase++;
      previousMillisBuzzer = currentMillis();
    }
  }
  else if (tikFase == 6) {
    if (currentMillis() >= previousMillisBuzzer + KNIPPER_PAUZE) {
      buzzerControlStop();
      previousMillisBuzzer = currentMillis();
      tikFase = 0;
    }

  }
}
