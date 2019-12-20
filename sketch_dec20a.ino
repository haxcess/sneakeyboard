
#include <avr/pgmspace.h> // gives us PROGMEM to put strings in Flash storage rather than RAM
#include "DigiKeyboard.h"
#include "FastLED.h" // tiny OK random number generator


//long string in flash memory
// ruler                      ----5----10---5----20---5----30---5----40---5----50--------60---5
const char line1[] PROGMEM = "   Jeffrey Epstein didn't kill himself ";
const char line2[] PROGMEM = "     relaod in 9999999; copy run stort ";
const char line3[] PROGMEM = "           Santa prefers rich families ";
const char line4[] PROGMEM = "       wherever you go, there you are! ";
const char line5[] PROGMEM = " Laws are like stop signs: suggestions ";
const char line6[] PROGMEM = "     Errrorr RAM subsystem nearly full ";
const char line7[] PROGMEM = "   jEfFrEy ePsTaIn DiDnaT kIlL HiMsElF ";


#define LINES 6
#define KEY_CAPS 0x39

char buffer[42]; //greater than longest string + 1 for null
#define GetPsz( x ) (strcpy_P(buffer, (char*)x))

#define MINUTES(_Mins) (_Mins * 60000)
#define MAXWAIT 60
#define MINWAIT 25

void digiReset() {
  DigiKeyboard.sendKeyStroke(0, 0);
  DigiKeyboard.delay(50);
}

void waitFor( int d ) {
  DigiKeyboard.delay( d );
}

void longWaitFor( int d = 1) {
  // waits for d minutes, blinking led
  for (int i = 0; i < d; i++) {
    for (int j = 0; j < 60; j++) {
      waitFor(1000);
      digitalWrite(1, !digitalRead(1));
    }
  }
}

void sendModKey( int key, int mod ) {
  DigiKeyboard.sendKeyStroke( key, mod );
  DigiKeyboard.update();
}

void sendKey( int key ) {
  DigiKeyboard.sendKeyStroke( key );
  DigiKeyboard.update();
}

void printText( char * txt ) {
  int l = strlen(txt);
  for (int i = 0; i < l; i++) {
    uint8_t r = random8();
    if (r > 120) txt[i] |= 32;
    DigiKeyboard.print( txt[i] );
    DigiKeyboard.update();
  }
}

void setup() {
  digiReset();
  pinMode(1, OUTPUT);
  uint16_t i = random8(); // seed it
  longWaitFor( random8(MINWAIT, MAXWAIT));
}

void loop() {
  uint16_t i = random8(MINWAIT, MAXWAIT) ;
  longWaitFor(i); // Sleep a while

  i = i % LINES ;

  if (1 == i)      printText( GetPsz (line1) );
  else if (2 == i) printText( GetPsz (line2) );
  else if (3 == i) printText( GetPsz (line3) );
  else if (4 == i) printText( GetPsz (line4) );
  else if (5 == i) printText( GetPsz (line5) );
  else if (6 == i) printText( GetPsz (line6) );
  else if (7 == i) printText( GetPsz (line7) );
  else  sendKey(KEY_CAPS);  //capslock
}

