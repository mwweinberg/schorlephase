// *******libraries
#include <Adafruit_NeoPixel.h>
#include <Stepper.h>

// *******these constants won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to (may be legacy for pre-neopixel)
//LED constants
const int neoPin = 11;         //neopixel control pin
const int pixelQuant = 1;     // number of neopixels
//sound Pin
const int upPin = 4;
const int pingPin = 3;
const int downPin = 5;
// how long the on period should be
const int onTime = 300;



// *******these variables will change:
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int counter = 0;
int stateTracker = 0;          // used to prevent double off-sequencing
int pingTracker = 0;        // used to make the ping in the on phase happen only once
//LED variables
int redVal = 255;            // used to fade out LED. Starts at 255 to match startup val
int greenVal = 0;             //used to fade in LED
//stepper variables
//number of steps you want the motor to take
#define STEPS 600


//********other initialization things
// intitialize neopixel object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelQuant, neoPin, NEO_RGB + NEO_KHZ800);
// create an instance of the stepper, specifiying number of steps and pins
Stepper stepper(STEPS, 7, 8, 9, 10);



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

  //initialize the stepper
  // speed in RPM - keep it below 25
  stepper.setSpeed(10);

  //initilizes the audio pin
  pinMode(upPin,OUTPUT);
  digitalWrite(upPin, HIGH);
  pinMode(pingPin,OUTPUT);
  digitalWrite(pingPin, HIGH);
  pinMode(downPin,OUTPUT);
  digitalWrite(downPin, HIGH);
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
    // if the state changed, the switch is high, and the flag is down
    //pushing the button means that it is time for startup
    if ((buttonState == HIGH) && (counter == 0)) {

      startup();
      
    } 

    //if the state changed, the switch is high, and the flag is up
    // pushing the botton means that it is time to shut down early
    //conter >1 instead of >0 becasue it gets set to 1 in startup so will be 1 before completing this
    //sub routine
    if ((buttonState == HIGH) && (counter > 1)) {
      turnoff();
    }

    
   
   
  }

  
  //****************************************************
  /* while it is on sequences */
  //****************************************************

  // if the counter > 0 the startup sequence has been initiated
  if ((counter > 0) && (counter < onTime)) {
    on();
  }


  // if counter > onTime it is time to shut down
  if (counter > (onTime-1)) {
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

  //*******LED section
  ////this section is optional for if you want a color on during the on sequence
  ////I think you don't, but just in case I'm leaving it as a placeholder
  ////sets the color
  //strip.setPixelColor(0, 255, 0, 0); //pixel number, r,g,b
  ////pushes change to neopixels
  //strip.show();

  //*******Tone section
  //trigger the sound
  digitalWrite(upPin, LOW);
  delay(200);
  digitalWrite(upPin, HIGH);

  //*******Stepper section
  //goes up STEPS steps
  stepper.step(STEPS);

  //*******cleanup section
  counter = 1;
  stateTracker = 1;
  pingTracker = 0;
  Serial.println("Startup complete");
  
}

// this is the on function
void on() {
  Serial.println("On");

  //***** Tone Section
  //trigger the ping
  //^^^^^^^^NOTE: ping won't trigger if the startup song ends after the stepper stops in startup()^^^^^
  if (pingTracker == 0) {
    digitalWrite(pingPin, LOW);
    delay(200);
    digitalWrite(pingPin, HIGH);
    //tells the variable that ping has already happened
    pingTracker = 1;
  }

  //*****LED section
  // allows the LED to fade out
  // counter is how far it is into the counter sequence
  // 0 is the lowest counter number, 100 is the highest number
  // 255 is where the output number should start (because it is on when counter = 0
  // 0 is where the output ends when the counter  hits 100
  redVal = map(counter, 0, onTime, 255, 0); 
  // turns up the green as the red fades out
  greenVal = map(counter, 0, onTime, 0, 255);  
  //sets the color
  strip.setPixelColor(0, redVal, greenVal, 0); //pixel number, r,g,b
  //pushes change to neopixels
  strip.show();

  //******cleanup section
  //increases counter
  counter += 1;
  Serial.print("Counter is: ");
  Serial.println(counter);
}

//  this is the shutdow function
void turnoff() {
  Serial.println("shutdown");


  //***** Tone Section
  //trigger the down music
  digitalWrite(downPin, LOW);
  delay(200);
  digitalWrite(downPin, HIGH);
  //this is for the on ping reset
  pingTracker = 0;

  //*****LED section
  // turns off neopixels
  strip.setPixelColor(0, 0, 0, 0); //pixel number, r,g,b
  strip.show();
  

  //*****stepper section
  // goes down STEPS steps (down because it is negative)
  stepper.step(-STEPS);


  
  //*****cleanup section
  counter = 0;
  stateTracker = 0;
  
}
