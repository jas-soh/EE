#include <stdint.h>
#include "task1a.h"

#define LED1 0x02
#define LED2 0x01
#define LED3 0x10
#define LED4 0x01

void timer_init();
void count_down();
int main()
{
  volatile unsigned short delay = 0 ;
  RCGCGPIO |= 0x00000020; // enable port F
  RCGCGPIO |= 0x00001000; // enable port N
  delay++;
  delay++;
  
  GPIODIR_F |= (LED4 | LED3); // PF4 and PF3 to output
  GPIODIR_N |= (LED1 | LED2); // PN0 and PN1 to output
  
  GPIODEN_F |= (LED4 | LED3); // PF4 and PF3 to digital
  GPIODEN_N |= (LED1 | LED2); // PN0 and PN1 to digital
  
  timer_init();
  
  while (1) {
    GPIODATA_F = 0x1; // LED4 on
    count_down();
    GPIODATA_F = 0x0; // LED4 off
    count_down();
    
    GPIODATA_F = 0x10; // LED3 on
    count_down();
    GPIODATA_F = 0x0; // LED3 off
    count_down();
    
    GPIODATA_N = 0x1; // LED2 on
    count_down();
    GPIODATA_N = 0x0; // LED2 off
    count_down();
    
    GPIODATA_N = 0x2; // LED1 on
    count_down();
    GPIODATA_N = 0x0; // LED1 off
    count_down();
    
  }
  
  return 0;
}

void timer_init()
{
  RCGCTIMER |= 0x01; // enable timer 0
  GPTMCTL_0 &= 0x01; // disable Timer 0
  GPTMCFG_0 |= 0x00; // select 32-bit
  GPTMTAMR_0 |= 0x02; // TAMR bit to periodic mode
  GPTMTAMR_0 |= 0x10; // TACDIR bit to count down
  GPTMTAILR_0 = 0xF42400; // 16 MHz
}


void count_down() {
  while ((GPTMRIS_0 & 0x01) != 0x0) {}
  GPTMICR_0 |= 0x01; // clears TATORIS bit
}
