#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

// Initialize the LCD object with I2C address 0x27, 16 columns, 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Set up the configuration for the Keypad
const byte ROWS = 4; // Number of rows
const byte COLS = 4; // Number of columns
char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; // Pins connected to the rows of the keypad
byte colPins[COLS] = {5, 4, 3, 2}; // Pins connected to the columns of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

float num1 = 0, num2 = 0;
char operatorChar;
boolean operatorPressed = false;
boolean resultDisplayed = false;

void setup() {
  lcd.init();  // Initialize the LCD
  lcd.backlight();  // Turn on the LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("Calculator");
}

void loop() {
  char key = keypad.getKey();
  
  if (key) {
    if (key >= '0' && key <= '9') {
      if (resultDisplayed) {
        // Start a new calculation if a number is pressed after displaying the result
        num1 = 0;
        num2 = 0;
        operatorPressed = false;
        resultDisplayed = false;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Calculator");
      }
      
      if (operatorPressed) {
        num2 = num2 * 10 + (key - '0');
        lcd.setCursor(0, 1);
        lcd.print(num2);
      } else {
        num1 = num1 * 10 + (key - '0');
        lcd.setCursor(0, 1);
        lcd.print(num1);
      }
    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
      operatorChar = key;
      operatorPressed = true;
      resultDisplayed = false;
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print(operatorChar);
      lcd.print(' '); // Add a space for better readability
    } else if (key == '=') {
      float result = 0;
      if (operatorChar == '+') {
        result = num1 + num2;
      } else if (operatorChar == '-') {
        result = num1 - num2;
      } else if (operatorChar == '*') {
        result = num1 * num2;
      } else if (operatorChar == '/') {
        result = num1 / num2;
      }
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Result:");
      lcd.setCursor(0, 1);
      lcd.print(result);
      
      // Store the result for potential further calculations but set flag to start new if needed
      num1 = result;
      num2 = 0;
      operatorPressed = false;
      resultDisplayed = true;
    } else if (key == 'C') {
      // Clear everything
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Calculator");
      num1 = num2 = 0;
      operatorPressed = false;
      resultDisplayed = false;
    }
  }
}
