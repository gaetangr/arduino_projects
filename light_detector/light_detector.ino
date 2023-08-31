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

const int tempLimit = 28;
const int distanceLimit = 50;


float h = dht.readHumidity();
float t = dht.readTemperature();
int sensorValue = 0;
int sensorMiddlevalue = 0;

bool lightOn = false;


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
  }

  if (distance <= distanceLimit) {
    delay(500);
    digitalWrite(leftLed, HIGH);
    delay(500);
    digitalWrite(rightLed, HIGH);
    delay(500);
    digitalWrite(middleLed, HIGH);
    delay(20900);

  } else {

    digitalWrite(leftLed, LOW);
    delay(500);
    digitalWrite(middleLed, LOW);
    delay(500);
    digitalWrite(rightLed, LOW);
    delay(500);
  }
}
