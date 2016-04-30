/*
 * Led.cpp
 *
 *  Created on: 02 Apr 2016
 *      Author: seppe
 */

#include "Led.h"

Led::Led(int8_t pin) :
		_pin(pin),
		_intensity(0),
		_startIntensity(0),
		_targetIntensity(0),
		_minIntensity(0),
		_maxIntensity(100),
		_fadeDurationMillis(0),
		_flashTimes(3) {
	setPin(_pin);
	_applyIntensityToLed();
}

Led::Led(int8_t pin, uint8_t maxIntensity) :
		Led(pin) {
	setMaxIntensity(maxIntensity);
}

Led::Led(int8_t pin, uint8_t minIntensity, uint8_t maxIntensity) :
		Led(pin) {
	setMinIntensity(minIntensity);
	setMaxIntensity(maxIntensity);
}

void Led::setup() {
}

void Led::loop() {
	if(_intensity != _targetIntensity) {
		/**
		 * Todo: Adapt "t" computation to make _fadeDurationMillis represent the time
		 *       to fade from minIntensity to maxIntensity and not from startIntensity
		 *       to targetIntensity. (Or consider making this an optional behavior.)
		 */
		float k = 1.0;
		if(0)
			k = abs(_targetIntensity-_startIntensity) / (_maxIntensity-_minIntensity);

		float t = k * float(millis()-_startMillis) / _fadeDurationMillis;

		if(t<1.0)
			_intensity = _startIntensity + int8_t(t*float(_targetIntensity-_startIntensity));
		else
			_intensity = _targetIntensity;

		_applyIntensityToLed();
	}
}

int8_t Led::pin() {
	return _pin;
}

boolean Led::isOn() {
	return(_intensity == _maxIntensity);
}

boolean Led::isOff() {
	return(_intensity == _minIntensity);
}

uint8_t Led::intensity() {
	return _intensity;
}

uint8_t Led::minIntensity() {
	return _minIntensity;
}

uint8_t Led::maxIntensity() {
	return _maxIntensity;
}

uint8_t Led::targetIntensity() {
	return _targetIntensity;
}

uint16_t Led::fadeDuration() {
	return _fadeDurationMillis;
}

void Led::setPin(int8_t pin) {
	_pin = pin;
	setup();
}

void Led::setMinIntensity(uint8_t percent) {
	if(percent > _maxIntensity)
		percent = _maxIntensity;
	_minIntensity = percent;

	if(_intensity < _minIntensity)
		setIntensity(_minIntensity);
}

void Led::setMaxIntensity(uint8_t percent) {
	if(percent < _minIntensity)
		percent = _minIntensity;
	if(percent > 100)
		percent = 100;
	_maxIntensity = percent;

	if(_intensity > _maxIntensity)
		setIntensity(_maxIntensity);
}

void Led::setIntensityImmediately(uint8_t percent) {
	if(percent < _minIntensity) {
		percent = _minIntensity;
	}
	else {
		if(percent > _maxIntensity)
			percent = _maxIntensity;
	}
	_intensity = percent;
	_targetIntensity = _intensity;
	_applyIntensityToLed();
}

void Led::setIntensity(uint8_t target) {
	if(_fadeDurationMillis>0) {
		_startIntensity = _intensity;
		_targetIntensity = target;
		_startMillis = millis();
	}
	else {
		_intensity = target;
		_applyIntensityToLed();
	}
}

void Led::setFadeDurationMillis(uint16_t duration) {
	_fadeDurationMillis = duration;
}

void Led::setFlash(uint8_t times) {
	_flashTimes = times;
}

void Led::setFlash(uint8_t times, uint16_t cycleMillis) {
	_flashTimes = times;
	setFadeDurationMillis(uint16_t(cycleMillis/2));
}

void Led::toggle(boolean onOff) {
	if(onOff)
		setIntensity(_maxIntensity);
	else
		setIntensity(_minIntensity);
}

void Led::toggle() {
	if(isOn() || isOff())
		toggle(!isOn());
}

void Led::on() {
	toggle(true);
}

void Led::off() {
	toggle(false);
}

void Led::flash(uint8_t times, uint16_t wait) {
/*
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
*/
}

/**
 * This is the method that actually sets the intensity
 * directly.
 * Caution. No input value check performed!
 */
void Led::_applyIntensityToLed() {
	if(_pin>=0)
		analogWrite(_pin,LED_gamma[_intensity]);
}
