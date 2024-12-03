#include <Arduino.h>
#include <TM1638plus.h>

#define STB 10
#define CLK 9
#define DIO 8

TM1638plus disP(STB, CLK, DIO);
//void checkedPositions(int buttons);

int firstOperand = 0;
int secondOperand = 0;
char operation = '\0';
bool isSecondOperand = false;
bool clearFlag = false;

//String message = " ARDUINO TM1638 DEMO ";
//void scrollText (String text, int delayTime);

void setup() {
  //Serial.begin(9600);
  disP.displayBegin();
  disP.reset();
  //disP.displayText("Hello P3");
  //delay(2000);
}

void loop() {
  // scrollText(message, 250);
  byte buttons = disP.readButtons();
  if (buttons & 0b10000000) {
    firstOperand = 0;
    secondOperand = 0;
    operation = '\0';
    isSecondOperand = false;
    disP.displayText("CLEAR");
    delay(500);
    disP.reset();
    return;
  }

  for (int i = 0; i < 4; i++) {
     if (buttons & (1 << i)) {
      int num = i + 1;
      if (!isSecondOperand) {
        firstOperand = firstOperand * 10 + num;
        disP.displayIntNum(firstOperand, false);
      } else {
        secondOperand = secondOperand * 10 + num;
        disP.displayIntNum(secondOperand, false);
      }
      delay(300); 
  }
}

  if (buttons & 0b00010000) {
    operation = '+';
    isSecondOperand = true;
    disP.displayText("PLUS");
    delay(1000);
   }
  if (buttons & 0b00100000) {
    operation = '-';
    isSecondOperand = true;
    disP.displayText("MINUS");
    delay(1000);
  }

  if (buttons & 0b01000000) {
    int result = 0;

    if (operation == '+') {
      result = firstOperand + secondOperand;
    } else if (operation == '-') {
      result = firstOperand - secondOperand;
    }

    disP.displayIntNum(result, false);

    firstOperand = result;
    secondOperand = 0;
    operation = '\0';
    isSecondOperand = false;

    delay(2000);
  }
}

/* void checkedPosition(void) {
  byte buttons = disP.readButtons();
   if (buttons == 1)
      {
        buttons = 0;
      }
      else if (buttons == 2) 
      {
        buttons = 1;
      }
      else if (buttons == 4)
      {
        buttons = 2;
      }
      else if (buttons == 8)
      {
        buttons = 3;
      }
      else if (buttons == 16)
      {
        buttons = 4;
      }
      else if (buttons == 32)
      {
        buttons = 5;
      }
      else if (buttons == 64)
      {
        buttons = 6;
      }
      else if (buttons == 128)
      {
        buttons = 7;
      }
 } */  

/*void scrollText(String text, int delayTime) {
  int displayLength = 8;
  String paddedText = text + "    ";

  for (int i = 0; i <= paddedText.length() - displayLength; i++) {
    String subText = paddedText.substring(i, i + displayLength);
    disP.displayText(subText.c_str());
    delay(delayTime);
  }
}*/

      
 