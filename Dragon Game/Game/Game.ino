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

int beginTime = 0;
int duration = 20000;
int countdown = 4000;

LedControl matrix = LedControl(DIN, CLK, CS, AANT);
arduino::Player player = arduino::Player(matrix, { 3, 0 });;
Servo lock;

arduino::Button btnUp(3, M_UP);
arduino::Button btnDown(2, M_DOWN);

bool randomFireball(arduino::Player& player);
void lost();
void win();
void readInput(arduino::Button& btn);

// the setup function runs once when you press reset or power the board
void setup() {
    beginTime = millis();
    //Serial.begin(9600);
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
    int Time = millis() - beginTime;
    if (Time < countdown && !winFlag) {
        byte number_1[8] = { B00111100,B00011000,B00011000,B00011000,B00011000,B00011000,B01111000,B00111000 };
        byte number_2[8] = { B01111110,B00100000,B00010000,B00001000,B00000100,B00000010,B01000010,B00111100 };
        byte number_3[8] = { B00111100,B01000010,B00000010,B00111100,B00000010,B01000010,B00111100,B00000000 };
        matrix.clearDisplay(0);

        if (Time < 2000 && Time > 1000) {
            for (int i = 0; i < 8; i++)
                matrix.setColumn(0, i, number_3[i]);
        }
        if (Time < 3000 && Time > 2000) {
            for (int i = 0; i < 8; i++)
                matrix.setColumn(0, i, number_2[i]);
        }
        if (Time < countdown && Time > 3000) {
            for (int i = 0; i < 8; i++)
                matrix.setColumn(0, i, number_1[i]);
            matrix.clearDisplay(0);
        }
        return;
    }

    if (isHitFlag == FALSE && winFlag == FALSE) {
        if (Time >= duration + countdown) {
            // Win state geo cache lock
            lock.write(150);
            win();
            winFlag = TRUE;
        }
        else if (randomFireball(player) && !winFlag)
            lost();
    }
}

void lost() {
    byte l_letter[8] = {B01111110,B01111110,B01100000,B01100000,B01100000,B01100000,B01100000,B01100000};

    matrix.clearDisplay(0);
    for (int i = 0; i < 8; i++) 
        matrix.setColumn(0, i, l_letter[i]);

    arduino::playLose();
}

void win() {
    byte w_letter[8] = { B01100110,B11011011,B11011011,B11011011,B11011011,B11011011,B11011011,B10000001 };

    matrix.clearDisplay(0);
    for (int i = 0; i < 8; i++)
        matrix.setColumn(0, i, w_letter[i]);

    arduino::playWin();
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
    arduino::playFireball();
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
