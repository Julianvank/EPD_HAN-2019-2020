const byte NACHT() {
  return 3;
}
const byte AVOND() {
  return 2;
}
const byte OCHTEND() {
  return 1;
}
const byte DAG() {
  return 0;
}

int ldrPin = A0;

void ldrControlSetup() {
  pinMode(A0, INPUT);
}

byte ldrControlcheckStatusDag() {
  int lichtSterkte = analogRead(ldrPin);
  if (lichtSterkte >= 500) {
    return AVOND();
  } else {
    return DAG();
  }
}
