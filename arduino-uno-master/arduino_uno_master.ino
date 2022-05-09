#include <VirtualWire.h>
#include <Wire.h>              // Must include Wire library for I2C
#include "SparkFun_MMA8452Q.h" // Click here to get the library: http://librarymanager/All#SparkFun_MMA8452Q

MMA8452Q accel; // create instance of the MMA8452 class

enum Operations
{
  PRESS_KEY_LEFT_ARROW,
  PRESS_KEY_RIGHT_ARROW,
  PRESS_KEY_SPACE,
  RELEASE_ALL_KEYS,
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
      sendOperation(PRESS_KEY_RIGHT_ARROW);
    }
    else if (accel.isLeft() == true)
    {
      sendOperation(PRESS_KEY_LEFT_ARROW);
    }
    else if (accel.isUp() == true)
    {
      sendOperation(PRESS_KEY_SPACE);
    }
    else if (accel.isDown() == true)
    {
      // Serial.println("Down");
    }
    else if (accel.isFlat() == true)
    {
      sendOperation(RELEASE_ALL_KEYS);
    }
    delay(50);
  }
}

void sendOperation(Operations operation)
{
  char buffer[5];
  sprintf(buffer, "%s%d", prefix, operation);
  Serial.print("sending: ");
  Serial.println(buffer);
  vw_send((uint8_t *)buffer, 4);
  
  switch (operation)
  {
  case PRESS_KEY_LEFT_ARROW:
    // Keyboard.press(KEY_LEFT_ARROW);
    Serial.println("press left");
    break;
  case PRESS_KEY_RIGHT_ARROW:
    // Keyboard.press(KEY_RIGHT_ARROW);
    Serial.println("press right");
    break;
  case PRESS_KEY_SPACE:
    // Keyboard.press(' ');
    Serial.println("press space");
    break;
  case RELEASE_ALL_KEYS:
    // Keyboard.releaseAll();
    Serial.println("release all");
    break;
  }
}

const char *concatOpWithPrefix(Operations operation)
{
  char buffer[5];
  sprintf(buffer, "%s%d", prefix, operation);
  Serial.println(prefix);
  Serial.println(operation);
  Serial.println(buffer);
  return buffer;
}
