#include "Audio.h"

Audio::Audio(string file)
{
	this->file = file;
	audio.loadSound(file);
	audio.setLoop(true);
}

void Audio::start(void) {
	audio.play();
}

void Audio::stop(void) {
	audio.stop();
}

void Audio::setVol(string volumeLevel) {
	if (volumeLevel == "high")
		audio.setVolume(1.0);

	else if(volumeLevel == "normal")
		audio.setVolume(0.6);

	else if(volumeLevel == "low")
		audio.setVolume(0.2);
}

void Audio::setVol(float vol) {
	audio.setVolume(vol);
}


Audio::~Audio(void)
{
}
