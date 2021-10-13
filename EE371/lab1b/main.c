#include <stdint.h>
#include "task1b.h"


int main (void) {
  volatile unsigned short delay = 0 ;

  RCGCGPIO |= 0x1000; // Enable PortN GPIO
  RCGCGPIO |= 0x100; // Enable PortN GPIO
  delay++; // Delay 2 more cycles before access Timer registers
  delay++;
  
  GPIODIR_N = 0x3; // Set PN0 and PN1 to output
  GPIODIR_J = 0x0; // Set PJ0 and PN1 to input

  GPIODEN_N = 0x3; // Set PN0 and PN1 to digital
  GPIODEN_J = 0x3; // Set PN0 and PN1 to digital

  
  while (1) {
    GPIODATA_N = 0x0;
    //GPIODATA_N = ~((GPIODATA_J << 1) | (GPIODATA_J >> 1));
  }
  return 0;
}
