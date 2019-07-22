//Libraries Needed
#include <Servo.h> 
#include <Wire.h>




Servo motors;    // create servo object to control a servo
unsigned long micro = 1200;    // variable to store the servo position
int data[3];
unsigned long val = 1000;
unsigned long now = 1000;

void setupServo(void)
{
  Wire.begin(0x8);                // join I2C bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(9600);
}


void setup() 
{
  motors.attach(4);  // attaches the servo on pin 4 to the servo object 
  setupServo();
}
 
void loop()
{
 if(val > now)
 {
  now = now + 20;
 }
 else if(val < now)
 {
  now = now - 20;
  delay(10);
  if((now < 1500) and (val < 1400))
  {
    now = 1000;
  }
 }
 motors.writeMicroseconds(now);
 delay(100);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

void receiveEvent(int howMany)
{
  while (Wire.available())
  { // loop through all but the last
      int i = 0;

      for(i=0;i< howMany;i++)
      {
        data[i] = Wire.read();
      }

      micro = data[2];
      micro = micro << 8;
      micro = micro + data[1];
      val = micro;
      Serial.println(val);
  }
}
