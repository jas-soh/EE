#ifndef __task1a_H__
#define __task1a_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

#define GPIODIR_F (*((volatile uint32_t *)0x4005D400))
#define GPIODIR_N (*((volatile uint32_t *)0x40064400))

#define GPIODEN_F (*((volatile uint32_t *)0x4005D51C))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))

#define GPIODATA_F (*((volatile uint32_t *)0x4005D35C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))

#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018))
#define EN0 (*((volatile uint32_t *)0xE000E100))
#define ENABLE_19 0x80000

void timer_init();
//void interrupt_init();
void count_down();
void Timer0A_Handler();
void pattern();

#endif //__TASK1a_H__
