const int DS_LED = 7;
const int ST_CP_LED = 6;
const int SH_CP_LED = 5;

const byte BEIDE_ROOD(){
  return 0;
}
const byte LINKS_ORANJE(){
  return 1;
}
const byte LINKS_GROEN(){
  return 2;
}
const byte RECHTS_ORANJE(){
  return 3;
}
const byte RECHTS_GROEN(){
  return 4;
}
const byte BEIDE_ORANJE(){
  return 5;
}


void ledControlSetup() {
  pinMode(DS_LED, OUTPUT);
  pinMode(ST_CP_LED, OUTPUT);
  pinMode(SH_CP_LED, OUTPUT);
}


byte ledControlPatronen(int i) {
  byte patroon[6] {
    //Beide Rood
    B00100100,
    //Links Oranje/Rechts Rood
    B01000100,
    //Links Groen/Rechts Rood
    B10000100,
    //Links Rood/Rechts Oranje
    B00101000,
    //Links Rood/Rechts Groen
    B00110000,  
    //Beide Oranje
    B01001000  
  };
  return patroon[i];
}


void ledControlSetShiftRegister(byte patroon) {
  digitalWrite(ST_CP_LED, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(SH_CP_LED, LOW);
    digitalWrite(DS_LED, isBitSet(patroon, i));
    digitalWrite(SH_CP_LED, HIGH);
  }
  digitalWrite(ST_CP_LED, HIGH);
}
int ledControlClearShiftRegister() {
  digitalWrite(ST_CP_LED, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(SH_CP_LED, LOW);
    digitalWrite(DS_LED, 0);
    digitalWrite(SH_CP_LED, HIGH);
  }
  digitalWrite(ST_CP_LED, HIGH);
  return 0;
}

void ledControlAllOnShiftRegister() {
  digitalWrite(ST_CP_LED, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(SH_CP_LED, LOW);
    digitalWrite(DS_LED, 1);
    digitalWrite(SH_CP_LED, HIGH);
  }
  digitalWrite(ST_CP_LED, HIGH);
}
