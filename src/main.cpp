#include <Arduino.h>

// Define pin numbers
const int ledPin = 13;   // Pin for the LED
const int buttonPin = 2; // Pin for the button

// Timing variables
int slowBlinkDelay = 1000;  // 1 second delay for slow blink (in milliseconds)
int fastBlinkDelay = 100;   // 0.1 second delay for fast blink (in milliseconds)

int currentDelay = slowBlinkDelay;  // Default delay is slow blink
int buttonState = 0;       // Variable for reading the button state
int lastButtonState = 0;   // Last button state to detect changes

void setup() {
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);

  // Set button pin as input with pull-up resistor
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // Read the current button state
  buttonState = digitalRead(buttonPin);

  // Check if the button was pressed (buttonState goes LOW when pressed)
  if (buttonState == LOW && lastButtonState == HIGH) {
    // Toggle the blink speed
    if (currentDelay == slowBlinkDelay) {
      currentDelay = fastBlinkDelay;  // Switch to fast blink
    } else {
      currentDelay = slowBlinkDelay;  // Switch to slow blink
    }
    // Wait for button debounce (a short delay to avoid multiple toggles)
    delay(1000);
  }

  // Store the current button state for next loop iteration
  lastButtonState = buttonState;

  // Blink the LED with the current delay (slow or fast)
  digitalWrite(ledPin, HIGH);  // Turn the LED on
  delay(currentDelay);         // Wait for the appropriate time
  digitalWrite(ledPin, LOW);   // Turn the LED off
  delay(currentDelay);         // Wait for the appropriate time
}
