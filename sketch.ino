# include <WiFi.h>
#include "DHTesp.h"
#include "ThingSpeak.h"

const int DHTpin=15;
const char* ssid="Wokwi-GUEST";
const char* pass="";
const int chno=2476755;
const char* apikey="Y76266JNWL5QBAOA";
const char* server="api.thingspeak.com";
const int buzzpin= 18;
DHTesp dhtSensor;
WiFiClient client;


void setup() {
  
  Serial.begin(115200);
  dhtSensor.setup(DHTpin, DHTesp::DHT22);
  WiFi.begin("Wokwi-GUEST","" );
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("WiFi not connected");
  
  }
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
 pinMode(buzzpin,OUTPUT);
}

void loop() {
  TempAndHumidity data= dhtSensor.getTempAndHumidity();
  ThingSpeak.setField(1,data.temperature);
  ThingSpeak.setField(2,data.humidity);
  if (data.temperature>=40.00){
    Serial.println("Buzzer is on");
    digitalWrite(buzzpin,HIGH);
  }
  else{
    digitalWrite(buzzpin,LOW);
  }

  int status= ThingSpeak.writeFields(2476755,"Y76266JNWL5QBAOA");
  Serial.println(data.temperature);
  Serial.println(data.humidity);

  if(status==200){
    Serial.println("Data sent succesfully");
  }
  else{
    Serial.println("Error");
  }
  delay(1000);

  // put your main code here, to run repeatedly:
  delay(10); // this speeds up the simulation
}
