#include <Arduino.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

#define IMMEDIATE_NEW   0
#define USE_POT_CONTROL 1
#define PRINT_CALLBACK  0

#define PRINT(s, v) { Serial.print(F(s)); Serial.print(v); }
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4


#define CLK_PIN   13  // or SCK
#define DATA_PIN  11  // or MOSI
#define CS_PIN    10  // or SS


// SPI hardware interface
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);
// Arbitrary pins
//MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

#if USE_POT_CONTROL
#define SPEED_IN A5
#else
#define SCROLL_DELAY 75
#endif

// Text parameters
#define CHAR_SPACING  1  // pixels between characters


// Global message buffers shared by Serial and Scrolling functions
#define BUF_SIZE  75
uint8_t curMessage[BUF_SIZE] = {" Hello Awatsadaaaaaa! And Jieeeeee. XD" };
uint8_t newMessage[BUF_SIZE];
bool newMessageAvailable = false;

uint16_t scrollDelay;

void readSerial(void) {
  static uint8_t putIndex = 0;

  while (Serial.available()) {
    newMessage[putIndex] = (char)Serial.read();
    if ((newMessage[putIndex] == '\n') || (putIndex >= BUF_SIZE-3)) {  // end of message character or full buffer
      // Put in a message separator and end the string
      newMessage[putIndex] = ' ';
      newMessage[putIndex] = '\0';
      // Restart the index for next filling spree and flag we have a message waiting
      putIndex = 0;
      newMessageAvailable = true;
    }
    else if (newMessage[putIndex] != '\r')
      // Just save the next char in next location
      putIndex++;
    }
  }

void scrollDataSink(uint8_t dev, MD_MAX72XX::transformType_t t, uint8_t col) {
  #if PRINT_CALLBACK
    Serial.print("\n cb");
    Serial.print(dev);
    Serial.print(' ');
    Serial.print(t);
    Serial.print(' ');
    Serial.println(col);
  #endif
}

uint8_t scrollDataSource(uint8_t dev, MD_MAX72XX::transformType_t t) {
  static uint8_t* p = curMessage;
  static enum { NEW_MESSAGE, LOAD_CHAR, SHOW_CHAR, BETWEEN_CHAR } state = LOAD_CHAR;
  static uint8_t curLen, showLen;
  static uint8_t cBuf[15];
  uint8_t colData = 0;

  #if IMMEDIATE_NEW
    if (newMessageAvailable) {
      state = NEW_MESSAGE;
      mx.clear();
    }
  #endif

  switch(state) {
    case NEW_MESSAGE:
      memcpy(curMessage, newMessage, BUF_SIZE);
      newMessageAvailable = false;
      p = curMessage;
      state = LOAD_CHAR;
      break;
    
    case LOAD_CHAR:
      showLen = mx.getChar(*p++, sizeof(cBuf)/sizeof(cBuf[0]),cBuf);
      curLen = 0;
      state = SHOW_CHAR;

      if (*p == '\0') {
        p = curMessage;
#if !IMMEDIATE_NEW
        if (newMessageAvailable) {
          state = NEW_MESSAGE;
          break;
        }
#endif
      }

      case SHOW_CHAR:
        colData = cBuf[curLen++];
        if (curLen == showLen) {
          showLen = CHAR_SPACING;
          curLen = 0;
          state = BETWEEN_CHAR;
        }
        break;

      case BETWEEN_CHAR:
        colData = 0;
        curLen++;
        if (curLen == showLen)
          state = LOAD_CHAR;
        break;

      default:
        state = LOAD_CHAR;
  }

  return(colData);
}

void scrollText(void) {
  static uint32_t prevTime = 0;

  if (millis() - prevTime >= scrollDelay) {
    mx.transform(MD_MAX72XX::TSL);
    prevTime = millis();
  }
}

uint16_t getScrollDelay(void) {
#if USE_POT_CONTROL
  uint16_t t;

  t = analogRead(SPEED_IN);
  t = map(t, 0, 1032, 25, 250);

  return(200);
#else 
  return(SCROLL_DELAY);
#endif
}

void setup() {
  mx.begin();
  mx.setShiftDataInCallback(scrollDataSource);
  mx.setShiftDataOutCallback(scrollDataSink);

#if USE_POT_CONTROL
  pinMode(SPEED_IN, INPUT);
#else
  scrollDelay = SCROLL_DELAY;
#endif

  newMessage[0] = '\0';

  Serial.begin(57600);
  Serial.print("\n[MD_MAX72XX MEssage Display]\nType a message for the scrolling dislay\nEnd message line with a newline");
}

void loop() {
  scrollDelay = getScrollDelay();
  readSerial();
  scrollText();
}
