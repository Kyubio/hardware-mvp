#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial bluetoothObject; //Object for Bluetooth

int incoming;

void setup() {
  Serial.begin(9600); //Start Serial monitor in 9600
  bluetoothObject.begin("Kyubio SF-05-K9"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");

  pinMode (LED_BUILTIN, OUTPUT);//Specify that LED pin is output
}

void loop() {
  
  if (bluetoothObject.available()) //Check if we receive anything from Bluetooth
  {
    incoming = bluetoothObject.read(); //Read what we recevive 
    Serial.print("Received:"); Serial.println(incoming);

    if (incoming == 49)
        {
        digitalWrite(LED_BUILTIN, HIGH);
        bluetoothObject.println("LED turned ON");
        }
        
    if (incoming == 48)
        {
        digitalWrite(LED_BUILTIN, LOW);
        bluetoothObject.println("LED turned OFF");
        }     
  }
  delay(20);
}
