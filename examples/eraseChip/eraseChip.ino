/*
 * eraseChip
 *
 * Sets all of the bytes of the memory to the default value (0xFF).
 * Could take until 240 seconds to erase all the memory (worst conditions).
 *
 */

#include <QuadSPIFlash.h>

void setup() {
  // initialize the LED pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // initialize the QSPIFlash flash memory
  QSPIFlash.begin();

  // erase all the memory: set byte to 0xFF
  QSPIFlash.eraseChip();

  // turn the LED on when we're done
  digitalWrite(LED_BUILTIN, HIGH);
}

void loop() {
  /** Empty loop. **/
}
