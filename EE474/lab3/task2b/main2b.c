/**
* EE/CSE 474: Lab3 Task2b main function
*/

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdio.h>
#include <stdint.h>
#include "task2b_inits.h"
#include "task2b.h"
#include <string.h>  


// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE
enum frequency freq;
int main(void) {
  // Select system clock frequency preset
  freq = PRESET2; 
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  UART_Init(); 
      
  while (1)
  {
      while ((UARTFR_2 & (1 << 4)) != 0x0) // while not full
      {}
      char value = UARTDR_2;
      while ((UARTFR_2 & (1 << 3)) != 0x0) // while not empty
      {}
      UARTDR_2 = value;
  }
  return 0;
}
