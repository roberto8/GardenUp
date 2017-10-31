#include <time.h> //make parameter to controll water irrigation making it irrigate for less then (x) value
#include <Servo.h>
#define delayTime 20 //var not in use
#include <dht.h>  //moisture and temperature sensor (dht.11)
#define DHT11_PIN 7 //temperature and moisture sensor atached to port 7 (digital)
dht DHT;

//temperature//
int ptemp;//temperature needed
//temperature

//servo
boolean servo = false;
Servo servotop;
int pos = 0;//servo starts in position 0 (closed)
//servo

//watering
int solenoidPin = 4; //solenoid pin atached to port 4 (not using solenoid) no relay
//sensor humidade porta A0//
int rainPin = A0; //soil moisture sensor 1
//sensor humidade porta A0//
//int rainPin2 = A1; //soil moisture sensor 2 not in use
int thresholdValue = 50; //moisture needed (%)
//watering

//led
int tempH = 10; //temperature's high
int tempL = 11; //temperature's  low
int SoilMoistureH = 12; //SoilMoisture's high
int SoilMoistureL = 13; //SoilMoisture's Low
//led

//potentiometer
int potPin = 2;    // select the input pin for the potentiometer //not in use
int val = 0;       // variable to store the value coming from the potentiometer
//potentiometer

void setup() {

servotop.attach(9); //SERVO ataches to port 9
servobottom.attach(8)//SERVO attaches to port 8 (bottom servo)

Serial.begin(9600);
pinMode(rainPin, INPUT);
pinMode(solenoidPin, OUTPUT);
pinMode(tempH, OUTPUT);
pinMode(tempL, OUTPUT);
pinMode(SoilMoistureH, OUTPUT);
pinMode(SoilMoistureL, OUTPUT);
ptemp=20;
}

void loop() {


int sensorValue =  (analogRead(rainPin)); //using to moisture sensors to do the average

sensorValue = map(sensorValue, 300,1023,100,0); //maping moisture value from 0-100 (percentage)
Serial.print("Soil Humidity needed= ");
Serial.println(thresholdValue);
Serial.print("Soil Humidity= ");
Serial.println(sensorValue);

if(sensorValue < thresholdValue){


  digitalWrite(SoilMoistureL,HIGH);
  digitalWrite(SoilMoistureH,LOW);
  Serial.println("Need irrigation");
  digitalWrite(solenoidPin, LOW);

// if irrigation needed indicating LED will light up and print, solenoid open (LOW signal, normaly open)
}

else if (sensorValue > thresholdValue || sensorValue == thresholdValue) {


  digitalWrite(SoilMoistureL,LOW);
  digitalWrite(SoilMoistureH,HIGH);
  Serial.println("Doesn't need irrigation");
 digitalWrite(solenoidPin, HIGH);
// if no irrigation needed indicating LED will light up and print, solenoid close (HIGH signal, normaly open)
}

val = analogRead(potPin);    // read the value from the potentiometer
val=map(val, 0,1023,50,0); //map potentiometer value from 0 to 50 (ºC)
 //temperature is set by the potentiometer in 0-50ºC scale ("val" var)
  Serial.print("Temperature needed= ");
  //Serial.println(ptemp);


  int chk = DHT.read11(DHT11_PIN);

  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);//check delay to make serial prints at lower rates






   if (((DHT.temperature) > (ptemp)) && (pos!=90)){  //if temperature is HIGHER then needed (defined by var "val") and door is closed

Serial.print("temperature higher than needed");
digitalWrite(tempH, HIGH);
digitalWrite(tempL, LOW);
for (pos = 0; pos <= 90; pos =+1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servotop.write(pos);              // tell servo to go to position in variable 'pos'
    //Serial.print(pos);
    delay(15);                      // waits 15ms for the servo to reach the position
  }

  }
   else if ((DHT.temperature)<=ptemp && (pos == 90))
   {


digitalWrite(tempH, LOW);
digitalWrite(tempL, HIGH);

for(pos = 90; pos >= 0; pos -= 1){
  servotop.write(pos);
  Serial.print(pos);
  delay(15);
}



   }


}
