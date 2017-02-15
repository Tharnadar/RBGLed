#include "RGBLedLib.h"

RGBLed led;	// use default pin numbers R=11, G=10, B=9

void setup() {
	led.init();

	led.set(RGBLed::BLACK);
	delay(100);
}

void loop() {
	led.crossFade(RGBLed::RED);
	led.crossFade(RGBLed::GREEN);
	led.crossFade(RGBLed::BLUE);
	led.crossFade(RGBLed::YELLOW);
	led.crossFade(RGBLed::WHITE);
	led.crossFade(RGBLed::BLACK);
}
