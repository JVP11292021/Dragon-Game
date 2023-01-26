// Sound.h

#ifndef _SOUND_h
#define _SOUND_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
namespace  arduino{
	void playWii();
	void playWin();
	void playLose();
	void playFireball();
}
#endif

