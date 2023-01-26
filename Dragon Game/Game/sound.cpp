// 
// 
// 

#include "sound.h"
#include "pitches.h"

namespace arduino {
    // change this to make the song slower or faster
    int tempo = 114;
    
    // change this to whichever pin you want to use
    int buzzer = 7;
    
    // notes of the moledy followed by the duration.
    // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
    // !!negative numbers are used to represent dotted notes,
    // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
    int melody[] = {
    
        // Mii Channel theme 
        // Score available at https://musescore.com/user/16403456/scores/4984153
        // Uploaded by Catalina Andrade 
    
        NOTE_FS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8, //1
        NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, REST,4, REST,8, NOTE_CS4,8,
        NOTE_D4,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8,
        NOTE_E5,-4, NOTE_DS5,8, NOTE_D5,8, REST,8, REST,4,
    
        NOTE_GS4,8, REST,8, NOTE_CS5,8, NOTE_FS4,8, REST,8,NOTE_CS5,8, REST,8, NOTE_GS4,8, //5
        REST,8, NOTE_CS5,8, NOTE_G4,8, NOTE_FS4,8, REST,8, NOTE_E4,8, REST,8,
        NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,8, REST,4, NOTE_E4,8, NOTE_E4,8,
        NOTE_E4,8, REST,8, REST,4, NOTE_DS4,8, NOTE_D4,8,
    
        NOTE_CS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8, //9
        NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, REST,8,
        REST,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8,
        NOTE_E5,2, NOTE_D5,8, REST,8, REST,4,
    
        NOTE_B4,8, NOTE_G4,8, NOTE_D4,8, NOTE_CS4,4, NOTE_B4,8, NOTE_G4,8, NOTE_CS4,8, //13
        NOTE_A4,8, NOTE_FS4,8, NOTE_C4,8, NOTE_B3,4, NOTE_F4,8, NOTE_D4,8, NOTE_B3,8,
        NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,4, REST,4, NOTE_AS4,4,
        NOTE_CS5,8, NOTE_D5,8, NOTE_FS5,8, NOTE_A5,8, REST,8, REST,4,
    
        REST,2, NOTE_A3,4, NOTE_AS3,4, //17 
        NOTE_A3,-4, NOTE_A3,8, NOTE_A3,2,
        REST,4, NOTE_A3,8, NOTE_AS3,8, NOTE_A3,8, NOTE_F4,4, NOTE_C4,8,
        NOTE_A3,-4, NOTE_A3,8, NOTE_A3,2,
    
        REST,2, NOTE_B3,4, NOTE_C4,4, //21
        NOTE_CS4,-4, NOTE_C4,8, NOTE_CS4,2,
        REST,4, NOTE_CS4,8, NOTE_C4,8, NOTE_CS4,8, NOTE_GS4,4, NOTE_DS4,8,
        NOTE_CS4,-4, NOTE_DS4,8, NOTE_B3,1,
    
        NOTE_E4,4, NOTE_E4,4, NOTE_E4,4, REST,8,//25
    
        //repeats 1-25
    
        NOTE_FS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8, //1
        NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, REST,4, REST,8, NOTE_CS4,8,
        NOTE_D4,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8,
        NOTE_E5,-4, NOTE_DS5,8, NOTE_D5,8, REST,8, REST,4,
    
        NOTE_GS4,8, REST,8, NOTE_CS5,8, NOTE_FS4,8, REST,8,NOTE_CS5,8, REST,8, NOTE_GS4,8, //5
        REST,8, NOTE_CS5,8, NOTE_G4,8, NOTE_FS4,8, REST,8, NOTE_E4,8, REST,8,
        NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,8, REST,4, NOTE_E4,8, NOTE_E4,8,
        NOTE_E4,8, REST,8, REST,4, NOTE_DS4,8, NOTE_D4,8,
    
        NOTE_CS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8,NOTE_A4,8, REST,8, NOTE_FS4,8, //9
        NOTE_D4,8, NOTE_D4,8, NOTE_D4,8, REST,8, NOTE_E5,8, NOTE_E5,8, NOTE_E5,8, REST,8,
        REST,8, NOTE_FS4,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_F4,8,
        NOTE_E5,2, NOTE_D5,8, REST,8, REST,4,
    
        NOTE_B4,8, NOTE_G4,8, NOTE_D4,8, NOTE_CS4,4, NOTE_B4,8, NOTE_G4,8, NOTE_CS4,8, //13
        NOTE_A4,8, NOTE_FS4,8, NOTE_C4,8, NOTE_B3,4, NOTE_F4,8, NOTE_D4,8, NOTE_B3,8,
        NOTE_E4,8, NOTE_E4,8, NOTE_E4,8, REST,4, REST,4, NOTE_AS4,4,
        NOTE_CS5,8, NOTE_D5,8, NOTE_FS5,8, NOTE_A5,8, REST,8, REST,4,
    
        REST,2, NOTE_A3,4, NOTE_AS3,4, //17 
        NOTE_A3,-4, NOTE_A3,8, NOTE_A3,2,
        REST,4, NOTE_A3,8, NOTE_AS3,8, NOTE_A3,8, NOTE_F4,4, NOTE_C4,8,
        NOTE_A3,-4, NOTE_A3,8, NOTE_A3,2,
    
        REST,2, NOTE_B3,4, NOTE_C4,4, //21
        NOTE_CS4,-4, NOTE_C4,8, NOTE_CS4,2,
        REST,4, NOTE_CS4,8, NOTE_C4,8, NOTE_CS4,8, NOTE_GS4,4, NOTE_DS4,8,
        NOTE_CS4,-4, NOTE_DS4,8, NOTE_B3,1,
    
        NOTE_E4,4, NOTE_E4,4, NOTE_E4,4, REST,8,//25
    
        //finishes with 26
        //NOTE_FS4,8, REST,8, NOTE_A4,8, NOTE_CS5,8, REST,8, NOTE_A4,8, REST,8, NOTE_FS4,8
    
    };
    
    // sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
    // there are two values per note (pitch and duration), so for each note there are four bytes
    int notes = sizeof(melody) / sizeof(melody[0]) / 2;
    
    // this calculates the duration of a whole note in ms
    int wholenote = (60000 * 4) / tempo;
    
    int divider = 0, noteDuration = 0;

    void playWii() {
        // iterate over the notes of the melody. 
        // Remember, the array is twice the number of notes (notes + durations)
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

            // calculates the duration of each note
            divider = melody[thisNote + 1];
            if (divider > 0) {
                // regular note, just proceed
                noteDuration = (wholenote) / divider;
            }
            else if (divider < 0) {
                // dotted notes are represented with negative durations!!
                noteDuration = (wholenote) / abs(divider);
                noteDuration *= 1.5; // increases the duration in half for dotted notes
            }

            // we only play the note for 90% of the duration, leaving 10% as a pause
            tone(buzzer, melody[thisNote], noteDuration * 0.9);

            // Wait for the specief duration before playing the next note.
            delay(noteDuration);

            // stop the waveform generation before the next note.
            noTone(buzzer);
        }
    }

    void playWin() {
        // Play coin sound
        /*
        tone(buzzer, NOTE_B5, 100);
        delay(100);
        tone(buzzer, NOTE_E6, 850);
        delay(800);
        noTone(buzzer);

        delay(2000);  // pause 2 seconds

        */
        // Play 1-up sound
        tone(buzzer, NOTE_E6, 125);
        delay(130);
        tone(buzzer, NOTE_G6, 125);
        delay(130);
        tone(buzzer, NOTE_E7, 125);
        delay(130);
        tone(buzzer, NOTE_C7, 125);
        delay(130);
        tone(buzzer, NOTE_D7, 125);
        delay(130);
        tone(buzzer, NOTE_G7, 125);
        delay(125);
        noTone(buzzer);
    }

    void playLose() {
        delay(500);
        tone(buzzer, 500, 200);
        delay(200);
        tone(buzzer, 1200, 200);
        delay(200);
        tone(buzzer, 300, 200);
        delay(200);
        tone(buzzer, 1000, 200);
        delay(200);
        tone(buzzer, 400, 200);
    }

    void playFireball() {
        tone(buzzer, NOTE_G4, 35);
        delay(35);
        tone(buzzer, NOTE_G5, 35);
        delay(35);
        tone(buzzer, NOTE_G6, 35);
        delay(35);
        noTone(buzzer);
    }
}

