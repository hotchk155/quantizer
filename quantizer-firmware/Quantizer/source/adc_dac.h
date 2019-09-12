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

	typedef uint32_t DAC_VALUE;

	enum {
		DEV_NONE,
		DEV_ADC,
		DEV_DAC
	};

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
	};
	DAC_VALUE m_dac[4]; // the lowest 16 bits are DAC value.. bit 16 is a "ready" flag
	volatile DAC_VALUE m_prev_dac[4];
	uint8_t m_adc_init[5];

	enum {
		TX_BUF_SIZE = 16,
		RX_BUF_SIZE = 16,
	};

	volatile int m_device;

	volatile uint8_t m_tx[TX_BUF_SIZE];
	volatile int m_tx_pos;
	volatile int m_tx_len;

	volatile uint8_t m_rx[TX_BUF_SIZE];
	volatile int m_rx_len;

	enum {
		TXN_ADCMODE,
		TXN_ADCCFG0,
		TXN_ADCCFG1,
		TXN_ADCCFG2,
		TXN_ADCCFG3,
		TXN_DAC0,
		TXN_DAC1,
		TXN_DAC2,
		TXN_DAC3
	};

	volatile int m_txn;

public:
	int m_done;
	CAdcDac() {
		memset(m_dac, 0, sizeof m_dac);
		memset((void*)m_prev_dac, 0, sizeof m_prev_dac);
		m_device = DEV_DAC;
		m_tx_pos = 0;
		m_tx_len = 0;
		m_rx_len = 0;
		m_txn = TXN_ADCMODE;
		m_done = 0;
		m_adc_init[0] = 0x88;
		m_adc_init[1] = 0x87;
		m_adc_init[2] = 0x97;
		m_adc_init[3] = 0xA7;
		m_adc_init[4] = 0xB7;
	}


	/*
	 	 MODE control byte 0x88 = 0b10001000 = external clock mode 0
	 	 Input config 	1ccc0rrr
	 	 conversion start 1ccc0000

	 	 ccc = channel 0-7


	 	 rrr = 111 = -Vref to +Vref (default)
	 	       110 = 0 to Vref
	 */
	void init_adc() {

	}

/*	inline void update_dac() {
	    SPI1->C1 |= SPI_C1_SPTIE_MASK;
	}*/




	void init() {
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


	    EnableIRQ(SPI1_IRQn);

		SPI1->C1 |= (SPI_C1_SPTIE_MASK|SPI_C1_SPIE_MASK);

	}

	inline void set_dac(byte which, uint16_t value, byte update = 0) {
		if(which<4) {
			m_dac[which] = value;
		}
	}


	void get_tx() {
		int idx;
		switch(m_txn) {
		case TXN_ADCMODE:
		case TXN_ADCCFG0:
		case TXN_ADCCFG1:
		case TXN_ADCCFG2:
		case TXN_ADCCFG3:
			m_device = DEV_ADC;
			idx = m_txn-TXN_ADCMODE;
			m_tx[0] = m_adc_init[idx];
			m_tx_len = 1;
			break;

		///////////////////////////////////////////
		case TXN_DAC0:
		case TXN_DAC1:
		case TXN_DAC2:
		case TXN_DAC3:
			m_device = DEV_DAC;
			idx = m_txn-TXN_DAC0;
			// form the data word to be sent (3 bytes used)
			if(m_dac[idx] != m_prev_dac[idx]) {
				m_tx[0] = 0x10|idx;
				m_tx[1] = (uint8_t)(m_dac[idx]>>8);
				m_tx[2] = (uint8_t)(m_dac[idx]);
			}
			else {
				m_tx[0] = 0x20;
				m_tx[1] = 0x00;
				m_tx[2] = 0x00;
			}
			m_tx_len = 3;
			break;
		}
	}
	void handle_rx() {
		switch(m_txn) {

		///////////////////////////////////////////
		case TXN_DAC0:
		case TXN_DAC1:
		case TXN_DAC2:
			++m_txn;
			break;
		case TXN_DAC3:
			m_txn = TXN_DAC0;
			break;

		///////////////////////////////////////////
		case TXN_ADCMODE:
		case TXN_ADCCFG0:
		case TXN_ADCCFG1:
		case TXN_ADCCFG2:
			++m_txn;
			break;
		case TXN_ADCCFG3:
			m_txn = TXN_ADCMODE;
			break;

		}
	}

	// Called when the last transmitted byte has started sending and the
	// SPI peripheral is ready to queue up a next one
	inline void tx_ready_irq() {

		// if there is no transaction in progress then we will
		// kick off the next one
		if(!m_tx_len) {
			// select the device
			csel(m_device);

			// prepare the next transaction and queue the first byte
			get_tx();
			m_tx_pos = 1;
			m_rx_len = 0;
			SPI1->D = m_tx[0];
		}
		// do we have any more of the current transaction to send out?
		else if(m_tx_pos < m_tx_len) {
			// send next byte
			SPI1->D = m_tx[m_tx_pos++];
		}
		// this is the final TX ready interrupt we get after all the data
		// for the transaction has been sent
		else {
			// prevent another interrupt until re-enabled by the receive
			// complete ISR
			++m_tx_pos;
			SPI1->C1 &= ~SPI_C1_SPTIE_MASK;
		}
	}

	inline void rx_complete_irq() {

		// capture the received byte
		m_rx[m_rx_len++] = SPI1->D;

		// is the transaction complete?
		if(m_tx_pos > m_tx_len) {
			// deselect the device
			csel(DEV_NONE);

			// handle the response
			handle_rx();

			// mark transaction as complete
			m_tx_len = 0;

			// re-enable the transmit buffer empty interrupt
			SPI1->C1 |= SPI_C1_SPTIE_MASK;
		}
	}
};

CAdcDac g_adc_dac;


/*******************************************************************************
 * Code
 ******************************************************************************/

extern "C" void SPI1_IRQHandler(void)
{
	uint8_t s = SPI1->S;
    if (s & SPI_S_SPTEF_MASK) {
    	g_adc_dac.tx_ready_irq();
    }
    if(s & SPI_S_SPRF_MASK) {
    	g_adc_dac.rx_complete_irq();
    }
}



#endif /* ADC_DAC_H_ */
