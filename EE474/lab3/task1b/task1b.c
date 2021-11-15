#ifndef _task1b_H_
#define _task1b_H_

//GPIO
#define RCGCGPIO (*((volatile uint32_t *) 0x400FE608))
#define PORT_F 0x20
#define PORT_N 0x1000
#define PORT_E 0x10
#define PORT_J 0x100


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

// switches
#define SW1 0x1
#define SW2 0x2
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
#define GPTMCC_0 (*((volatile uint32_t *)0x40030FC8))

// interrupt
#define NVIC_EN0  (*((volatile uint32_t *)0xE000E100))
#define EN1 (*((volatile uint32_t *)0xE000E104))
#define ENABLE_51 0x80000

// UART page 1172
#define PIN_0 0x1
#define PIN_1 0x2
#define RCGCUART  (*((volatile uint32_t *)  0x400FE618))
#define PORT_A 0x1;
#define GPIODEN_A (*((volatile uint32_t *)0x4005851C))
#define GPIOAFSEL_A  (*((volatile uint32_t *)0x40058420))
#define GPIODR2R_A  (*((volatile uint32_t *)0x40058500))
//#define GPIOASLR_A  (*((volatile uint32_t *)0x40058518))
#define GPIOPCTL_A  (*((volatile uint32_t *)0x4005852C))

#define UARTCTL_0 (*((volatile uint32_t *)  0x400C030))
#define UARTIBRD_0 (*((volatile uint32_t *)  0x400C024))
#define UARTFBRD_0 (*((volatile uint32_t *)  0x400C028))
#define UARTLCRH_0 (*((volatile uint32_t *)  0x400C02C))
#define UARTCC_0 (*((volatile uint32_t *)  0x400CFC8))
#define UARTDR_0 (*((volatile uint32_t *)0x4000C000))

#endif  // _task1a_H_
