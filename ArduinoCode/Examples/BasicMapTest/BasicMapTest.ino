#include "FastLED.h"
//next step is separating to a proper class but this is neat and small enough for now
//majority of mem use is NUM_LEDS*3 + NUM_LEDS*2
#define NUM_LEDS 20

struct map2d{

byte x[NUM_LEDS];
byte y[NUM_LEDS]; 
};

struct map2d mapping ={
{116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 110, 105, 99, 94, 88, 83, 77, 72, 66, 60, 55, 49, 44, 38, 33, 27, 22, 16, 11, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 11, 16, 22, 27, 33, 38, 44, 49, 55, 60, 66, 72, 77, 83, 88, 94, 99, 105, 110, 255, 249, 243, 238, 232, 227, 221, 216, 210, 205, 199, 194, 188, 182, 177, 171, 166, 160, 155, 149, 144, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 138, 144, 149, 155, 160, 166, 171, 177, 182, 188, 194, 199, 205, 210, 216, 221, 227, 232, 238, 243, 249, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255},
{116, 110, 105, 99, 94, 88, 83, 77, 72, 66, 60, 55, 49, 44, 38, 33, 27, 22, 16, 11, 5, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 0, 5, 11, 16, 22, 27, 33, 38, 44, 49, 55, 60, 66, 72, 77, 83, 88, 94, 99, 105, 110, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 11, 16, 22, 27, 33, 38, 44, 49, 55, 60, 66, 72, 77, 83, 88, 94, 99, 105, 110, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 110, 105, 99, 94, 88, 83, 77, 72, 66, 60, 55, 49, 44, 38, 33, 27, 22, 16, 11, 5}
};
CRGB leds[NUM_LEDS];

long lastModeChange = 0;

const int LED_PIN = 4;

CRGBPalette16 currentPalette( PartyColors_p );
CRGBPalette16 targetPalette( PartyColors_p );

TBlendType  currentBlending;

void setup() {
//  Serial.begin(115200);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  
  FastLED.clear();
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  FastLED.setDither(false);
  FastLED.show();
  currentBlending = LINEARBLEND;
  setRandomTargetPalette();

}

/////////////////////////////////////////////////////////////////////////////
void loop() {

  if (millis() - lastModeChange > 12000) {
    setRandomTargetPalette();
  }
  mapNoiseTest();//fill leds with simple 2d noise pattern that moves in 3rd dimension
  nblendPaletteTowardPalette(currentPalette, targetPalette, 2);
  FastLED.show();

}



void mapNoiseTest() {
  int noiseTempThing = 0;
  int timeVal = (int)millis()>>3;
  for (int i = 0; i < NUM_LEDS; i++) {
    noiseTempThing = inoise16(mapping.x[i] * 1, mapping.y[i] * 1, timeVal);
    leds[i] = ColorFromPalette( currentPalette, noiseTempThing, 255, currentBlending);
  }
}




void verticalOneDimensionScroll() {

  int timeVal = (int)millis()>>2;
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t noiseTempThing = inoise8((mapping.y[i] + timeVal));
    leds[i] = ColorFromPalette( currentPalette, noiseTempThing, 255, currentBlending);
  }
}




//test code to flip mappings
//there should be 1 that works for all four or four seperate ones
//left-right flip, top-bottom flip
//rotate 90
//rotate 180
//these MUST be completely reversible
void flipTopBottom() {
  for (int i = 0; i < NUM_LEDS; i++) {
    mapping.y[i] = 255 - mapping.y[i];
  }
}

void flipLeftRight() {
  for (int i = 0; i < NUM_LEDS; i++) {
    mapping.x[i] = 255 - mapping.x[i];
  }
}

void flipXY() {
  //mirror on 45 axis i think?
  //swaps x and y so whatever that does...
  byte temp = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    temp = mapping.y[i];
    mapping.y[i] = mapping.x[i];
    mapping.x[i] = temp;
  }
}


void mapTestQuadrants() {
//show different colour in each quarter so you can see which way round it is
  for (int i = 0; i < NUM_LEDS; i++) {
    if ((mapping.x[i] < 128) && (mapping.y[i] < 128)) {
      leds[i] = CRGB(255, 0, 0);
    }
    if ((mapping.x[i] > 128) && (mapping.y[i] < 128)) {
      leds[i] = CRGB(0, 255, 0);
    }
    if ((mapping.x[i] > 128) && (mapping.y[i] > 128)) {
      leds[i] = CRGB(0, 0, 255);
    }
    if ((mapping.x[i] < 128) && (mapping.y[i] > 128)) {
      leds[i] = CRGB(0, 255, 255);
    }
  }
}


void singleWhite() {

  int currentpos = millis() / 100;
  currentpos = currentpos % NUM_LEDS;
  for (int i = 0; i < NUM_LEDS; i++) {
    if (i == currentpos) {
      leds[i] = CRGB(128, 128, 128);
    } else {
      leds[i].nscale8(245);
    }
  }
}


void setRandomTargetPalette() {

  targetPalette = CRGBPalette16(
                    CHSV(0, 255, 0),
                    CHSV( random8(), 255, 32),
                    CHSV( random8(), 255, 255),
                    CHSV( random8(), 128, 255)
                  );
}



