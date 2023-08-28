
// Variable that will be changed
int switchState = 0;

// Constantes for the leds
// the variable can be used just as any other variable of its type, but its value cannot be changed. 
// -------------------------
const int greenLed = 6;
const int redLeftLed = 3;
const int redRightLed = 5;

// -------------------------
void setup() {
  
  // Define the purpose of the pin using the pinMode function
  // Take the pin number and the type, output or input
  // Output : Can activate components 
  // Input : Check if a button is pressed for example
  // -------------------------
  pinMode(greenLed, OUTPUT);
  pinMode(redLeftLed, OUTPUT);
  pinMode(redRightLed, OUTPUT);
  pinMode(2, INPUT);

  // pinMode : Configures the specified pin to behave either as an input or an output.
}

void loop() {
  // pin 2 and store the value in the switchState variable.
  // If there’s voltage on the pin when digitalRead() is called, the switchState variable will get the value HIGH (or 1).
  // If there is no voltage on the pin, switchState will get the value LOW (or 0)

  switchState = digitalRead(2); // Reads the value from a specified digital pin, either HIGH or LOW.


  if (switchState == LOW) {
    // the button is not pressed
    digitalWrite(greenLed, HIGH);  // green LED
    digitalWrite(redLeftLed, HIGH);   // red LED
    digitalWrite(redRightLed, HIGH);

    delay(390);
         digitalWrite(greenLed, LOW);  // green LED

     digitalWrite(redLeftLed, LOW);   // red LED
    digitalWrite(redRightLed, LOW);


 delay(390);
     digitalWrite(greenLed, HIGH);  // green LED

     digitalWrite(redLeftLed, HIGH);   // red LED
    digitalWrite(redRightLed, LOW);

       // red LED
  }

  else {  // the button is pressed
    digitalWrite(greenLed, LOW);
    digitalWrite(redLeftLed, LOW);
    digitalWrite(redRightLed, HIGH);
    delay(250);  // wait for a quarter second
                 // toggle the LEDs
    digitalWrite(greenLed, LOW);
    digitalWrite(redRightLed, LOW);

    delay(250);  // wait for a quarter second

    digitalWrite(redLeftLed, HIGH);
    delay(360);
    digitalWrite(redLeftLed, LOW);
  }


}
