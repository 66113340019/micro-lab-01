#include <Arduino.h>


const int rpin = 8;
const int ypin= 9;
const int gpin = 10;

void setup() {
  pinMode(rpin, OUTPUT);
  pinMode(ypin, OUTPUT);
  pinMode(gpin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter brightness (0-255): ");
}


void brightness();


void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    if (input.length() >1) {
      char led = input.charAt(0);
      int brightness = input.substring(1).toInt();

      if (brightness >= 0 && brightness <= 255) {
        switch (led) {
          case 'R':
          case 'r': 
            analogWrite(rpin, brightness);
            Serial.print("Red LED brightness set to: ");
            break;
          case 'Y':
          case 'y':
            analogWrite(ypin, brightness);
            Serial.print("Yellow LED brightness set to: ");
            break;
          case 'G':
          case 'g':
            analogWrite(gpin, brightness);
            Serial.print("Green LED brightness set to: ");
            break;
          default:
            Serial.println("No value entered.");
            return;
        } 
        Serial.println(brightness);
    }
}
  }
}
  