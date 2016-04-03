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

#define L_ON HIGH
#define L_OFF LOW

// ========================================================

class Led {
public:
	Led(int8_t pin = -1, boolean initial_state = L_OFF);
	~Led();
	boolean state();
	uint8_t intensityPercent();
	void setPin(int8_t pin);
	void toggle(boolean onOff);
	void toggle();
	void on();
	void off();
	void flash(uint8_t times = 0, uint16_t wait = 0);
	//void flash();
	void setFlash(uint8_t times = 3, uint16_t wait = 0);
	void setIntensityPercent(uint8_t percent = 100);
	void setFlashSoftness(uint16_t slowness = 0);
	/*
	 void bkgSetFlash( int timesOn = 3, int millisOn = -1, int millisOff = -1);
	 void bkgResetTimer();
	 void bkgFlash();
	 */
private:
	boolean _on_off;
	int8_t _pin;
	uint8_t _flash_times;
	uint16_t _flash_wait;
	uint8_t _intensity;     // in percent (0 - 100)
	uint16_t _toggle_slowness;  // milliseconds to toggle
	/*
	 int _bkg_flash_on_times;
	 int _bkg_flash_on_wait;
	 int _bkg_flash_off_millis;
	 boolean _bkg_flash_current_state;
	 boolean _bkg_flash_current_sub_state;
	 long _bkg_flash_start_millis;
	 */
};

#endif /* Led_H */
