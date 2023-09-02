
#include <NewPing.h>

#include "DHT.h"

#include <EEPROM.h>

#define TRIG_PIN 13
#define ECHO_PIN 12


// Instances initialization
//------------------------
DHT dht(11, DHT11);
NewPing sonar(ECHO_PIN, TRIG_PIN, 500);

// CONSTANTES
// ------------------------
long distance;
unsigned long arduinoStartedTime;


const int sensorMiddlePin = A5;
bool ligthOn = false;
const int eepromAddr = 1;
const int leftLed = 5;
const int middleLed = 3;
const int rightLed = 2;



const int tempLimit = 200;
const int distanceLimit = 30;
const long interval = 20000;
const int delayBetweenLight = 500;
int passage = 0;


float h = dht.readHumidity();
float t = dht.readTemperature();
int sensorValue = 0;
int sensorMiddlevalue = 0;

bool lightOn = false;

unsigned long previousTime = 0;           // variable to store the previous time
const unsigned long intervalFunc = 3400;  // interval of 30 minutes in milliseconds


void switchOffLights() {

  //delay(delayBetweenLight);
  digitalWrite(leftLed, LOW);
  //delay(delayBetweenLight);
  digitalWrite(rightLed, LOW);
  //delay(delayBetweenLight);
  digitalWrite(middleLed, LOW);
}

void switchOnLights() {
  //delay(delayBetweenLight);
  digitalWrite(leftLed, HIGH);
  //delay(delayBetweenLight);
  digitalWrite(rightLed, HIGH);
  //delay(delayBetweenLight);
  digitalWrite(middleLed, HIGH);
}


void setup() {
  Serial.begin(9600);
  // Initialize pins
  //-------------------
  pinMode(leftLed, OUTPUT);
  pinMode(middleLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  
  dht.begin();
  
}



void loop() {
  
  
  
  arduinoStartedTime = millis();


  long minutesEllapses = arduinoStartedTime / 60000;
  unsigned int distance = sonar.ping_cm();
  sensorMiddlevalue = analogRead(sensorMiddlePin);
  int val = sensorValue + sensorMiddlevalue;

if (arduinoStartedTime < 10000) {
delay(15000);
switchOffLights();

}


  unsigned long currentTime = millis();              // get the current time
  if (currentTime - previousTime >= intervalFunc) {  // check if the interval has passed
    previousTime = currentTime;                      // update the previous time
    EEPROM.write(eepromAddr, passage);
    
  }

  if (sonar.ping_cm() < 40) {
    passage++;
    lightOn = !lightOn;
    if (lightOn) {
    switchOnLights();
    delay(60000);
    }
    
  
  }
  else {
   switchOffLights();

  }



  // if (!lightOn) {
  //   switchOffLights();
      
  // }

  // if (lightOn) {

  //   switchOnLights();  // keep light on
  //      delay(10000);
  // }
}
