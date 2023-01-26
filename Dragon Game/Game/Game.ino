/*
 Name:		Game.ino
 Created:	1/23/2023 11:09:10 AM
 Author:	jessy
*/

#include "Sound.h"
#include "GPIO.h"
#include "pins.h"
#include "types.h"
#include "player.h"
#include "libraries.h"
#include "LedControl.h"
#include "button.h"
#include "Servo.h"
#include "sound.h"

#define TRUE 1
#define FALSE 0

#define M_UP arduino::Movements::UP
#define M_DOWN  arduino::Movements::DOWN

const int DIN = 8;
const int CS = 9;
const int CLK = 10;
const int AANT = 1;

const int servoPin = 11;

bool isHitFlag = FALSE;
bool isMovedFlag = FALSE;
bool winFlag = FALSE;

LedControl matrix = LedControl(DIN, CLK, CS, AANT);
arduino::Player player = arduino::Player(matrix, { 3, 0 });;
Servo lock;

arduino::Button btnUp(3, M_UP);
arduino::Button btnDown(2, M_DOWN);

void randomSizedFireball(int sizeX, int sizeY);
bool randomFireball(arduino::Player& player);
void lost();
void win();
void readInput(arduino::Button& btn);

// the setup function runs once when you press reset or power the board
void setup() {
    Serial.begin(9600);
    matrix.shutdown(0, false);
    matrix.setIntensity(0, 8);
    matrix.clearDisplay(0);
    player.set(matrix);

    pinMode(2, INPUT);
    pinMode(3, INPUT);
    lock.attach(servoPin);

    // Servo begin position
    lock.write(0);
}

// the loop function runs over and over again until power down or reset
void loop() {
    if (millis() < 3100 && millis() > 1000) {
        byte number_1[8] = {B00111000,B01111000,B00011000,B00011000,B00011000,B00011000,B00011000,B00111100};
        byte number_2[8] = {B00111100,B01111110,B01100110,B00000110,B00001100,B00011000,B00110000,B01111110};
        byte number_3[8] = {B00000000,B00111100,B01000010,B00000010,B00011100,B00000010,B01000010,B00111100};
        matrix.clearDisplay(0);

        if (millis() < 2000) {
            for (int i = 0; i < 8; i++)
                matrix.setColumn(0, i, number_1[i]);
        }
        else if (millis() < 3000) {
            for (int i = 0; i < 8; i++)
                matrix.setColumn(0, i, number_2[i]);
        }
        else {
            for (int i = 0; i < 8; i++)
                matrix.setColumn(0, i, number_3[i]);
        }

        return;
    }

    if (isHitFlag == FALSE && winFlag == FALSE) {
        if (millis() >= 30000) {
            lock.write(150);
            win();
            winFlag = TRUE;
            arduino::play();
        }
        else if (randomFireball(player) && !winFlag) 
            lost();
        
    }
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
    byte l_letter[8] = { B00000110,B00000110,B00000110,B00000110,B00000110,B00000110,B01111110,B01111110 };

    matrix.clearDisplay(0);
    for (int i = 0; i < 8; i++) 
        matrix.setColumn(0, i, l_letter[i]);
}

void win() {
    byte w_letter[8] = { B11000011,B11000011,B11011011,B11011011,B11011011,B11011011,B11111111,B01100110 };

    matrix.clearDisplay(0);
    for (int i = 0; i < 8; i++)
        matrix.setColumn(0, i, w_letter[i]);
}

void readInput(arduino::Button& btn) {
    if (btn.isPressed() && isMovedFlag == FALSE) {
        player.move(matrix, btn.getMovement());
        isMovedFlag = TRUE;
    }
}


bool randomFireball(arduino::Player& player) {
    //srand(time(NULL));
    int min = 0;
    int max = 7;
    int range = max - min + 1;
    int r = (rand() % range);

    player.set(matrix);
    for (int i = 7; i >= 0; i--) {

        btnUp.read();
        btnDown.read();

        readInput(btnUp);
        readInput(btnDown);

        matrix.setLed(0, r, i, TRUE);
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

