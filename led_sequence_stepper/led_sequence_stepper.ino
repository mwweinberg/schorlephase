#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"


// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int counter = 0;
int stateTracker = 0;          // used to prevent double off-sequencing

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

  //stepper stuff
  AFMS.begin();  // create with the default frequency 1.6KHz
  myMotor->setSpeed(100);  // 100 rpm - to get faster need to change code
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
  myMotor->step(1000, FORWARD, SINGLE); 
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(500);
  digitalWrite(ledPin, HIGH);
  counter = 1;
  stateTracker = 1;
  Serial.println("Startup complete");
  
}

// this is the on function
void on() {
  Serial.println("On");
  // may add a count on this line at some point
  digitalWrite(ledPin,  HIGH);
  //increases counter
  counter += 1;
  Serial.print("Counter is: ");
  Serial.println(counter);
}

//  this is the shutdow function
void turnoff() {
  Serial.println("shutdown");
  myMotor->step(1000, BACKWARD, SINGLE);
  // a series of faster flashes
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  delay(200);
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
  counter = 0;
  stateTracker = 0;
  
}

