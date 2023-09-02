#include <NewPing.h>

#include "DHT.h"

#include <EEPROM.h>

#define TRIG_PIN 13
#define ECHO_PIN 12


// Instances initialization
//------------------------
DHT dht(11, DHT11);
NewPing sonar(TRIG_PIN, ECHO_PIN, 500);

// CONSTANTES
// ------------------------
long distance;
unsigned long arduinoStartedTime;

bool DEBUG = true;
const int sensorPin = A0;
const int sensorMiddlePin = A5;
bool ligthOn = false;
const int eepromAddr = 1;
const int leftLed = 5;
const int middleLed = 3;
const int rightLed = 2;

const int alertRedLed = A4;
const int alertBlueLed = A3;

const int tempLimit = 200;
const int distanceLimit = 90;
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

  delay(delayBetweenLight);
  digitalWrite(leftLed, LOW);
  delay(delayBetweenLight);
  digitalWrite(rightLed, LOW);
  delay(delayBetweenLight);
  digitalWrite(middleLed, LOW);
}

void switchOnLights() {
  delay(delayBetweenLight);
  digitalWrite(leftLed, HIGH);
  delay(delayBetweenLight);
  digitalWrite(rightLed, HIGH);
  delay(delayBetweenLight);
  digitalWrite(middleLed, HIGH);
}


void setup() {

  Serial.begin(9600);
  // Initialize pins
  //-------------------
  pinMode(sensorPin, OUTPUT);
  pinMode(leftLed, OUTPUT);
  pinMode(middleLed, OUTPUT);
  pinMode(rightLed, OUTPUT);
  pinMode(alertBlueLed, OUTPUT);
  pinMode(alertRedLed, OUTPUT);
  dht.begin();
}



void loop() {
  arduinoStartedTime = millis();
  long minutesEllapses = arduinoStartedTime / 60000;
  unsigned int distance = sonar.ping_cm();
  sensorValue = analogRead(sensorPin);
  sensorMiddlevalue = analogRead(sensorMiddlePin);
  int val = sensorValue + sensorMiddlevalue;


  float h = dht.readHumidity();
  float t = dht.readTemperature();


  unsigned long currentTime = millis();              // get the current time
  if (currentTime - previousTime >= intervalFunc) {  // check if the interval has passed
    previousTime = currentTime;                      // update the previous time
    EEPROM.write(eepromAddr, passage);
  }


  Serial.println(sonar.ping_cm());
  if (DEBUG) {
    //Serial.print("Distance cm: ");
    //Serial.println(distance);
    // Serial.print("Luminosity: ");
    //Serial.println(val);
    // Serial.print("Temperature: ");
    // Serial.println(t);
    // Serial.print("Nombre de passages: ");
    // Serial.println(passage);
    //Serial.println(lightOn);
  }



  if (t >= tempLimit) {
    digitalWrite(alertBlueLed, HIGH);
    delay(300);
    digitalWrite(alertBlueLed, LOW);
    digitalWrite(alertRedLed, HIGH);
    delay(300);
    digitalWrite(alertRedLed, LOW);
  } else {
    digitalWrite(alertBlueLed, LOW);
    digitalWrite(alertRedLed, LOW);
  }



  if (sonar.ping_cm() <= distanceLimit) {
    passage++;
    lightOn = !lightOn;
    digitalWrite(alertRedLed, HIGH);
  }

  if (!lightOn) {
    switchOffLights();
  }

  if (lightOn) {

    switchOnLights();  // keep light on
  }
}
