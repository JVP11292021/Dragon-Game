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
#include "ezButton.h"

#define TRUE 1
#define FALSE 0

const int DIN = 8;
const int CS = 9;
const int CLK = 10;
const int AANT = 1;

#define VRX_PIN  A0 // Arduino pin connected to VRX pin
#define VRY_PIN  A1 // Arduino pin connected to VRY pin
#define SW_PIN   2  // Arduino pin connected to SW  pin


int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int bValue = 0; // To store value of the button

bool isHitFlag = false;

ezButton button = ezButton(SW_PIN);
LedControl matrix = LedControl(DIN, CLK, CS, AANT);
LedControl playerControl = LedControl(DIN, CLK, CS, AANT);

void randomSizedFireball(int sizeX, int sizeY);
bool randomFireball(arduino::Player& player);
void lost();

// the setup function runs once when you press reset or power the board
void setup() {
    matrix.shutdown(0, false);
    matrix.setIntensity(0, 8);
    matrix.clearDisplay(0);

    button.setDebounceTime(50);
}

// the loop function runs over and over again until power down or reset
void loop() {
    button.loop(); // MUST call the loop() function first

// read analog X and Y analog values
    xValue = analogRead(VRX_PIN);
    yValue = analogRead(VRY_PIN);

    // Read the button value
    bValue = button.getState();

    if (button.isPressed()) {
        Serial.println("The button is pressed");
        // TODO do something here
    }

    if (button.isReleased()) {
        Serial.println("The button is released");
        // TODO do something here
    }


    arduino::Player player = arduino::Player(playerControl, { 3, 0 });
    if (isHitFlag == false) {
        if (randomFireball(player))
            lost();
    }
    
    delay(100);
}

void _HWDEBUG() {
    // print data to Serial Monitor on Arduino IDE
    Serial.print("x = ");
    Serial.print(xValue);
    Serial.print(", y = ");
    Serial.print(yValue);
    Serial.print(" : button = ");
    Serial.println(bValue);
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
    matrix.setChar(0, 0, 'L', TRUE);
}

bool randomFireball(arduino::Player& player) {
    int min = 0;
    int max = 7;
    int range = max - min + 1;
    int r = (rand() % range);
 
    for (int i = 7; i >= 0; i--) {
        matrix.setLed(0, r, i, TRUE);
        
        if (player.isHit(r, i)) {
            isHitFlag = true;
            return TRUE;
        }
    }
    delay(300);
    for (int i = 7; i >= 0; i--)
        matrix.setLed(0, r, i, FALSE);
    return FALSE;
}

