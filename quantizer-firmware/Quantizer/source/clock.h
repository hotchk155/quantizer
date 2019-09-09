#pragma GCC diagnostic ignored "-Wswitch"

#ifndef CLOCK_H_
#define CLOCK_H_



/////////////////////////////////////////////////////////////////
// This class maintains a count of 24ppqn ticks based on the
// current BPM or the external MIDI clock. Internal clock is
// generated based on a once-per-millisecond interrupt
class CClock {
public:
	volatile byte m_ms_tick;					// flag set each time 1ms is up
	volatile unsigned int m_ms;					// ms counter


	///////////////////////////////////////////////////////////////////////////////
	CClock() {
		m_ms_tick = 0;
		m_ms = 0;
	}


	///////////////////////////////////////////////////////////////////////////////
	void init() {
		// configure a timer to cause an interrupt once per millisecond
		CLOCK_EnableClock(kCLOCK_Pit0);
		pit_config_t timerConfig = {
		 .enableRunInDebug = true,
		};
		PIT_Init(PIT, &timerConfig);
		EnableIRQ(PIT_CH0_IRQn);
		PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);
		PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, (uint32_t) MSEC_TO_COUNT(1, CLOCK_GetBusClkFreq()));
		PIT_StartTimer(PIT, kPIT_Chnl_0);

	}



	///////////////////////////////////////////////////////////////////////////////
	void wait_ms(int ms) {
		while(ms) {
			m_ms_tick = 0;
			while(!m_ms_tick);
			--ms;
		}
	}


	///////////////////////////////////////////////////////////////////////////////
	// Interrupt service routine called once per millisecond
	void tick_isr() {

		++m_ms;
		// set flag to indicate that a milliecond has elapsed
		// this is used for general timing purposes
		m_ms_tick = 1;
	}

};



///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


// define the clock instance
CClock g_clock;



// ISR for the millisecond timer
extern "C" void PIT_CH0_IRQHandler(void) {
	PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
	g_clock.tick_isr();
}


#endif // CLOCK_H_
