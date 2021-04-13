//als button na een aantal seconden geen input meer heeft gaat de trilmotor af. 

const int trilMotorPin = 22;
const int buttonPin = 23; 

int buttonState; 
int lastButtonState = LOW;  
int count = 0;
bool trilMotorToggle = true;

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

unsigned long trilTimer;
unsigned long trilTime = 5000;

void setup() 
{
  pinMode(trilMotorPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  int reading = digitalRead(buttonPin);


  if (reading != lastButtonState) 
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) 
  {
    if (reading != buttonState) 
    {
      buttonState = reading;
      if(buttonState == HIGH)
      {
        count++;
        Serial.println(count);
        trilmotorOff(); 
        trilTimer = millis();    
      }

    }
  }
  lastButtonState = reading;
  if ((millis()- trilTimer) >  trilTime && trilMotorToggle == true)
  {
    trilmotorOn();  
  }
}


void trilmotorOn()
{
  digitalWrite(trilMotorPin, HIGH);
}

void trilmotorOff() 
{
  digitalWrite(trilMotorPin, LOW);
}
