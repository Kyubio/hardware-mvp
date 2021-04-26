//Libraries die gebruikt worden
#include <SPI.h>
#include <WiFi.h>
#include <Ethernet.h>
#include <PubSubClient.h>

//variabelen die aangemaakt worden
const char* ssid     = "Kappa123";
const char* password = "Maanlanding";
const char* server = "broker.mqttdashboard.com";


//callback functie wordt aangeroepen vanuit de library en zorgt ervoor dat er berichten worden uitgelezen op de HiveMQ
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void reconnect() {
  
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    Serial.print("Attempting MQTT connection...");
    
    // Attempt to connect
    if (mqttClient.connect("arduinoClient")) {
      Serial.println("connected");
      
      // Wanneer er verbinding gemaakt is verzend dit bericht naar de broker (published berichten)
      mqttClient.publish("testTopic123","hello world");
      
      //Subribed op een topic (krijgt berichten binnen vanuit broker)
      mqttClient.subscribe("TestReceive");

      //Als hij niet verbonden is doet hij een delay
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(57600); //baud van de arduino

  mqttClient.setServer(server, 1883);//je zegt wat aangeroepen moet worden namelijk de server HiveMQ
  mqttClient.setCallback(callback);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
}

void loop()
{
  if (!mqttClient.connected()) {
    reconnect();
  }
  mqttClient.loop();
}
