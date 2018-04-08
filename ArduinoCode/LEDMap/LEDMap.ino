/*
  LED Map

  A simple program to connect with a processing sketch for automatic LED mapping
  When powered on all pixels flash to indicate ready to connect
  SERIAL_SPEED needs to match processing codes equivalent
  NUM_LEDS size is sent to processing side automatically
  Code by info@devicer.net
*/
#include <FastLED.h>

#define NUM_LEDS 20
#define LED_PIN 4
#define CLOCK_PIN 5
#define ONBOARD_LED_PIN 16 //13 on many, 16 on NodeMCU style ESP8266 modules
long SERIAL_SPEED = 115200; //needs to match processing parts serial speed

const int BUF_SIZE = NUM_LEDS * 3;
CRGB leds[NUM_LEDS];

char buf[BUF_SIZE];

boolean commActive = false;
int inByte = 0;         // incoming serial byte
boolean ledsActive = false;
long lastActiveTime = 0;
long TIMEOUT = 4000; //timeout if not receiving led data in millis


void setup() {
  // start serial port and wait for port to open:
  Serial.begin(SERIAL_SPEED);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  FastLED.addLeds<APA102, LED_PIN, CLOCK_PIN, BGR, DATA_RATE_MHZ(24)>(leds, NUM_LEDS);
  //  LEDS.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS); //usually GRB for strips, RGB for ws2811 pixels...
  LEDS.clear();
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  LEDS.setDither(false);
  LEDS.show();

  establishContact();  // send string to establish contact until receiver responds
}

void loop() {

  if (ledsActive) {
    //communication is active:
    //receive  serial and put it on the lights
    //If there's nothing for a while then timeout
    if ((Serial.available() > 3)) { //needs minimum of 3 bytes for 1 led...
      //if not timed out and leds are active then receive led data
      getNumbersFromSerial();
      memcpy8(leds, buf, NUM_LEDS * sizeof(struct CRGB));
      lastActiveTime = millis();
    }
    if (((millis() - lastActiveTime) > TIMEOUT) ) {
      Serial.println("Timeout! - too long without signal received");
      //      cycleSerialConnection();
      ledsActive = false;
      commActive = false;
      establishContact();
    }
  } else {
    if ((Serial.available() > 0)) {
      // get incoming byte:
      commActive = true;
      inByte = Serial.read();
      if (inByte == 'A') {
        //got valid response from processing side
        //so send NUM_LEDS to processing side and then
        //set as active ready to receive LED data
        Serial.print("NUM_LEDS=");
        Serial.println(NUM_LEDS);
        ledsActive = true;
      }
      lastActiveTime = millis();
    }
  }
  
  LEDS.show();
}


void establishContact() {
  int counter;
  Serial.println("Est contact");
  while ((Serial.available() <= 0) && (commActive == false)) {
    Serial.println("LEDmap");   // send an initial string
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB(counter, counter / 4, 0));
    LEDS.show();
    counter += 16;
    counter = counter % 32;
  }
}


void getNumbersFromSerial() {

  //light led to show activity...
  digitalWrite(ONBOARD_LED_PIN, HIGH);
  int count = 0;
  while (count < BUF_SIZE) {
    if (Serial.available()) {
      char c = Serial.read();
      buf[count] = c;
      count++;
    }
  }
  digitalWrite(ONBOARD_LED_PIN, LOW);
}


