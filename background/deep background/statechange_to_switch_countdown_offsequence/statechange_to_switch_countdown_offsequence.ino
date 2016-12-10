// this constant won't change:
const int  buttonPin = 2;    // the pin that the pushbutton is attached to
const int ledPin = 13;       // the pin that the LED is attached to

// Variables will change:
int buttonPushCounter = 0;   // counter for the number of button presses
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int tracker = 0;             //this tracks to see if the windown sequence has fininshed


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
    if ((buttonState == HIGH) && (tracker == 0)) {
      //this sequence is beginning so the tracker is set to true
      Serial.print("T1: ");
      Serial.println(tracker);
      //tracker = 1;
      // this is the action section, simulates the flag being up
      Serial.println("HIGH");
      Serial.print("T2: ");
      Serial.println(tracker);
      digitalWrite(ledPin, HIGH);
      delay(3000);
      

      // this simulates winding down (switch going off, flag lowering)
      Serial.println("HIGH off begin");
      digitalWrite(ledPin, LOW);
      delay(400);
      digitalWrite(ledPin, HIGH);
      delay(400);
      digitalWrite(ledPin, LOW);
      delay(400);
      digitalWrite(ledPin, HIGH);
      delay(400);
      digitalWrite(ledPin, LOW);
      
      //now the tracker knows the entire thing is complete
      Serial.print("T3: ");
      Serial.println(tracker);
      tracker = 0;
      Serial.print("T4: ");
      Serial.println(tracker);
      Serial.println("HIGH off complete");
    } 

    
    // if the switch is set of LOW but the winding down sequence hasn't completed, complete it
    if ((buttonState == HIGH) && (tracker = 1)) {
      // this simulates winding down (switch going off, flag lowering)
      Serial.print("T5: ");
      Serial.println(tracker);
      Serial.println("safety HIGH off begin");
      Serial.println(tracker);
      digitalWrite(ledPin, LOW);
      delay(400);
      digitalWrite(ledPin, HIGH);
      delay(400);
      digitalWrite(ledPin, LOW);
      delay(400);
      digitalWrite(ledPin, HIGH);
      delay(400);
      digitalWrite(ledPin, LOW);
      Serial.println("safety HIGH off complete");
      
      //now the tracker knows the entire thing is complete
      tracker = 0;
      Serial.print("T6: ");
      Serial.println(tracker);
    }
    
    
    // if the button is low and the tracker is false, everything is put away and should stay that way
    if ((buttonState == LOW) && (tracker = 0))     
    {
      Serial.print("T7: ");
      Serial.println(tracker);
      Serial.println("LOW");
      digitalWrite(ledPin, LOW);
    }

    tracker = tracker;
   
  }
  // save the current state as the last state,
  //for next time through the loop
  lastButtonState = buttonState;


}

