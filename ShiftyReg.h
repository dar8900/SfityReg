#ifndef SHIFTY_REG_H
#define SHIFTY_REG_H

#include "Arduino.h"

#define DFLT_N_SHIFT_REG 	1
#define NOT_DEFINED_PIN     0

class ShiftyReg
{
	public:

		ShiftyReg(uint8_t DataPin = 2, 
					uint8_t ClockPin = 3, 
					uint8_t LatchPin = 4, 
					uint8_t OutPutEnablePin = NOT_DEFINED_PIN, 
					uint8_t ClearRegPin = NOT_DEFINED_PIN,
					uint8_t NShiftReg = DFLT_N_SHIFT_REG);
	
		void begin();
		bool clear();
		bool setExit(uint8_t ExitNumber, uint8_t Value);
		uint8_t getExit(uint8_t ExitNumber);
		bool toggleExit(uint8_t ExitNumber);
		bool setGroupOfExits(uint8_t *Exits, uint8_t NExits, uint8_t Value);
		void noOutput();
		void noOutput(uint16_t AmountOfTime);
	
	
	private:
		uint8_t _dataPin, _clockPin, _latchPin, _outputEnablePin, _clearRegPin;
		uint8_t _numRegisters = DFLT_N_SHIFT_REG;
		uint8_t _numberOfExits = DFLT_N_SHIFT_REG * 8;
		uint8_t *_shiftRegExits;
		bool _initilized = false;
		void _pulseClock();
		void _pulseLatch();
		void _pulseClear();
		void _updateBitConf(uint8_t RegNum, uint8_t NExit, uint8_t Value);
		uint8_t _readBitConf(uint8_t RegNum, uint8_t NExit);
		void _writeData(uint8_t Conf);
		void _loadExitConf();
		
};


#endif