#include <stdint.h>
#include "task2.h"

enum TL_States { TL_SMStart, TL_stop, TL_warn, TL_go, TL_off } TL_State;

void LED_init(void); // initializes the LEDs
void extern_switch_init(void); // initializes the Switches
unsigned long switch_input(void); // reads from the Switches


void main(void){
  RCGCGPIO |= 0x400; // activate clock for Port L
  LED_init();
  extern_switch_init();

  while(1){
    switch(TL_State) { // state logic
     case TL_SMStart:
        if(switch_input() == 0x01){
          TL_State = TL_go;
        } else { 
          TL_State = TL_off;
        }
        break;

     case TL_stop:
        if(switch_input() == 0x01){
          TL_State = TL_off;
        } else { 
          TL_State = TL_go;
        }
        break;

     case TL_warn:
        if(switch_input() == 0x01){
          TL_State = TL_off;
        } else { 
          TL_State = TL_stop;
        }
        break;
        
     case TL_go:
        if (switch_input() == 0x01) {
          TL_State = TL_off; 
        } else if (switch_input() == 0x02){
          TL_State = TL_warn;
        } else {
           TL_State = TL_stop;
        }
        break;
        
     case TL_off:
        if (switch_input() == 0x01) {
           TL_State = TL_SMStart;
        } else {
           TL_State = TL_off;
        }
        break;

     default:
        TL_State = TL_SMStart;
        break;
  }

    switch(TL_State) { // output logic
       case TL_stop: // red on, others off
          GPIODATA_L |= 0x4;
          GPIODATA_L &= 0x4;
          break;

       case TL_warn: // yellow on, others off
          GPIODATA_L |= 0x8;
          GPIODATA_L &= 0x8;
          break;
          
       case TL_go: // green on, others off
          GPIODATA_L |= 0x10;
          GPIODATA_L &= 0x10;
          break;
          
       case TL_off: // turn off all
          GPIODATA_L = 0x0;
          break;
          
       default:
          break;
    }
    for (int j = 0; j < 1000000; j++) {} // delay
  }
}


void LED_init(void) {
  volatile unsigned short delay = 0;
  delay++;
  delay++;
  
  GPIOAMSEL_L &= ~(0x04 | 0x08 | 0x20); // disable analog function of PL2, PL3, PL4
  GPIOAFSEL_L &= ~(0x04 | 0x08 | 0x20); // set PL2, PL3, PL4 to regular port function
  GPIODIR_L |= (0x04 | 0x08 | 0x20); // set PL2, PL3, PL4 to output
  GPIODEN_L |= (0x04 | 0x08 | 0x20); // enable digital output on PL2, PL3, PL4
}

void extern_switch_init(void) {
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x400; // activate clock for Port L
  delay++;
  delay++;
  
  GPIOAMSEL_L &= ~(0x01 | 0x2); // disable analog function of PL0, PL1
  GPIOAFSEL_L &= ~(0x01 | 0x2); // set PL0, PL1 to regular port function
  GPIODIR_L &= ~(0x01 | 0x2); // set PL0, PL1 to input
  GPIODEN_L |= (0x01 | 0x2); // enable digital output on PL0, PL1
}

unsigned long switch_input(void) {
  return (GPIODATA_L & 0x03); // non zero if one of the switches is pressed, or 0 if not pressed
}
