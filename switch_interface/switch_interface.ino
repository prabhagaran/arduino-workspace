#define BTN_LEFT   PB12
#define BTN_RIGHT  PB13
#define BTN_SEL    PB14
#define BTN_BACK   PB15

#define DRE(signal, state) (state = ((state << 1) | (signal & 1)) & 15) == 7

byte leftState  = 7;
byte rightState = 7;
byte selState   = 7;
byte backState  = 7;

void setup() {
  Serial.begin(115200);
  delay(200);

  pinMode(BTN_LEFT,  INPUT_PULLUP);
  pinMode(BTN_RIGHT, INPUT_PULLUP);
  pinMode(BTN_SEL,   INPUT_PULLUP);
  pinMode(BTN_BACK,  INPUT_PULLUP);

  Serial.println("DRE button test started");
}

void loop() {
  bool L = !digitalRead(BTN_LEFT);
  bool R = !digitalRead(BTN_RIGHT);
  bool S = !digitalRead(BTN_SEL);
  bool B = !digitalRead(BTN_BACK);

  if (DRE(L, leftState))  Serial.println("LEFT pressed");
  if (DRE(R, rightState)) Serial.println("RIGHT pressed");
  if (DRE(S, selState))   Serial.println("SELECT pressed");
  if (DRE(B, backState))  Serial.println("BACK pressed");
}
