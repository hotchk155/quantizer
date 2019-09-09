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
	typedef uint16_t DAC_VALUE;

	enum {
		DEV_NONE,
		DEV_ADC,
		DEV_DAC
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
		MAX_TX_BUF = 32
	};
	DAC_VALUE m_dac[4];
	volatile DAC_VALUE m_prev_dac[4];
	volatile byte m_tx_buf[MAX_TX_BUF];
	volatile int m_tx_index;
	volatile int m_tx_size;


	// Prepare data for the DAC
	int prepare_dac_tx() {
		m_tx_index = 0;
		m_tx_size = 0;
		if(m_dac[0] != m_prev_dac[0]) {
			m_tx_buf[m_tx_size++] =  0x11; // write through DAC0
			m_tx_buf[m_tx_size++] =  m_dac[0]>>8;
			m_tx_buf[m_tx_size++] =  (byte)m_dac[0];
			m_tx_buf[m_tx_size++] =  0;
			m_prev_dac[0] = m_dac[0];
		}
		/*
		if(m_dac[1] != m_prev_dac[1]) {
			m_tx_buf[m_tx_size++] =  0x12; // write through DAC1
			m_tx_buf[m_tx_size++] =  m_dac[1]>>8;
			m_tx_buf[m_tx_size++] =  (byte)m_dac[1];
			m_prev_dac[1] = m_dac[1];
		}
		if(m_dac[2] != m_prev_dac[2]) {
			m_tx_buf[m_tx_size++] =  0x14; // write through DAC2
			m_tx_buf[m_tx_size++] =  m_dac[2]>>8;
			m_tx_buf[m_tx_size++] =  (byte)m_dac[2];
			m_prev_dac[2] = m_dac[2];
		}
		if(m_dac[3] != m_prev_dac[3]) {
			m_tx_buf[m_tx_size++] =  0x18; // write through DAC3
			m_tx_buf[m_tx_size++] =  m_dac[3]>>8;
			m_tx_buf[m_tx_size++] =  (byte)m_dac[3];
			m_prev_dac[3] = m_dac[3];
		}*/
		return m_tx_size;
	}

public:
	CAdcDac() {
		memset(m_dac, 0, sizeof m_dac);
		memset((void*)m_prev_dac, 0, sizeof m_prev_dac);
		m_tx_index = 0;
		m_tx_size = 0;
	}
	inline void update_dac() {
		// SPI_C1_SPTIE_MASK bit 5
		// SPI_C1_SPIE_MASK bit 7
	    //SPI1->C1 |= (SPI_C1_SPTIE_MASK|SPI_C1_SPIE_MASK);
	    SPI1->C1 |= SPI_C1_SPTIE_MASK;
	}

	inline void set_dac(byte which, DAC_VALUE value, byte update = 0) {
		if(which<4) {
			m_dac[which] = value;
		}
		if(update) {
			update_dac();
		}
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
		//masterConfig.phase = kSPI_ClockPhaseSecondEdge;
	    SPI_MasterInit(SPI1, &masterConfig, CLOCK_GetFreq(kCLOCK_BusClk));


	    /* Enable interrupt, first enable slave and then master. */
	    EnableIRQ(SPI1_IRQn);


	}
	/*
	void refresh() {
		tx_prep();
   	    SPI0->C1 |= SPI_C1_SPTIE_MASK;
	}
	void tx_prep() {
		memcpy(m_tx_buf, m_buf, sizeof m_tx_buf);
		m_tx_index = 0;
		m_tx_pending = 0;
	}
	inline int is_tx_pending() {
		return m_tx_pending;
	}
	inline int is_tx_in_progress() {
		return m_tx_index < BUF_SIZE;
	}
	inline byte get_tx_byte() {
		return m_tx_buf[m_tx_index++];
	}

*/

	// called when transmit buffer empty
	// this is when data is loaded to SPI output shift register but
	// it has not been sent out yet!
	inline void tx_empty_irq() {
		if(m_tx_index < m_tx_size) {
			SPI1->D = m_tx_buf[m_tx_index++];
		}
		else if(prepare_dac_tx()) {
			csel(DEV_DAC);
			SPI1->D = m_tx_buf[m_tx_index++];
		}
		//else if(m_tx_index == m_tx_size){
    	  //  m_tx_index++;
		//}
		else {
    	    SPI1->C1 &= ~SPI_C1_SPTIE_MASK;
			csel(DEV_NONE);
		}
	}

	// called when receive buffer full
	// this is when SPI output shift register has finished sending
	inline void rx_full_irq() {
		/*
		if(m_tx_index > m_tx_size) {
    	    //SPI1->C1 &= ~SPI_C1_SPTIE_MASK;
			csel(DEV_NONE);
		}
		*/
	}

};

CAdcDac g_adc_dac;


/*******************************************************************************
 * Code
 ******************************************************************************/

extern "C" void SPI1_IRQHandler(void)
{
//    if ((SPI_GetStatusFlags(EXAMPLE_SPI_MASTER) & kSPI_TxBufferEmptyFlag) && g_leds.is_tx_pending()) {
    if (SPI1->S & SPI_S_SPTEF_MASK) {
    	g_adc_dac.tx_empty_irq();
    }
    /*
    if(SPI1->S & SPI_S_SPRF_MASK) {
    	g_adc_dac.rx_full_irq();
    }
*/


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
