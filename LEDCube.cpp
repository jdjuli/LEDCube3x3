#include <stddef.h>  // defines NULL
#include <stdint.h>
#include "LEDCube.h"


LEDCube* LEDCube::m_pInstance = NULL;

LEDCube* LEDCube::Instance() {
	return m_pInstance;
}

LEDCube::LEDCube(uint8_t* layers, uint8_t* leds) {
	this->layers = layers;
	this->leds = leds;
	this->currentLayer = 2;
}

void LEDCube::set(uint32_t status) {
	this->status = status;
}

void LEDCube::start() {
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	//set compare register values:
	OCR1A = 1; //Time = 1/(16*10E+6 / prescaler) * OCR1A
	TCCR1B |= (1 << WGM12); //Set CTC mode
	//Prescaler:
	// CS12  CS11  CS10
	//   0     0     1   ->  /1 (no prescaling)
	//   0     1     0   ->  /8
	//   0     1     1   ->  /64
	//   1     0     0   ->  /256
	//   1     0     1   ->  /1024
	TCCR1B |= (1 << CS12); //Set /256 prescaler
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);
	m_pInstance = this;
}

ISR(TIMER1_COMPA_vect) {
	LEDCube::Instance()->interruptionRoutine();
}

void LEDCube::interruptionRoutine() {
	digitalWrite(layers[currentLayer],LOW);
	this->currentLayer = (this->currentLayer + 1)%3;
	digitalWrite(layers[currentLayer],HIGH);
	uint8_t offset = currentLayer * 9;
	for (uint8_t i = 0; i < 9; i++) {
		uint8_t shamt = offset + i;
		uint32_t mask = 1ul << shamt;
		if (status & mask) {
			digitalWrite(leds[i],HIGH);
		}
		else {
			digitalWrite(leds[i],LOW);
		}
	}
}