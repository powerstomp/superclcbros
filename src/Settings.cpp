#include "Settings.h"

bool& Settings::GetMusicEnabledRef() {
	return enableMusic;
}
bool& Settings::GetSoundEffectsEnabledRef() {
	return enableSoundEffects;
}

bool Settings::IsMusicEnabled() const {
	return enableMusic;
}
bool Settings::IsSoundEffectsEnabled() const {
	return enableSoundEffects;
}
