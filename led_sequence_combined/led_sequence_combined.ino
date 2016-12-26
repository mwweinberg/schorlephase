// *******libraries
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// *******these constants won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to
//LED constants
const int neoPin = 6;         //neopixel control pin
const int pixelQuant = 1;     // number of neopixels
//servo constant
const int servoPin = 9;     // the pin that the servo is attached to
//sound Pin
const int upPin = 4;
const int pingPin = 3;
const int downPin = 5;
// how long the on operiod should be
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
//servo varialbe
int angle = 0;              // servo position in degrees

//********other initialization things
// intitialize neopixel object
Adafruit_NeoPixel strip = Adafruit_NeoPixel(pixelQuant, neoPin, NEO_RGB + NEO_KHZ800);
//defines the servo
Servo servo;
// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
// Connect a stepper motor with 200 steps per revolution (1.8 degree)
// to motor port #2 (M3 and M4)
Adafruit_StepperMotor *myMotor = AFMS.getStepper(200, 2);



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

  //initializes the servo
  servo.attach(servoPin);
  //sets servo at 0 degrees
  servo.write(0);

  //initialize the stepper
  AFMS.begin();  // create with the default frequency 1.6KHz
  myMotor->setSpeed(100);  // 100 rpm - to get faster need to change code

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
  if ((counter > 0) && (counter < onTime)) {
    on();
  }


  // if counter > 99 it is time to shut down
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
  myMotor->step(1000, FORWARD, SINGLE);

  //*******cleanup section
  counter = 1;
  stateTracker = 1;
  Serial.println("Startup complete");
  
}

// this is the on function
void on() {
  Serial.println("On");

  //***** Tone Section
  //trigger the ping
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


  //*****LED section
  // turns off neopixels
  strip.setPixelColor(0, 0, 0, 0); //pixel number, r,g,b
  strip.show();

  //*****servo section
  //start at angle 0 and then move towards 180
  for(angle = 0; angle < 180; angle++) {
    //update the servo with the new angle
    servo.write(angle);
    delay(15);
  }
  // now come back
  for(angle = 180; angle >0; angle--) {
    servo.write(angle);
    delay(15);
  }

  //*****stepper section
  myMotor->step(1000, BACKWARD, SINGLE);

  //***** Tone Section
  //trigger the down music
  digitalWrite(downPin, LOW);
  delay(200);
  digitalWrite(downPin, HIGH);
  //this is for the on ping reset
  pingTracker = 0;
  
  //*****cleanup section
  counter = 0;
  stateTracker = 0;
  
}

