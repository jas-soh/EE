#include <stdint.h>
#include "task1b.h"

int main()
{
  timer0_init();
  LED_init();
  extern_switch_init();

  while (1)
  {
    SM();
  }
  return 0;
}

void timer0_init()
{
  RCGCTIMER |= GPTM0_16_32; // Enable 16/32 Timer 0

  GPTMCTL_0 = 0x0; // Disable Timer A
  GPTMCFG_0 = MODE_32; // Set to 32-bit mode
  GPTMTAMR_0 |= PERIODIC_MODE; // Set periodic timer mode
  GPTMTAMR_0 = COUNT_DOWN; // TACDIR0 to count down
  GPTMTAILR_0 = VAL_16_MIL; // Load value of 16 million into GPTMTAILR0
  GPTMCTL_0 |= 0x1; // Enable Timer A
}


int two_seconds()
{
  GPTMICR_0 |= 0x1;
  int t = 0;
  while (t < 2 )
  {
      if ((GPIODATA_L & 0x03) == 0x0) // unpressed
      {
        GPTMICR_0 |= 0x1;
        return 0;
      }
      if (GPTMRIS_0 & 0x1)
      {
        GPTMICR_0 |= 0x1;
        t++;
      }
  }
  // must have finished holding two seconds
  return 1;
}

int five_seconds(int go)
{
  GPTMICR_0 |= 0x1;
  int time = 0;
  while (time < 5)
  {
    if (sys_switch())
    {
      GPTMICR_0 |= 0x1;
      return 0; // return 0 means sys switch was activated
    }
    if ((go == 1) && ped_switch())
    {
      GPTMICR_0 |= 0x1;
      return 2; // return 0 means sys switch was activated
    }
    if (GPTMRIS_0 & 0x1)
    {
      time++;
      GPTMICR_0 |= 0x1;
    }
  }
  GPTMICR_0 |= 0x1;
  return 1; // return 1 means nothing was pressed; continue w/ default
}

void LED_init(void)
{
  // Enable Port L
  RCGCGPIO |= Port_L;

  GPIOAMSEL_L &= ~(0x04 | 0x08 | 0x20); // disable analog function of PL2, PL3, PL4
  GPIOAFSEL_L &= ~(0x04 | 0x08 | 0x20); // set PL2, PL3, PL4 to regular port function
  GPIODIR_L |= (0x04 | 0x08 | 0x20); // set PL2, PL3, PL4 to output
  GPIODEN_L |= (0x04 | 0x08 | 0x20); // enable digital output on PL2, PL3, PL4
}

void extern_switch_init(void)
{
  volatile unsigned short delay = 0;
  RCGCGPIO |= 0x400; // activate clock for Port L
  delay++;
  delay++;
  
  GPIOAMSEL_L &= ~(0x01 | 0x2); // disable analog function of PL0, PL1
  GPIOAFSEL_L &= ~(0x01 | 0x2); // set PL0, PL1 to regular port function
  GPIODIR_L &= ~(0x01 | 0x2); // set PL0, PL1 to input
  GPIODEN_L |= (0x01 | 0x2); // enable digital output on PL0, PL1
}

unsigned long sys_switch(void)
{
    if (GPIODATA_L & 0x1)
    {
      int held = two_seconds();
      return held;
    }
    else
    {
      return 0x0;
    }
}

unsigned long ped_switch(void)
{
  if (GPIODATA_L & 0x2)
  {
    int held = two_seconds();
    return held;
  }
  else
  {
    return 0x0;
  }
}

 // state variables
enum TL_State {TL_SMStart,TL_Go, TL_Warn, TL_Stop, TL_Off} TL_State;

void SM()
{
  int wait;

  switch (TL_State)
  {
    
    case TL_SMStart:
      TL_State = TL_Stop;
      break;
      
    case TL_Go:
      wait = five_seconds(1);
      if (wait == 1)
      {
        TL_State = TL_Stop;
      } 
      else if (wait == 2)
      {
        TL_State = TL_Warn;
      }
      else
      {
        TL_State = TL_Off;
      }
      break;
      
    case TL_Warn:
      wait = five_seconds(0);
      if (wait == 1)
      {
        TL_State = TL_Stop;
      } 
      else if (wait == 0)
      {
        TL_State = TL_Off;
      }
      else
      {
        TL_State = TL_Stop;
      }
      break;
      
    case TL_Stop:
      wait = five_seconds(0);
      if (wait == 1)
      {
        TL_State = TL_Go;
      } 
      else if (wait == 0)
      {
        TL_State = TL_Off;
      }
      else
      {
        TL_State = TL_Go;
      }
      break;
      
    case TL_Off:
        TL_State = TL_Off;
        if (sys_switch())
        {
            TL_State = TL_SMStart;
        }
        break;
        
    default:
        TL_State = TL_SMStart;
        break;
    }
  
  
  switch (TL_State) // State actions
  {
    case TL_Go:
      GPIODATA_L |= 0x10;
      GPIODATA_L &= 0x10;
      break;
    case TL_Warn:
      GPIODATA_L |= 0x8;
      GPIODATA_L &= 0x8;
      break;
    case TL_Stop:
      GPIODATA_L |= 0x4;
      GPIODATA_L &= 0x4;
      break;
    case TL_Off:
      GPIODATA_L = 0x0;
      break;
    default:
      break;
  }
}
