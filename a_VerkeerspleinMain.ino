int currentState;

//Dag situatie.
const int KRUISPUNT_GESLOTEN = 0;
const int OPEN_SLAGBOOM = 1;
const int BEGIN_OVERSTEEK_VOETGANGER = 2;
const int EIND_OVERSTEEK_VOETGANGER = 3;
const int SLUIT_SLAGBOOM = 4;
const int STOPLICHT_LINKS_GROEN = 5;
const int STOPLICHT_LINKS_ORANJE = 6;
const int STOPLICHT_LINKS_ROOD = 7;
const int STOPLICHT_RECHTS_GROEN = 8;
const int STOPLICHT_RECHTS_ORANJE = 9;
const int STOPLICHT_RECHTS_ROOD = 10;
//Nacht situatie.
const int START_NACHT = 11;
const int KRUISPUNT_NACHT = 12;
const int EIND_NACHT = 13;

//Timer
unsigned long int previousMillis;
int displayGetal;

//Servo
boolean statusSlagboom;
const boolean OPEN = true;
const boolean DICHT = false;
//knipper boolean
boolean knipper;
const boolean AAN = true;
const boolean UIT = false;

//Dag en Nacht sensor
byte tijdVanDag;
//Buzzer
boolean buzzerTik;

int richting;

void verkeerspleinMainSetup() {
  currentState = KRUISPUNT_GESLOTEN;
  KRUISPUNT_GESLOTEN_ENTRY();
  knipper = UIT;
}

void verkeerspleinMainLoop() {
  switch (currentState) {
    case KRUISPUNT_GESLOTEN: {
        KRUISPUNT_GESLOTEN_DO();
        if (tijdVanDag == DAG()) {
          switch (richting) {
            case BUTTON_VOETGANGER:
              KRUISPUNT_GESLOTEN_EXIT();
              currentState = OPEN_SLAGBOOM;
              OPEN_SLAGBOOM_ENTRY();
              break;
            case BUTTON_LINKS:
              KRUISPUNT_GESLOTEN_EXIT();
              currentState = STOPLICHT_LINKS_GROEN;
              STOPLICHT_LINKS_GROEN_ENTRY();
              break;
            case BUTTON_RECHTS:
              KRUISPUNT_GESLOTEN_EXIT();
              currentState = STOPLICHT_RECHTS_GROEN;
              STOPLICHT_RECHTS_GROEN_ENTRY();
              break;
          }
        } else if (tijdVanDag == AVOND()) {
          KRUISPUNT_GESLOTEN_EXIT();
          currentState = START_NACHT;
          START_NACHT_ENTRY();
        }
      }
      break;
    case OPEN_SLAGBOOM: {
        OPEN_SLAGBOOM_DO();
        if (statusSlagboom == OPEN) {
          OPEN_SLAGBOOM_EXIT();
          currentState = BEGIN_OVERSTEEK_VOETGANGER;
          BEGIN_OVERSTEEK_VOETGANGER_ENTRY();
        }
      }
      break;
    case BEGIN_OVERSTEEK_VOETGANGER: {
        BEGIN_OVERSTEEK_VOETGANGER_DO();
        if (currentMillis() >= previousMillis + 5000) {
          BEGIN_OVERSTEEK_VOETGANGER_EXIT();
          currentState = EIND_OVERSTEEK_VOETGANGER;
        }
      }
      break;
    case EIND_OVERSTEEK_VOETGANGER: {
        EIND_OVERSTEEK_VOETGANGER_DO();
        if (displayGetal == 0) {
          EIND_OVERSTEEK_VOETGANGER_EXIT();
          currentState = SLUIT_SLAGBOOM;
          SLUIT_SLAGBOOM_ENTRY();
        }
      }
      break;
    case SLUIT_SLAGBOOM: {
        SLUIT_SLAGBOOM_DO();
        if (statusSlagboom == DICHT) {
          SLUIT_SLAGBOOM_EXIT();
          currentState = KRUISPUNT_GESLOTEN;
          KRUISPUNT_GESLOTEN_ENTRY();
        }
      }
      break;
    case STOPLICHT_LINKS_GROEN: {
        STOPLICHT_LINKS_GROEN_DO();
        if (currentMillis() >= previousMillis + 5000) {
          STOPLICHT_LINKS_GROEN_EXIT();
          currentState = STOPLICHT_LINKS_ORANJE;
          STOPLICHT_LINKS_ORANJE_ENTRY();
        }
      }
      break;
    case STOPLICHT_LINKS_ORANJE: {
        STOPLICHT_LINKS_ORANJE_DO();
        if (currentMillis() >= previousMillis + 2000) {
          STOPLICHT_LINKS_ORANJE_EXIT();
          currentState = STOPLICHT_LINKS_ROOD;
          STOPLICHT_LINKS_ROOD_ENTRY();
        }
      }
      break;
    case STOPLICHT_LINKS_ROOD: {
        STOPLICHT_LINKS_ROOD_DO();
        if (currentMillis() >= previousMillis + 2000) {
          STOPLICHT_LINKS_ROOD_EXIT();
          currentState = KRUISPUNT_GESLOTEN;
          KRUISPUNT_GESLOTEN_ENTRY();
        }
      }
      break;
    case STOPLICHT_RECHTS_GROEN: {
        STOPLICHT_RECHTS_GROEN_DO();
        if (currentMillis() >= previousMillis + 5000) {
          STOPLICHT_RECHTS_GROEN_EXIT();
          currentState = STOPLICHT_RECHTS_ORANJE;
          STOPLICHT_RECHTS_ORANJE_ENTRY();
        }
      }
      break;
    case STOPLICHT_RECHTS_ORANJE: {
        STOPLICHT_RECHTS_ORANJE_DO();
        if (currentMillis() >= previousMillis + 2000) {
          STOPLICHT_RECHTS_ORANJE_EXIT();
          currentState = STOPLICHT_RECHTS_ROOD;
          STOPLICHT_RECHTS_ROOD_ENTRY();
        }
      }
      break;
    case STOPLICHT_RECHTS_ROOD: {
        STOPLICHT_RECHTS_ROOD_DO();
        if (currentMillis() >= previousMillis + 2000) {
          STOPLICHT_RECHTS_ROOD_EXIT();
          currentState = KRUISPUNT_GESLOTEN;
          KRUISPUNT_GESLOTEN_ENTRY();
        }
      }
      break;
    case START_NACHT: {
        START_NACHT_DO();
        tijdVanDag = NACHT();
        if (tijdVanDag == NACHT()) {
          START_NACHT_EXIT();
          currentState = KRUISPUNT_NACHT;
          KRUISPUNT_NACHT_ENTRY();
          Serial.println("test-------------");

        }
      }
      break;
    case KRUISPUNT_NACHT: {
        KRUISPUNT_NACHT_DO();
        
        if (tijdVanDag == OCHTEND()) {
          KRUISPUNT_NACHT_EXIT();
          currentState = EIND_NACHT;
          EIND_NACHT_ENTRY();
        }
      }
      break;
    case EIND_NACHT: {
        EIND_NACHT_DO();
        tijdVanDag = DAG();
        if (tijdVanDag == DAG()) {
          EIND_NACHT_EXIT();
          currentState = KRUISPUNT_GESLOTEN;
          KRUISPUNT_GESLOTEN_ENTRY();
        }
      }
      break;
  }
}
//----Functies
int setRichting() {
  return getButton();
}


//-----------Kruispunt_gesloten.
void KRUISPUNT_GESLOTEN_ENTRY() {
  setButton(0);
}
void KRUISPUNT_GESLOTEN_DO() {
  buzzerControlTik(buzzerLengteRustig());
  segmentDisplaySetShiftRegister(segmentDisplayStop());
  ledControlSetShiftRegister(ledControlPatronen(BEIDE_ROOD()));
  tijdVanDag = ldrControlcheckStatusDag();
  richting = setRichting();
}
void KRUISPUNT_GESLOTEN_EXIT() {
  previousMillis = currentMillis();
  buzzerControlStop();
  timerControlDodeTijd(previousMillis);

}
//-----------OPEN_SLAGBOOM
void OPEN_SLAGBOOM_ENTRY() {
  ledControlSetShiftRegister(ledControlPatronen(BEIDE_ROOD()));
}
void OPEN_SLAGBOOM_DO() {
  //Open Slagboom
  servoControlOpenSlagboom();
  statusSlagboom = OPEN;
}
void OPEN_SLAGBOOM_EXIT() {
  previousMillis = currentMillis();
}
//-----------BEGIN_OVERSTEEK_VOETGANGER
void BEGIN_OVERSTEEK_VOETGANGER_ENTRY() {

}
void BEGIN_OVERSTEEK_VOETGANGER_DO() {
  segmentDisplaySetShiftRegister(segmentDisplayLopen());
  buzzerControlTik(50);
}
void BEGIN_OVERSTEEK_VOETGANGER_EXIT() {
  previousMillis = currentMillis();
  displayGetal = 6;
  buzzerControlStop();
}
//-----------EIND_OVERSTEEK_VOETGANGER
void EIND_OVERSTEEK_VOETGANGER_ENTRY() {
//<nothing>
}
void EIND_OVERSTEEK_VOETGANGER_DO() {
  while (displayGetal > 0) {
    if (currentMillis() >= previousMillis + 1000) {
      displayGetal--;
      previousMillis = currentMillis();
    }
    buzzerControlTikSpeciaal();
    segmentDisplaySetShiftRegister(segmentDisplayPatronen(displayGetal));
  }
}
void EIND_OVERSTEEK_VOETGANGER_EXIT() {
  buzzerControlStop();
}
//-----------SLUIT_SLAGBOOM
void SLUIT_SLAGBOOM_ENTRY() {
//<nothing>
}
void SLUIT_SLAGBOOM_DO() {
  servoControlSluitSlagboom();
  statusSlagboom = DICHT;

}
void SLUIT_SLAGBOOM_EXIT() {
  buzzerControlStop();
}
//-----------STOPLICHT_LINKS_GROEN
void STOPLICHT_LINKS_GROEN_ENTRY() {
  previousMillis = currentMillis();
}
void STOPLICHT_LINKS_GROEN_DO() {
  ledControlSetShiftRegister(ledControlPatronen(LINKS_GROEN()));
  buzzerControlTik(timerLengteRustig());
}
void STOPLICHT_LINKS_GROEN_EXIT() {
//<nothing>
}
//-----------STOPLICHT_LINKS_ORANJE
void STOPLICHT_LINKS_ORANJE_ENTRY() {
  previousMillis = currentMillis();
}
void STOPLICHT_LINKS_ORANJE_DO() {
  ledControlSetShiftRegister(ledControlPatronen(LINKS_ORANJE()));
  buzzerControlTik(timerLengteRustig());
}
void STOPLICHT_LINKS_ORANJE_EXIT() {
//<nothing>
}
//-----------STOPLICHT_LINKS_ROOD
void STOPLICHT_LINKS_ROOD_ENTRY() {
  previousMillis = currentMillis();
}
void STOPLICHT_LINKS_ROOD_DO() {
  ledControlSetShiftRegister(ledControlPatronen(BEIDE_ROOD()));
  buzzerControlTik(timerLengteRustig());
}
void STOPLICHT_LINKS_ROOD_EXIT() {
//<nothing>
}
//-----------STOPLICHT_RECHTS_GROEN
void STOPLICHT_RECHTS_GROEN_ENTRY() {
  previousMillis = currentMillis();
}
void STOPLICHT_RECHTS_GROEN_DO() {
  ledControlSetShiftRegister(ledControlPatronen(RECHTS_GROEN()));
  buzzerControlTik(timerLengteRustig());
}
void STOPLICHT_RECHTS_GROEN_EXIT() {
//<nothing>
}

//-----------STOPLICHT_RECHTS_ORANJE
void STOPLICHT_RECHTS_ORANJE_ENTRY() {
  previousMillis = currentMillis();
}
void STOPLICHT_RECHTS_ORANJE_DO() {
  ledControlSetShiftRegister(ledControlPatronen(RECHTS_ORANJE()));
  buzzerControlTik(timerLengteRustig());
}
void STOPLICHT_RECHTS_ORANJE_EXIT() {
//<nothing>
}
//-----------STOPLICHT_RECHTS_ROOD
void STOPLICHT_RECHTS_ROOD_ENTRY() {
  previousMillis = currentMillis();
}
void STOPLICHT_RECHTS_ROOD_DO() {
  ledControlSetShiftRegister(ledControlPatronen(BEIDE_ROOD()));
  buzzerControlTik(timerLengteRustig());
}
void STOPLICHT_RECHTS_ROOD_EXIT() {
//<nothing>
}

//-----------START_NACHT
void START_NACHT_ENTRY() {
  //<nothing>
}
void START_NACHT_DO() {
  servoControlOpenSlagboomNacht();
}
void START_NACHT_EXIT() {
  buzzerControlStop();
}
//-----------NACHT
void KRUISPUNT_NACHT_ENTRY() {
//<nothing>
}
void KRUISPUNT_NACHT_DO() {
  segmentDisplaySetShiftRegister(segmentDisplayWaarschuwing());
  if (currentMillis() >= previousMillis + timerLengteRustig()) {
    if (knipper == UIT) {
      ledControlSetShiftRegister(ledControlPatronen(BEIDE_ORANJE()));
      knipper = AAN;
    } else if (knipper == AAN) {
      ledControlClearShiftRegister();
      knipper = UIT;
    }
    previousMillis = currentMillis();
  }
  //Check status van nacht.
  if (ldrControlcheckStatusDag() == DAG()) {
    tijdVanDag = OCHTEND();
  }
}
void KRUISPUNT_NACHT_EXIT() {
  previousMillis = currentMillis();
}
//-----------EIND_NACHT
void EIND_NACHT_ENTRY() {
  timerControlDodeTijd(previousMillis);
}
void EIND_NACHT_DO() {
  servoControlSluitSlagboomNacht();
}
void EIND_NACHT_EXIT() {
  ledControlSetShiftRegister(ledControlPatronen(BEIDE_ROOD()));

}
