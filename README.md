# ShiftyReg Class
## This is a C++ class called ShiftyReg that provides an interface for controlling shift registers. The shift register is used to expand the number of digital output pins on a microcontroller. This library is designed to work with the popular 74HC595 shift register.

## Constructor
The constructor takes the following parameters:

```c++

ShiftyReg(
    uint8_t DataPin = 2, 
    uint8_t ClockPin = 3, 
    uint8_t LatchPin = 4, 
    uint8_t OutPutEnablePin = NOT_DEFINED_PIN, 
    uint8_t ClearRegPin = NOT_DEFINED_PIN,
    uint8_t NShiftReg = DFLT_N_SHIFT_REG
);
```
DataPin - the pin number to which the shift register's serial data input pin is connected (default: 2)
ClockPin - the pin number to which the shift register's clock input pin is connected (default: 3)
LatchPin - the pin number to which the shift register's latch input pin is connected (default: 4)
OutPutEnablePin - the pin number to which the shift register's output enable pin is connected (default: NOT_DEFINED_PIN)
ClearRegPin - the pin number to which the shift register's clear pin is connected (default: NOT_DEFINED_PIN)
NShiftReg - the number of shift registers in the chain (default: DFLT_N_SHIFT_REG)

## Public Methods

**begin**
```c++

void begin();
```
This method initializes the shift registers and sets the pins as outputs.

**clear**
```c++

bool clear();
```
This method clears all the shift register's outputs.

**setExit**
```c++

bool setExit(uint8_t ExitNumber, uint8_t Value);
```
This method sets a specific output of the shift register to the specified value.

**ExitNumber** - the output number to set
**Value** - the value to set the output to (0 or 1)

**getExit**
```c++

uint8_t getExit(uint8_t ExitNumber);
```
This method returns the value of a specific output of the shift register.

**ExitNumber** - the output number to get

**toggleExit**
```c++

bool toggleExit(uint8_t ExitNumber);
```
This method toggles the value of a specific output of the shift register.

**ExitNumber** - the output number to toggle

**setGroupOfExits**
```c++

bool setGroupOfExits(uint8_t *Exits, uint8_t NExits, uint8_t Value);
```
This method sets the values of a group of outputs of the shift register to the specified value.

**Exits** - an array of output numbers to set
**NExits** - the number of outputs in the array
**Value** - the value to set the outputs to (0 or 1)

**noOutput**
```c++

void noOutput();
```
This method disables the shift register's output.

**noOutput(uint16_t AmountOfTime)**
```c++

void noOutput(uint16_t AmountOfTime);
```
This method disables the shift register's output for a specified amount of time (in milliseconds).

**AmountOfTime** - the amount of time to disable the output (in milliseconds)