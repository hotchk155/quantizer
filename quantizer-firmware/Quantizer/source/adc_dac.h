/*
 * adc_dac.h
 *
 *  Created on: 19 Aug 2019
 *      Author: jason
 */

#ifndef ADC_DAC_H_
#define ADC_DAC_H_

//ADC MAX1303
//DAC MAX5134


#define BITA_DAC_LDAC		MK_GPIOA_BIT(PORTD_BASE, 6)
#define BITA_ADC_CSEL		MK_GPIOA_BIT(PORTD_BASE, 3)
#define BITA_ADC_SSTP		MK_GPIOA_BIT(PORTD_BASE, 4)
#define BITA_DAC_CSEL		MK_GPIOA_BIT(PORTA_BASE, 6)
#define BITA_DAC_READY		MK_GPIOA_BIT(PORTA_BASE, 7)

CDigitalOut<kGPIO_PORTD, 3, 1> g_adc_csel; // initially high
CDigitalIn<kGPIO_PORTD, 4> g_adc_sstp;

CDigitalOut<kGPIO_PORTA, 6, 1> g_dac_csel; // initially high
CDigitalIn<kGPIO_PORTA, 7> g_dac_ready;
CDigitalOut<kGPIO_PORTD, 6, 0> g_dac_ldac;

class CAdcDac {
public:
private:

//	byte m_tx_buf[BUF_SIZE];
	//byte m_buf[BUF_SIZE];
	//volatile int m_tx_index;
	//volatile int m_tx_pending;
	typedef uint32_t DAC_VALUE;

	enum {
		DEV_NONE,
		DEV_ADC,
		DEV_DAC
	};


	enum {
		ST_BEGIN,
		ST_DAC_DATA1,
		ST_DAC_DATA2,
		ST_DAC_DATA3,
		ST_DAC_WAIT1,
		ST_DAC_WAIT2
	};

	/*
#define SET_GPIOA(mask) ((GPIO_Type *)GPIOA_BASE)->PSOR = (mask)
#define CLR_GPIOA(mask) ((GPIO_Type *)GPIOA_BASE)->PCOR = (mask)
#define READ_GPIOA(mask) (((GPIO_Type *)GPIOA_BASE)->PDIR & (mask))
*/
	// select either device by pulling its chip select low
	void csel(int device) {

		switch(device) {
		case DEV_ADC:
			SET_GPIOA(BITA_DAC_CSEL);
			CLR_GPIOA(BITA_ADC_CSEL);
			break;
		case DEV_DAC:
			SET_GPIOA(BITA_ADC_CSEL);
			CLR_GPIOA(BITA_DAC_CSEL);
			break;
		default:
			SET_GPIOA(BITA_ADC_CSEL);
			SET_GPIOA(BITA_DAC_CSEL);
			break;
		}
	}

	enum {
		NUM_DAC_CHANNELS = 4,
		//MAX_TX_BUF = 32,
		//SELECT_DAC = 0x100,
		//DESELECT_DAC = 0x200
	};
	uint32_t m_dac[4]; // the lowest 16 bits are DAC value.. bit 16 is a "ready" flag
	volatile uint16_t m_prev_dac[4];
	//volatile uint16_t m_tx_buf[MAX_TX_BUF];
	//volatile int m_tx_index;
	//volatile int m_tx_size;
	//volatile byte m_dac_deselect;
	volatile uint32_t m_dac_tx;
	volatile int m_state;
	volatile int m_chan;

	// Prepare data for the DAC
	/*
	int prepare_dac_tx() {
		m_tx_index = 0;
		m_tx_size = 0;
		if(m_dac[0] != m_prev_dac[0]) {
			m_tx_buf[m_tx_size++] =  SELECT_DAC|0x11; // write through DAC0
			m_tx_buf[m_tx_size++] =  m_dac[0]>>8;
			m_tx_buf[m_tx_size++] =  (byte)m_dac[0];
			m_tx_buf[m_tx_size++] =  DESELECT_DAC;
			m_prev_dac[0] = m_dac[0];
		}
		if(m_dac[1] != m_prev_dac[1]) {
			m_tx_buf[m_tx_size++] =  SELECT_DAC|0x12; // write through DAC1
			m_tx_buf[m_tx_size++] =  m_dac[1]>>8;
			m_tx_buf[m_tx_size++] =  (byte)m_dac[1];
			m_tx_buf[m_tx_size++] =  DESELECT_DAC;
			m_prev_dac[1] = m_dac[1];
		}
		if(m_dac[2] != m_prev_dac[2]) {
			m_tx_buf[m_tx_size++] =  SELECT_DAC|0x14; // write through DAC2
			m_tx_buf[m_tx_size++] =  m_dac[2]>>8;
			m_tx_buf[m_tx_size++] =  (byte)m_dac[2];
			m_tx_buf[m_tx_size++] =  DESELECT_DAC;
			m_prev_dac[2] = m_dac[2];
		}
		if(m_dac[3] != m_prev_dac[3]) {
			m_tx_buf[m_tx_size++] =  SELECT_DAC|0x18; // write through DAC3
			m_tx_buf[m_tx_size++] =  m_dac[3]>>8;
			m_tx_buf[m_tx_size++] =  (byte)m_dac[3];
			m_tx_buf[m_tx_size++] =  DESELECT_DAC;
			m_prev_dac[3] = m_dac[3];
		}
		return m_tx_size;
	}*/

public:
	CAdcDac() {
		memset(m_dac, 0, sizeof m_dac);
		memset((void*)m_prev_dac, 0, sizeof m_prev_dac);
//		m_tx_index = 0;
//		m_tx_size = 0;
		m_dac_tx = 0;
//		m_dac_deselect = 0;
		m_state = ST_BEGIN;
	}


	/*
	 	 MODE control byte 0xA8 = 0b10101000 = internal clock
	 	 Input config 	1ccc0rrr
	 	 conversion start 1ccc0000

	 	 ccc = channel 0-7


	 	 rrr = 111 = -Vref to +Vref (default)
	 	       110 = 0 to Vref
	 */
	void init_adc() {

	}

	inline void update_dac() {
	    SPI1->C1 |= SPI_C1_SPTIE_MASK;
	}




	void init() {
		//m_tx_index = 0;
		//m_tx_pending = 0;
		//int index = 0;


	    /* Init SPI master */
	    /*
	     * masterConfig->enableStopInWaitMode = false;
	     * masterConfig->polarity = kSPI_ClockPolarityActiveHigh;
	     * masterConfig->phase = kSPI_ClockPhaseFirstEdge;
	     * masterConfig->direction = kSPI_MsbFirst;
	     * masterConfig->dataMode = kSPI_8BitMode;
	     * masterConfig->txWatermark = kSPI_TxFifoOneHalfEmpty;
	     * masterConfig->rxWatermark = kSPI_RxFifoOneHalfFull;
	     * masterConfig->pinMode = kSPI_PinModeNormal;
	     * masterConfig->outputMode = kSPI_SlaveSelectAutomaticOutput;
	     * masterConfig->baudRate_Bps = 500000U;
	     */
	    spi_master_config_t masterConfig = {0};
		SPI_MasterGetDefaultConfig(&masterConfig);
	    masterConfig.polarity = kSPI_ClockPolarityActiveLow;
	    masterConfig.baudRate_Bps = 1000000U;
		//masterConfig.phase = kSPI_ClockPhaseSecondEdge;
	    SPI_MasterInit(SPI1, &masterConfig, CLOCK_GetFreq(kCLOCK_BusClk));


	    /* Enable interrupt, first enable slave and then master. */
	    EnableIRQ(SPI1_IRQn);


	}

	inline void set_dac(byte which, uint16_t value, byte update = 0) {
		if(which<4) {
			m_dac[which] = value;
		}
	}


	// called when transmit buffer empty
	// this is when data is loaded to SPI output shift register but
	// it has not been sent out yet!
	inline void tx_empty_irq() {
		switch(m_state) {
			case ST_BEGIN:
				m_chan = 0;
				m_state = ST_DAC_DATA1;
				// fall thru

			/////////////////////////////////////////////////////////////////////
			case ST_DAC_DATA1:

				// deselect DAC
				csel(DEV_NONE);

				// form the data word to be sent (3 bytes used)
				if(m_dac[m_chan] != m_prev_dac[m_chan]) {
					m_dac_tx = ((uint32_t)(0x10|m_chan)<<16)|m_dac[m_chan];
					m_prev_dac[m_chan] = m_dac[m_chan];
				}
				else {
					m_dac_tx = 0x00200000; // NOOP
				}

				// select DAC
				csel(DEV_DAC);
				SPI1->D = (uint8_t)(m_dac_tx>>16);
				m_state = ST_DAC_DATA2;
				break;
			case ST_DAC_DATA2:
				SPI1->D = (uint8_t)(m_dac_tx>>8);
				m_state = ST_DAC_DATA3;
				break;
			case ST_DAC_DATA3:
				SPI1->D = (uint8_t)(m_dac_tx);
				m_state = ST_DAC_WAIT1;
				break;
			case ST_DAC_WAIT1:
			    SPI1->C1 &= ~SPI_C1_SPTIE_MASK;
				m_state = ST_DAC_WAIT2;
				break;
		}
	}

	inline void rx_full_irq() {
		switch(m_state) {
		case ST_DAC_WAIT1:
			m_state = ST_DAC_WAIT2;
			break;
		case ST_DAC_WAIT2:
			if(++m_chan > NUM_DAC_CHANNELS) {
				m_chan = 0;
			}
			m_state = ST_DAC_DATA1;
		    SPI1->C1 |= SPI_C1_SPTIE_MASK;
		    break;
		}
	}

/*
		if(m_dac_deselect) {
			csel(DEV_NONE);
			m_dac_deselect = 0;
		}
		if(m_tx_index >= m_tx_size) {
			prepare_dac_tx();
		}
		if(m_tx_index < m_tx_size) {
			uint16_t cmd = m_tx_buf[m_tx_index++];
			if(cmd & SELECT_DAC) {
				csel(DEV_DAC);
			}
			SPI1->D = (byte)cmd;
			if(cmd & DESELECT_DAC) {
				m_dac_deselect = 1;
			}
		}
		else {
			SPI1->C1 &= ~SPI_C1_SPTIE_MASK;
		}
	}*/

};

CAdcDac g_adc_dac;


/*******************************************************************************
 * Code
 ******************************************************************************/

extern "C" void SPI1_IRQHandler(void)
{
	byte q = SPI1->S;
//    if ((SPI_GetStatusFlags(EXAMPLE_SPI_MASTER) & kSPI_TxBufferEmptyFlag) && g_leds.is_tx_pending()) {
    if (q & SPI_S_SPTEF_MASK) {
    	g_adc_dac.tx_empty_irq();
    }

    if(q & SPI_S_SPRF_MASK) {
    	g_adc_dac.rx_full_irq();
    }



	/*
    if (SPI1->S & SPI_S_SPTEF_MASK) {
    	if(g_apa102.is_tx_in_progress()) {
    		SPI1->D = g_apa102.get_tx_byte();
    	}
    	else {
    	    SPI1->C1 &= ~SPI_C1_SPTIE_MASK;
    	}
    }*/
}



#endif /* ADC_DAC_H_ */
