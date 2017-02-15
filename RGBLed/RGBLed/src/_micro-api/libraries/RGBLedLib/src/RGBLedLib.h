/*
 Name:		RGBLedLib.h
 Created:	2/15/2017 10:31:00 AM
 Author:	giancarlo.riccio
 Editor:	http://www.visualmicro.com
*/

#ifndef _RGBLedLib_h
#define _RGBLedLib_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

struct Color_t {
	uint8_t R;
	uint8_t G;
	uint8_t B;
};

class RGBLed
{
private:
	uint8_t redPin = 11;	// Red LED
	uint8_t grnPin = 10;	// Green LED
	uint8_t bluPin = 9;		// Blue LED

	int redVal = 0, grnVal = 0, bluVal = 0;
	int prevR = 0, prevG = 0, prevB = 0;
	int stepR = 0, stepG = 0, stepB = 0;
	int step = 0;

	int wait = 10;      // 10ms internal crossFade delay; increase for slower fades
	int hold = 0;       // Optional hold when a color is complete, before the next crossFade
	int DEBUG = 0;
	int loopCount = 60; // How often should DEBUG report?


protected:
	int calculateStep(int prevValue, int endValue);
	int calculateVal(int step, int val, int i);

public:
	RGBLed();
	RGBLed(uint8_t redPin, uint8_t grnPin, uint8_t bluPin);

	void init();
	void init(uint8_t redPin, uint8_t grnPin, uint8_t bluPin);

	void crossFade(Color_t color);
	void crossFade(Color_t color, int millisDuration);
	void set(Color_t color);

	bool stepCrossFade(Color_t color);

	static Color_t
		BLACK,
		RED,
		GREEN,
		BLUE,
		YELLOW,
		WHITE;
};

#endif

