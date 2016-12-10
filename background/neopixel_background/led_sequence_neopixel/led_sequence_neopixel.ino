
#include <Adafruit_NeoPixel.h>

// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to
const int neoPin = 6;         //neopixel control pin
const int pixelQuant = 1;     // number of neopixels

// Variables will change:
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int counter = 0;
int stateTracker = 0;          // used to prevent double off-sequencing

// intitialize neopixel object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelQuant, neoPin, NEO_RGB + NEO_KHZ800);

void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);

  //initialize neopixels
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  //****************************************************
  /* state change sequences */
  //****************************************************

  // compare the buttonState to its previous state and see if it changed
  if (buttonState != lastButtonState) {
    // Delay a little bit to avoid bouncing
    delay(50);
    // if the state changed and the switch is high
    if (buttonState == HIGH) {

      startup();
      
    } 

    // if the state changed and the switch is low
    if ((buttonState == LOW) && (stateTracker == 1))
    
    {
      turnoff();
    }
   
   
  }

  
  //****************************************************
  /* while it is on sequences */
  //****************************************************

  // if the counter > 0 the startup sequence has been initiated
  if ((counter > 0) && (counter < 100)) {
    on();
  }


  // if counter > 99 it is time to shut down
  if (counter > 99) {
    turnoff();
  }



  
  //****************************************************
  /* housecleaning sequence */
  //****************************************************
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;


}

//****************************************************
/* functions */
//****************************************************

// this function is "void" becuase it is not expected to return a value - it just does something
// this is the startup  sequence where it flashes the LED on 3 times for 1 second each and then stays on
void startup() {
  Serial.println("starting");
  //sets the color
  strip.setPixelColor(0, 244, 238, 66); //pixel number, r,g,b
  //pushes change to neopixels
  strip.show();
  counter = 1;
  stateTracker = 1;
  Serial.println("Startup complete");
  
}

// this is the on function
void on() {
  Serial.println("On");
  //sets the color
  strip.setPixelColor(0, 255, 100, 0); //pixel number, r,g,b
  //pushes change to neopixels
  strip.show();
  counter += 1;
  Serial.print("Counter is: ");
  Serial.println(counter);
}

//  this is the shutdow function
void turnoff() {
  Serial.println("shutdown");
  // turns off neopixels
  strip.setPixelColor(0, 0, 0, 0); //pixel number, r,g,b
  strip.show();
  counter = 0;
  stateTracker = 0;
  
}

