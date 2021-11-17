/**
 * EE/CSE 474: Lab3 Task1a main function
 */

// NOTE: This is the main function for Task 1a. You should start by
// implementing Lab3_Driver.c (STEP 0a, 1-3) and then come back to finish
// the ISR and the main function (STEP 0b, 4-5).

#include <stdio.h>
#include <stdint.h>
#include "Lab3_Inits.h"
#include "task2a.h"
#include <string.h>  
#include <math.h>

// STEP 0b: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

uint32_t ADC_value;
enum frequency freq;
float temp;
int update;

int main(void) {
  // Select system clock frequency preset
  freq = PRESET1; 
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  
  Switches_Init();           // Initialize the 2 onboard switches (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0
  UART_Init(0x30D, 0x10); 
      
  while(1) {
    
    update = 0;
    temp = (float) 147.5 - ((247.5 * ADC_value) / 4096);
    temp = roundf(temp * 100) / 100;
    printf("%f\n", temp);

    char output[9];
    sprintf(output, "%.2f\r\n", temp); 
    for (int i = 0; i < 9; i++)
    {
        UARTDR_0 = output[i];
    }
    while (update = 0) {};

  }
  return 0;
}

void PortJ_Handler(void) {
   if (GPIOMIS_J & SW1) { // Sw1 is pressed
      GPIOICR_J |= 0x3; // clear interupt from SW1
      freq = PRESET1;
      PLL_Init(freq); 
      UART_Init(0x30D, 0x10);
   }

   if (GPIOMIS_J & SW2) { // Sw2 is pressed
      GPIOICR_J |= 0x3;// clear interupt from SW2
      freq = PRESET3;
      PLL_Init(freq); 
      UART_Init(0x4E,0x8);
   }
}


void ADC0SS3_Handler(void)
{                           
    ADCISC_0 |= 0x8;          // clear the ADC0 interrupt flag
    GPTMICR_0 |= 0x1;       // clear timed out
    ADC_value = ADCSSFIFO3; // save the ADC value to global variable ADC_value
    update = 1;
}
