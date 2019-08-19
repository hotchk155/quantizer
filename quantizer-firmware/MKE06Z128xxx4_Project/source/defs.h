///////////////////////////////////////////////////////////////////////////////////
//
//                                  ~~  ~~             ~~
//  ~~~~~~    ~~~~~    ~~~~~    ~~~~~~  ~~     ~~~~~   ~~~~~~    ~~~~~   ~~    ~~
//  ~~   ~~  ~~   ~~  ~~   ~~  ~~   ~~  ~~    ~~   ~~  ~~   ~~  ~~   ~~   ~~  ~~
//  ~~   ~~  ~~   ~~  ~~   ~~  ~~   ~~  ~~    ~~~~~~~  ~~   ~~  ~~   ~~     ~~
//  ~~   ~~  ~~   ~~  ~~   ~~  ~~   ~~  ~~    ~~       ~~   ~~  ~~   ~~   ~~  ~~
//  ~~   ~~   ~~~~~    ~~~~~    ~~~~~~   ~~~   ~~~~~   ~~~~~~    ~~~~~   ~~    ~~
//
//  Serendipity Sequencer                                   CC-NC-BY-SA
//  hotchk155/2018                                          Sixty-four pixels ltd
//
//  GLOBAL DEFINITIONS
//
///////////////////////////////////////////////////////////////////////////////////

#ifndef DEFS_H_
#define DEFS_H_

#if DEBUG
	#define ASSERT(e) {if(!(e)) for(;;) {}}
#else
	#define ASSERT(e)
#endif

#if DEBUG
	#include "stdio.h"
	#define DBGLOG0(s) printf("%s\r\n",s)
	#define DBGLOG1(s,t) printf(s,t)
	#define DBGLOG2(s,t,u) printf(s,t,u)
#else
	#define DBGLOG0(s)
	#define DBGLOG1(s,t)
	#define DBGLOG2(s,t,u)
#endif

enum {
	EV_NONE,
	EV_KEY_PRESS,
	EV_KEY_RELEASE,
	EV_KEY_CLICK,
	EV_KEY_HOLD,
};

typedef unsigned char byte;

#define PORTA_BASE 0
#define PORTB_BASE 8
#define PORTC_BASE 16
#define PORTD_BASE 24

#define PORTE_BASE 0
#define PORTF_BASE 8
#define PORTG_BASE 16
#define PORTH_BASE 24

#define MK_GPIOA_BIT(port, bit) (((uint32_t)1) << ((port) + (bit)))
#define SET_GPIOA(mask) ((GPIO_Type *)GPIOA_BASE)->PSOR = (mask)
#define CLR_GPIOA(mask) ((GPIO_Type *)GPIOA_BASE)->PCOR = (mask)
#define READ_GPIOA(mask) (((GPIO_Type *)GPIOA_BASE)->PDIR & (mask))

#define MK_GPIOB_BIT(port, bit) (((uint32_t)1) << ((port) + (bit)))
#define SET_GPIOB(mask) ((GPIO_Type *)GPIOB_BASE)->PSOR = (mask)
#define CLR_GPIOB(mask) ((GPIO_Type *)GPIOB_BASE)->PCOR = (mask)
#define READ_GPIOB(mask) (((GPIO_Type *)GPIOB_BASE)->PDIR & (mask))


#endif /* DEFS_H_ */
