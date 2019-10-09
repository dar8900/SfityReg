#include "ShiftyReg.h"



SHIFTY_REG::~SHIFTY_REG()
{
	delete [] shifRegRegisters;	
}

void SHIFTY_REG::pulseClock()
{
	digitalWrite(clockPin, HIGH);
	digitalWrite(clockPin, LOW);	
}

void SHIFTY_REG::pulseLatch()
{
	digitalWrite(latchPin, HIGH);
	digitalWrite(latchPin, LOW);	
}

void SHIFTY_REG::pulseClear()
{
	digitalWrite(clearRegPin, LOW);
	digitalWrite(clearRegPin, HIGH);
}

void SHIFTY_REG::begin(uint8_t DataPin, uint8_t ClockPin, uint8_t LatchPin,  uint8_t OutputEnablePin, uint8_t ClearRegPin, uint8_t NOutput, uint8_t NShiftReg)
{
	dataPin = DataPin;
	clockPin = ClockPin;
	latchPin = LatchPin;
	outputEnablePin = OutputEnablePin;
	clearRegPin = ClearRegPin;
	nRegisterExits = NShiftReg * 8;
	numberOfExits = NOutput;
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	digitalWrite(clockPin, LOW);
	digitalWrite(latchPin, LOW);
	
	if(outputEnablePin != NOT_DEFINED_PIN)
	{
		pinMode(outputEnablePin, OUTPUT);
		digitalWrite(outputEnablePin, HIGH); // Active low
	}
	if(clearRegPin != NOT_DEFINED_PIN)
	{
		pinMode(clearRegPin, OUTPUT);
		digitalWrite(clearRegPin, HIGH);    // Active low
	}
	shifRegRegisters = new uint8_t [nRegisterExits];
	if(!shifRegRegisters)
	{
		return;
	}
	for(int RegIndex = 0; RegIndex < nRegisterExits; RegIndex++)
	{
		shifRegRegisters[RegIndex] = 0;
		digitalWrite(dataPin, shifRegRegisters[RegIndex]);
		pulseClock();
	}
	pulseLatch();
	if(outputEnablePin != NOT_DEFINED_PIN)
	{
		pinMode(outputEnablePin, OUTPUT);
		digitalWrite(outputEnablePin, LOW); // Active low
	}
}

bool SHIFTY_REG::setSingleExit(uint8_t WichExit, uint8_t State)
{
	if(WichExit < numberOfExits && (State == 0 || State == 1))
	{
		shifRegRegisters[numberOfExits - 1 - WichExit] = State;
	}
	else
	{
		return false;
	}
	return true;
}

bool SHIFTY_REG::loadSingleExit(uint8_t WichExit)
{
	if(WichExit < numberOfExits)
	{
		for(int j = 0; j < numberOfExits; j++)
		{
			if(j == WichExit)
				digitalWrite(dataPin, shifRegRegisters[WichExit]);
			else
				digitalWrite(dataPin, LOW);
			pulseClock();
		}
		pulseLatch();
	}
	else
	{
		return false;
	}
	return true;
}

bool SHIFTY_REG::setAllExit(uint8_t *StateArray)
{
	for(int i = 0; i < numberOfExits; i++)
	{
		if((StateArray + i) != NULL)
			shifRegRegisters[numberOfExits - 1 - i] = StateArray[i];
	}
	return true;
}


bool SHIFTY_REG::setAndLoadSingleExit(uint8_t WichExit, uint8_t State)
{
	if(WichExit < numberOfExits)
	{
		shifRegRegisters[numberOfExits - 1 - WichExit] = State;
		for(int j = 0; j < numberOfExits; j++)
		{
			if(j == WichExit)
				digitalWrite(dataPin, shifRegRegisters[WichExit]);
			else
				digitalWrite(dataPin, LOW);
			pulseClock();
		}
		pulseLatch();
	}
	else
	{
		return false;
	}
	return true;
}

bool SHIFTY_REG::loadAllExit()
{
	for(int j = 0; j < numberOfExits; j++)
	{
		digitalWrite(dataPin, shifRegRegisters[j]);
		pulseClock();
	}	
	pulseLatch();
	return true;
}

bool SHIFTY_REG::loadAllExit(uint8_t State)
{
	if(State == 0 || State == 1)
	{
		for(int j = 0; j < numberOfExits; j++)
		{
			shifRegRegisters[numberOfExits - 1 - j] = State;
			digitalWrite(dataPin, shifRegRegisters[j]);
			pulseClock();
		}	
		pulseLatch();
	}
	else
		return false;
	return true;
}


uint8_t SHIFTY_REG::getSingleExit(uint8_t WichExit)
{
	if(WichExit < numberOfExits)
	{
		return shifRegRegisters[numberOfExits - 1 - WichExit];
	}
	else 
		return 0;
}


void SHIFTY_REG::getAllExit(uint8_t *ExitsArray)
{
	for(int i = 0; i < numberOfExits; i++)
	{
		if((ExitsArray + i) != NULL)
		{
			ExitsArray[i] = shifRegRegisters[numberOfExits - 1 - i];
		}
	}
}

bool SHIFTY_REG::clear()
{
	for(int j = 0; j < numberOfExits; j++)
	{
		shifRegRegisters[j] = 0;
	}	
	pulseClear();
	pulseLatch();
	return true;
}

void SHIFTY_REG::noOutput()
{
	digitalWrite(outputEnablePin, HIGH);
}

void SHIFTY_REG::noOutput(uint16_t AmountOfTime)
{
	digitalWrite(outputEnablePin, HIGH);
	delay(AmountOfTime);
	digitalWrite(outputEnablePin, LOW);
}
