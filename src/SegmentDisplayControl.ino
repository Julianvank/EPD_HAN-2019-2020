const int DS_7SEGMENT = 10;
const int ST_CP_7SEGMENT = 9;
const int SH_CP_7SEGMENT = 8;

void segmentDisplaySetup() {
  pinMode(DS_7SEGMENT, OUTPUT);
  pinMode(ST_CP_7SEGMENT, OUTPUT);
  pinMode(SH_CP_7SEGMENT, OUTPUT);
}



byte segmentDisplayLopen(){
  return B00011101;
}
byte segmentDisplayHalt(){
  return B01101111;
}
byte segmentDisplayStop(){
  return B10110111;
}
byte segmentDisplayWaarschuwing(){
  return B11001111;
}

int patroon1Lengte() {
  return 16;
}
byte segmentDisplayPatronen(int i) {
  byte patroon[patroon1Lengte()] {
    //0
    B11111100,
    //1
    B01100000,
    //2
    B11011010,
    //3
    B11110010,
    //4
    B01100110,
    //5
    B10110110,
    //6
    B10111110,
    //7
    B11100000,
    //8
    B11111110,
    //9
    B11110110,
    //A
    B11101111,
    //B
    B11111111,
    //C
    B10011101,
    //D
    B11111101,
    //E
    B10011111,
    //F
    B10001111
  };
  return patroon[i];
}

void segmentDisplaySetShiftRegister(byte patroon) {
  digitalWrite(ST_CP_7SEGMENT, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(SH_CP_7SEGMENT, LOW);
    digitalWrite(DS_7SEGMENT, isBitSet(patroon, i));
    digitalWrite(SH_CP_7SEGMENT, HIGH);
  }
  digitalWrite(ST_CP_7SEGMENT, HIGH);
}
int segmentDisplayClearShiftRegister() {
  digitalWrite(ST_CP_7SEGMENT, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(SH_CP_7SEGMENT, LOW);
    digitalWrite(DS_7SEGMENT, 0);
    digitalWrite(SH_CP_7SEGMENT, HIGH);
  }
  digitalWrite(ST_CP_7SEGMENT, HIGH);
  return 0;
}

void segmentDisplayAllOnShiftRegister() {
  digitalWrite(ST_CP_7SEGMENT, LOW);
  for (int i = 0; i < 8; i++) {
    digitalWrite(SH_CP_7SEGMENT, LOW);
    digitalWrite(DS_7SEGMENT, 1);
    digitalWrite(SH_CP_7SEGMENT, HIGH);
  }
  digitalWrite(ST_CP_7SEGMENT, HIGH);
}
