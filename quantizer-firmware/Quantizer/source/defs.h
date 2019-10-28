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

enum {
	EV_NONE,
	EV_KEYDOWN,
	EV_KEYUP,
	EV_CV0,	// GRID
	EV_CV1, // ROOT
	EV_CV2, // IN
	EV_CV3, // CHORD
	EV_CV4, // POT
	EV_CV5, // AMOUNT
	EV_CV6 // SCALE
};

//
// FUNCTION PROTOTYPES
//
extern void event(byte event, int param);



#endif /* DEFS_H_ */
