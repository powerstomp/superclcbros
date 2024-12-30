#include "StateSettings.h"

#include "../Settings.h"
#include "../Utility/ServiceLocator.h"

StateSettings::StateSettings(Game* game) : StateMenu("Settings", game) {
	auto& settings = ServiceLocator<Settings>::Get();
	AddMenuItem(settings.GetMusicEnabledRef(), "Music");
	AddMenuItem(settings.GetSoundEffectsEnabledRef(), "Sound Effects");
}
