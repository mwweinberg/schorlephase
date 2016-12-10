
#include <Adafruit_NeoPixel.h>


// pixel control pin
#define PIN            6

// number of pixels
#define NUMPIXELS      1

// intitialize neopixel object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);



void setup() {

  //initialize neopixels
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {

  //sets the color
  strip.setPixelColor(0, 255, 69, 0); //pixel number, r,g,b
  //pushes change to neopixels
  strip.show();
  //waits 300ms
  delay(300);
  strip.setPixelColor(0, 255, 0, 255);
  strip.show();
  delay(300);
  strip.setPixelColor(0, 100, 69, 200);
  strip.show();
  delay(300);
  

  
}
