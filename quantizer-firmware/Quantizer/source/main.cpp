/*
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKE06Z128xxx4_Project.cpp
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKE06Z4.h"
#include "fsl_spi.h"
#include "fsl_pit.h"

#include "defs.h"
#include "digital_out.h"
#include "clock.h"
#include "apa102.h"
#include "adc_dac.h"
#include "ui.h"

/* TODO: insert other include files here. */

/* TODO: insert other definitions and declarations here. */

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*#define BUFFER_SIZE (64)
static uint8_t srcBuff[BUFFER_SIZE];
static uint8_t destBuff[BUFFER_SIZE];
static uint32_t txIndex = BUFFER_SIZE;
static uint32_t rxIndex = BUFFER_SIZE;
static volatile bool masterFinished = false;
static volatile bool slaveFinished = false;
*/


int main(void)
{
   uint32_t sourceClock = 0U;
//    uint32_t i = 0U;
//    uint32_t err = 0U;

    /* Init the boards */
    BOARD_InitPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();

//    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    //PRINTF("\r\nSPI board to board interrupt master example started!\r\n");

    g_clock.init();
    g_apa102.init();
    g_adc_dac.init();

    uint32_t xx[32] = {
    		KEY_GRID,
    		KEY_ROOT,
    		KEY_SCALE,
    		KEY_SHIFT,
    		KEY_CHORD,
    		KEY_SAVE,
    		KEY_C,
    		KEY_CSHARP,
    		KEY_D,
    		KEY_DSHARP,
    		KEY_E,
    		KEY_F,
    		KEY_FSHARP,
    		KEY_G,
    		KEY_GSHARP,
    		KEY_A,
    		KEY_ASHARP,
    		KEY_B
    };
    int q=0;
    int ii=32000;
	g_apa102.cls();
	g_apa102.refresh();

    while(1) {
    	ii ^=1;
    	g_adc_dac.set_dac(0, ii);
    	g_adc_dac.set_dac(1, ii);
    	g_adc_dac.set_dac(2, ii);
    	g_adc_dac.set_dac(3, ii);
    	g_adc_dac.update_dac();
    	//ii=ii+100;
    	if(ii>65535) ii=0;
		g_clock.wait_ms(1);
    }/*
    	g_pin_trigout.set(q);
    	g_pin_led0.set(q);
    	g_pin_led1.set(!q);
    	q=!q;
		g_clock.wait_ms(100);
		uint32_t k = read_keys();
		g_apa102.cls();
		for(uint32_t i=0; i<g_apa102.NUM_LEDS; ++i) {
			g_apa102.set(i, (k&(xx[i]))? 0x70:0);
		}
		g_apa102.refresh();
    }*/

    while (1)
    {
    }
}

/*
 * @brief   Application entry point.
int main(void) {
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
	BOARD_InitDebugConsole();



    volatile static int i = 0 ;
    while(1) {
        i++ ;
    }
    return 0 ;
}
*/
