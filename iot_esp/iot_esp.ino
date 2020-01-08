 #define BLYNK_PRINT Serial
#include <SoftwareSerial.h>

#include <ESP8266WiFi.h>
#include <SimpleTimer.h>
#include <BlynkSimpleEsp8266.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = " kBxjoansoP3DOXys4UHwnZnISZQ7Xqw8"; //Enter the Auth code which was send by Blink

// Your WiFi credentials.
// Set password to "" for open networks.
const char* ssid="Ananna";
const char* password = "zjra6533";

SimpleTimer timer;
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors

float Val1, Val2,Val6;
String Val3="";
int Val4, Val5;


void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V1, millis() / 1000);
  
}
void setup() {
  Serial.begin(9600); // See the connection status in Serial Monitor
  WiFi.begin(ssid,password);
  Blynk.begin(auth, ssid, password);
  timer.setInterval(1000L,sensorvalue1); 
       timer.setInterval(1000L,sensorvalue2);

     timer.setInterval(1000L,sensorvalue3);
     timer.setInterval(1000L,sensorvalue4); 
       timer.setInterval(1000L,sensorvalue5);
       timer.setInterval(1000L,sensorvalue6);

}

void loop() {
  if (Serial.available() == 0 ) 
   {
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
   }
     if (Serial.available() > 0 ) 
  {
    rdata = Serial.read(); 
    Serial.print(rdata);
    myString = myString+ rdata; 
   // Serial.print(rdata);
    if( rdata == '\n')
    {
   //  Serial.println(myString); 
  // Serial.println("fahad");
// new code
String h = getValue(myString, ',', 0);
String t = getValue(myString, ',', 1);
String r = getValue(myString, ',', 2);
String v = getValue(myString, ',', 3);
String l = getValue(myString, ',', 4); 
String d = getValue(myString, ',', 5); 
 
 Val1 = h.toFloat();
 Val2 = t.toFloat() ;
 Val6 = d.toFloat();
 Val3 = "";
 Val3 = Val3+r;
 Val4 = v.toInt();
  Val5 = l.toInt();
  if(Val3 == "Rain Warning" ||  (Val2 >=90.00 && Val2>=27.00 )){
    notify1();
  }
  if(Val3 == "Flood" ){
    notify2();
  }

 
  myString = "";
  
// end new code
    }
  }

}
void sensorvalue1()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, Val1);
 
}
void sensorvalue2()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V6, Val2);
 
}
void sensorvalue3()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V7, Val3);
 
}
void sensorvalue4()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V8, Val4);
 
}
void sensorvalue5()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V9, Val5);
 
}
void sensorvalue6()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V10, Val6);
 
}
void notify1(){
  String notify = "WARNING: Take your umbrella with you "; 
  Blynk.notify(notify);
  }
  void notify2(){
  String notify = "Don't Go Outside Today"; 
  Blynk.notify(notify);
  }

String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
