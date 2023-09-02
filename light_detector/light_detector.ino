#include <NewPing.h>
#include <EEPROM.h>

#define TRIG_PIN 13
#define ECHO_PIN 12


const int LEFT_LED_PIN = 5;
const int MIDDLE_LED_PIN = 3;
const int RIGHT_LED_PIN = 2;
const int SENSOR_MIDDLE_PIN = A5;
const int EEPROM_ADDR = 1;
const int DISTANCE_LIMIT = 30;
const long INTERVAL = 20000;
const int DELAY_BETWEEN_LIGHT = 500;
const int TEMP_LIMIT = 200;
const unsigned long INTERVAL_FUNC = 3400;

NewPing sonar(ECHO_PIN, TRIG_PIN, 500);

int passage = 0;
unsigned long previousTime = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LEFT_LED_PIN, OUTPUT);
  pinMode(MIDDLE_LED_PIN, OUTPUT);
  pinMode(RIGHT_LED_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - previousTime >= INTERVAL_FUNC) {
    previousTime = currentTime;
    EEPROM.write(EEPROM_ADDR, passage);
  }

  unsigned int distance = sonar.ping_cm();
  if (distance < DISTANCE_LIMIT) {
    passage++;
    digitalWrite(LEFT_LED_PIN, HIGH);
    digitalWrite(MIDDLE_LED_PIN, HIGH);
    digitalWrite(RIGHT_LED_PIN, HIGH);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(60000);
    digitalWrite(LEFT_LED_PIN, LOW);
    digitalWrite(MIDDLE_LED_PIN, LOW);
    digitalWrite(RIGHT_LED_PIN, LOW);
    digitalWrite(LED_BUILTIN, LOW);
 
  } else {
    digitalWrite(LEFT_LED_PIN, LOW);
    digitalWrite(MIDDLE_LED_PIN, LOW);
    digitalWrite(RIGHT_LED_PIN, LOW);
    digitalWrite(LED_BUILTIN, LOW);
  }
}