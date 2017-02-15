#include "RGBLedLib.h"

int RGBLed::calculateStep(int prevValue, int endValue)
{
	int step = endValue - prevValue; // What's the overall gap?
	if (step) {                      // If its non-zero, 
		step = 1020 / step;              //   divide by 1020
	}
	return step;
}

int RGBLed::calculateVal(int step, int val, int i)
{
	if ((step) && i % step == 0) { // If step is non-zero and its time to change a value,
		if (step > 0) {              //   increment the value if step is positive...
			val += 1;
		}
		else if (step < 0) {         //   ...or decrement it if step is negative
			val -= 1;
		}
	}
	// Defensive driving: make sure val stays in the range 0-255
	if (val > 255) {
		val = 255;
	}
	else if (val < 0) {
		val = 0;
	}
	return val;
}

RGBLed::RGBLed()
{
}

RGBLed::RGBLed(uint8_t redPin, uint8_t grnPin, uint8_t bluPin)
{
	this->redPin = redPin;
	this->grnPin = grnPin;
	this->bluPin = bluPin;
}

void RGBLed::init()
{
	pinMode(redPin, OUTPUT);   // sets the pins as output
	pinMode(grnPin, OUTPUT);
	pinMode(bluPin, OUTPUT);
}

void RGBLed::init(uint8_t redPin, uint8_t grnPin, uint8_t bluPin) {
	this->redPin = redPin;
	this->grnPin = grnPin;
	this->bluPin = bluPin;

	init();
}

void RGBLed::crossFade(Color_t color)
{
	// Convert to 0-255
	int R = (color.R * 255) / 100;
	int G = (color.G * 255) / 100;
	int B = (color.B * 255) / 100;

	stepR = calculateStep(prevR, R);
	stepG = calculateStep(prevG, G);
	stepB = calculateStep(prevB, B);

	for (int i = 0; i <= 1020; i++) {
		redVal = calculateVal(stepR, redVal, i);
		grnVal = calculateVal(stepG, grnVal, i);
		bluVal = calculateVal(stepB, bluVal, i);

		analogWrite(redPin, redVal);   // Write current values to LED pins
		analogWrite(grnPin, grnVal);
		analogWrite(bluPin, bluVal);

		delay(wait); // Pause for 'wait' milliseconds before resuming the loop

		if (DEBUG) { // If we want serial output, print it at the 
			if (i == 0 || i % loopCount == 0) { // beginning, and every loopCount times
				Serial.print("Loop/RGB: #");
				Serial.print(i);
				Serial.print(" | ");
				Serial.print(redVal);
				Serial.print(" / ");
				Serial.print(grnVal);
				Serial.print(" / ");
				Serial.println(bluVal);
			}
			DEBUG += 1;
		}
	}
	// Update current values for next loop
	prevR = redVal;
	prevG = grnVal;
	prevB = bluVal;
	delay(hold); // Pause for optional 'wait' milliseconds before resuming the loop
}

void RGBLed::crossFade(Color_t color, int millisDuration) {
	wait = millisDuration / 1020;
	crossFade(color);
}

void RGBLed::set(Color_t color)
{
	redVal = color.R;
	grnVal = color.G;
	bluVal = color.B;

	analogWrite(redPin, redVal);   // Write current values to LED pins
	analogWrite(grnPin, grnVal);
	analogWrite(bluPin, bluVal);

	prevR = redVal;
	prevG = grnVal;
	prevB = bluVal;
	delay(hold); // Pause for optional 'wait' milliseconds before resuming the loop
}

bool RGBLed::stepCrossFade(Color_t color)
{
	if (step >= 0 && step <= 1020) {
		// Convert to 0-255
		int R = (color.R * 255) / 100;
		int G = (color.G * 255) / 100;
		int B = (color.B * 255) / 100;

		if (step == 0) {
			stepR = calculateStep(prevR, R);
			stepG = calculateStep(prevG, G);
			stepB = calculateStep(prevB, B);
		}

		redVal = calculateVal(stepR, redVal, step);
		grnVal = calculateVal(stepG, grnVal, step);
		bluVal = calculateVal(stepB, bluVal, step);

		analogWrite(redPin, redVal);   // Write current values to LED pins
		analogWrite(grnPin, grnVal);
		analogWrite(bluPin, bluVal);

		delay(wait); // Pause for 'wait' milliseconds before resuming the loop

		if (DEBUG) { // If we want serial output, print it at the 
			if (step == 0 || step % loopCount == 0) { // beginning, and every loopCount times
				Serial.print("Loop/RGB: #");
				Serial.print(step);
				Serial.print(" | ");
				Serial.print(redVal);
				Serial.print(" / ");
				Serial.print(grnVal);
				Serial.print(" / ");
				Serial.println(bluVal);
			}
			DEBUG += 1;
		}
		step++;
	}
	return (step >= 0 && step <= 1020);
}

Color_t RGBLed::BLACK = { 0, 0, 0 };
Color_t RGBLed::RED = { 100, 0, 0 };
Color_t RGBLed::GREEN = { 0, 100, 0 };
Color_t RGBLed::BLUE = { 0, 0, 100 };
Color_t RGBLed::YELLOW = { 100, 100, 0 };
Color_t RGBLed::WHITE = { 100, 100, 100 };