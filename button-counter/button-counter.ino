
int count = 0;
int buttonState = 0;
int lastButtonState = 0;

const int buttonPin = 23;


void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

}

void loop() {

  buttonState = digitalRead(buttonPin);

  if(buttonState != lastButtonState) {
    if(buttonState == HIGH) {
      count++;
      Serial.println(count);
      }
    }
   delay(50);
   lastButtonState = buttonState;
} 
