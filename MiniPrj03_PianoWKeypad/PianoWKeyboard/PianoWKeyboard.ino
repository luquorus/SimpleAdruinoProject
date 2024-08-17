#include <Keypad.h>

const byte ROWS = 4; // Number of rows
const byte COLS = 4; // Number of columns

// Define array containing the characters on the keypad
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Pins connected to the rows and columns of the keypad
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// Initialize Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Pin connected to the buzzer
const int buzzerPin = 10;

// Frequencies of the musical notes (C4 - C5)
const int NOTE_C4 = 262;
const int NOTE_D4 = 294;
const int NOTE_E4 = 330;
const int NOTE_F4 = 349;
const int NOTE_G4 = 392;
const int NOTE_A4 = 440;
const int NOTE_B4 = 494;
const int NOTE_C5 = 523;

void playsound(int frequency) {
  tone(buzzerPin, frequency);                                              
  delay(500);                                                       
  noTone(buzzerPin);                                                       
}

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    switch (key) {
      case '1':
        playsound(NOTE_C4); // Note C4
        break;
      case '2':
        playsound(NOTE_D4); // Note D4
        break;
      case '3':
        playsound(NOTE_E4); // Note E4
        break;
      case '4':
        playsound(NOTE_F4); // Note F4
        break;
      case '5':
        playsound(NOTE_G4); // Note G4
        break;
      case '6':
        playsound(NOTE_A4); // Note A4
        break;
      case '7':
        playsound(NOTE_B4); // Note B4
        break;
      case '8':
        playsound(NOTE_C5); // Note C5
        break;
      default:
        break;
    }
  } 
}
