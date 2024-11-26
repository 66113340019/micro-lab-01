#include <Arduino.h>
 
 //Pin definitions (คำจำกัดความของพิน)
const int buttonPin = 2; //Push button connected to D2
const int redPin = 10; //Red LED connected to D8
const int yellowPin = 8; //Yellow LED connected to D9
const int greenPin = 9; //Green LED connected to D10


//State variables (ตัวแปรสถานะ)
int buttonState = 0; //Current state of button (สถานะปัจจุบันของปุ่ม)
int lastButtonState = 0; //Previous state of button (สถานะก่อนหน้าของปุ่ม)
int trafficState = 0; //Traffic light state (0: REd, 1: Green, 2: Yellow) [สถานะไฟจราจร (0: สีแดง, 1: สีเขียว, 2: สีเหลือง)]
unsigned long lastDebounceTime = 0; //Debounce timer (ตัวจับเวลาดีบาวน์)
const unsigned long debounceDelay = 50; //Debounce delay in milliseconds (ความล่าช้าในการดีบาวน์เป็นมิลลิวินาที)


void updateTrafficLights();
void stopTrafficLights1();
void stopTrafficLights2();


void setup() {
Serial.begin(9600);


  //Initialize LEDs as output (เริ่มต้น LED เป็นเอาท์พุต)
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);


  //Initialize push button as INPUT (เริ่มต้นกดปุ่มเป็น INPUT)
  pinMode(buttonPin, INPUT);
 
  //Start with green light ON (เริ่มด้วยไฟสีแดงเปิด)
  digitalWrite(redPin, HIGH);
}


void loop() {
  //Read the push button state (อ่านสถานะปุ่มกด)
  int reading = digitalRead(buttonPin);


  //Debounce logic 9ตรรกะดีบาวน์
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }


  if ((millis() - lastDebounceTime) > debounceDelay) {
    //If the button state has changed (หากสถานะปุ่มมีการเปลี่ยนแปลง)
    if (reading != buttonState) {
      buttonState = reading;
      //If button is pressed (หากกดปุ่ม)
        if (buttonState == HIGH) {
          //Cycle traffic light states (สถานะสัญญาณไฟจราจรจักรยาน)
          trafficState = (trafficState + 1) % 3;
          //updateTrafficLights();
          //stopTrafficLights2();
        }
    }
  }


  lastButtonState = reading;
  stopTrafficLights2();
}


//Function to update traffic light states (ฟังก์ชั่นอัปเดตสถานะไฟจราจร)
void updateTrafficLights() {
    //Turn off all LEDs (ปิดไฟ LED ทั้งหมด)
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);


    //Turn on the corresponding LED based on trafficState (เปิดไฟ LED ที่สอดคล้องกันตามสถานะการจราจร)
    switch (trafficState) {
      case 0: //green
        digitalWrite(greenPin, HIGH);
        break;
      case 1: //yellow
        digitalWrite(yellowPin, HIGH);
        break;
      case 2: //red
        digitalWrite(redPin, HIGH);
        break;
    }
  }


void stopTrafficLights1() {
  digitalWrite(greenPin, HIGH); digitalWrite(yellowPin, LOW); digitalWrite(redPin, LOW); delay(1000);
  digitalWrite(greenPin, LOW); digitalWrite(yellowPin, HIGH); digitalWrite(redPin, LOW); delay(500);
  digitalWrite(greenPin, LOW); digitalWrite(yellowPin, LOW); digitalWrite(redPin, HIGH); delay(2000);
}


void stopTrafficLights2() {
  trafficState = 2; updateTrafficLights(); delay(1000);
  trafficState = 1; updateTrafficLights(); delay(500);
  trafficState = 0; updateTrafficLights(); delay(3000);
  //trafficState = 2; updateTrafficLights(); delay(3000);
}
