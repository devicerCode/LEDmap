# LEDmap
##### Processing and Arduino code for automatic addressable LED mapping

Ever have trouble showing fancy patterns on LEDs because your layout is chaotic or a zigzag and you can't address the lights easily in order? This code is designed to give you a mapping output that contains the coordinates of each light ready to paste into your arduino pattern code and it does so semi-automatically by using a webcam to detect the position of each light.


The code here is in two parts - the arduino part and the processing part. You need to flash your arduino compatible microcontroller of choice with the arduino part, then connect to it using the (hopefully) platform independent processing sketch.

### Dependencies
##### Arduino part
- FastLED
##### Processing part
- controlP5
- blobDetection http://www.v3ga.net/processing/BlobDetection/libraries
- processing serial (built in)
- processing video (built in)
- java.util (you should also have this!)

You quite possibly have all but the blobDetection library already. There are lots of tutorials available elsewhere if you need assistance with installing libraries but it should be very simple with the new library managers.

### Ouput style

Currently there's one useable output style - outputting byte values (0-255) for each coordinate in the format:

```
struct map2d {
  byte x[NUM_LEDS];
  byte y[NUM_LEDS];
};
```
It's small, it's simple and it's easy to address the coords of an LED by using int xcoord = mapping.x[position]

For convenience saving the output creates a line for copy and pasting with the NUM_LEDS so an example output is:
```
#define NUM_LEDS 20
struct map2d mapping ={
{248,249,249,248,252,237,233,234,233,233,211,212,212,212,215,187,185,184,184,184},
{73,100,127,157,182,183,155,128,101,73,72,100,127,154,182,179,151,123,96,68}
};
```
See the included "Examples" folder for examples of useage using fastLED.



If you are reading this just now stay tuned for more documentation and proper 1.0 release when I'm a bit happier with how useful it is but it should be useable right now. This is a completely rewritten from scratch version of my old unwieldy hacky code, it lacks a huge number of features which I will hopefully be adding in soon, see 'issues' for some of them.
