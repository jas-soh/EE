#include <stdint.h>
#include "task1b.h"

int main()
{
    timer1_init();
    timer0_init();
    LED_init();
    extern_switch_init();

    while (1)
    {
      tffFunc();
    }
    return 0;
}

int time = 0; // declare time to count the time
int cnt = 0;
int prev = 0;

void timer0_init()
{
    RCGCTIMER |= TIMER0_EN; // Enable 16/32 Timer 0

    GPTMCTL_0 = 0x0; // Disable Timer A
    GPTMCFG_0 = MODE_32_bit; // Select two timer to 32-bit mode
    GPTMTAMR_0 = PERIODIC_MODE; // Set to periodic timer mode
    GPTMTAMR_0 = COUNT_DOWN; // Configure TACDIR to count down
    GPTMTAILR_0 = VAL_16_MIL; // Load value of 16 million
    GPTMCTL_0 |= 0x1; // Enable Timer A
}

void timer1_init()
{
    RCGCTIMER |= TIMER1_EN; // Enable 16/32 Timer 1

    GPTMCTL_1 = 0x0; // Disable Timer A
    GPTMCFG_1 = MODE_32_bit; // Select two timer to 32-bit mode
    GPTMTAMR_1 = PERIODIC_MODE; // Set to periodic timer mode
    GPTMTAMR_1 = COUNT_DOWN; // Configure TACDIR to count down
    GPTMTAILR_1 = VAL_80_MIL; // Load value of 16 million
    GPTMCTL_1 |= 0x1; // Enable Timer A
}

int isReached()
{
    return (GPTMRIS_0 & 0x1);
}

void resetTimer()
{
    GPTMICR_0 |= 0x1;
}

int two_seconds()
{
    resetTimer();
    int t = 0;
    while (t < 2 )
    {
        if ((GPIODATA_L & 0x03) == 0x0) 
        {
          resetTimer();
          t = 0;
          return 0;
        }
        if (isReached())
        {
          resetTimer();
          t++;
        }
    }
    // must have finished holding two seconds
    return 1;
}

int five_seconds()
{
    GPTMICR_1 |= 0x1;
    int t = 0;
    while (t < 5 )
    {
        if (GPTMRIS_1 & 0x1)
        {
          GPTMICR_1 |= 0x1;
          t++;
        }
    }
    // must have finished holding two seconds
    return 1;
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
void go_output(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L |= 0x10;
}
// turn on Red LED
void stop_output(void)
{
    GPIODATA_L |= 0x4;
    GPIODATA_L &= ~0x8;
    GPIODATA_L &= ~0x10;
}
// turn on Yellow LED
void warn_output(void)
{
    GPIODATA_L &= ~0x4;
    GPIODATA_L |= 0x8;
    GPIODATA_L &= ~0x10;
}
// turn off all LEDs
void off_output(void)
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
    long pressed = GPIODATA_L & 0x1;
    if (pressed == 0x0)
        return pressed;
    int held = two_seconds();
    return pressed & held;
}

unsigned long ped_switch(void)
{
    long pressed = GPIODATA_L & 0x2;
    if (pressed == 0x0)
        return pressed;
    int held = two_seconds();
    return pressed & held;
}

enum TL_State
{
    TL_SMStart,
    TL_Go,
    TL_Warn,
    TL_Stop,
    TL_Off
} TL_State; // state variable declaration

void tffFunc()
{
    if (GPTMRIS_0 & 0x1)
    {
        cnt += 1;
        resetTimer();
    }

    switch (TL_State)
    {
    case TL_SMStart:
        prev = cnt;
        TL_State = TL_Stop;
        break;
    case TL_Go:
        if (sys_switch())
        {
            TL_State = TL_Off;
        }
        else if (ped_switch())
        {
            TL_State = TL_Warn;
            time = 0;
        }
        //else if (time == 500000)
        else if (cnt - prev >= 5)
        {
            prev = cnt;
            TL_State = TL_Stop;
        }
        else
        {
            GPTMICR_1 |= 0x1;
            while (!(GPTMRIS_1 & 0x1)) {}
            TL_State = TL_Stop;
          }
        break;
    case TL_Warn:

        if (sys_switch())
        {
            TL_State = TL_Off;
        }
        else if (cnt - prev >= 5)
        {
            prev = cnt;
            TL_State = TL_Stop;
        }
        else
            time++;
        break;
    case TL_Stop:

        if (sys_switch())
        {
            TL_State = TL_Off;
        }
        else if (cnt - prev >= 5)
        {
            prev = cnt;
            TL_State = TL_Go;
            time = 0;
        }
        else
            time++;
        break;
    case TL_Off:
        off_output();
        time = 0;
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
        go_output();
        break;
    case TL_Warn:
        warn_output();
        break;
    case TL_Stop:
        stop_output();
        break;
    case TL_Off:
        off_output();
        break;
    default:
        break;
    }
}
