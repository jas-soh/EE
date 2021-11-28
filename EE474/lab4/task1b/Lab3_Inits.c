/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "Lab3_Inits.h"
#include "tm4c1294ncpdt.h"
#include <stdint.h>

// STEP 0a: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

#define SW1 0x1
#define SW2 0x2
   
   
int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    SYSCTL_MOSCCTL_R &= ~(0x4);                         // Power up MOSC
    SYSCTL_MOSCCTL_R &= ~(0x8);                         // Enable MOSC
    while ((SYSCTL_RIS_R & 0x100) == 0) {};             // Wait for MOSC to be ready
    SYSCTL_RSCLKCFG_R |= (0x3 << 20);                   // Select MOSC as system clock source
    SYSCTL_RSCLKCFG_R |= (0x3 << 24);                   // Select MOSC as PLL clock source

    SYSCTL_PLLFREQ0_R |= 0x60;                          // Set MINT field
    SYSCTL_PLLFREQ1_R |= 0x4;                           // Set N field

    SYSCTL_MEMTIM0_R &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    SYSCTL_MEMTIM0_R &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    SYSCTL_MEMTIM0_R &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    SYSCTL_RSCLKCFG_R &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            SYSCTL_MEMTIM0_R |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            SYSCTL_MEMTIM0_R |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            SYSCTL_RSCLKCFG_R |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            SYSCTL_RSCLKCFG_R &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            SYSCTL_MEMTIM0_R |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            SYSCTL_MEMTIM0_R |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            SYSCTL_RSCLKCFG_R |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            SYSCTL_RSCLKCFG_R &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            SYSCTL_MEMTIM0_R |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            SYSCTL_RSCLKCFG_R |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            SYSCTL_RSCLKCFG_R &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    SYSCTL_RSCLKCFG_R |= (0x1 << 30);                // Enable new PLL settings
    SYSCTL_PLLFREQ0_R |= (0x1 << 23);                // Power up PLL
    while ((SYSCTL_PLLSTAT_R & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    SYSCTL_RSCLKCFG_R |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void Switches_Init(void) {
   volatile unsigned short delay = 0;
   SYSCTL_RCGCGPIO_R |= 0x100; // Enable PortJ(Switches)
   delay++; // Delay 2 more cycles before access Timer registers
   delay++; // Refer to Page. 756 of Datasheet for info
   
   //GPIODATA_N = 0x0;
   
   // Set up Port J for switches
   GPIO_PORTJ_DIR_R = 0x0; // Set PJ0 and PJ1 to input
   GPIO_PORTJ_DEN_R = (SW2| SW1); // Set PJ0 and PJ1 to digital
   GPIO_PORTJ_PUR_R = (SW2 | SW1); // Set up pullup resistors
   GPIO_PORTJ_LOCK_R = 0x4C4F434B; // Unlock Port J

   // Set up interrupts for switches
   GPIO_PORTJ_ICR_R |= (SW2| SW1); // clear prior interrupt
   GPIO_PORTJ_IM_R |= (SW2| SW1); // unmask interrupts
   NVIC_EN1_R |= 0x80000; // Enables Port J interrupt. Set field 51 to 1
};


void ADCReadPot_Init(void) {
  volatile unsigned short delay = 0 ;
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  SYSCTL_RCGCADC_R |= 0x1;

  // 2.2: Delay for RCGCADC (Refer to page 1073)
  // must delay 3
  delay++;
  delay++;
  delay++;

  // 2.3: Power up the PLL (if not already)
  SYSCTL_PLLFREQ0_R |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (SYSCTL_PLLSTAT_R != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADC0_CC_R = 0x1;

  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  SYSCTL_RCGCGPIO_R |= 0x10; // enable port E
  GPIO_PORTE_DIR_R |= 0x0; // input

  // 2.7: Delay for RCGCGPIO
  delay++;
  delay++;

  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIO_PORTE_AFSEL_R |= 0x8; // to be controlled

  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIO_PORTE_DEN_R &= ~0x8; // disable digital

  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIO_PORTE_AMSEL_R |= 0x8;

  // 2.11: Disable sample sequencer 3 (SS3)
  ADC0_ACTSS_R &= ~0x8; //checked

  // 2.12: Select timer as the trigger for SS3
  ADC0_EMUX_R |= 0x5000; //checked

  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADC0_SSEMUX3_R = 0x0; // checked
  ADC0_SSMUX3_R = 0xC; // Select AIN3

  // 2.14: Configure ADCSSCTL3 register
  ADC0_SSCTL3_R = (0x4 | 0x8);

  // 2.15: Set the SS3 interrupt mask
  ADC0_IM_R = 0x8; // 0x8 checked

  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  NVIC_EN0_R |= (1 << 17);

  // 2.17: Enable ADC0 SS3
  ADC0_ACTSS_R |= 0x8;

}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  SYSCTL_RCGCTIMER_R |= 0x1; // Enable Timer 0
  TIMER0_CTL_R &= 0x0; // Disable 
  TIMER0_CFG_R = 0x0; // Set 32-bit configuration
  TIMER0_TAMR_R |= 0x2; // Set Periodic timer mode
  TIMER0_TAMR_R &= ~(0x10); // Set to count down mode
  TIMER0_TAILR_R = 0xF42400; // Load 16 million on to timer (1Hz)
  TIMER0_ADCEV_R |= 0x1; // Enable ADC Event
  TIMER0_CC_R = 0x1;
  TIMER0_CTL_R |= 0x21; // Enable ADC trigger & timer0A
}
