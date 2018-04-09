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



If you are reading this just now hold your horses, i'm a few tests away from making a proper version 1.0 alpha for a more public release. 
