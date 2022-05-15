#include <VirtualWire.h>
#include <Wire.h>              // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h" // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q

MMA8452Q accel; // create instance of the MMA8452 class

enum Operations
{
  LEFT,
  RIGHT,
  UP,
  DOWN,
  FLAT,
};

const char prefix[] = "TII";

void setup()
{
  Serial.begin(9600);
  Serial.println("MMA8452Q Basic Reading Code!");
  Wire.begin();

  if (accel.begin() == false)
  {
    Serial.println("Not Connected. Please check connections and read the hookup guide.");
    while (1)
      ;
  }

  vw_set_ptt_inverted(true);
  vw_set_tx_pin(12);
  vw_setup(4000);
}

void loop()
{

  if (accel.available())
  { 
    // Wait for new data from accelerometer
    // Orientation of board (Right, Left, Down, Up);
    if (accel.isRight() == true)
    {
      sendOperation(RIGHT);
    }
    else if (accel.isLeft() == true)
    {
      sendOperation(LEFT);
    }
    else if (accel.isUp() == true)
    {
      sendOperation(UP);
    }
    else if (accel.isDown() == true)
    {
      sendOperation(DOWN);
    }
    else if (accel.isFlat() == true)
    {
      sendOperation(FLAT);
    }
    // delay(50);
  }
}

void sendOperation(Operations operation)
{
  char buffer[5];
  sprintf(buffer, "%s%d", prefix, operation);
  vw_send((uint8_t *)buffer, 4);
}
