/*
 * Led.h
 *
 *  Created on: 02 Apr 2016
 *      Author: seppe
 */

#ifndef Led_H
#define Led_H

#include "Arduino.h"
#include <stdint.h>

#define LED_ON HIGH
#define LED_OFF LOW

/**
 *  Inspired from https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix
 *  Rescaled to have a gamma intensity corresponding to a **percent** value.
 */
const uint8_t LED_gamma[] = { \
	  0,   0,   0,   0,   0,   0,   0,   0,   0,   0, \
	  0,   1,   1,   1,   1,   1,   2,   2,   2,   2, \
	  3,   3,   4,   4,   5,   5,   6,   7,   7,   8, \
	  9,  10,  11,  11,  13,  13,  15,  16,  17,  18, \
	 20,  21,  22,  24,  25,  27,  29,  31,  32,  35, \
	 37,  39,  41,  43,  46,  48,  50,  52,  56,  58, \
	 61,  64,  67,  70,  73,  77,  79,  83,  86,  90, \
	 95,  98, 102, 105, 110, 114, 119, 122, 127, 131, \
	137, 142, 146, 152, 156, 162, 167, 173, 177, 184, \
	191, 196, 203, 208, 215, 220, 228, 233, 241, 247, \
	255 };

// ========================================================

class Led {
public:
	Led(int8_t pin = -1);
	Led(int8_t pin, uint8_t maxIntensity);
	Led(int8_t pin, uint8_t minIntensity, uint8_t maxIntensity);
	virtual ~Led() {}

	virtual void setup();
	virtual void loop();

	int8_t pin();
	boolean isOn();
	boolean isOff();
	uint8_t intensity();
	uint8_t minIntensity();
	uint8_t maxIntensity();
	uint8_t targetIntensity();
	uint16_t fadeDuration();

	void setPin(int8_t pin);
	void setMinIntensity(uint8_t percent);
	void setMaxIntensity(uint8_t percent);
	void setFadeDurationMillis(uint16_t duration);

	void setFlash(uint8_t times);
	void setFlash(uint8_t times, uint16_t cycleMillis);

	void setIntensityImmediately(uint8_t percent);
	void setIntensity(uint8_t percent);

	void flash(uint8_t times = 0, uint16_t cycleMillis = 0);

	virtual void toggle(boolean onOff);
	virtual void toggle();
	virtual void on();
	virtual void off();

private:
	int8_t _pin;

	uint8_t _intensity;        // Current intensity
	uint8_t _startIntensity;
	uint8_t _targetIntensity;
	uint8_t _minIntensity;     // in percent (0 - 100)
	uint8_t _maxIntensity;
	uint32_t _startMillis;

	uint16_t _fadeDurationMillis;
	uint8_t _flashTimes;

	void _applyIntensityToLed();
};

#endif /* Led_H */
