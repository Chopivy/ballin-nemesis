//LM35 leży jak U
//Pin 1 of the LM35 goes into +5V of the arduino
//Pin 2 of the LM35 goes into analog pin A0 of the arduino
//Pin 3 of the LM35 goes into ground (GND) of the arduino
//http://goo.gl/Bd60lX

int rawdata;
int tempPin = 0;
float celsius;
float millivolts;


void setup() {
  Serial.begin(9600);
}

void loop() {
  rawdata = analogRead(tempPin);
  millivolts = (rawdata/1024.0) * 5000;
  celsius = millivolts / 10;
  Serial.print(celsius);
  Serial.println();
  delay(10000);
}
