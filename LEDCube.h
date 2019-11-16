#include "Arduino.h"

class LEDCube {
	uint8_t *layers;
	uint8_t *leds;
	volatile uint8_t currentLayer;
	volatile uint32_t status;
public:
	static LEDCube* Instance();
	LEDCube(uint8_t* layers, uint8_t* leds);
	void set(uint32_t status);
	void interruptionRoutine();
	void start();
private:
	LEDCube() {};
	LEDCube(LEDCube const&) {};             
	LEDCube& operator=(LEDCube const&) {};  
	static LEDCube* m_pInstance;
};