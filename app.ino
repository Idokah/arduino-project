#include <Wire.h>
#include "i2c.h"
#include "i2c.MMA8451.h"
#include "Keyboard.h"
MMA8451 mma8451;
const int X_AXIS = 0;
const int X_POS = 0;
const LIGHT_THRESHOLD
const int LDR_PIN = A0;
int movementState = 0;

enum Directions {
    LEFT,
    RIGHT,
    NONE
} direction;

enum Operations {
    PRESS_KEY_LEFT_ARROW,
    RELEASE_KEY_LEFT_ARROW
    PRESS_KEY_RIGHT_ARROW,
    RELEASE_KEY_RIGHT_ARROW,
    PRESS_KEY_SPACE,
    RELEASE_KEY_SPACE,
    RELEASE_ALL_KEYS,
};

void setup() {
    Serial.begin(115200);
    Keyboard.begin();
    Serial.println("MMA8451 test");
    if (mma8451.initilize()) {
        Serial.println("MMA8451 initialized");
    pinMode(LDR_PIN, INPUT);
}

void loop() {
    static float xyz[3];
    mma.getMeasurements(xyz);
    int movement = getMovement(xyz);
    switch (getMovementDirection(movement)) {
        case LEFT:
            sendOperation(Operations.PRESS_KEY_LEFT_ARROW);
            break;
        case RIGHT:
            sendOperation(Operations.PRESS_KEY_RIGHT_ARROW);
            break;
        case NONE:
            sendOperation(Operations.RELEASE_ALL_KEYS);
            break;
    }


    if (checkShoot()) {
        sendOperation(Operations.PRESS_KEY_SPACE);
    }

    delay(100);
}

getMovementDirection() {

    movementState+=movement;

    if (movementState > X_AXIS) {
        return LEFT;
    } else if (movementState < X_AXIS) {
        return RIGHT;
    }
    
    return NONE;
}

int getMovement(float xyz[3]) {
}

bool checkShoot() {
    int ldrStatus = analogRead(LDR_PIN);
    return ldrStatus > LIGHT_THRESHOLD
}

void moveRight() {
    
}

void sendOperation(Operations operation) {
    
    switch (operation) {
        case PRESS_KEY_LEFT_ARROW:
            Keyboard.press(KEY_LEFT_ARROW);
            break;
        case RELEASE_KEY_LEFT_ARROW:
            Keyboard.release(KEY_LEFT_ARROW);
            break;
        case PRESS_KEY_RIGHT_ARROW:
            Keyboard.press(KEY_RIGHT_ARROW);
            break;
        case RELEASE_KEY_RIGHT_ARROW:
            Keyboard.release(KEY_RIGHT_ARROW);
            break;
        case PRESS_KEY_SPACE:
            Keyboard.press(KEY_SPACE);
            break;
        case RELEASE_KEY_SPACE:
            Keyboard.release(KEY_SPACE);
            break;
        case RELEASE_ALL_KEYS:
            Keyboard.releaseAll();
            break;
    }   


}