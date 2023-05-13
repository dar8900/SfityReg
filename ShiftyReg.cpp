#include "ShiftyReg.h"

#define MAX_EXIT_4_REG	8

ShiftyReg::ShiftyReg(uint8_t DataPin, 
				uint8_t ClockPin, 
				uint8_t LatchPin, 
				uint8_t OutPutEnablePin, 
				uint8_t ClearRegPin,
				uint8_t NShiftReg)
{
	_dataPin = DataPin;
	_clockPin = ClockPin;
	_latchPin = LatchPin;
	_outputEnablePin = OutPutEnablePin;
	_clearRegPin = ClearRegPin;
	_numRegisters = NShiftReg;
	_numberOfExits = _numRegisters * MAX_EXIT_4_REG;
}

void ShiftyReg::_pulseClock()
{
	digitalWrite(_clockPin, HIGH);
	digitalWrite(_clockPin, LOW);	
}

void ShiftyReg::_pulseLatch()
{
	digitalWrite(_latchPin, HIGH);
	digitalWrite(_latchPin, LOW);	
}

void ShiftyReg::_pulseClear()
{
	digitalWrite(_clearRegPin, LOW);
	digitalWrite(_clearRegPin, HIGH);
}

/* First exit is the most left */
void ShiftyReg::_writeData(uint8_t Conf)
{
	uint8_t Data = LOW;
	int8_t Bit = MAX_EXIT_4_REG - 1;
	while(Bit >= 0){
		((Conf >> Bit) & 0x1) == 0x0 ? Data = LOW : Data = HIGH;
		Bit--;
		digitalWrite(_dataPin, Data);
		_pulseClock();
	}
}


void ShiftyReg::_loadExitConf()
{
	if(!_initilized){
		return;
	}
	for(uint8_t i = 0; i < _numRegisters; i++)
	{
		_writeData(_shiftRegExits[i]);
	}
	_pulseLatch();
}

void ShiftyReg::_updateBitConf(uint8_t RegNum, uint8_t NExit, uint8_t Value)
{
	uint8_t NewVal = 0x00;
	if(RegNum < _numRegisters && NExit < MAX_EXIT_4_REG && _initilized)
	{
		NewVal = _shiftRegExits[RegNum];
		switch (NExit)
		{
		case 0:
			Value > 0 ? NewVal |= 0b00000001 : NewVal &= 0b11111110;
			break;
		case 1:
			Value > 0 ? NewVal |= 0b00000010 : NewVal &= 0b11111101;
			break;
		case 2:
			Value > 0 ? NewVal |= 0b00000100 : NewVal &= 0b11111011;
			break;
		case 3:
			Value > 0 ? NewVal |= 0b00001000 : NewVal &= 0b11110111;
			break;
		case 4:
			Value > 0 ? NewVal |= 0b00010000 : NewVal &= 0b11101111;
			break;
		case 5:
			Value > 0 ? NewVal |= 0b00100000 : NewVal &= 0b11011111;	
			break;
		case 6:
			Value > 0 ? NewVal |= 0b01000000 : NewVal &= 0b10111111;
			break;						 
		case 7:
			Value > 0 ? NewVal |= 0b10000000 : NewVal &= 0b01111111;
			break;			
		default:
			break;
		}
		_shiftRegExits[RegNum] = NewVal;
	}
}

uint8_t ShiftyReg::_readBitConf(uint8_t RegNum, uint8_t NExit)
{
	uint8_t Ret = 0;
	if(RegNum < _numRegisters && NExit < MAX_EXIT_4_REG && _initilized)
	{
		Ret = (uint8_t)((_shiftRegExits[RegNum] >> NExit) & 0x1);
	}
	return Ret;
}

void ShiftyReg::begin()
{
	_shiftRegExits = new uint8_t[_numRegisters];

	pinMode(_dataPin, OUTPUT);
	pinMode(_clockPin, OUTPUT);
	pinMode(_latchPin, OUTPUT);
	digitalWrite(_clockPin, LOW);
	digitalWrite(_latchPin, LOW);
	
	if(_outputEnablePin != NOT_DEFINED_PIN)
	{
		pinMode(_outputEnablePin, OUTPUT);
		digitalWrite(_outputEnablePin, HIGH); // Active low
	}
	if(_clearRegPin != NOT_DEFINED_PIN)
	{
		pinMode(_clearRegPin, OUTPUT);
		digitalWrite(_clearRegPin, HIGH);    // Active low
	}

	if(_outputEnablePin != NOT_DEFINED_PIN)
	{
		pinMode(_outputEnablePin, OUTPUT);
		digitalWrite(_outputEnablePin, LOW); // Active low
	}
	_initilized = true;
}


bool ShiftyReg::clear()
{
	if(!_initilized){
		return false;
	}
	_pulseClear();
	_pulseLatch();
	return true;
}


bool ShiftyReg::setExit(uint8_t ExitNumber, uint8_t Value)
{
	bool ExitSetted = false;
	if(ExitNumber > 0){
		ExitNumber = ExitNumber - 1;
	}
	if(ExitNumber > _numberOfExits){
		return false;
	}
	_updateBitConf(ExitNumber / MAX_EXIT_4_REG, ExitNumber % MAX_EXIT_4_REG, Value);
	_loadExitConf();
	ExitSetted = true;
	return ExitSetted;
}


uint8_t ShiftyReg::getExit(uint8_t ExitNumber)
{
	if(ExitNumber > 0){
		ExitNumber = ExitNumber - 1;
	}
	return (_readBitConf(ExitNumber / MAX_EXIT_4_REG, ExitNumber % MAX_EXIT_4_REG));
}

bool ShiftyReg::toggleExit(uint8_t ExitNumber)
{
	bool Ret = false;
	if(getExit(ExitNumber) == 0){
		Ret = setExit(ExitNumber, 1);
	} else {
		Ret = setExit(ExitNumber, 0);
	}
	return Ret;
}

bool ShiftyReg::setGroupOfExits(uint8_t *Exits, uint8_t NExits, uint8_t Value)
{
	if(!Exits){
		return false;
	}
	for(int i = 0; i < NExits; i++)
	{
		setExit(Exits[i], Value);
	}
}

void ShiftyReg::noOutput()
{
	if(_initilized){
		digitalWrite(_outputEnablePin, HIGH);
	}
}

void ShiftyReg::noOutput(uint16_t AmountOfTime)
{
	if(_initilized){
		digitalWrite(_outputEnablePin, HIGH);
		delay(AmountOfTime);
		digitalWrite(_outputEnablePin, LOW);
	}
}
