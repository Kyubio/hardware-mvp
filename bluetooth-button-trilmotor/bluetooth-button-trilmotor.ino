//Libraries die gebruikt worden
#include <SPI.h>
#include "BluetoothSerial.h"

//bluetooth variabelen
BluetoothSerial bluetoothObject; //Object for Bluetooth
int incoming;

//variabelen button
const int buttonPin = 23; 
int buttonState; 
int lastButtonState = LOW;  
int count = 0;

//debounce
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//trilmotor
const int trilMotorPin = 22;
bool trilMotorToggle = false;//als de boolean op true wordt gezet begint als het ware de focus sessie. (Dit moet vanuit de app geregeld worden)

//timer trilmotor
unsigned long trilTimer;
unsigned long trilTime = 5000;


void setup()
{
  //bluetooth device pairing
  bluetoothObject.begin("Kyubio SF-05-K9"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  
  pinMode(trilMotorPin, OUTPUT);//trilmotor
  pinMode(buttonPin, INPUT); //button
  Serial.begin(57600); //baud van de arduino

}

void loop()
{
  if (bluetoothObject.available()) //Check if we receive anything from Bluetooth
  {
    incoming = bluetoothObject.read(); //Read what we recevive 
    incoming = incoming - 48;//omdat ze char versturen ipv int
    Serial.print("Received:"); Serial.println(incoming);

    if (incoming == 1)
        {
         trilMotorToggle = true;
         bluetoothObject.println("trilmotor aan");
         trilTimer = millis();
        }
        
    if (incoming == 0)
        {
         trilMotorToggle = false;
         bluetoothObject.println("trilmotor uit");
        }     
  }
  delay(20);


//button, debounce, trilmotor en timertrilmotor
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
        bluetoothObject.println(count);
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
