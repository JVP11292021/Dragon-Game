/*
 Name:		Game.ino
 Created:	1/23/2023 11:09:10 AM
 Author:	jessy
*/

#include "GPIO.h"
#include "pins.h"
#include "types.h"
#include "player.h"
#include "libraries.h"
#include "LedControl.h"
#include "button.h"

#define TRUE 1
#define FALSE 0

const int DIN = 8;
const int CS = 9;
const int CLK = 10;
const int AANT = 1;

//const int buttonPin = 2;
//int buttonState = 0;

bool isHitFlag = FALSE;
bool isMovedFlag = FALSE;

LedControl matrix = LedControl(DIN, CLK, CS, AANT);
arduino::Player player = arduino::Player(matrix, { 3, 0 });;

void randomSizedFireball(int sizeX, int sizeY);
bool randomFireball(arduino::Player& player);
void lost();

// the setup function runs once when you press reset or power the board
void setup() {
    matrix.shutdown(0, false);
    matrix.setIntensity(0, 8);
    matrix.clearDisplay(0);
    player.set(matrix);
    pinMode(2, INPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
    //buttonState = digitalRead(buttonPin);
    if (isHitFlag == FALSE) {
        if (randomFireball(player))
            //lost();
            Serial.print("Lost");
    }
    
    //Serial.println(buttonState);
    
    delay(100);
}

void randomSizedFireball(int sizeX, int sizeY) {
    int min = sizeY - 1;
    int max = 7;
    int range = max - min + 1;
    int r = (rand() % range);
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < sizeX; j++) {
            matrix.setLed(0, r, i + j, TRUE);
            for (int k = 0; k < sizeY; k++) {
                matrix.setLed(0, r + k, i + j, TRUE);
            }
        }
        delay(100);
        matrix.clearDisplay(0);
    }
}

void lost() {
    matrix.clearDisplay(0);
    matrix.setChar(7, 0, 'L', TRUE);
}

bool randomFireball(arduino::Player& player) {
    int min = 0;
    int max = 7;
    int range = max - min + 1;
    int r = (rand() % range);

    arduino::Button btn(2);

    player.set(matrix);
    for (int i = 7; i >= 0; i--) {
        matrix.setLed(0, r, i, TRUE);
        if (btn.isPressed() && isMovedFlag == FALSE) {
            player.move(matrix, arduino::Movements::UP);
            isMovedFlag = TRUE;
        }
        // code
        delay(100);
        matrix.setLed(0, r, i, FALSE);

        if (player.isHit(r, i)) {
            isHitFlag = TRUE;
            return TRUE;
        }
    }
    player.set(matrix);
    isMovedFlag = FALSE;

    return FALSE;
}

