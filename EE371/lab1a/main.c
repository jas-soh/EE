#include <stdint.h>
#include "task1a.h"

// defining masks to access each LED
#define LED1MASK 0x02
#define LED2MASK 0x01
#define LED3MASK 0x10
#define LED4MASK 0x01


int main (void) {
  volatile unsigned short delay = 0 ;
  RCGCGPIO |= 0x20; // Enable PortF GPIO
  RCGCGPIO |= 0x1000; // Enable PortN GPIO
  delay++; // Delay 2 more cycles before access Timer registers
  delay++;
  
  GPIODIR_F = 0x11; // Set PF0 and PF4 to output
  GPIODIR_N = 0x3; // Set PN0 and PN1 to output
  
  GPIODEN_F = 0x11;// Set PF0 and PF4 to digital
  GPIODEN_N = 0x3; // Set PN0 and PN1 to digital

  
  while (1) {
    GPIODATA_F = 0x1; // LED4 on
    for (int j = 0; j < 1000000; j++) {}
    GPIODATA_F = 0x0; // LED4 off
    for (int j = 0; j < 1000000; j++) {}
    
    GPIODATA_F = 0x10; // LED3 on
    for (int j = 0; j < 1000000; j++) {}
    GPIODATA_F = 0x0; // LED3 off
    for (int j = 0; j < 1000000; j++) {}
    
    GPIODATA_N = 0x1; // LED2 on
    for (int j = 0; j < 1000000; j++) {}
    GPIODATA_N = 0x0; // LED2 off
    for (int j = 0; j < 1000000; j++) {}
    
    GPIODATA_N = 0x2; // LED1 on
    for (int j = 0; j < 1000000; j++) {}
    GPIODATA_N = 0x0; // LED1 off
    for (int j = 0; j < 1000000; j++) {}
    
  }
  return 0;
}
