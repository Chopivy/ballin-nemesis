//Conecting LM35 sensor on Arduino Yun board with Nod-RED flow
#include <SPI.h>
#include <Bridge.h>
#include <YunClient.h>
#include <PubSubClient.h>
// Update these with values suitable for your network.
byte server[] = { 192, 168, 1, 11 }; // mosquitto
char buff[5];

void callback(char* topic, byte* payload, unsigned int length);

YunClient yun;
PubSubClient client(server, 1883, callback, yun);
int rawData;
String data;
int analogPin = 0;
int len;
int i;

///yun/sensor/1: LM35
//Pin ================ Yun
//  1 ================ +5V
//  2 ================ A0
//  3 ================ GND

void setup()
{
  Bridge.begin();
  Serial.begin(9600);
  if (client.connect("arduinoClient")) {
    Serial.println("client connected");
  }
}

void loop()
{
  rawData = analogRead(analogPin);
  data = String(rawData);
  len = data.length();
  
  for(i=0; i < len; i++)
    buff[i] = data[i];
  buff[i] = '\0';
  
  if (client.connect("arduinoClient")) {
    client.publish("yun/sensor/1", buff);
    Serial.println(data);
   }
}
void callback(char* topic, byte* payload, unsigned int length) {
}

//nodeRed flow:
// <mqtt| <f()> |debug>
// <mqtt|: Broker="localhost:1883"; Topic="yun/sensor/1"
// <f()>: var tempC = parseInt(msg.payload) * (500/1024);
//        msg.payload = tempC.toString();
//        return msg;
