#ifndef _STATESELECTPLAYER_H
#define _STATESELECTPLAYER_H

#include "StateMenu.h"

class StateSelectPlayer : public StateMenu {
private:
	std::string mapPath;
	void AddPlayerType(const std::string name, PlayerType);

public:
	StateSelectPlayer(Game* game, const std::string& mapPath);
};

#endif
