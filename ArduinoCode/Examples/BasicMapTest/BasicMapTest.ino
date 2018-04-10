#include "FastLED.h"
//next step is separating to a proper class but this is neat and small enough for now
//majority of mem use is NUM_LEDS*3 + NUM_LEDS*2
#define NUM_LEDS 60

struct map2d {
  byte x[NUM_LEDS];
  byte y[NUM_LEDS];
};

//struct map2d mapping ={
//{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19},
//{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
//};
struct map2d mapping = {
  {248, 248, 250, 248, 252, 237, 233, 234, 233, 233, 211, 212, 212, 212, 215, 187, 184, 184, 184, 184, 164, 164, 164, 163, 165, 145, 143, 144, 144, 143, 107, 104, 103, 103, 100, 81, 84, 84, 84, 87, 68, 65, 65, 65, 61, 38, 42, 41, 43, 45, 27, 24, 23, 24, 19, 5, 6, 7, 8, 9},
  {73, 100, 127, 157, 182, 183, 155, 128, 101, 73, 72, 100, 127, 154, 182, 179, 151, 123, 96, 68, 67, 94, 120, 147, 174, 171, 145, 119, 93, 67, 85, 110, 135, 157, 183, 181, 159, 134, 108, 84, 85, 108, 133, 157, 180, 182, 158, 132, 108, 84, 86, 109, 133, 157, 180, 177, 156, 132, 107, 84}
};

CRGB leds[NUM_LEDS];

long lastModeChange = 0;

#define LED_PIN 4
#define CLOCK_PIN 5
CRGBPalette16 currentPalette( PartyColors_p );
CRGBPalette16 targetPalette( PartyColors_p );

TBlendType  currentBlending;

void setup() {
  Serial.begin(115200);
  //  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<APA102, LED_PIN, CLOCK_PIN, BGR, DATA_RATE_MHZ(24)>(leds, NUM_LEDS);
  FastLED.setDither(false);
  //  FastLED.show();
  currentBlending = LINEARBLEND;
  setRandomTargetPalette();

}

void loop() {

  if (millis() - lastModeChange > 12000) {
    setRandomTargetPalette();
  }
  mapTestQuadrants();//fill leds with simple 2d noise pattern that moves in 3rd dimension
  nblendPaletteTowardPalette(currentPalette, targetPalette, 2);
  FastLED.show();
}


void mappedNoiseBasic() {
  //simple 2d noise pattern that moves through 3rd dimension for nice swirly movement
  int noiseTempThing = 0;
  uint16_t scale = 2;
  int timeVal = (int)(millis() >> 2);
  for (int i = 0; i < NUM_LEDS; i++) {
    noiseTempThing = inoise8(mapping.x[i] * scale, mapping.y[i] * scale, timeVal);
    leds[i] = ColorFromPalette( currentPalette, noiseTempThing, 255, currentBlending);
  }
}


void verticalOneDimensionScroll() {
  //all pixels at same y get same value, constantly scrolls up
  uint16_t timeVal = (uint16_t)(millis() >> 2);
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
  //mirror on 45 axis
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
  //fast single pixel move around whole strip, no mapping.
  uint16_t currentpos = (uint16_t)(millis() / 100);
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


