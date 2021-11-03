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
    RCGCTIMER |= GPTM0_16_32;           // Enable 16/32 Timer 0

    GPTMCTL_0 = GPTMA_DISABLE;           // Disable Timer A
    GPTMCFG_0 = TM_MODE_32;              // Select two timer to 32-bit mode
    GPTMTAMR_0 |= TAMR_PER_TM_MODE;      // Set periodic timer mode
    GPTMTAMR_0 &= ~TACDIR_COUNT_UP;      // Configure TACDIR0 to count down
    GPTMTAILR_0 = N16_MIL;               // Load value of 16 million into GPTMTAILR0
    GPTMCTL_0 |= GPTMA_ENABLE;           // Enable Timer A
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
    // Enable Port L Gating Clock
    RCGCGPIO |= Port_L;
    
    // Disable PL2, PL3, PL4 analog function
    GPIOAMSEL_L &= ~0x4;
    GPIOAMSEL_L &= ~0x8;
    GPIOAMSEL_L &= ~0x10;
    // Select PL2, PL3, PL4 regular port function
    GPIOAFSEL_L &= ~0x4;
    GPIOAFSEL_L &= ~0x8;
    GPIOAFSEL_L &= ~0x10;
    // Set PL2, PL3, PL4 to input direction
    GPIODIR_L |= 0x4;
    GPIODIR_L |= 0x8;
    GPIODIR_L |= 0x10;
    // Enable PL2, PL3, PL4 digital function
    GPIODEN_L |= 0x4;
    GPIODEN_L |= 0x8;
    GPIODEN_L |= 0x10;
}
// turn on Green LED
void Go_Output(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L |= 0x10;
}
// turn on Red LED
void Stop_Output(void)
{
    GPIODATA_L |= 0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L &= ~0x10;
}
// turn on Yellow LED
void Warn_Output(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L |= 0x8;
    GPIODATA_L &= ~0x10;
}
// turn off all LEDs
void Off_Output(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L &= ~0x10;
}

void extern_switch_init(void)
{
    RCGCGPIO |= 0x400;
    // Disable PL0, PL1 analog function
    GPIOAMSEL_L &= ~0x1;
    GPIOAMSEL_L &= ~0x2;
    // Select PL0, PL1 regular port function
    GPIOAFSEL_L &= ~0x1;
    GPIOAFSEL_L &= ~0x2;
    // Set PL0, PL1 to input direction
    GPIODIR_L &= ~0x1;
    GPIODIR_L &= ~0x2;
    // Enable PL0, PL1 digital function
    GPIODEN_L |= 0x1;
    GPIODEN_L |= 0x2;   
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
enum TL_State
{
    TL_SMStart,
    TL_Go,
    TL_Warn,
    TL_Stop,
    TL_Off
} TL_State; // state variable declaration

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
        Off_Output();
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
        Go_Output();
        break;
    case TL_Warn:
        Warn_Output();
        break;
    case TL_Stop:
        Stop_Output();
        break;
    case TL_Off:
        Off_Output();
        break;
    default:
        break;
    }
}
