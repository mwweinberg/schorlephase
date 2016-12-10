// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
boolean tracker = false;  // apparently booleans use up less data than ints, since this is just a 1 or 0 
// to track if the HIGH function is still running I used the boolean


void setup() {
  // initialize the button pin as a input:
  pinMode(buttonPin, INPUT);
  // initialize the LED as an output:
  pinMode(ledPin, OUTPUT);
  // initialize serial communication:
  Serial.begin(9600);
}


void loop() {
  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state and see if it changed
  if (buttonState != lastButtonState) {
    // Delay a little bit to avoid bouncing
    delay(50);
    // if the state has is high and the countdown isn't running
    if ((buttonState == HIGH) && (tracker == false)) {

      
      Serial.println("HIGH");
      digitalWrite(ledPin, HIGH);
      delay(3000);
      tracker = true;
      digitalWrite(ledPin, LOW);
      Serial.println("HIGH off");
      tracker = false;
      
    } 
    else
    
    {
      // if the current state is LOW then the button
      // went from on to off:
      Serial.println("LOW");
      digitalWrite(ledPin, LOW);
    }
   
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;


}

