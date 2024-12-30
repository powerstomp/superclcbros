#ifndef _SETTINGS_H
#define _SETTINGS_H

#include "Utility/NonCopyable.h"

class Settings : public NonCopyable {
	// Use friend for better encapsulation here.
	// We only want the settings screen to change settings.
	friend class StateSettings;

private:
	bool enableMusic = true;
	bool enableSoundEffects = true;

	bool& GetMusicEnabledRef();
	bool& GetSoundEffectsEnabledRef();

public:
	bool IsMusicEnabled() const;
	bool IsSoundEffectsEnabled() const;
};

#endif
