/*
 * ui.h
 *
 *  Created on: 18 Aug 2019
 *      Author: jason
 */

#ifndef UI_H_
#define UI_H_


#define BITB_LED0		MK_GPIOA_BIT(PORTE_BASE, 1) // LED #0
#define BITA_LED1		MK_GPIOA_BIT(PORTC_BASE, 6) // LED #1

#define BITB_KCOL0		MK_GPIOA_BIT(PORTE_BASE, 0) // Col #0
#define BITB_KCOL1		MK_GPIOB_BIT(PORTE_BASE, 2) // Col #1
#define BITA_KCOL2		MK_GPIOA_BIT(PORTC_BASE, 7) // Col #2
#define BITA_KCOL3		MK_GPIOA_BIT(PORTB_BASE, 7) // Col #3
#define BITB_KCOL4		MK_GPIOB_BIT(PORTH_BASE, 2) // Col #4
#define BITA_KCOL5		MK_GPIOA_BIT(PORTC_BASE, 5) // Col #5

#define BITB_KROW0		MK_GPIOB_BIT(PORTE_BASE, 7) // Row #0
#define BITA_KROW1		MK_GPIOA_BIT(PORTB_BASE, 6) // Row #1
#define BITA_KROW2		MK_GPIOA_BIT(PORTA_BASE, 0) // Row #2
#define BITA_SWITCH		MK_GPIOA_BIT(PORTA_BASE, 1) // Switch

CDigitalOut<kGPIO_PORTE, 1> g_pin_led0;
CDigitalOut<kGPIO_PORTC, 6> g_pin_led1;

CDigitalOut<kGPIO_PORTE, 7> g_pin_krow0;
CDigitalOut<kGPIO_PORTB, 6> g_pin_krow1;
CDigitalOut<kGPIO_PORTA, 0> g_pin_krow2;

CDigitalIn<kGPIO_PORTE, 0> g_pin_kcol0;
CDigitalIn<kGPIO_PORTE, 2> g_pin_kcol1;
CDigitalIn<kGPIO_PORTC, 7> g_pin_kcol2;
CDigitalIn<kGPIO_PORTB, 7> g_pin_kcol3;
CDigitalIn<kGPIO_PORTH, 2> g_pin_kcol4;
CDigitalIn<kGPIO_PORTC, 5> g_pin_kcol5;

CDigitalIn<kGPIO_PORTA, 1> g_pin_switch;

CDigitalOut<kGPIO_PORTC, 0> g_pin_trigout;

/*
 Main boad net names
 VCC	K10	K09	K00 K02 K04 K06	MOSI
 GND 	K11	K08	K01	K03	K05	K07 SCK

 	 	B7  H2  C5  E1  C6  A0
 	 	B6  E7  E0  E2  C7  A1

 Control board net names
 VCC 	K03 K04 K05 LD0 LD1 CM2	MOSI
 GND	CM1 CM0 K00 K01 K02 SW1 SCK
 */

//////////////////////////////////////////////////////////////////////////////
//
// GLOBAL DATA DEFINITIONS
//
//////////////////////////////////////////////////////////////////////////////

class CUI {
	uint32_t m_key_acc;
	uint32_t m_key_state;
	byte m_state;
	int m_debounce;

	enum {
		ST_INIT,
		ST_READ0,
		ST_READ1,
		ST_READ2,
		ST_DEBOUNCE
	};

	enum {
		DEBOUNCE_MS = 50,
		MAX_KEYBIT = (1U<<18)
	};

public:
	enum {
		KEY_A1 = (1U<<0),
		KEY_A2 = (1U<<2),
		KEY_A3 = (1U<<3),

		KEY_B1 = (1U<<4),
		KEY_B2 = (1U<<5),
		KEY_B3 = (1U<<6),

		KEY_N1 = (1U<<18),
		KEY_N2 = (1U<<17),
		KEY_N3 = (1U<<16),
		KEY_N4 = (1U<<15),
		KEY_N5 = (1U<<14),
		KEY_N6 = (1U<<13),
		KEY_N7 = (1U<<7),
		KEY_N8 = (1U<<8),
		KEY_N9 = (1U<<9),
		KEY_N10 = (1U<<10),
		KEY_N11 = (1U<<11),
		KEY_N12 = (1U<<12),

		KEY_GRID 	= KEY_A1,
		KEY_ROOT 	= KEY_A2,
		KEY_SCALE 	= KEY_A3,
		KEY_SHIFT 	= KEY_B1,
		KEY_CHORD 	= KEY_B2,
		KEY_SAVE 	= KEY_B3,
		KEY_C 		= KEY_N12,
		KEY_CSHARP 	= KEY_N11,
		KEY_D 		= KEY_N10,
		KEY_DSHARP 	= KEY_N9,
		KEY_E 		= KEY_N8,
		KEY_F 		= KEY_N7,
		KEY_FSHARP 	= KEY_N6,
		KEY_G 		= KEY_N5,
		KEY_GSHARP 	= KEY_N4,
		KEY_A 		= KEY_N3,
		KEY_ASHARP 	= KEY_N2,
		KEY_B 		= KEY_N1
	};

	void init() {
		m_key_state = 0;
		m_key_acc = 0;
		m_state = 0;
		m_debounce = 0;
	}

	inline uint32_t key_state() {
		return m_key_state;
	}
	// to be called once per millisecond
	void run(){
		uint32_t bit;
		uint32_t delta;

		switch(m_state) {

		case ST_INIT:
			// clear key accumulator
			m_key_acc = 0;

			// pull row 0 down
			CLR_GPIOB(BITB_KROW0);
			SET_GPIOA(BITA_KROW1);
			SET_GPIOA(BITA_KROW2);
			++m_state;
			break;

		case ST_READ0:
			// read column statuses
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOB(BITB_KCOL0));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOB(BITB_KCOL1));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_KCOL2));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_KCOL3));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOB(BITB_KCOL4));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_KCOL5));

			// pull row 1 down
			SET_GPIOB(BITB_KROW0);
			CLR_GPIOA(BITA_KROW1);
			SET_GPIOA(BITA_KROW2);
			++m_state;
			break;

		case ST_READ1:
			// read column statuses
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOB(BITB_KCOL0));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOB(BITB_KCOL1));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_KCOL2));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_KCOL3));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOB(BITB_KCOL4));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_KCOL5));

			// pull row 2 down
			SET_GPIOB(BITB_KROW0);
			SET_GPIOA(BITA_KROW1);
			CLR_GPIOA(BITA_KROW2);
			++m_state;
			break;

		case ST_READ2:
			// read column statuses
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOB(BITB_KCOL0));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOB(BITB_KCOL1));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_KCOL2));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_KCOL3));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOB(BITB_KCOL4));
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_KCOL5));

			// read the switch
			m_key_acc = (m_key_acc<<1)|(!READ_GPIOA(BITA_SWITCH));
			m_state = ST_INIT;

			bit = MAX_KEYBIT;
			delta = (m_key_acc ^ m_key_state);
			while(bit) {
				if(delta & bit) {
					if(m_key_acc & bit) {
						event(EV_KEYDOWN, bit);
						m_debounce = DEBOUNCE_MS;
						m_state = ST_DEBOUNCE;
					}
					else {
						event(EV_KEYUP, bit);
					}
				}
				bit <<= 1;
			}
			break;

		case ST_DEBOUNCE:
			if(!m_debounce) {
				m_state = 0;
			}
			else {
				--m_debounce;
			}
			break;
		}
	}
};


CUI g_ui;

#endif /* UI_H_ */
