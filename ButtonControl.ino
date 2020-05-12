const int BUTTON_VOETGANGER = 13;
const int BUTTON_LINKS = 12;
const int BUTTON_RECHTS = 11;
int button;
int getButton() {
  return button;
}
int setButton(int i) {
  button = i;
  return button;
}
// --- States -----------
const int BUTTON_STATE_RELEASED = 1;
const int BUTTON_STATE_CHECK_PRESSED = 2;
const int BUTTON_STATE_PRESSED = 3;
const int BUTTON_STATE_CHECK_RELEASED = 4;

// Current state
int button_State;

// Timer variables
const int BUTTON_INTERVAL = 10; // 10 msec
unsigned long button_Previous;

// Click variable
boolean button_Click;


// SetButton

//----Setup----
void buttonControlSetup() {
  pinMode(BUTTON_VOETGANGER, INPUT);
  pinMode(BUTTON_LINKS, INPUT);
  pinMode(BUTTON_RECHTS, INPUT);

  button_State = BUTTON_STATE_RELEASED;
  button_Released_Entry();
  button = BUTTON_LINKS;
}
//----Loop----
void buttonControlLoop() {
  switch (button_State) {
    case BUTTON_STATE_RELEASED:
      button_Released_Do();
      for (int i = 13; i > 10; i--) {
        if (buttonHardware_Down(i) == true) {
          button_Released_Exit(i);
          button_State = BUTTON_STATE_CHECK_PRESSED;
          button_Check_Pressed_Entry();
        }
      }
      break;
    case BUTTON_STATE_CHECK_PRESSED:
      button_Check_Pressed_Do();

      if (buttonHardware_Up() == true) {
        button_Check_Pressed_Exit();
        button_State = BUTTON_STATE_RELEASED;
        button_Released_Entry();
      }
      else if ((buttonHardware_Down(button) == true)
               && (millis() - BUTTON_INTERVAL >= button_Previous)) {
        button_Check_Pressed_Exit();
        button_State = BUTTON_STATE_PRESSED;
        button_Pressed_Entry();

      }
      break;
    case BUTTON_STATE_PRESSED:
      button_Pressed_Do();
      if (buttonHardware_Up() == true) {
        button_Pressed_Exit();
        button_State = BUTTON_STATE_CHECK_RELEASED;
        button_Check_Released_Entry();
      }
  
  break;
case BUTTON_STATE_CHECK_RELEASED:
  button_Check_Released_Do();

    if (buttonHardware_Down(button) == true) {
      button_Check_Released_Exit();
      button_State = BUTTON_STATE_PRESSED;
      setButton(0);
      button_Pressed_Entry();
    }
    else if ((buttonHardware_Up() == true)
             && (millis() - BUTTON_INTERVAL >= button_Previous)) {
      button_Check_Released_Exit();
      button_State = BUTTON_STATE_RELEASED;
      // On this transition the click has occured.
      button_Click = true;
      setButton(button);
      button_Released_Entry();
    }
  break;
}
}

//----Functies----
boolean buttonHardware_Down(int buttonPin) {
  return (digitalRead(buttonPin) == LOW);
}

boolean buttonHardware_Up() {
  return !buttonHardware_Down(button);
}

boolean button_Clicked() {
  if (button_Click == true) {
    button_Click = false;
    return true;
  }
  else {
    return false;
  }
}

// --- BUTTON_STATE_RELEASED -----------
void button_Released_Entry() {
  // <nothing>
}
void button_Released_Do() {
  // <nothing>
}
void button_Released_Exit(int button) {
  setButton(button);
}
// --- BUTTON_STATE_CHECK_PRESSED -----------
void button_Check_Pressed_Entry() {
  button_Previous = millis();
}
void button_Check_Pressed_Do() {
  // <nothing>
}
void button_Check_Pressed_Exit() {
  // <nothing>
}
// --- BUTTON_STATE_PRESSED -----------
void button_Pressed_Entry() {
  // <nothing>
}
void button_Pressed_Do() {
  // <nothing>
}
void button_Pressed_Exit() {
  // <nothing>
}
// --- BUTTON_STATE_CHECK_RELEASED -----------
void button_Check_Released_Entry() {
  button_Previous = millis();
}
void button_Check_Released_Do() {
  // <nothing>
}
void button_Check_Released_Exit() {
  // <nothing>
}
