
#include <stdint.h>
#include "task1a.h"

#define LED1 0x02
#define LED2 0x01
#define LED3 0x10
#define LED4 0x01

int LED = 0;
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
  
  GPIODATA_F = 0x0;
  GPIODATA_N = 0x0;
  
  while (1) {}
  
  return 0;
}


void timer_init()
{
  RCGCTIMER |= 0x01; // enable timer 0
  GPTMCTL_0 &= 0x0; // disable Timer 0
  GPTMCFG_0 = 0x0; // select 32-bit
  GPTMTAMR_0 = 0x02; // TAMR bit to periodic mode
  GPTMTAMR_0 = 0x0; // TACDIR bit to count down
  GPTMTAILR_0 = 0xF42400; // 16 MHz
  GPTMIMR_0 = 0x1;
  EN0 |= ENABLE_19;  // Enable interrupt 19
  GPTMCTL_0 |= 0x1;
}


void Timer0A_Handler() {
    pattern();
    if (LED == 7)
    {
      LED = 0;
    }
    else
    {
      LED++;
    }
    GPTMICR_0 |= 0x1; // reset timer
}

void pattern()
{
  switch(LED)
  {
    case 0:
      GPIODATA_F |= 0x1; // LED4 on
      break;
    case 1:
      GPIODATA_F = 0x0; // LED4 off
      break;
    case 2:
      GPIODATA_F = 0x10; // LED4 off
      break;
    case 3:
      GPIODATA_F = 0x0; // LED4 off
      break;
    case 4:
      GPIODATA_N = 0x1; // LED4 off
      break;
    case 5:
      GPIODATA_N = 0x0; // LED4 off
      break;
    case 6:
      GPIODATA_N = 0x2; // LED4 off
      break;
    case 7:
      GPIODATA_N = 0x0; // LED4 off
      break;
    
  }
}
