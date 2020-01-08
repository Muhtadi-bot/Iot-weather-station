#include <SoftwareSerial.h>
#include<dht.h>
dht DHT;
#define DHT11_PIN 3
SoftwareSerial nodemcu(2,4);


// lowest and highest rain sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

//For CO sensor
const int AOUTpin=1;//the AOUT pin of the CO sensor goes into analog pin A0 of the arduino
const int DOUTpin=8;//the DOUT pin of the CO sensor goes into digital pin D8 of the arduino
const int ledPin=13;//the anode of the LED connects to digital pin D13 of the arduino

int limit;
int value;

// Optical Dust Sensor
int measurePin = A5;
int ledPower = 12;

unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;

float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;


String cdata;
void setup() {
 Serial.begin(9600);
 nodemcu.begin(9600);
 //For CO sensor
  pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
  pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino

// For Optical Dust Sensor
  pinMode(ledPower,OUTPUT);

}

void loop() {
//DHT11 Temperature Humidity Code

int chk = DHT.read11(DHT11_PIN);
float v1 = DHT.humidity;
float v2 = DHT.temperature;
Serial.println(" Humidity " );

Serial.println(DHT.humidity, 1);

Serial.println(" Temparature ");

Serial.println(DHT.temperature, 1);
delay(10);

//Rain Module Sensor Code

// read the sensor on analog A0:
int sensorReading = analogRead(A0);
  // map the sensor range (four options):
  // ex: 'long int map(long int, long int, long int, long int, long int)'
int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
 String v3 = "";
  // range value:
  switch (range) {
 case 0:    // Sensor getting wet
 v3 = "Flood";
    Serial.println("Flood");
    
    break;
 case 1:    // Sensor getting wet
 v3 = "Rain Warning";
    Serial.println("Rain Warning");
    break;
 case 2:    // Sensor dry - To shut this up delete the " Serial.println("Not Raining"); " below.
 v3 = "Not Raining";
    Serial.println("Not Raining");
    break;
  }
  delay(10);

//MQ-7 CO Sensor Code

  value= analogRead(AOUTpin);//reads the analaog value from the CO sensor's AOUT pin
  limit= digitalRead(DOUTpin);//reads the digital value from the CO sensor's DOUT pin
  Serial.print("CO value: ");
  Serial.println(value);//prints the CO value
  int v4 = value;
  Serial.print("Limit: ");
  Serial.println(limit);//prints the limit reached as either LOW or HIGH (above or underneath)
  int v5 = limit;
  delay(10);
  if (limit == HIGH){
    digitalWrite(ledPin, HIGH);//if limit has been reached, LED turns on as status indicator
  }
  else{
    digitalWrite(ledPin, LOW);//if threshold not reached, LED remains off
  }

  //Optical Dust Sensor Code
digitalWrite(ledPower,LOW);
  delayMicroseconds(samplingTime);

  voMeasured = analogRead(measurePin);

  delayMicroseconds(deltaTime);
  digitalWrite(ledPower,HIGH);
  delayMicroseconds(sleepTime);

  calcVoltage = voMeasured*(5.0/1024);
  dustDensity = 0.17*calcVoltage-0.1;

  if ( dustDensity < 0)
  {
    dustDensity = 0.00;
  }

 // Serial.println("Raw Signal Value (0-1023):");
 // Serial.println(voMeasured);

 // Serial.println("Voltage:");
 // Serial.println(calcVoltage);

  Serial.println("Dust Density:");
  Serial.println(dustDensity);
  float v6 = dustDensity;
cdat  a = cdata +v1+","+v2+","+v3+","+v4+","+v5+","+v6+","; // comma will be used a delimeter
   Serial.println(cdata); 
   nodemcu.println(cdata);
   delay(1000); // 100 milli seconds
   cdata = ""; 

}
