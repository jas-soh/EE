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
#define GPTM0_16_32 0x1           // Enable 16/32 Timer 0

#define MODE_32 0x0            // Select 32-bit mode
#define PERIODIC_MODE 0x2      // Configure TAMR bit of GPTMTAMR to be in periodic timer mode
#define TACDIR_COUNT_UP 0x10000   // Configure TACDIR bit of GPTMTAMR to count down
#define COUNT_DOWN 0x10000 // Configure TACDIR bit of GPTMTAMR to count down
#define VAL_16_MIL 0xF42400          // load the value 16,000,000

// Port L Address
#define GPIODIR_L   (*((volatile uint32_t *)0x40062400))
#define GPIODEN_L   (*((volatile uint32_t *)0x4006251C))
#define GPIODATA_L  (*((volatile uint32_t *)0x400623FC))
#define GPIOAMSEL_L (*((volatile uint32_t *)0x40062528))
#define GPIOAFSEL_L (*((volatile uint32_t *)0x40062420))

// initialize the RGB LEDs, no input variable
void LED_init();

// initialize the Timer0
void timer0_init();

// input variable n to keep n seconds
int two_seconds();

// initialize the system switch and pedestrian switch, no input variable
void extern_switch_init();

// check if system switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long sys_switch();

// check if pedestrian switch is pressed, no input variable, return value is 0 (unpreessed) or 1 (if pressed)
unsigned long ped_switch();

// traffice light controller, FSM function, Moore Machine, no input variable, no output value
void SM();
int five_seconds(int go);

#endif //__HEADER1_H__
