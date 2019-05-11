#include "songs.h"

#define OUTPUT_PIN 6

void setup() {
  pinMode(6, OUTPUT); //Digital Pin 6 is where you connect your Buzzer
  Serial.begin(9600);
  
  setupKeyboard();
  
  Serial.println("Welcome to the Virtual Keyboard!");
  Serial.println("Notes: S-D-F-G-H-J-K-L");
  Serial.println("  #  : -E-R---Y-U-I-");
}

void loop() {
  while (Serial.available()) {
    String inputStr = Serial.readString();
    inputStr.toLowerCase();

    Serial.println(inputStr);
    playSong(OUTPUT_PIN, inputStr);
  }
}
