#ifndef _task1a_H_
#define _task1a_H_

//GPIO
#define RCGCGPIO (*((volatile uint32_t *) 0x400FE608))
#define PORT_F 0x00000020
#define PORT_N 0x00001000
#define PORT_E 0x00000010


#define GPIODATA_F (*((volatile uint32_t *) 0x4005D3FC))
#define GPIODATA_N (*((volatile uint32_t *) 0x400643FC))
#define GPIODATA_E (*((volatile uint32_t *) 0x4005C3FC))

#define GPIODIR_F (*((volatile uint32_t *) 0x4005D400))
#define GPIODIR_N (*((volatile uint32_t *) 0x40064400))
#define GPIODIR_E (*((volatile uint32_t *) 0x4005C400))

#define GPIODEN_F (*((volatile uint32_t *) 0x4005D51C))
#define GPIODEN_N (*((volatile uint32_t *) 0x4006451C))
#define GPIODEN_E (*((volatile uint32_t *) 0x4005C51C))

#define GPIOAMSEL_E (*((volatile uint32_t *) 0x4005C528))
#define GPIOAFSEL_E (*((volatile uint32_t *) 0x4005C420))

#define LED1 0x2
#define LED2 0x1
#define LED3 0x10
#define LED4 0x1

// ADC
#define RCGCADC (*((volatile uint32_t *) 0x400FE638))
#define ADC_0_EN 0x1;

#define ADCACTSS_0 (*((volatile uint32_t *) 0x40038000))

#define ADCSSPRI_SS3 0x3000 // sequencer 3

#define ADCEMUX_0 (*((volatile uint32_t *) 0x40038014))

#define ADCTSSEL_0 (*((volatile uint32_t *) 0x4003801C))

#define ADCSSMUX3_0 (*((volatile uint32_t *) 0x400380A0))
#define ADCSSEMUX3_0 (*((volatile uint32_t *) 0x400380B8))

#define ADCSSCTL3_0 (*((volatile uint32_t *) 0x400380A4))

#define ADCIM_0 (*((volatile uint32_t *) 0x40038008))
#define MASK3_EN 0x8

#define ADCACTSS_0 (*((volatile uint32_t *) 0x40038000)
// ASEN3_EN

#define ADCCC_0 (*((volatile uint32_t *) 0x40038FC8))
#define ALTCLKCFG_EN 0x1

#define ADCISC_0 (*((volatile uint32_t *) 0x4003800C))
#define ADCSSFIFO3 (*((volatile uint32_t *) 0x400380A8))

// timer
#define RCGCTIMER (*((volatile uint32_t *)0x400FE604))
#define GPTMCTL_0 (*((volatile uint32_t *)0x4003000C))
#define GPTMCFG_0 (*((volatile uint32_t *)0x40030000))
#define GPTMTAMR_0 (*((volatile uint32_t *)0x40030004))
#define GPTMTAILR_0 (*((volatile uint32_t *)0x40030028))
#define GPTMADCEV_0 (*((volatile uint32_t *)0x40030070))

// interrupt
#define NVIC_EN0  (*((volatile uint32_t *)0xE000E100))

#endif  // _task1a_H_
