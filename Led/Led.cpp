/*
 * Led.cpp
 *
 *  Created on: 02 Apr 2016
 *      Author: seppe
 */

#include "Led.h"

Led::Led(int8_t pin, boolean initial_state) :
		_on_off(initial_state),
		_pin(pin),
		_flash_times(3),
		_flash_wait(333),
		_intensity(100) {
	pinMode(_pin, OUTPUT);
	toggle(_on_off);
}

int8_t Led::pin() {
	return _pin;
}

boolean Led::state() {
	return _on_off;
}

uint8_t Led::intensityPercent() {
	return _intensity;
}

void Led::setPin(int8_t pin) {
	_pin = pin;
	pinMode(_pin, OUTPUT);
	toggle(LOW);
}

void Led::toggle(boolean onOff) {
	if (_pin >= 0 && onOff != _on_off) {
		_on_off = onOff;
		analogWrite(_pin, _on_off ? map(_intensity, 0, 100, 0.0, 1023.0) : 0);
	}
}

void Led::toggle() {
	if (_pin > 0)
		toggle(!_on_off);
}

void Led::on() {
	toggle(true);
}

void Led::off() {
	toggle(false);
}

void Led::flash(uint8_t times, uint16_t wait) {
	if (wait == 0) {
		if(times == 0)
			wait = _flash_wait;
		else
			wait = 1000 / times;
	}
	if (times == 0)
		times = _flash_times;

	for (uint8_t i = 0; i < 2 * times; i++) {
		toggle();
		delay(uint16_t(wait / 2));
	}
}

void Led::setFlash(uint8_t times, uint16_t wait) {
	_flash_times = times;
	_flash_wait = wait;
}
