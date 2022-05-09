#include <Keyboard.h>
#include <VirtualWire.h>

enum Operations
{
  PRESS_KEY_LEFT_ARROW,
  PRESS_KEY_RIGHT_ARROW,
  PRESS_KEY_SPACE,
  RELEASE_ALL_KEYS,
};

char *controller;

void setup()
{
  pinMode(13, OUTPUT);

  vw_set_ptt_inverted(true);
  vw_set_rx_pin(11);
  vw_setup(4000);
  vw_rx_start();

  Serial.begin(9600);
  Serial.println("setup");
}

void loop()
{
  uint8_t buf[VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;

  if (vw_get_message(buf, &buflen))
  {
    digitalWrite(13, HIGH);

    if (validatePrefix(buf))
    {
      int operation = buf[3] - '0';
      Serial.println(operation);
      switch (operation)
      {
      case PRESS_KEY_LEFT_ARROW:
        Keyboard.press(KEY_LEFT_ARROW);
        Serial.println("press left");
        break;
      case PRESS_KEY_RIGHT_ARROW:
        Keyboard.press(KEY_RIGHT_ARROW);
        Serial.println("press right");
        break;
      case PRESS_KEY_SPACE:
        Keyboard.press(' ');
        Serial.println("press space");
        break;
      case RELEASE_ALL_KEYS:
        Keyboard.releaseAll();
        Serial.println("release all");
        break;
      }
    }
    digitalWrite(13, LOW);
  }
}

bool validatePrefix(uint8_t *buf)
{
  return !((buf[0] - 'T') || (buf[1] - 'I') || (buf[2] - 'I'));
}
