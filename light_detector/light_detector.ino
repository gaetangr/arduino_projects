#include "DHT.h"
#include "SR04.h"


#define TRIG_PIN 13
#define ECHO_PIN 12


// Instances initialization
//------------------------
DHT dht(11, DHT11);
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

// CONSTANTES
// ------------------------
long distance;
bool DEBUG = false;
const int sensorPin = A0;
const int sensorMiddlePin = A5;

const int leftLed = 5;
const int middleLed = 3;
const int rightLed = 2;

const int alertRedLed = A4;
const int alertBlueLed = A3;

const int tempLimit = 27;
const int distanceLimit = 50;
const long interval = 20000;
const int delayBetweenLight = 500;
int passage = 0;


float h = dht.readHumidity();
float t = dht.readTemperature();
int sensorValue = 0;
int sensorMiddlevalue = 0;

bool lightOn = false;



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
  distance = sr04.Distance();
  sensorValue = analogRead(sensorPin);
  sensorMiddlevalue = analogRead(sensorMiddlePin);
  int val = sensorValue + sensorMiddlevalue;


  if (DEBUG) {
    Serial.print("Distance cm: ");
    Serial.println(distance);
    Serial.print("Luminosity: ");
    Serial.println(val);
    Serial.print("Temperature: ");
    Serial.println(t);
  }


  float h = dht.readHumidity();
  float t = dht.readTemperature();

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



  if (distance <= distanceLimit) {
    passage += 1;
  }

  if (passage > 1) {
    switchOffLights();
    passage = 0;
    delay(8000); // wait 20s to make sure no false positive
  }

  if (distance <= distanceLimit && val <= 2) {
    if (passage == 0) {
     switchOnLights(); // keep light on
    }
  }
}
