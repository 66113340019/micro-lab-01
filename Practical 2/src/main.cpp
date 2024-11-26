#include <Arduino.h>

int buttonPin = 2; // Button connected to pin 2
int ledPin = 13;
int buttonState = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set pin as input with pull-up reisstor
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) { // Button pressed (LOW because of pull-up)
    digitalWrite(ledPin, HIGH);
    Serial.println("Button pressed, LED ON");
  } else {
    digitalWrite(ledPin, LOW);
    Serial.println("Button not pressed, LED OFF");
  }

  delay(100); // Debounce delay
}