#include <IRremote.h>

#define IR_RECEIVE_PIN 3
#define BUTTON_CODE 0x45 // HEX code for button 45 (0x2D in HEX)
const int ledPin = 2;

bool ledState = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); // Establish serial communication
  IrReceiver.begin(IR_RECEIVE_PIN); // Start the receiver without LED feedback
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.print("Button Code: ");
      Serial.println(IrReceiver.decodedIRData.command, HEX); // Print the button code in HEX format

      // Check if the received command matches the desired button code
      if (IrReceiver.decodedIRData.command == BUTTON_CODE) {
        // Toggle LED state
        ledState = !ledState;
        digitalWrite(ledPin, ledState ? HIGH : LOW);

        // Add a small delay to debounce
        delay(1000); 
      }

      IrReceiver.resume(); // Enable receiving of the next value
  }
}
