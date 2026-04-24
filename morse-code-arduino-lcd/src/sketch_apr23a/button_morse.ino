
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// PINS
const int morseButtonPin = 6;
const int spaceButtonPin = 7;

// SETTINGS
int dotThreshold = 300;
int letterGapTime = 1200;

// STORAGE
String morseBuffer = "";
String outputText = "";

// SCROLL CONTROL
int scrollIndex = 0;
unsigned long lastScrollTime = 0;
int scrollDelay = 400;

// TIMING
unsigned long pressStart = 0;
unsigned long lastInputTime = 0;

// STATES
bool lastMorseState = HIGH;
bool lastSpaceState = HIGH;

// ---------------- MORSE DECODER ----------------
char decodeMorse(String code) {

  if (code == ".-") return 'A';
  if (code == "-...") return 'B';
  if (code == "-.-.") return 'C';
  if (code == "-..") return 'D';
  if (code == ".") return 'E';
  if (code == "..-.") return 'F';
  if (code == "--.") return 'G';
  if (code == "....") return 'H';
  if (code == "..") return 'I';
  if (code == ".---") return 'J';
  if (code == "-.-") return 'K';
  if (code == ".-..") return 'L';
  if (code == "--") return 'M';
  if (code == "-.") return 'N';
  if (code == "---") return 'O';
  if (code == ".--.") return 'P';
  if (code == "--.-") return 'Q';
  if (code == ".-.") return 'R';
  if (code == "...") return 'S';
  if (code == "-") return 'T';
  if (code == "..-") return 'U';
  if (code == "...-") return 'V';
  if (code == ".--") return 'W';
  if (code == "-..-") return 'X';
  if (code == "-.--") return 'Y';
  if (code == "--..") return 'Z';

  return '?';
}

// ---------------- DISPLAY WITH SCROLL ----------------
void updateLCD() {

  String displayText = outputText;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Text:");

  // if long text → scroll
  if (displayText.length() > 16) {

    String visible = displayText.substring(scrollIndex, scrollIndex + 16);

    lcd.setCursor(0, 1);
    lcd.print(visible);

  } else {
    lcd.setCursor(0, 1);
    lcd.print(displayText);
  }
}

// ---------------- SETUP ----------------
void setup() {
  pinMode(morseButtonPin, INPUT_PULLUP);
  pinMode(spaceButtonPin, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Morse Ready");
  delay(1500);
  lcd.clear();

  lastInputTime = millis();
}

// ---------------- LOOP ----------------
void loop() {

  // ================= MORSE INPUT =================
  bool morseState = digitalRead(morseButtonPin);

  if (morseState == LOW && lastMorseState == HIGH) {
    pressStart = millis();
    lastInputTime = millis();
  }

  if (morseState == HIGH && lastMorseState == LOW) {

    unsigned long duration = millis() - pressStart;
    lastInputTime = millis();

    if (duration < dotThreshold) {
      morseBuffer += ".";
    } else {
      morseBuffer += "-";
    }
  }

  lastMorseState = morseState;

  if (morseBuffer.length() > 0 && millis() - lastInputTime > letterGapTime) {
    char decoded = decodeMorse(morseBuffer);
    outputText += decoded;
    morseBuffer = "";
    updateLCD();
  }

  // ================= SPACE BUTTON =================
  bool spaceState = digitalRead(spaceButtonPin);

  if (spaceState == LOW && lastSpaceState == HIGH) {

    if (outputText.length() > 0 && outputText[outputText.length() - 1] != ' ') {
      outputText += " ";
      updateLCD();
    }

    lastInputTime = millis();
  }

  lastSpaceState = spaceState;

  // ================= AUTO SCROLL RIGHT =================
  if (outputText.length() > 16) {

    if (millis() - lastScrollTime > scrollDelay) {

      if (scrollIndex < outputText.length() - 16) {
        scrollIndex++;
      } else {
        scrollIndex = 0; // loop back
      }

      updateLCD();
      lastScrollTime = millis();
    }
  }

  // ================= AUTO CLEAR =================
  if (outputText.length() > 0 && millis() - lastInputTime > 5000) {
    outputText = "";
    morseBuffer = "";
    scrollIndex = 0;

    lcd.clear();
    lcd.print("Cleared");
    delay(800);
    lcd.clear();
  }
}