#define LED 13
#define BUTTON 2

int val = 0;
int old_val = 0;
int state = 0;
int counter = 0;

void setup()
{
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  
}

void loop()
{
  val = digitalRead(BUTTON);

  if ((val == HIGH) && (old_val == LOW))
  {
    state = 1 - state;
    delay(30);
 
  }

  old_val = val;

  if (state == 1 && counter ==0)
  {
    digitalWrite(LED, HIGH);
    delay(3000);
    counter = 1;
    digitalWrite(LED, LOW);
  }
  if (state == 1 && counter == 1)
  {
    digitalWrite(LED, LOW);
  }
  else
  {
    digitalWrite(LED, LOW);
    counter = 0;
  }
  
}

