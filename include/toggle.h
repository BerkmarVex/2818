#ifndef TOGGLE_H
#define TOGGLE_H
#include <main.h>

#ifdef __cplusplus

extern "C" {
	#endif

	bool toggle(bool button, bool *prevButton, bool *toggleSwitch) {
		bool temp = &toggleSwitch;

		if(button && !&prevButton) {
			*toggleSwitch = !temp;
			*prevButton = true;
		}

		else if(!button) {
			*prevButton = false;
		}
	}

	#ifdef __cplusplus

}

#endif

#endif
