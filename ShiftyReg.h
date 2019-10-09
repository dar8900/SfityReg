#ifndef SHIFTY_REG_H
#define SHIFTY_REG_H

#include "Arduino.h"

#define DFLT_N_SHIFT_REG 	1
#define NOT_DEFINED_PIN     0

class SHIFTY_REG
{
	public:
	~SHIFTY_REG();
	
	uint8_t numberOfExits = 8;
	
	/*  begin()    
	
		Inizializza i pin di default o nel caso quelli che l'utente seleziona e stabilisce la dimensione dell'array delle uscite
		
		#param DataPin         - Pin dedicato ai dati da inviare allo shift register
		#param ClockPin 	   - Pin dedicato al clock per registrare i dati nello shift register
		#param LatchPin 	   - Pin dedicato per memorizzare l'output
		#param OutputEnablePin - Pin dedicato per la fuoriuscita parallela dell'output
		#param ClearRegPin 	   - Pin per la pulizia del registro interno 
		#param NShiftReg 	   - Numero di shift register inseriti in serie	
	*/
		void begin(uint8_t DataPin = 2, uint8_t ClockPin = 3, uint8_t LatchPin = 4, uint8_t OutPutEnablePin = NOT_DEFINED_PIN, uint8_t ClearRegPin = NOT_DEFINED_PIN, uint8_t NOutput = 8 ,uint8_t NShiftReg = DFLT_N_SHIFT_REG);
		
	/*  setSingleExit(uint8_t WichExit, uint8_t State)
		
		Salva nell'array in RAM lo stato dell'uscita selezionata
		
		#param WichExit         - Quale uscita dello shift register
		#param State 	        - Stato associato all'uscita
	*/
		bool setSingleExit(uint8_t WichExit, uint8_t State);

	/*  setAllExit(uint8_t *StateArray)
		
		Salva nell'array in RAM tutte le uscite utilizzando un vettore fornito dall'utente
		
		#param *StateArray         - Quale uscita dello shift register
	*/		
		bool setAllExit(uint8_t *StateArray);
		
	/*  loadSingleExit(uint8_t WichExit)
		
		#param WichExit         - Quale uscita dello shift register
	*/
		bool loadSingleExit(uint8_t WichExit);
		
	/*  setAndLoadSingleExit(uint8_t WichExit, uint8_t State)
		
		#param WichExit         - Quale uscita dello shift register
		#param State
	*/
		bool setAndLoadSingleExit(uint8_t WichExit, uint8_t State);
		
	/*  loadAllExit()
		
		#param ---
	*/
		bool loadAllExit();
		
	/*  loadAllExit(uint8_t State)
		
		#param State         - Quale uscita dello shift register
	*/
		bool loadAllExit(uint8_t State);

	/*  getSingleExit(uint8_t WichExit)
		
		#param State         - Quale uscita dello shift register
	*/		
		uint8_t getSingleExit(uint8_t WichExit);
		
	/*  getAllExit(uint8_t *ExitsArray)
		
		#param State         - Quale uscita dello shift register
	*/
		void getAllExit(uint8_t *ExitsArray);
		
		
	/*  clear()
		
		#param ---
	*/
		bool clear();
		
	/*  noOutput()
		
		#param ---
	*/
		
		void noOutput();
		
	/*  noOutput()
		
		#param AmountOfTime         - Quale uscita dello shift register
	*/
		void noOutput(uint16_t AmountOfTime);
	
	
	private:
		uint8_t dataPin, clockPin, latchPin, outputEnablePin, clearRegPin;
		uint8_t nRegisterExits;
		uint8_t *shifRegRegisters;
		void pulseClock();
		void pulseLatch();
		void pulseClear();
		
};


#endif