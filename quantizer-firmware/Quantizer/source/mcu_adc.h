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
#define DEMO_ADC_BASE ADC
#define DEMO_ADC_IRQn ADC_IRQn
#define EXAMPLE_ADC_IRQHandler ADC_IRQHandler
*/
#define DEMO_ADC_USER_CHANNEL 11

volatile bool g_AdcConversionDoneFlag;
volatile uint32_t g_AdcConversionValue;
volatile uint32_t g_AdcInterruptCounter;

/*

class CMcuAdc {
adc_config_t adcConfigStrcut;
adc_channel_config_t adcChannelConfigStruct;

public:
	void init() {

	    EnableIRQ(ADC_IRQn);

	     // config->referenceVoltageSource = kADC_ReferenceVoltageSourceAlt0;
	    // config->enableLowPower = false;
	    // config->enableLongSampleTime = false;
	    // config->clockDivider = kADC_ClockDivider1;
	    //config->ResolutionMode = kADC_Resolution8BitMode;
	    //config->clockSource = kADC_ClockSourceAlt0;
	    ADC_GetDefaultConfig(&adcConfigStrcut);
	    ADC_Init(ADC, &adcConfigStrcut);
	    ADC_EnableHardwareTrigger(ADC, false);

	    // Configure the user channel and interrupt.
	    adcChannelConfigStruct.channelNumber = DEMO_ADC_USER_CHANNEL;
	    adcChannelConfigStruct.enableInterruptOnConversionCompleted = true;
	    adcChannelConfigStruct.enableContinuousConversion = false;
	    g_AdcInterruptCounter = 0U;

	    ADC_EnableAnalogInput(ADC, 1U << DEMO_ADC_USER_CHANNEL, true);
	}

	void run() {
		g_AdcConversionDoneFlag = false;

		// When in software trigger mode, each conversion would be launched once calling the "ADC_ChannelConfigure()"
		// function, which works like writing a conversion command and executing it. For another channel's conversion,
		// just to change the "channelNumber" field in channel configuration structure, and call the function
		// "ADC_ChannelConfigure()" again.
		// Also, the "enableInterruptOnConversionCompleted" inside the channel configuration structure is a parameter
		// for the conversion command. It takes affect just for the current conversion. If the interrupt is still
		// required for the following conversion, it is necessary to assert the "enableInterruptOnConversionCompleted"
		// every time for each command.
		ADC_SetChannelConfig(ADC, &adcChannelConfigStruct);
		while (!g_AdcConversionDoneFlag);
	}
};
extern "C" void ADC_IRQHandler(void) {
    g_AdcConversionDoneFlag = true;
    g_AdcConversionValue = ADC_GetChannelConversionValue(ADC);
    g_AdcInterruptCounter++;
}*/

//CMcuAdc g_mcu_adc;

#endif
