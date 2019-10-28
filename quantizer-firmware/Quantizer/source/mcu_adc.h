/*
 * mcu_adc.h
 *
 *  Created on: 17 Sep 2019
 *      Author: jason
 */

#ifndef MCU_ADC_H_
#define MCU_ADC_H_

#include "fsl_adc.h"
/*
PTC1	ADC0_SE9	CONTROL POT
PTC2	ADC0_SE10	AMOUNT INPUT
PTC3	ADC0_SE11	SCALE INPUT

*/

class CMcuAdc {
	enum {
		ADC_CHAN_KNOB = 9,
		ADC_CHAN_CV1 = 10,
		ADC_CHAN_CV2 = 11,
	};
public:
	enum {
		CH_KNOB,
		CH_CV1,
		CH_CV2,
		CH_MAX
	};
	enum {
		NO_RESULT = 0xFFFFFFFF
	};
private:
	adc_config_t adcConfigStrcut;
	adc_channel_config_t adcChannelConfigStruct;
	int m_last_result[CH_MAX];
	static const int m_adc_chan[CH_MAX];
	int m_chan;
	volatile byte m_adc_done;
	volatile int m_adc_result;

public:

	void init() {

		m_adc_done = 0;
		m_chan = 0;

	    EnableIRQ(ADC_IRQn);

	     // config->referenceVoltageSource = kADC_ReferenceVoltageSourceAlt0;
	    // config->enableLowPower = false;
	    // config->enableLongSampleTime = false;
	    // config->clockDivider = kADC_ClockDivider1;
	    //config->ResolutionMode = kADC_Resolution8BitMode;
	    //config->clockSource = kADC_ClockSourceAlt0;
	    ADC_GetDefaultConfig(&adcConfigStrcut);
	    config->ResolutionMode = kADC_Resolution12BitMode;
	    ADC_Init(ADC, &adcConfigStrcut);
	    ADC_EnableHardwareTrigger(ADC, false);

	    // Configure the user channel and interrupt.
	    adcChannelConfigStruct.enableInterruptOnConversionCompleted = true;
	    adcChannelConfigStruct.enableContinuousConversion = false;
	    for(int i=0; i<CH_MAX; ++i) {
	    	ADC_EnableAnalogInput(ADC, 1U << m_adc_chan[i], true);
	    	m_last_result[i] = NO_RESULT;
	    }

	    // kick off the first conversion
	    adcChannelConfigStruct.channelNumber = m_adc_chan[m_chan];
		ADC_SetChannelConfig(ADC, &adcChannelConfigStruct);

	}

	void run() {
		if(m_adc_done) {

		    m_last_result[m_chan] = m_adc_result;
		    if(++m_chan >= CH_MAX) {
		    	m_chan = 0;
		    }

		    m_adc_done = 0;
		    adcChannelConfigStruct.channelNumber = m_adc_chan[m_chan];
			ADC_SetChannelConfig(ADC, &adcChannelConfigStruct);
		}
	}
	inline volatile void on_adc_done()
	{
		m_adc_result = ADC_GetChannelConversionValue(ADC);
		m_adc_done = 1;
	}
};
const int CMcuAdc::m_adc_chan[CH_MAX] = {
		ADC_CHAN_KNOB,
		ADC_CHAN_CV1,
		ADC_CHAN_CV2
};


CMcuAdc g_mcu_adc;

extern "C" void ADC_IRQHandler(void) {
	g_mcu_adc.on_adc_done();
}

#endif
