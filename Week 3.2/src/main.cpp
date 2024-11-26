#include <Arduino.h>

const int buttonPin = 2;
const int redPin = 8;
const int yellowPin = 9;
const int greenPin = 10;

int counter = 0; 
int buttonState = 0;
int lastButtonState = 0;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

char incomingByte = 0;

void setup() {
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT);
  Serial.println("Enter a character ");

  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
   if (Serial.available() >0) {
    incomingByte = Serial.read();
    Serial.print("Received byte is ");
    Serial.println(incomingByte);

    switch (incomingByte) 
    {
      case 'R':
        digitalWrite(redPin, HIGH);
        break;
      case 'Y':
        digitalWrite(yellowPin, HIGH);
        break;
      case 'G':
        digitalWrite(greenPin, HIGH);
        break;
        case 'r':
        digitalWrite(redPin, LOW);
        break;
      case 'y':
        digitalWrite(yellowPin, LOW);
        break;
      case 'g':
        digitalWrite(greenPin, LOW);
        break;
    }
  }

  int reading = digitalRead(buttonPin);
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        counter = counter + 1;
        Serial.println("Counter value: "); //Label for the counter
        Serial.println(counter); //Print the counter value
      }
    }
  }
  lastButtonState = reading;
}

