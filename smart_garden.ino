#include <time.h>
#include <Servo.h>
#define delayTime 20
#include <dht.h>
#define DHT11_PIN 7
dht DHT;

//temperature//
int ptemp;//temperature needed
//temperature

//servo
boolean servo = false;
Servo myservo;
int pos = 0;//servo position
//servo 

//watering
int solenoidPin = 4; 
int rainPin = A0;
int thresholdValue = 50;
//watering

//led
int ledW = 6;
int templed1 = 11; //appropriate temperature
int templed2 = 12; //temperature's to low
//led 

//potentiometer
int potPin = 2;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the potentiometer
//potentiometer

void setup() {
  // put your setup code here, to run once:
myservo.attach(9);//servo is on port 9/ check what port it is connected to

Serial.begin(9600);
pinMode(rainPin, INPUT);
pinMode(solenoidPin, OUTPUT); 

}

void loop() {

 
int sensorValue = analogRead(rainPin);

sensorValue = map(sensorValue, 300,1023,100,0);//measure 0 value
Serial.print("Soil Humidity needed= ");
Serial.println(thresholdValue);
Serial.print("Soil Humidity= ");
Serial.println(sensorValue);

if(sensorValue < thresholdValue){

 
  digitalWrite(ledW,HIGH);
  Serial.println("Need irrigation"); //Blue LED
  digitalWrite(solenoidPin, LOW);
  
//
}

else if(sensorValue > thresholdValue || sensorValue == thresholdValue){

  
  digitalWrite(ledW,LOW);
  Serial.println("Doesn't need irrigation");
 digitalWrite(solenoidPin, HIGH);
}

val = analogRead(potPin);    // read the value from the potent
val=map(val, 0,1023,50,0);
ptemp=16;
  Serial.print("Temperature needed= ");
  Serial.println(ptemp);


  //ggg
  int chk = DHT.read11(DHT11_PIN);
  
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);//check delay to make serial prints at lower rates
  //ggg

 
 


   if ((DHT.temperature) > (ptemp)){ //check () in DHT.temperature 
 digitalWrite(templed1, HIGH);
 //check with serial print
Serial.print("temperature higher than needed");

for (pos = 0; pos <= 25; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  }

 

  
   
   else if ((DHT.temperature)<(ptemp) || (DHT.temperature) == (ptemp) ){
    

digitalWrite(templed2, HIGH);

for(pos = 25; pos >= 0; pos -= 1){
  myservo.write(pos);
  delay(15);
}

  //make servo open

  //create opening loop, with boolean, so that code doesn't repeat
   
   }

}







