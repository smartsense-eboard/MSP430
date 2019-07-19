#include <Servo.h> 
#include <Wire.h>

#define LED RED_LED


const int ledPin = 13; // onboard LED
Servo motors;    // create servo object to control a servo 
int angle = 0;    // variable to store the servo position 


void setupServo(void)
{
  Wire.begin(0x8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  pinMode(LED, OUTPUT);
  digitalWrite(ledPin, LOW); // turn it off
  Serial.begin(9600);
}


void setup() 
{ 
  motors.attach(4);  // attaches the servo on pin 4 to the servo object 
  setupServo();
}
 
void loop() 
{
motors.write(angle);
//delay(1); //delay ms may or may not need 
  
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    int c = Wire.read(); // receive byte as a character
    Serial.println(c);
    angle = c;
  }
}

/*  for(angle = 0; angle< 180; angle++)  // goes from 0 degrees to 180 degrees 
  {                                       // in steps of 1 degree 
    //motors.write(angle);              // tell servo to go to position in variable 'angle’ 
    delay(20);                       // waits 20ms for the servo to reach the position 
  } 
  for(angle = 180;angle>=1; angle--)     // goes from 180 degrees to 0 degrees 
  {                                
   // motors.write(angle);              // tell servo to go to position in variable 'angle' 
    delay(20);                       // waits 20ms for the servo to reach the position 
  } 
}*/
