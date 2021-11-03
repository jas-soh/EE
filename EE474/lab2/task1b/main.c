#include <stdint.h>
#include "task1b.h"


int main()
{
    timer0_init();
    LED_init();
    extern_switch_init();

    while (1)
    {
        tffFunc();
    }
    return 0;
}

void timer0_init()
{
    RCGCTIMER |= GPTM0_16_32;           // Enable 16/32 Timer 0

    GPTMCTL0 = GPTMA_DISABLE;           // Disable Timer A
    GPTMCFG0 = TM_MODE_32;              // Select two timer to 32-bit mode
    GPTMTAMR0 |= TAMR_PER_TM_MODE;      // Set periodic timer mode
    GPTMTAMR0 &= ~TACDIR_COUNT_UP;      // Configure TACDIR0 to count down
    GPTMTAILR0 = N16_MIL;               // Load value of 16 million into GPTMTAILR0
    GPTMCTL0 |= GPTMA_ENABLE;           // Enable Timer A
}


int two_seconds()
{
    GPTMICR0 |= 0x1;
    int t = 0;
    while (t < 2 )
    {
        if ((GPIODATA_L & 0x03) == 0x0) // unpressed
        {
          GPTMICR0 |= 0x1;
          return 0;
        }
        if (GPTMRIS0 & 0x1)
        {
          GPTMICR0 |= 0x1;
          t++;
        }
    }
    // must have finished holding two seconds
    return 1;
}

int five_seconds(int go)
{
    GPTMICR0 |= 0x1;
    int time = 0;
    while (time < 5)
    {
      if (sys_switch())
      {
        GPTMICR0 |= 0x1;
        return 0; // return 0 means sys switch was activated
      }
      if ((go == 1) && ped_switch())
      {
        GPTMICR0 |= 0x1;
        return 2; // return 0 means sys switch was activated
      }
      if (GPTMRIS0 & 0x1)
      {
        time++;
        GPTMICR0 |= 0x1;
      }
    }
    GPTMICR0 |= 0x1;
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
void Go_State(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L |= 0x10;
}
// turn on Red LED
void Stop_State(void)
{
    GPIODATA_L |= 0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L &= ~0x10;
}
// turn on Yellow LED
void Warn_State(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L |= 0x8;
    GPIODATA_L &= ~0x10;
}
// turn off all LEDs
void LED_off(void)
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
    int firstTime = GPIODATA_L & 0x1;
    if (firstTime == 0)
        return 0;
    int held = two_seconds();
    int secondTime = GPIODATA_L & 0x1;
    return firstTime && held;
}

unsigned long ped_switch(void)
{
    int firstTime = GPIODATA_L & 0x2;
    if (firstTime == 0)
        return 0;
    int held = two_seconds();
    int secondTime = GPIODATA_L & 0x2;
    return firstTime && held;
}
enum TFF_State
{
    TFF_Begin,
    TFF_S0,
    TFF_S1,
    TFF_S2,
    TFF_End
} TFF_State; // state variable declaration

void tffFunc()
{
  int wait;

  switch (TFF_State)
  {
    
    case TFF_Begin:
      TFF_State = TFF_S2;
      break;
      
    case TFF_S0:
      wait = five_seconds(1);
      if (wait == 1)
      {
        TFF_State = TFF_S2;
      } 
      else if (wait == 2)
      {
        TFF_State = TFF_S1;
      }
      else
      {
        TFF_State = TFF_End;
      }
      break;
      
    case TFF_S1:
      wait = five_seconds(0);
      if (wait == 1)
      {
        TFF_State = TFF_S2;
      } 
      else if (wait == 0)
      {
        TFF_State = TFF_End;
      }
      else
      {
        TFF_State = TFF_S2;
      }
      break;
      
    case TFF_S2:
      wait = five_seconds(0);
      if (wait == 1)
      {
        TFF_State = TFF_S0;
      } 
      else if (wait == 0)
      {
        TFF_State = TFF_End;
      }
      else
      {
        TFF_State = TFF_S0;
      }
      break;
      
    case TFF_End:
        LED_off();
        if (sys_switch())
        {
            TFF_State = TFF_Begin;
        }
        break;
        
    default:
        TFF_State = TFF_Begin;
        break;
    }
  
  
    switch (TFF_State) // State actions
    {
    case TFF_S0:
        Go_State();
        break;
    case TFF_S1:
        Warn_State();
        break;
    case TFF_S2:
        Stop_State();
        break;
    case TFF_End:
        LED_off();
        break;
    default:
        break;
    }
}
