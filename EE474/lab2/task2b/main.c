#include <stdint.h>
#include <stdio.h>
#include "task2b.h"

#define LED1 0x2
#define LED2 0x1
#define SW1 0x1
#define SW2 0x2

int LED = 0;

int main(void) {
   GPIO_init(); 
   timer_init();
   while (1) {}
   return 0;
}

void GPIO_init(void) {
   volatile unsigned short delay = 0;
   RCGCGPIO |= 0x1100; // Enable PortJ(Switches) and PortN(led1, 2) GPIO
   delay++; // Delay 2 more cycles before access Timer registers
   delay++; // Refer to Page. 756 of Datasheet for info
   
   // Set up Port N for LEDs
   GPIODIR_N |= (LED1 | LED2); // PN0 and PN1 to output
   GPIODEN_N |= (LED1 | LED2); // PN0 and PN1 to digital
   GPIODATA_N = 0x0;
   
   // Set up Port J for switches
   GPIODIR_J = 0x0; // Set PJ0 and PJ1 to input
   GPIODEN_J = (SW2| SW1); // Set PJ0 and PJ1 to digital
   GPIOPUR_J = (SW2 | SW1); // Set up pullup resistors
   GPIOLOCK_J = 0x4C4F434B; // Unlock Port J

   // Set up interrupts for switches
   GPIOICR_J |= (SW2| SW1); // clear prior interrupt
   GPIOIM_J |= (SW2| SW1); // unmask interrupt
   EN1 |= ENABLE_51; // Enables Port I interrupt. Set field 19 to 1
};

void timer_init(void) {
   // Set up timer
   RCGCTIMER |= 0x01; // enable timer 0
   GPTMCTL_0 &= 0x0; // disable Timer 0
   GPTMCFG_0 = 0x0; // select 32-bit
   GPTMTAMR_0 = 0x02; // TAMR bit to periodic mode
   GPTMTAMR_0 &= ~(1<<4);// TACDIR bit to count down
   GPTMTAILR_0 = 0xF42400; // 16 MHz
   
   // Set up interrupts for timer
   EN0 |= ENABLE_19;  // Enable interrupt 19
   GPTMIMR_0 = 0x1; // Enable timer interrupt mask

   GPTMCTL_0 |= 0x1; // start timer
}


void Timer0A_Handler() {
    GPTMICR_0 |= 0x1; // reset timer
    pattern();
    if (LED == 1)
    {
      LED = 0;
    }
    else
    {
      LED = 1;
    }
}

void PortJ_Handler(void) {
   if (GPIOMIS_J & SW1) { // Sw1 is pressed
      GPIOICR_J |= SW1; // clear interupt from SW1
      GPIODATA_N |= LED2 ;// turn on LED2
      GPTMCTL_0 = 0x0; // disable timer 0
   }

   if (GPIOMIS_J & SW2) { // Sw2 is pressed
      GPIOICR_J |= SW2;// clear interupt from SW2
      GPIODATA_N &= ~(LED2); // turn off LED2
      GPTMCTL_0 |= 0x1; // Reenables timer 0
   }
}
void pattern()
{
  switch(LED)
  {
    case 0:
      GPIODATA_N = LED1; // LED1 on
      break;
    case 1:
      GPIODATA_N = 0x0; // LED1 off
      break; 
  }
}
