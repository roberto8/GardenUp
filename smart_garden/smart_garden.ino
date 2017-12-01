#include <time.h> //make parameter to controll water irrigation making it irrigate for less then (x) value
#include <Servo.h>
#define delayTime 20 //var not in use
#include <dht.h>  //moisture and temperature sensor (dht.11)
#define DHT11_PIN 7 //temperature and moisture sensor atached to port 7 (digital)
dht DHT;
//const byte numPins = 8; //binary led temperature indicator
//int state;				// used for HIGH or LOW - binary
//byte pins [] = {0, 1, 3, 5, 6, 7, 8, 11, 12}; //check availability
//temperature//
int ptemp;//temperature needed
//temperature

//servo
boolean servo = false;
Servo servotop;
Servo servobottom;
int pos = 0;//servo starts in position 0 (closed)
//servo

//watering
int waterPin = 4;
//sensor humidade porta A0//
int rainPin = A0; //soil moisture sensor 1
//sensor humidade porta A0//
//int rainPin2 = A1; //soil moisture sensor 2 not in use
int thresholdValue = 50; //moisture needed (%)
//watering

//led
int tempH = 12; //temperature's high
int tempL = 13; //temperature's  low
int SoilMoistureL = 10; //SoilMoisture's Low
//led

//potentiometer
int potPin = 3;    // select the input pin for the potentiometer //not in use
int val = 0;       // variable to store the value coming from the potentiometer
//potentiometer

void setup() {

servotop.attach(9); //SERVO ataches to port 9
//servobottom.attach(8);//SERVO attaches to port 8 (bottom servo)

Serial.begin(9600);
pinMode(rainPin, INPUT);
pinMode(waterPin, OUTPUT);
pinMode(tempH, OUTPUT);
pinMode(tempL, OUTPUT);
pinMode(SoilMoistureL, OUTPUT);


//for(int i = 0; i < numPins; i++) {
 // pinMode(pins[i], OUTPUT);
//}

//check this code function
	//attachInterrupt(0, count, LOW); //count is not declared
//check this code function


}

void loop() {


int sensorValue =  (analogRead(rainPin)); //using to moisture sensors to do the average
Serial.println(analogRead(rainPin));
sensorValue = map(sensorValue, 250,1023,100,0); //maping moisture value from 0-100 (percentage)
Serial.print("Soil Humidity needed= ");
Serial.println(thresholdValue);
Serial.print("Soil Humidity= ");
Serial.println(sensorValue);

if(sensorValue < thresholdValue){


  digitalWrite(SoilMoistureL,HIGH);
  Serial.println("Need irrigation");
  digitalWrite(waterPin, LOW);

// if irrigation needed indicating LED will light up and print, solenoid open (LOW signal, normaly open)
}

else if (sensorValue > thresholdValue || sensorValue == thresholdValue) {


  digitalWrite(SoilMoistureL,LOW);
  Serial.println("Doesn't need irrigation");
 digitalWrite(waterPin, HIGH);
// if no irrigation needed indicating LED will light up and print, solenoid close (HIGH signal, normaly open)
}

//val = analogRead(potPin);    // read the value from the potentiometer
//val = map(val, 0,1023,50,0); //map potentiometer value from 0 to 50 (ºC)
 //temperature is set by the potentiometer in 0-50ºC scale ("val" var)
  Serial.println(analogRead(potPin));
  Serial.print("Temperature needed= ");
  ptemp=25;
  Serial.println(ptemp);
  
  /*





uint8_t bitsCount = sizeof( val ) * 8;
char str[ bitsCount + 1 ];

uint8_t i = 0;
while ( bitsCount-- )
    str[ i++ ] = bitRead( val, bitsCount ) + '0';
str[ i ] = '\0';

Serial.println( str );





*/

//add binary led for temperature

  int chk = DHT.read11(DHT11_PIN);

  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);







   if (((DHT.temperature) > (ptemp)) ){  //if temperature is HIGHER then needed (defined by var "val") and door is closed

Serial.println("temperature higher than needed");
digitalWrite(tempH, HIGH);
digitalWrite(tempL, LOW);
/*for (pos = 0; pos <= 90; pos =+1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    servotop.write(pos);              // tell servo to go to position in variable 'pos'
    //Serial.print(pos);
    delay(15);                      // waits 15ms for the servo to reach the position
  }*/
servotop.write(90);
  }
   else if ((DHT.temperature)<=ptemp )
   {


digitalWrite(tempH, LOW);
digitalWrite(tempL, HIGH);
/*
for(pos = 90; pos >= 0; pos -= 1){
  servotop.write(pos);
  Serial.print(pos);
  delay(15);
}
*/
servotop.write(0);

/*
String binNumber = String(ptemp, BIN); // change the vriable potentiometer to the potentiometer pin

int binLength = binNumber.length();
if(ptemp <= 255) {	// if we have less or equal to 255 presses
              // here is the scary code
  for(int i = 0, x = 1; i < binLength; i++, x+=2) {
    if(binNumber[i] == '0') state = LOW;
    if(binNumber[i] == '1') state = HIGH;
    digitalWrite(pins[i] + binLength - x, state);
  }
} else {
  // do something when we reach 255
}
*/
   }
delay(1000);
}
