#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

String morseBuffer = "";
String outputText = "";

unsigned long lastInputTime = 0;

// FULL MORSE DECODER
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

  // numbers
  if (code == "-----") return '0';
  if (code == ".----") return '1';
  if (code == "..---") return '2';
  if (code == "...--") return '3';
  if (code == "....-") return '4';
  if (code == ".....") return '5';
  if (code == "-....") return '6';
  if (code == "--...") return '7';
  if (code == "---..") return '8';
  if (code == "----.") return '9';

  return '?';
}

// LCD update helper
void updateLCD() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Text:");
  lcd.setCursor(0, 1);
  lcd.print(outputText);
}

void setup() {
  lcd.init();
  lcd.backlight();

  Serial.begin(9600);

  lcd.setCursor(0, 0);
  lcd.print("Morse Ready");
  delay(1200);
  lcd.clear();

  lastInputTime = millis();
}

void loop() {

  while (Serial.available()) {

    char input = Serial.read();
    lastInputTime = millis(); // reset timer on ANY input

    // DOT / DASH
    if (input == '.' || input == '-') {
      morseBuffer += input;
    }

    // SPACE = end of letter
    else if (input == ' ') {
      if (morseBuffer.length() > 0) {
        char decoded = decodeMorse(morseBuffer);
        outputText += decoded;
        morseBuffer = "";
        updateLCD();
      }
    }

    // '/' = word space
    else if (input == '/') {
      outputText += ' ';
      updateLCD();
    }

    // ENTER / newline = force flush last letter
    else if (input == '\n' || input == '\r') {
      if (morseBuffer.length() > 0) {
        char decoded = decodeMorse(morseBuffer);
        outputText += decoded;
        morseBuffer = "";
        updateLCD();
      }
    }
  }

  // ⏱ AUTO-CLEAR AFTER 10 SECONDS OF INACTIVITY
  if (outputText.length() > 0 && millis() - lastInputTime > 10000) {

    morseBuffer = "";
    outputText = "";

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Cleared");

    delay(800);

    lcd.clear();
  }
}