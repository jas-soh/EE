/**
 * EE/CSE 474: Lab3 drivers starter code
 */

#include "PLL_Header.h"
#include "Lab3_Inits.h"
#include "task2a.h"

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

void Switches_Init(void) {
   volatile unsigned short delay = 0;
   RCGCGPIO |= PORT_J; // Enable PortJ(Switches)
   delay++; // Delay 2 more cycles before access Timer registers
   delay++; // Refer to Page. 756 of Datasheet for info
   
   //GPIODATA_N = 0x0;
   
   // Set up Port J for switches
   GPIODIR_J = 0x0; // Set PJ0 and PJ1 to input
   GPIODEN_J = (SW2 | SW1); // Set PJ0 and PJ1 to digital
   GPIOPUR_J = (SW2 | SW1); // Set up pullup resistors
   //GPIOLOCK_J = 0x4C4F434B; // Unlock Port J

   // Set up interrupts for switches
   EN1 = ENABLE_51; // Enables Port J interrupt. Set field 51 to 1
   GPIOIM_J = 0x0; // Mask all interrupts
   GPIOIS_J &= ~0x3; // Make bits 1 and 0 edge sensitive
   GPIOIBE_J &= ~0x3; // Deactivate both edge detection
   GPIOIEV_J &= ~0x3; // Falling edge
   GPIOICR_J |= 0x3; // Clear Port J interruption
   GPIOIM_J |= 0x3; // Unmask bits 1 and 0
};


void ADCReadPot_Init(void) {
  volatile unsigned short delay = 0 ;
  // STEP 2: Initialize ADC0 SS3.
  // 2.1: Enable the ADC0 clock
  RCGCADC |= (1<<0);
  // 2.2: Delay for RCGCADC (Refer to page 1073)
  delay++;
  delay++;
  delay++;
  // 2.3: Power up the PLL (if not already)
  PLLFREQ0 |= 0x00800000; // we did this for you
  // 2.4: Wait for the PLL to lock
  while (PLLSTAT != 0x1); // we did this for you
  // 2.5: Configure ADCCC to use the clock source defined by ALTCLKCFG
  ADCCC_0 = (0x1); 

  // 2.7: Delay for RCGCGPIO
  delay++;
  delay++;
  delay++;

  // 2.11: Disable sample sequencer 3 (SS3)
  ADCACTSS_0 &= ~(1<<3); //ss3 disable
  
  // 2.12: Select timer as the trigger for SS3
  ADCEMUX_0 = (0x5<<12);
  // 2.13: Select the analog input channel for SS3 (Hint: Table 15-1)
  ADCSSMUX3_0 = 0x2; 
  // 2.14: Configure ADCSSCTL3 register
  ADCSSCTL3_0 = 0x6; 
  // 2.15: Set the SS3 interrupt mask
  ADCIM_0 |= (1<<3);
  // 2.16: Set the corresponding bit for ADC0 SS3 in NVIC
  ADCISC_0 |= (1<<3);
  EN0 |= (0x1<<17);
  // 2.17 setting up ADCSSOP3 for temperature read
  ADCSSCTL3_0 |= (1<<3); 

  // 2.17: Enable ADC0 SS3
  ADCACTSS_0 |= (1<<3);
}
    
void TimerADCTriger_Init(void) {
  RCGCTIMER |= 0x1; // Enable timer 0 clock
  GPTMCTL_0 = 0x0; // Disable timer 0
  GPTMCTL_0 |= 0x20; // enable ADC output trigger
  GPTMCFG_0 = 0x0; // Set 32-bit mode
  GPTMTAMR_0 |= 0x2; // Set timer to periodic and countdown
  GPTMTAILR_0 = 0xF42400; // 16M in hex
  GPTMADCEV_0 |= 0x1; // enable trigger on timeout event
  GPTMCC_0 = 0x1; // set the clock source to alternate clock
  GPTMCTL_0 |= 0x1; // Enable timer 0
}
   

void UART_Init(uint32_t bdi, uint32_t bdf) {
//void UART_Init() {
  volatile unsigned short delay = 0;
  RCGCUART |= 0x1;//(PIN_0 | PIN_1);
  RCGCGPIO |= PORT_A; // enable port A
  
  delay++;
  delay++;
  delay++; // delay for three clock cycles before further configuration
  
  GPIOAFSEL_A = (PIN_0 | PIN_1);
  GPIODEN_A = (PIN_0 | PIN_1); 
  GPIODR2R_A = (PIN_0 | PIN_1); // 2-mA drive to pin 0
  GPIOPCTL_A = 0x11; // configuration for pin 0 and 1 (TX and RX)
  
  // disable UART by clearing UARTEN bit in UARTCTL reg
  UARTCTL_0 &= ~0x1;       // Disable UART
  //UARTCTL_0 |= (0x3 << 8); // Enable UART transmission/reception
  
  // BRD = 120,000,000/(16*9600) for freq 1
  // BRD = 60,000,000/(16*9600) for freq 2
  // BRD = 12,000,000/(16*9600) for freq 3
  
  // write integer portion of BRD in UARTIBRD reg
  UARTIBRD_0 = bdi; // integer in hex 
  //UARTIBRD_0 = 781; // integer in hex 
  //UARTIBRD_0 = 0x68; // integer in hex 
  
  // write fraction portion of BRD to UARTFBRD reg
  UARTFBRD_0 = bdf; // fraction in hex
  //UARTFBRD_0 = 0xB; // fraction in hex
  
  // write desired serial parameter to UARTLCRH reg
  UARTLCRH_0 |= (0x3 << 5); // no parity and one bit stop
  
  // write to UARTCC reg
  UARTCC_0 = 0x0;// alternate clock source
    
  // enable UART by setting UARTEN bit in UARTCTL reg
  UARTCTL_0 |= 0x1;
}

