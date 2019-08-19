/*
 * apa102.h
 *
 *  Created on: 18 Aug 2019
 *      Author: jason
 */

#ifndef APA102_H_
#define APA102_H_



class CAPA102 {
public:
	enum {
		NUM_LEDS = 25,
		BUF_SIZE = (4 * (2+NUM_LEDS))
	};
private:

	byte m_tx_buf[BUF_SIZE];
	byte m_buf[BUF_SIZE];
	volatile int m_tx_index;
	volatile int m_tx_pending;

public:
	void init() {
		m_tx_index = 0;
		m_tx_pending = 0;
		int index = 0;

		// start frame
		m_buf[index++] = 0;
		m_buf[index++] = 0;
		m_buf[index++] = 0;
		m_buf[index++] = 0;

		// prepare each LED frame
		for(int i=0; i<NUM_LEDS; ++i) {
			m_buf[index++] = 0xFF;
			m_buf[index++] = 0;
			m_buf[index++] = 0;
			m_buf[index++] = 0;
		}

		// end frame
		m_buf[index++] = 0xFF;
		m_buf[index++] = 0xFF;
		m_buf[index++] = 0xFF;
		m_buf[index++] = 0xFF;

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
	    SPI_MasterInit(SPI0, &masterConfig, CLOCK_GetFreq(kCLOCK_BusClk));


	    /* Enable interrupt, first enable slave and then master. */
	    EnableIRQ(SPI0_IRQn);


	}
	void set(uint32_t index, uint32_t value) {
		if(index < NUM_LEDS) {
			int i = 4 + 4*index;
			m_buf[i+1] = (byte)(value);
			m_buf[i+2] = (byte)(value>>8);
			m_buf[i+3] = (byte)(value>>16);
		}
	}
	void cls() {
		for(int i=0; i<NUM_LEDS; ++i) {
			set(i,0);
		}
	}
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


};

CAPA102 g_apa102;


/*******************************************************************************
 * Code
 ******************************************************************************/

extern "C" void SPI0_IRQHandler(void)
{
//    if ((SPI_GetStatusFlags(EXAMPLE_SPI_MASTER) & kSPI_TxBufferEmptyFlag) && g_leds.is_tx_pending()) {

    if (SPI0->S & SPI_S_SPTEF_MASK) {
    	if(g_apa102.is_tx_in_progress()) {
    		SPI0->D = g_apa102.get_tx_byte();
    	}
    	else {
    	    SPI0->C1 &= ~SPI_C1_SPTIE_MASK;
    	}
    }
}


#endif /* APA102_H_ */
