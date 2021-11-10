/**
 * EE/CSE 474: Lab3 Task1a main function
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdio.h>
#include <stdint.h>
#include "Lab3_Inits.h"
#include "task1a.h"

// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

uint32_t ADC_value;

int main(void) {
  // Select system clock frequency preset
  enum frequency freq = PRESET2; // 60 MHz
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  LED_Init();            // Initialize the 4 onboard LEDs (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  float resistance;
  while(1) {
    resistance = (double) ADC_value / 4095.0 * 10.0;
    if (resistance < 2.5) {
      GPIODATA_N = LED1; // turn on only LED1
      GPIODATA_F = 0x0; // turn off everything else
    } else if (resistance < 5.0) {
      GPIODATA_N = LED1 | LED2; // turn on LED1 and LED2
      GPIODATA_F = 0x0; // turn off everything else
    } else if (resistance < 7.5) {
      GPIODATA_N = LED1 | LED2; // turn on LED1 and LED2
      GPIODATA_F = LED3; // turn on only LED3
    } else {
      GPIODATA_N = LED1 | LED2; // turn on LED1 and LED2
      GPIODATA_F = LED3 | LED4; // turn on LED3 and LED4
    }
  }
  return 0;
}

void ADC0SS3_Handler(void) {
   ADCISC_0 |= 0x8; // clear the interrupt flag
   ADC_value = ADCSSFIFO3; // save adc value to global variable
}
