
#include <avr/pgmspace.h> // gives us PROGMEM to put strings in Flash storage rather than RAM
#include "DigiKeyboard.h"
#include "FastLED.h" // tiny OK random number generator


//long string in flash memory
// ruler                      ----5----10---5----20---5----30---5----40---5----50--------60---5
const char line1[] PROGMEM = "   Jeffrey Epstein didn't kill himself ";
const char line2[] PROGMEM = "    !  write erose; relaod in 9999999  ";
const char line3[] PROGMEM = "           make america great again!   ";
const char line4[] PROGMEM = "              ping tracking.amazon.com ";
const char line5[] PROGMEM = " Laws are like stop signs: suggestions ";
const char line6[] PROGMEM = "                  I like rusty spoons  ";
const char line7[] PROGMEM = "https://github.com/haxcess/sneakeyboard";


#define LINES 8
#define KEY_CAPS 0x39

char buffer[42]; //greater than longest string + 1 for null
#define GF( x ) (strcpy_P(buffer, (char*)x))  // GetFlash copy string from progmem(flash) to buffer[]

#define MINUTES(_Mins) (_Mins * 60000)    // Could use this to get milliseconds out of minutes
#define MAXWAIT 60  // Minutes to wait
#define MINWAIT 25

void digiReset() {
  DigiKeyboard.sendKeyStroke(0, 0);
  DigiKeyboard.delay(50);
}

void waitFor( int d ) {
  // wait for d milliseconds
  DigiKeyboard.delay( d );
}

void longWaitFor( int d = 1) {
  // waits for d minutes, blinking led
  for (int i = 0; i < d; i++) { 
    for (int j = 0; j < 60; j++) {  
      waitFor(1000);  // Wait one second
      digitalWrite(1, !digitalRead(1)); // blink the LED
    }
  }
}

void sendModKey( int key, int mod ) {
  // could use this to send modified keys, like CTRL-V
  // sendModKey( KEY_V, MOD_CONTROL_LEFT )
  DigiKeyboard.sendKeyStroke( key, mod );
  DigiKeyboard.update();
}

void sendKey( int key ) {
  DigiKeyboard.sendKeyStroke( key );
  DigiKeyboard.update();
}

void printText( char * txt ) {
  // simple loop through the buffer and send keys out
  int l = strlen(txt);
  for (int i = 0; i < l; i++) {
    uint8_t r = random8();
    // this toggles case of the character based on random number
    if (r > 120) txt[i] ^= 32;  
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

  i = i % LINES ; // recycle that random number for the string choice

  if (1 == i)      printText( GF (line1) );
  else if (2 == i) printText( GF (line2) );
  else if (3 == i) printText( GF (line3) );
  else if (4 == i) printText( GF (line4) );
  else if (5 == i) printText( GF (line5) );
  else if (6 == i) printText( GF (line6) );
  else if (7 == i) printText( GF (line7) );
  else  sendKey(KEY_CAPS);  //capslock
}
