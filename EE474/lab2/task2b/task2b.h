#ifndef __task2b_H__
#define __task2b_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))
#define GPIOLOCK_J (*((volatile uint32_t *)0x40060520))
#define GPIOCR_J (*((volatile uint32_t *)0x40060524))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))
#define GPIOIS_J  (*((volatile uint32_t *)0x40060404))
#define GPIOIBE_J (*((volatile uint32_t *)0x40060408))
#define GPIOIEV_J (*((volatile uint32_t *)0x4006040C))
#define GPIOICR_J (*((volatile uint32_t *)0x4006041C))
#define GPIOIM_J (*((volatile uint32_t *)0x40060410))
#define GPIOMIS_J (*((volatile uint32_t *)0x40060418))


#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMRIS_0 (*((volatile uint32_t *)0x4003001C))
#define GPTMICR_0 (*((volatile uint32_t *)0x40030024))

#define GPTMIMR_0 (*((volatile uint32_t *)0x40030018))
#define GPTMIMR_1 (*((volatile uint32_t *)0x40031018))
#define EN0 (*((volatile uint32_t *)0xE000E100))
#define EN1 (*((volatile uint32_t *)0xE000E104))
#define ENABLE_19 0x80000
#define ENABLE_51 0x80000

void GPIO_init();
void timer_init();
void Timer0A_Handler();
void PortJ_Handler();
void pattern();

#endif //__TASK2b_H__
