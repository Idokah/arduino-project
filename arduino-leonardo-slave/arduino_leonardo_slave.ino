#include <VirtualWire.h>
#include <VirtualWire_Config.h>
#include <Keyboard.h>

int LEFT_LED = 10;
int RIGHT_LED = 8;
int SPACE_LED = 9;

enum Operations
{
  PRESS_KEY_SPACE,
  PRESS_KEY_DOWN_ARROW,
  PRESS_KEY_RIGHT_ARROW,
  PRESS_KEY_LEFT_ARROW,  
  RELEASE_ALL_KEYS,
  NONE,
};

char *controller;

void setup()
{
  pinMode(LEFT_LED, OUTPUT);
  pinMode(RIGHT_LED, OUTPUT);
  pinMode(SPACE_LED, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, OUTPUT);

  vw_set_ptt_inverted(true);
  vw_set_rx_pin(11);
  vw_setup(4000);
  vw_rx_start();

  Serial.begin(9600);
  Serial.println("setup");
}

int prevOperation = NONE;

void loop()
{
  if (digitalRead(12) == LOW) {
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;

    if (vw_get_message(buf, &buflen))
    {
      digitalWrite(13, HIGH);

      if (validatePrefix(buf))
      {
        int operation = buf[3] - '0';
        pressKey((Operations)operation);
        turnLigthsOn((Operations)operation);
        prevOperation = operation;
      }
      digitalWrite(13, LOW);
    }
  }
  else {
    pressKey(RELEASE_ALL_KEYS);
    turnLigthsOn(RELEASE_ALL_KEYS);
    prevOperation = RELEASE_ALL_KEYS;

  }
}

void pressKey(Operations operation) {
  if (operation != prevOperation) {
    switch (operation)
    {
      case PRESS_KEY_LEFT_ARROW:
        Keyboard.releaseAll();
        Keyboard.press(KEY_LEFT_ARROW);
        Serial.println("press left");
        break;
      case PRESS_KEY_RIGHT_ARROW:
        Keyboard.releaseAll();
        Keyboard.press(KEY_RIGHT_ARROW);
        Serial.println("press right");
        break;
      case PRESS_KEY_SPACE:
        Keyboard.releaseAll();
        Keyboard.press(' ');
        Serial.println("press space");
        break;
      case PRESS_KEY_DOWN_ARROW:
      case RELEASE_ALL_KEYS:
        Keyboard.releaseAll();
        Serial.println("release all");
        break;
    }
  }
}


void turnLigthsOn(Operations operation) {
  if (operation != prevOperation) {
    switch (operation)
    {
      case PRESS_KEY_LEFT_ARROW:
        digitalWrite(LEFT_LED, HIGH);
        digitalWrite(RIGHT_LED, LOW);
        digitalWrite(SPACE_LED, LOW);
        break;
      case PRESS_KEY_RIGHT_ARROW:
        digitalWrite(RIGHT_LED, HIGH);
        digitalWrite(LEFT_LED, LOW);
        digitalWrite(SPACE_LED, LOW);
        break;
      case PRESS_KEY_SPACE:
        digitalWrite(SPACE_LED, HIGH);
        digitalWrite(LEFT_LED, LOW);
        digitalWrite(RIGHT_LED, LOW);
        break;
      case RELEASE_ALL_KEYS:
        digitalWrite(LEFT_LED, LOW);
        digitalWrite(RIGHT_LED, LOW);
        digitalWrite(SPACE_LED, LOW);
        break;
    }
  }
}

bool validatePrefix(uint8_t *buf)
{
  return !((buf[0] - 'T') || (buf[1] - 'I') || (buf[2] - 'I'));
}
