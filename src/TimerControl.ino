unsigned long int currentMillis() {
  return millis();
}

int timerLengteRustig() {
  return 500;
}

int timerLengteDodeTijd(){
  return 500;
}

void timerControlDodeTijd(unsigned long int previousMillis) {
  while (currentMillis() <= previousMillis + timerLengteDodeTijd()) {
    buzzerControlTik(timerLengteRustig());
  }
}
