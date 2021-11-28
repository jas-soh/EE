#include <stdint.h>
#include "SSD2119_Display.h"
#include "Lab3_Inits.h"
#include "tm4c1294ncpdt.h"

uint32_t ADC_value;
enum frequency freq;
int clk_freq;

#define SW1 0x1
#define SW2 0x2

int main(void) {
  // Select system clock frequency preset
  LCD_Init();
  LCD_ColorFill(Color4[1]);
  
  freq = PRESET1; // 60 MHz
  clk_freq = 120;
  PLL_Init(freq);        // Set system clock frequency to 60 MHz
  Switches_Init();           // Initialize the 2 onboard switches (GPIO)
  ADCReadPot_Init();     // Initialize ADC0 to read from the potentiometer
  TimerADCTriger_Init(); // Initialize Timer0A to trigger ADC0

  float temp_c;
  float temp_f;
  while(1) {
    
    temp_c = (float) 147.5 - ((247.5 * ADC_value) / 4096);
    temp_f = (float) (9 / 5) * temp_c + 32;
    printf("%.2f\n", temp_c);
    LCD_PrintString("The current temperature is ");
    LCD_PrintFloat(temp_c);
    LCD_PrintString(" C, ");
    LCD_PrintFloat(temp_f);
    LCD_PrintString(" F\n");
    LCD_PrintString("The current clock frequency is ");
    LCD_PrintInteger(clk_freq);
    LCD_PrintString(" MHz\n");

  }
  return 0;
}

void PortJ_Handler(void) {
   if (GPIO_PORTJ_MIS_R & SW1) { // Sw1 is pressed
      GPIO_PORTJ_ICR_R |= 0x3; // clear interupt from SW1
      freq = PRESET1;
      clk_freq = 120;
   }

   if (GPIO_PORTJ_MIS_R & SW2) { // Sw2 is pressed
      GPIO_PORTJ_ICR_R |= 0x3;// clear interupt from SW2
      freq = PRESET3;
      clk_freq = 12;
   }
   PLL_Init(freq); 
}

void ADC0SS3_Handler(void) {
   ADC0_ISC_R |= 0x8; // clear the interrupt flag
   ADC_value = ADC0_SSFIFO3_R; // save adc value to global variable
}
