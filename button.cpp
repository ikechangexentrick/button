
#include "button.h"
#include <Arduino.h>

Button::Button(int pin)
	:	pin(pin), state_prev(true)
{
	t_prev = millis();
}

void Button::callback()
{
	unsigned long cur = millis();
	if (cur - t_prev < BUTTON_INTERVAL_THRESHOLD) return;

	bool state = digitalRead(pin);
	if (state != state_prev) {
		state_prev = state;
		t_prev = cur;
		onButton(state);
	}
}

void Button::onButton(int state)
{
	char buf[32];
 	snprintf(buf, 32, "Button::onButton(%d): %d", pin, state);
 	Serial.println(buf);
}

/* ---------------------------- */

RotarySwitch::RotarySwitch(int pin_1, int pin_2)
	: pin_1(pin_1), pin_2(pin_2)
	, prev_state_1(0), prev_state_2(0)
{}

void RotarySwitch::callback()
{
	bool state_1 = digitalRead(pin_1);
	bool state_2 = digitalRead(pin_2);

	if (prev_state_1 != state_1) {
		prev_state_1 = state_1;
		prev_state_2 = state_2;

		if (state_1 == 0) {
			if (state_1 == state_2) onRotarySW(CCW);
			else onRotarySW(CW);
		}
	}
}

void RotarySwitch::onRotarySW(RSW_DIR dir)
{
	char buf[32];
	snprintf(buf, 32, "RotarySwitch::onRotarySW: %d", dir);
	Serial.println( buf );
}
