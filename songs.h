/*
  https://create.arduino.cc/projecthub/Noshirt/keyboard-v2-0-5dcacc?ref=search&ref_id=keyboard&ASCII_OFFSET=0
*/
#include "pitches.h"

#define ASCII_OFFSET 'a'

unsigned int NOTES[26];
String VALID_INPUT("sedrfgyhujikl");
int duration(400);

boolean isValidNote(char ch) {
  return VALID_INPUT.indexOf(ch) != -1;
}

// character 'a' is reserved in screen utility
void setupKeyboard() {
  // invalid pitch
  NOTES['a' - ASCII_OFFSET] = NOTE_A0;
  
  NOTES['s' - ASCII_OFFSET] = NOTE_C5;
  NOTES['d' - ASCII_OFFSET] = NOTE_D5;
  NOTES['f' - ASCII_OFFSET] = NOTE_E5;
  NOTES['g' - ASCII_OFFSET] = NOTE_F5;
  NOTES['h' - ASCII_OFFSET] = NOTE_G5;
  NOTES['j' - ASCII_OFFSET] = NOTE_A5;
  NOTES['k' - ASCII_OFFSET] = NOTE_B5;
  NOTES['l' - ASCII_OFFSET] = NOTE_C6;

  NOTES['e' - ASCII_OFFSET] = NOTE_CS5;
  NOTES['r' - ASCII_OFFSET] = NOTE_DS5;
  NOTES['y' - ASCII_OFFSET] = NOTE_FS5;
  NOTES['u' - ASCII_OFFSET] = NOTE_GS5;
  NOTES['i' - ASCII_OFFSET] = NOTE_AS5;
}

void playSong(int outputPin, String inputStr) {
    for (int i = 0; i < inputStr.length(); i++) {
      char ch = inputStr.charAt(i);
      if (isValidNote(ch)) {
        
        // Note: Only the last tone is heard, one tone at a time, require noTone()
        // tone(outputPin, NOTES[ch - ASCII_OFFSET], duration);
        
        tone(outputPin, NOTES[ch - ASCII_OFFSET]);
        delay(duration);
        noTone(outputPin);
      }
    }
  
}
