/*
 * Led.cpp
 *
 *  Created on: 02 Apr 2016
 *      Author: seppe
 */

#include "Led.h"

Led::Led(int8_t pin, boolean initial_state) {
	_on_off = initial_state;
	_pin = pin;
	_flash_times = 3;
	_flash_wait = 333;
	_intensity = 100;
	_toggle_slowness = 0;
	pinMode(_pin, OUTPUT);
	toggle(_on_off);
}

Led::~Led() {
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
	toggle( LOW);
}

void Led::toggle(boolean onOff) {
	if (_pin >= 0 && onOff != _on_off) {
		/*
		 if( _toggle_slowness > 0 ) {
		 float wait = _toggle_slowness/1024.0;
		 float step = (onOff?1:-1) * ;
		 ---> FINISH
		 boolean val = (onOff?0:1024.0);
		 while val>0 && val<1024 {
		 val += step;
		 analogWrite( _pin, int(val) );
		 delay(wait);
		 }
		 }
		 */
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

void Led::flash(uint8_t times = 0, uint16_t wait = 0) {
	if (wait == 0)
		if(times == 0)
			wait = _flash_wait;
		else
			wait = 1000 / times;
	if (times == 0)
		times = _flash_times;

	for (uint8_t i = 0; i < 2 * times; i++) {
		toggle();
		delay(uint16_t(wait / 2));
	}
}
/*
void Led::flash() {
	flash(_flash_times, _flash_wait);
}
*/
void Led::setFlash(uint8_t times, uint16_t wait) {
	_flash_times = times;
	_flash_wait = wait;
}
/*
 void bkgSetFlash( int timesOn, int millisOn, int millisOff)
 {

 if( millisOn < 0 )
 milliOn = 1000 / nOn;

 if( waitOff < 0 )
 waitOff = secondsOn * 2;

 _bkg_flash_on_times = nOn;
 _bkg_flash_on_wait = secondsOn;
 _bkg_flash_off_duration = waitOff;

 bkgResetTimer();
 }

 void bkgResetTimer()
 {
 _bkg_flash_start_millis = millis();
 _bkg_flash_current_state = true;
 _bkg_flash_current_sub_state = false;
 _bkg_flash_current_sub_count = 0;
 }

 void bkgFlash()
 {
 if( _bkg_flash_current_state ) { // if currently in ON state

 }

 if( millis()-_bkg_flash_start_millis > int(READ_VALVE_DELAY*1000.0) ) {
 }
 */

