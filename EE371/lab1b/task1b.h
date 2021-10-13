#ifndef __TASK1B_H__
#define __TASK1B_H__

#define RCGCGPIO (*((volatile uint32_t *)0x400FE608))

#define GPIODIR_J (*((volatile uint32_t *)0x40060400))
#define GPIODEN_J (*((volatile uint32_t *)0x4006051C))
#define GPIODATA_J (*((volatile uint32_t *)0x400603FC))

#define GPIODIR_N (*((volatile uint32_t *)0x40064400))
#define GPIODEN_N (*((volatile uint32_t *)0x4006451C))
#define GPIODATA_N (*((volatile uint32_t *)0x400643FC))

#define GPIOPUR_J (*((volatile uint32_t *)0x40060510))

#endif //__TASK1A_H__
