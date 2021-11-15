/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "PLL_Header.h"
#include "Lab3_Inits.h"
#include "task1a.h"

// STEP 0a: Include your header file here
// YOUR CUSTOM HEADER FILE HERE

int PLL_Init(enum frequency freq) {
    // Do NOT modify this function.
    MOSCCTL &= ~(0x4);                      // Power up MOSC
    MOSCCTL &= ~(0x8);                      // Enable MOSC
    while ((RIS & 0x100) == 0) {};          // Wait for MOSC to be ready
    RSCLKCFG |= (0x3 << 20);                // Select MOSC as system clock source
    RSCLKCFG |= (0x3 << 24);                // Select MOSC as PLL clock source

    PLLFREQ0 |= 0x60;                       // Set MINT field
    PLLFREQ1 |= 0x4;                        // Set N field

    MEMTIM0 &= ~((0xF << 22) | (0xF << 6));     // Reset FBCHT and EBCHT
    MEMTIM0 &= ~((0xF << 16) | (0xF << 0));     // Reset EWS and FWS
    MEMTIM0 &= ~((0x1 << 21) | (0x1 << 5));     // Reset FBCE and EBCE

    RSCLKCFG &= ~(0x1 << 28);                   // Temporarilly bypass PLL

    switch (freq) {
        case 120:
            MEMTIM0 |= (0x6 << 22) | (0x6 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x5 << 16) | (0x5 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x3;                        // Set PSYSDIV to use 120 MHZ clock
            RSCLKCFG &= ~0x3FC;                     // Update PSYSDIV field
            break;
        case 60:
            MEMTIM0 |= (0x3 << 22) | (0x3 << 6);    // Set FBCHT and EBCHT
            MEMTIM0 |= (0x2 << 16) | (0x2 << 0);    // Set EWS and FWS
            RSCLKCFG |= 0x7;                        // Set PSYSDIV to use 60 MHZ clock
            RSCLKCFG &= ~0x3F8;                     // Update PSYSDIV field
            break;
        case 12:
            MEMTIM0 |= (0x1 << 21) | (0x1 << 5);    // Set FBCE and EBCE
            RSCLKCFG |= 0x27;                       // Set PSYSDIV to use 12 MHZ clock
            RSCLKCFG &= ~0x3D8;                     // Update PSYSDIV field
            break;
        default:
            return -1;
    }

    RSCLKCFG |= (0x1 << 30);                // Enable new PLL settings
    PLLFREQ0 |= (0x1 << 23);                // Power up PLL
    while ((PLLSTAT & 0x1) == 0) {};        // Wait for PLL to lock and stabilize

    RSCLKCFG |= (0x1u << 31) | (0x1 << 28);  // Use PLL and update Memory Timing Register
    return 1;
}

void LED_Init(void) {
  // STEP 1: Initialize the 4 on board LEDs by initializing the corresponding
  // GPIO pins.

  volatile unsigned short delay = 0 ;
  RCGCGPIO |= PORT_F;
  RCGCGPIO |= PORT_N;
  delay++;
  delay++;
  
  // enable digital functions
  GPIODEN_F |= (LED3 | LED4);
  GPIODEN_N |= (LED1 | LED2); 
  
  // to output
  GPIODIR_F |= (LED3 | LED4);
  GPIODIR_N |= (LED1 | LED2); 
  
  // initialize data
  GPIODATA_F = 0;
  GPIODATA_N = 0x0;
}

void Switches_Init(void) {
   volatile unsigned short delay = 0;
   RCGCGPIO |= PORT_J; // Enable PortJ(Switches)
   delay++; // Delay 2 more cycles before access Timer registers
   delay++; // Refer to Page. 756 of Datasheet for info
   
   GPIODATA_N = 0x0;
   
   // Set up Port J for switches
   GPIODIR_J = 0x0; // Set PJ0 and PJ1 to input
   GPIODEN_J = (SW2| SW1); // Set PJ0 and PJ1 to digital
   GPIOPUR_J = (SW2 | SW1); // Set up pullup resistors
   GPIOLOCK_J = 0x4C4F434B; // Unlock Port J

   // Set up interrupts for switches
   GPIOICR_J |= (SW2| SW1); // clear prior interrupt
   GPIOIM_J |= (SW2| SW1); // unmask interrupts
   EN1 |= ENABLE_51; // Enables Port J interrupt. Set field 51 to 1
};


void ADCReadPot_Init(void) {
  volatile unsigned short delay = 0 ;
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= 0x1;//ADC_0_EN;

  // 2.2: Delay for RCGCADC (Refer to page 1073)
  // must delay 3
  delay++;
  delay++;
  delay++;

  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  //RCGCADC |= ADC_0_EN;
  ADCCC_0 = 0x1;

  // 2.6: Enable clock to the appropriate GPIO Modules (Hint: Table 15-1)
  RCGCGPIO |= PORT_E;
  GPIODIR_E |= 0x0; // input

  // 2.7: Delay for RCGCGPIO
  delay++;
  delay++;

  // 2.8: Set the GPIOAFSEL bits for the ADC input pins
  GPIOAFSEL_E |= 0x8; // to be controlled

  // 2.9: Clear the GPIODEN bits for the ADC input pins
  GPIODEN_E &= ~0x8; // disable digital

  // 2.10: Disable the analog isolation circuit for ADC input pins (GPIOAMSEL)
  GPIOAMSEL_E |= 0x8;

  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS_0 &= ~0x8; //checked

  // 2.12: Select timer as the trigger for SS3
  ADCEMUX_0 |= 0x5000; //checked

  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSEMUX3_0 = 0x0; // checked
  ADCSSMUX3_0 = 0xC; // Select AIN3

  // 2.14: Configure ADCSSCTL3 register
  ADCSSCTL3_0 = 0x4 | 0x8;

  // 2.15: Set the SS3 interrupt mask
  ADCIM_0 = 0x8; // 0x8 checked

  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  NVIC_EN0 |= (1 << 17);

  // 2.17: Enable ADC0 SS3
  ADCACTSS_0 |= 0x8;

}

void TimerADCTriger_Init(void) {
  // STEP 3: Initialize Timer0A to trigger ADC0 at 1 HZ.
  // Hint: Refer to section 13.3.7 of the datasheet

  RCGCTIMER |= 0x1; // Enable Timer 0
  GPTMCTL_0 &= 0x0; // Disable 
  GPTMCFG_0 = 0x0; // Set 32-bit configuration
  GPTMTAMR_0 |= 0x2; // Set Periodic timer mode
  GPTMTAMR_0 &= ~(0x10); // Set to count down mode
  GPTMTAILR_0 = 0xF42400; // Load 16 million on to timer (1Hz)
  GPTMADCEV_0 |= 0x1; // Enable ADC Event
  GPTMCC_0 = 0x1;
  GPTMCTL_0 |= 0x21; // Enable ADC trigger & timer0A
}

// NEXT STEP: Go to Lab3_Task1a.c and finish implementing ADC0SS3_Handler

//void UART_Init(unsigned char bdi, unsigned char bdf) {
void UART_Init() {
  RCGCGPIO |= PORT_A; // enable port A
  GPIODEN_A |= (PIN_0 | PIN_1); 
  RCGCUART = (PIN_0 | PIN_1); // disable UART module 0
  GPIOAFSEL_A |= (PIN_0 | PIN_1);
  GPIODR2R_A |= (PIN_0 | PIN_1); // 2-mA drive to pin 0
  GPIOPCTL_A |= 0x11; // configuration for pin 0 and 1 (TX and RX)
  
  // disable UART by clearing UARTEN bit in UARTCTL reg
  UARTCTL_0 = 0 << 0;
  
  // BRD = 120,000,000/(16*9600) for freq 1
  // BRD = 60,000,000/(16*9600) for freq 2
  // BRD = 12,000,000/(16*9600) for freq 3
  
  // write integer portion of BRD in UARTIBRD reg
  //UARTIBRD_0 = bdi; // integer in hex 
  UARTIBRD_0 = 58; // integer in hex 
  
  // write fraction portion of BRD to UARTFBRD reg
  //UARTFBRD_0 = bdf; // fraction in hex
  UARTFBRD_0 = 8; // fraction in hex
  
  // write desired serial parameter to UARTLCRH reg
  UARTLCRH_0 |= 0xA; // no parity and one bit stop
  
  // write to UARTCC reg
  UARTCC_0 |= 0x5; // alternate cock source
    
  // enable UART by setting UARTEN bit in UARTCTL reg
  UARTCTL_0 |= 0x1;
}
