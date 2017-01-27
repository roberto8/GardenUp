#include <time.h>
#include <Servo.h>
#define delayTime 20
#include <dht.h>
#define DHT11_PIN 7
dht DHT;
boolean win=false;//tells if window is open or closed, used to send info to phone so that it can be sent all at the same time and we have a reference
int tempo; //make arduino clock
boolean wat;//water irrigation on or off
int ptemp;//temperature needed
int led = 13;
int pos = 0;//servo position
int buttonop = 4;//button port
boolean butopval = false;//button open HIGH/LOW
boolean butclval = true; //button closed HIGH/LOW
int buttoncl = 7;//button port

Servo myservo;

int potPin = 2;    // select the input pin for the potentiometer
int val = 0;       // variable to store the value coming from the sensor

void setup() {
  // put your setup code here, to run once:
myservo.attach(9);//servo is on port 9
pinMode (led, OUTPUT);
Serial.begin(9600);
pinMode(buttonop,INPUT);
pinMode(buttoncl, INPUT);
}

void loop() {

 butval= digitalRead(buttonop);
if(butopval==true){
  digitalWrite(led, HIGH);//Check conflit with temperature setting
 
}

val = analogRead(potPin);    // read the value from the sensor
val=map(val, 0,1023,50,0);
ptemp=val;
  Serial.print("Temperature needed= ");
  Serial.println(ptemp);


  //ggg
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.println(DHT.temperature);
  Serial.print("Humidity = ");
  Serial.println(DHT.humidity);
  delay(1000);
  //ggg

 
 
 delay(1000); 

   if (DHT.temperature>(ptemp) && buttonop==false){

digitalWrite (led, HIGH);
delay(500);
digitalWrite(led, LOW);

  //make servo move -1
   }
   else if (DHT.temperature<(ptemp) || DHT.temperature ==(ptemp) && buttoncl == false){
    
digitalWrite (led, HIGH);
delay(500);
digitalWrite(led, LOW);


  //make servo move +1
   
   }

}





