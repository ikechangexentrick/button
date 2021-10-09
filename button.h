#ifndef BUTTON__H
#define BUTTON__H

class Button
{
public:
	Button(int pin);
	virtual ~Button() = default;

	void callback();

	const int get_pin() const
	{ return pin; }

private:
	virtual void onButton(int state);

	const int pin;
	volatile unsigned long t_prev;
	volatile bool state_prev;

	const int BUTTON_INTERVAL_THRESHOLD = 20; // ms
};

class RotarySwitch
{
public:
	enum RSW_DIR {
		CW, CCW
	};

	RotarySwitch(int pin_1, int pin_2);

	void callback();

private:
	virtual void onRotarySW(RSW_DIR dir);

	const int pin_1, pin_2;
	volatile int prev_state_1;
	volatile int prev_state_2;
};

#endif // BUTTON__H
