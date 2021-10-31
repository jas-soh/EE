/*
#ifndef __task2_H__
#define __task2_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

// Port L Address
#define GPIODIR_L (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L (*((volatile uint32_t *)0x4006251C))
#define GPIODATA_L (*((volatile uint32_t *)0x400623FC))

#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))


// Port L Control
#define PL0 0x1  // connect to System ON/OFF button
#define PL1 0x2  // connect to Pedestrian ON/OFF button
#define PL2 0x4  // connect to Red LED
#define PL3 0x8  // connect to Yellow LED
#define PL4 0x10 // connect to Green LED

#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))

#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))

#define GPTMCTL_1 (*((volatile uint32_t *)0x4003100C))
#define GPTMCFG_1 (*((volatile uint32_t *)0x40031000))
#define GPTMTAMR_1 (*((volatile uint32_t *)0x40031004))
#define GPTMTAILR_1 (*((volatile uint32_t *)0x40031028))
#define GPTMRIS_1 (*((volatile uint32_t *)0x4003101C))
#define GPTMICR_1 (*((volatile uint32_t *)0x40031024))


#endif //__HEADER1_H__
*/

#ifndef __HEADER1_H__
#define __HEADER1_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))
#define Port_L 0x400
#define Port_F 0x20

// Timer
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))

#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMCFG_1 (*((volatile uint32_t *)0x40031000))

#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCTL_1 (*((volatile uint32_t *)0x4003100C))

#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAMR_1 (*((volatile uint32_t *)0x40031004))

#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMTAILR_1 (*((volatile uint32_t *)0x40031028))

#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMRIS_1 (*((volatile uint32_t *)0x4003101C))

#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))
#define GPTMICR_1 (*((volatile uint32_t *)0x40031024))

// Timer Configuation
#define TIMER0_EN 0x1 // Enable 16/32 Timer 0
#define TIMER1_EN 0x2 // Enable 16/32 Timer 1

#define MODE_32_bit 0x0 // 32-bit mode
#define PERIODIC_MODE 0x2 // Periodic timer mode
#define COUNT_DOWN 0x10000 // TACDIR bit to count down
#define VAL_16_MIL 0xF42400 // The value 16,000,000 in hex
#define VAL_80_MIL 0x4C4B400 // The value 16,000,000 in hex


// Port L Address
#define GPIODIR_L   (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L   (*((volatile uint32_t *)0x4006251C))
#define GPIODATA_L  (*((volatile uint32_t *)0x400623FC))
#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))

// Port L Control
#define PL0 0x1  // connect to System ON/OFF button
#define PL1 0x2  // connect to Pedestrian ON/OFF button
#define PL2 0x4  // connect to Red LED
#define PL3 0x8  // connect to Yellow LED
#define PL4 0x10 // connect to Green LED

// initialize the RGB LEDs, no input variable
void LED_init();

// Turn on green light
void go_output();

// Turn on yellow light
void warn_output();

// Turn on red light
void stop_output();

// Turn off all LEDs
void off_output();

// reset the timer
void resetTimer();

// initialize the Timer0 and Timer1
void timer0_init();
void timer1_init();

// input variable n to keep n seconds
int twoSeconds();

// initialize the system switch and pedestrian switch, no input variable
void extern_switch_init();

// check if system switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long sys_switch();

// check if pedestrian switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long ped_switch();

// check if the timer reach to 1 sec, return value is 0 (unreached) or 1 (if reached)
int isReached();

// traffice light controller, FSM function, Moore Machine, no input variable, no output value
void tffFunc();

#endif //__HEADER1_H__
