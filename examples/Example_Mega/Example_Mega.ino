#include <LEDCube.h>

LEDCube* cube;

void setup() {
  uint8_t* layers = new uint8_t[3]{2,3,4};
  uint8_t* leds = new uint8_t[9]{30,31,32,33,34,35,36,37,38};
  for(int i = 0 ; i<9 ; i++){
    if(i<3){
      pinMode(layers[i],OUTPUT);
    }
    pinMode(leds[i],OUTPUT);
  }
  cube = new LEDCube(layers, leds);
  cube->start();
}

void loop() {
  cube->set(0b100100100010010010001001001);
  delay(5000);
  cube->set(0b111000000000111000000000111);
  delay(5000);
}